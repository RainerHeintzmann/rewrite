/*
 *	run.c V1.00
 *
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *
 *	Variables
 */

#include <string.h> /* for strcmp */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>	/* 2026: Ctrl-C */
#include "strsave.h"

#include "inout.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "stack.h"
#include "forms.h"
#include "userfn.h"
#include "sync.h" /* for IS_follows,IS_search  */
#include "node.h"
#include "defs.h"
#include "nodes.h"
#include "symfn.h"
#include "listmatch.h"
#include "numsort.h"	/* 2026: SUBSORT */

#define EQUAL  0	/* important because of strcmp */


Node * numbertype = NULL;

static int mistake = FALSE;

static BOOLEAN didrewrite = FALSE; /* for chaining the algebras : (real;diff);more -> not reentrant */

BOOLEAN truefunc _1p (Node *);
BOOLEAN in_tree2 _2p(Node * npl,Node * npr);
int tcmp _2p(Node * a, Node * b);      /* forward : compares trees  1 : a>b */


Node var_chain =
{CHAIN,
NULL,
NULL};

Node * chain_pos = & var_chain;

Node * condarg;
BOOLEAN (* condfunc) (Node *);

/* void tprint _2p(Node *,int); */

int i;    /* for temporary storage */

Node * rewrite _2a ((term,rtree) , Node * term ,Node * rtree)
{
	DEBG((5,"rewrite : trying Term : "));
	DBFN(5,print(term));
	DEBG((5,", Tree : "));
	DBFN(5,print(rtree));
	DEBG((5,"\n"));

	if (rtree && rtree->type == RULELIST)	/* rule list (listmatch.c) */
		return match_list(term,rtree);
	return match(term,rtree);

}

/* 2026: Ctrl-C in an interactive session stops the running REWR or loop
   (as in Julia) instead of ending rewrite; set by the signal handler, cleared
   before each input line (sync.c) */
volatile sig_atomic_t rw_interrupted = 0;

void on_interrupt (int sig)
{
	rw_interrupted = 1;
	signal(SIGINT, on_interrupt);	/* Windows resets the handler */
}

/* 2026: step limit, so that a rule loop does not let REWR run forever */
long max_rewrite_steps = 100000;	/* 2026: MAXSTEPS, --max-steps */
long max_term_depth = 1000;		/* 2026: MAXDEPTH, --max-depth (levels of the term) */
static long rewrite_steps = 0;
static int  rewrite_depth = 0;
static BOOLEAN step_limit_hit = FALSE;

/* 2026: the terms most recently replaced by rule lists and their results. A
   result from which the chain of replacements leads back to the current term
   closes a cycle (A -> B -> A) and counts as no progress. */
#define NHIST 16
static Node * hist[NHIST], * hist_to[NHIST];
static int hist_rule[NHIST];
static int hist_pos = 0;

static void hist_clear (void)
{
	int i;
	for (i = 0; i < NHIST; i++)
		{
		delete(hist[i]);
		delete(hist_to[i]);
		hist[i] = hist_to[i] = NULL;
		}
	hist_pos = 0;
}

/* 2026: a REWR inside a rewrite step, as for a function defined by rules
   (ATT RULES) in a condition: the bindings of the rule being tried, the
   history and didrewrite of the outer rewriting are set aside meanwhile */
struct rewrite_nest {
	Node * chain_l, * chain_pos;
	Node * hist[NHIST], * hist_to[NHIST];
	int hist_rule[NHIST], hist_pos;
	BOOLEAN didrewrite;
};

void * rewrite_push (void)
{
	struct rewrite_nest * s = (struct rewrite_nest *) malloc(sizeof(struct rewrite_nest));
	int i;
	if (! s) fatal("run.c : no room");
	s->chain_l = var_chain.l;
	s->chain_pos = chain_pos;
	for (i = 0; i < NHIST; i++)
		{
		s->hist[i] = hist[i]; s->hist_to[i] = hist_to[i]; s->hist_rule[i] = hist_rule[i];
		hist[i] = hist_to[i] = NULL;
		}
	s->hist_pos = hist_pos;
	hist_pos = 0;
	s->didrewrite = didrewrite;
	var_chain.l = NULL;
	chain_pos = & var_chain;
	return s;
}

void rewrite_pop (void * p)
{
	struct rewrite_nest * s = (struct rewrite_nest *) p;
	int i;
	hist_clear();
	for (i = 0; i < NHIST; i++)
		{
		hist[i] = s->hist[i]; hist_to[i] = s->hist_to[i]; hist_rule[i] = s->hist_rule[i];
		}
	hist_pos = s->hist_pos;
	didrewrite = s->didrewrite;
	var_chain.l = s->chain_l;
	chain_pos = s->chain_pos;
	free(s);
}

static void hist_add (Node * t, Node * to, int rule)
{
	delete(hist[hist_pos]);
	delete(hist_to[hist_pos]);
	hist[hist_pos] = term_copy(t);
	hist_to[hist_pos] = term_copy(to);
	hist_rule[hist_pos] = rule;
	hist_pos = (hist_pos + 1) % NHIST;
}

/* the same rule rewrote this term several times recently: a longer cycle */
static BOOLEAN hist_revisit (Node * t, int rule)
{
	int i, n = 0;
	for (i = 0; i < NHIST; i++)
		if (hist[i] && hist_rule[i] == rule && term_equal(hist[i], t)) n++;
	return n >= 3;
}

