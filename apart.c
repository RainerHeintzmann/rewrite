/*
 *	apart.c (2026)
 *
 *	Partial fractions of a rational function in x with exact rational
 *	coefficients, as Mathematica's Apart, which Rubi's ExpandIntegrand uses:
 *
 *	    (x^2+2x+3)/((x-1)(x+1)^2) = 3/2/(x-1) - 1/2/(x+1) - 1/(x+1)^2
 *
 *	The function is built from the term (rf_const, rf_var, rf_add, rf_mul,
 *	rf_pow) with the denominator kept as a product of factors, so that the
 *	factors of the input, like (x^2+1)(x^2+4), are known. rf_apart divides
 *	out the polynomial part, splits the factors into pairwise coprime ones
 *	(square-free parts, rational roots, common divisors), and splits the
 *	remainder with the extended Euclidean algorithm. Irreducible factors of
 *	degree 2 and more that the input does not show are not found.
 */

#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#include "fatal.h"
#include "apart.h"

#define MAXDEG 60		/* larger functions are left alone */
#define MAXROOT 100000		/* rational roots p/q: |p|, |q| up to this */

#define C(p, k) ((mpq_ptr) (p)->c[k])

/* ---------------- polynomials with mpq coefficients ---------------- */

static QPoly p_new (int deg)		/* zero coefficients c[0..deg] */
{
	QPoly p;
	int k;
	p.deg = deg;
	p.c = (void **) malloc((deg + 1 > 0 ? deg + 1 : 1) * sizeof(void *));
	if (! p.c) fatal("apart : no room");
	for (k = 0; k <= deg; k++)
		{
		mpq_ptr q = (mpq_ptr) malloc(sizeof(__mpq_struct));
		if (! q) fatal("apart : no room");
		mpq_init(q);
		p.c[k] = q;
		}
	return p;
}

void qpoly_clear (QPoly * p)
{
	int k;
	for (k = 0; k <= p->deg; k++)
		{
		mpq_clear(C(p, k));
		free(p->c[k]);
		}
	free(p->c);
	p->c = NULL;
	p->deg = -1;
}

static void p_trim (QPoly * p)		/* no leading zero coefficients */
{
	while (p->deg >= 0 && mpq_sgn(C(p, p->deg)) == 0)
		{
		mpq_clear(C(p, p->deg));
		free(p->c[p->deg]);
		p->deg--;
		}
}

static QPoly p_copy (const QPoly * a)
{
	QPoly p = p_new(a->deg);
	int k;
	for (k = 0; k <= a->deg; k++) mpq_set(C(&p, k), C(a, k));
	return p;
}

static QPoly p_const (mpq_srcptr q)
{
	QPoly p = p_new(0);
	mpq_set(C(&p, 0), q);
	p_trim(&p);
	return p;
}

static QPoly p_one (void)
{
	QPoly p = p_new(0);
	mpq_set_ui(C(&p, 0), 1, 1);
	return p;
}

static QPoly p_add (const QPoly * a, const QPoly * b, int sign)	/* a + sign*b */
{
	int d = a->deg > b->deg ? a->deg : b->deg, k;
	QPoly p = p_new(d);
	for (k = 0; k <= d; k++)
		{
		if (k <= a->deg) mpq_set(C(&p, k), C(a, k));
		if (k <= b->deg)
			{
			if (sign > 0) mpq_add(C(&p, k), C(&p, k), C(b, k));
			else mpq_sub(C(&p, k), C(&p, k), C(b, k));
			}
		}
	p_trim(&p);
	return p;
}

static QPoly p_mul (const QPoly * a, const QPoly * b)
{
	QPoly p;
	mpq_t t;
	int i, j;
	if (a->deg < 0 || b->deg < 0) return p_new(-1);
	p = p_new(a->deg + b->deg);
	mpq_init(t);
	for (i = 0; i <= a->deg; i++)
		for (j = 0; j <= b->deg; j++)
			{
			mpq_mul(t, C(a, i), C(b, j));
			mpq_add(C(&p, i + j), C(&p, i + j), t);
			}
	mpq_clear(t);
	p_trim(&p);
	return p;
}

static void p_scale (QPoly * p, mpq_srcptr s)	/* in place */
{
	int k;
	for (k = 0; k <= p->deg; k++) mpq_mul(C(p, k), C(p, k), s);
	p_trim(p);
}

