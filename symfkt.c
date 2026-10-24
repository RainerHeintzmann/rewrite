/*
 *	symfkt.c (2026)
 *
 *	Symbolic helper functions, mainly for the rule-based integration
 *	(names follow Rubi's helpers in lower case, e.g. FreeQ -> freeq).
 *	They work on terms: the arguments are not evaluated numerically.
 *
 *	Predicates (result 1 or 0):
 *	  freeq(u,x)      x does not occur in u
 *	  integerq(u)     u is an integer number;  integersq(u,v,...) all are
 *	  rationalq(u,..) all arguments are numbers
 *	  posq(u), negq(u) u has a positive / negative form (as Rubi's PosQ)
 *	  eqq(u,v), neq(u,v)   u equals v (numerically, or as the same term)
 *	  igtq(u,n), iltq(u,n) u is an integer greater / less than n
 *	  polyq(u,x), polyq(u,x,n)  u is a polynomial in x (of degree n)
 *	  linearq(u,x)    u is a polynomial of degree 1 in x
 *	  sumq(u), productq(u), powerq(u)  form of the top level of u
 *	Term functions:
 *	  expand(u)            multiply out products and integer powers of sums
 *	  expandintegrand(u,x), expandintegrand(u,v,x)   expand(u), expand(u*v)
 *	  coeff(u,x,n)         coefficient of x^n in u
 *	  expon(u,x)           degree of u in x
 *	  subst(u,x,v)         u with x replaced by v
 *	  simp(u,x), simplify(u)  u (simplification is left to the rule sets)
 *	  dist(u,v,x)          u*v
 *	  rt(u,n)              n-th root of u
 *	  intpart(u), fracpart(u)  integer / non-integer part of numbers
 *	  inthide(u,x)                      Int(u,x)
 *	  fractionq(u,..), halfintegerq(u,..), nicesqrtq(u)   number tests
 *	  gcd(m,n,..)          greatest common divisor of fractions
 *	  numerator(u), denominator(u)  of a number or a product
 *	  freefactors(u,x), nonfreefactors(u,x)  factors free / not free of x
 *	  expandtosum(u,x)     polynomial u as a sum c_k*x^k
 *	  expandtosum(u,v,x)   u*expandtosum(v,x), distributed
 *	  polyquotient(p,q,x), polyremainder(p,q,x)  polynomial division
 *	  normpoly(u,x)        polynomial sums in u as c0 + c1*x + c2*x^2 + ...
 *	  deriv(u,x)           derivative (elementary functions; else unevaluated)
 *	  collect(u)           like summands combined, e.g. 2*a+b-a -> a+b
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "inout.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "node.h"
#include "nodes.h"
#include "sync.h"
#include "userfkt.h"  /* MAXARGS */
#include "symfkt.h"
#include "numsort.h"	/* 2026: integer, rational */

/* ================= basic term helpers ================= */

static Node * deref (Node * t)		/* follow Term symbols to their term */
{
	while (t && t->type == SYM_TYPE && lexval((Symbol *) t) == Term && t->l)
		t = t->l;
	return t;
}

static Symbol * num_sym (Node * t)	/* symbol of a real number, or NULL */
{
	Symbol * s;
	t = deref(t);
	if (! t) return NULL;
	if (t->type == Const) s = (Symbol *) t->l;
	else if (t->type == SYM_TYPE) s = (Symbol *) t;
	else return NULL;
	if (lexval(s) != Const || ! hasval(s) || ! value(s)) return NULL;
	if (sort_dist(rtypes(s), get_numbertype()) < 0) return NULL;	/* real, integer, rational */
	return s;
}

static int is_num (Node * t, double * v)
{
	Symbol * s = num_sym(t);
	double d;
	if (! s) return 0;
	if (! num_to_double(s, & d)) return 0;
	if (v) * v = d;
	return 1;
}

/* numeric value, also of a calculable expression like 2*3-1 */
static int num_value (Node * t, double * v)
{
	Node * r;
	if (is_num(t, v)) return 1;
	t = deref(t);
	if (! t || t->type != Func) return 0;
	r = calkulate(t);
	if (! r) return 0;
	if (! num_to_double((Symbol *) r, v))
		{ delnum((Symbol *) r, TRUE); return 0; }
	delnum((Symbol *) r, TRUE);
	return 1;
}

/* is the numeric value of t (see num_value) exact? */
static int num_value_exact (Node * t)
{
	Node * r;
	Symbol * s = num_sym(t);
	int ex;
	if (s) return num_exact(s);
	t = deref(t);
	if (! t || t->type != Func) return 0;
	r = calkulate(t);
	if (! r) return 0;
	ex = num_exact((Symbol *) r);
	delnum((Symbol *) r, TRUE);
	return ex;
}

static int is_head (Node * t, const char * h, int nargs)
{
	t = deref(t);
	return t && t->type == Func && strcmp(name(TERM_HEAD(t)), h) == 0
	       && (nargs < 0 || term_nargs(t) == nargs);
}

static Node * arg (Node * t, int i)
{
	return deref(term_arg(deref(t), i));
}

static Symbol * atom_sym (Node * t)	/* symbol of an atom (constant, variable) */
{
	t = deref(t);
	if (! t) return NULL;
	if (t->type == Const) return (Symbol *) t->l;
	if (t->type == SYM_TYPE) return (Symbol *) t;
	return NULL;
}

static Node * untrivial (Node * t)	/* 1*u, u*1, 0+u, u+0, u^1 -> u */
{
	double v;
	for (;;)
		{
		t = deref(t);
		if (is_head(t, "*", 2) && is_num(arg(t, 0), & v) && v == 1) t = arg(t, 1);
		else if (is_head(t, "*", 2) && is_num(arg(t, 1), & v) && v == 1) t = arg(t, 0);
		else if (is_head(t, "+", 2) && is_num(arg(t, 0), & v) && v == 0) t = arg(t, 1);
		else if (is_head(t, "+", 2) && is_num(arg(t, 1), & v) && v == 0) t = arg(t, 0);
		else if (is_head(t, "^", 2) && is_num(arg(t, 1), & v) && v == 1) t = arg(t, 0);
		else return t;
		}
}

static int tequal (Node * a, Node * b)
{
	double va, vb;
	Symbol * sa, * sb;
	int i, n;
	a = untrivial(a); b = untrivial(b);
	if (a == b) return 1;
	if (! a || ! b) return 0;
	if (is_num(a, & va) && is_num(b, & vb))
		return fabs(va - vb) <= 1e-12 * (1.0 + fabs(va));
	sa = atom_sym(a); sb = atom_sym(b);
	if (sa || sb) return sa == sb && sa != NULL;
	if (a->type != Func || b->type != Func) return 0;
	if (strcmp(name(TERM_HEAD(a)), name(TERM_HEAD(b))) != 0) return 0;
	n = term_nargs(a);
	if (n != term_nargs(b)) return 0;
	for (i = 0; i < n; i++)
		if (! tequal(arg(a, i), arg(b, i))) return 0;
	return 1;
}

int term_equal (Node * a, Node * b)	/* structural equality (exported) */
{
	return tequal(a, b);
}

int term_has_nan (Node * t)	/* contains NaN, infinity or a division by zero */
{
	double v;
	int i, n;
	t = deref(t);
	if (! t) return 0;
	if (is_num(t, & v)) return ! isfinite(v);
	if (t->type != Func) return 0;
	/* exact division by zero stays a term (1/0, 0^-1, mi(0)): also invalid */
	if (is_head(t, "/", 2) && is_num(arg(t, 1), & v) && v == 0) return 1;
	if (is_head(t, "^", 2) && is_num(arg(t, 0), & v) && v == 0
	    && is_num(arg(t, 1), & v) && v < 0) return 1;
	if (is_head(t, "mi", 1) && is_num(arg(t, 0), & v) && v == 0) return 1;
	n = term_nargs(t);
	for (i = 0; i < n; i++)
		if (term_has_nan(arg(t, i))) return 1;
	return 0;
}

static int contains (Node * t, Node * x)
{
	int i, n;
	t = deref(t);
	if (! t) return 0;
	if (tequal(t, x)) return 1;
	if (t->type != Func) return 0;
	n = term_nargs(t);
	for (i = 0; i < n; i++)
		if (contains(arg(t, i), x)) return 1;
	return 0;
}

/* ================= building terms ================= */

static Node * mk_num (double v)
{
	double * d = (double *) malloc(sizeof(double));
	if (! d) fatal("symfkt : no room");
	* d = v;
	return mknod(Const, (Node *) mknum(d, NULL), NULL);
}

static Node * mk_bool (int b, Symbol * f)		/* 1/0 in the result sort of f */
{
	double * d = (double *) malloc(sizeof(double));
	if (! d) fatal("symfkt : no room");
	* d = b ? 1.0 : 0.0;
	return mknod(Const, (Node *) mknum(d, rtypes(f)), NULL);
}

static int rat_approx (double v, double * p, double * q);

/* number from a double: exact (integer or rational) if 'exact' and inc/exact
 * is loaded, else real */
static Node * mk_num_ex (double v, int exact)
{
	double p, q;
	Symbol * es;
	if (exact && exact_numbers() && rat_approx(v, & p, & q)
	    && fabs(p) < 9e15 && q < 9e15
	    && (es = make_exact((long long) p, (long long) q)) != NULL)
		return mknod(Const, (Node *) es, NULL);
	return mk_num(v);
}

static Node * mk_int (double v)		/* a number that is exact by construction */
{
	return mk_num_ex(v, 1);
}

static int is_exact (Node * t)		/* integer or rational number */
{
	Symbol * s = num_sym(t);
	return s && num_exact(s);
}

/* copy of a term: new nodes, numbers cloned, other symbols shared */
static Node * tcpy (Node * t)
{
	Symbol * ns;
	t = deref(t);
	if (! t) return NULL;
	if ((ns = num_sym(t)) != NULL)		/* number: clone it, keep its sort */
		return mknod(Const, (Node *) mknum(CPYNUM(ns, value(ns)), rtypes(ns)), NULL);
	if (t->type == SYM_TYPE) return t;
	if (t->type == Const) return mknod(Const, t->l, NULL);
	if (t->type == Func) return mknod(Func, t->l, tcpy(t->r));
	return mknod(t->type, tcpy(t->l), tcpy(t->r));
}

Node * term_copy (Node * t)	/* exported tcpy */
{
	return tcpy(t);
}

static Symbol * fsym (const char * f)
{
	Symbol * s = find_symbol(f);
	if (! s) fatal("symfkt : function %s is not declared", f);
	return s;
}


static Node * mk_f2 (const char * f, Node * a, Node * b)
{
	Node * t = mknod(Terms, a, b);
	return mknod(Func, (Node *) getsymbol(fsym(f), t), t);
}

/* the constructors take ownership of their arguments */
static Node * fold_exact (const char * f, Node * a, Node * b);

static Node * mk_add (Node * a, Node * b)
{
	double va, vb;
	if (! a) return b;
	if (! b) return a;
	if (is_exact(a) && is_exact(b)) return fold_exact("+", a, b);
	if (is_num(a, & va) && is_num(b, & vb)) { delete(a); delete(b); return mk_num(va + vb); }
	if (is_num(a, & va) && va == 0) { delete(a); return b; }
	if (is_num(b, & vb) && vb == 0) { delete(b); return a; }
	return mk_f2("+", a, b);
}

static Node * mk_mul (Node * a, Node * b)
{
	double va, vb;
	if (is_exact(a) && is_exact(b)) return fold_exact("*", a, b);
	if (is_num(a, & va) && is_num(b, & vb)) { delete(a); delete(b); return mk_num(va * vb); }
	if ((is_num(a, & va) && va == 0) || (is_num(b, & vb) && vb == 0))
		{ delete(a); delete(b); return mk_int(0); }
	if (is_num(a, & va) && va == 1) { delete(a); return b; }
	if (is_num(b, & vb) && vb == 1) { delete(b); return a; }
	return mk_f2("*", a, b);
}