static BOOLEAN has_subterm (Node * t, Node * s)
{
	if (! t) return FALSE;
	if (term_equal(t, s)) return TRUE;
	if (t->type == SYM_TYPE || t->type == Const) return FALSE;
	return has_subterm(t->l, s) || has_subterm(t->r, s);
}

/* does old -> fresh close a cycle? fresh was replaced before, and the chain of
 * replacements from there (also of subterms, as in A -> subst(B), B -> A)
 * leads to old. A term that was replaced in another branch (Int(b,x) -> b*x
 * elsewhere) may come up again. */
static BOOLEAN hist_cycle (Node * fresh, Node * old)
{
	Node * cur = fresh;
	int steps, i;
	for (steps = 0; steps < NHIST; steps++)
		{
		for (i = 0; i < NHIST; i++)
			if (hist[i] && has_subterm(cur, hist[i])) break;
		if (i == NHIST) return FALSE;
		cur = hist_to[i];
		if (has_subterm(cur, old)) return TRUE;
		}
	return FALSE;
}

/* 2026: solution steps. STEPS Alg "file" shows every rule of the rule list
   of Alg that is applied, with a label from the file (lines
   "index<TAB>label<TAB>text", index = position of the rule in the list);
   STEPS Alg "" switches it off. */
static Symbol * steps_alg = NULL;
static char ** steps_label = NULL;
static int steps_n = 0, step_no = 0;

static void steps_clear (void)
{
	int i;
	for (i = 0; i < steps_n; i++) free(steps_label[i]);
	free(steps_label);
	steps_label = NULL;
	steps_n = 0;
}

void steps_fn (Node * np)
{
	const char * file = name((Symbol *) np->r->r);
	FILE * f;
	char line[8192];
	steps_clear();
	steps_alg = NULL;
	if (! file || ! * file) return;			/* STEPS Alg "": off */
	if (! (f = fopen(file, "r")))
		{
		printfErr("STEPS : cannot read %s\n", file);
		return;
		}
	while (fgets(line, sizeof(line), f))
		{
		char * tab;
		long i = strtol(line, & tab, 10);
		if (tab == line || * tab != '\t' || i < 0 || i > 1000000) continue;
		if (i >= steps_n)
			{
			int n = (int) i + 1, k;
			steps_label = (char **) realloc(steps_label, n * sizeof(char *));
			if (! steps_label) fatal("STEPS : no room");
			for (k = steps_n; k < n; k++) steps_label[k] = NULL;
			steps_n = n;
			}
		line[strcspn(line, "\r\n")] = 0;
		free(steps_label[i]);
		steps_label[i] = strsave(tab + 1);
		}
	fclose(f);
	steps_alg = (Symbol *) np->r->l;
}

static void show_step (int rule, Node * old, Node * fresh)
{
	const char * l = (rule >= 0 && rule < steps_n) ? steps_label[rule] : NULL;
	const char * t = l ? strchr(l, '\t') : NULL;
	printfOut("Step %d: ", ++step_no);
	if (l) printfOut("%.*s\n  %s\n  ", (int) (t ? t - l : (int) strlen(l)), l, t ? t + 1 : "");
	else printfOut("rule %d\n  ", rule);
	print(old);
	printfOut("\n    = ");
	print(fresh);
	printfOut("\n");
}

void rewrite_begin (void)	/* before REWR (nested: reset only on the outermost level) */
{
	if (rewrite_depth++ == 0)
		{
		step_no = 0;
		rewrite_steps = 0;
		step_limit_hit = FALSE;
		hist_clear();
		}
}

void rewrite_end (void)
{
	if (rewrite_depth > 0) rewrite_depth--;
	if (rewrite_depth == 0) hist_clear();
}

/* 2026: a rule that makes the term deeper on every step (f(c) = c*f(1),
   applied again inside) would overflow the C stack in the recursion here
   long before the step limit: REWR stops at the depth max_term_depth. The
   recursion goes through the function node and the argument list, two
   calls per level of the term. The default 1000 still fits a sum of 1000
   summands (longer ones need more than the step limit anyway). Each step
   searches the whole term again, so a runaway rule costs time quadratic in
   this limit. */
static int position_depth = 0;

static BOOLEAN find_position_at (Node * * p_term, Node * rtree);

BOOLEAN find_position (Node * * p_term, Node * rtree)
{
	BOOLEAN r;
	if (position_depth >= 2 * max_term_depth)
		{
		if (! step_limit_hit)
			{
			step_limit_hit = TRUE;
			printfErr("REWR : the term became deeper than about %ld levels (a rule that "
			          "keeps growing it? MAXDEPTH sets the limit), the result is not complete\n",
			          max_term_depth);
			}
		return FALSE;
		}
	position_depth++;
	r = find_position_at(p_term, rtree);
	position_depth--;
	return r;
}