/* a = q*b + r with deg r < deg b; b is not zero */
static void p_divmod (const QPoly * a, const QPoly * b, QPoly * q, QPoly * r)
{
	QPoly rr = p_copy(a);
	mpq_t f, t;
	int k, j;
	mpq_init(f); mpq_init(t);
	if (q) * q = p_new(a->deg >= b->deg ? a->deg - b->deg : -1);
	for (k = a->deg - b->deg; k >= 0; k--)
		{
		mpq_div(f, C(&rr, k + b->deg), C(b, b->deg));
		if (q) mpq_set(C(q, k), f);
		for (j = 0; j <= b->deg; j++)
			{
			mpq_mul(t, f, C(b, j));
			mpq_sub(C(&rr, k + j), C(&rr, k + j), t);
			}
		}
	mpq_clear(f); mpq_clear(t);
	p_trim(&rr);
	if (q) p_trim(q);
	if (r) * r = rr; else qpoly_clear(&rr);
}

static void p_monic (QPoly * p)
{
	mpq_t s;
	if (p->deg < 0) return;
	mpq_init(s);
	mpq_inv(s, C(p, p->deg));
	p_scale(p, s);
	mpq_clear(s);
}

static int p_equal (const QPoly * a, const QPoly * b)
{
	int k;
	if (a->deg != b->deg) return 0;
	for (k = 0; k <= a->deg; k++)
		if (! mpq_equal(C(a, k), C(b, k))) return 0;
	return 1;
}

/* monic gcd; with s, t: s*a + t*b = gcd */
static QPoly p_gcdext (const QPoly * a, const QPoly * b, QPoly * s, QPoly * t)
{
	QPoly r0 = p_copy(a), r1 = p_copy(b);
	QPoly s0 = p_one(), s1 = p_new(-1), t0 = p_new(-1), t1 = p_one();
	mpq_t lc;
	while (r1.deg >= 0)
		{
		QPoly q, r, h, n;
		p_divmod(&r0, &r1, &q, &r);
		qpoly_clear(&r0); r0 = r1; r1 = r;
		h = p_mul(&q, &s1); n = p_add(&s0, &h, -1);
		qpoly_clear(&h); qpoly_clear(&s0); s0 = s1; s1 = n;
		h = p_mul(&q, &t1); n = p_add(&t0, &h, -1);
		qpoly_clear(&h); qpoly_clear(&t0); t0 = t1; t1 = n;
		qpoly_clear(&q);
		}
	qpoly_clear(&r1); qpoly_clear(&s1); qpoly_clear(&t1);
	mpq_init(lc);
	if (r0.deg >= 0) mpq_inv(lc, C(&r0, r0.deg));
	p_scale(&r0, lc); p_scale(&s0, lc); p_scale(&t0, lc);
	mpq_clear(lc);
	if (s) * s = s0; else qpoly_clear(&s0);
	if (t) * t = t0; else qpoly_clear(&t0);
	return r0;
}

static QPoly p_gcd (const QPoly * a, const QPoly * b)
{
	return p_gcdext(a, b, NULL, NULL);
}

static QPoly p_deriv (const QPoly * a)
{
	QPoly p = p_new(a->deg - 1);
	int k;
	for (k = 1; k <= a->deg; k++)
		{
		mpq_set_ui(C(&p, k - 1), k, 1);
		mpq_mul(C(&p, k - 1), C(&p, k - 1), C(a, k));
		}
	p_trim(&p);
	return p;
}

static QPoly p_pow (const QPoly * a, int e)
{
	QPoly p = p_one();
	while (e-- > 0)
		{
		QPoly n = p_mul(&p, a);
		qpoly_clear(&p);
		p = n;
		}
	return p;
}

/* a = u * b with b integer, primitive, positive leading coefficient */
static void p_primitive (const QPoly * a, QPoly * b, mpq_ptr u)
{
	mpz_t l, g;
	mpq_t s;
	int k;
	mpz_init_set_ui(l, 1); mpz_init_set_ui(g, 0); mpq_init(s);
	for (k = 0; k <= a->deg; k++)
		{
		mpz_lcm(l, l, mpq_denref(C(a, k)));
		mpz_gcd(g, g, mpq_numref(C(a, k)));
		}
	if (mpz_sgn(g) == 0) mpz_set_ui(g, 1);
	mpq_set_num(s, l); mpq_set_den(s, g); mpq_canonicalize(s);
	if (a->deg >= 0 && mpq_sgn(C(a, a->deg)) < 0) mpq_neg(s, s);
	* b = p_copy(a);
	p_scale(b, s);
	mpq_inv(u, s);
	mpz_clear(l); mpz_clear(g); mpq_clear(s);
}

