#ifndef NUMSORT_H
#define NUMSORT_H

/*
 *	numsort.h (2026)
 *
 *	Subsorts of numbers and integer literals.
 *
 *	    SUBSORT integer,rational ATT int2rat
 *	    SUBSORT rational,real ATT rat2real
 *	    INTNUM integer ATT read_int
 *
 *	SUBSORT declares that every value of the first sort is also a value of
 *	the second one; the C function converts a value (widening). Sorts are
 *	static: a term keeps its sort, but a function declared for a wider sort
 *	accepts its arguments (getsymbol), and the values are converted when the
 *	function is calculated (realcalc). Each sort has at most one wider sort,
 *	so the subsorts form chains like integer < rational < real.
 *
 *	INTNUM makes numbers written without '.' and exponent (12, 0, 7) values
 *	of the given sort, created by the C function from the text. Without
 *	INTNUM all numbers are of the sort set with NUM (real).
 */

#include "run.h"
#include "sym.h"

void subsort_def (Node * np);			/* SUBSORT statement */
void intnum_def (Node * np);			/* INTNUM statement */

/* steps from sort 'from' up to sort 'to' (0: same sort), -1 if 'to' is not
 * reachable */
int sort_dist (Node * from, Node * to);

/* value of sort 'from' converted to sort 'to' (new value; the caller frees
 * it with the delete function of 'to'); NULL if not possible */
void * sort_convert (void * value, Node * from, Node * to);
void * term_convert (Node * term, Node * to);	/* a list [1,2,3] as an rvector */

/* number of the sort of an integer literal, or NULL (no INTNUM) */
Symbol * int_literal (const char * text);

/* value of a number symbol as a double (via the subsort chain up to the
 * NUM sort); FALSE if it is no number of such a sort */
BOOLEAN num_to_double (Symbol * num, double * v);

/* exact numbers made in C (integer if q == 1, else rational); NULL if
 * INTNUM and the rational sort are not declared */
BOOLEAN exact_numbers (void);
Symbol * make_exact (long long p, long long q);
BOOLEAN num_exact (Symbol * s);			/* integer or rational value */
Symbol * exact_root (Symbol * s, long k);	/* exact k-th root, or NULL */

/* for apart.c: an exact number as a new mpq_ptr (NULL if not exact), and a
 * number from an mpq_ptr (taken; integer sort if the denominator is 1) */
void * exact_to_rat (Symbol * s);
Symbol * make_exact_rat (void * q);

/* may a meta variable of sort vsort match term? Only checked for sorts that
 * are subsorts of another (nonneg, integer, ...); a variable of sort real
 * matches any term, as before. */
BOOLEAN var_sort_ok (Node * vsort, Node * term);

/* the sort has no wider sort (SUBSORT) */
BOOLEAN sort_top (Node * s);

/* the sort has exact values (natural, integer, rational) */
BOOLEAN sort_exact (Node * s);

/* sort of an argument node (as eq_rtypes sees it) */
Node * arg_sort (Node * a);

#endif