static BOOLEAN find_position_at (Node * * p_term, Node * rtree)
{
	Node * lt, * rt,* repl ,* maintype;
	BOOLEAN rewritten;

	if (rw_interrupted && ! step_limit_hit)	/* 2026: Ctrl-C */
		{
		step_limit_hit = TRUE;
		printfErr("REWR : interrupted (Ctrl-C), the result is not complete\n");
		}
	if (* p_term == NULL || step_limit_hit)
		return FALSE;

	DEBG((4,"\nsuche_Stelle : term : "));
	DBFN(4,print(* p_term));
	DEBG((4,"\n"));

    /* first local terms, then global ones */

	do rewritten=(find_position (&((* p_term) -> l),rtree));
	while (rewritten);
	do rewritten=(find_position (&((* p_term) -> r),rtree));
	while (rewritten);

	lm_start = 0;
	while (1)
			{
			double tp = profiling() ? profile_now() : 0;
			repl = rewrite(* p_term,rtree);
			if (tp > 0) profile_add("[loop] match", profile_now() - tp);
			if (! repl) break;
			{
			Node * old = * p_term, * fresh;
			int found = lm_last;

				lt = (* p_term) -> l;
				rt = (* p_term) -> r;
				if (RES_DO(repl)) {CALLFUNCT(RES_DO(repl));} /* executes a DO block */
				if (lt && lt->type == SYM_TYPE)
					maintype=rtypes((Symbol *) lt);
				else
					maintype=NULL;
				fresh = tcopy(RES_RHS(repl)); /* insert formula (it is also 'lifted' !) */
				retype_term(fresh);	/* 2026: variants matching the sorts of the arguments (SUBSORT) */
				tp = profiling() ? profile_now() : 0;
				fresh = tcalc(fresh);  /* evaluate formula numerically */
				if (tp > 0) profile_add("[loop] tcalc rhs", profile_now() - tp);
				tp = profiling() ? profile_now() : 0;
				if (rtree && rtree->type == RULELIST)
					term_simplify_trivial(& fresh);	/* x^0, 1*u, ... like Mathematica */
				RESTORE;					/* restore symbol table (also remove locks)*/
				/* 2026: in a rule list a rule without progress
				   (result equal to the term) is skipped; the next one is tried */
				if (rtree && rtree->type == RULELIST
				    && (term_equal(fresh, old) || term_has_nan(fresh) || hist_cycle(fresh, old)
				        || hist_revisit(old, found)))
					{
					if (tp > 0) profile_add("[loop] progress checks", profile_now() - tp);
					DEBG((2,"REWR: rule %d makes no progress or gives NaN, skipped\n", found));
					delete(fresh);
					lm_start = found + 1;
					continue;
					}
				if (tp > 0) profile_add("[loop] progress checks", profile_now() - tp);
				if (rtree && rtree->type == RULELIST)
					hist_add(old, fresh, found);
				if (steps_alg && rtree && rtree == atypes(steps_alg))
					show_step(found, old, fresh);
				DEBG((2,"REWR: "));
				DBFN(2,print(old));
				* p_term = fresh;
				delete (lt);
				delete (rt);
				if (old->type != SYM_TYPE)
					delnod(old);  /* replaced node (children are already deleted) */
				else
					delete(old);  /* frees only numbers */
				DEBG((2," -> "));
				DBFN(2,print(*p_term));
				DEBG((2,"\n"));
				didrewrite = TRUE; /* was rewritten */
				if (++rewrite_steps > max_rewrite_steps && ! step_limit_hit)
					{
					step_limit_hit = TRUE;
					printfErr("REWR : step limit (%ld rewrites, MAXSTEPS sets it) reached, "
					          "the result is not complete\n", max_rewrite_steps);
					}
				return TRUE;
			}
			}
	RESTORE;					/* restore symbol table */
	lm_start = 0;

	return FALSE;

}

Node * solve _2a ((term,alglist), Node * term ,Node * alglist)
{
	int rewritten;
	Node  * rtree;
	Node  * algpt;
	BOOLEAN wasbefore;

	if(!alglist) return term; /* empty algebra (without SPEC) */

	if (alglist -> type == Alg)
		{
		wasbefore = didrewrite;
		do 
		{
		didrewrite = FALSE;
		term = solve(term,(alglist->l));
		if (didrewrite) wasbefore = TRUE;
		}
		while (didrewrite);
		didrewrite = wasbefore;
		return term;
		}

	if (alglist -> type == Algs)  /* this is a list ! */
		{
		for (algpt=alglist; algpt != NULL; algpt = algpt -> r)
			{
			if (algpt->l->type == Alg) /* algpt -> l is Alg2 ,here : chaining */
				term = solve(term,(algpt->l));
			else
				term = solve(term,atypes((Symbol *)(algpt->l)));

			DEBG((1,"Alg: "));
			DBFN(1,print(algpt->l));
			DEBG((1,"Term: "));
			DBFN(1,print(term));
			DEBG((1,"\n"));
			}

		return term;
		}

	rtree=alglist;

	chain_pos = & var_chain;
	do rewritten=(find_position (&term,rtree));
	while (rewritten);


	{
	double tp = profiling() ? profile_now() : 0;
	term = tcalc(term);  /* evaluate formula numerically and return it */
	if (tp > 0) profile_add("[solve] tcalc term", profile_now() - tp);
	return term;
	}
}


Node * print_root = NULL;	/* 2026: the term printed by print (SHOW functions: two-dimensional only there) */

void print _1a((np),Node * np)
{
	Node * save = print_root;
	print_root = np;
	while (print_root && print_root->type == SYM_TYPE && lexval((Symbol *) print_root) == Term && print_root->l)
		print_root = print_root->l;
	tprint(np,0);
	print_root = save;
}