/* ---------------- rational functions ---------------- */

typedef struct { QPoly f; int e; } Fac;	/* monic factor and exponent */

struct RatFun {
	QPoly num;
	int n;
	Fac * fac;
};

static RatFun * rf_new (void)
{
	RatFun * r = (RatFun *) calloc(1, sizeof(RatFun));
	if (! r) fatal("apart : no room");
	r->num.deg = -1;
	return r;
}

void rf_free (RatFun * a)
{
	int i;
	if (! a) return;
	qpoly_clear(& a->num);
	for (i = 0; i < a->n; i++) qpoly_clear(& a->fac[i].f);
	free(a->fac);
	free(a);
}

static void fac_add (RatFun * r, QPoly f, int e)	/* takes f (monic) */
{
	int i;
	if (f.deg <= 0) { qpoly_clear(&f); return; }
	for (i = 0; i < r->n; i++)
		if (p_equal(& r->fac[i].f, &f))
			{
			r->fac[i].e += e;
			qpoly_clear(&f);
			return;
			}
	r->fac = (Fac *) realloc(r->fac, (r->n + 1) * sizeof(Fac));
	if (! r->fac) fatal("apart : no room");
	r->fac[r->n].f = f;
	r->fac[r->n].e = e;
	r->n++;
}

static int rf_degree (const RatFun * a)
{
	int d = a->num.deg, i;
	for (i = 0; i < a->n; i++) d += a->fac[i].e * a->fac[i].f.deg;
	return d;
}

RatFun * rf_const (void * q)
{
	RatFun * r = rf_new();
	r->num = p_const((mpq_srcptr) q);
	mpq_clear((mpq_ptr) q);
	free(q);
	return r;
}

RatFun * rf_var (void)
{
	RatFun * r = rf_new();
	r->num = p_new(1);
	mpq_set_ui(C(& r->num, 1), 1, 1);
	return r;
}

/* product of the factors of a with exponent e_a(f) - e_b(f) > 0 */
static QPoly missing (const RatFun * a, const RatFun * b)
{
	QPoly p = p_one();
	int i, j;
	for (i = 0; i < a->n; i++)
		{
		int e = a->fac[i].e;
		for (j = 0; j < b->n; j++)
			if (p_equal(& a->fac[i].f, & b->fac[j].f)) e -= b->fac[j].e;
		if (e > 0)
			{
			QPoly h = p_pow(& a->fac[i].f, e), n = p_mul(&p, &h);
			qpoly_clear(&h); qpoly_clear(&p);
			p = n;
			}
		}
	return p;
}

RatFun * rf_add (RatFun * a, RatFun * b)
{
	RatFun * r;
	QPoly ma, mb, x, y;
	int i;
	if (! a || ! b) { rf_free(a); rf_free(b); return NULL; }
	ma = missing(b, a);		/* a needs the factors that only b has */
	mb = missing(a, b);
	x = p_mul(& a->num, &ma);
	y = p_mul(& b->num, &mb);
	r = rf_new();
	r->num = p_add(&x, &y, 1);
	qpoly_clear(&x); qpoly_clear(&y); qpoly_clear(&ma); qpoly_clear(&mb);
	for (i = 0; i < a->n; i++)		/* common denominator: maximal exponents */
		fac_add(r, p_copy(& a->fac[i].f), a->fac[i].e);
	for (i = 0; i < b->n; i++)
		{
		int j, found = 0;
		for (j = 0; j < r->n; j++)
			if (p_equal(& r->fac[j].f, & b->fac[i].f))
				{
				found = 1;
				if (b->fac[i].e > r->fac[j].e) r->fac[j].e = b->fac[i].e;
				}
		if (! found) fac_add(r, p_copy(& b->fac[i].f), b->fac[i].e);
		}
	rf_free(a); rf_free(b);
	if (rf_degree(r) > MAXDEG) { rf_free(r); return NULL; }
	return r;
}