static Node * mk_pow (Node * a, Node * b)
{
	double va, vb;
	if (is_num(b, & vb) && vb == 0) { delete(a); delete(b); return mk_int(1); }
	if (is_num(b, & vb) && vb == 1) { delete(b); return a; }
	if (is_exact(a) && is_exact(b) && is_num(b, & vb) && vb == floor(vb) && fabs(vb) < 1000)
		return fold_exact("^", a, b);
	if (is_num(a, & va) && is_num(b, & vb) && (va > 0 || vb == floor(vb)))
		{ delete(a); delete(b); return mk_num(pow(va, vb)); }
	return mk_f2("^", a, b);
}

/* a f b for two exact numbers, with the exact functions of inc/exact */
static Node * fold_exact (const char * f, Node * a, Node * b)
{
	Node * t = mk_f2(f, a, b), * r = calkulate(t);
	if (! r) return t;		/* e.g. division by zero: stays a term */
	delete(t);
	return mknod(Const, r, NULL);
}

/* ================= expansion into summands ================= */

typedef struct { Node ** t; int n, cap; } TList;

static void tl_add (TList * l, Node * t)
{
	if (l->n == l->cap)
		{
		l->cap = l->cap ? 2 * l->cap : 8;
		l->t = (Node **) realloc(l->t, l->cap * sizeof(Node *));
		if (! l->t) fatal("symfkt : no room");
		}
	l->t[l->n++] = t;
}

static void tl_free (TList * l)
{
	int i;
	for (i = 0; i < l->n; i++) delete(l->t[i]);
	free(l->t);
	l->t = NULL; l->n = l->cap = 0;
}

static void tl_product (TList * a, TList * b, TList * out)	/* all products a_i*b_j */
{
	int i, j;
	for (i = 0; i < a->n; i++)
		for (j = 0; j < b->n; j++)
			tl_add(out, mk_mul(tcpy(a->t[i]), tcpy(b->t[j])));
}

#define MAXEXPPOWER 30

static void summands_to (Node * t, TList * out, int neg);
static Node * tl_collect (TList * l);

static void expand_to (Node * t, TList * out)
{
	TList a = {0}, b = {0};
	double e;
	int i;
	t = deref(t);
	if (is_head(t, "+", 2))
		{
		expand_to(arg(t, 0), out);
		expand_to(arg(t, 1), out);
		}
	else if (is_head(t, "-", 2) || is_head(t, "-", 1))
		{
		if (term_nargs(t) == 2) expand_to(arg(t, 0), out);
		expand_to(arg(t, term_nargs(t) - 1), & a);
		for (i = 0; i < a.n; i++)
			tl_add(out, mk_mul(mk_int(-1), tcpy(a.t[i])));
		}
	else if (is_head(t, "*", 2))
		{
		expand_to(arg(t, 0), & a);
		expand_to(arg(t, 1), & b);
		tl_product(& a, & b, out);
		}
	else if (is_head(t, "/", 2))
		{
		expand_to(arg(t, 0), & a);
		for (i = 0; i < a.n; i++)
			tl_add(out, mk_mul(tcpy(a.t[i]), mk_pow(tcpy(arg(t, 1)), mk_int(-1))));
		}
	else if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e == 1)
		expand_to(arg(t, 0), out);			/* u^1 = u */
	else if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e == 0)
		tl_add(out, mk_int(1));				/* u^0 = 1 */
	else if (is_head(t, "^", 2) && num_value(arg(t, 1), & e)
	         && e == floor(e) && e >= 2 && e <= MAXEXPPOWER)
		{
		expand_to(arg(t, 0), & a);
		if (a.n < 2)
			tl_add(out, tcpy(t));
		else
			{
			TList r = {0}, nr = {0};
			for (i = 0; i < a.n; i++) tl_add(& r, tcpy(a.t[i]));
			for (i = 1; i < (int) e; i++)
				{
				Node * c;
				nr.t = NULL; nr.n = nr.cap = 0;
				tl_product(& r, & a, & nr);
				tl_free(& r);
				/* collect like terms after each step: (1-x)^20 has 21
				   terms, not 2^20 */
				c = tl_collect(& nr);
				r.t = NULL; r.n = r.cap = 0;
				summands_to(c, & r, 0);
				delete(c);
				}
			for (i = 0; i < r.n; i++) tl_add(out, r.t[i]);
			free(r.t);
			}
		}
	else
		tl_add(out, tcpy(t));
	tl_free(& a);
	tl_free(& b);
}

/* ---- collecting like terms: c * b1^e1 * b2^e2 ... ---- */

int tcmp (Node * a, Node * b);	/* run.c: order of terms (as LB) */

typedef struct { Node * base; double e; int exact; } Fac;
typedef struct { double c; Fac * f; int nf, cap; int exact; } Mono;	/* exact: all numbers were exact */

static void mono_addfac (Mono * m, Node * base, double e, int exact)
{
	int i;
	for (i = 0; i < m->nf; i++)
		if (tequal(m->f[i].base, base)) { m->f[i].e += e; m->f[i].exact &= exact; return; }
	if (m->nf == m->cap)
		{
		m->cap = m->cap ? 2 * m->cap : 4;
		m->f = (Fac *) realloc(m->f, m->cap * sizeof(Fac));
		if (! m->f) fatal("symfkt : no room");
		}
	m->f[m->nf].base = base;
	m->f[m->nf].e = e;
	m->f[m->nf].exact = exact;
	m->nf++;
}

static void mono_flatten (Node * t, Mono * m)	/* t is a product */
{
	double v, e;
	t = deref(t);
	if (num_value(t, & v)) { m->c *= v; if (! num_value_exact(t)) m->exact = 0; }
	else if (is_head(t, "*", 2)) { mono_flatten(arg(t, 0), m); mono_flatten(arg(t, 1), m); }
	else if (is_head(t, "-", 1)) { m->c = -m->c; mono_flatten(arg(t, 0), m); }
	else if (is_head(t, "^", 2) && num_value(arg(t, 1), & e))
		mono_addfac(m, arg(t, 0), e, num_value_exact(arg(t, 1)));
	else mono_addfac(m, t, 1, 1);
}

static void mono_normalize (Mono * m)	/* drop x^0, sort the bases */
{
	int i, j, k = 0;
	for (i = 0; i < m->nf; i++)
		if (m->f[i].e != 0) m->f[k++] = m->f[i];
	m->nf = k;
	for (i = 1; i < m->nf; i++)	/* insertion sort by tcmp */
		for (j = i; j > 0 && tcmp(m->f[j-1].base, m->f[j].base) > 0; j--)
			{ Fac h = m->f[j]; m->f[j] = m->f[j-1]; m->f[j-1] = h; }
}

static int mono_like (Mono * a, Mono * b)
{
	int i;
	if (a->nf != b->nf) return 0;
	for (i = 0; i < a->nf; i++)
		if (a->f[i].e != b->f[i].e || ! tequal(a->f[i].base, b->f[i].base)) return 0;
	return 1;
}

static Node * mono_build (Mono * m)
{
	Node * t = NULL;
	int i;
	for (i = 0; i < m->nf; i++)
		{
		Node * p = mk_pow(tcpy(m->f[i].base), mk_num_ex(m->f[i].e, m->f[i].exact));
		t = t ? mk_mul(t, p) : p;
		}
	if (! t) return mk_num_ex(m->c, m->exact);
	return (m->c == 1) ? t : mk_mul(mk_num_ex(m->c, m->exact), t);
}

/* sum of the summands with like terms collected (takes the terms) */
static Node * tl_collect (TList * l)
{
	Mono * ms = (Mono *) calloc(l->n ? l->n : 1, sizeof(Mono));
	double * mag = (double *) calloc(l->n ? l->n : 1, sizeof(double));
	int i, j, nm = 0;
	Node * s = NULL;
	if (! ms || ! mag) fatal("symfkt : no room");
	for (i = 0; i < l->n; i++)
		{
		Mono m = { 1.0, NULL, 0, 0, 1 };
		mono_flatten(l->t[i], & m);
		mono_normalize(& m);
		for (j = 0; j < nm; j++)
			if (mono_like(& ms[j], & m)) break;
		if (j < nm) { ms[j].c += m.c; ms[j].exact &= m.exact; free(m.f); }
		else ms[nm++] = m;
		if (fabs(m.c) > mag[j]) mag[j] = fabs(m.c);
		}
	for (j = 0; j < nm; j++)
		{
		/* cancelled up to rounding errors: 0.375 a - 0.375 a */
		if (fabs(ms[j].c) > 1e-12 * mag[j]) s = mk_add(s, mono_build(& ms[j]));
		free(ms[j].f);
		}
	free(ms);
	free(mag);
	tl_free(l);	/* the monomials referred to these terms */
	return s ? s : mk_int(0);
}


/* t = c * x^k with c free of x.  *c is a new term. */
static int monomial (Node * t, Node * x, Node ** c, double * k)
{
	Node * c1, * c2;
	double k1, k2, e;
	t = deref(t);
	if (! contains(t, x)) { * c = tcpy(t); * k = 0; return 1; }
	if (tequal(t, x)) { * c = mk_int(1); * k = 1; return 1; }
	if (is_head(t, "^", 2) && tequal(arg(t, 0), x) && num_value(arg(t, 1), & e))
		{ * c = mk_int(1); * k = e; return 1; }
	if (is_head(t, "*", 2))
		{
		if (! monomial(arg(t, 0), x, & c1, & k1)) return 0;
		if (! monomial(arg(t, 1), x, & c2, & k2)) { delete(c1); return 0; }
		* c = mk_mul(c1, c2); * k = k1 + k2;
		return 1;
		}
	if (is_head(t, "-", 1))
		{
		if (! monomial(arg(t, 0), x, & c1, & k1)) return 0;
		* c = mk_mul(mk_int(-1), c1); * k = k1;
		return 1;
		}
	if (is_head(t, "/", 2) && ! contains(arg(t, 1), x))
		{
		if (! monomial(arg(t, 0), x, & c1, & k1)) return 0;
		* c = mk_mul(c1, mk_pow(tcpy(arg(t, 1)), mk_int(-1))); * k = k1;
		return 1;
		}
	return 0;
}

/* polynomial analysis of u in x: degree, coefficient of x^n (if wanted) */
static int poly_info (Node * u, Node * x, double * degree, double n, Node ** coef)
{
	TList l = {0}, cl = {0};	/* summands of u, parts of the coefficient */
	int i, ok = 1;
	double deg = 0;
	expand_to(u, & l);
	for (i = 0; i < l.n && ok; i++)
		{
		Node * c; double k;
		if (! monomial(l.t[i], x, & c, & k) || k < 0 || k != floor(k))
			{ ok = 0; break; }
		if (k > deg) deg = k;
		if (coef && k == n) tl_add(& cl, c);
		else delete(c);
		}
	tl_free(& l);
	if (degree) * degree = deg;
	if (coef && ok)
		* coef = tl_collect(& cl);	/* coefficient with like terms collected */
	else
		{
		tl_free(& cl);
		if (coef) * coef = NULL;
		}
	return ok;
}

/* ================= predicates ================= */

static Node * s_freeq (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_bool(! contains(a[0], a[1]), f);
}

static Node * s_integerq (Node * a[], int n, Symbol * f)
{
	int i; double v;
	for (i = 0; i < n; i++)
		if (! num_value(a[i], & v) || v != floor(v)) return mk_bool(0, f);
	return mk_bool(n > 0, f);
}

static Node * s_rationalq (Node * a[], int n, Symbol * f)
{
	int i; double v;
	for (i = 0; i < n; i++)
		if (! num_value(a[i], & v)) return mk_bool(0, f);
	return mk_bool(n > 0, f);
}

static int posaux (Node * u)		/* Rubi's PosAux */
{
	double v, e;
	u = deref(u);
	if (num_value(u, & v)) return v > 0;
	if (is_head(u, "^", 2))
		{
		if (is_num(arg(u, 1), & e) && e == floor(e))
			return fmod(e, 2.0) == 0 || posaux(arg(u, 0));
		return 1;
		}
	if (is_head(u, "*", 2) || is_head(u, "/", 2))
		return posaux(arg(u, 0)) ? posaux(arg(u, 1)) : ! posaux(arg(u, 1));
	if (is_head(u, "+", 2) || is_head(u, "-", 2))
		return posaux(arg(u, 0));
	if (is_head(u, "-", 1))
		return ! posaux(arg(u, 0));
	return 1;
}

static int is_zero (Node * u)
{
	double v;
	return num_value(u, & v) && v == 0;
}