void tprint _2a((np,last_func_type),Node * np,int last_func_type)
{
int	this_type;					/* since La1 .. La5 are entered in the tree as Func ! */

	if (! np)	return;
	this_type = (np -> type);

	switch(this_type)
	{
	case Cond2 :
		printfOut("Cond2 ");
		if (COND_ARG(COND2_COND(np)) != (Node *) NULL)
			{printfOut("( ");
			tprint(COND_ARG(COND2_COND(np)),0);
  		printfOut(") ");
			}
		printfOut(", ");
		tprint(np ->r,0);
		break;

	case OR_TYPE :
		printfOut("( ");
		tprint(np ->l,0);
		printfOut(") OR (");
		tprint(np ->r,0);
		printfOut(") ");
		break;

	case REPL_TYPE :
		printfOut("( ");
		tprint(np ->l,0);
		printfOut(") = (");
		tprint(np ->r,0);
		printfOut(") ");
		break;

	case SYM_TYPE :
		if (lexval((Symbol *) np) == Term)
			{
			if (np->l)
				tprint(np->l,last_func_type); /* last type */
			else
				printfOut("%s ",name((Symbol *) np));	/* 2026: no term yet */
			}
		else
			if ((lexval((Symbol *) np) == Const)
				&& (hasval(np) == TRUE)
				&& ! symbolic_constant((Symbol *) np))	/* 2026: pi by its name (exact mode) */
				{
				if (rtypes((Symbol *) np) == NULL)
					fatal("run.c : tprint no rtypes given for Symbol");

				if (NULL==(void *) show(rtypes((Symbol *) np)))
         		printfOut("%g ",* ((double *) value(np)));
				else
          SHOWNUM(np,value(np));            /* print value */
				}
			else    /* otherwise names */
      	    printfOut("%s ",name((Symbol *) np) );
      break;
	case Var :
		printfOut("-Fehler : Hier tritt 'Var' auf ! -");
		break;
	case Const :
		tprint(np -> l,0);			/* symbol table entry */
		break;
	case Func :
		if (showfn(np->l) && ((show_function *) showfn(np->l))(np, last_func_type))
			return;			/* 2026: own print function (SHOW) */
		if (lexval((Symbol *) (np -> l)) == Func)
			{
			tprint(np -> l,0);		/* print name of the function */
			printfOut("(");
			tprint(np -> r,0);
			printfOut(")");
			return;
			}
		else 
			this_type = lexval((Symbol *) (np->l));
	case Ru:											/* entered in the tree as Func ! */
		if (lexval((Symbol *) (np -> l)) == Ru)
			{
			if (last_func_type > this_type)
				printfOut("(");
			tprint(np -> r,this_type);
			if (last_func_type > this_type)
				printfOut(")");
			tprint(np -> l,0);		/* print name of the function */
			return;
			}
		/* else			; */

	case Bra:
	case Bra1:
		if ((lexval((Symbol *) (np -> l)) == Bra)
		 || (lexval((Symbol *) (np -> l)) == Bra1))
			{
			tprint(np -> l,0);		/* print name of the function (opening bracket) */
			tprint(np -> r,0);              /* print content in between */
			tprint((Node *) (((Symbol *)(np -> l))->bracket),0); /* other bracket */
			return;
			}
		/* else			; */
	case Ra:							/* entered in the tree as Func ! */
	case La1:
	case La2:
	case La3:
	case La4:
	case La5:						/* equal or stronger -> no brackets */

		DEBG((9,"-Vorrang : %d -",this_type));
		if (last_func_type > this_type)
			printfOut("(");

			/* with one argument : left-unary, otherwise like left-associative */
			if (term_nargs(np) == 1) /* -> one argument -> left-unary */
				{
				tprint((Node *) TERM_HEAD(np),0);		/* print name of the function */
				tprint(term_arg(np,0),this_type+1); /* with equal precedence put the argument term in brackets, e.g. -(1-2) */
				}
			else /* left op. right */
				{
				if (lexval(TERM_HEAD(np)) == Ra) /* right-associative */
					{
					tprint(term_arg(np,0),this_type+1);  	/* left subtree must be bracketed at equal precedence : a-(b+c) */
					tprint((Node *) TERM_HEAD(np),0);			/* print name of the function */
					tprint(term_arg(np,1),this_type);
					}
				else 																	/* left-associative */
					{
					tprint(term_arg(np,0),this_type);
					tprint((Node *) TERM_HEAD(np),0);			/* print name of the function */
					tprint(term_arg(np,1),this_type + 1); /* right subtree must be bracketed at equal precedence : a-(b+c) */
					}
				}

		if (last_func_type > this_type)
			printfOut(")");
		break;
	case Terms:
	case Forms:
		tprint(np -> l,0);
		if (np -> r)
			{
			printfOut(",");
			tprint(np -> r,0);
			}
		break;
	case Form:
		tprint(np ->l,0);
		printfOut(" = ");
		tprint(np ->r,0);
		break;
	case FUNC:
		printfOut("INSTR. (");
		tprint(np ->r,0);
		printfOut(")");
		break;
	case Cond:
		printfOut("Condition (");
		tprint(np ->r,0);
		printfOut(")");
		break;
	default :
		tprint(np->l,0);
		tprint(np->r,0);
		break;
	}
	return;
}

/* free the list from rec_build_list (defs.c). Its SYM_TYPE nodes are
 * not symbols but nodes with (address, symbol) and must not be
 * treated like symbols. */
static void delete_locals_list (Node * p)
{
	if (! p) return;
	if (p->type == PARAM)
		{
		delete_locals_list(p->l);
		delete_locals_list(p->r);
		}
	delnod(p);
}

