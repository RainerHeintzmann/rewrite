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

#define BLOCKAUF '{'
#define BLOCKZU  '}'

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

int cmp_blockstufe (Node * term,int maxstufe)
{
	if (! term) return TRUE;
	if (term->type != SYM_TYPE)
		{
		return (cmp_blockstufe (term->l,maxstufe) && cmp_blockstufe (term->r,maxstufe));
		}
	else
		if (lexval((Symbol *) term) == Term) return cmp_blockstufe (term->l,maxstufe); /* is replaced by tcopy anyway */
		else
			if (defined_in_block((Symbol *) term) > maxstufe)
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
Node * merkold;

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

if (!cmp_blockstufe(froass,defined_in_block((Symbol *) toass))) return FALSE;

merkold=toass->l;
toass->l = tcopy(froass);      /* overwrite directly in the symbol table ! */
delete(merkold);   /* stops before term symbols */
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
	if (IS_kette(TERM_HEAD(jog1->l)) != (Symbol *) NULL)
		{
		ErrorMsg("");
		printfErr("Symbol '");
		print((Node *) TERM_HEAD(jog1->l));
		printfErr("' is already lifted \n");
		return;
		}
if (IS_kette(TERM_HEAD(jog1)) != (Symbol *) NULL)
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
		IS_kette(TERM_HEAD(jog1->l)) = oldsym;
		oldsym = TERM_HEAD(jog1->l);
		IS_Verbindung(oldsym) = TERM_HEAD(jog2->l);
          /* Symbol2 ^^                                 Symbol1 ^^ */
	}

if (jog2->type == Terms) /* jog1 is shorter */
	{
	ErrorMsg("");
	printfErr("Assigned list is too long\n");
	IS_kette(TERM_HEAD(jog1)) = oldsym;
	oldsym = TERM_HEAD(jog1);
	IS_Verbindung(oldsym) = TERM_HEAD(jog2->l);
	}
if (jog1->type == Terms) /* jog1 is longer */
	{
	ErrorMsg("");
	printfErr("Assigned list is too short\n");
	IS_kette(TERM_HEAD(jog1->l)) = oldsym;
	oldsym = TERM_HEAD(jog1->l);
	IS_Verbindung(oldsym) = TERM_HEAD(jog2);
	}
if (jog1->type != Terms && jog2->type != Terms) /* jog1,jog2 have the same length */
	{
	IS_kette(TERM_HEAD(jog1)) = oldsym;
	oldsym = TERM_HEAD(jog1);
	IS_Verbindung(oldsym) = TERM_HEAD(jog2);
	}

if (LIFT_TO(np)->type != Terms)                          /* chain in a circle */
	IS_kette(TERM_HEAD(LIFT_TO(np))) = oldsym;
else
	IS_kette(TERM_HEAD(LIFT_TO(np)->l)) = oldsym;

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
Node * erg;
if (erg=calkulate (np ->r)) 
	{
	print(erg);
	delnum((Symbol *) erg,TRUE); /* also value */
	}
else print(np -> r);

/* printfOut("\t"); */ /* print tab */

history_store(np->r);

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

void numassign2 (Node * froass, Symbol * toass)   /* sets or deletes a number */
{
Node * erg;
while (((froass)->type != Const) && (froass->type != Func))
	{
	if (!(froass->l))	
		{ErrorMsg("Wrong const-assignment : no Valid Term\n");
		return;}
	froass=froass->l;
	}
erg = calkulate(froass);

/* 2026: without a value (e.g. a = nothing) the value is deleted, for every
   sort; otherwise the sort must fit (subsorts allowed) */
if (erg && rtypes(toass) != rtypes((Symbol *) erg)
    && sort_dist(rtypes((Symbol *) erg), rtypes(toass)) < 0)
 	{
 	ErrorMsg("Wrong const-assignment : different types\n");
 	delete(erg);
 	return;
 	}

if (hasval(toass)) DELNUM(toass,value(toass));

if (erg && rtypes((Symbol *) erg) != rtypes(toass))	/* 2026: convert the value (SUBSORT) */
	{
	void * w = sort_convert(value((Symbol *) erg), rtypes((Symbol *) erg), rtypes(toass));
	delete(erg);
	hasval(toass) = (w != NULL);
	value(toass) = w;
	return;
	}
if (erg)
	{
	if (is_shared_num((Symbol *) erg))  /* 0,1: copy the static value, otherwise free() is later called on static memory */
		value(toass) = CPYNUM(erg,value(erg));
	else
		value(toass)  = value(erg);
	hasval(toass) = TRUE;
	delnum((Symbol *) erg,FALSE); /* Do not delete value */
	}
else 
	hasval(toass) = FALSE;
}