static Node * s_posq (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return mk_bool(! is_zero(a[0]) && posaux(a[0]), f);
}

static Node * s_negq (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return mk_bool(! is_zero(a[0]) && ! posaux(a[0]), f);
}

/* u = v: numerically, as the same term, or if u-v expands to 0
 * (like Rubi's EqQ, which tests PossibleZeroQ[u-v]) */
static int eq_terms (Node * u, Node * v)
{
	double x, y;
	TList l = {0};
	Node * d;
	int zero;
	if (num_value(u, & x) && num_value(v, & y))
		return fabs(x - y) <= 1e-12 * (1.0 + fabs(x));
	if (tequal(u, v)) return 1;
	d = mk_add(tcpy(u), mk_mul(mk_int(-1), tcpy(v)));
	expand_to(d, & l);
	delete(d);
	d = tl_collect(& l);
	zero = is_num(d, & x) && fabs(x) <= 1e-12;
	delete(d);
	return zero;
}

static Node * s_eqq (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_bool(eq_terms(a[0], a[1]), f);
}

static Node * s_neq (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_bool(! eq_terms(a[0], a[1]), f);
}

static Node * s_igtq (Node * a[], int n, Symbol * f)
{
	double u, m;
	if (n != 2) return NULL;
	return mk_bool(num_value(a[0], & u) && u == floor(u) && num_value(a[1], & m) && u > m, f);
}

static Node * s_iltq (Node * a[], int n, Symbol * f)
{
	double u, m;
	if (n != 2) return NULL;
	return mk_bool(num_value(a[0], & u) && u == floor(u) && num_value(a[1], & m) && u < m, f);
}

static Node * s_polyq (Node * a[], int n, Symbol * f)
{
	double deg, want;
	Node * c = NULL;
	int ok;
	if (n == 2)
		return mk_bool(poly_info(a[0], a[1], & deg, -1, NULL), f);
	if (n != 3 || ! num_value(a[2], & want)) return NULL;
	ok = poly_info(a[0], a[1], & deg, want, & c);
	ok = ok && deg == want && ! is_zero(c);
	delete(c);
	return mk_bool(ok, f);
}

static Node * s_linearq (Node * a[], int n, Symbol * f)
{
	double deg;
	if (n != 2) return NULL;
	return mk_bool(poly_info(a[0], a[1], & deg, -1, NULL) && deg == 1, f);
}

static Node * s_sumq (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return mk_bool(is_head(a[0], "+", 2) || is_head(a[0], "-", 2), f);
}

static Node * s_productq (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return mk_bool(is_head(a[0], "*", 2) || is_head(a[0], "/", 2), f);
}

static Node * s_powerq (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return mk_bool(is_head(a[0], "^", 2), f);
}

/* ================= term functions ================= */

static Node * s_expand (Node * a[], int n, Symbol * f)
{
	TList l = {0};
	if (n < 1 || n > 2) return NULL;	/* expand(u), expand(u,x) */
	expand_to(a[0], & l);
	return tl_collect(& l);
}

static Node * expand_linear_product (Node * u, Node * x);

static Node * s_expandintegrand (Node * a[], int n, Symbol * f)
{
	TList l = {0};
	Node * in, * r;
	if (n == 2 && (r = expand_linear_product(a[0], a[1])))
		return r;
	if (n == 2)
		in = tcpy(a[0]);
	else if (n == 3)
		in = mk_mul(tcpy(a[0]), tcpy(a[1]));
	else
		return NULL;
	expand_to(in, & l);
	r = tl_collect(& l);
	/* Rubi rules like Int[u] := Int[ExpandIntegrand[u,x],x] loop if the
	 * expansion makes no progress (e.g. partial fractions, which are not
	 * implemented). Then expandintegrand stays unevaluated. */
	if (tequal(r, in))
		{
		delete(r);
		r = NULL;
		}
	delete(in);
	return r;
}

static Node * s_coeff (Node * a[], int n, Symbol * f)
{
	double deg, k = 1;
	Node * c = NULL;
	if (n == 3 && ! num_value(a[2], & k)) return NULL;
	if (n != 2 && n != 3) return NULL;
	if (! poly_info(a[0], a[1], & deg, k, & c)) return NULL;
	return c;
}

static Node * s_expon (Node * a[], int n, Symbol * f)
{
	double deg;
	if (n != 2) return NULL;
	if (! poly_info(a[0], a[1], & deg, -1, NULL)) return NULL;
	return mk_int(deg);
}

static Node * replace (Node * t, Node * x, Node * v)
{
	t = deref(t);
	if (! t) return NULL;
	if (tequal(t, x)) return tcpy(v);
	if (t->type == Func) return mknod(Func, t->l, replace(t->r, x, v));
	if (t->type == Terms) return mknod(Terms, replace(t->l, x, v), replace(t->r, x, v));
	return tcpy(t);
}

static int contains_head (Node * t, const char * h)	/* is h(...) somewhere in t? */
{
	int i, n;
	t = deref(t);
	if (! t || t->type != Func) return 0;
	if (strcmp(name(TERM_HEAD(t)), h) == 0) return 1;
	n = term_nargs(t);
	for (i = 0; i < n; i++)
		if (contains_head(arg(t, i), h)) return 1;
	return 0;
}

static Node * s_subst (Node * a[], int n, Symbol * f)
{
	if (n != 3) return NULL;
	if (tequal(a[1], a[2])) return tcpy(a[0]);	/* x -> x (also x^1, 1*x) */
	/* Rubi: Subst[Int[...],x,u] integrates first. Wait until no Int is left. */
	if (contains_head(a[0], "Int")) return NULL;
	return replace(a[0], a[1], a[2]);
}

static Node * s_simp (Node * a[], int n, Symbol * f)	/* simp(u,x), simplify(u) */
{
	if (n < 1 || n > 2) return NULL;
	return tcpy(a[0]);
}

static Node * s_dist (Node * a[], int n, Symbol * f)
{
	if (n != 2 && n != 3) return NULL;
	return mk_mul(tcpy(a[0]), tcpy(a[1]));
}

static Node * s_rt (Node * a[], int n, Symbol * f)
{
	double u, k;
	if (n != 2 || ! num_value(a[1], & k) || k == 0) return NULL;
	if (k == floor(k) && k > 0 && num_sym(a[0]) && is_exact(a[0]))	/* exact root? */
		{
		Symbol * r = exact_root(num_sym(a[0]), (long) k), * r2;
		if (r) return mknod(Const, (Node *) r, NULL);
		if (fmod(k, 2.0) != 0 && num_value(a[0], & u) && u < 0)	/* odd root of a negative number */
			{
			Node * neg = mk_mul(mk_int(-1), tcpy(a[0]));
			r2 = exact_root(num_sym(neg), (long) k);
			delete(neg);
			if (r2) return mk_mul(mk_int(-1), mknod(Const, (Node *) r2, NULL));
			}
		}
	if (num_value(a[0], & u))
		{
		if (u < 0 && k == floor(k) && fmod(k, 2.0) != 0)
			return mk_num(-pow(-u, 1.0 / k));
		if (u >= 0)
			return mk_num(pow(u, 1.0 / k));
		}
	return mk_pow(tcpy(a[0]), mk_num_ex(1.0 / k, num_value_exact(a[1])));
}

static Node * part (Node * u, int frac)
{
	double v;
	u = deref(u);
	if (num_value(u, & v))
		return mk_num_ex(frac ? v - trunc(v) : trunc(v), num_value_exact(u));
	if (is_head(u, "+", 2))
		return mk_add(part(arg(u, 0), frac), part(arg(u, 1), frac));
	return frac ? tcpy(u) : mk_int(0);
}

static Node * s_intpart (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return part(a[0], 0);
}

static Node * s_fracpart (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return part(a[0], 1);
}

static Node * s_inthide (Node * a[], int n, Symbol * f)	/* inthide */
{
	if (n != 2 || ! find_symbol("Int")) return NULL;
	return mk_f2("Int", tcpy(a[0]), tcpy(a[1]));
}

/* ================= numbers as fractions ================= */

/* v = p/q (continued fractions, q <= 1e6); 0 if no such fraction is close */
static int rat_approx (double v, double * p, double * q)
{
	double x = fabs(v), h0 = 0, h1 = 1, k0 = 1, k1 = 0, a, h, k;
	int i;
	if (! isfinite(v)) return 0;
	for (i = 0; i < 40; i++)
		{
		a = floor(x);
		h = a * h1 + h0; k = a * k1 + k0;
		h0 = h1; h1 = h; k0 = k1; k1 = k;
		if (k1 > 1e6) return 0;
		if (fabs(fabs(v) - h1 / k1) <= 1e-12 * (1.0 + fabs(v))) break;
		if (x - a < 1e-15) break;
		x = 1.0 / (x - a);
		}
	* p = v < 0 ? -h1 : h1;
	* q = k1;
	return 1;
}

static double gcd2 (double a, double b)		/* integers */
{
	a = fabs(a); b = fabs(b);
	while (b > 0.5) { double r = fmod(a, b); a = b; b = r; }
	return a;
}

static Node * s_fractionq (Node * a[], int n, Symbol * f)	/* all non-integer numbers */
{
	int i; double v;
	for (i = 0; i < n; i++)
		if (! num_value(a[i], & v) || v == floor(v)) return mk_bool(0, f);
	return mk_bool(n > 0, f);
}

static Node * s_halfintegerq (Node * a[], int n, Symbol * f)
{
	int i; double v;
	for (i = 0; i < n; i++)
		if (! num_value(a[i], & v) || v == floor(v) || 2 * v != floor(2 * v))
			return mk_bool(0, f);
	return mk_bool(n > 0, f);
}

static Node * s_nicesqrtq (Node * a[], int n, Symbol * f)	/* Rubi: rational and > 0 */
{
	double v;
	if (n != 1) return NULL;
	return mk_bool(num_value(a[0], & v) && v > 0, f);
}

static Node * s_gcd (Node * a[], int n, Symbol * f)	/* gcd of fractions */
{
	double p, q, gp = 0, gq = 1, v;
	int i;
	if (n < 1) return NULL;
	for (i = 0; i < n; i++)
		{
		if (! num_value(a[i], & v) || ! rat_approx(v, & p, & q)) return NULL;
		/* gcd(gp/gq, p/q) = gcd(gp*q, p*gq) / (gq*q) */
		gp = gcd2(gp * q, p * gq);
		gq = gq * q;
		v = gcd2(gp, gq);
		if (v > 0) { gp /= v; gq /= v; }
		}
	return mk_int(gp / gq);
}

/* factors of a product (binary *) */
static void factors_to (Node * t, TList * out)
{
	t = deref(t);
	if (is_head(t, "*", 2))
		{
		factors_to(arg(t, 0), out);
		factors_to(arg(t, 1), out);
		}
	else
		tl_add(out, t);
}

/* numerator (den = 0) or denominator (den = 1) of u */
static Node * numden (Node * u, int den)
{
	TList l = {0};
	Node * r = NULL;
	double v, p, q, e;
	int i;
	if (num_value(u, & v))
		{
		if (! rat_approx(v, & p, & q)) return den ? mk_int(1) : mk_num(v);
		return mk_int(den ? q : p);
		}
	factors_to(u, & l);
	for (i = 0; i < l.n; i++)
		{
		Node * t = l.t[i], * part = NULL;
		if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e < 0)
			{
			if (den) part = mk_pow(tcpy(arg(t, 0)), mk_num_ex(-e, num_value_exact(arg(t, 1))));
			}
		else if (is_head(t, "/", 2))
			part = tcpy(arg(t, den ? 1 : 0));
		else if (num_value(t, & v) && rat_approx(v, & p, & q))
			part = mk_int(den ? q : p);
		else if (! den)
			part = tcpy(t);
		if (part) r = r ? mk_mul(r, part) : part;
		}
	l.n = 0;	/* the factors belong to u */
	tl_free(& l);
	return r ? r : mk_int(1);
}

static Node * s_numerator (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return numden(a[0], 0);
}

static Node * s_denominator (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return numden(a[0], 1);
}