void delete _1a ((p), Node * p)
{
	void set_locals_seq (Node * np);
	void declare (Node * np);
	if (p)
		{
		if (((p -> type) == FUNC) && ((p->l) == (Node *) declare) && p->r)
			{ /* FUNC declare ( lexv ( Idlist, hasv ( rtypes, atypes ) ) )
			   * The hasv node has type TRUE/FALSE (FALSE == SYM_TYPE !).
			   * rtypes/atypes now belong to the declared symbols. */
			if (DECL_HASVNODE(p))
				delnod(DECL_HASVNODE(p));
			delete(DECL_IDLIST(p));
			delnod(DECL_LEXNODE(p));
			delnod(p);
			return;
			}
		if (((p -> type) == FUNC) && ((p->l) == (Node *) set_locals_seq))
			{ /* FUNC set_locals_seq ( PARAM ( list, statement ) ) */
			delete_locals_list(LOCALS_LIST(p));
			delete(LOCALS_INSTR(p));
			delnod(p->r);
			delnod(p);
			return;
			}
		if ( ((p -> type) == Cond)
		  || ((p -> type) == FUNC))
			{
			/* Formerly the terms of printterm and termassign were not deleted
			 * here. But % and term variables store copies (tcopy in
			 * termassign2), so the terms can be deleted. */
			delete(p->r); /* do not destroy the function ! */

			delnod(p);
			p = NULL;
			}
		else if ((p -> type) != SYM_TYPE)
				{
				delete(p -> l), delete(p -> r);
				delnod(p);
				p = NULL;
				}
		  else
				{
				if (number_symbol((Symbol *) p))
					delnum((Symbol *) p,TRUE); /* delete value too */
				}
		}
	return;
}


/* condition functions */

BOOLEAN truefunc _1a((np),Node * np)
{
	return TRUE;
}



BOOLEAN in_tree _1a((np),Node * np)
{
	return in_tree2 (np->l,np->r);
}


BOOLEAN in_tree2 _2a((npl,npr),Node * npl,Node * npr)
{
Node * npre = npr;

	if (npr == NULL) return FALSE;

	DEBG((4,"func in_tree2 ( "));
	DBFN(4,print(npl));
	DEBG((4,", "));
	DBFN(4,print(npr));
	DEBG((4," )\n"));

	if (npr->type != Terms)
		{
		if (testrewrite(npre,npl) == TRUE)
			{
			return TRUE;
			}
		/* do not restore the symbol table !! Variables are replaced later, and the restoring is done there ! */
		}

		DEBG((4," end in_tree2 \n"));

	return (in_tree2(npl,npr->l) || in_tree2(npl,npr->r));

}

BOOLEAN not_in_tree _1a ((np),Node * np)
{
	DEBG((4,"func not in_tree2 , "));
	return ! in_tree(np);
}

BOOLEAN isnt_zero (Node * np)
{ Node * rslt1;
	double val;
  BOOLEAN iszero=FALSE;
	rslt1=calculate (np);
	if (! rslt1)
		return FALSE;	/* not calculable (e.g. symbolic): condition does not hold */
	/* if (rtypes((Symbol *) rslt1) != numbertype)
		fprintf(stderr,"ERROR -- Condition with non calculatable type !\n");
	else */

		{
		if (! num_to_double((Symbol *) rslt1, & val))	/* 2026: also integer, rational */
			val=(* ((double *) value((Symbol *) rslt1)));
		iszero=(val==0.0);
		}
	delete (rslt1);
	return (! iszero);
}

BOOLEAN lower_between _1a((np),Node * np)
{
	int rtw;
	DEBG((4,"func lower_between ( "));
	DBFN(4,print(np));
	DEBG((4," )\n"));

	rtw= (tcmp(np->l,np->r) > 0) ? TRUE : FALSE;

	DEBG((4,"lower_between rt: %d\n",rtw));
	return rtw;
}

int tcmp _2a((a,b), Node * a, Node * b) /* compares trees  1 : a>b */
{													 /* 0  : a == b */
int rtn;									 /* -1 : a < b */

if (a == b)						 		 /* also NULL !! */	
	return 0;
if (a == NULL)
	return -1;
if (b == NULL)
	return  1;

DEBG((4,"tcmp ( "));
DBFN(4,print(a));
DEBG((4," und "));
DBFN(4,print(b));
DEBG((4," )\n"));

if (a->type == SYM_TYPE)
	if (b->type == SYM_TYPE)
		{
		DEBG((4,".. both Symbols\n"));
		if (hasval((Symbol *) a))
			if (hasval((Symbol *) b))
				if (rtypes((Symbol *) a) == rtypes((Symbol *) b))
					if (IS_FUNCTION(lexval((Symbol *) a)))
					 if (IS_FUNCTION(lexval((Symbol *) b)))
					  return strcmp(name((Symbol *) a),name((Symbol *) b));	
					 else return 1;
					else if (IS_FUNCTION(lexval((Symbol *) b)))
					   return -1;
				   	else
			 		return CMPNUM(a,value(a),value(b));
				else
					return strcmp(name((Symbol *) rtypes((Symbol *) a)) ,name((Symbol *) rtypes((Symbol *) b)));
	  		else
	    		return -1; /* a Num ,b not */
		else
			if (hasval((Symbol *) b))
	    		return 1; /* b Num ,a not */
			else
				{
				rtn=strcmp(name((Symbol *) a),name((Symbol *) b)); /* compare names */
				DEBG((4,".. comparing Names : %s , %s : %d\n",name((Symbol *) a),name((Symbol *) b),rtn));
				return rtn;
				}
		}
	else
		return -1;
else
	if (b->type == SYM_TYPE)
		return 1;
	else
		{
		if ((rtn=tcmp(a->l,b->l)) == 0) /* first function names, then arguments */
			return tcmp(a->r,b->r);
		else
			{
			DEBG((4,".. left tree was %d\n",rtn));
			return rtn;
			}
		}

}