RatFun * rf_mul (RatFun * a, RatFun * b)
{
	RatFun * r;
	int i;
	if (! a || ! b) { rf_free(a); rf_free(b); return NULL; }
	r = rf_new();
	r->num = p_mul(& a->num, & b->num);
	for (i = 0; i < a->n; i++) fac_add(r, p_copy(& a->fac[i].f), a->fac[i].e);
	for (i = 0; i < b->n; i++) fac_add(r, p_copy(& b->fac[i].f), b->fac[i].e);
	rf_free(a); rf_free(b);
	if (rf_degree(r) > MAXDEG) { rf_free(r); return NULL; }
	return r;
}

RatFun * rf_pow (RatFun * a, int k)
{
	RatFun * r;
	int i;
	if (! a) return NULL;
	if (k == 0)
		{
		rf_free(a);
		r = rf_new();
		r->num = p_one();
		return r;
		}
	if (k < 0)			/* 1/a: numerator and denominator swap */
		{
		mpq_t lc;
		QPoly f;
		if (a->num.deg < 0 || a->num.deg * -k > MAXDEG) { rf_free(a); return NULL; }
		r = rf_new();
		r->num = p_one();
		for (i = 0; i < a->n; i++)
			{
			QPoly h = p_pow(& a->fac[i].f, a->fac[i].e), n = p_mul(& r->num, &h);
			qpoly_clear(&h); qpoly_clear(& r->num);
			r->num = n;
			}
		mpq_init(lc);
		mpq_inv(lc, C(& a->num, a->num.deg));
		p_scale(& r->num, lc);
		f = p_copy(& a->num);
		p_monic(&f);
		fac_add(r, f, 1);
		mpq_clear(lc);
		rf_free(a);
		a = r;
		k = -k;
		}
	if (rf_degree(a) * k > MAXDEG) { rf_free(a); return NULL; }
	r = rf_new();
	r->num = p_pow(& a->num, k);
	for (i = 0; i < a->n; i++) fac_add(r, p_copy(& a->fac[i].f), a->fac[i].e * k);
	rf_free(a);
	return r;
}

/* ---------------- factors ---------------- */

static int root_cands (unsigned long v, unsigned long * d, int max)	/* divisors */
{
	unsigned long k;
	int n = 0;
	for (k = 1; k * k <= v && n < max - 1; k++)
		if (v % k == 0)
			{
			d[n++] = k;
			if (k * k != v) d[n++] = v / k;
			}
	return n;
}

static int is_root (const QPoly * f, mpq_srcptr r)	/* Horner */
{
	mpq_t v;
	int k, z;
	mpq_init(v);
	for (k = f->deg; k >= 0; k--)
		{
		mpq_mul(v, v, r);
		mpq_add(v, v, C(f, k));
		}
	z = mpq_sgn(v) == 0;
	mpq_clear(v);
	return z;
}

/* splits off the rational roots of the square-free monic f: adds x - r to
 * the list with exponent e, returns the rest (monic) */
static QPoly split_roots (RatFun * out, QPoly f, int e)
{
	QPoly b;
	mpq_t u, r;
	unsigned long dp[256], dq[256];
	int np, nq, i, j, s;
	if (f.deg <= 1) { if (f.deg == 1) fac_add(out, f, e); else qpoly_clear(&f); return p_one(); }
	mpq_init(u); mpq_init(r);
	p_primitive(&f, &b, u);
	if (mpq_sgn(C(&b, 0)) == 0)		/* root 0 */
		{
		QPoly x = p_new(1), q;
		mpq_set_ui(C(&x, 1), 1, 1);
		p_divmod(&f, &x, &q, NULL);
		fac_add(out, x, e);
		qpoly_clear(&f); qpoly_clear(&b);
		mpq_clear(u); mpq_clear(r);
		p_monic(&q);
		return split_roots(out, q, e);
		}
	/* b has integer coefficients: a root p/q has p | b_0 and q | b_deg */
	if (mpz_cmpabs_ui(mpq_numref(C(&b, 0)), MAXROOT) > 0
	    || mpz_cmpabs_ui(mpq_numref(C(&b, b.deg)), MAXROOT) > 0)
		goto done;
	np = root_cands(mpz_get_ui(mpq_numref(C(&b, 0))), dp, 256);	/* absolute value */
	nq = root_cands(mpz_get_ui(mpq_numref(C(&b, b.deg))), dq, 256);
	for (i = 0; i < np; i++)
		for (j = 0; j < nq; j++)
			for (s = 1; s >= -1; s -= 2)
				{
				mpq_set_ui(r, dp[i], dq[j]);
				mpq_canonicalize(r);
				if (s < 0) mpq_neg(r, r);
				if (is_root(&f, r))
					{
					QPoly x = p_new(1), q;
					mpq_set_ui(C(&x, 1), 1, 1);
					mpq_neg(C(&x, 0), r);
					p_divmod(&f, &x, &q, NULL);
					fac_add(out, x, e);
					qpoly_clear(&f); qpoly_clear(&b);
					mpq_clear(u); mpq_clear(r);
					p_monic(&q);
					return split_roots(out, q, e);
					}
				}
done:
	qpoly_clear(&b);
	mpq_clear(u); mpq_clear(r);
	return f;
}