/* product of the factors of u that are free (free = 1) or not free of x */
static Node * s_freefactors_aux (Node * u, Node * x, int free)
{
	TList l = {0};
	Node * r = NULL;
	int i;
	factors_to(u, & l);
	for (i = 0; i < l.n; i++)
		if ((! contains(l.t[i], x)) == free)
			r = r ? mk_mul(r, tcpy(l.t[i])) : tcpy(l.t[i]);
	l.n = 0;
	tl_free(& l);
	return r ? r : mk_int(1);
}

static Node * s_freefactors (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return s_freefactors_aux(a[0], a[1], 1);
}

static Node * s_nonfreefactors (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return s_freefactors_aux(a[0], a[1], 0);
}

/* coefficients c[0..deg] of the polynomial u in x (new terms), or 0 */
#define MAXDEG 64
static int poly_coeffs (Node * u, Node * x, Node * c[], int * deg)
{
	double d;
	int k;
	if (! poly_info(u, x, & d, -1, NULL) || d > MAXDEG - 1) return 0;
	* deg = (int) d;
	for (k = 0; k <= * deg; k++)
		if (! poly_info(u, x, & d, k, & c[k]))
			{
			while (--k >= 0) delete(c[k]);
			return 0;
			}
	return 1;
}

static Node * poly_build (Node * c[], int deg, Node * x)	/* takes the c[k] */
{
	Node * s = NULL;
	int k;
	for (k = 0; k <= deg; k++)
		{
		if (is_zero(c[k])) { delete(c[k]); continue; }
		s = mk_add(s, k == 0 ? c[k] : mk_mul(c[k], mk_pow(tcpy(x), mk_int(k))));
		}
	return s ? s : mk_int(0);
}

static Node * expand_to_sum (Node * u, Node * x)
{
	Node * c[MAXDEG];
	int deg;
	if (! poly_coeffs(u, x, c, & deg)) return tcpy(u);
	return poly_build(c, deg, x);
}

static Node * s_expandtosum (Node * a[], int n, Symbol * f)	/* (u,x), (u,v,x) */
{
	TList l = {0};
	Node * w, * r = NULL;
	int i;
	if (n == 2) return expand_to_sum(a[0], a[1]);
	if (n != 3) return NULL;
	w = expand_to_sum(a[1], a[2]);		/* u * ExpandToSum[v,x], distributed */
	expand_to(w, & l);
	for (i = 0; i < l.n; i++)
		r = mk_add(r, mk_mul(tcpy(a[0]), tcpy(l.t[i])));
	tl_free(& l);
	delete(w);
	return r ? r : mk_int(0);
}

/* polynomial division p = quot*q + rem in x */
static Node * polydiv (Node * a[], int n, int want_rem)
{
	Node * p[MAXDEG], * q[MAXDEG], * quot[MAXDEG];
	int dp, dq, k, j;
	if (n != 3) return NULL;
	if (! poly_coeffs(a[0], a[2], p, & dp)) return NULL;
	if (! poly_coeffs(a[1], a[2], q, & dq) || is_zero(q[dq]))
		{
		for (k = 0; k <= dp; k++) delete(p[k]);
		return NULL;
		}
	for (k = dp - dq; k >= 0; k--)
		{
		/* quot[k] = p[k+dq] / q[dq];  p[k+j] -= quot[k]*q[j] */
		quot[k] = mk_mul(tcpy(p[k + dq]), mk_pow(tcpy(q[dq]), mk_int(-1)));
		for (j = 0; j <= dq; j++)
			p[k + j] = mk_add(p[k + j],
				mk_mul(mk_int(-1), mk_mul(tcpy(quot[k]), tcpy(q[j]))));
		}
	for (j = 0; j <= dq; j++) delete(q[j]);
	if (want_rem)
		{
		for (k = 0; k <= dp - dq; k++) delete(quot[k]);
		if (dp < dq) return poly_build(p, dp, a[2]);
		for (k = dq; k <= dp; k++) delete(p[k]);	/* zero now */
		if (dq == 0) return mk_int(0);
		return poly_build(p, dq - 1, a[2]);
		}
	for (k = 0; k <= dp; k++) delete(p[k]);
	if (dp < dq) return mk_int(0);
	return poly_build(quot, dp - dq, a[2]);
}

/* Rubi's ExpandLinearProduct: P(x) * (c + d x)^n with P a polynomial and n
 * not a non-negative integer is written as a sum of e_k (c + d x)^(k + n):
 *   x = (v - c)/d,  e_k = sum_{j>=k} p_j d^-j binomial(j,k) (-c)^(j-k).
 * Returns NULL if u has not this form. */
static Node * expand_linear_product (Node * u, Node * x)
{
	TList l = {0};
	Node * lin = NULL, * expo = NULL, * rest = NULL, * p[MAXDEG], * lc[MAXDEG];
	Node * r = NULL;
	double n = 0, binom;
	int i, j, k, deg, dl;
	factors_to(u, & l);
	for (i = 0; i < l.n; i++)
		{
		Node * t = l.t[i];
		double e;
		if (! lin && is_head(t, "^", 2) && contains(arg(t, 0), x)
		    && ! contains(arg(t, 1), x)
		    && ! (num_value(arg(t, 1), & e) && e >= 0 && e == floor(e)))
			{
			if (! poly_coeffs(arg(t, 0), x, lc, & dl)) continue;
			if (dl != 1) { delete(lc[0]); delete(lc[1]); continue; }
			lin = arg(t, 0);
			expo = arg(t, 1);
			continue;
			}
		rest = rest ? mk_mul(rest, tcpy(t)) : tcpy(t);
		}
	l.n = 0;
	tl_free(& l);
	if (! lin) { delete(rest); return NULL; }
	if (! rest) rest = mk_int(1);
	if (! contains(rest, x) || ! poly_coeffs(rest, x, p, & deg) || deg < 1)
		{
		delete(rest); delete(lc[0]); delete(lc[1]);
		return NULL;
		}
	delete(rest);
	num_value(expo, & n);
	for (k = 0; k <= deg; k++)
		{
		Node * e = NULL, * ex;
		for (j = k; j <= deg; j++)
			{
			Node * term;
			int m;
			binom = 1;
			for (m = 1; m <= k; m++) binom = binom * (j - k + m) / m;
			term = mk_mul(mk_int(binom), tcpy(p[j]));
			term = mk_mul(term, mk_pow(tcpy(lc[1]), mk_int(-j)));
			term = mk_mul(term, mk_pow(mk_mul(mk_int(-1), tcpy(lc[0])), mk_int(j - k)));
			e = mk_add(e, term);
			}
		ex = mk_add(tcpy(expo), mk_int(k));
		r = mk_add(r, mk_mul(e, mk_pow(tcpy(lin), ex)));
		}
	for (j = 0; j <= deg; j++) delete(p[j]);
	delete(lc[0]); delete(lc[1]);
	return r;
}

static Node * s_polyquotient (Node * a[], int n, Symbol * f)
{
	return polydiv(a, n, 0);
}

static Node * s_polyremainder (Node * a[], int n, Symbol * f)
{
	return polydiv(a, n, 1);
}

/* ================= polynomial normal form and derivative ================= */

static Node * mk_f1 (const char * f, Node * a)
{
	return mknod(Func, (Node *) getsymbol(fsym(f), a), a);
}

static Node * mk_neg (Node * a)
{
	return mk_mul(mk_int(-1), a);
}

/* every sum that is a polynomial in x becomes c0 + c1*x + c2*x^2 + ...
 * with collected coefficients (Mathematica's canonical form) */
static Node * normpoly (Node * u, Node * x);

static Node * normpoly_args (Node * r, Node * x)
{
	if (r && r->type == Terms)
		return mknod(Terms, normpoly(r->l, x), normpoly_args(r->r, x));
	return normpoly(r, x);
}

static Node * normpoly (Node * u, Node * x)
{
	Node * c[MAXDEG];
	int deg;
	u = deref(u);
	if (! u) return NULL;
	if ((is_head(u, "+", 2) || is_head(u, "-", 2)) && contains(u, x)
	    && poly_coeffs(u, x, c, & deg))
		{
		if (deg >= 1) return poly_build(c, deg, x);
		while (deg >= 0) delete(c[deg--]);
		}
	if (u->type == Func && ! num_sym(u))
		return mknod(Func, u->l, normpoly_args(u->r, x));
	return tcpy(u);
}

static void summands_to (Node * t, TList * out, int neg);

/* numeric content of a polynomial: gcd of the numeric factors of all its
 * monomials (as fractions); 1 if there is none */
static double poly_content (Node * c[], int deg)
{
	double g = 0, gq = 1, p, q, d;
	int k, i;
	for (k = 0; k <= deg; k++)
		{
		TList l = {0};
		summands_to(c[k], & l, 0);
		for (i = 0; i < l.n; i++)
			{
			Mono m = { 1.0, NULL, 0, 0, 1 };
			mono_flatten(l.t[i], & m);
			free(m.f);
			if (m.c == 0) continue;
			if (! rat_approx(m.c, & p, & q)) { tl_free(& l); return 1; }
			g = gcd2(g * q, p * gq);	/* gcd(g/gq, p/q) */
			gq = gq * q;
			d = gcd2(g, gq);
			if (d > 0) { g /= d; gq /= d; }
			}
		tl_free(& l);
		}
	return (g > 0) ? g / gq : 1;
}

static Node * scale_collect (Node * u, double s)	/* s*u, like terms collected */
{
	TList l = {0}, out = {0};
	int i;
	summands_to(u, & l, 0);
	for (i = 0; i < l.n; i++)
		tl_add(& out, mk_mul(mk_int(s), tcpy(l.t[i])));
	tl_free(& l);
	return tl_collect(& out);
}

/* a polynomial factor of the integrand: normal form with the numeric
 * content in front, 140*a + 70*b*x -> 70*(2*a + b*x). Without this, a rule
 * that only rescales the integrand would make the coefficients grow forever. */
static Node * normpoly_factor (Node * u, Node * x)
{
	Node * c[MAXDEG];
	int deg, k;
	double g;
	u = deref(u);
	if ((is_head(u, "+", 2) || is_head(u, "-", 2)) && contains(u, x)
	    && poly_coeffs(u, x, c, & deg))
		{
		if (deg < 1)
			while (deg >= 0) delete(c[deg--]);
		else
			{
			g = poly_content(c, deg);
			if (g == 1 || ! isfinite(g)) return poly_build(c, deg, x);
			for (k = 0; k <= deg; k++)
				{
				Node * t = scale_collect(c[k], 1.0 / g);
				delete(c[k]);
				c[k] = t;
				}
			return mk_mul(mk_int(g), poly_build(c, deg, x));
			}
		}
	return normpoly(u, x);
}

static Node * s_normpoly (Node * a[], int n, Symbol * f)
{
	TList l = {0};
	Node * r = NULL;
	int i;
	if (n != 2) return NULL;
	if (! is_head(a[0], "*", 2)) return normpoly(a[0], a[1]);
	factors_to(a[0], & l);
	for (i = 0; i < l.n; i++)
		{
		Node * t = normpoly_factor(l.t[i], a[1]);
		r = r ? mk_mul(r, t) : t;
		}
	l.n = 0;	/* the factors belong to a[0] */
	tl_free(& l);
	return r;
}

