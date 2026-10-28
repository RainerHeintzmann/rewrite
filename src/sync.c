/*
 *	sync.c V1.00
 *	Copyright (c)  Rainer Heintzmann (1992)
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>  /* for ReadInput */
#include <unistd.h> /* isatty (2026) */

#include "sym.h"
#include "syn.h"
#include "run.h"
#include "node.h"  /* for symeq */
#include "sync.h"
#include "numsort.h"		/* 2026: SUBSORT */
#include "inout.h"
#include "defs.h"
#include "nodes.h"
#include "symfn.h"		/* 2026: term_has_builtin */
#include "help.h"		/* 2026: ?name */

#define BLOCK_OPEN '{'
#define BLOCK_CLOSE  '}'

#define BUFFSIZE 65536	/* program stack must be large enough ! (2026: long rules from Rubi) */

#ifdef NO_MAIN
#define main(argc,argv) start_input(argc,argv)
#endif

extern int yyparse(void); /* in syn.c */

void yyerror (const char *);

static const char * IncFileName = "stdin";
static const char * ActualLine = "";

int inc_level=0;

static Symbol LastTerm =
{
{
SYM_TYPE,
NULL,
NULL},
"%",
Term,
NULL, /* any data type */
NULL,
FALSE,
NULL,
NULL,
0,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
0 /* global */
};

Symbol * lastterm =  & LastTerm; /* temporarily stores the last term */

void ErrorMsg(const char * s)
{
	printfErr("\n>> %s",ActualLine);
	printfErr("Error in %s : %s",IncFileName, s);
}


void sequence (Node * np)	/* executes instructions one after another */
{
 	np = np->r;
	while (np)  /* formerly -> type == PARAM */ 
		{
		if (np->l != NULL)
			{
#ifdef DEBUG
			if (np->l->type != FUNC)
				fatal("sequence: ERROR expected a function here !\n");
#endif
			CALLFUNCT(np->l);
			}
		np = np->r;
		}
}	 

BOOLEAN rm_term_in(Node * to_remove,Node ** p_in) /* skips 'to_remove' */
{
BOOLEAN changed = FALSE;
	if (!(* p_in)) return FALSE;
	if (to_remove == (* p_in))
		{(* p_in) =(* p_in)->l;
		 changed = TRUE;
		}
	else /* to_remove != % */
		if (((Node *) lastterm) == (* p_in)) /* do not remember the term dependency of % -> do not delete the term */
			(* p_in) = tcopy((* p_in)->l); /* % is copied, since it is deleted later */

	if (!(* p_in)) return FALSE;

	if ((* p_in) -> l)
		{
		changed = changed | (rm_term_in(to_remove,&((* p_in) ->l)));
		}
	if ((* p_in) -> r)
		{
		changed = changed | (rm_term_in(to_remove,&((* p_in)->r)));
		}		
	return changed;
}

int cmp_block_level (Node * term,int max_level)
{
	if (! term) return TRUE;
	if (term->type != SYM_TYPE)
		{
		return (cmp_block_level (term->l,max_level) && cmp_block_level (term->r,max_level));
		}
	else
		if (lexval((Symbol *) term) == Term) return cmp_block_level (term->l,max_level); /* is replaced by tcopy anyway */
		else
			if (defined_in_block((Symbol *) term) > max_level)
				if (! hasval((Symbol *) term))
					{
					ErrorMsg("");
					printfErr("Local Symbol '%s' should not be assigned to more global Term ! (not done)\n",name((Symbol *) term));
					return FALSE;
					}
				else
					if (IS_FUNCTION(lexval((Symbol *) term)))
						{
						ErrorMsg("");
						printfErr("Local Function '%s' should not be assigned to more global Term ! (not done)\n",name((Symbol *) term));
						return FALSE;
						}
					else return TRUE;
			else
				return TRUE;
return TRUE;
}

int termassign2 (Node * toass, Node * froass)
{
Node * saved_old;

if (froass->type != SYM_TYPE)
	{if (rtypes((Symbol *) toass) != rtypes((Symbol *) (froass->l))
	     && sort_dist(rtypes((Symbol *) (froass->l)), rtypes((Symbol *) toass)) < 0)	/* 2026: subsort allowed */
		{
		ErrorMsg("");
		printfErr("Termsort equals not the used sort ! (Converted to %s )\n",name((Symbol *) rtypes((Symbol *) toass)));
		}
	}
else
	if (rtypes((Symbol *) toass) != rtypes((Symbol *) froass)
	    && sort_dist(rtypes((Symbol *) froass), rtypes((Symbol *) toass)) < 0)
		{
		ErrorMsg("");
		printfErr("Termsort equals not the used sort ! (Converted to %s )\n",name((Symbol *) rtypes((Symbol *) toass)));
		}

if (!cmp_block_level(froass,defined_in_block((Symbol *) toass))) return FALSE;

saved_old=toass->l;
toass->l = tcopy(froass);      /* overwrite directly in the symbol table ! */
delete(saved_old);   /* stops before term symbols */
return TRUE;
}

Node * get_type(Node * np)
{
if (np->type != SYM_TYPE)
	return rtypes((Symbol *)(np->l));     /* setting the variable term type */
else
	return rtypes((Symbol *) np);         /* e.g. Term */
}


void termassign (Node * np)
{
termassign2(ASSIGN_TARGET(np),ASSIGN_TERM(np));
}

