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
	if (rtypes(s) != get_numbertype()) return NULL;
	return s;
}

static int is_num (Node * t, double * v)
{
	Symbol * s = num_sym(t);
	if (! s) return 0;
	if (v) * v = * (double *) value(s);
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
	if (rtypes((Symbol *) r) != get_numbertype())
		{ delnum((Symbol *) r, TRUE); return 0; }
	* v = * (double *) value((Symbol *) r);
	delnum((Symbol *) r, TRUE);
	return 1;
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

int term_has_nan (Node * t)	/* contains a number that is NaN or infinite */
{
	double v;
	int i, n;
	t = deref(t);
	if (! t) return 0;
	if (is_num(t, & v)) return ! isfinite(v);
	if (t->type != Func) return 0;
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

/* copy of a term: new nodes, numbers cloned, other symbols shared */
static Node * tcpy (Node * t)
{
	double v;
	t = deref(t);
	if (! t) return NULL;
	if (is_num(t, & v)) return mk_num(v);
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
static Node * mk_add (Node * a, Node * b)
{
	double va, vb;
	if (! a) return b;
	if (! b) return a;
	if (is_num(a, & va) && is_num(b, & vb)) { delete(a); delete(b); return mk_num(va + vb); }
	if (is_num(a, & va) && va == 0) { delete(a); return b; }
	if (is_num(b, & vb) && vb == 0) { delete(b); return a; }
	return mk_f2("+", a, b);
}

static Node * mk_mul (Node * a, Node * b)
{
	double va, vb;
	if (is_num(a, & va) && is_num(b, & vb)) { delete(a); delete(b); return mk_num(va * vb); }
	if ((is_num(a, & va) && va == 0) || (is_num(b, & vb) && vb == 0))
		{ delete(a); delete(b); return mk_num(0); }
	if (is_num(a, & va) && va == 1) { delete(a); return b; }
	if (is_num(b, & vb) && vb == 1) { delete(b); return a; }
	return mk_f2("*", a, b);
}

static Node * mk_pow (Node * a, Node * b)
{
	double va, vb;
	if (is_num(b, & vb) && vb == 0) { delete(a); delete(b); return mk_num(1); }
	if (is_num(b, & vb) && vb == 1) { delete(b); return a; }
	if (is_num(a, & va) && is_num(b, & vb) && (va > 0 || vb == floor(vb)))
		{ delete(a); delete(b); return mk_num(pow(va, vb)); }
	return mk_f2("^", a, b);
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
			tl_add(out, mk_mul(mk_num(-1), tcpy(a.t[i])));
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
			tl_add(out, mk_mul(tcpy(a.t[i]), mk_pow(tcpy(arg(t, 1)), mk_num(-1))));
		}
	else if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e == 1)
		expand_to(arg(t, 0), out);			/* u^1 = u */
	else if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e == 0)
		tl_add(out, mk_num(1));				/* u^0 = 1 */
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
				nr.t = NULL; nr.n = nr.cap = 0;
				tl_product(& r, & a, & nr);
				tl_free(& r);
				r = nr;
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

typedef struct { Node * base; double e; } Fac;
typedef struct { double c; Fac * f; int nf, cap; } Mono;

static void mono_addfac (Mono * m, Node * base, double e)
{
	int i;
	for (i = 0; i < m->nf; i++)
		if (tequal(m->f[i].base, base)) { m->f[i].e += e; return; }
	if (m->nf == m->cap)
		{
		m->cap = m->cap ? 2 * m->cap : 4;
		m->f = (Fac *) realloc(m->f, m->cap * sizeof(Fac));
		if (! m->f) fatal("symfkt : no room");
		}
	m->f[m->nf].base = base;
	m->f[m->nf].e = e;
	m->nf++;
}

static void mono_flatten (Node * t, Mono * m)	/* t is a product */
{
	double v, e;
	t = deref(t);
	if (num_value(t, & v)) m->c *= v;
	else if (is_head(t, "*", 2)) { mono_flatten(arg(t, 0), m); mono_flatten(arg(t, 1), m); }
	else if (is_head(t, "-", 1)) { m->c = -m->c; mono_flatten(arg(t, 0), m); }
	else if (is_head(t, "^", 2) && num_value(arg(t, 1), & e)) mono_addfac(m, arg(t, 0), e);
	else mono_addfac(m, t, 1);
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
		Node * p = mk_pow(tcpy(m->f[i].base), mk_num(m->f[i].e));
		t = t ? mk_mul(t, p) : p;
		}
	if (! t) return mk_num(m->c);
	return (m->c == 1) ? t : mk_mul(mk_num(m->c), t);
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
		Mono m = { 1.0, NULL, 0, 0 };
		mono_flatten(l->t[i], & m);
		mono_normalize(& m);
		for (j = 0; j < nm; j++)
			if (mono_like(& ms[j], & m)) break;
		if (j < nm) { ms[j].c += m.c; free(m.f); }
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
	return s ? s : mk_num(0);
}