/* derivative of u with respect to x, or NULL for unknown functions */
static Node * deriv (Node * u, Node * x)
{
	Node * a, * b, * da, * db;
	u = deref(u);
	if (! u) return NULL;
	if (! contains(u, x)) return mk_int(0);
	if (tequal(u, x)) return mk_int(1);
	if (u->type != Func) return NULL;
	if (term_nargs(u) == 2)
		{
		a = arg(u, 0); b = arg(u, 1);
		if (is_head(u, "^", 2) && ! contains(b, x))		/* b a^(b-1) a' */
			{
			if (! (da = deriv(a, x))) return NULL;
			return mk_mul(mk_mul(tcpy(b), mk_pow(tcpy(a), mk_add(tcpy(b), mk_int(-1)))), da);
			}
		if (is_head(u, "^", 2))		/* u (b' ln a + b a'/a) */
			{
			if (! (da = deriv(a, x))) return NULL;
			if (! (db = deriv(b, x))) { delete(da); return NULL; }
			return mk_mul(tcpy(u), mk_add(mk_mul(db, mk_f1("ln", tcpy(a))),
				mk_mul(mk_mul(tcpy(b), da), mk_pow(tcpy(a), mk_int(-1)))));
			}
		if (! (da = deriv(a, x))) return NULL;
		if (! (db = deriv(b, x))) { delete(da); return NULL; }
		if (is_head(u, "+", 2)) return mk_add(da, db);
		if (is_head(u, "-", 2)) return mk_add(da, mk_neg(db));
		if (is_head(u, "*", 2)) return mk_add(mk_mul(da, tcpy(b)), mk_mul(tcpy(a), db));
		if (is_head(u, "/", 2))
			return mk_mul(mk_add(mk_mul(da, tcpy(b)), mk_neg(mk_mul(tcpy(a), db))),
			              mk_pow(tcpy(b), mk_int(-2)));
		delete(da); delete(db);
		return NULL;
		}
	if (term_nargs(u) != 1) return NULL;
	a = arg(u, 0);
	if (! (da = deriv(a, x))) return NULL;
	{
	const char * h = name(TERM_HEAD(u));
	Node * g = NULL;		/* outer derivative at a */
	#define A tcpy(a)
	#define SQ(t) mk_pow(t, mk_int(2))
	if (! strcmp(h, "-")) g = mk_int(-1);
	else if (! strcmp(h, "sin")) g = mk_f1("cos", A);
	else if (! strcmp(h, "cos")) g = mk_neg(mk_f1("sin", A));
	else if (! strcmp(h, "tan")) g = mk_pow(mk_f1("cos", A), mk_int(-2));
	else if (! strcmp(h, "cot")) g = mk_neg(mk_pow(mk_f1("sin", A), mk_int(-2)));
	else if (! strcmp(h, "sec")) g = mk_mul(mk_f1("sec", A), mk_f1("tan", A));
	else if (! strcmp(h, "csc")) g = mk_neg(mk_mul(mk_f1("csc", A), mk_f1("cot", A)));
	else if (! strcmp(h, "exp")) g = mk_f1("exp", A);
	else if (! strcmp(h, "ln")) g = mk_pow(A, mk_int(-1));
	else if (! strcmp(h, "sqrt")) g = mk_mul(mk_int(0.5), mk_pow(A, mk_int(-0.5)));
	else if (! strcmp(h, "mi")) g = mk_neg(mk_pow(A, mk_int(-2)));
	else if (! strcmp(h, "arcsin")) g = mk_pow(mk_add(mk_int(1), mk_neg(SQ(A))), mk_int(-0.5));
	else if (! strcmp(h, "arccos")) g = mk_neg(mk_pow(mk_add(mk_int(1), mk_neg(SQ(A))), mk_int(-0.5)));
	else if (! strcmp(h, "arctan")) g = mk_pow(mk_add(mk_int(1), SQ(A)), mk_int(-1));
	else if (! strcmp(h, "arccot")) g = mk_neg(mk_pow(mk_add(mk_int(1), SQ(A)), mk_int(-1)));
	else if (! strcmp(h, "sinh")) g = mk_f1("cosh", A);
	else if (! strcmp(h, "cosh")) g = mk_f1("sinh", A);
	else if (! strcmp(h, "tanh")) g = mk_pow(mk_f1("cosh", A), mk_int(-2));
	else if (! strcmp(h, "coth")) g = mk_neg(mk_pow(mk_f1("sinh", A), mk_int(-2)));
	else if (! strcmp(h, "sech")) g = mk_neg(mk_mul(mk_f1("sech", A), mk_f1("tanh", A)));
	else if (! strcmp(h, "csch")) g = mk_neg(mk_mul(mk_f1("csch", A), mk_f1("coth", A)));
	else if (! strcmp(h, "arcsinh")) g = mk_pow(mk_add(mk_int(1), SQ(A)), mk_int(-0.5));
	else if (! strcmp(h, "arccosh")) g = mk_pow(mk_add(SQ(A), mk_int(-1)), mk_int(-0.5));
	else if (! strcmp(h, "arctanh") || ! strcmp(h, "arccoth"))
		g = mk_pow(mk_add(mk_int(1), mk_neg(SQ(A))), mk_int(-1));
	/* 2026: special functions (inc/alg) */
	else if (! strcmp(h, "erf") || ! strcmp(h, "erfc") || ! strcmp(h, "erfi"))
		{
		Node * ex = mk_pow(A, mk_int(2));
		if (strcmp(h, "erfi")) ex = mk_neg(ex);
		g = mk_mul(mk_num(2.0 / sqrt(M_PI)), mk_f1("exp", ex));
		if (! strcmp(h, "erfc")) g = mk_neg(g);
		}
	else if (! strcmp(h, "fresnels")) g = mk_f1("sin", mk_mul(mk_num(M_PI / 2), SQ(A)));
	else if (! strcmp(h, "fresnelc")) g = mk_f1("cos", mk_mul(mk_num(M_PI / 2), SQ(A)));
	else if (! strcmp(h, "sinint")) g = mk_mul(mk_f1("sin", A), mk_pow(A, mk_int(-1)));
	else if (! strcmp(h, "cosint")) g = mk_mul(mk_f1("cos", A), mk_pow(A, mk_int(-1)));
	else if (! strcmp(h, "sinhint")) g = mk_mul(mk_f1("sinh", A), mk_pow(A, mk_int(-1)));
	else if (! strcmp(h, "coshint")) g = mk_mul(mk_f1("cosh", A), mk_pow(A, mk_int(-1)));
	else if (! strcmp(h, "expint")) g = mk_mul(mk_f1("exp", A), mk_pow(A, mk_int(-1)));
	else if (! strcmp(h, "logint")) g = mk_pow(mk_f1("ln", A), mk_int(-1));
	else if (! strcmp(h, "arcsec") || ! strcmp(h, "arccsc"))
		{
		g = mk_pow(mk_mul(SQ(A), mk_pow(mk_add(mk_int(1), mk_neg(mk_pow(A, mk_int(-2)))), mk_num_ex(0.5, 1))), mk_int(-1));
		if (! strcmp(h, "arccsc")) g = mk_neg(g);
		}
	else if (! strcmp(h, "arcsech"))
		g = mk_neg(mk_pow(mk_mul(A, mk_pow(mk_add(mk_int(1), mk_neg(SQ(A))), mk_num_ex(0.5, 1))), mk_int(-1)));
	else if (! strcmp(h, "arccsch"))
		g = mk_neg(mk_pow(mk_mul(SQ(A), mk_pow(mk_add(mk_int(1), mk_pow(A, mk_int(-2))), mk_num_ex(0.5, 1))), mk_int(-1)));
	#undef A
	#undef SQ
	if (! g) { delete(da); return NULL; }
	return mk_mul(g, da);
	}
}

static Node * s_deriv (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return deriv(a[0], a[1]);
}

/* collect(u): like summands of u combined (no multiplying out) */
static void summands_to (Node * t, TList * out, int neg)
{
	t = deref(t);
	if (is_head(t, "+", 2))
		{
		summands_to(arg(t, 0), out, neg);
		summands_to(arg(t, 1), out, neg);
		}
	else if (is_head(t, "-", 2))
		{
		summands_to(arg(t, 0), out, neg);
		summands_to(arg(t, 1), out, ! neg);
		}
	else
		tl_add(out, neg ? mk_neg(tcpy(t)) : tcpy(t));
}

static Node * s_collect (Node * a[], int n, Symbol * f)
{
	TList l = {0};
	if (n != 1) return NULL;
	summands_to(a[0], & l, 0);
	return tl_collect(& l);
}

/* ================= more Rubi helpers (2026) ================= */

static int is_free (Node * u, Node * x) { return ! contains(u, x); }

static Node * s_replaceall (Node * a[], int n, Symbol * f)	/* u with x -> v */
{
	if (n != 3) return NULL;
	return replace(a[0], a[1], a[2]);
}

/* ---- BinomialParts: u = a + b x^n (Rubi's definition) ---- */
static int bparts (Node * u, Node * x, Node ** pa, Node ** pb, Node ** pn)
{
	Node * c[MAXDEG], * a1, * b1, * n1, * a2, * b2, * n2;
	int deg, k, nz;
	u = deref(u);
	if (! u) return 0;
	if (contains(u, x) && poly_coeffs(u, x, c, & deg))	/* polynomial */
		{
		for (nz = 0, k = 1; k < deg; k++) if (! is_zero(c[k])) nz++;
		if (deg > 0 && nz == 0)
			{
			* pa = c[0]; * pb = c[deg]; * pn = mk_int(deg);
			for (k = 1; k < deg; k++) delete(c[k]);
			return 1;
			}
		for (k = 0; k <= deg; k++) delete(c[k]);
		return 0;
		}
	if (is_head(u, "^", 2) && tequal(arg(u, 0), x) && is_free(arg(u, 1), x))
		{
		* pa = mk_int(0); * pb = mk_int(1); * pn = tcpy(arg(u, 1));
		return 1;
		}
	if (is_head(u, "-", 1))
		{
		if (! bparts(arg(u, 0), x, & a1, & b1, & n1)) return 0;
		* pa = mk_neg(a1); * pb = mk_neg(b1); * pn = n1;
		return 1;
		}
	if (is_head(u, "*", 2))
		{
		Node * p = arg(u, 0), * q = arg(u, 1);
		int ok = 1;
		Node * sum;
		if (is_free(p, x))
			{
			if (! bparts(q, x, & a2, & b2, & n2)) return 0;
			* pa = mk_mul(tcpy(p), a2); * pb = mk_mul(tcpy(p), b2); * pn = n2;
			return 1;
			}
		if (is_free(q, x))
			{
			if (! bparts(p, x, & a1, & b1, & n1)) return 0;
			* pa = mk_mul(tcpy(q), a1); * pb = mk_mul(tcpy(q), b1); * pn = n1;
			return 1;
			}
		if (! bparts(p, x, & a1, & b1, & n1)) return 0;
		if (! bparts(q, x, & a2, & b2, & n2)) { delete(a1); delete(b1); delete(n1); return 0; }
		sum = mk_add(tcpy(n1), tcpy(n2));
		if (is_zero(a1) && is_zero(a2))
			{ * pa = mk_int(0); * pb = mk_mul(tcpy(b1), tcpy(b2)); * pn = mk_add(tcpy(n1), tcpy(n2)); }
		else if (is_zero(a1) && is_zero(sum))
			{ * pa = mk_mul(tcpy(b1), tcpy(b2)); * pb = mk_mul(tcpy(b1), tcpy(a2)); * pn = tcpy(n1); }
		else if (is_zero(a2) && is_zero(sum))
			{ * pa = mk_mul(tcpy(b1), tcpy(b2)); * pb = mk_mul(tcpy(a1), tcpy(b2)); * pn = tcpy(n2); }
		else
			{
			Node * cross = mk_add(mk_mul(tcpy(a1), tcpy(b2)), mk_mul(tcpy(b1), tcpy(a2)));
			if (eq_terms(n1, n2) && is_zero(cross))
				{ * pa = mk_mul(tcpy(a1), tcpy(a2)); * pb = mk_mul(tcpy(b1), tcpy(b2)); * pn = mk_mul(mk_int(2), tcpy(n1)); }
			else ok = 0;
			delete(cross);
			}
		delete(sum);
		delete(a1); delete(b1); delete(n1); delete(a2); delete(b2); delete(n2);
		return ok;
		}
	if (is_head(u, "+", 2) || is_head(u, "-", 2))
		{
		Node * p = arg(u, 0), * q = arg(u, 1);
		int minus = is_head(u, "-", 2);
		if (is_free(p, x))
			{
			if (! bparts(q, x, & a2, & b2, & n2)) return 0;
			if (minus) { a2 = mk_neg(a2); b2 = mk_neg(b2); }
			* pa = mk_add(tcpy(p), a2); * pb = b2; * pn = n2;
			return 1;
			}
		if (is_free(q, x))
			{
			if (! bparts(p, x, & a1, & b1, & n1)) return 0;
			* pa = mk_add(minus ? mk_neg(tcpy(q)) : tcpy(q), a1); * pb = b1; * pn = n1;
			return 1;
			}
		if (! bparts(p, x, & a1, & b1, & n1)) return 0;
		if (! bparts(q, x, & a2, & b2, & n2)) { delete(a1); delete(b1); delete(n1); return 0; }
		if (minus) { a2 = mk_neg(a2); b2 = mk_neg(b2); }
		if (! eq_terms(n1, n2))
			{
			delete(a1); delete(b1); delete(n1); delete(a2); delete(b2); delete(n2);
			return 0;
			}
		* pa = mk_add(a1, a2); * pb = mk_add(b1, b2); * pn = n1;
		delete(n2);
		return 1;
		}
	return 0;
}