void termlist_is_termlist(Node * np)   /* LIFT command */
{
Node * jog1, * jog2;
Symbol * oldsym=(Symbol *) 0;

/* check whether symbols are already bound  */
for (jog1= LIFT_TO(np);jog1->type==Terms; jog1=jog1->r)
	if (IS_chain(TERM_HEAD(jog1->l)) != (Symbol *) NULL)
		{
		ErrorMsg("");
		printfErr("Symbol '");
		print((Node *) TERM_HEAD(jog1->l));
		printfErr("' is already lifted \n");
		return;
		}
if (IS_chain(TERM_HEAD(jog1)) != (Symbol *) NULL)
	{
	ErrorMsg("");
	printfErr("Symbol '");
	print((Node *) TERM_HEAD(jog1));
	printfErr("' is already lifted \n");
	return;
	}


for (jog1= LIFT_TO(np),jog2= LIFT_FROM(np);jog1->type==Terms; jog1=jog1->r,jog2=jog2->r)
	{
		if (jog2->type != Terms)
			break;
		IS_chain(TERM_HEAD(jog1->l)) = oldsym;
		oldsym = TERM_HEAD(jog1->l);
		IS_link(oldsym) = TERM_HEAD(jog2->l);
          /* Symbol2 ^^                                 Symbol1 ^^ */
	}

if (jog2->type == Terms) /* jog1 is shorter */
	{
	ErrorMsg("");
	printfErr("Assigned list is too long\n");
	IS_chain(TERM_HEAD(jog1)) = oldsym;
	oldsym = TERM_HEAD(jog1);
	IS_link(oldsym) = TERM_HEAD(jog2->l);
	}
if (jog1->type == Terms) /* jog1 is longer */
	{
	ErrorMsg("");
	printfErr("Assigned list is too short\n");
	IS_chain(TERM_HEAD(jog1->l)) = oldsym;
	oldsym = TERM_HEAD(jog1->l);
	IS_link(oldsym) = TERM_HEAD(jog2);
	}
if (jog1->type != Terms && jog2->type != Terms) /* jog1,jog2 have the same length */
	{
	IS_chain(TERM_HEAD(jog1)) = oldsym;
	oldsym = TERM_HEAD(jog1);
	IS_link(oldsym) = TERM_HEAD(jog2);
	}

if (LIFT_TO(np)->type != Terms)                          /* chain in a circle */
	IS_chain(TERM_HEAD(LIFT_TO(np))) = oldsym;
else
	IS_chain(TERM_HEAD(LIFT_TO(np)->l)) = oldsym;

return;
}

void history_store (Node * np)
{
if (!(np->l))
	return;    /* store only terms that are not NULL */

rtypes(lastterm)=get_type(np);

termassign2((Node *) lastterm,np);         /* tcopy here, otherwise confusion when it is used */
}

void printterm (Node * np)
{
Node * rslt;
if (rslt=calculate (np ->r)) 
	{
	print(rslt);
	delnum((Symbol *) rslt,TRUE); /* also value */
	}
else if (term_has_builtin(np -> r))	/* 2026: symbolic C functions, e.g. [1,2] + [3,4] */
	{
	rslt = tcalc(tcopy(np -> r));
	print(rslt);
	delete(rslt);
	}
else print(np -> r);
if (pretty_output) printfOut(" ");	/* 2026: a, b: the plain output ends with a blank */

/* printfOut("\t"); */ /* print tab */

history_store(np->r);

}

/* 2026: TYPEOF term: the sort of the term, as the sort system chose it
   when the term was built; for a name also its kind (SYM, TERM, PAT,
   NUMPAT) and its value or term */
static const char * sort_name (Node * s)
{
	return s ? name((Symbol *) s) : "?";
}

void typeof_fn (Node * np)
{
	Node * t = np->r;
	Symbol * sp = NULL;
	if (t->type == Const) sp = (Symbol *) t->l;
	else if (t->type == SYM_TYPE) sp = (Symbol *) t;
	if (sp && find_symbol(name(sp)) == sp)		/* a declared name, no number */
		{
		switch (lexval(sp))
			{
			case Const:
				printfOut("SYM %s : %s", name(sp), sort_name(rtypes(sp)));
				if (hasval(sp))
					{
					printfOut(" = ");
					((void (*) (void *)) show(rtypes(sp))) (value(sp));
					}
				else
					printfOut(" (no value)");
				break;
			case Term:
				printfOut("TERM %s : %s", name(sp), sort_name(rtypes(sp)));
				if (((Node *) sp)->l)
					{
					printfOut(" = ");
					tprint(((Node *) sp)->l, 0);
					}
				else
					printfOut(" (no term)");
				break;
			case Var:
				printfOut("%s %s : %s", hasval(sp) ? "NUMPAT" : "PAT", name(sp), sort_name(rtypes(sp)));
				break;
			default:
				printfOut("%s : %s", name(sp), sort_name(rtypes(sp)));
			}
		printfOut("\n");
		return;
		}
	tprint(t, 0);
	printfOut(": %s\n", sort_name(get_type(t)));
}

/* TYPEOF f: the variants of a function, its argument and result sorts */
static void print_sorts (Node * a)
{
	int var = 0;
	if (! a) { printfOut("()"); return; }
	if (a->type == VARPAR) { var = 1; a = a->l; }
	for ( ; a->r != NULL; a = a->r)
		printfOut("%s,", sort_name(a->l));
	printfOut("%s%s", sort_name(a), var ? "++" : "");
}

void typeof_func (Node * np)
{
	print_variants((Symbol *) np->r);
}

void print_variants (Symbol * f)	/* the variants of a function with their sorts */
{
	Symbol * v = f;
	do	{
		printfOut("%s : ", name(v));
		print_sorts(atypes(v));
		printfOut(" >> %s", sort_name(rtypes(v)));
		if (exe_always(v)) printfOut("   (defined by a term)");
		else if (builtin(v)) printfOut("   (symbolic C function or rules)");
		else if (hasval(v)) printfOut("   (numerical C function)");
		else printfOut("   (symbolic)");
		printfOut("\n");
		v = variants(v);
		} while (v && v != f);
}

void printstring (Node * np)
{char * cp;
cp= name(((Symbol *) (np -> r)));
/* if ((cp[0] == '\\') &&( cp[1] == 'n'))	{cp+=2;	printfOut("\n");	} */
printfOut("%s",cp);
}

void printnl (Node * np)
{
CALLFUNCT(PRINTNL_SEQ(np));
printfOut("\n");
}


void setdebug (Node * np)
{
	double d;
	if (! num_to_double((Symbol *) np->r, & d))	/* 2026: also integer */
		d = * (double *) value(np ->r);
	setDebug((int) d);
}

/* 2026: ALIAS "from" = "to": the name from is read as to (sym.c) */
void alias_fn (Node * np)
{
	alias_def(name((Symbol *) np->r->l), name((Symbol *) np->r->r), 0);
}

void alias_show_fn (Node * np)		/* ALIAS "π" = "pi" SHOW: also the printed name */
{
	alias_def(name((Symbol *) np->r->l), name((Symbol *) np->r->r), 1);
}