void numassign (Node * np)   /* sets or deletes a number */
{
numassign2(ASSIGN_TERM(np),(Symbol *) ASSIGN_TARGET(np));
}

void while_fkt (Node * np)
{
	while (COND_CALL(WHILE_COND(np)))
		CALLFUNCT(WHILE_BODY(np));
}

void if_fkt (Node * np)
{
	DEBG((5,"-- If_fkt ( "));
	DBFK(5, print(COND_ARG(IF_COND(np))));
	DEBG((5,") \n"));
	if (COND_CALL(IF_COND(np)))
		CALLFUNCT(IF_THEN(np));
	else
		if (IF_ELSE(np)) CALLFUNCT(IF_ELSE(np));
}

void forschleife (Node * np)
{
Node * p_anf,
		 * p_ende,
		 * p_step = FOR_STEP(np),
		 * p_symbol;

double anf,ende,step;
long schritte,i;
double counter;    /* local */
double * merkval;
int merkhasval;

if (	!( p_anf = calkulate(FOR_FROM(np)))
	||	!(p_ende = calkulate(FOR_TO(np)))
	||	((p_step) && !(p_step = calkulate(FOR_STEP(np)))))
	{
	ErrorMsg("Wrong FOR-loop: all values must be calculable !\n");
	if (p_anf)  delnum((Symbol *) p_anf,TRUE); /* also value */
	if (p_ende) delnum((Symbol *) p_ende,TRUE); /* also value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* also value */
	return;
	}
/* 2026: also values of subsorts (integer, rational) */
if (! num_to_double((Symbol *) p_anf, & anf)) anf = * (double *) value(p_anf);
if (! num_to_double((Symbol *) p_ende, & ende)) ende = * (double *) value(p_ende);

if (p_step)
	{
	if (! num_to_double((Symbol *) p_step, & step)) step = * (double *) value(p_step);
	}
else
	step = (double) 1.0;

	DEBG((5,"-- Forschleife (%g,%g,%g) \n",anf,ende,step));

if (step == 0) 
	{ErrorMsg("Step must not be zero !\n");
	return;
	}

schritte = ((long) 1) + (long) ((ende-anf)/step);
if  (schritte < 0)
	{ErrorMsg("Step must point in the other direction ! \n");
	delnum((Symbol *) p_anf,TRUE); /* also value */
	delnum((Symbol *) p_ende,TRUE); /* also value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* also value */
	return;
	}

if (FOR_VAR(np) -> type != Const)
	{ErrorMsg("Assigned Term should be a CONST - Value \n");
	delnum((Symbol *) p_anf,TRUE); /* also value */
	delnum((Symbol *) p_ende,TRUE); /* also value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* also value */
	return;
	}

p_symbol = (Node *) TERM_HEAD(FOR_VAR(np));

DEBG((5, "-- Symbol to count : "));
DBFK(5, print(p_symbol));
DEBG((5,"\n"));

merkhasval = hasval(p_symbol);
merkval = (double *) value(p_symbol);

hasval(p_symbol) = TRUE;

value(p_symbol)= & counter;

for (i=0;i<schritte;i++)
	{
	counter = ((double) i)*step+anf;
	if (FOR_BODY(np))				/* otherwise effectively a NOP (instruction is NULL) */
		CALLFUNCT(FOR_BODY(np));
	}

hasval(p_symbol) = merkhasval;
value(p_symbol) = (void *) merkval;

delnum((Symbol *) p_anf,TRUE); /* also value */
delnum((Symbol *) p_ende,TRUE); /* also value */
if (p_step) delnum((Symbol *) p_step,TRUE); /* also value */

return;
}

void changeout (Node * np)
{	
	changeOut(name((Symbol *) np->r));
	return;
}