static Node * s_binomialq (Node * a[], int n, Symbol * f)	/* binomialq(u,x[,n]) */
{
	Node * pa, * pb, * pn;
	int ok;
	if (n != 2 && n != 3) return NULL;
	ok = bparts(a[0], a[1], & pa, & pb, & pn);
	if (ok)
		{
		if (n == 3) ok = eq_terms(pn, a[2]);
		delete(pa); delete(pb); delete(pn);
		}
	return mk_bool(ok, f);
}

static Node * s_binomialdegree (Node * a[], int n, Symbol * f)
{
	Node * pa, * pb, * pn;
	if (n != 2 || ! bparts(a[0], a[1], & pa, & pb, & pn)) return NULL;
	delete(pa); delete(pb);
	return pn;
}

static Node * s_quadraticq (Node * a[], int n, Symbol * f)	/* degree 2, not just c x^2 */
{
	Node * c[MAXDEG];
	int deg, ok, k;
	if (n != 2) return NULL;
	if (! poly_coeffs(a[0], a[1], c, & deg)) return mk_bool(0, f);
	ok = (deg == 2) && ! (is_zero(c[0]) && is_zero(c[1]));
	for (k = 0; k <= deg; k++) delete(c[k]);
	return mk_bool(ok, f);
}

static int ratfunq (Node * u, Node * x)
{
	double e;
	u = deref(u);
	if (! u || u->type != Func || is_free(u, x)) return 1;
	if (is_head(u, "^", 2)) return num_value(arg(u, 1), & e) && e == floor(e) && ratfunq(arg(u, 0), x);
	if (is_head(u, "+", 2) || is_head(u, "-", 2) || is_head(u, "*", 2) || is_head(u, "/", 2))
		return ratfunq(arg(u, 0), x) && ratfunq(arg(u, 1), x);
	if (is_head(u, "-", 1) || is_head(u, "mi", 1)) return ratfunq(arg(u, 0), x);
	return 0;
}

static Node * s_rationalfunctionq (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_bool(ratfunq(a[0], a[1]), f);
}

static int invfunfreeq (Node * u, Node * x)
{
	static const char * inv[] = { "ln", "arcsin", "arccos", "arctan", "arccot", "arcsec",
		"arccsc", "arcsinh", "arccosh", "arctanh", "arccoth", "arcsech", "arccsch",
		"polylog", "Int", "D", "deriv", "subst", "hyp2f1", "appellf1", NULL };
	int i, k, n;
	u = deref(u);
	if (! u || u->type != Func) return 1;
	for (i = 0; inv[i]; i++)
		if (is_head(u, inv[i], -1)) return is_free(u, x);
	n = term_nargs(u);
	for (k = 0; k < n; k++)
		if (! invfunfreeq(arg(u, k), x)) return 0;
	return 1;
}

static Node * s_inversefunctionfreeq (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_bool(invfunfreeq(a[0], a[1]), f);
}

/* ---- LeafCount (sums and products counted flat, as in Mathematica) ---- */
static int leafcount (Node * u)
{
	double v, p, q;
	int k, n, c;
	const char * h;
	u = deref(u);
	if (! u) return 0;
	if (is_num(u, & v))
		return (v != floor(v) && rat_approx(v, & p, & q)) ? 3 : 1;
	if (u->type != Func) return 1;
	h = name(TERM_HEAD(u));
	n = term_nargs(u);
	c = 1;
	for (k = 0; k < n; k++)
		{
		Node * t = arg(u, k);
		/* nested + or * of the same kind: no extra head */
		if ((! strcmp(h, "+") || ! strcmp(h, "*")) && is_head(t, h, 2)) c += leafcount(t) - 1;
		else c += leafcount(t);
		}
	return c;
}

static Node * s_leafcount (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return mk_int(leafcount(a[0]));
}

/* ---- SimplerQ, SumSimplerQ, SimplerSqrtQ ---- */
static int is_integer_num (Node * u, double * v) { return num_value(u, v) && * v == floor(* v); }
static int is_atomic (Node * u) { u = deref(u); return u && u->type != Func; }

static int simplerq (Node * u, Node * v)
{
	double a, b, p1, q1, p2, q2;
	int iu = is_integer_num(u, & a), iv = is_integer_num(v, & b);
	if (iu) return iv ? (a == b ? 0 : (a == -b ? b < 0 : fabs(a) < fabs(b))) : 1;
	if (iv) return 0;
	if (num_value(u, & a) && rat_approx(a, & p1, & q1))
		{
		if (num_value(v, & b) && rat_approx(b, & p2, & q2))
			{
			if (q1 == q2) return (p1 == p2) ? 0 : (p1 == -p2 ? p2 < 0 : fabs(p1) < fabs(p2));
			return q1 < q2;
			}
		return 1;
		}
	if (num_value(v, & b)) return 0;
	if (is_atomic(u)) return is_atomic(v) ? tcmp(u, v) < 0 : 1;
	if (is_atomic(v)) return 0;
	{
	int lu = leafcount(u), lv = leafcount(v);
	if (lu != lv) return lu < lv;
	return tcmp(u, v) < 0;
	}
}

static Node * s_simplerq (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_bool(simplerq(a[0], a[1]), f);
}

static int sum_aux (Node * u, Node * v)
{
	double a, b;
	u = deref(u); v = deref(v);
	if (is_head(v, "+", 2))
		return (num_value(arg(v, 0), & a) || sum_aux(u, arg(v, 0)))
		    && (num_value(arg(v, 1), & b) || sum_aux(u, arg(v, 1)));
	if (is_head(u, "+", 2))
		return sum_aux(arg(u, 0), v) || sum_aux(arg(u, 1), v);
	if (is_zero(v)) return 0;
	{
	Mono mu = { 1.0, NULL, 0, 0, 1 }, mv = { 1.0, NULL, 0, 0, 1 };
	int r;
	mono_flatten(u, & mu); mono_normalize(& mu);
	mono_flatten(v, & mv); mono_normalize(& mv);
	r = mono_like(& mu, & mv) && mv.c != 0
	    && (mu.c / mv.c < -0.5 || (mu.c / mv.c == -0.5 && mu.c < 0));
	free(mu.f); free(mv.f);
	return r;
	}
}

static Node * s_sumsimplerq (Node * a[], int n, Symbol * f)
{
	double u, v;
	TList lu = {0}, lv = {0};
	Node * eu, * ev;
	int r;
	if (n != 2) return NULL;
	if (num_value(a[0], & u) && num_value(a[1], & v))
		return mk_bool(v == 0 ? 0 : (v > 0 ? u < -1 : u >= -v), f);
	expand_to(a[0], & lu); eu = tl_collect(& lu);
	expand_to(a[1], & lv); ev = tl_collect(& lv);
	r = sum_aux(eu, ev);
	delete(eu); delete(ev);
	return mk_bool(r, f);
}

static Node * s_simplersqrtq (Node * a[], int n, Symbol * f)
{
	double u, v, su, sv;
	Node * ra[2], * qu, * qv;
	int lu, lv, r, iu, iv, nu, nv;
	if (n != 2) return NULL;
	if (num_value(a[1], & v) && v < 0 && ! (num_value(a[0], & u) && u < 0)) return mk_bool(1, f);
	if (num_value(a[0], & u) && u < 0 && ! (num_value(a[1], & v) && v < 0)) return mk_bool(0, f);
	ra[1] = mk_int(2);
	ra[0] = a[0]; qu = s_rt(ra, 2, f);
	ra[0] = a[1]; qv = s_rt(ra, 2, f);
	delete(ra[1]);
	if (! qu || ! qv) { delete(qu); delete(qv); return mk_bool(0, f); }
	iu = is_integer_num(qu, & su); iv = is_integer_num(qv, & sv);
	nu = is_exact(qu); nv = is_exact(qv);
	if (iu) r = iv ? su < sv : 1;
	else if (iv) r = 0;
	else if (nu) { num_value(qu, & su); r = nv ? (num_value(qv, & sv), su < sv) : 1; }
	else if (nv) r = 0;
	else if (posaux(a[0])) r = posaux(a[1]) ? leafcount(qu) < leafcount(qv) : 1;
	else if (posaux(a[1])) r = 0;
	else
		{
		lu = leafcount(qu); lv = leafcount(qv);
		r = (lu != lv) ? lu < lv : tcmp(a[1], a[0]) > 0;
		}
	delete(qu); delete(qv);
	return mk_bool(r, f);
}

/* ---- KnownSineIntegrandQ and friends ----
 * u is 1, or (a+b g)^m, or (a+b g)^m (A+B g), or (A+B g+C g^2), or
 * (a+b g)^m (A+B g+C g^2), with g = func(e+f x), func from the list. */
static Node * trig_kernel (Node * u, Node * x, const char ** funcs)	/* first func(e+f x) in u */
{
	int k, n, i;
	Node * r;
	u = deref(u);
	if (! u || u->type != Func) return NULL;
	for (i = 0; funcs[i]; i++)
		if (is_head(u, funcs[i], 1))
			{
			double deg;
			if (poly_info(arg(u, 0), x, & deg, -1, NULL) && deg == 1) return u;
			return NULL;
			}
	n = term_nargs(u);
	for (k = 0; k < n; k++)
		if ((r = trig_kernel(arg(u, k), x, funcs)) != NULL) return r;
	return NULL;
}

static int poly_in_g (Node * u, Node * g, Node * x, int maxdeg)	/* coefficients free of x */
{
	Node * c[MAXDEG];
	int deg, k, ok = 1;
	if (! poly_coeffs(u, g, c, & deg)) return 0;
	if (deg > maxdeg) ok = 0;
	for (k = 0; k <= deg; k++) { if (contains(c[k], x)) ok = 0; delete(c[k]); }
	return ok;
}

static int known_trig (Node * u, Node * x, const char ** funcs)
{
	TList l = {0};
	Node * g;
	int i, lin = 0, quad = 0, ok = 1;
	double v;
	if (num_value(u, & v) && v == 1) return 1;
	if (! (g = trig_kernel(u, x, funcs))) return 0;
	factors_to(u, & l);
	for (i = 0; i < l.n && ok; i++)
		{
		Node * t = l.t[i], * base = t, * m = NULL;
		if (is_head(t, "^", 2)) { base = arg(t, 0); m = arg(t, 1); }
		if (m && contains(m, x)) { ok = 0; break; }
		if (! contains(base, x)) continue;		/* constant factor */
		if (poly_in_g(base, g, x, 1)) lin++;
		else if (! m && poly_in_g(base, g, x, 2)) quad++;
		else ok = 0;
		}
	l.n = 0;
	tl_free(& l);
	return ok && quad <= 1 && (lin + quad) <= 2;
}

static const char * fn_sine[] = { "sin", "cos", NULL };
static const char * fn_tan[] = { "tan", NULL };
static const char * fn_cot[] = { "cot", NULL };
static const char * fn_sec[] = { "sec", "csc", NULL };

#define KNOWN(name, list) \
static Node * name (Node * a[], int n, Symbol * f) \
{ if (n != 2) return NULL; return mk_bool(known_trig(a[0], a[1], list), f); }
KNOWN(s_knownsine, fn_sine)
KNOWN(s_knowntangent, fn_tan)
KNOWN(s_knowncotangent, fn_cot)
KNOWN(s_knownsecant, fn_sec)

/* ---- PiecewiseLinearQ, LinearMatchQ ---- */
static int linq (Node * u, Node * x)
{
	double deg;
	return poly_info(u, x, & deg, -1, NULL) && deg == 1;
}

