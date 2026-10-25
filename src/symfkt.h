#ifndef SYMFKT_H
#define SYMFKT_H

/*
 *	symfkt.h (2026)
 *
 *	Symbolic C functions: unlike the numeric functions in userfkt.c they
 *	get the argument terms and return a new term (or NULL if they do not
 *	apply). They are attached like numeric functions:
 *	    FUNC expand : real >> real ATT expand
 *	Predicates return 1 or 0 and can be used in conditions.
 */

#include "run.h"
#include "sym.h"

typedef Node * s_function (Node * args[], int nargs, Symbol * f);

s_function * give_sfkt (const char * name);   /* NULL if unknown */
void rules_fn_register (Symbol * f, Node * algs); /* ATT RULES alglist */
s_function * rules_sfkt (void);               /* the C function behind ATT RULES */
void role_fkt (Node * np);                    /* SYMBOLIC "role" = "symbol" */
Node * call_builtin (Node * term);
int profiling (void);                         /* REWRITE_PROFILE set? */
double profile_now (void);
void profile_add (const char * name, double secs);
extern double prof_match_secs;
extern long prof_match_calls;            /* term: Func node of a builtin */
int term_equal (Node * a, Node * b);          /* structurally equal terms */
Node * term_copy (Node * t);                  /* copy of a term */
int term_has_nan (Node * t);                  /* contains NaN, infinity, 1/0 or a failed polyquotient */
Node * numeric_contagion (Node * t);          /* 2^(1/2)*0.7 as a real number, or NULL */
Node * numeric_real (Node * t);               /* value with real numbers, or NULL */
void exact_integers (Node * t);               /* 1.0 next to an exact number as 1 */
Node * exact_pow_pow (Node * t);              /* (2^(1/2))^2 = 2 */
void term_simplify_trivial (Node ** p);       /* u^0, u^1, 1*u, 0*u, 0+u in place */

#endif