/* t = c * x^k with c free of x.  *c is a new term. */
static int monomial (Node * t, Node * x, Node ** c, double * k)
{
	Node * c1, * c2;
	double k1, k2, e;
	t = deref(t);
	if (! contains(t, x)) { * c = tcpy(t); * k = 0; return 1; }
	if (tequal(t, x)) { * c = mk_num(1); * k = 1; return 1; }
	if (is_head(t, "^", 2) && tequal(arg(t, 0), x) && num_value(arg(t, 1), & e))
		{ * c = mk_num(1); * k = e; return 1; }
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
		* c = mk_mul(mk_num(-1), c1); * k = k1;
		return 1;
		}
	if (is_head(t, "/", 2) && ! contains(arg(t, 1), x))
		{
		if (! monomial(arg(t, 0), x, & c1, & k1)) return 0;
		* c = mk_mul(c1, mk_pow(tcpy(arg(t, 1)), mk_num(-1))); * k = k1;
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
	d = mk_add(tcpy(u), mk_mul(mk_num(-1), tcpy(v)));
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
	return mk_num(deg);
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
	if (num_value(a[0], & u))
		{
		if (u < 0 && k == floor(k) && fmod(k, 2.0) != 0)
			return mk_num(-pow(-u, 1.0 / k));
		if (u >= 0)
			return mk_num(pow(u, 1.0 / k));
		}
	return mk_pow(tcpy(a[0]), mk_num(1.0 / k));
}

static Node * part (Node * u, int frac)
{
	double v;
	u = deref(u);
	if (num_value(u, & v))
		return mk_num(frac ? v - trunc(v) : trunc(v));
	if (is_head(u, "+", 2))
		return mk_add(part(arg(u, 0), frac), part(arg(u, 1), frac));
	return frac ? tcpy(u) : mk_num(0);
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
	return mk_num(gp / gq);
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
		if (! rat_approx(v, & p, & q)) return den ? mk_num(1) : mk_num(v);
		return mk_num(den ? q : p);
		}
	factors_to(u, & l);
	for (i = 0; i < l.n; i++)
		{
		Node * t = l.t[i], * part = NULL;
		if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e < 0)
			{
			if (den) part = mk_pow(tcpy(arg(t, 0)), mk_num(-e));
			}
		else if (is_head(t, "/", 2))
			part = tcpy(arg(t, den ? 1 : 0));
		else if (num_value(t, & v) && rat_approx(v, & p, & q))
			part = mk_num(den ? q : p);
		else if (! den)
			part = tcpy(t);
		if (part) r = r ? mk_mul(r, part) : part;
		}
	l.n = 0;	/* the factors belong to u */
	tl_free(& l);
	return r ? r : mk_num(1);
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
	return r ? r : mk_num(1);
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
		s = mk_add(s, k == 0 ? c[k] : mk_mul(c[k], mk_pow(tcpy(x), mk_num(k))));
		}
	return s ? s : mk_num(0);
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
	return r ? r : mk_num(0);
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
		quot[k] = mk_mul(tcpy(p[k + dq]), mk_pow(tcpy(q[dq]), mk_num(-1)));
		for (j = 0; j <= dq; j++)
			p[k + j] = mk_add(p[k + j],
				mk_mul(mk_num(-1), mk_mul(tcpy(quot[k]), tcpy(q[j]))));
		}
	for (j = 0; j <= dq; j++) delete(q[j]);
	if (want_rem)
		{
		for (k = 0; k <= dp - dq; k++) delete(quot[k]);
		if (dp < dq) return poly_build(p, dp, a[2]);
		for (k = dq; k <= dp; k++) delete(p[k]);	/* zero now */
		if (dq == 0) return mk_num(0);
		return poly_build(p, dq - 1, a[2]);
		}
	for (k = 0; k <= dp; k++) delete(p[k]);
	if (dp < dq) return mk_num(0);
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
	if (! rest) rest = mk_num(1);
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
			term = mk_mul(mk_num(binom), tcpy(p[j]));
			term = mk_mul(term, mk_pow(tcpy(lc[1]), mk_num(-j)));
			term = mk_mul(term, mk_pow(mk_mul(mk_num(-1), tcpy(lc[0])), mk_num(j - k)));
			e = mk_add(e, term);
			}
		ex = mk_add(tcpy(expo), mk_num(k));
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
	return mk_mul(mk_num(-1), a);
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

static Node * s_normpoly (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return normpoly(a[0], a[1]);
}