static int pwlinq (Node * u, Node * x)
{
	static const char * pairs[][2] = { {"arctanh","tanh"}, {"arctanh","coth"}, {"arccoth","coth"},
		{"arccoth","tanh"}, {"arctan","tan"}, {"arctan","cot"}, {"arccot","cot"}, {"arccot","tan"} };
	int i;
	u = deref(u);
	if (linq(u, x)) return 1;
	if (is_head(u, "ln", 1))
		{
		Node * w = arg(u, 0), * p = w;
		if (is_head(w, "*", 2))
			{
			if (! contains(arg(w, 0), x)) p = arg(w, 1);
			else if (! contains(arg(w, 1), x)) p = arg(w, 0);
			}
		if (is_head(p, "^", 2) && ! contains(arg(p, 0), x) && linq(arg(p, 1), x)) return 1;
		if (is_head(p, "exp", 1) && linq(arg(p, 0), x)) return 1;
		return 0;
		}
	for (i = 0; i < 8; i++)
		if (is_head(u, pairs[i][0], 1) && is_head(arg(u, 0), pairs[i][1], 1)
		    && linq(arg(arg(u, 0), 0), x)) return 1;
	return 0;
}

static Node * s_piecewiselinearq (Node * a[], int n, Symbol * f)
{
	if (n == 2) return mk_bool(pwlinq(a[0], a[1]), f);
	if (n == 3) return mk_bool(pwlinq(a[0], a[2]) && pwlinq(a[1], a[2]), f);
	return NULL;
}

static Node * s_linearmatchq (Node * a[], int n, Symbol * f)	/* u is x, b*x, a+b*x literally */
{
	Node * u, * x;
	if (n != 2) return NULL;
	u = deref(a[0]); x = a[1];
	if (tequal(u, x)) return mk_bool(1, f);
	if (is_head(u, "*", 2) && tequal(arg(u, 1), x) && ! contains(arg(u, 0), x)) return mk_bool(1, f);
	if (is_head(u, "+", 2) && ! contains(arg(u, 0), x))
		{
		Node * t = deref(arg(u, 1));
		if (tequal(t, x) || (is_head(t, "*", 2) && tequal(arg(t, 1), x) && ! contains(arg(t, 0), x)))
			return mk_bool(1, f);
		}
	return mk_bool(0, f);
}

/* ---- ExpandTrigReduce: products and powers of sin, cos (sinh, cosh) to
 * sums of single functions of multiple angles ---- */
typedef struct { int hyp; int kind; Node * arg; } TrigF;	/* kind 0: sin(h), 1: cos(h) */

static Node * lin_sum (Node * a, Node * b, int sign)		/* a + sign*b, collected */
{
	TList l = {0};
	Node * s = mk_add(tcpy(a), sign > 0 ? tcpy(b) : mk_neg(tcpy(b)));
	expand_to(s, & l);
	delete(s);
	return tl_collect(& l);
}

static Node * mk_trig (int hyp, int kind, Node * arg)		/* takes arg */
{
	return mk_f1(hyp ? (kind ? "cosh" : "sinh") : (kind ? "cos" : "sin"), arg);
}

/* coef * prod(trig factors) as a sum of single functions (appended to out);
 * takes coef */
static void trig_reduce_term (Node * coef, TrigF * tf, int nt, TList * out)
{
	TrigF a, b;
	Node * s, * d;
	int i, k[2];
	double sg[2];
	if (nt <= 1)
		{
		Node * t = coef;
		if (nt == 1) t = mk_mul(t, mk_trig(tf[0].hyp, tf[0].kind, tcpy(tf[0].arg)));
		tl_add(out, t);
		return;
		}
	a = tf[nt - 2]; b = tf[nt - 1];
	if (a.hyp != b.hyp)		/* trig times hyperbolic: keep the last one */
		{
		Node * t = mk_mul(coef, mk_trig(b.hyp, b.kind, tcpy(b.arg)));
		trig_reduce_term(t, tf, nt - 1, out);
		return;
		}
	s = lin_sum(a.arg, b.arg, 1);		/* a + b */
	d = lin_sum(a.arg, b.arg, -1);		/* a - b */
	{
	int negd = ! posaux(d);			/* sin(-u) = -sin(u), cos(-u) = cos(u) */
	if (negd) { delete(d); d = lin_sum(b.arg, a.arg, -1); }
	/* term 0 has argument d, term 1 argument s:
	   sin a sin b = (cos d - cos s)/2      sinh a sinh b = (cosh s - cosh d)/2
	   cos a cos b = (cos d + cos s)/2      cosh a cosh b = (cosh d + cosh s)/2
	   sin a cos b = (sin d + sin s)/2      sinh a cosh b = (sinh d + sinh s)/2
	   cos a sin b = (-sin d + sin s)/2     cosh a sinh b = (-sinh d + sinh s)/2 */
	if (a.kind == 0 && b.kind == 0) { k[0] = k[1] = 1; sg[0] = a.hyp ? -1 : 1; sg[1] = a.hyp ? 1 : -1; }
	else if (a.kind == 1 && b.kind == 1) { k[0] = k[1] = 1; sg[0] = sg[1] = 1; }
	else if (a.kind == 0) { k[0] = k[1] = 0; sg[0] = sg[1] = 1; }
	else { k[0] = k[1] = 0; sg[0] = -1; sg[1] = 1; }
	if (negd && k[0] == 0) sg[0] = -sg[0];	/* odd function of the negated argument */
	}
	for (i = 0; i < 2; i++)
		{
		TrigF nf[64];
		Node * arg = (i == 0) ? d : s;
		Node * c = mk_mul(mk_num_ex(sg[i] / 2, 1), tcpy(coef));
		double v;
		memcpy(nf, tf, (nt - 2) * sizeof(TrigF));
		if (num_value(arg, & v) && v == 0)		/* sin(0) = 0, cos(0) = 1 */
			{
			if (k[i] == 0) { delete(c); continue; }
			trig_reduce_term(c, nf, nt - 2, out);
			}
		else
			{
			nf[nt - 2].hyp = a.hyp; nf[nt - 2].kind = k[i]; nf[nt - 2].arg = arg;
			trig_reduce_term(c, nf, nt - 1, out);
			}
		}
	delete(s); delete(d); delete(coef);
}

static Node * expand_trig_reduce (Node * v)
{
	TList l = {0}, out = {0};
	int i, j;
	expand_to(v, & l);
	for (i = 0; i < l.n; i++)
		{
		TList fl = {0};
		TrigF tf[64];
		int nt = 0;
		Node * coef = NULL;
		factors_to(l.t[i], & fl);
		for (j = 0; j < fl.n; j++)
			{
			Node * t = fl.t[j], * base = t;
			double e = 1;
			int hyp = -1, kind = 0, k;
			if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e == floor(e) && e > 0 && e < 30)
				base = arg(t, 0);
			else e = 1;
			if (is_head(base, "sin", 1)) { hyp = 0; kind = 0; }
			else if (is_head(base, "cos", 1)) { hyp = 0; kind = 1; }
			else if (is_head(base, "sinh", 1)) { hyp = 1; kind = 0; }
			else if (is_head(base, "cosh", 1)) { hyp = 1; kind = 1; }
			if (hyp >= 0 && nt + (int) e < 64)
				for (k = 0; k < (int) e; k++)
					{ tf[nt].hyp = hyp; tf[nt].kind = kind; tf[nt].arg = arg(base, 0); nt++; }
			else
				coef = coef ? mk_mul(coef, tcpy(t)) : tcpy(t);
			}
		trig_reduce_term(coef ? coef : mk_int(1), tf, nt, & out);
		fl.n = 0;
		tl_free(& fl);
		}
	tl_free(& l);
	return tl_collect(& out);
}

static Node * s_expandtrigreduce (Node * a[], int n, Symbol * f)	/* (v,x), (u,v,x) */
{
	Node * w;
	TList l = {0};
	Node * r = NULL;
	int i;
	if (n == 2) return expand_trig_reduce(a[0]);
	if (n != 3) return NULL;
	w = expand_trig_reduce(a[1]);
	summands_to(w, & l, 0);
	delete(w);
	for (i = 0; i < l.n; i++)
		r = mk_add(r, mk_mul(tcpy(a[0]), tcpy(l.t[i])));
	tl_free(& l);
	return r ? r : mk_int(0);
}

/* ---- BinomialMatchQ, QuadraticMatchQ: literal forms a + b x^n, a + b x + c x^2 ---- */

/* t is b*x^n (b, n free of x; b or n may be missing): power of x in *pn (NULL: 1) */
static int x_power_term (Node * t, Node * x, Node ** pn)
{
	t = deref(t);
	* pn = NULL;
	if (is_head(t, "*", 2))
		{
		if (! contains(arg(t, 0), x)) t = deref(arg(t, 1));
		else if (! contains(arg(t, 1), x)) t = deref(arg(t, 0));
		else return 0;
		}
	if (tequal(t, x)) return 1;
	if (is_head(t, "^", 2) && tequal(arg(t, 0), x) && ! contains(arg(t, 1), x))
		{
		* pn = arg(t, 1);
		return 1;
		}
	return 0;
}

static int binmatchq (Node * u, Node * x)
{
	Node * n;
	u = deref(u);
	if (x_power_term(u, x, & n)) return 1;
	if (is_head(u, "+", 2))
		return (! contains(arg(u, 0), x) && x_power_term(arg(u, 1), x, & n))
		    || (! contains(arg(u, 1), x) && x_power_term(arg(u, 0), x, & n));
	return 0;
}

static Node * s_binomialmatchq (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_bool(binmatchq(a[0], a[1]), f);
}

static Node * s_quadraticmatchq (Node * a[], int n, Symbol * f)
{
	TList l = {0};
	Node * pn;
	double e;
	int i, n0 = 0, n1 = 0, n2 = 0, ok = 1;
	if (n != 2) return NULL;
	summands_to(a[0], & l, 0);
	for (i = 0; i < l.n && ok; i++)
		{
		if (! contains(l.t[i], a[1])) n0++;
		else if (x_power_term(l.t[i], a[1], & pn))
			{
			if (! pn) n1++;
			else if (num_value(pn, & e) && e == 2) n2++;
			else ok = 0;
			}
		else ok = 0;
		}
	tl_free(& l);
	return mk_bool(ok && n2 == 1 && n1 <= 1 && n0 <= 1, f);
}

/* TrinomialQ: c0 + c1 x^m + c2 x^(2m), not quadratic, not w^2 with binomial w */
static Node * s_trinomialq (Node * a[], int n, Symbol * f)
{
	Node * c[MAXDEG];
	int deg, k, m, ok = 0;
	if (n != 2) return NULL;
	if (is_head(a[0], "^", 2))
		{
		double e;
		Node * pa, * pb, * pn;
		if (num_value(arg(a[0], 1), & e) && e == 2 && bparts(arg(a[0], 0), a[1], & pa, & pb, & pn))
			{
			delete(pa); delete(pb); delete(pn);
			return mk_bool(0, f);
			}
		}
	if (poly_coeffs(a[0], a[1], c, & deg))
		{
		if (deg >= 2 && deg % 2 == 0 && deg != 2)
			{
			m = deg / 2;
			ok = ! is_zero(c[m]);
			for (k = 1; k < deg && ok; k++)
				if (k != m && ! is_zero(c[k])) ok = 0;
			}
		for (k = 0; k <= deg; k++) delete(c[k]);
		}
	return mk_bool(ok, f);
}

static Node * s_linearpairq (Node * a[], int n, Symbol * f)
{
	Node * u0, * u1, * v0, * v1, * d;
	double deg;
	int ok;
	if (n != 3) return NULL;
	if (! (poly_info(a[0], a[2], & deg, -1, NULL) && deg == 1)) return mk_bool(0, f);
	if (! (poly_info(a[1], a[2], & deg, -1, NULL) && deg == 1)) return mk_bool(0, f);
	if (tequal(a[0], a[2])) return mk_bool(0, f);
	poly_info(a[0], a[2], & deg, 0, & u0); poly_info(a[0], a[2], & deg, 1, & u1);
	poly_info(a[1], a[2], & deg, 0, & v0); poly_info(a[1], a[2], & deg, 1, & v1);
	d = mk_add(mk_mul(u0, v1), mk_neg(mk_mul(u1, v0)));
	ok = is_zero(d);
	if (! ok)
		{
		TList l = {0};
		Node * e;
		expand_to(d, & l);
		e = tl_collect(& l);
		ok = is_zero(e);
		delete(e);
		}
	delete(d);
	return mk_bool(ok, f);
}