/* 2026: PRETTY 1: the output with Unicode (x², √x, π, ·), PRETTY 0: plain
   text that can be read in again by any program; PRETTY alone shows it.
   On at the start of an interactive session. */
int pretty_output = 0;

void pretty_fn (Node * np)
{
	double d;
	if (! np->r) { printf("PRETTY %d\n", pretty_output); return; }
	if (! num_to_double((Symbol *) np->r, & d)) { printfErr("PRETTY : expected 0 or 1\n"); return; }
	pretty_output = d != 0;
}

/* 2026: MAXSTEPS n, MAXDEPTH n set a limit of REWR; without n they show it */
static void set_limit (Node * np, long * limit, const char * what)
{
	double d;
	if (! np->r)
		{
		printf("%s %ld\n", what, * limit);
		return;
		}
	if (! num_to_double((Symbol *) np->r, & d) || d < 1 || d > 1e9)
		{
		printfErr("%s : expected a number from 1 to 10^9\n", what);
		return;
		}
	* limit = (long) d;
}

void maxsteps_fn (Node * np)
{
	set_limit(np, & max_rewrite_steps, "MAXSTEPS");
}

void maxdepth_fn (Node * np)
{
	set_limit(np, & max_term_depth, "MAXDEPTH");
}

/* 2026: AUTOSYM sort: a new name in a term is declared as SYM name : sort,
 * with a note (it may be a typo); AUTOSYM alone switches this off */
static Node * auto_sort = NULL;

void autosym_fn (Node * sort)		/* at parse time, for the lines after it */
{
	auto_sort = sort;
}

void unknown_function (Symbol * sp)	/* f(..) of an undeclared f: an error */
{
	char msg[200];
	snprintf(msg, sizeof msg, "unknown function %s (declare it: FUNC %s : real >> real)", name(sp), name(sp));
	yyerror(msg);
}

/* the new name sp as a constant of the AUTOSYM sort, or NULL (an error) */
Symbol * auto_symbol (Symbol * sp)
{
	if (! auto_sort)
		{
		char msg[200];
		snprintf(msg, sizeof msg, "unknown name %s (declare it: SYM %s : real, or AUTOSYM real)",
		         name(sp), name(sp));
		yyerror(msg);
		return NULL;
		}
	sp = declaresym(sp, auto_sort, NULL, Const, FALSE);
	printfErr("note : SYM %s : %s\n", name(sp), name((Symbol *) auto_sort));
	return sp;
}

void numassign2 (Node * froass, Symbol * toass)   /* sets or deletes a number */
{
Node * rslt;
while (((froass)->type != Const) && (froass->type != Func))
	{
	if (!(froass->l))	
		{ErrorMsg("Wrong assignment to a SYM : no Valid Term\n");
		return;}
	froass=froass->l;
	}
rslt = calculate(froass);

/* 2026: a constant of a sort without values (number, vector, ...) never
   has a value; a = nothing is allowed */
if (rtypes(toass) && ! sort_valued(rtypes(toass)) && (rslt || froass->type == Func))
	{
	ErrorMsg("");
	printfErr("Wrong assignment to a SYM : the sort %s of '%s' has no numerical values;\n"
	          "  declare a value sort (e.g. SYM %s : real), or store a term in a TERM\n",
	          name((Symbol *) rtypes(toass)), name(toass), name(toass));
	if (rslt) delnum((Symbol *) rslt, TRUE);
	return;
	}

/* 2026: a term of a sort without values, assigned to a constant of a wider
   sort with values: converted (a list [1,2,3] for a SYM of sort rvector,
   SUBSORT vector,rvector ATT constr_vec) */
if (! rslt && froass->type == Func && get_type(froass) && rtypes(toass)
    && get_type(froass) != rtypes(toass) && ! sort_valued(get_type(froass))
    && sort_dist(get_type(froass), rtypes(toass)) > 0)
	{
	void * w = term_convert(froass, rtypes(toass));
	if (w)
		{
		if (hasval(toass)) DELNUM(toass,value(toass));
		value(toass) = w;
		hasval(toass) = TRUE;
		return;
		}
	}

/* 2026: a term that can never have a value of the constant's sort is not
   stored: a term of a sort that does not fit, or of a sort without
   numerical values (sort_valued, e.g. the lists of inc/list). An error,
   the constant is not changed (terms are stored in a TERM). Otherwise a
   term without a value deletes the value (a = nothing;
   the library assigns h/(2*pi) before pi has a value). */
if (! rslt && froass->type == Func && get_type(froass)
    && (sort_dist(get_type(froass), rtypes(toass)) < 0 || ! sort_valued(get_type(froass))))
	{
	const char * sn = name((Symbol *) get_type(froass));
	ErrorMsg("");
	printfErr("Wrong assignment to a SYM : the term (sort %s) has no numerical value, '%s' (sort %s) is not changed;\n"
	          "  a term is stored in a TERM, e.g. TERM t : %s\n",
	          sn, name(toass), name((Symbol *) rtypes(toass)), sn);
	return;
	}

/* 2026: without a value (e.g. a = nothing) the value is deleted, for every
   sort; otherwise the sort must fit (subsorts allowed) */
if (rslt && rtypes(toass) != rtypes((Symbol *) rslt)
    && sort_dist(rtypes((Symbol *) rslt), rtypes(toass)) < 0)
 	{
 	ErrorMsg("Wrong assignment to a SYM : different types\n");
 	delete(rslt);
 	return;
 	}

if (hasval(toass)) DELNUM(toass,value(toass));

if (rslt && rtypes((Symbol *) rslt) != rtypes(toass))	/* 2026: convert the value (SUBSORT) */
	{
	void * w = sort_convert(value((Symbol *) rslt), rtypes((Symbol *) rslt), rtypes(toass));
	delete(rslt);
	hasval(toass) = (w != NULL);
	value(toass) = w;
	return;
	}
if (rslt)
	{
	if (is_shared_num((Symbol *) rslt))  /* 0,1: copy the static value, otherwise free() is later called on static memory */
		value(toass) = CPYNUM(rslt,value(rslt));
	else
		value(toass)  = value(rslt);
	hasval(toass) = TRUE;
	delnum((Symbol *) rslt,FALSE); /* Do not delete value */
	}
else 
	hasval(toass) = FALSE;
}

