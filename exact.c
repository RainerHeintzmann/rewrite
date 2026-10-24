/*
 *	exact.c (2026)
 *
 *	Exact numbers for rewrite: the sorts integer (arbitrary size) and
 *	rational (fractions), with GMP. Declared in inc/exact:
 *
 *	    SORT integer, rational
 *	    ATT integer  show_int,cmp_int,cpy_int,del_int
 *	    ATT rational show_rat,cmp_rat,cpy_rat,del_rat
 *	    SUBSORT integer,rational ATT int2rat
 *	    SUBSORT rational,real ATT rat2real
 *	    INTNUM integer ATT read_int
 *
 *	The values are pointers to mpz_t (integer) and mpq_t (rational). As all
 *	C functions of rewrite, the arithmetic functions get an array of
 *	argument values and return a new value. A result that does not exist
 *	(division by zero, too large power) is NULL: the term stays unevaluated.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gmp.h>

#include "inout.h"
#include "fatal.h"
#include "real.h"
/* exact.h declares these with void * (without gmp.h); not included here */

#define MAXEXP 100000		/* largest exponent of an exact power */

/* ---------------- integer ---------------- */

static mpz_ptr new_int (void)
{
	mpz_ptr z = (mpz_ptr) malloc(sizeof(__mpz_struct));
	if (! z) fatal("exact : no room for an integer");
	mpz_init(z);
	return z;
}

void show_int (mpz_ptr z)
{
	char * s = mpz_get_str(NULL, 10, z);
	printfOut("%s ", s);
	free(s);
}

int cmp_int (mpz_ptr a, mpz_ptr b)
{
	int c = mpz_cmp(a, b);
	return (c > 0) - (c < 0);
}

mpz_ptr cpy_int (mpz_ptr a)
{
	mpz_ptr z = new_int();
	mpz_set(z, a);
	return z;
}

void del_int (mpz_ptr a)
{
	mpz_clear(a);
	free(a);
}

void * read_int (void * arg[])		/* arg[0]: text of the literal */
{
	mpz_ptr z = new_int();
	if (mpz_set_str(z, (const char *) arg[0], 10) != 0)
		{
		del_int(z);
		return NULL;
		}
	return z;
}

#define I(k) ((mpz_ptr) arg[k])

void * int_plus (void * arg[])  { mpz_ptr z = new_int(); mpz_add(z, I(0), I(1)); return z; }
void * int_minus (void * arg[]) { mpz_ptr z = new_int(); mpz_sub(z, I(0), I(1)); return z; }
void * int_mal (void * arg[])   { mpz_ptr z = new_int(); mpz_mul(z, I(0), I(1)); return z; }
void * int_neg (void * arg[])   { mpz_ptr z = new_int(); mpz_neg(z, I(0)); return z; }
void * int_abs (void * arg[])   { mpz_ptr z = new_int(); mpz_abs(z, I(0)); return z; }

void * int_fak (void * arg[])		/* n! */
{
	mpz_ptr z;
	if (mpz_sgn(I(0)) < 0 || ! mpz_fits_ulong_p(I(0)) || mpz_get_ui(I(0)) > MAXEXP)
		return NULL;
	z = new_int();
	mpz_fac_ui(z, mpz_get_ui(I(0)));
	return z;
}

void * int_mod (void * arg[])		/* remainder with the sign of the divisor */
{
	mpz_ptr z;
	if (mpz_sgn(I(1)) == 0) return NULL;
	z = new_int();
	mpz_fdiv_r(z, I(0), I(1));
	return z;
}

void * int_quot (void * arg[])		/* integer quotient, rounded down */
{
	mpz_ptr z;
	if (mpz_sgn(I(1)) == 0) return NULL;
	z = new_int();
	mpz_fdiv_q(z, I(0), I(1));
	return z;
}

void * int_gcd (void * arg[])   { mpz_ptr z = new_int(); mpz_gcd(z, I(0), I(1)); return z; }

static double * truth (int b) { return mkreal(b ? 1.0 : 0.0); }