void readdata (Node * np)
{ double * zahlp;
	zahlp = (double *) malloc(sizeof(double));
  if (! zahlp)
				fatal("readdata: no room for making real-number !\n");
	(* zahlp) = readData();
	if (hasval(np->r) && value(np->r))
		DELNUM(np->r,value(np->r)); /* free the old value */
	value(np->r)=zahlp;
	hasval(np->r)=TRUE;
	return;
}

void changedata (Node * np)
{
	changeData(name((Symbol *) np->r));
	return;
}

void system_fkt (Node * np)
{
	system(name((Symbol *) np->r));
}

void include_fkt (Node * np)
{
	include(name((Symbol *) np -> r));
}

void info_fkt (Node * np)
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

void rewrite_ass_fkt (Node * np)
{
Node * to_rewr = tcopy(REWRASS_TERM(np)); /* no replacing inside terms (TERM t) ; tcopy skips the symbols 'TERM' */
rewrite_begin();
to_rewr = solve(to_rewr,REWRASS_ALGS(np));
rewrite_end();
termassign2(REWRASS_TARGET(np),to_rewr); /* stores a copy */
delete(to_rewr);
}

void rewrite_fkt (Node * np)
{
Node * to_rewr = tcopy(REWR_TERM(np)); /* no replacing inside terms (TERM t) ; tcopy skips the symbols 'TERM' */
rewrite_begin();
to_rewr = solve(to_rewr,REWR_ALGS(np));
rewrite_end();
print(to_rewr);
printfOut("\n");
history_store(to_rewr); /* stores a copy in % */
delete(to_rewr);
}

void quit_fkt (Node * np)
{
	exit(0);
}

BOOLEAN IS_follows(Symbol * from,Symbol * to) /* to is in an IS connection */
{
	Symbol * jog;
	DEBG((4,"DB : IS_follows : from :"));
	DBFK(4,print((Node *) from));
	DEBG((4,"to :"));
	DBFK(4,print((Node *) to));

	for (jog=from;jog != (Symbol *) NULL ;jog=IS_Verbindung(jog))
		{
		if (symeq(jog,to)) /* symbols or values equal */
			{
			DEBG((4," .. returned TRUE\n"));
			return TRUE;
			}
		if (IS_Verbindung(jog) == from) /* once around the circle */
			{
			DEBG((4," .. returned FALSE\n"));
			return FALSE;
			}
		}
	DEBG((4," .. returned FALSE\n"));
	return FALSE;
}