void numassign (Node * np)   /* sets or deletes a number */
{
numassign2(ASSIGN_TERM(np),(Symbol *) ASSIGN_TARGET(np));
}

void while_fn (Node * np)
{
	while (! rw_interrupted && COND_CALL(WHILE_COND(np)))	/* 2026: Ctrl-C ends it */
		CALLFUNCT(WHILE_BODY(np));
}

void if_fn (Node * np)
{
	DEBG((5,"-- If_fkt ( "));
	DBFN(5, print(COND_ARG(IF_COND(np))));
	DEBG((5,") \n"));
	if (COND_CALL(IF_COND(np)))
		CALLFUNCT(IF_THEN(np));
	else
		if (IF_ELSE(np)) CALLFUNCT(IF_ELSE(np));
}

void for_loop (Node * np)
{
Node * p_from,
		 * p_to,
		 * p_step = FOR_STEP(np),
		 * p_symbol;

double from_val,to_val,step;
long nsteps,i;
double counter;    /* local */
double * saved_val;
int saved_hasval;

if (	!( p_from = calculate(FOR_FROM(np)))
	||	!(p_to = calculate(FOR_TO(np)))
	||	((p_step) && !(p_step = calculate(FOR_STEP(np)))))
	{
	ErrorMsg("Wrong FOR-loop: all values must be calculable !\n");
	if (p_from)  delnum((Symbol *) p_from,TRUE); /* also value */
	if (p_to) delnum((Symbol *) p_to,TRUE); /* also value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* also value */
	return;
	}
/* 2026: also values of subsorts (integer, rational) */
if (! num_to_double((Symbol *) p_from, & from_val)) from_val = * (double *) value(p_from);
if (! num_to_double((Symbol *) p_to, & to_val)) to_val = * (double *) value(p_to);

if (p_step)
	{
	if (! num_to_double((Symbol *) p_step, & step)) step = * (double *) value(p_step);
	}
else
	step = (double) 1.0;

	DEBG((5,"-- For loop (%g,%g,%g) \n",from_val,to_val,step));

if (step == 0) 
	{ErrorMsg("Step must not be zero !\n");
	return;
	}

nsteps = ((long) 1) + (long) ((to_val-from_val)/step);
if  (nsteps < 0)
	{ErrorMsg("Step must point in the other direction ! \n");
	delnum((Symbol *) p_from,TRUE); /* also value */
	delnum((Symbol *) p_to,TRUE); /* also value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* also value */
	return;
	}

if (FOR_VAR(np) -> type != Const)
	{ErrorMsg("Assigned Term should be a SYM with a value \n");
	delnum((Symbol *) p_from,TRUE); /* also value */
	delnum((Symbol *) p_to,TRUE); /* also value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* also value */
	return;
	}

p_symbol = (Node *) TERM_HEAD(FOR_VAR(np));

DEBG((5, "-- Symbol to count : "));
DBFN(5, print(p_symbol));
DEBG((5,"\n"));

saved_hasval = hasval(p_symbol);
saved_val = (double *) value(p_symbol);

hasval(p_symbol) = TRUE;

value(p_symbol)= & counter;

for (i=0;i<nsteps && ! rw_interrupted;i++)	/* 2026: Ctrl-C ends it */
	{
	counter = ((double) i)*step+from_val;
	if (FOR_BODY(np))				/* otherwise effectively a NOP (instruction is NULL) */
		CALLFUNCT(FOR_BODY(np));
	}

hasval(p_symbol) = saved_hasval;
value(p_symbol) = (void *) saved_val;

delnum((Symbol *) p_from,TRUE); /* also value */
delnum((Symbol *) p_to,TRUE); /* also value */
if (p_step) delnum((Symbol *) p_step,TRUE); /* also value */

return;
}

void changeout (Node * np)
{	
	changeOut(name((Symbol *) np->r));
	return;
}

void readdata (Node * np)
{ double * nump;
	nump = (double *) malloc(sizeof(double));
  if (! nump)
				fatal("readdata: no room for making real-number !\n");
	(* nump) = readData();
	if (hasval(np->r) && value(np->r))
		DELNUM(np->r,value(np->r)); /* free the old value */
	value(np->r)=nump;
	hasval(np->r)=TRUE;
	return;
}

void changedata (Node * np)
{
	changeData(name((Symbol *) np->r));
	return;
}

void system_fn (Node * np)
{
	system(name((Symbol *) np->r));
}

void include_fn (Node * np)
{
	include(name((Symbol *) np -> r));
}

void info_fn (Node * np)
{
printfOut("Object        : %s\n",name((Symbol *) np->r ));
printfOut("is a          : %s\n",type((Symbol *) np->r ));
if ((lexval((Symbol *) np->r) == Id) ||
		(lexval((Symbol *) np->r) == Sort)) return;

printfOut("result-type   : ");
if (rtypes((Symbol *) np->r )) tprint(rtypes((Symbol *) np->r ),0);
else printfOut("none");
printfOut("\n");
printfOut("argument-type : ");
if (atypes((Symbol *) np->r )) tprint(atypes((Symbol *) np->r ),0);
else printfOut("none");
printfOut("\n");
if	(((lexval((Symbol *) np->r) == Const) ||
		 ((lexval((Symbol *) np->r) == Var))) &&
		 (hasval((Symbol *) np->r))) {
		 printfOut("Value         : ");
		 tprint(np->r,0);
     printfOut("\n"); }
else
	if (hasval((Symbol *) np->r)) printfOut("is attached to a C-function \n");
}

/* 2026: the first TERM in t that has no term yet (declared, never
   assigned), or NULL */
static Symbol * empty_term (Node * t)
{
	Symbol * s;
	if (! t) return NULL;
	if (t->type == SYM_TYPE)
		{
		if (lexval((Symbol *) t) != Term) return NULL;
		return t->l ? empty_term(t->l) : (Symbol *) t;
		}
	if ((s = empty_term(t->l)) != NULL) return s;
	return empty_term(t->r);
}

/* TRUE (and an error message) if t uses a TERM without a term */
static int term_missing (Node * t)
{
	Symbol * s = empty_term(t);
	if (! s) return FALSE;
	ErrorMsg("");
	printfErr("TERM %s has no term yet: assign one first, e.g. %s = REWR ... : All\n", name(s), name(s));
	return TRUE;
}

