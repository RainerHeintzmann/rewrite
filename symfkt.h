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
Node * call_builtin (Node * term);            /* term: Func node of a builtin */

#endif