/* square-free parts of the monic f (Yun): f = prod s_i^i; each with its
 * rational roots split off, added with exponent i*e */
static void split_factor (RatFun * out, QPoly f, int e)
{
	QPoly d = p_deriv(&f), a, b, c, y, z;
	int i = 1;
	if (f.deg <= 1) { fac_add(out, f, e); qpoly_clear(&d); return; }
	a = p_gcd(&f, &d);
	p_divmod(&f, &a, &b, NULL);
	p_divmod(&d, &a, &c, NULL);
	qpoly_clear(&d); qpoly_clear(&f);
	for (;;)
		{
		QPoly bd = p_deriv(&b), s;
		y = p_add(&c, &bd, -1);
		qpoly_clear(&bd);
		if (y.deg < 0)
			{
			qpoly_clear(&y);
			p_monic(&b);
			s = split_roots(out, b, i * e);		/* takes b */
			fac_add(out, s, i * e);
			b = p_new(-1);
			break;
			}
		z = p_gcd(&b, &y);		/* s_i */
			{
			QPoly nb, nc;
			p_divmod(&b, &z, &nb, NULL);
			p_divmod(&y, &z, &nc, NULL);
			qpoly_clear(&b); qpoly_clear(&c); qpoly_clear(&y);
			b = nb; c = nc;
			}
		p_monic(&z);
		s = split_roots(out, z, i * e);
		fac_add(out, s, i * e);
		i++;
		if (b.deg <= 0) break;
		}
	qpoly_clear(&a); qpoly_clear(&b); qpoly_clear(&c);
}

/* pairwise coprime factors: g = gcd(f_i, f_j) of degree > 0 becomes a factor
 * of its own */
static void make_coprime (RatFun * r)
{
	int i, j, again = 1;
	while (again)
		{
		again = 0;
		for (i = 0; i < r->n && ! again; i++)
			for (j = i + 1; j < r->n && ! again; j++)
				{
				QPoly g = p_gcd(& r->fac[i].f, & r->fac[j].f), a, b;
				int ei = r->fac[i].e, ej = r->fac[j].e;
				if (g.deg <= 0) { qpoly_clear(&g); continue; }
				p_divmod(& r->fac[i].f, &g, &a, NULL);
				p_divmod(& r->fac[j].f, &g, &b, NULL);
				p_monic(&a); p_monic(&b);
				qpoly_clear(& r->fac[i].f); r->fac[i].f = a;
				qpoly_clear(& r->fac[j].f); r->fac[j].f = b;
				fac_add(r, g, ei + ej);
				for (int k = r->n - 1; k >= 0; k--)	/* remove constants */
					if (r->fac[k].f.deg <= 0)
						{
						qpoly_clear(& r->fac[k].f);
						r->fac[k] = r->fac[--r->n];
						}
				again = 1;
				}
		}
}

/* ---------------- partial fractions ---------------- */