void rewrite_ass_fn (Node * np)
{
Node * to_rewr;
if (term_missing(REWRASS_TERM(np))) return;
to_rewr = tcopy(REWRASS_TERM(np)); /* no replacing inside terms (TERM t) ; tcopy skips the symbols 'TERM' */
rewrite_begin();
to_rewr = tcalc(to_rewr);	/* 2026: as after each rule set, also before the first (laplace(..) by its rules) */
to_rewr = solve(to_rewr,REWRASS_ALGS(np));
rewrite_end();
termassign2(REWRASS_TARGET(np),to_rewr); /* stores a copy */
delete(to_rewr);
}

void rewrite_fn (Node * np)
{
Node * to_rewr;
if (term_missing(REWR_TERM(np))) return;
to_rewr = tcopy(REWR_TERM(np)); /* no replacing inside terms (TERM t) ; tcopy skips the symbols 'TERM' */
rewrite_begin();
to_rewr = tcalc(to_rewr);	/* 2026: as after each rule set, also before the first (laplace(..) by its rules) */
to_rewr = solve(to_rewr,REWR_ALGS(np));
rewrite_end();
print(to_rewr);
printfOut("\n");
history_store(to_rewr); /* stores a copy in % */
delete(to_rewr);
}

void quit_fn (Node * np)
{
	exit(0);
}

BOOLEAN IS_follows(Symbol * from,Symbol * to) /* to is in an IS connection */
{
	Symbol * jog;
	DEBG((4,"DB : IS_follows : from :"));
	DBFN(4,print((Node *) from));
	DEBG((4,"to :"));
	DBFN(4,print((Node *) to));

	for (jog=from;jog != (Symbol *) NULL ;jog=IS_link(jog))
		{
		if (symeq(jog,to)) /* symbols or values equal */
			{
			DEBG((4," .. returned TRUE\n"));
			return TRUE;
			}
		if (IS_link(jog) == from) /* once around the circle */
			{
			DEBG((4," .. returned FALSE\n"));
			return FALSE;
			}
		}
	DEBG((4," .. returned FALSE\n"));
	return FALSE;
}

/* 2026: a pattern with a symbolic variant of a function (one without a
   numerical C function, like + : number,number, or a symbolic C function
   like D) also matches the variants on narrower
   sorts: + : real,real and + : complex,real, as a method for Number in
   Julia applies to Float64. Variants with a C function (+ : real,real,
   + : integer,integer) match only themselves, as before. */
static BOOLEAN sort_fits (Node * t, Node * p)
{
	return t && p && sort_dist(t, p) >= 0;
}

BOOLEAN variant_fits (Symbol * t, Symbol * p)
{
	Node * at = atypes(t), * ap = atypes(p);
	if (t == p) return TRUE;
	if (! at || ! ap || name(t)[0] != name(p)[0] || strcmp(name(t), name(p)) != 0) return FALSE;
	if (hasval(p) && ! builtin(p)) return FALSE;	/* no numerical C function: a symbolic variant */
	if (! sort_fits(rtypes(t), rtypes(p))) return FALSE;
	if ((at->type == VARPAR) != (ap->type == VARPAR)) return FALSE;
	if (at->type == VARPAR) { at = at->l; ap = ap->l; }
	for ( ; at->r != NULL && ap->r != NULL; at = at->r, ap = ap->r)
		if (! sort_fits(at->l, ap->l)) return FALSE;
	if ((at->r != NULL) != (ap->r != NULL)) return FALSE;
	return sort_fits(at, ap);
}

Symbol * IS_search (Symbol * from,Symbol * to)
{
	Symbol * jog;

	DEBG((4,"DB : IS_search : from :"));
	DBFN(4,print((Node *) from));
	DEBG((4,"to :"));
	DBFN(4,print((Node *) to));

	if (IS_follows(from,to))
		return from;
	if (! IS_chain(from))
		return (Symbol *) NULL; /* variable is not entered in any chain ! */

	for (jog=IS_chain(from);jog != from;jog=IS_chain(jog))
		{
		if (! jog)
			{
			fatal("Internal Error: Broken IS_chain ! ");
			}
		if (IS_follows(jog,to))
			return jog;
		}
	return (Symbol *) NULL;
}

BOOLEAN lock_rtypes (Symbol * which,Symbol * from,Node * * chain)
{
	Symbol * lock,* jog,* jog2,* from2;
	BOOLEAN detected=FALSE;

	DEBG((4,"DB : lock_rtypes : which :"));
	DBFN(4,print((Node *) which));
	DEBG((4,"from :"));
	DBFN(4,print((Node *) from));

if (symeq(which,from))
	return TRUE;

/* walk the IS connection chain once and detect a possible contradiction : */
for (from2=from,jog2=IS_link(from);!symeq(from2,which);from2=jog2,jog2=IS_link(jog2))
	{
	if (jog2 == NULL)
		fatal("ERROR sync.c: lock_rtypes : 'which' does'nt follow from 'from'\n") ; /* end of the chain reached without finding which */
	if ((lock=IS_link(rtypes(jog2))) != NULL)
			{
			if (lock != from2)
				{	detected=FALSE;
				for (jog=IS_chain(lock);jog!=lock;jog=IS_chain(jog))
					{
					DEBG((4,"DB : lock_rtype : jog :"));
					DBFN(4,print((Node *) jog));
					DEBG((4,"\n"));

					if (jog == from2)
						{
						DEBG((4," .. detected old\n"));
						detected=TRUE;
						}
					if (jog == (Symbol *) NULL)
						fatal("INTERNAL ERROR: sync.c:  lock_rtype got NULL");
					}
				}
			else
				detected=TRUE;
			if (! detected)
				{
				DEBG((4," did not detect one, returned FALSE\n"));
				return FALSE; /* locked differently */
				}
			}
	}

/* no wrongly locked set present -> lock the remaining ones */

for (from2=from,jog2=IS_link(from);!symeq(from2,which);from2=jog2,jog2=IS_link(jog2))
	{
	if ((lock=IS_link(rtypes(jog2))) == NULL)
			{
			IS_link(rtypes(jog2)) = from2;
			* chain = mknod(CHAIN,* chain,rtypes(jog2)); /* skewer them so they can be deleted again */
			
			DEBG((4," .. established new\n"));
			}
	}


	DEBG((4,"lock_rtypes returned TRUE\n"));
			
return TRUE;
			
}

