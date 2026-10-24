#ifndef APART_H
#define APART_H

/*
 *	apart.h (2026)
 *
 *	Partial fractions of rational functions in one variable with exact
 *	rational coefficients (Mathematica's Apart), see apart.c. The
 *	coefficients are pointers to mpq_t, passed as void * so that this
 *	header does not need gmp.h.
 */

typedef struct {
	int deg;		/* -1: the zero polynomial */
	void ** c;		/* c[0..deg], mpq_ptr */
} QPoly;

typedef struct RatFun RatFun;	/* numerator / product of factors^e */

/* constructors; the operations free their arguments */
RatFun * rf_const (void * q);		/* takes the mpq_ptr */
RatFun * rf_var (void);			/* x */
RatFun * rf_add (RatFun * a, RatFun * b);
RatFun * rf_mul (RatFun * a, RatFun * b);
RatFun * rf_pow (RatFun * a, int k);	/* NULL: 0^-k or too large */
void rf_free (RatFun * a);

/* one summand coef * num(x) / base(x)^k of the result; num and base have
 * integer coefficients without a common divisor and a positive leading one,
 * as Mathematica's Apart writes the numeric factor in front */
typedef struct {
	void * coef;		/* mpq_ptr */
	QPoly num, base;
	int k;
} ApartTerm;

/* the partial fractions of a: quot + sum of terms[i]; returns the number of
 * terms, -1 if a has no denominator or is too large. Frees a. */
int rf_apart (RatFun * a, QPoly * quot, ApartTerm ** terms);
void qpoly_clear (QPoly * p);
void apart_free (ApartTerm * terms, int n);
int mpq_is_one (void * q);

#endif