void * int_gt (void * arg[]) { return truth(mpz_cmp(I(0), I(1)) > 0); }
void * int_ge (void * arg[]) { return truth(mpz_cmp(I(0), I(1)) >= 0); }
void * int_lt (void * arg[]) { return truth(mpz_cmp(I(0), I(1)) < 0); }
void * int_le (void * arg[]) { return truth(mpz_cmp(I(0), I(1)) <= 0); }
void * int_eq (void * arg[]) { return truth(mpz_cmp(I(0), I(1)) == 0); }
void * int_ne (void * arg[]) { return truth(mpz_cmp(I(0), I(1)) != 0); }

/* ---------------- rational ---------------- */

static mpq_ptr new_rat (void)
{
	mpq_ptr q = (mpq_ptr) malloc(sizeof(__mpq_struct));
	if (! q) fatal("exact : no room for a rational number");
	mpq_init(q);
	return q;
}

void show_rat (mpq_ptr q)		/* 1/3 as (1/3), 4/1 as 4 */
{
	char * s = mpq_get_str(NULL, 10, q);
	if (mpz_cmp_ui(mpq_denref(q), 1) == 0)
		printfOut("%s ", s);
	else
		printfOut("(%s) ", s);
	free(s);
}

int cmp_rat (mpq_ptr a, mpq_ptr b)
{
	int c = mpq_cmp(a, b);
	return (c > 0) - (c < 0);
}

mpq_ptr cpy_rat (mpq_ptr a)
{
	mpq_ptr q = new_rat();
	mpq_set(q, a);
	return q;
}

void del_rat (mpq_ptr a)
{
	mpq_clear(a);
	free(a);
}

#define Q(k) ((mpq_ptr) arg[k])

void * int2rat (void * arg[])
{
	mpq_ptr q = new_rat();
	mpq_set_z(q, I(0));
	return q;
}

void * rat2real (void * arg[])
{
	return mkreal(mpq_get_d(Q(0)));
}

void * int_div (void * arg[])		/* integer / integer -> rational */
{
	mpq_ptr q;
	if (mpz_sgn(I(1)) == 0) return NULL;
	q = new_rat();
	mpz_set(mpq_numref(q), I(0));
	mpz_set(mpq_denref(q), I(1));
	mpq_canonicalize(q);
	return q;
}

void * rat_plus (void * arg[])  { mpq_ptr q = new_rat(); mpq_add(q, Q(0), Q(1)); return q; }
void * rat_minus (void * arg[]) { mpq_ptr q = new_rat(); mpq_sub(q, Q(0), Q(1)); return q; }
void * rat_mal (void * arg[])   { mpq_ptr q = new_rat(); mpq_mul(q, Q(0), Q(1)); return q; }
void * rat_neg (void * arg[])   { mpq_ptr q = new_rat(); mpq_neg(q, Q(0)); return q; }
void * rat_abs (void * arg[])   { mpq_ptr q = new_rat(); mpq_abs(q, Q(0)); return q; }

void * rat_div (void * arg[])
{
	mpq_ptr q;
	if (mpq_sgn(Q(1)) == 0) return NULL;
	q = new_rat();
	mpq_div(q, Q(0), Q(1));
	return q;
}

void * rat_mi (void * arg[])		/* 1/q */
{
	mpq_ptr q;
	if (mpq_sgn(Q(0)) == 0) return NULL;
	q = new_rat();
	mpq_inv(q, Q(0));
	return q;
}

void * rat_pow (void * arg[])		/* rational ^ integer -> rational */
{
	mpq_ptr q;
	long e;
	if (! mpz_fits_slong_p(I(1))) return NULL;
	e = mpz_get_si(I(1));
	if (e > MAXEXP || e < -MAXEXP) return NULL;
	if (e < 0 && mpq_sgn(Q(0)) == 0) return NULL;
	q = new_rat();
	mpz_pow_ui(mpq_numref(q), mpq_numref(Q(0)), (unsigned long) labs(e));
	mpz_pow_ui(mpq_denref(q), mpq_denref(Q(0)), (unsigned long) labs(e));
	mpq_canonicalize(q);
	if (e < 0) mpq_inv(q, q);
	return q;
}