BOOLEAN eq_rtypes(Node * a,Node * typ)
{
	switch(a->type)
	{
	case Terms:
		DEBG((4,"DB : eq_rtypes : a->type is 'Terms' \n"));
		return FALSE;

	case SYM_TYPE: /* PAT (replaced PATs are overwritten with Const or Func)*/
		DEBG((4,"DB : eq_rtypes Termsort : %s  required sort : %s \n",name((Symbol *) (rtypes((Symbol *)(a)))),name((Symbol *) (typ))));
		if (typ!=rtypes((Symbol *) (a))) /* ! eq_sorts(typ,rtypes..) causes immediate reduction */
			 return FALSE;
	break;

	default:                          /* Funct ,Const */
		DEBG((4,"DB : eq_rtypes Termsort : %s  required sort : %s \n",name((Symbol *) (rtypes((Symbol *)(a->l)))),name((Symbol *) (typ))));
		if (typ!=rtypes((Symbol *) (a->l))) /* ! eq_sorts(typ,rtypes..) causes immediate reduction */
			return FALSE;
	break;
	}

return TRUE;		
}


/* 2026: cost of a variant with extension of the sorts (SUBSORT):
   sum of the steps integer -> rational -> real ... (see arg_cost); -1 if
   it does not fit */
/* twice the steps; a term of a sort without values that a numerical C
   function would get converted into a value (a list [1,2] for an rvector,
   term_convert) counts one more, so that an equally long widening that
   keeps the term symbolic wins */
static int arg_cost (Node * a, Node * typ, int numeric)
{
	Node * as;
	int d;
	if (a->type == Terms) return -1;
	as = arg_sort(a);
	d = sort_dist(as, typ);
	if (d <= 0) return d;
	return 2 * d + (numeric && as && ! sort_valued(as) ? 1 : 0);
}

static int variant_cost (Symbol * sym, Node * termlist)
{
	Node * at1, * at2, * asym = atypes(sym);
	int atype, cost = 0, c, num = hasval(sym) && ! builtin(sym) && ! exe_always(sym);
	if (! asym) return -1;
	atype = asym->type;
	if (atype == VARPAR) asym = asym->l;
	for (at1=termlist,at2=asym;(at2->r!=NULL);at1=at1->r,at2=at2->r)
		{
		if ((at1->r==NULL) || (at1->type!=Terms)) return -1;
		if ((c = arg_cost(at1->l,at2->l,num)) < 0) return -1;
		cost += c;
		}
	if (atype == VARPAR)
		for ( ;(at1->r!=NULL) && (at1->type==Terms);at1=at1->r)
			{
			if ((c = arg_cost(at1->l,at2,num)) < 0) return -1;
			cost += c;
			}
	if ((c = arg_cost(at1,at2,num)) < 0) return -1;
	return cost + c;
}

/* variant with the fewest extensions, or NULL. A variant that fits exactly
   has cost 0, so a specific variant (+ : real,complex) always wins over a
   general one reached by conversions (+ : complex,complex), as the most
   specific method in Julia. If two variants need equally few conversions,
   the first declared one is used, and this is reported once per function. */
#define MAXAMBIG 64
static Symbol * ambig_reported[MAXAMBIG];
static int nambig = 0;

static void report_ambiguous (Symbol * a, Symbol * b, Node * termlist)
{
	Node * t;
	int i;
	for (i = 0; i < nambig; i++)
		if (ambig_reported[i] == orig_func(a)) return;
	if (nambig < MAXAMBIG) ambig_reported[nambig++] = orig_func(a);
	printfErr("warning : ambiguous variants of '%s' for the argument sorts (", name(a));
	for (t = termlist; t; t = (t->type == Terms) ? t->r : NULL)
		{
		Node * s = arg_sort(t->type == Terms ? t->l : t);
		printfErr("%s%s", s ? name((Symbol *) s) : "?", (t->type == Terms && t->r) ? "," : "");
		}
	printfErr("): the results %s and %s need equally many conversions; the first is used\n",
	          name(rtypes(a) ? (Symbol *) rtypes(a) : a), name(rtypes(b) ? (Symbol *) rtypes(b) : b));
}

Symbol * getsymbol_widen (Symbol * symbol,Node * termlist)
{
	Symbol * sym = symbol, * best = NULL, * tie = NULL;
	int bestc = -1, c;
	if (! termlist) return NULL;
	do	{
		c = variant_cost(sym, termlist);
		if (c >= 0 && (bestc < 0 || c < bestc))
			{
			bestc = c;
			best = sym;
			tie = NULL;
			}
		else if (c >= 0 && c == bestc && ! tie)
			tie = sym;
		sym = variants(sym);
		} while ((sym != (Symbol *) NULL) && (sym != symbol));
	if (tie && bestc > 0) report_ambiguous(best, tie, termlist);
	return best;
}

/* 2026: after inserting a right-hand side, choose for every function the
   cheapest variant for the actual sorts of the arguments.
   LIFTing replaces all symbols of one sort by those of another; with
   subsorts (integer < rational < real) the arguments then do not always
   fit. Without SUBSORT the variants fit exactly and nothing changes. */
void retype_term (Node * t)
{
	Node * a;
	if (! t) return;
	if (t->type != Func)
		{
		if (t->type != SYM_TYPE && t->type != Const)
			{
			retype_term(t->l);
			retype_term(t->r);
			}
		return;
		}
	for (a = TERM_ARGS(t); a; a = ARGS_NEXT(a))
		retype_term(ARGS_ITEM(a));
	retype_node(t);
}

/* only this node (the arguments are already correct) */
void retype_node (Node * t)
{
	Symbol * best;
	int c, cb;
	if (! t || t->type != Func) return;
	if (! TERM_ARGS(t) || ! atypes(TERM_HEAD(t))) return;
	c = variant_cost(TERM_HEAD(t), TERM_ARGS(t));
	if (c == 0) return;
	best = getsymbol_widen(TERM_HEAD(t), TERM_ARGS(t));
	if (! best || best == TERM_HEAD(t)) return;
	cb = variant_cost(best, TERM_ARGS(t));
	if (c < 0 || cb < c)
		t->l = (Node *) best;
}

