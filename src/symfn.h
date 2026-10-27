#ifndef SYMFN_H
#define SYMFN_H

/*
 *	symfn.h (2026)
 *
 *	Symbolic C functions: unlike the numeric functions in userfn.c they
 *	get the argument terms and return a new term (or NULL if they do not
 *	apply). They are attached like numeric functions:
 *	    FUNC expand : real >> real ATT expand
 *	Predicates return 1 or 0 and can be used in conditions.
 */

#include "run.h"
#include "sym.h"

typedef Node * s_function (Node * args[], int nargs, Symbol * f);

s_function * give_sfn (const char * name);   /* NULL if unknown */
void rules_fn_register (Symbol * f, Node * algs); /* ATT RULES alglist */
s_function * rules_sfn (void);               /* the C function behind ATT RULES */
void role_fn (Node * np);                    /* SYMBOLIC "role" = "symbol" */
Node * call_builtin (Node * term);
int symbolic_constant (Symbol * s);	/* 2026: pi, im in exact mode: no value in terms */
int exact_symbolic (Node * t);	/* 2026: exact mode: f(exact args), pi: no numeric value in a term */
Node * special_value (Node * t);	/* 2026: its exact value (1/2, 3^(1/2)/2, pi/6) or NULL */
typedef int show_function (Node * term, int prec);	/* 2026: SHOW: 1 if it printed the term */
show_function * give_pfn (const char * name);	/* print function by name, NULL if unknown (reported) */
void show_def (Node * np);			/* SHOW f ATT name */
int profiling (void);                         /* REWRITE_PROFILE set? */
double profile_now (void);
void profile_add (const char * name, double secs);
extern double prof_match_secs;
extern long prof_match_calls;            /* term: Func node of a builtin */
int term_equal (Node * a, Node * b);          /* structurally equal terms */
Node * term_copy (Node * t);                  /* copy of a term */
int term_has_builtin (Node * t);              /* a symbolic C function somewhere in t */
int term_has_nan (Node * t);                  /* contains NaN, infinity, 1/0 or a failed polyquotient */
Node * numeric_contagion (Node * t);          /* 2^(1/2)*0.7 as a real number, or NULL */
Node * numeric_real (Node * t);               /* value with real numbers, or NULL */
void exact_integers (Node * t);               /* 1.0 next to an exact number as 1 */
Node * exact_pow_pow (Node * t);              /* (2^(1/2))^2 = 2 */
void term_simplify_trivial (Node ** p);       /* u^0, u^1, 1*u, 0*u, 0+u in place */

#endif