static void add_term (ApartTerm ** t, int * n, QPoly num, const QPoly * base, int k)
{
	mpq_t u, s;
	QPoly b;
	if (num.deg < 0) { qpoly_clear(&num); return; }
	* t = (ApartTerm *) realloc(* t, (* n + 1) * sizeof(ApartTerm));
	if (! * t) fatal("apart : no room");
	mpq_init(u); mpq_init(s);
	p_primitive(base, &b, u);		/* base = u*b: num/base^k = num u^-k / b^k */
	mpz_pow_ui(mpq_numref(s), mpq_denref(u), k);
	mpz_pow_ui(mpq_denref(s), mpq_numref(u), k);
	if (mpz_sgn(mpq_denref(s)) < 0)
		{
		mpz_neg(mpq_numref(s), mpq_numref(s));
		mpz_neg(mpq_denref(s), mpq_denref(s));
		}
	mpq_canonicalize(s);
	p_scale(&num, s);
	(* t)[* n].coef = malloc(sizeof(__mpq_struct));
	if (! (* t)[* n].coef) fatal("apart : no room");
	mpq_init((mpq_ptr) (* t)[* n].coef);
	p_primitive(&num, & (* t)[* n].num, (mpq_ptr) (* t)[* n].coef);	/* num = coef*prim */
	qpoly_clear(&num);
	(* t)[* n].base = b;
	(* t)[* n].k = k;
	(* n)++;
	mpq_clear(u); mpq_clear(s);
}

int rf_apart (RatFun * a, QPoly * quot, ApartTerm ** terms)
{
	RatFun * f;
	QPoly den = p_one(), rem;
	int i, n = 0;
	* terms = NULL;
	quot->deg = -1; quot->c = NULL;
	if (! a || a->n == 0 || a->num.deg < 0) { rf_free(a); qpoly_clear(&den); return -1; }
	f = rf_new();			/* the factors, split and coprime */
	for (i = 0; i < a->n; i++)
		split_factor(f, p_copy(& a->fac[i].f), a->fac[i].e);
	make_coprime(f);
	for (i = 0; i < f->n; i++)
		{
		QPoly h = p_pow(& f->fac[i].f, f->fac[i].e), m = p_mul(&den, &h);
		qpoly_clear(&h); qpoly_clear(&den);
		den = m;
		}
	p_divmod(& a->num, &den, quot, &rem);
	qpoly_clear(&den);
	for (i = 0; i < f->n && rem.deg >= 0; i++)
		{
		QPoly pi = p_pow(& f->fac[i].f, f->fac[i].e), m = p_one(), s, t, g, ai, b;
		int j, k;
		for (j = i + 1; j < f->n; j++)
			{
			QPoly h = p_pow(& f->fac[j].f, f->fac[j].e), mm = p_mul(&m, &h);
			qpoly_clear(&h); qpoly_clear(&m);
			m = mm;
			}
		/* s pi + t m = 1:  rem/(pi m) = rem t/pi + rem s/m */
		g = p_gcdext(&pi, &m, &s, &t);
		qpoly_clear(&g);
		if (i < f->n - 1)
			{
			QPoly x = p_mul(&rem, &t), y = p_mul(&rem, &s);
			p_divmod(&x, &pi, NULL, &ai);
			qpoly_clear(&rem);
			p_divmod(&y, &m, NULL, &rem);
			qpoly_clear(&x); qpoly_clear(&y);
			}
		else
			{
			ai = rem;
			rem = p_new(-1);
			}
		qpoly_clear(&s); qpoly_clear(&t); qpoly_clear(&m); qpoly_clear(&pi);
		/* ai / f^e = sum c_k f^k / f^e with deg c_k < deg f */
		for (k = f->fac[i].e; k >= 1 && ai.deg >= 0; k--)
			{
			QPoly q, c;
			p_divmod(&ai, & f->fac[i].f, &q, &c);
			qpoly_clear(&ai);
			ai = q;
			add_term(terms, &n, c, & f->fac[i].f, k);
			}
		qpoly_clear(&ai);
		}
	qpoly_clear(&rem);
	rf_free(f);
	rf_free(a);
	return n;
}

void apart_free (ApartTerm * terms, int n)
{
	int i;
	for (i = 0; i < n; i++)
		{
		mpq_clear((mpq_ptr) terms[i].coef);
		free(terms[i].coef);
		qpoly_clear(& terms[i].num);
		qpoly_clear(& terms[i].base);
		}
	free(terms);
}

int mpq_is_one (void * q)
{
	return mpq_cmp_ui((mpq_ptr) q, 1, 1) == 0;
}