static int algfunq (Node * u, Node * x, int flag)
{
	double e;
	u = deref(u);
	if (! u || u->type != Func || ! contains(u, x)) return 1;
	if (is_head(u, "^", 2) && ((num_value(arg(u, 1), & e)) || (flag && ! contains(arg(u, 1), x))))
		return algfunq(arg(u, 0), x, flag);
	if (is_head(u, "+", 2) || is_head(u, "-", 2) || is_head(u, "*", 2) || is_head(u, "/", 2))
		return algfunq(arg(u, 0), x, flag) && algfunq(arg(u, 1), x, flag);
	if (is_head(u, "-", 1) || is_head(u, "mi", 1) || is_head(u, "sqrt", 1)) return algfunq(arg(u, 0), x, flag);
	return 0;
}

static Node * s_algebraicfunctionq (Node * a[], int n, Symbol * f)
{
	double fl = 0;
	if (n != 2 && n != 3) return NULL;
	if (n == 3) num_value(a[2], & fl);
	return mk_bool(algfunq(a[0], a[1], fl != 0), f);
}

/* ---- intsubst(u, x, v): Rubi's Subst[Int[u, x], x, v] ----
 * u is integrated in a fresh variable w, which then is replaced by v. If v
 * is known to be non-negative (a square root, an even root, exp, abs, a
 * term of sort nonneg), w is the constant Xnn of sort nonneg, so that rules
 * like sqrt(w^2) = w apply. Otherwise x itself is used (or the real
 * constant Xre, if x is Xnn: its sign is not known any more). */

static int nonnegq (Node * v)
{
	double e, p, q;
	Node * s;
	v = deref(v);
	if (! v) return 0;
	if (num_value(v, & e)) return e >= 0;
	s = arg_sort(v);
	if (s && find_symbol("nonneg") && sort_dist(s, (Node *) find_symbol("nonneg")) >= 0) return 1;
	if (is_head(v, "sqrt", 1) || is_head(v, "exp", 1) || is_head(v, "abs", 1)) return 1;
	if (is_head(v, "^", 2) && num_value(arg(v, 1), & e))
		{
		if (e == floor(e)) return fmod(e, 2.0) == 0 || nonnegq(arg(v, 0));
		if (rat_approx(e, & p, & q) && fmod(q, 2.0) == 0) return 1;	/* even root */
		return nonnegq(arg(v, 0));
		}
	if (is_head(v, "^", 2) && num_value(arg(v, 0), & e) && e > 0) return 1;	/* e^u, 2^u */
	if (is_head(v, "*", 2) || is_head(v, "+", 2) || is_head(v, "/", 2))
		return nonnegq(arg(v, 0)) && nonnegq(arg(v, 1));
	return 0;
}

static Node * mk_f3 (const char * f, Node * a, Node * b, Node * c)
{
	Node * t = mknod(Terms, a, mknod(Terms, b, c));
	return mknod(Func, (Node *) getsymbol(fsym(f), t), t);
}

static Node * s_substint (Node * a[], int n, Symbol * f)
{
	Symbol * xnn = find_symbol("Xnn"), * xre = find_symbol("Xre"), * ws = NULL;
	Node * w, * u;
	if (n != 3) return NULL;
	if (xnn && nonnegq(a[2])) ws = xnn;
	else if (xre && xnn && atom_sym(a[1]) == xnn) ws = xre;
	w = ws ? mknod(Const, (Node *) ws, NULL) : tcpy(a[1]);
	u = ws ? replace(a[0], a[1], w) : tcpy(a[0]);
	return mk_f3("subst", mk_f2("Int", u, w), tcpy(w), tcpy(a[2]));
}

/* ---- hyp2exp(u, x): hyperbolic functions of x as exponentials ----
 * Rubi integrates sinh, cosh, ... by turning them into sin, cos of an
 * imaginary argument, which needs complex numbers. Instead, the last rule
 * of the rule list writes them with e^u (sinh u = (e^u - e^-u)/2, ...) and
 * multiplies out, so that the rules for exponentials apply. */

static Node * ex_pow (Node * u, int k)		/* e^(k u) */
{
	Node * arg = (k == 1) ? tcpy(u) : mk_mul(mk_int(k), tcpy(u));
	Symbol * es = find_symbol("eE");	/* symbolic e of the integration */
	return mk_pow(es ? mknod(Const, (Node *) es, NULL) : mk_num(M_E), arg);
}

static Node * hyp2exp (Node * u, Node * x, int * changed)
{
	Node * a;
	int k, n;
	u = deref(u);
	if (! u || u->type != Func || ! contains(u, x)) return tcpy(u);
	if (term_nargs(u) == 1 && contains(arg(u, 0), x))
		{
		const char * h = name(TERM_HEAD(u));
		Node * inner = hyp2exp(arg(u, 0), x, changed), * r = NULL;
		if (! strcmp(h, "sinh"))
			r = mk_mul(mk_num_ex(0.5, 1), mk_add(ex_pow(inner, 1), mk_neg(ex_pow(inner, -1))));
		else if (! strcmp(h, "cosh"))
			r = mk_mul(mk_num_ex(0.5, 1), mk_add(ex_pow(inner, 1), ex_pow(inner, -1)));
		else if (! strcmp(h, "tanh"))
			r = mk_mul(mk_add(ex_pow(inner, 2), mk_int(-1)), mk_pow(mk_add(ex_pow(inner, 2), mk_int(1)), mk_int(-1)));
		else if (! strcmp(h, "coth"))
			r = mk_mul(mk_add(ex_pow(inner, 2), mk_int(1)), mk_pow(mk_add(ex_pow(inner, 2), mk_int(-1)), mk_int(-1)));
		else if (! strcmp(h, "sech"))
			r = mk_mul(mk_int(2), mk_pow(mk_add(ex_pow(inner, 1), ex_pow(inner, -1)), mk_int(-1)));
		else if (! strcmp(h, "csch"))
			r = mk_mul(mk_int(2), mk_pow(mk_add(ex_pow(inner, 1), mk_neg(ex_pow(inner, -1))), mk_int(-1)));
		if (r)
			{
			delete(inner);
			* changed = 1;
			return r;
			}
		a = mknod(Func, u->l, inner);		/* other function: keep */
		return a;
		}
	n = term_nargs(u);
	{
	Node * args = NULL, ** tail = & args;
	for (k = 0; k < n; k++)
		{
		Node * c = hyp2exp(arg(u, k), x, changed);
		if (k < n - 1)
			{
			* tail = mknod(Terms, c, NULL);
			tail = & (* tail)->r;
			}
		else
			* tail = c;
		}
	return mknod(Func, u->l, args);
	}
}

static Node * s_hyp2exp (Node * a[], int n, Symbol * f)
{
	int changed = 0;
	Node * r;
	TList l = {0};
	if (n != 2) return NULL;
	r = hyp2exp(a[0], a[1], & changed);
	if (! changed) return r;		/* no hyperbolic function: unchanged */
	expand_to(r, & l);			/* multiply out */
	delete(r);
	return tl_collect(& l);
}

/* ================= trivial simplification of rule results ================= */

static int num_is (Node * t, double v)
{
	double w;
	return is_num(t, & w) && w == v;
}

/* Mathematica simplifies these automatically, and Rubi's rules rely on it:
 * u^0 -> 1, u^1 -> u, 1*u -> u, u*1 -> u, 0*u -> 0, 0+u -> u, u+0 -> u.
 * Works in place on a term built by tcopy (owned nodes). */
void term_simplify_trivial (Node ** p)
{
	Node * t = * p, ** q, * a, * b, * keep;
	if (! t || t->type != Func) return;
	for (q = & t->r; * q && (* q)->type == Terms; q = & (* q)->r)
		term_simplify_trivial(& (* q)->l);
	if (* q) term_simplify_trivial(q);
	if (! t->r || t->r->type != Terms || term_nargs(t) != 2) return;
	a = t->r->l; b = t->r->r;
	keep = NULL;
	if (is_head(t, "^", 2))
		{
		if (num_is(b, 0)) { delete(t); * p = mk_int(1); return; }
		if (num_is(b, 1)) keep = a;
		}
	else if (is_head(t, "*", 2))
		{
		if (num_is(a, 0) || num_is(b, 0)) { delete(t); * p = mk_int(0); return; }
		if (num_is(a, 1)) keep = b;
		else if (num_is(b, 1)) keep = a;
		}
	else if (is_head(t, "+", 2))
		{
		if (num_is(a, 0)) keep = b;
		else if (num_is(b, 0)) keep = a;
		}
	if (! keep) return;
	delete(keep == a ? b : a);
	delnod(t->r);
	delnod(t);
	* p = keep;
}

/* ================= table and call ================= */

static struct { const char * name; s_function * fn; } symfunction[] = {
	{ "freeq",           s_freeq },
	{ "integerq",        s_integerq },
	{ "integersq",       s_integerq },
	{ "rationalq",       s_rationalq },
	{ "posq",            s_posq },
	{ "negq",            s_negq },
	{ "eqq",             s_eqq },
	{ "neq",             s_neq },
	{ "igtq",            s_igtq },
	{ "iltq",            s_iltq },
	{ "polyq",           s_polyq },
	{ "linearq",         s_linearq },
	{ "sumq",            s_sumq },
	{ "productq",        s_productq },
	{ "powerq",          s_powerq },
	{ "expand",          s_expand },
	{ "expandintegrand", s_expandintegrand },
	{ "coeff",           s_coeff },
	{ "expon",           s_expon },
	{ "subst",           s_subst },
	{ "simp",            s_simp },
	{ "simplify",        s_simp },
	{ "dist",            s_dist },
	{ "rt",              s_rt },
	{ "intpart",         s_intpart },
	{ "fracpart",        s_fracpart },
	{ "inthide",         s_inthide },
	{ "fractionq",       s_fractionq },
	{ "halfintegerq",    s_halfintegerq },
	{ "nicesqrtq",       s_nicesqrtq },
	{ "gcd",             s_gcd },
	{ "numerator",       s_numerator },
	{ "denominator",     s_denominator },
	{ "freefactors",     s_freefactors },
	{ "nonfreefactors",  s_nonfreefactors },
	{ "expandtosum",     s_expandtosum },
	{ "polyquotient",    s_polyquotient },
	{ "polyremainder",   s_polyremainder },
	{ "normpoly",        s_normpoly },
	{ "deriv",           s_deriv },
	{ "collect",         s_collect },
	{ "hyp2exp", s_hyp2exp },
	{ "intsubst", s_substint },
	{ "binomialmatchq", s_binomialmatchq },
	{ "quadraticmatchq", s_quadraticmatchq },
	{ "trinomialq", s_trinomialq },
	{ "linearpairq", s_linearpairq },
	{ "algebraicfunctionq", s_algebraicfunctionq },
	{ "replaceall", s_replaceall },
	{ "binomialq", s_binomialq },
	{ "binomialdegree", s_binomialdegree },
	{ "quadraticq", s_quadraticq },
	{ "rationalfunctionq", s_rationalfunctionq },
	{ "inversefunctionfreeq", s_inversefunctionfreeq },
	{ "leafcount", s_leafcount },
	{ "simplerq", s_simplerq },
	{ "sumsimplerq", s_sumsimplerq },
	{ "simplersqrtq", s_simplersqrtq },
	{ "piecewiselinearq", s_piecewiselinearq },
	{ "linearmatchq", s_linearmatchq },
	{ "expandtrigreduce", s_expandtrigreduce },
	{ "knownsineintegrandq", s_knownsine },
	{ "knowntangentintegrandq", s_knowntangent },
	{ "knowncotangentintegrandq", s_knowncotangent },
	{ "knownsecantintegrandq", s_knownsecant },
};

s_function * give_sfkt (const char * name)
{
	int i;
	for (i = 0; i < (int) (sizeof(symfunction) / sizeof(symfunction[0])); i++)
		if (strcmp(name, symfunction[i].name) == 0)
			return symfunction[i].fn;
	return NULL;
}

Node * call_builtin (Node * term)
{
	Symbol * f = TERM_HEAD(term);
	Node * args[MAXARGS], * a;
	int n = 0;
	Node * res;
	for (a = TERM_ARGS(term); a && n < MAXARGS; a = ARGS_NEXT(a))
		args[n++] = deref(ARGS_ITEM(a));
	res = ((s_function *) value(f))(args, n, f);
	retype_term(res);	/* function variants matching the sorts of the new arguments */
	return res;
}