/* derivative of u with respect to x, or NULL for unknown functions */
static Node * deriv (Node * u, Node * x)
{
	Node * a, * b, * da, * db;
	u = deref(u);
	if (! u) return NULL;
	if (! contains(u, x)) return mk_num(0);
	if (tequal(u, x)) return mk_num(1);
	if (u->type != Func) return NULL;
	if (term_nargs(u) == 2)
		{
		a = arg(u, 0); b = arg(u, 1);
		if (is_head(u, "^", 2) && ! contains(b, x))		/* b a^(b-1) a' */
			{
			if (! (da = deriv(a, x))) return NULL;
			return mk_mul(mk_mul(tcpy(b), mk_pow(tcpy(a), mk_add(tcpy(b), mk_num(-1)))), da);
			}
		if (is_head(u, "^", 2))		/* u (b' ln a + b a'/a) */
			{
			if (! (da = deriv(a, x))) return NULL;
			if (! (db = deriv(b, x))) { delete(da); return NULL; }
			return mk_mul(tcpy(u), mk_add(mk_mul(db, mk_f1("ln", tcpy(a))),
				mk_mul(mk_mul(tcpy(b), da), mk_pow(tcpy(a), mk_num(-1)))));
			}
		if (! (da = deriv(a, x))) return NULL;
		if (! (db = deriv(b, x))) { delete(da); return NULL; }
		if (is_head(u, "+", 2)) return mk_add(da, db);
		if (is_head(u, "-", 2)) return mk_add(da, mk_neg(db));
		if (is_head(u, "*", 2)) return mk_add(mk_mul(da, tcpy(b)), mk_mul(tcpy(a), db));
		if (is_head(u, "/", 2))
			return mk_mul(mk_add(mk_mul(da, tcpy(b)), mk_neg(mk_mul(tcpy(a), db))),
			              mk_pow(tcpy(b), mk_num(-2)));
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
	#define SQ(t) mk_pow(t, mk_num(2))
	if (! strcmp(h, "-")) g = mk_num(-1);
	else if (! strcmp(h, "sin")) g = mk_f1("cos", A);
	else if (! strcmp(h, "cos")) g = mk_neg(mk_f1("sin", A));
	else if (! strcmp(h, "tan")) g = mk_pow(mk_f1("cos", A), mk_num(-2));
	else if (! strcmp(h, "cot")) g = mk_neg(mk_pow(mk_f1("sin", A), mk_num(-2)));
	else if (! strcmp(h, "sec")) g = mk_mul(mk_f1("sec", A), mk_f1("tan", A));
	else if (! strcmp(h, "csc")) g = mk_neg(mk_mul(mk_f1("csc", A), mk_f1("cot", A)));
	else if (! strcmp(h, "exp")) g = mk_f1("exp", A);
	else if (! strcmp(h, "ln")) g = mk_pow(A, mk_num(-1));
	else if (! strcmp(h, "sqrt")) g = mk_mul(mk_num(0.5), mk_pow(A, mk_num(-0.5)));
	else if (! strcmp(h, "mi")) g = mk_neg(mk_pow(A, mk_num(-2)));
	else if (! strcmp(h, "arcsin")) g = mk_pow(mk_add(mk_num(1), mk_neg(SQ(A))), mk_num(-0.5));
	else if (! strcmp(h, "arccos")) g = mk_neg(mk_pow(mk_add(mk_num(1), mk_neg(SQ(A))), mk_num(-0.5)));
	else if (! strcmp(h, "arctan")) g = mk_pow(mk_add(mk_num(1), SQ(A)), mk_num(-1));
	else if (! strcmp(h, "arccot")) g = mk_neg(mk_pow(mk_add(mk_num(1), SQ(A)), mk_num(-1)));
	else if (! strcmp(h, "sinh")) g = mk_f1("cosh", A);
	else if (! strcmp(h, "cosh")) g = mk_f1("sinh", A);
	else if (! strcmp(h, "tanh")) g = mk_pow(mk_f1("cosh", A), mk_num(-2));
	else if (! strcmp(h, "coth")) g = mk_neg(mk_pow(mk_f1("sinh", A), mk_num(-2)));
	else if (! strcmp(h, "sech")) g = mk_neg(mk_mul(mk_f1("sech", A), mk_f1("tanh", A)));
	else if (! strcmp(h, "csch")) g = mk_neg(mk_mul(mk_f1("csch", A), mk_f1("coth", A)));
	else if (! strcmp(h, "arcsinh")) g = mk_pow(mk_add(mk_num(1), SQ(A)), mk_num(-0.5));
	else if (! strcmp(h, "arccosh")) g = mk_pow(mk_add(SQ(A), mk_num(-1)), mk_num(-0.5));
	else if (! strcmp(h, "arctanh") || ! strcmp(h, "arccoth"))
		g = mk_pow(mk_add(mk_num(1), mk_neg(SQ(A))), mk_num(-1));
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
		if (num_is(b, 0)) { delete(t); * p = mk_num(1); return; }
		if (num_is(b, 1)) keep = a;
		}
	else if (is_head(t, "*", 2))
		{
		if (num_is(a, 0) || num_is(b, 0)) { delete(t); * p = mk_num(0); return; }
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
	for (a = TERM_ARGS(term); a && n < MAXARGS; a = ARGS_NEXT(a))
		args[n++] = deref(ARGS_ITEM(a));
	return ((s_function *) value(f))(args, n, f);
}
