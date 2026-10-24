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
 *	  inthide(u,x), unintegrable(u,x)   Int(u,x)
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

static int tequal (Node * a, Node * b)
{
	double va, vb;
	Symbol * sa, * sb;
	int i, n;
	a = deref(a); b = deref(b);
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
	else if (is_head(t, "^", 2) && is_num(arg(t, 1), & e) && e == 1)
		expand_to(arg(t, 0), out);			/* u^1 = u */
	else if (is_head(t, "^", 2) && is_num(arg(t, 1), & e) && e == 0)
		tl_add(out, mk_num(1));				/* u^0 = 1 */
	else if (is_head(t, "^", 2) && is_num(arg(t, 1), & e)
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
	if (is_num(t, & v)) m->c *= v;
	else if (is_head(t, "*", 2)) { mono_flatten(arg(t, 0), m); mono_flatten(arg(t, 1), m); }
	else if (is_head(t, "-", 1)) { m->c = -m->c; mono_flatten(arg(t, 0), m); }
	else if (is_head(t, "^", 2) && is_num(arg(t, 1), & e)) mono_addfac(m, arg(t, 0), e);
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
	int i, j, nm = 0;
	Node * s = NULL;
	if (! ms) fatal("symfkt : no room");
	for (i = 0; i < l->n; i++)
		{
		Mono m = { 1.0, NULL, 0, 0 };
		mono_flatten(l->t[i], & m);
		mono_normalize(& m);
		for (j = 0; j < nm; j++)
			if (mono_like(& ms[j], & m)) break;
		if (j < nm) { ms[j].c += m.c; free(m.f); }
		else ms[nm++] = m;
		}
	for (j = 0; j < nm; j++)
		{
		if (ms[j].c != 0) s = mk_add(s, mono_build(& ms[j]));
		free(ms[j].f);
		}
	free(ms);
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
	if (is_head(t, "^", 2) && tequal(arg(t, 0), x) && is_num(arg(t, 1), & e))
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

static int eq_terms (Node * u, Node * v)
{
	double x, y;
	if (num_value(u, & x) && num_value(v, & y))
		return fabs(x - y) <= 1e-12 * (1.0 + fabs(x));
	return tequal(u, v);
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
	if (n != 1) return NULL;
	expand_to(a[0], & l);
	return tl_collect(& l);
}

static Node * s_expandintegrand (Node * a[], int n, Symbol * f)
{
	TList l = {0};
	Node * in, * r;
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

static Node * s_inthide (Node * a[], int n, Symbol * f)	/* inthide, unintegrable */
{
	if (n != 2 || ! find_symbol("Int")) return NULL;
	return mk_f2("Int", tcpy(a[0]), tcpy(a[1]));
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
	{ "unintegrable",    s_inthide },
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