void set_numbertype (Node * np)
{	Node * nt=np->r;
		numbertype = nt;
		sort_valued(nt) = TRUE;		/* 2026: numbers are of this sort */
}

Node * get_numbertype (void)
{
return numbertype; 
}


/* 2026: declared sort of the i-th argument of a function (NULL: unknown) */
static Node * param_sort (Symbol * f, int i)
{
	Node * a = atypes(f);
	int k;
	if (! a) return NULL;
	if (a->type == VARPAR)
		{
		a = a->l;
		for (k = 0; k < i && a->r != NULL; k++) a = a->r;
		return (a->r != NULL) ? a->l : a;
		}
	for (k = 0; k < i; k++)
		{
		if (a->r == NULL) return NULL;
		a = a->r;
		}
	return (a->r != NULL) ? a->l : a;
}

static Symbol * lastsym = NULL;	/* symbol with the sort of the last value of realcalc */

/* 2026: a fixed symbol with the sort s, for lastsym when a value keeps its
   own sort after the term that produced it is deleted (one per sort, so
   that nested calculations do not overwrite it) */
static Symbol * sort_rep (Node * s)
{
	static struct { Node * sort; Symbol sym; } rep[64];
	static int nrep = 0;
	int i;
	for (i = 0; i < nrep; i++)
		if (rep[i].sort == s) return & rep[i].sym;
	if (nrep == 64) fatal("run.c : too many sorts");
	rep[nrep].sort = s;
	rep[nrep].sym.node.type = SYM_TYPE;
	rep[nrep].sym.name = "(value)";
	rep[nrep].sym.rtypes = s;
	return & rep[nrep++].sym;
}

Node * realcalc_sort (void)	/* 2026: the sort of the last value of realcalc */
{
	return lastsym ? rtypes(lastsym) : NULL;
}

void * realcalc(Node * term,int * perr)
{
	Node * lterm;
	void * rslt; /* results of the subtrees */

	DEBG((5,"realcalc : "));
	DBFN(5,print(term));
	DEBG((5,"\n"));

  if (term->type == SYM_TYPE)
		{
		if ((hasval(term)) && lexval((Symbol *) term)==Const)
			{
			lastsym = (Symbol *) term;
			return CPYNUM(term,value(term));
			}
		if (lexval((Symbol *) term) == Term) /* replaced term ? */
			if (term->l) 
				return realcalc(term->l,perr);
		
		* perr = TRUE; /* e.g. PAT */
		return NULL;
		}

	if (term->type == Func && builtin(term->l))	/* symbolic C function (symfn.c) */
		{
		Node * res = call_builtin(term);
		void * v = NULL;
		if (res)
			{
			v = realcalc(res, perr);
			/* 2026: the value has the sort of the result (e.g. rational); for
			   the caller it must have the declared sort of the function, if
			   that sort has values (not number: the value keeps its sort) */
			if (! * perr && v && rtypes(lastsym) != rtypes(TERM_HEAD(term))
			    && sort_valued(rtypes(TERM_HEAD(term))))
				{
				Node * from = rtypes(lastsym), * to = rtypes(TERM_HEAD(term));
				void * w = (sort_dist(from, to) > 0) ? sort_convert(v, from, to) : NULL;
				((void (*) (void *)) del(from)) (v);
				v = w;
				if (! v) * perr = TRUE;
				else lastsym = TERM_HEAD(term);	/* for DELNUM: sort of the result */
				}
			else if (! * perr && v)		/* the value keeps its sort; res is deleted */
				lastsym = sort_rep(rtypes(lastsym));
			delete(res);
			}
		else
			* perr = TRUE;
		return * perr ? NULL : v;
		}

  if (term->type == Func && ! hasval(term->l) && ! exe_always(term->l)
      && variants((Symbol *) term->l) != NULL)
		{	/* 2026: a symbolic variant (e.g. > : number,number in a rule with
			   variables of sort number): the variant for the sorts of the
			   actual arguments may be calculable */
		Node * c = tcopy(term);
		void * v = NULL;
		retype_term(c);
		if (TERM_HEAD(c) != TERM_HEAD(term) && hasval(TERM_HEAD(c)))
			{
			v = realcalc(c, perr);
			delete(c);
			return v;
			}
		delete(c);
		}

  if (!hasval(term->l) || exe_always(term->l))  /* symbol of the function */
		{
		if (exe_always(term->l) && (term->type == Func)) /* user-defined function */
			{ Node * lterm;
			if ((lterm=exe_function(term)) != NULL)
				return realcalc(lterm,perr);
			}

		* perr = TRUE;       /* function not calculable or constant without value */
		DEBG((5,"realcalc: found not calkulable symbol : "));
		DBFN(5,print(term));
		DEBG((5,"\n"));
		return NULL;
		}

	if (term->type == Const) /***/
		{
		lastsym = (Symbol *) term->l;
		return CPYNUM(term->l,value(term->l));
		}

	/* --------------------------- up to here on any Num Const */

	/* if (term -> type == SYM_TYPE)	lastsym=term,return value(term); */

	/* from now on it is a numerical function */

	if (term->type != Func) 
		{
		printf("--- Internal Error run.c expected Funct got : ");
		print(term);
		fatal("\n");
		}


	if (* perr) 
		return (void *) NULL;

	lterm=TERM_ARGS(term);

	{
	void * vals[MAXARGS];
	Symbol * syms[MAXARGS];
	Node * conv[MAXARGS];		/* 2026: sort after extension (SUBSORT), otherwise NULL */
	int i=0,j;

	for ( ; lterm; lterm = ARGS_NEXT(lterm))
		{
		Node * want = param_sort(TERM_HEAD(term), i), * at = ARGS_ITEM(lterm);
		conv[i]=NULL;
		/* 2026: a term of a sort without values (a list [1,0,0]) where a
		   value of a wider sort is expected (an rvector): term_convert */
		if (want && at->type == Func && rtypes(TERM_HEAD(at)) != want
		    && ! sort_valued(rtypes(TERM_HEAD(at))) && sort_dist(rtypes(TERM_HEAD(at)), want) > 0)
			{
			vals[i] = term_convert(at, want);
			syms[i] = TERM_HEAD(at);
			if (vals[i]) conv[i] = want;
			else * perr = TRUE;
			i++;
			if (* perr) break;
			continue;
			}
		vals[i]=realcalc(at,perr);/* Const or Funct */
		syms[i]=lastsym;
		/* 2026: convert the value of a subsort into the declared sort; a
		   value that cannot be converted (a complex number for a real
		   argument, as im^2 built by a C helper) makes it not calculable */
		if (! * perr && vals[i] && want != NULL && want != rtypes(syms[i]))
			{
			void * w = sort_dist(rtypes(syms[i]), want) > 0
			           ? sort_convert(vals[i], rtypes(syms[i]), want) : NULL;
			if (w)
				{
				DELNUM(syms[i],vals[i]);
				vals[i] = w;
				conv[i] = want;
				}
			else if (sort_dist(rtypes(syms[i]), want) < 0)
				* perr = TRUE;
			}
		i++;
		if (i > MAXARGS-2) fatal("Fatal Error run.c : Too max Arguments for Function !");
		if (* perr)
			break;
		}
	if (!(* perr))
		{
		vals[i] = NULL; /* mark the end (for variable arguments) */
		lastsym = TERM_HEAD(term);
		rslt= ((void * (*) (void * [])) value(TERM_HEAD(term)))(vals); /* call of the user function */
		if (rslt == NULL)	/* 2026: no result (e.g. exact division by 0) */
			* perr = TRUE;
		}

	for (j=0;j<i;j++)
		{
		if (((Node *) syms[j])->type != SYM_TYPE)
			 fatal("run.c : Not a Symbol to delete !! j: %d, type: %d\n",j,((Node *) syms[j])->type);
		if (vals[j] && conv[j])	/* converted value */
			((void (*) (void *)) del(conv[j])) (vals[j]);
		else if (vals[j])  /* on error (perr) the value is NULL: nothing to free */
			DELNUM(syms[j],vals[j]);
		}
	}

	if (!(* perr))
		return rslt;
	else
		return (void *) NULL;
}