Symbol * getsymbol (Symbol * symbol,Node * termlist) /* picks, among symbols of the same name, the one with the right arguments */
{                                                    /* termlist is the list of the arguments actually present */
	Node * at1,* at2,* asym;
	Symbol * sym=symbol;           /* symbols are chained in a circle */
	int			varcount=-1,atype;
	BOOLEAN iseq;

	if (! termlist) fatal("Internal ERROR : No termlist in getsymbol\n ");	

	do	{       /* runs through the individual functions */
		iseq=TRUE;	
		varcount = -1;

		asym = atypes(sym); /* sym cannot be NULL ! */
		atype= asym->type;

		if (atype == VARPAR)
			{
			asym=asym->l;
			}

		for (at1=termlist,at2=asym;(at2->r!=NULL);at1=at1->r,at2=at2->r)
			{
			if ((at1->r==NULL) || (at1->type!=Terms) )
				{iseq=FALSE;break;}
			if (! eq_rtypes(at1->l,at2->l))
				{iseq=FALSE;break;}
			}

		if (iseq)
			if (atype == VARPAR)
				{
				for (varcount=0;(at1->r!=NULL) && (at1->type==Terms);at1=at1->r,varcount++)
					if (! eq_rtypes(at1->l,at2))
						{iseq=FALSE;break;}
				}

		if (iseq)
			if (! eq_rtypes(at1,at2))
				{iseq=FALSE;}

	DEBG((4,"DB : -getsymbol  reached last parameter \n"));

		if (iseq) break;

	sym=variants(sym); /* next symbol */
	}  while	((sym != (Symbol *) NULL) && (sym != symbol));  /* NULL for the case of only one symbol */

	if (iseq==FALSE)		/* 2026: with extension of the sorts (SUBSORT) */
		{
		Symbol * w = getsymbol_widen(symbol, termlist);
		if (w)
			return w;
		}
	if (iseq==FALSE)
		{
		ErrorMsg("");
		printfErr("Used wrong argumenttype or -number for Funktion '%s' !\n",name(symbol));
		sym=symbol; /* use the first definition */
		}
	else
		if (varcount != -1)
			{
			DEBG((4,"DB : -getsymbol  varcount is %d \n",varcount));
			}

	return sym;
}


static int interactive = 0;	/* 2026: input from the keyboard: greeting, prompt */

int read_input _1a ((fp), FILE * fp)
{	
	char buf[BUFFSIZE], * bp;
	char * const ep = buf + sizeof buf;
	int bracket_balance=0;
	void lexi_buf _1p (const char *);


	do
	{	if (fp == stdin && interactive)		/* 2026: prompt */
			{
			fputs("> ", stdout);
			fflush(stdout);
			}
		for (bp = buf; bp < ep && fgets(bp, ep - bp, fp); ) /* calls yacc line by line */
		{	
			if (fp != stdin)
				DEBG((1,bp));  /* text from file to the screen */

			for (;*bp != '\0';bp++)
				{
				if (*bp == BLOCK_OPEN) bracket_balance++;
				if (*bp == BLOCK_CLOSE) bracket_balance--;
				}
			DEBG((10,"klammerbal.: %d\n",bracket_balance));
			if (bp > buf + 1 && bp[-2] == '\\' && bp[-1] == '\n')
				{(-- bp)[-1] = ' '; 
				continue;
				}
			if (bracket_balance > 0)
				{if (fp == stdin && interactive)	/* 2026: only in interactive mode */
					{
					fputs("--> ", stdout);
					fflush(stdout);
					}
				 continue;
				}
			if (bracket_balance < 0) bracket_balance=0;

			break;
		}

		/* 2026: a UTF-8 byte order mark (Notepad, PowerShell pipes) is no input */
		if (bp - buf >= 3 && (unsigned char) buf[0] == 0xEF && (unsigned char) buf[1] == 0xBB
		    && (unsigned char) buf[2] == 0xBF)
			{
			memmove(buf, buf + 3, bp - buf - 2);
			bp -= 3;
			}
		if (ferror(fp)) clearerr(fp);	/* 2026: a Ctrl-C while reading (Windows console) */
		rw_interrupted = 0;		/* 2026: a Ctrl-C before this line does not count */
		if (bp > buf && ! help_line(buf))	/* 2026: ?name prints the help (help.c) */
			{
			ActualLine=buf;
			lexi_buf(buf);
			yyparse();
			}
		if (fp == stdin)	/* 2026: a program reading through a pipe gets each answer at once */
			{
			fflush(stdout);
			fflush(stderr);
			}

	} while (! feof(fp));
	return 0;
}

int parse_it(char * text)
{
void lexi_buf(const char *); /* prototype */

lexi_buf(text);
yyparse();
return 0;
}


#ifndef REWRITE_VERSION
#define REWRITE_VERSION "2026"
#endif

static void usage (void)
{
	printf("Usage: rewrite [-i] [--no-startup] [--max-steps n] [--max-depth n] [file ...]\n"
	       "  rewrite              read statements from the keyboard (or a pipe)\n"
	       "  rewrite file ...     run the files, then exit\n"
	       "  rewrite -i file ...  run the files, then continue interactively\n"
	       "  rewrite < file       run a file without prompts (as in scripts)\n"
	       "An interactive session first runs ~/.rewrite/startup.rw if it exists\n"
	       "(~ is HOME, else USERPROFILE); --no-startup skips it.\n"
	       "--max-steps n   REWR stops after n rewrites (default 100000), as MAXSTEPS n\n"
	       "--max-depth n   REWR stops when the term is deeper than n levels (default\n"
	       "                1000), as MAXDEPTH n\n"
	       "--version       the version of rewrite\n"
	       "Library files (INC \"inc/all\") not found from the current folder are looked\n"
	       "for in the folders of REWRITE_PATH, the installation and next to the program.\n");
}

/* 2026: the startup file of an interactive session, as Julia's startup.jl:
   ~/.rewrite/startup.rw (~ is HOME, else USERPROFILE); the path or NULL */
static char startup_path[1024];

