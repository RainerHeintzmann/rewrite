#ifndef EXACT_H
#define EXACT_H

/*
 *	exact.h (2026)
 *
 *	Exact numbers (sorts integer and rational) with GMP, see exact.c.
 *	The value types are passed as void * so that this header does not need
 *	gmp.h.
 */

void show_int (void * z);
int cmp_int (void * a, void * b);
void * cpy_int (void * a);
void del_int (void * a);
void * read_int (void * arg[]);
void * int_plus (void * arg[]);
void * int_minus (void * arg[]);
void * int_mal (void * arg[]);
void * int_neg (void * arg[]);
void * int_abs (void * arg[]);
void * int_fak (void * arg[]);
void * int_mod (void * arg[]);
void * int_quot (void * arg[]);
void * int_gcd (void * arg[]);
void * int_div (void * arg[]);
void * int_gt (void * arg[]);
void * int_ge (void * arg[]);
void * int_lt (void * arg[]);
void * int_le (void * arg[]);
void * int_eq (void * arg[]);
void * int_ne (void * arg[]);

void show_rat (void * q);
int cmp_rat (void * a, void * b);
void * cpy_rat (void * a);
void del_rat (void * a);
void * int2rat (void * arg[]);
void * rat2real (void * arg[]);
void * rat_plus (void * arg[]);
void * rat_minus (void * arg[]);
void * rat_mal (void * arg[]);
void * rat_div (void * arg[]);
void * rat_neg (void * arg[]);
void * rat_abs (void * arg[]);
void * rat_mi (void * arg[]);
void * rat_pow (void * arg[]);
void * rat_qpow (void * arg[]);      /* NULL if not exact */
void * nat_qpow (void * arg[]);      /* natural^rational, NULL if not exact */
void * int_pow (void * arg[]);
void * rat_num (void * arg[]);
void * int2int (void * arg[]);
void * int2real (void * arg[]);
void * real2real (void * arg[]);
void * nat_pow (void * arg[]);
void * int_from_ll (long long v);
void * rat_from_ll (long long p, long long q);
void * rat_root_exact (void * q, long k);    /* NULL if not exact */
void * rat_pow_norm (void * base, void * expo, void ** rest, void ** fexp);	/* 8^(1/2) = 2*2^(1/2) */
void * rat_den (void * arg[]);
int rat_is_integer (void * q);
int rat_sgn (void * q);
void * rat_numer (void * q);			/* new mpz */
void * rat_is_int (void * arg[]);
void * rat_gt (void * arg[]);
void * rat_ge (void * arg[]);
void * rat_lt (void * arg[]);
void * rat_le (void * arg[]);
void * rat_eq (void * arg[]);
void * rat_ne (void * arg[]);

#endif