void functions_execute(Node * np) /* Caution: the tree is modified ! Completely WRONG (for loop ..) !!!!! */
{
if (! np) return;

if (np ->type != Func)
	{functions_execute(np->l);functions_execute(np->r);}
else
	if (exe_always(np->l))
		{ Node * lterm;
		if (! (lterm=exe_function(np)))
			return;
		else
			{ /* enter the result into the current tree */
			delete(np->r);
			delete(np->l);
			if (TERM_CONTENT(lterm)->type == SYM_TYPE) fatal ("run.h fatal internal TYPE ERROR ! ");

			np->type=TERM_CONTENT(lterm)->type;  /* overwrite the Func node -> transparent to the outside */
			np->r = tcopy(TERM_CONTENT(lterm)->r);
			np->l = tcopy(TERM_CONTENT(lterm)->l);

			functions_execute(np); /* search in the return value */
			return;
			}
		}
	else
		functions_execute(np->r); /* search in the arguments */
return;
}

/* 2026: in terms (tcalc, exact folding) 2^(1/2) stays exact; a value that
   is asked for (an expression statement, a condition) is then calculated
   with real numbers */
int calc_exact_only = 0;

Node * calculate (Node * term) /* gets a pointer to a calculable function */
{
	Symbol * sp;
	int error = FALSE;
	void * rslt;

	DEBG((4,"calculate : "));
	DBFN(4,print(term));
	DEBG((4,"\n"));

	/* functions_execute(term);  modifies the tree ! */

	rslt=realcalc(term,&error);

#ifdef DEBUG
	DEBG((4,"calculate : realcalc : "));
	if (error== TRUE)
		DEBG((4,"Term not calkulable \n"));
	else
		DEBG((4,"calkulated Term \n"));
#endif

	if (error==TRUE)
		{
		Node * r = NULL;
		if (! calc_exact_only)
			{
			calc_exact_only = 1;
			r = numeric_real(term);
			calc_exact_only = 0;
			}
		return r;
		}
	else
		{

			if ((term->type == Const)
				|| (term->type == Func))
				{
				sp=mknum(rslt,rtypes((Symbol *) (term->l)));

				rtypes(sp)=rtypes((Symbol *)(term->l)); /* result type of the function */
				/* 2026: calculated by a narrower variant (realcalc: e.g. + :
				   integer,integer for + : number,number): its sort */
				if (term->type == Func && lastsym && rtypes(lastsym) != rtypes(sp)
				    && sort_dist(rtypes(lastsym), rtypes(sp)) > 0)
					rtypes(sp)=rtypes(lastsym);
				}
			else
				{
				sp=mknum(rslt,rtypes((Symbol *) term));

				if ((term->type == SYM_TYPE) && (lexval((Symbol *)term) == Term))
					{
					/* 2026: a value of a subsort (e.g. integer in a
					   real term) keeps its sort */
					if (lastsym && rtypes(lastsym) != rtypes((Symbol *) term)
					    && sort_dist(rtypes(lastsym), rtypes((Symbol *) term)) > 0)
						rtypes(sp)=rtypes(lastsym);
					else
						rtypes(sp)=rtypes((Symbol *) term);
					}
				else
					{
					printfOut("calculate : Internal ERROR : unexpected term-type : ");
					print(term);
					printfOut("  Typenr. : %d\n",term->type);
					delnum(sp,TRUE); /* the value belongs to the number */
					return NULL;
					}
				}
		DEBG((4,"calculate returned : "));
		DBFN(4,print((Node *) sp));
		DEBG((4,"\n"));
		return (Node *) sp;
		}
}