static const char * startup_file (void)
{
	/* HOME first, then the Windows home: in the MSYS2 shell HOME is
	   C:\msys64\home\<user>, elsewhere only USERPROFILE C:\Users\<user> */
	const char * homes[3];
	FILE * f;
	int i;
	homes[0] = getenv("HOME");
	homes[1] = getenv("USERPROFILE");
	homes[2] = windows_home();	/* the same, from Windows (console.c) */
	for (i = 0; i < 3; i++)
		{
		if (! homes[i] || ! * homes[i]) continue;
		snprintf(startup_path, sizeof startup_path, "%s/.rewrite/startup.rw", homes[i]);
		if ((f = fopen(startup_path, "r")) != NULL)
			{
			fclose(f);
			return startup_path;
			}
		}
	return NULL;
}

static void welcome (void)
{
	printf("rewrite - a language for symbolic and numerical mathematics\n"
	       "(c) 1992-1996, 2026 Rainer Heintzmann, MIT license\n"
	       "Load the standard library with   INC \"inc/all\"\n"
	       "then try   REWR D(sin(x)^2,x) : All\n"
	       "End with QUIT or the end-of-file key (Ctrl-D, on Windows Ctrl-Z Enter).\n\n");
}

int main(int argc, char * argv []) /* no space between main and '(' ! */
{
	int i, files = 0, force = 0, nostart = 0;
	const char * start = NULL;
	inc_level=0;
	console_utf8();		/* 2026: Unicode names, console.c */
	for (i = 1; i < argc; i++)		/* 2026: options and files; an option is removed */
		{
		long * limit = NULL;
		if (! strcmp(argv[i], "-h") || ! strcmp(argv[i], "--help")) { usage(); return 0; }
		else if (! strcmp(argv[i], "--version")) { printf("rewrite %s\n", REWRITE_VERSION); return 0; }
		else if (! strcmp(argv[i], "-i")) force = 1;
		else if (! strcmp(argv[i], "--no-startup")) nostart = 1;
		else if (! strcmp(argv[i], "--max-steps")) limit = & max_rewrite_steps;
		else if (! strcmp(argv[i], "--max-depth")) limit = & max_term_depth;
		else { files++; continue; }
		if (limit)
			{
			char * end = NULL;
			long n = i + 1 < argc ? strtol(argv[i + 1], & end, 10) : 0;
			if (n < 1 || * end)
				{
				fprintf(stderr, "rewrite : %s needs a number from 1 on\n", argv[i]);
				return 1;
				}
			* limit = n;
			argv[i++] = NULL;
			}
		argv[i] = NULL;
		}
	/* an interactive session (not a script, a pipe or the tests): Ctrl-C stops a
	   computation instead of ending rewrite; the startup file first */
	if (force || (! files && isatty(fileno(stdin))))
		{
		pretty_output = 1;		/* x², √x; scripts, pipes and tests stay plain */
		signal(SIGINT, on_interrupt);
		if (! nostart && (start = startup_file()) != NULL)
			include(start);
		}
	for (i = 1; i < argc; i++)
		if (argv[i])
			include(argv[i]);	/* like INC "file" */
	if (files && ! force) return 0;
	interactive = force || isatty(fileno(stdin));
	if (interactive && files) putchar(10);	/* finish the output of the files */
	if (interactive) welcome();
	if (interactive && start) printf("(the startup file %s was run)\n", start);
	read_input(stdin);
	if (interactive) putchar(10);
	return 0;
}

/* 2026: a file that is not found from the current folder (a relative name
   like "inc/all") is looked for in the library folders: those in
   REWRITE_PATH (separated by ':', on Windows by ';'), the folder of the
   installation (REWRITE_LIBDIR, set by make install), and the folder of
   the program and its ../share/rewrite. path gets the name of the file. */
#ifdef _WIN32
#define PATH_SEP ';'
#else
#define PATH_SEP ':'
#endif

static FILE * open_in (const char * dir, size_t len, const char * name, char * path, size_t size)
{
	if (len == 0 || len + strlen(name) + 2 > size) return NULL;
	snprintf(path, size, "%.*s/%s", (int) len, dir, name);
	return fopen(path, "r");
}

static FILE * open_library_file (const char * name, char * path, size_t size)
{
	FILE * fp;
	const char * dir, * end;
	snprintf(path, size, "%s", name);
	if ((fp = fopen(name, "r")) != NULL) return fp;
	if (name[0] == '/' || name[0] == '\\' || (name[0] && name[1] == ':'))
		return NULL;			/* an absolute name */
	for (dir = getenv("REWRITE_PATH"); dir && * dir; dir = * end ? end + 1 : end)
		{
		end = strchr(dir, PATH_SEP);
		if (! end) end = dir + strlen(dir);
		if ((fp = open_in(dir, end - dir, name, path, size)) != NULL) return fp;
		}
#ifdef REWRITE_LIBDIR
	if ((fp = open_in(REWRITE_LIBDIR, strlen(REWRITE_LIBDIR), name, path, size)) != NULL) return fp;
#endif
	if ((dir = program_dir()) != NULL)
		{
		char share[4096];
		if ((fp = open_in(dir, strlen(dir), name, path, size)) != NULL) return fp;
		snprintf(share, sizeof share, "%s/../share/rewrite", dir);
		if ((fp = open_in(share, strlen(share), name, path, size)) != NULL) return fp;
		}
	snprintf(path, size, "%s", name);
	return NULL;
}

void include _1a ((cp), const char * cp)
{
	FILE * fp;
	const char * old;
	char path[4096];

	if ((fp = open_library_file(cp, path, sizeof path)) != NULL)
		{
		old=IncFileName;
		IncFileName=path;
		int oldbase;
		is_not_running();
		inc_level++;
		oldbase = include_begin(); /* treat file like top-level input */
		read_input(fp);
		include_end(oldbase);
		inc_level--;
		fclose (fp);
		is_running();
		IncFileName=old;
		}
	else
		{
		ErrorMsg("");
		printfErr("Unable to open includefile \"%s\" (also not in the library folders, see REWRITE_PATH)\n",cp);
		}
}

void yyerror (const char * s)
{
	end_all_blocks();
	is_not_running();
	ErrorMsg(s);
	printfErr("\n");
}
int yywrap(void) /* called by flex: 1 = end of input */
{
return 1;
}