Symbol * IS_search (Symbol * from,Symbol * to)
{
	Symbol * jog;

	DEBG((4,"DB : IS_search : from :"));
	DBFK(4,print((Node *) from));
	DEBG((4,"to :"));
	DBFK(4,print((Node *) to));

	if (IS_follows(from,to))
		return from;
	if (! IS_kette(from))
		return (Symbol *) NULL; /* variable is not entered in any chain ! */

	for (jog=IS_kette(from);jog != from;jog=IS_kette(jog))
		{
		if (! jog)
			{
			fatal("Internal Error: Broken IS_kette ! ");
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
	DBFK(4,print((Node *) which));
	DEBG((4,"from :"));
	DBFK(4,print((Node *) from));

if (symeq(which,from))
	return TRUE;

/* walk the IS connection chain once and detect a possible contradiction : */
for (from2=from,jog2=IS_Verbindung(from);!symeq(from2,which);from2=jog2,jog2=IS_Verbindung(jog2))
	{
	if (jog2 == NULL)
		fatal("ERROR sync.c: lock_rtypes : 'which' does'nt follow from 'from'\n") ; /* end of the chain reached without finding which */
	if ((lock=IS_Verbindung(rtypes(jog2))) != NULL)
			{
			if (lock != from2)
				{	detected=FALSE;
				for (jog=IS_kette(lock);jog!=lock;jog=IS_kette(jog))
					{
					DEBG((4,"DB : lock_rtype : jog :"));
					DBFK(4,print((Node *) jog));
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

for (from2=from,jog2=IS_Verbindung(from);!symeq(from2,which);from2=jog2,jog2=IS_Verbindung(jog2))
	{
	if ((lock=IS_Verbindung(rtypes(jog2))) == NULL)
			{
			IS_Verbindung(rtypes(jog2)) = from2;
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

	case SYM_TYPE: /* VAR (replaced VARs are overwritten with Const or Func)*/
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
   sum of the steps integer -> rational -> real ...; -1 if it does not fit */
static int arg_cost (Node * a, Node * typ)
{
	if (a->type == Terms) return -1;
	return sort_dist(arg_sort(a), typ);
}

static int variant_cost (Symbol * sym, Node * termlist)
{
	Node * at1, * at2, * asym = atypes(sym);
	int atype, cost = 0, c;
	if (! asym) return -1;
	atype = asym->type;
	if (atype == VARPAR) asym = asym->l;
	for (at1=termlist,at2=asym;(at2->r!=NULL);at1=at1->r,at2=at2->r)
		{
		if ((at1->r==NULL) || (at1->type!=Terms)) return -1;
		if ((c = arg_cost(at1->l,at2->l)) < 0) return -1;
		cost += c;
		}
	if (atype == VARPAR)
		for ( ;(at1->r!=NULL) && (at1->type==Terms);at1=at1->r)
			{
			if ((c = arg_cost(at1->l,at2)) < 0) return -1;
			cost += c;
			}
	if ((c = arg_cost(at1,at2)) < 0) return -1;
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
		if (ambig_reported[i] == urs_fkt(a)) return;
	if (nambig < MAXAMBIG) ambig_reported[nambig++] = urs_fkt(a);
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
		sym = kette(sym);
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

	sym=kette(sym); /* next symbol */
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
	int klammerbalance=0;
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
				if (*bp == BLOCKAUF) klammerbalance++;
				if (*bp == BLOCKZU) klammerbalance--;
				}
			DEBG((10,"klammerbal.: %d\n",klammerbalance));
			if (bp > buf + 1 && bp[-2] == '\\' && bp[-1] == '\n')
				{(-- bp)[-1] = ' '; 
				continue;
				}
			if (klammerbalance > 0)
				{if (fp == stdin && interactive)	/* 2026: only in interactive mode */
					{
					fputs("--> ", stdout);
					fflush(stdout);
					}
				 continue;
				}
			if (klammerbalance < 0) klammerbalance=0;

			break;
		}

		if (bp > buf)
			{
			ActualLine=buf;
			lexi_buf(buf);
			yyparse();
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


static void usage (void)
{
	printf("Usage: rewrite [-i] [file ...]\n"
	       "  rewrite              read statements from the keyboard (or a pipe)\n"
	       "  rewrite file ...     run the files, then exit\n"
	       "  rewrite -i file ...  run the files, then continue interactively\n"
	       "  rewrite < file       run a file without prompts (as in scripts)\n");
}

static void welcome (void)
{
	printf("rewrite - a language for symbolic and numerical mathematics\n"
	       "(c) 1992-1996, 2026 Rainer Heintzmann, MIT license\n"
	       "Load the standard library with   INC \"inc/all\"   (paths are relative to\n"
	       "the current folder), then try   REWR D(sin(x)^2,x) : All\n"
	       "End with QUIT or the end-of-file key (Ctrl-D, on Windows Ctrl-Z Enter).\n\n");
}

int main(int argc, char * argv []) /* no space between main and '(' ! */
{
	int i, files = 0, force = 0;
	inc_level=0;
	for (i = 1; i < argc; i++)		/* 2026: options and files */
		{
		if (! strcmp(argv[i], "-h") || ! strcmp(argv[i], "--help")) { usage(); return 0; }
		else if (! strcmp(argv[i], "-i")) force = 1;
		else files++;
		}
	for (i = 1; i < argc; i++)
		if (strcmp(argv[i], "-i"))
			include(argv[i]);	/* like INC "file" */
	if (files && ! force) return 0;
	interactive = force || isatty(fileno(stdin));
	if (interactive && files) putchar(10);	/* finish the output of the files */
	if (interactive) welcome();
	read_input(stdin);
	if (interactive) putchar(10);
	return 0;
}

void include _1a ((cp), const char * cp)
{
	FILE * fp;
	const char * old;

	if (fp = fopen (cp,"r"))
		{
		old=IncFileName;
		IncFileName=cp;
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
		printfErr("Unabel to open includefile \"%s\" \n",cp);
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