void * int_pow (void * arg[])		/* integer ^ integer -> rational (2^-1 = 1/2) */
{
	void * a[3], * r;
	mpq_ptr b = new_rat();
	mpq_set_z(b, I(0));
	a[0] = b; a[1] = arg[1]; a[2] = NULL;
	r = rat_pow(a);
	del_rat(b);
	return r;
}

/* conversions for the subsorts natural < integer, natural < nonneg,
 * positive < nonneg < real */
void * int2int (void * arg[]) { return cpy_int(I(0)); }		/* natural -> integer */
void * int2real (void * arg[]) { return mkreal(mpz_get_d(I(0))); }	/* natural -> nonneg */
void * real2real (void * arg[]) { return mkreal(* (double *) arg[0]); }	/* nonneg -> real */

void * nat_pow (void * arg[])		/* natural ^ natural -> natural */
{
	mpz_ptr z;
	if (! mpz_fits_ulong_p(I(1)) || mpz_get_ui(I(1)) > MAXEXP) return NULL;
	z = new_int();
	mpz_pow_ui(z, I(0), mpz_get_ui(I(1)));
	return z;
}

/* for C code (numsort.c): exact numbers from machine integers */
void * int_from_ll (long long v)
{
	mpz_ptr z = new_int();
	mpz_set_si(z, (long) v);
	if ((long long) (long) v != v)		/* long is 32 bit on Windows */
		{
		char buf[32];
		sprintf(buf, "%lld", v);
		mpz_set_str(z, buf, 10);
		}
	return z;
}

void * rat_from_ll (long long p, long long q)
{
	mpq_ptr r = new_rat();
	mpz_ptr a = int_from_ll(p), b = int_from_ll(q);
	mpz_set(mpq_numref(r), a);
	mpz_set(mpq_denref(r), b);
	mpq_canonicalize(r);
	del_int(a); del_int(b);
	return r;
}

/* exact k-th root of a non-negative rational, or NULL */
void * rat_root_exact (void * qv, long k)
{
	mpq_ptr q = (mpq_ptr) qv, r;
	mpz_t a, b;
	int ea, eb;
	if (k < 1 || mpq_sgn(q) < 0) return NULL;
	mpz_init(a); mpz_init(b);
	ea = mpz_root(a, mpq_numref(q), (unsigned long) k);
	eb = mpz_root(b, mpq_denref(q), (unsigned long) k);
	if (! ea || ! eb) { mpz_clear(a); mpz_clear(b); return NULL; }
	r = new_rat();
	mpz_set(mpq_numref(r), a);
	mpz_set(mpq_denref(r), b);
	mpq_canonicalize(r);
	mpz_clear(a); mpz_clear(b);
	return r;
}

void * rat_num (void * arg[])		/* numerator */
{
	mpz_ptr z = new_int();
	mpz_set(z, mpq_numref(Q(0)));
	return z;
}

void * rat_den (void * arg[])		/* denominator */
{
	mpz_ptr z = new_int();
	mpz_set(z, mpq_denref(Q(0)));
	return z;
}

void * rat_is_int (void * arg[])	{ return truth(mpz_cmp_ui(mpq_denref(Q(0)), 1) == 0); }

void * rat_gt (void * arg[]) { return truth(mpq_cmp(Q(0), Q(1)) > 0); }
void * rat_ge (void * arg[]) { return truth(mpq_cmp(Q(0), Q(1)) >= 0); }
void * rat_lt (void * arg[]) { return truth(mpq_cmp(Q(0), Q(1)) < 0); }
void * rat_le (void * arg[]) { return truth(mpq_cmp(Q(0), Q(1)) <= 0); }
void * rat_eq (void * arg[]) { return truth(mpq_equal(Q(0), Q(1))); }
void * rat_ne (void * arg[]) { return truth(! mpq_equal(Q(0), Q(1))); }