Node * tcalc (Node * term)   /* traverses the tree and calculates */
{
if (! term)
	return NULL;
if (term->type == Func && builtin(term->l) == 2)	/* 2026: HOLD (matchq): arguments unevaluated */
	{
	Node * res = call_builtin(term);
	if (res)
		{
		delete(term);
		return tcalc(res);
		}
	return term;
	}
term->l = tcalc(term->l);
term->r = tcalc(term->r);

if ((term -> type) == Func && ! builtin(term->l))
	{
	exact_integers(term);	/* 2026: (1/2)*1.0 = 1/2, not 0.5 */
	retype_node(term);	/* 2026: arguments can now be exact numbers (SUBSORT) */
	}

if ((term -> type) == Func && builtin(term->l))  /* symbolic C function (symfn.c) */
	{
	Node * res = call_builtin(term);
	if (res)
		{
		delete(term);
		return tcalc(res);
		}
	return term;	/* not applicable */
	}

if  ((term -> type) == Func) /* the rest is mapped onto it */
	{
	Symbol * sp;
	Node * pp = exact_pow_pow(term);	/* 2026: (2^(1/2))^2 = 2 */
	if (pp)
		{
		delete(term);
		return tcalc(pp);
		}
	if (exact_symbolic(term))	/* 2026: ln(2), pi/6 stay terms; cos(pi/3) = 1/2 */
		{
		Node * sv = special_value(term);
		if (sv)
			{
			delete(term);
			return tcalc(sv);
			}
		return term;
		}
	int save = calc_exact_only;
	calc_exact_only = 1;		/* 2^(1/2) stays exact in a term */
	sp = (Symbol *) calculate(term);
	calc_exact_only = save;

	if (sp == NULL)		/* 2026: 2^(1/2)*0.7: a real number makes it numeric */
		sp = (Symbol *) numeric_contagion(term);
	if (sp==(Symbol *) NULL)
		return term;
	else
		{
		DEBG((4,"- tcalc did numerics : funct : "));
		DBFN(4,print(term));
		DEBG((4," => "));
		DBFN(4,print((Node *) sp));
		DEBG((4," \n"));

		delete(term);
		return mknod(Const,(Node *) sp,NULL);
		}
	}
return term;
}

/* ---- arguments of Func nodes (see nodes.h) ---- */

int term_nargs (Node * t)
{
	int n = 0;
	Node * a;
	if (! t) return 0;
	for (a = TERM_ARGS(t); a; a = ARGS_NEXT(a))
		n++;
	return n;
}

Node ** term_argp (Node * t, int i)
{
	Node ** pp;
	if (! t || ! TERM_ARGS(t) || i < 0) return NULL;
	pp = & TERM_ARGS(t);
	while ((* pp)->type == Terms)
		{
		if (i == 0) return & (* pp)->l;
		i--;
		pp = & (* pp)->r;
		}
	return (i == 0) ? pp : NULL;  /* last argument is directly in r */
}

Node * term_arg (Node * t, int i)
{
	Node ** pp = term_argp(t, i);
	return pp ? * pp : NULL;
}

Node * tcopy _1a ((term), Node * term)
{
Symbol * sp;

if (term==NULL)
	return NULL;

if (term->type == SYM_TYPE)
	{
	if (lexval((Symbol *) term) == Term) /* replace term */
		return term->l ? tcopy(term->l) : term;	/* 2026: a TERM without a term stays its name */

	if ((hasval((Symbol *) term)) && lexval((Symbol *) term)==Const
	    && ! symbolic_constant((Symbol *) term))	/* 2026: pi stays a symbol (exact mode) */
		{
		return (Node *) mknum(CPYNUM(term,value(term)),rtypes((Symbol *) term));
		}

	if (IS_FUNCTION(lexval((Symbol *) term))
			|| (lexval((Symbol *) term) == Const))  /*  'lift' */
		{Symbol * sp2=(Symbol *) term,* spnew, * spold=NULL;
		while((sp=IS_link(rtypes(sp2))) != NULL)  /* IS_VERB. is set while analysing the left part of the formula */
			{
			if (sp == spold) break; /* runs in a circle */
			spold=sp;

			DEBG((4,"lift : "));
			DBFN(4,print((Node *) sp));
			DEBG((4,", "));
			DBFN(4,print((Node *) rtypes(sp)));
			DEBG((4,"\n"));
			if ((spnew=IS_search(sp,sp2)) == NULL) break;
			sp2=spnew;
			}
		return (Node *) sp2;
		}

	return term; /* pointer to symbol */
	}

return mknod(term->type,tcopy(term->l),tcopy(term->r));
}
