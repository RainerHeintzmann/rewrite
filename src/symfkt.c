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
 *	  expandintegrand(u,x), expandintegrand(u,v,x)   expand(u), expand(u*v);
 *	                       partial fractions of a rational function
 *	  coeff(u,x,n)         coefficient of x^n in u
 *	  expon(u,x)           degree of u in x
 *	  subst(u,x,v)         u with x replaced by v
 *	  simp(u,x), simplify(u)  u with like powers in a product combined
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
 *	  (deriv(u,x), the derivative, is a function of inc/helpers defined by
 *	  rules, see ATT RULES below; deriv() here calls it)
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
#include "exact.h"
#include "apart.h"	/* partial fractions */
#include "listmatch.h"	/* matchq */

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

static Node * real_copy (Node * t);
static Node * mk_neg (Node * a);

/* numeric value, also of a calculable expression like 2*3-1, and of an
 * exact expression without an exact value like 2^(1/2) (calculated with
 * real numbers) */
static int nv_strict = 1;	/* no real fallback (see num_value_r) */

static int num_value (Node * t, double * v)
{
	Node * r;
	if (is_num(t, v)) return 1;
	t = deref(t);
	if (! t || t->type != Func) return 0;
	if (nv_strict)		/* an exact value only (2^(1/2) has none) */
		{
		int save = calc_exact_only;
		calc_exact_only = 1;
		r = calkulate(t);
		calc_exact_only = save;
		}
	else
		r = calkulate(t);	/* with a real value for 2^(1/2) */
	if (! r) return 0;
	if (! num_to_double((Symbol *) r, v))
		{ delnum((Symbol *) r, TRUE); return 0; }
	delnum((Symbol *) r, TRUE);
	return 1;
}

/* the value of t, with a real value for 2^(1/2): for signs and comparisons
 * only, a term built from it would contain 1.41421 */
static int num_value_r (Node * t, double * v)
{
	int save = nv_strict, r;
	nv_strict = 0;
	r = num_value(t, v);
	nv_strict = save;
	return r;
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

/* ---- roles: the functions and constants the helpers know ----
 * The helpers recognize and build terms with the operators and functions
 * of the library (inc/alg): "+", "*", "^", "-", "/", "mi" (1/x), "sin",
 * "cos", ..., "ln", "exp", the constants "pi" and "eE", "Int", "D". These
 * strings are roles. By default a role is played by the symbol of the
 * same name; a library with other names declares
 *     SYMBOLIC "cos" = "cosinus"
 * The helpers assume the usual properties: "+" and "*" are commutative and
 * associative, "mi(x)" is 1/x, "cos" is the cosine, and so on. */

#define MAXROLES 128
static struct { char * role, * sym; } roles[MAXROLES];
static int nroles = 0;

void role_fkt (Node * np)	/* SYMBOLIC "role" = "symbol"; SYMBOLIC alone: clear */
{
	const char * r, * sy;
	int i;
	np = np->r;			/* the statement: FUNC(role_fkt, PARAM(role, symbol)) */
	if (! np)
		{
		for (i = 0; i < nroles; i++) { free(roles[i].role); free(roles[i].sym); }
		nroles = 0;
		return;
		}
	r = name((Symbol *) np->l);
	sy = name((Symbol *) np->r);
	if (! find_symbol(sy))
		printfErr("SYMBOLIC : %s is not declared (role %s)\n", sy, r);
	for (i = 0; i < nroles; i++)
		if (strcmp(roles[i].role, r) == 0) break;
	if (i == nroles)
		{
		if (nroles == MAXROLES) { printfErr("SYMBOLIC : too many roles\n"); return; }
		roles[nroles++].role = strdup(r);
		}
	else
		free(roles[i].sym);
	roles[i].sym = strdup(sy);
}

static const char * role_symbol_name (const char * role)	/* the symbol playing a role */
{
	int i;
	for (i = 0; i < nroles; i++)
		if (strcmp(roles[i].role, role) == 0) return roles[i].sym;
	return role;
}

/* the role of a function symbol: its name, unless a role is mapped to it,
 * or its name is a role that another symbol plays ("" then) */
static const char * role_of (Symbol * f)
{
	const char * n = name(f);
	int i;
	if (nroles == 0) return n;		/* the usual case: names are roles */
	for (i = 0; i < nroles; i++)
		if (strcmp(roles[i].sym, n) == 0) return roles[i].role;
	for (i = 0; i < nroles; i++)
		if (strcmp(roles[i].role, n) == 0) return "";
	return n;
}

static Symbol * role_find (const char * role)	/* symbol of a role or NULL */
{
	return find_symbol(role_symbol_name(role));
}

static int is_imag_unit (Node * t);
static int imag_reduce (double e, double * rest);

static int is_head (Node * t, const char * h, int nargs)
{
	t = deref(t);
	return t && t->type == Func && strcmp(role_of(TERM_HEAD(t)), h) == 0
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
	if (strcmp(role_of(TERM_HEAD(a)), role_of(TERM_HEAD(b))) != 0) return 0;
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
	/* a polynomial division that was not possible (no polynomial), or an
	 * expansion that did not apply (partial fractions with symbolic
	 * coefficients): the rule assumed Mathematica's semantics, its result is
	 * of no use */
	if (is_head(t, "polyquotient", 3) || is_head(t, "polyremainder", 3)
	    || is_head(t, "expandintegrand", -1) || is_head(t, "substexp", -1) || is_head(t, "binomsum", -1)
	    || is_head(t, "substfor", -1) || is_head(t, "trignorm", -1)
	    || is_head(t, "substfracpow", -1) || is_head(t, "substsqrtquad", -1)
	    || is_head(t, "trigexpand", -1)) return 1;
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

/* copy of a numeric expression with the exact numbers as real numbers
 * (for the value of 2^(1/2)); NULL if it contains a symbol without value */
static Node * real_copy (Node * t)
{
	Symbol * ns;
	double d;
	Node * l, * r;
	t = deref(t);
	if (! t) return NULL;
	if ((ns = num_sym(t)) != NULL)
		return num_to_double(ns, & d) ? mk_num(d) : NULL;
	if (t->type == Func)
		{
		Node * a = real_copy(t->r);
		return a ? mknod(Func, t->l, a) : NULL;
		}
	if (t->type != Terms) return NULL;		/* a symbol: no number */
	l = real_copy(t->l);
	r = l ? real_copy(t->r) : NULL;
	if (! r) { delete(l); return NULL; }
	return mknod(Terms, l, r);
}

/* real numbers with an integer value next to an exact number become exact
 * integers: the 1 of a rule loaded before inc/exact is a real number, and
 * (1/2)*1.0 would be 0.5 instead of 1/2. Changes the arguments of t. */
void exact_integers (Node * t)
{
	Node ** slot;
	int exact = 0, k, n;
	double v;
	t = deref(t);
	if (! t || t->type != Func || ! exact_numbers()) return;
	n = term_nargs(t);
	for (k = 0; k < n; k++)
		if (is_exact(arg(t, k))) exact = 1;
	if (! exact) return;
	slot = & t->r;
	for (k = 0; k < n; k++)
		{
		Node ** cur = (k < n - 1) ? & (* slot)->l : slot;
		Symbol * s = num_sym(* cur), * e;
		if ((* cur)->type == Const && s && ! num_exact(s) && num_to_double(s, & v) && v == floor(v) && fabs(v) < 1e15
		    && (e = make_exact((long long) v, 1)) != NULL)
			{
			delete(* cur);
			* cur = mknod(Const, (Node *) e, NULL);
			}
		if (k < n - 1) slot = & (* slot)->r;
		}
}

/* the value of t calculated with real numbers (2^(1/2) = 1.41421), or NULL
 * (also for 1/0) */
Node * numeric_real (Node * t)
{
	Node * c = real_copy(t), * r;
	double v;
	if (! c) return NULL;
	retype_term(c);
	r = calkulate(c);
	delete(c);
	if (r && num_to_double((Symbol *) r, & v) && ! isfinite(v))	/* 1/0 stays 1/0 */
		{ delnum((Symbol *) r, TRUE); return NULL; }
	return r;
}

/* numeric contagion, as in Mathematica: an operation on numbers that has no
 * exact value (2^(1/2)*0.7) is calculated with real numbers if one of its
 * arguments is a real number. The value (a number symbol) or NULL. */
Node * numeric_contagion (Node * t)
{
	Node * c, * r;
	int k, n, inexact = 0;
	t = deref(t);
	if (! t || t->type != Func || builtin(t->l)) return NULL;
	n = term_nargs(t);
	for (k = 0; k < n; k++)
		{
		Symbol * s = num_sym(arg(t, k));
		double v;
		/* a real 1 (from rules loaded before inc/exact) counts as exact */
		if (s && ! num_exact(s) && num_to_double(s, & v) && v != floor(v)) inexact = 1;
		}
	if (! inexact || ! (c = real_copy(t))) return NULL;
	retype_term(c);
	r = calkulate(c);
	delete(c);
	return r;
}

Node * term_copy (Node * t)	/* exported tcpy */
{
	return tcpy(t);
}

static Symbol * fsym (const char * f)	/* f: a role */
{
	Symbol * s = role_find(f);
	if (! s) fatal("symfkt : function %s is not declared (SYMBOLIC role)", role_symbol_name(f));
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
	if (is_exact(a) && is_exact(b) && is_num(b, & vb) && fabs(vb) < 1000)
		return fold_exact("^", a, b);	/* 4^(1/2) = 2, 2^(1/2) stays (exact) */
	if (is_num(a, & va) && is_num(b, & vb) && (va > 0 || vb == floor(vb)))
		{ delete(a); delete(b); return mk_num(pow(va, vb)); }
	return mk_f2("^", a, b);
}

/* a f b for two exact numbers, with the exact functions of inc/exact */
static Node * fold_exact (const char * f, Node * a, Node * b)
{
	Node * t = mk_f2(f, a, b), * r;
	int save = calc_exact_only;
	calc_exact_only = 1;		/* 2^(1/2) stays a term */
	r = calkulate(t);
	calc_exact_only = save;
	if (! r) return t;		/* e.g. division by zero: stays a term */
	delete(t);
	return mknod(Const, r, NULL);
}

/* exact powers in normal form, or NULL if there is nothing to do:
 * (a^q)^n = a^(q*n) for exact a, q and an integer n (true for every a, also
 * on the principal branch): (2^(1/2))^2 = 2; and roots of rationals as in
 * Mathematica (rat_pow_norm): 8^(1/2) = 2*2^(1/2), (1/3)^(1/2) = 3^(-1/2) */
Node * exact_pow_pow (Node * t)
{
	Node * b;
	double n;
	Symbol * sb, * se;
	t = deref(t);
	if (! t || ! is_head(t, "^", 2)) return NULL;
	b = deref(arg(t, 0));
	if (is_imag_unit(b) && is_num(arg(t, 1), & n) && n == floor(n))	/* im^3 = -im */
		{
		double rest;
		int sg = imag_reduce(n, & rest);
		Node * r = rest ? tcpy(b) : mk_int(1);
		return sg < 0 ? mk_mul(mk_int(-1), r) : r;
		}
	if (! exact_numbers()) return NULL;
	if ((sb = num_sym(b)) && (se = num_sym(arg(t, 1))) && num_exact(sb) && num_exact(se))
		{
		double vb, ve, p, q;
		/* (-3)^(1/2) is complex: NaN as with real numbers, so that a rule
		 * giving it counts as not applicable (Rubi's Rt[-3,2] is I*Sqrt[3]) */
		if (num_to_double(sb, & vb) && vb < 0 && num_to_double(se, & ve) && ve != floor(ve)
		    && rat_approx(ve, & p, & q) && fmod(q, 2.0) == 0)
			return mk_num(NAN);
		{
		void * qb = exact_to_rat(sb), * qe = exact_to_rat(se), * rest, * fexp, * c;
		Node * r = NULL;
		if (qb && qe && (c = rat_pow_norm(qb, qe, & rest, & fexp)) != NULL)
			r = mk_mul(mknod(Const, (Node *) make_exact_rat(c), NULL),
			           mk_pow(mknod(Const, (Node *) make_exact_rat(rest), NULL),
			                  mknod(Const, (Node *) make_exact_rat(fexp), NULL)));
		if (qb) del_rat(qb);
		if (qe) del_rat(qe);
		return r;
		}
		}
	if (! is_head(b, "^", 2) || ! is_exact(arg(b, 0)) || ! is_exact(arg(b, 1))
	    || ! is_exact(arg(t, 1)) || ! is_num(arg(t, 1), & n) || n != floor(n))
		return NULL;
	return mk_pow(tcpy(arg(b, 0)), fold_exact("*", tcpy(arg(b, 1)), tcpy(arg(t, 1))));
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
	int num;
	num = num_value(t, & v);	/* 3^(1/2) is a factor, not the number 1.73205 */
	if (num) { m->c *= v; if (! num_value_exact(t)) m->exact = 0; }
	else if (is_head(t, "*", 2)) { mono_flatten(arg(t, 0), m); mono_flatten(arg(t, 1), m); }
	else if (is_head(t, "-", 1)) { m->c = -m->c; mono_flatten(arg(t, 0), m); }
	else if (is_head(t, "^", 2) && num_value(arg(t, 1), & e))
		mono_addfac(m, arg(t, 0), e, num_value_exact(arg(t, 1)));
	else mono_addfac(m, t, 1, 1);
}

/* a root of an integer and the coefficient, as in Mathematica: 2*2^(-1/2) =
 * 2^(1/2), (1/2)*2^(1/2) = 2^(-1/2) */
/* the imaginary unit of the integration (role "im", inc/integration/base):
 * a symbol without value, im^2 = -1 when collecting and simplifying */
static int is_imag_unit (Node * t)
{
	Symbol * s = role_find("im");
	t = deref(t);
	return s && t && (atom_sym(t) == s);
}

/* im^e with an integer e: the sign (+1 or -1) and the remaining power 0 or 1 */
static int imag_reduce (double e, double * rest)
{
	int k = (int) fmod(e, 4.0);
	if (k < 0) k += 4;
	* rest = k % 2;
	return k >= 2 ? -1 : 1;
}

static void mono_imag (Mono * m)		/* c * im^e: im^2 = -1 */
{
	int i;
	double rest;
	for (i = 0; i < m->nf; i++)
		if (is_imag_unit(m->f[i].base) && m->f[i].e == floor(m->f[i].e))
			{
			m->c *= imag_reduce(m->f[i].e, & rest);
			m->f[i].e = rest;
			}
}

static void mono_roots (Mono * m)
{
	int i;
	double b, p, q;
	if (! m->exact) return;
	for (i = 0; i < m->nf; i++)
		{
		Fac * f = & m->f[i];
		if (! f->exact || f->e == floor(f->e) || fabs(f->e) >= 1
		    || ! is_exact(f->base) || ! is_num(f->base, & b) || b != floor(b) || b < 2
		    || ! rat_approx(m->c, & p, & q))
			continue;
		if (f->e < 0 && fmod(p, b) == 0) { m->c /= b; f->e += 1; }
		else if (f->e > 0 && fmod(q, b) == 0) { m->c *= b; f->e -= 1; }
		}
}

static void mono_normalize (Mono * m)	/* drop x^0, sort the bases */
{
	int i, j, k = 0;
	mono_roots(m);
	mono_imag(m);
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
	{
	double gmax = 0;		/* the largest coefficient of the sum */
	for (j = 0; j < nm; j++)
		if (fabs(ms[j].c) > gmax) gmax = fabs(ms[j].c);
	for (j = 0; j < nm; j++)
		{
		/* cancelled up to rounding errors: 0.375 a - 0.375 a; or a rounding
		 * error next to the other summands: 3e-17 * u from cos(pi/2) */
		if (fabs(ms[j].c) > 1e-12 * mag[j]
		    && (ms[j].exact || fabs(ms[j].c) > 1e-13 * gmax))
			s = mk_add(s, mono_build(& ms[j]));
		free(ms[j].f);
		}
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
	if (num_value_r(u, & v)) return v > 0;
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
	if (num_value_r(u, & x) && num_value_r(v, & y))
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

static int poly_coeffs (Node * u, Node * x, Node * c[], int * deg);

/* polynomial in x^k: a polynomial in x with only the powers k*j */
static int poly_in_power (Node * u, Node * x, int k)
{
	Node * c[64];
	int deg, j, ok = 1;
	if (! poly_coeffs(u, x, c, & deg)) return 0;
	for (j = 0; j <= deg; j++)
		{
		if (j % k != 0 && ! is_zero(c[j])) ok = 0;
		delete(c[j]);
		}
	return ok;
}

static Node * s_polyq (Node * a[], int n, Symbol * f)
{
	double deg, want, k;
	Node * c = NULL, * v;
	int ok;
	/* Rubi's PolyQ[u_, v_] := False unless v is a symbol x or a power x^n:
	 * PolyQ[x*Log[x], e*x] is False (as a generalized variable, e*x would
	 * take x*Log[x] for a constant, and a rule for polynomials would apply) */
	if (n < 2) return NULL;
	v = deref(a[1]);
	if (is_head(v, "^", 2)) v = arg(v, 0);
	if (! atom_sym(v) || num_sym(v)) return mk_bool(0, f);
	if (n == 2 && is_head(a[1], "^", 2) && ! is_head(arg(a[1], 0), "+", -1)
	    && num_value(arg(a[1], 1), & k) && k == floor(k) && k >= 1)	/* PolyQ[u, x^n] */
		return mk_bool(poly_in_power(a[0], arg(a[1], 0), (int) k), f);
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

static Node * s_nonsumq (Node * a[], int n, Symbol * f)	/* Rubi's NonsumQ */
{
	if (n != 1) return NULL;
	return mk_bool(! is_head(a[0], "+", 2) && ! is_head(a[0], "-", 2), f);
}

/* Rubi's GtQ, LtQ, GeQ, LeQ: false unless both are numbers (a symbolic
 * a^2 > 0 is not known, and Not[GtQ[a,0]] is then true) */
static Node * order_q (Node * a[], int n, Symbol * f, int op)
{
	double u, v;
	int r;
	if (n != 2) return NULL;
	if (! num_value_r(a[0], & u) || ! num_value_r(a[1], & v)) return mk_bool(0, f);
	r = op == 0 ? u > v : op == 1 ? u < v : op == 2 ? u >= v : u <= v;
	return mk_bool(r, f);
}
static Node * s_gtq (Node * a[], int n, Symbol * f) { return order_q(a, n, f, 0); }
static Node * s_ltq (Node * a[], int n, Symbol * f) { return order_q(a, n, f, 1); }
static Node * s_geq (Node * a[], int n, Symbol * f) { return order_q(a, n, f, 2); }
static Node * s_leq (Node * a[], int n, Symbol * f) { return order_q(a, n, f, 3); }

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
static Node * expand_linear_inner (Node * u, Node * x);
static Node * apart_term (Node * u, Node * x);

static Node * s_expandintegrand (Node * a[], int n, Symbol * f)
{
	TList l = {0};
	Node * in, * r;
	if (n == 2 && (r = expand_linear_product(a[0], a[1])))
		return r;
	if (n == 2 && (r = expand_linear_inner(a[0], a[1])))
		return r;
	if (n == 2)
		in = tcpy(a[0]);
	else if (n == 3)
		in = mk_mul(tcpy(a[0]), tcpy(a[1]));
	else
		return NULL;
	if ((r = apart_term(in, a[n - 1])) != NULL)	/* rational function */
		{
		delete(in);
		return r;
		}
	expand_to(in, & l);
	r = tl_collect(& l);
	/* Rubi rules like Int[u] := Int[ExpandIntegrand[u,x],x] loop if the
	 * expansion makes no progress. Then expandintegrand stays unevaluated;
	 * also if no sum results: only the form of a product would change,
	 * and RubiNorm would change it back. */
	if (tequal(r, in) || ! (is_head(r, "+", 2) || is_head(r, "-", 2)))
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
	if (strcmp(role_of(TERM_HEAD(t)), h) == 0) return 1;
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

/* a product of powers with like bases combined, as Mathematica's automatic
 * simplification does: (a*b)^k = a^k*b^k and (a^m)^k = a^(m*k) for integer
 * k, a^m*a^n = a^(m+n); numbers are multiplied */
#define MAXPF 64
typedef struct { Node * base; double e; } PowFac;

static int pf_merged, pf_numbers;	/* like bases combined, numbers seen */

static int pf_collect (Node * u, double k, PowFac * pf, int * n, Node ** coef)
{
	double e;
	int i;
	u = deref(u);
	if (is_head(u, "*", 2))
		return pf_collect(arg(u, 0), k, pf, n, coef)
		    && pf_collect(arg(u, 1), k, pf, n, coef);
	if (is_head(u, "/", 2))
		return pf_collect(arg(u, 0), k, pf, n, coef)
		    && pf_collect(arg(u, 1), -k, pf, n, coef);
	if (is_head(u, "mi", 1))
		return pf_collect(arg(u, 0), -k, pf, n, coef);
	if (is_head(u, "^", 2) && num_value(arg(u, 1), & e) && e == floor(e))
		return pf_collect(arg(u, 0), k * e, pf, n, coef);
	if (num_sym(u))
		{
		* coef = mk_mul(* coef, mk_pow(tcpy(u), mk_int(k)));
		pf_numbers++;
		return 1;
		}
	for (i = 0; i < * n; i++)
		if (tequal(pf[i].base, u))
			{
			pf[i].e += k;
			pf_merged++;
			return 1;
			}
	if (* n == MAXPF) return 0;
	pf[* n].base = u;
	pf[(* n)++].e = k;
	return 1;
}

static Node * simp_product (Node * u)
{
	PowFac pf[MAXPF];
	Node * coef = mk_int(1), * r = NULL, * own[MAXPF];
	double c;
	int n = 0, i, pass, nown = 0;
	pf_merged = pf_numbers = 0;
	if (! pf_collect(u, 1, pf, & n, & coef)) { delete(coef); return tcpy(u); }
	for (i = 0; i < n; i++)	/* im^2 = -1 */
		if (is_imag_unit(pf[i].base) && pf[i].e == floor(pf[i].e) && (pf[i].e < 0 || pf[i].e > 1))
			{
			double rest;
			if (imag_reduce(pf[i].e, & rest) < 0) coef = mk_mul(coef, mk_int(-1));
			pf[i].e = rest;
			pf_merged++;
			}
	for (i = 0; i < n; i++)	/* 2*2^(-1/2) = 2^(1/2), (1/3)*3^(1/2) = 3^(-1/2) */
		{
		Node * b = deref(pf[i].base);
		double v, f, bb, p, q;
		if (! is_head(b, "^", 2) || ! is_exact(arg(b, 0)) || ! is_num(arg(b, 0), & bb)
		    || bb != floor(bb) || bb < 2 || ! is_exact(arg(b, 1)) || ! is_num(arg(b, 1), & f)
		    || ! is_exact(coef) || ! is_num(coef, & v) || ! rat_approx(v, & p, & q))
			continue;
		f *= pf[i].e;
		if (f == floor(f) || fabs(f) >= 1) continue;
		if (f < 0 && fmod(p, bb) == 0) { coef = mk_mul(coef, mk_pow(tcpy(arg(b, 0)), mk_int(-1))); f += 1; }
		else if (f > 0 && fmod(q, bb) == 0) { coef = mk_mul(coef, tcpy(arg(b, 0))); f -= 1; }
		else continue;
		pf[i].base = own[nown++] = mk_pow(tcpy(arg(b, 0)), mk_num_ex(f, 1));
		pf[i].e = 1;
		pf_merged++;
		}
	/* powers and atoms first, other functions (ln, arcsec, ...) last: the
	 * matcher does not regroup products, and Rubi's patterns u*(a+b*f(x))
	 * need the function at the top level */
	for (pass = 0; pass < 2; pass++)
		for (i = 0; i < n; i++)
			{
			Node * t;
			int fn = pf[i].e == 1 && deref(pf[i].base)->type == Func
			         && ! is_head(pf[i].base, "+", -1) && ! is_head(pf[i].base, "^", -1);
			if (pf[i].e == 0 || fn != pass) continue;
			t = pf[i].e == 1 ? tcpy(pf[i].base) : mk_pow(tcpy(pf[i].base), mk_int(pf[i].e));
			r = r ? mk_mul(r, t) : t;
			}
	for (i = 0; i < nown; i++) delete(own[i]);
	if (! r) return coef;
	if (num_value(coef, & c) && c == 1) { delete(coef); return r; }
	return mk_mul(coef, r);
}

static Node * s_simp (Node * a[], int n, Symbol * f)	/* simp(u,x), simplify(u) */
{
	if (n < 1 || n > 2) return NULL;
	if (is_head(a[0], "*", 2) || is_head(a[0], "^", 2) || is_head(a[0], "/", 2))
		{
		Node * r = simp_product(a[0]);
		if (pf_merged || pf_numbers > 1 || is_zero(r)) return r;	/* 0*n^-1 = 0 */
		delete(r);		/* nothing combined: keep the order (no cycle with collect) */
		}
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
	if (num_value(a[0], & u) && ! (num_sym(a[0]) && is_exact(a[0])))
		{
		if (u < 0 && k == floor(k) && fmod(k, 2.0) != 0)
			return mk_num(-pow(-u, 1.0 / k));
		if (u >= 0)
			return mk_num(pow(u, 1.0 / k));
		}
	/* an exact number without an exact root: 2^(1/2) stays symbolic */
	if (num_sym(a[0]) && is_exact(a[0]) && num_value(a[0], & u) && u < 0
	    && k == floor(k) && fmod(k, 2.0) != 0)
		return mk_neg(mk_pow(mk_neg(tcpy(a[0])), mk_num_ex(1.0 / k, 1)));
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
	if (n != 2 || ! role_find("Int")) return NULL;
	return mk_f2("Int", tcpy(a[0]), tcpy(a[1]));
}

/* ================= numbers as fractions ================= */

/* v = p/q (continued fractions, q <= 1e6); 0 if no such fraction is close.
 * Close means a few rounding errors: with 1e-12, every real number had a
 * fraction (0.128710 = 245352250447/1906243172561 after a few steps). */
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
		if (fabs(fabs(v) - h1 / k1) <= 1e-14 * (1.0 + fabs(v))) break;
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
	int i, num;
	num = num_value(u, & v);	/* 2^(1/2) is no fraction: numerator 2^(1/2) */
	if (num)
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
		else if ((num = num_value(t, & v))
		         && rat_approx(v, & p, & q))
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

static Node * mk_f1 (const char * f, Node * a);
static Node * mk_neg (Node * a);

/* trig(u + k pi/2) with odd k as +-cofunction(u), as Mathematica evaluates
 * Cos[Pi/2 + x] = -Sin[x] automatically; NULL if u has no such form */
static Node * pi2_shift (Node * t)
{
	static const struct { const char * f, * g; int s1, s3; } sh[] = {	/* k = 1 and k = 3 (-1) */
		{ "sin", "cos", 1, -1 }, { "cos", "sin", -1, 1 }, { "tan", "cot", -1, -1 },
		{ "cot", "tan", -1, -1 }, { "sec", "csc", -1, 1 }, { "csc", "sec", 1, -1 } };
	TList l = {0};
	Node * rest = NULL, * r = NULL;
	int i, j, k = 0;
	double v, q;
	t = deref(t);
	for (i = 0; i < 6; i++)
		if (is_head(t, sh[i].f, 1)) break;
	if (i == 6 || ! is_head(arg(t, 0), "+", 2)) return NULL;
	summands_to(arg(t, 0), & l, 0);
	for (j = 0; j < l.n; j++)
		if (! k && num_value(l.t[j], & v) && (q = v / (M_PI / 2), fabs(q - floor(q + 0.5)) < 1e-9)
		    && ((long) floor(q + 0.5)) % 4 != 0)
			k = (int) ((((long) floor(q + 0.5)) % 4 + 4) % 4);	/* 1, 2 or 3 */
		else
			rest = rest ? mk_add(rest, tcpy(l.t[j])) : tcpy(l.t[j]);
	tl_free(& l);
	if (! k || ! rest) { delete(rest); return NULL; }
	if (k == 2)		/* shift by pi: sin(u+pi) = -sin(u), tan(u+pi) = tan(u) */
		{
		r = mk_f1(sh[i].f, rest);
		return (i == 2 || i == 3) ? r : mk_neg(r);
		}
	r = mk_f1(sh[i].g, rest);
	return (k == 1 ? sh[i].s1 : sh[i].s3) < 0 ? mk_neg(r) : r;
}

/* all trig functions of u + k*pi/2 in t written without the shift */
static Node * shift_all (Node * t)
{
	Node * r, * s;
	int k, n;
	t = deref(t);
	if (! t || t->type != Func) return tcpy(t);
	n = term_nargs(t);
	{
	Node * args = NULL, ** tail = & args;
	for (k = 0; k < n; k++)
		{
		Node * c = shift_all(arg(t, k));
		if (k < n - 1) { * tail = mknod(Terms, c, NULL); tail = & (* tail)->r; }
		else * tail = c;
		}
	r = mknod(Func, t->l, args);
	}
	if ((s = pi2_shift(r)) != NULL) { delete(r); return s; }
	return r;
}

/* ---- trignorm(u, x): Mathematica's 1/sin = csc and Rubi's FixInertTrigFunction ----
 * Every trig or hyperbolic factor with a negative integer exponent becomes
 * its reciprocal function (Mathematica writes Sin[x]^-3 as Csc[x]^3). Then
 * Rubi's FixInertTrigFunction writes the factors in the forms the rules
 * expect (sec^m*sin^n = cos^-m*sin^n): the function fixinert, defined by
 * rules translated from Rubi (inc/integration/rubi/r4_0_fixinert); without
 * it only the first step is done. NULL: no change. */

static Node * s_rules (Node * a[], int n, Symbol * f);

static const char * trig_recip (const char * h)
{
	static const char * p[][2] = { {"sin","csc"}, {"cos","sec"}, {"tan","cot"},
		{"sinh","csch"}, {"cosh","sech"}, {"tanh","coth"} };
	int i;
	for (i = 0; i < 6; i++)
		{
		if (! strcmp(h, p[i][0])) return p[i][1];
		if (! strcmp(h, p[i][1])) return p[i][0];
		}
	return NULL;
}

static int is_canon_trig (const char * h)	/* sin, cos, tan, sinh, cosh, tanh */
{
	return ! strcmp(h, "sin") || ! strcmp(h, "cos") || ! strcmp(h, "tan")
	    || ! strcmp(h, "sinh") || ! strcmp(h, "cosh") || ! strcmp(h, "tanh");
}

static Node * s_trignorm (Node * a[], int n, Symbol * f)
{
	TList l = {0};
	Node * fb[MAXPF], * r = NULL, * x;
	double fe[MAXPF];
	int trig[MAXPF];		/* 0: other, 1: trig with integer exponent, 2: other exponent */
	int i, j, nf, nt = 0;
	if (n != 2) return NULL;
	x = a[1];
	factors_to(a[0], & l);
	if (l.n > MAXPF) { l.n = 0; tl_free(& l); return NULL; }
	nf = 0;
	for (i = 0; i < l.n; i++)		/* factor = base^exponent, trig in sin, cos, tan */
		{
		Node * t = deref(l.t[i]), * b0 = t;
		double e = 1;
		int ie = 1;
		if (is_head(t, "^", 2))
			{
			b0 = arg(t, 0);
			ie = num_value(arg(t, 1), & e) && e == floor(e);
			}
		if (b0->type == Func && term_nargs(b0) == 1 && contains(b0, x)
		    && trig_recip(role_of(TERM_HEAD(b0))))
			{
			Node * b;
			nt++;
			if (! ie)			/* sin(2x)^(3/2): kept as it is */
				{
				fb[nf] = tcpy(t); fe[nf] = 1; trig[nf++] = 2;
				continue;
				}
			if (is_canon_trig(role_of(TERM_HEAD(b0)))) b = tcpy(b0);
			else { b = mk_f1(trig_recip(role_of(TERM_HEAD(b0))), tcpy(arg(b0, 0))); e = -e; }
			for (j = 0; j < nf; j++)		/* sin^a * csc^b = sin^(a-b) */
				if (trig[j] == 1 && tequal(fb[j], b)) break;
			if (j < nf) { fe[j] += e; delete(b); continue; }
			fb[nf] = b; fe[nf] = e; trig[nf++] = 1;
			}
		else
			{
			fb[nf] = tcpy(t); fe[nf] = 1; trig[nf++] = 0;
			}
		}
	l.n = 0;			/* the factors belong to a[0] */
	tl_free(& l);
	for (i = 0; i < nf; i++)		/* negative exponents: csc^3, sec, ... */
		if (trig[i] == 1 && fe[i] < 0)
			{
			Node * g = mk_f1(trig_recip(role_of(TERM_HEAD(fb[i]))), tcpy(arg(fb[i], 0)));
			delete(fb[i]);
			fb[i] = g;
			fe[i] = -fe[i];
			}
	for (i = 0; i < nf; i++)
		{
		Node * t = fb[i];
		if (trig[i] == 1 && fe[i] == 0) { delete(t); continue; }
		if (fe[i] != 1) t = mk_pow(t, mk_int(fe[i]));
		r = r ? mk_mul(r, t) : t;
		}
	if (! r) r = mk_int(1);
	if (nt > 0)			/* Rubi's FixInertTrigFunction: rules of the library */
		{
		Symbol * fi = role_find("fixinert");
		Node * fa[2], * g;
		fa[0] = r; fa[1] = x;
		if (fi && (g = s_rules(fa, 2, fi)) != NULL) { delete(r); r = g; }
		}
	if (nt == 0 || tequal(r, a[0])) { delete(r); return NULL; }	/* no change */
	return r;
}

/* ---- trigexpand(u, x): Mathematica's TrigExpand for multiple angles ----
 * If u contains sin, cos, tan, cot, sec, csc of at least two different
 * multiples k*w of one angle w = g*x (sin(2x) and cos(x), cos(x) and
 * tan(x/2)), all of them are written with sin(w) and cos(w):
 *   sin(k w) = sum_{j odd} (-1)^((j-1)/2) C(k,j) cos^(k-j) sin^j,
 *   cos(k w) = sum_{j even} (-1)^(j/2) C(k,j) cos^(k-j) sin^j,
 * tan, cot, sec, csc as quotients. NULL if u has no such form. */

#define MAXTX 16
typedef struct { int n, ok, denom; double c[MAXTX]; int frac[MAXTX]; double g; } TrigExp;

static int is_circ (Node * t)
{
	static const char * h[] = { "sin", "cos", "tan", "cot", "sec", "csc", NULL };
	int i;
	t = deref(t);
	if (! t || t->type != Func || term_nargs(t) != 1) return 0;
	for (i = 0; h[i]; i++)
		if (is_head(t, h[i], 1)) return 1;
	return 0;
}

static int tx_coeff (Node * t, Node * x, double * c)	/* argument = c*x */
{
	Node * k[64];		/* MAXDEG, defined below */
	int deg, j, ok;
	if (! poly_coeffs(arg(t, 0), x, k, & deg)) return 0;
	ok = deg == 1 && is_zero(k[0]) && num_value(k[1], c) && * c != 0;
	for (j = 0; j <= deg; j++) delete(k[j]);
	return ok;
}

/* ctx: 0 polynomial, 1 in a denominator (negative power), 2 under a
 * non-integer power, 3 in another function (exp(sin(x))) */
static void tx_scan (Node * u, Node * x, TrigExp * s, int ctx)
{
	double c, e;
	int i, k, n;
	u = deref(u);
	if (! s->ok || ! u || ! contains(u, x)) return;
	if (u->type != Func) { s->ok = 0; return; }	/* x outside the trig functions */
	if (is_head(u, "^", 2))
		{
		int c2 = ctx;
		if (! num_value(arg(u, 1), & e) || e != floor(e))
			{
			c2 = 2;
			/* (sin(x)*cos(x)^3)^(1/2): would be split into powers of
			 * the factors, which is wrong where both are negative */
			if (is_head(arg(u, 0), "*", 2) || is_head(arg(u, 0), "/", 2)) { s->ok = 0; return; }
			}
		else if (e < 0 && c2 == 0) c2 = 1;
		tx_scan(arg(u, 0), x, s, c2);
		tx_scan(arg(u, 1), x, s, ctx == 2 ? 2 : 3);	/* e^sin(x) */
		return;
		}
	if (! is_circ(u) && ! is_head(u, "+", 2) && ! is_head(u, "*", 2) && ! is_head(u, "-", -1))
		{
		n = term_nargs(u);
		for (k = 0; k < n; k++) tx_scan(arg(u, k), x, s, ctx == 2 ? 2 : 3);
		return;
		}
	if (is_circ(u))
		{
		if (! tx_coeff(u, x, & c)) { s->ok = 0; return; }
		/* not a polynomial in sin and cos */
		if (ctx != 0 || ! is_head(u, "sin", 1) && ! is_head(u, "cos", 1)) s->denom = 1;
		for (i = 0; i < s->n; i++)
			if (fabs(s->c[i] - c) < 1e-12) break;
		if (i == s->n)
			{
			if (s->n == MAXTX) { s->ok = 0; return; }
			s->frac[s->n] = 0;
			s->c[s->n++] = c;
			}
		/* under a root: sin(2x) = 2 sin cos is a product, cos(2x) a sum */
		if (ctx == 2 && ! is_head(u, "cos", 1)) s->frac[i] = 1;
		return;
		}
	n = term_nargs(u);
	for (k = 0; k < n; k++) tx_scan(arg(u, k), x, s, ctx);
}

static Node * tx_multiple (int sine, int k, Node * w)	/* sin(k w) or cos(k w) */
{
	Node * r = NULL;
	double binom = 1;
	int j;
	for (j = 0; j <= k; j++)
		{
		if (j > 0) binom = binom * (k - j + 1) / j;
		if ((j % 2 == 1) == sine)
			{
			double sg = ((sine ? (j - 1) / 2 : j / 2) % 2) ? -1 : 1;
			Node * t = mk_mul(mk_int(sg * binom),
				mk_mul(mk_pow(mk_f1("cos", tcpy(w)), mk_int(k - j)),
				       mk_pow(mk_f1("sin", tcpy(w)), mk_int(j))));
			r = r ? mk_add(r, t) : t;
			}
		}
	return r;
}

static Node * tx_repl (Node * u, Node * x, TrigExp * s, Node * w)
{
	double c;
	int k, n;
	u = deref(u);
	if (! contains(u, x) || u->type != Func) return tcpy(u);
	if (is_circ(u) && tx_coeff(u, x, & c))
		{
		const char * h = role_of(TERM_HEAD(u));
		int m = (int) floor(fabs(c) / s->g + 0.5);
		double sg = c < 0 ? -1 : 1;		/* sin(-kw) = -sin(kw) */
		Node * sk = mk_mul(mk_int(sg), tx_multiple(1, m, w)), * ck = tx_multiple(0, m, w);
		if (! strcmp(h, "sin")) { delete(ck); return sk; }
		if (! strcmp(h, "cos")) { delete(sk); return ck; }
		if (! strcmp(h, "tan")) return mk_mul(sk, mk_pow(ck, mk_int(-1)));
		if (! strcmp(h, "cot")) return mk_mul(ck, mk_pow(sk, mk_int(-1)));
		if (! strcmp(h, "sec")) { delete(sk); return mk_pow(ck, mk_int(-1)); }
		delete(ck);
		return mk_pow(sk, mk_int(-1));				/* csc */
		}
	n = term_nargs(u);
	{
	Node * args = NULL, ** tail = & args;
	for (k = 0; k < n; k++)
		{
		Node * a = tx_repl(arg(u, k), x, s, w);
		if (k < n - 1) { * tail = mknod(Terms, a, NULL); tail = & (* tail)->r; }
		else * tail = a;
		}
	return mknod(Func, u->l, args);
	}
}

static Node * s_trigexpand (Node * a[], int n, Symbol * f)
{
	TrigExp s;
	double p, q, gp = 0, gq = 1;
	int i;
	Node * w, * r;
	Node * u;
	if (n != 2) return NULL;
	s.n = 0; s.ok = 1; s.denom = 0;
	u = shift_all(a[0]);			/* sec(pi/2 + 2x) = -csc(2x) */
	tx_scan(u, a[1], & s, 0);
	/* only with trig functions in a denominator: products of sin and cos
	 * are left to Rubi's product-to-sum reduction (cos(3x)*cos(5x)) */
	if (! s.ok || s.n < 2 || ! s.denom) { delete(u); return NULL; }
	for (i = 0; i < s.n; i++)		/* g = gcd of the coefficients */
		{
		double x1, y1, t;
		if (! rat_approx(fabs(s.c[i]), & p, & q)) { delete(u); return NULL; }
		x1 = gp; y1 = p;
		while (y1 != 0) { t = fmod(x1, y1); x1 = y1; y1 = t; }
		gp = x1;
		x1 = gq; y1 = q;
		while (y1 != 0) { t = fmod(x1, y1); x1 = y1; y1 = t; }
		gq = gq / x1 * q;
		}
	s.g = gp / gq;
	for (i = 0; i < s.n; i++)
		if (fabs(s.c[i]) / s.g > 12.5			/* too many terms */
		    || (s.frac[i] && fabs(fabs(s.c[i]) - s.g) > 1e-12))	/* sin(2x)^(3/2) */
			{ delete(u); return NULL; }
	w = s.g == 1 ? tcpy(a[1]) : mk_mul(mk_num_ex(s.g, 1), tcpy(a[1]));
	r = tx_repl(u, a[1], & s, w);
	delete(w);
	delete(u);
	return r;
}

static Node * s_removecontent (Node * a[], int n, Symbol * f)	/* Rubi's RemoveContent */
{
	Node * s, * r;
	if (n != 2) return NULL;
	s = pi2_shift(a[0]);
	r = s_freefactors_aux(s ? s : a[0], a[1], 0);		/* without constant factors */
	delete(s);
	if (is_head(r, "+", 2) || is_head(r, "-", 2))
		{
		/* a sum whose first summand (in Mathematica's order the constant)
		 * is negative: -u, as Rubi's RemoveContentAux (ln(1+x^2), not
		 * ln(-1-x^2)) */
		TList l = {0};
		double v;
		int i, neg = 0;
		expand_to(r, & l);
		for (i = 0; i < l.n; i++)
			if (! contains(l.t[i], a[1]) && num_value_r(l.t[i], & v)) { neg = v < 0; break; }
		if (neg)
			{
			for (i = 0; i < l.n; i++) l.t[i] = mk_neg(l.t[i]);
			delete(r);
			return tl_collect(& l);
			}
		tl_free(& l);
		}
	return r;
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
		Node * t;
		if (is_zero(c[k])) { delete(c[k]); continue; }
		if (k == 0)
			t = c[k];
		else if (is_head(c[k], "*", 2) && num_sym(arg(c[k], 0)))
			{
			/* (n*b)*x^k as n*(b*x^k), the form of RubiNorm (else the two
			 * rule sets turn it back and forth) */
			t = mk_mul(tcpy(arg(c[k], 0)),
				mk_mul(tcpy(arg(c[k], 1)), mk_pow(tcpy(x), mk_int(k))));
			delete(c[k]);
			}
		else
			t = mk_mul(c[k], mk_pow(tcpy(x), mk_int(k)));
		s = mk_add(s, t);
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

/* the linear form L = c + d x (c != 0) inside t, if x occurs in t only
 * within L: ln(c (d (e + f x)^p)^q) gives e + f x. NULL otherwise. */
static Node * linear_inner (Node * t, Node * root, Node * x)
{
	Node * lc[MAXDEG], * r;
	int dl, k, i, n;
	t = deref(t);
	if (! t || ! contains(t, x)) return NULL;
	if (is_head(t, "+", 2) && poly_coeffs(t, x, lc, & dl))
		{
		int ok = dl == 1 && ! is_zero(lc[0]);
		for (k = 0; k <= dl; k++) delete(lc[k]);
		if (ok)
			{
			Node * z = mk_int(0), * test = replace(root, t, z);
			ok = ! contains(test, x);
			delete(test); delete(z);
			if (ok) return t;
			}
		}
	if (t->type != Func) return NULL;
	n = term_nargs(t);
	for (i = 0; i < n; i++)
		if ((r = linear_inner(arg(t, i), root, x)) != NULL) return r;
	return NULL;
}

/* the factors for which Rubi's ExpandIntegrand uses ExpandLinearProduct:
 * (a + b log(..(e + f x)..))^n, (a + b F(c + d x))^n with F = arcsin,
 * arccos, arcsinh, arccosh, and F^(e (c + d x)^n) */
static int linear_product_factor (Node * t, Node * x)
{
	t = deref(t);
	if (is_head(t, "^", 2) && ! contains(arg(t, 0), x)) return 1;	/* F^(..) */
	return contains_head(t, "ln") || contains_head(t, "arcsin") || contains_head(t, "arccos")
	       || contains_head(t, "arcsinh") || contains_head(t, "arccosh");
}

/* P(x) * f with a factor f as above, x only in L = e + f x inside it: the sum
 * of e_k L^k f, P(x) written in powers of L (Rubi's ExpandLinearProduct for
 * logarithms, inverse functions and exponentials). NULL if not this form. */
static Node * expand_linear_inner (Node * u, Node * x)
{
	TList l = {0};
	Node * fac = NULL, * lin = NULL, * rest = NULL, * p[MAXDEG], * lc[MAXDEG], * r = NULL;
	double binom;
	int i, j, k, m, deg, dl;
	factors_to(u, & l);
	for (i = 0; i < l.n; i++)
		{
		Node * t = l.t[i];
		if (! fac && contains(t, x) && linear_product_factor(t, x)
		    && (lin = linear_inner(t, t, x)) != NULL)
			{
			fac = t;
			continue;
			}
		rest = rest ? mk_mul(rest, tcpy(t)) : tcpy(t);
		}
	if (! fac || ! rest || ! contains(rest, x) || ! poly_coeffs(rest, x, p, & deg) || deg < 1)
		{
		l.n = 0; tl_free(& l); delete(rest);
		return NULL;
		}
	delete(rest);
	if (! poly_coeffs(lin, x, lc, & dl) || dl != 1)
		{
		for (j = 0; j <= deg; j++) delete(p[j]);
		l.n = 0; tl_free(& l);
		return NULL;
		}
	for (k = 0; k <= deg; k++)		/* e_k as in expand_linear_product */
		{
		Node * e = NULL;
		for (j = k; j <= deg; j++)
			{
			Node * term;
			binom = 1;
			for (m = 1; m <= k; m++) binom = binom * (j - k + m) / m;
			term = mk_mul(mk_int(binom), tcpy(p[j]));
			term = mk_mul(term, mk_pow(tcpy(lc[1]), mk_int(-j)));
			term = mk_mul(term, mk_pow(mk_mul(mk_int(-1), tcpy(lc[0])), mk_int(j - k)));
			e = mk_add(e, term);
			}
		r = mk_add(r, mk_mul(mk_mul(e, mk_pow(tcpy(lin), mk_int(k))), tcpy(fac)));
		}
	for (j = 0; j <= deg; j++) delete(p[j]);
	delete(lc[0]); delete(lc[1]);
	l.n = 0; tl_free(& l);
	return r;
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
		    && ! (num_value(arg(t, 1), & e) && e >= 0 && e == floor(e))
		    && poly_coeffs(arg(t, 0), x, lc, & dl))
			{
			if (dl == 1)
				{
				lin = arg(t, 0);
				expo = arg(t, 1);
				continue;
				}
			for (k = 0; k <= dl; k++) delete(lc[k]);
			}
		rest = rest ? mk_mul(rest, tcpy(t)) : tcpy(t);	/* also other powers */
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

/* ---- partial fractions (Mathematica's Apart, see apart.c) ---- */

/* u as a rational function of x with exact coefficients, or NULL */
static RatFun * to_ratfun (Node * u, Node * x)
{
	Symbol * s;
	Node * r;
	void * q;
	double e;
	u = deref(u);
	if (! u) return NULL;
	if (tequal(u, x)) return rf_var();
	if ((s = num_sym(u)) != NULL)
		return (q = exact_to_rat(s)) != NULL ? rf_const(q) : NULL;
	if (u->type != Func) return NULL;
	if (! contains(u, x))			/* a calculable number like 1/3 */
		{
		if (! (r = calkulate(u))) return NULL;
		q = exact_to_rat((Symbol *) r);
		delnum((Symbol *) r, TRUE);
		return q ? rf_const(q) : NULL;
		}
	if (is_head(u, "+", 2))
		return rf_add(to_ratfun(arg(u, 0), x), to_ratfun(arg(u, 1), x));
	if (is_head(u, "-", 2))
		return rf_add(to_ratfun(arg(u, 0), x),
			rf_mul(rf_const(rat_from_ll(-1, 1)), to_ratfun(arg(u, 1), x)));
	if (is_head(u, "-", 1))
		return rf_mul(rf_const(rat_from_ll(-1, 1)), to_ratfun(arg(u, 0), x));
	if (is_head(u, "*", 2))
		return rf_mul(to_ratfun(arg(u, 0), x), to_ratfun(arg(u, 1), x));
	if (is_head(u, "/", 2))
		return rf_mul(to_ratfun(arg(u, 0), x), rf_pow(to_ratfun(arg(u, 1), x), -1));
	if (is_head(u, "mi", 1))
		return rf_pow(to_ratfun(arg(u, 0), x), -1);
	if (is_head(u, "^", 2) && ! contains(arg(u, 1), x) && num_value(arg(u, 1), & e)
	    && e == floor(e) && fabs(e) <= MAXDEG)
		return rf_pow(to_ratfun(arg(u, 0), x), (int) e);
	return NULL;
}

static Node * qpoly_term (QPoly * p, Node * x)
{
	Node * c[MAXDEG];
	int k;
	if (p->deg < 0) return mk_int(0);
	for (k = 0; k <= p->deg; k++)
		c[k] = mknod(Const, (Node *) make_exact_rat(cpy_rat(p->c[k])), NULL);
	return poly_build(c, p->deg, x);
}

/* the partial fractions of the rational function u, if they are a sum;
 * else NULL */
static Node * apart_term (Node * u, Node * x)
{
	RatFun * f;
	QPoly quot;
	ApartTerm * t;
	Node * r = NULL;
	int n, i;
	if (! exact_numbers() || ! (f = to_ratfun(u, x))) return NULL;
	if ((n = rf_apart(f, & quot, & t)) < 0) return NULL;
	if (n + (quot.deg >= 0) >= 2)
		{
		if (quot.deg >= 0) r = qpoly_term(& quot, x);
		for (i = 0; i < n; i++)		/* coef * (num * base^-k), flat as in Mathematica */
			{
			Node * s = mk_pow(qpoly_term(& t[i].base, x), mk_int(-t[i].k));
			Node * c = mknod(Const, (Node *) make_exact_rat(cpy_rat(t[i].coef)), NULL);
			if (t[i].num.deg > 0) s = mk_mul(qpoly_term(& t[i].num, x), s);
			if (! mpq_is_one(t[i].coef)) s = mk_mul(c, s); else delete(c);
			r = mk_add(r, s);
			}
		}
	qpoly_clear(& quot);
	apart_free(t, n);
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
	Node * coef = NULL;
	double c;
	if (! is_head(a[0], "*", 2)) return normpoly(a[0], a[1]);
	factors_to(a[0], & l);
	for (i = 0; i < l.n; i++)
		{
		Node * t = normpoly_factor(l.t[i], a[1]);
		/* numbers to the front, also the content of a polynomial factor:
		 * c*(p*u), not (c*p)*u, so that rules for constant factors match */
		if (num_sym(t))
			{
			coef = coef ? mk_mul(coef, t) : t;
			continue;
			}
		if (is_head(t, "*", 2) && num_sym(arg(t, 0)))
			{
			Node * p = tcpy(arg(t, 1));
			coef = coef ? mk_mul(coef, tcpy(arg(t, 0))) : tcpy(arg(t, 0));
			delete(t);
			t = p;
			}
		r = r ? mk_mul(r, t) : t;
		}
	l.n = 0;	/* the factors belong to a[0] */
	tl_free(& l);
	if (is_head(r, "*", 2))		/* x*x^-1 = 1, as Mathematica simplifies */
		{
		Node * s = simp_product(r);
		delete(r);
		r = s;
		}
	if (! coef) return r;
	if (! r) return coef;
	if (num_value(coef, & c) && c == 1) { delete(coef); return r; }
	return mk_mul(coef, r);
}

static Node * s_rules (Node * a[], int n, Symbol * f);
static Node * collect_deep (Node * u);

/* derivative of u with respect to x, or NULL for unknown functions: the
 * library's function deriv, defined by rules (inc/helpers) */
static Node * deriv (Node * u, Node * x)
{
	Symbol * f = role_find("deriv");
	Node * a[2], * r;
	if (! f) return NULL;
	a[0] = u; a[1] = x;
	r = s_rules(a, 2, f);
	if (r && contains_head(r, "D")) { delete(r); return NULL; }	/* unknown function */
	if (r)				/* 0+1+4*(2*x) from the rules: collected */
		{
		Node * c = collect_deep(r);
		delete(r);
		r = c;
		}
	return r;
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

/* like summands combined in every sum of u, e.g. 1/(1/x + x/2 - x/2) = x */
static Node * collect_deep (Node * u)
{
	Node * args = NULL, ** tail = & args, * r;
	int k, n;
	u = deref(u);
	if (! u || u->type != Func) return tcpy(u);
	n = term_nargs(u);
	for (k = 0; k < n; k++)
		{
		Node * c = collect_deep(arg(u, k));
		if (k < n - 1)
			{
			* tail = mknod(Terms, c, NULL);
			tail = & (* tail)->r;
			}
		else
			* tail = c;
		}
	r = mknod(Func, u->l, args);
	if (is_head(r, "+", 2) || is_head(r, "-", 2))
		{
		TList l = {0};
		expand_to(r, & l);	/* (1/2)*(t+1/t) - (1/2)*(t-1/t) = 1/t */
		delete(r);
		r = tl_collect(& l);
		}
	return r;
}


/* ---- normform(u): the final form of a result, in one pass ----
 * Instead of the general simplification All, which sorts and simplifies a
 * large result one rule step at a time (24000 steps for a polynomial of 231
 * terms). Three passes:
 *   canonical:  a - b = a + (-1)*b,  a/b = a*b^-1,  mi(a) = a^-1,  -a = (-1)*a
 *   collected:  products with a sum as factor distributed (not powers of
 *               sums), like summands combined in every sum
 *   printed:    the positive summands first, then "- ..."; negative powers
 *               into a denominator, c*A/B^k; a negative product as -(...)
 * The result is the same when normform is applied again. */

static Node * nf_rebuild (Node * u, Node * (* fn) (Node *))	/* fn on the arguments */
{
	Node * args = NULL, ** tail = & args;
	int k, n = term_nargs(u);
	for (k = 0; k < n; k++)
		{
		Node * c = fn(arg(u, k));
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

static Node * nf_canon (Node * u)
{
	Node * r, * a0, * a1;
	u = deref(u);
	if (! u || u->type != Func) return tcpy(u);
	r = nf_rebuild(u, nf_canon);
	if (is_head(r, "-", 2) || is_head(r, "/", 2))
		{
		int minus = is_head(r, "-", 2);
		a0 = tcpy(arg(r, 0));
		a1 = tcpy(arg(r, 1));
		delete(r);
		return minus ? mk_add(a0, mk_neg(a1)) : mk_mul(a0, mk_pow(a1, mk_int(-1)));
		}
	if (is_head(r, "-", 1) || is_head(r, "mi", 1))
		{
		int minus = is_head(r, "-", 1);
		a0 = tcpy(arg(r, 0));
		delete(r);
		return minus ? mk_neg(a0) : mk_pow(a0, mk_int(-1));
		}
	{
	double e;			/* (c*u)^n = c^n u^n: (-sin(x))^3 = -sin(x)^3 */
	if (is_head(r, "^", 2) && is_num(arg(r, 1), & e) && e == floor(e)
	    && is_head(arg(r, 0), "*", 2) && num_sym(arg(arg(r, 0), 0)))
		{
		Node * c = mk_pow(tcpy(arg(arg(r, 0), 0)), tcpy(arg(r, 1)));
		Node * p = mk_pow(tcpy(arg(arg(r, 0), 1)), tcpy(arg(r, 1)));
		delete(r);
		return mk_mul(c, p);
		}
	}
	return r;
}

/* the summands of t, with numeric factors distributed: 3*(a - 2*(b + c))
 * gives 3*a, -6*b, -6*c (c: the factor so far, or NULL) */
static void nf_summands (Node * t, Node * c, TList * out)
{
	t = deref(t);
	if (is_head(t, "+", 2))
		{
		nf_summands(arg(t, 0), c, out);
		nf_summands(arg(t, 1), c, out);
		return;
		}
	if (is_head(t, "*", 2))		/* a product with a sum as factor: distributed */
		{
		TList l = {0};
		int i, k = -1;
		factors_to(t, & l);
		for (i = 0; i < l.n && k < 0; i++)
			if (is_head(l.t[i], "+", 2)) k = i;
		if (k >= 0)
			{
			Node * c2 = c ? tcpy(c) : NULL;
			for (i = 0; i < l.n; i++)
				if (i != k) c2 = c2 ? mk_mul(c2, tcpy(l.t[i])) : tcpy(l.t[i]);
			nf_summands(l.t[k], c2, out);
			delete(c2);
			l.n = 0;		/* the factors belong to t */
			tl_free(& l);
			return;
			}
		l.n = 0;
		tl_free(& l);
		}
	tl_add(out, c ? mk_mul(tcpy(c), tcpy(t)) : tcpy(t));
}

static Node * nf_collect (Node * u)
{
	Node * r;
	u = deref(u);
	if (! u || u->type != Func) return tcpy(u);
	r = nf_rebuild(u, nf_collect);
	if (is_head(r, "+", 2) || is_head(r, "*", 2))
		{
		TList l = {0};
		nf_summands(r, NULL, & l);
		delete(r);
		r = tl_collect(& l);
		}
	return r;
}

static Node * nf_pretty (Node * u);

static int neg_power (Node * t, double * e)	/* b^e with a number e < 0 */
{
	return is_head(t, "^", 2) && is_num(arg(t, 1), e) && * e < 0;
}

/* u without its sign (*neg: the numeric factor was negative), with negative
 * powers as a denominator */
static Node * nf_unsigned (Node * u, int * neg)
{
	TList l = {0}, nl = {0};
	Node * num = NULL, * den = NULL, * c = NULL;
	double v, e;
	int i;
	u = deref(u);
	* neg = 0;
	if (is_num(u, & v))
		{
		if (v < 0) { * neg = 1; return mk_mul(mk_int(-1), tcpy(u)); }
		return tcpy(u);
		}
	if (! is_head(u, "*", 2) && ! neg_power(u, & e)) return nf_pretty(u);
	factors_to(u, & l);
	for (i = 0; i < l.n; i++)
		{
		Node * t = deref(l.t[i]);
		if (num_sym(t))
			{
			c = c ? mk_mul(c, tcpy(t)) : tcpy(t);
			continue;
			}
		if (neg_power(t, & e))
			{
			Node * p = nf_pretty(arg(t, 0));
			if (e != -1) p = mk_pow(p, mk_num_ex(-e, is_exact(arg(t, 1))));
			den = den ? mk_mul(den, p) : p;
			continue;
			}
		tl_add(& nl, nf_pretty(t));
		}
	{				/* x^2*sin(x), not sin(x)*x^2: atoms and their powers first */
	int j, m = 0;
	for (j = 0; j < nl.n; j++)
		{
		Node * t = deref(nl.t[j]);
		if (atom_sym(t) || (is_head(t, "^", 2) && atom_sym(deref(arg(t, 0)))))
			{
			Node * h = nl.t[j];
			int q;
			for (q = j; q > m; q--) nl.t[q] = nl.t[q - 1];
			nl.t[m++] = h;
			}
		}
	}
	l.n = 0;			/* the factors belong to u */
	tl_free(& l);
	if (c && is_num(c, & v) && v < 0) { * neg = 1; c = mk_mul(mk_int(-1), c); }
	if (c && is_num(c, & v) && v == 1) { delete(c); c = NULL; }
	num = c;			/* c * f1 * f2 ..., built from the left: no parentheses */
	for (i = 0; i < nl.n; i++) num = num ? mk_f2("*", num, nl.t[i]) : nl.t[i];
	nl.n = 0;
	tl_free(& nl);
	if (! num) num = mk_int(1);
	return den ? mk_f2("/", num, den) : num;
}

static Node * nf_pretty (Node * u)
{
	double e, v;
	u = deref(u);
	if (! u || u->type != Func) return tcpy(u);
	if (is_head(u, "+", 2))
		{
		TList l = {0}, negs = {0};
		Node * r = NULL;
		int i, neg;
		summands_to(u, & l, 0);
		for (i = 0; i < l.n; i++)		/* positive summands first */
			{
			Node * s = nf_unsigned(l.t[i], & neg);
			if (neg) tl_add(& negs, s);
			else r = r ? mk_f2("+", r, s) : s;
			}
		for (i = 0; i < negs.n; i++)
			r = r ? mk_f2("-", r, negs.t[i]) : mk_f1("-", negs.t[i]);
		negs.n = 0;
		tl_free(& negs);
		tl_free(& l);
		return r ? r : mk_int(0);
		}
	if (is_head(u, "*", 2) || neg_power(u, & e) || (is_num(u, & v) && v < 0))
		{
		int neg;
		Node * s = nf_unsigned(u, & neg);
		return neg ? mk_f1("-", s) : s;
		}
	return nf_rebuild(u, nf_pretty);
}

static Node * s_normform (Node * a[], int n, Symbol * f)
{
	Node * c, * k, * r;
	if (n != 1) return NULL;
	c = nf_canon(a[0]);
	k = nf_collect(c);
	delete(c);
	r = nf_pretty(k);
	delete(k);
	return r;
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

/* has u (in x) an antiderivative without inverse functions? Rubi's IntHide
 * integrates, inthide leaves Int(u,x). For a rational function the partial
 * fractions tell: c/b^1 gives ln or arctan, and so does p/b^k with b of
 * degree 2 or more unless p has the degree of b' (x/(1+x^2)^2). Other
 * integrands count as free, as Rubi's integration by parts is valid anyway. */
/* tan, cot, sec, csc (also hyperbolic) or a negative power of sin, cos, ...
 * of x: their integrals contain ln or arctan */
static int has_log_trig (Node * u, Node * x)
{
	static const char * t[] = { "tan", "cot", "sec", "csc", "tanh", "coth", "sech", "csch", NULL };
	static const char * sc[] = { "sin", "cos", "sinh", "cosh", NULL };
	double e;
	int i, k, n;
	u = deref(u);
	if (! u || u->type != Func || ! contains(u, x)) return 0;
	for (i = 0; t[i]; i++)
		if (is_head(u, t[i], 1)) return 1;
	if (is_head(u, "^", 2) && num_value(arg(u, 1), & e) && e < 0)
		for (i = 0; sc[i]; i++)
			if (is_head(arg(u, 0), sc[i], 1)) return 1;
	n = term_nargs(u);
	for (k = 0; k < n; k++)
		if (has_log_trig(arg(u, k), x)) return 1;
	return 0;
}

static int int_invfree (Node * u, Node * x)
{
	RatFun * f;
	QPoly quot;
	ApartTerm * t;
	int n, i, ok = 1;
	if (has_log_trig(u, x)) return 0;
	if (! exact_numbers() || ! (f = to_ratfun(u, x))) return 1;
	if ((n = rf_apart(f, & quot, & t)) < 0) return 1;	/* a polynomial */
	for (i = 0; i < n; i++)
		if (t[i].k == 1 || (t[i].base.deg >= 2 && t[i].num.deg != t[i].base.deg - 1))
			ok = 0;
	qpoly_clear(& quot);
	apart_free(t, n);
	return ok;
}

static int invfunfreeq (Node * u, Node * x)
{
	static const char * inv[] = { "ln", "arcsin", "arccos", "arctan", "arccot", "arcsec",
		"arccsc", "arcsinh", "arccosh", "arctanh", "arccoth", "arcsech", "arccsch",
		"polylog", "Int", "D", "deriv", "subst", "hyp2f1", "appellf1", NULL };
	int i, k, n;
	u = deref(u);
	if (! u || u->type != Func) return 1;
	if (is_head(u, "Int", 2) && tequal(arg(u, 1), x))
		return int_invfree(arg(u, 0), x);
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
	h = role_of(TERM_HEAD(u));
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
	if (num_value_r(a[1], & v) && v < 0 && ! (num_value_r(a[0], & u) && u < 0)) return mk_bool(1, f);
	if (num_value_r(a[0], & u) && u < 0 && ! (num_value_r(a[1], & v) && v < 0)) return mk_bool(0, f);
	ra[1] = mk_int(2);
	ra[0] = a[0]; qu = s_rt(ra, 2, f);
	ra[0] = a[1]; qv = s_rt(ra, 2, f);
	delete(ra[1]);
	if (! qu || ! qv) { delete(qu); delete(qv); return mk_bool(0, f); }
	iu = is_integer_num(qu, & su); iv = is_integer_num(qv, & sv);
	nu = is_exact(qu); nv = is_exact(qv);
	if (iu) r = iv ? su < sv : 1;
	else if (iv) r = 0;
	else if (nu) { num_value_r(qu, & su); r = nv ? (num_value_r(qv, & sv), su < sv) : 1; }
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
	if (num_value_r(v, & e)) return e >= 0;
	s = arg_sort(v);
	if (s && role_find("nonneg") && sort_dist(s, (Node *) role_find("nonneg")) >= 0) return 1;
	if (is_head(v, "sqrt", 1) || is_head(v, "exp", 1) || is_head(v, "abs", 1)) return 1;
	if (is_head(v, "^", 2) && num_value(arg(v, 1), & e))
		{
		if (e == floor(e)) return fmod(e, 2.0) == 0 || nonnegq(arg(v, 0));
		if (rat_approx(e, & p, & q) && fmod(q, 2.0) == 0) return 1;	/* even root */
		return nonnegq(arg(v, 0));
		}
	if (is_head(v, "^", 2) && num_value_r(arg(v, 0), & e) && e > 0) return 1;	/* e^u, 2^u */
	if (is_head(v, "^", 2) && (s = arg_sort(arg(v, 0))) && role_find("nonneg")
	    && sort_dist(s, (Node *) role_find("nonneg")) >= 0) return 1;	/* eE^u */
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
	Symbol * xnn = role_find("Xnn"), * xre = role_find("Xre"), * ws = NULL;
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
	Symbol * es = role_find("eE");	/* symbolic e of the integration */
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
		const char * h = role_of(TERM_HEAD(u));
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

/* ---- substexp(u, x): Rubi's substitution for functions of F^(c x) ----
 * Rule 2.3 of Rubi (FunctionOfExponential): if u is a function of powers
 * F^(c_i x + d_i) with a constant F and of hyperbolic functions of linear
 * arguments, and an exponential occurs explicitly, then with g the greatest
 * common divisor of the c_i and v = F^(g x)
 *     Int(u, x) = 1/(g ln F) * Subst[Int[w(x)/x, x], x, v],
 * where w is u with F^(c x + d) replaced by F^d x^(c/g) and sinh(c x + d)
 * by (t - 1/t)/2 with t = e^d x^(c/g), ... The coefficients c_i must be
 * numbers, or all the same term. Not applicable: NULL. */

#define MAXEXPO 32
typedef struct {
	Node * base;		/* F (a node of u, or ee) */
	Node * ee;		/* the constant eE */
	int n, flag;		/* coefficients; an explicit exponential occurs */
	Node * c[MAXEXPO];
} ExpoState;

static const char * hyp_heads[] = { "sinh", "cosh", "tanh", "coth", "sech", "csch", NULL };

static int is_hyp (Node * u)
{
	int i;
	for (i = 0; hyp_heads[i]; i++)
		if (is_head(u, hyp_heads[i], 1)) return 1;
	return 0;
}

static int linear_parts (Node * v, Node * x, Node ** c0, Node ** c1)	/* v = c0 + c1 x */
{
	Node * c[MAXDEG];
	int deg, k;
	if (! poly_coeffs(v, x, c, & deg)) return 0;
	if (deg != 1)
		{
		for (k = 0; k <= deg; k++) delete(c[k]);
		return 0;
		}
	* c0 = c[0];
	* c1 = c[1];
	return 1;
}

static int expo_add (ExpoState * s, Node * base, Node * v, Node * x)
{
	Node * c0, * c1;
	if (! base || (s->base && ! tequal(s->base, base))) return 0;
	if (s->n == MAXEXPO || ! linear_parts(v, x, & c0, & c1)) return 0;
	s->base = base;
	delete(c0);
	s->c[s->n++] = c1;
	return 1;
}

static int expo_test (Node * u, Node * x, ExpoState * s)
{
	int k, n;
	double dd;
	u = deref(u);
	if (! contains(u, x)) return 1;
	if (tequal(u, x) || u->type != Func) return 0;
	if (is_head(u, "Int", -1) || is_head(u, "D", -1) || is_head(u, "deriv", -1)) return 0;
	/* (e^x - e^-x)^n with symbolic n: the result would need complex values
	 * ((1 + a^x)^n with one exponential summand is fine) */
	if (is_head(u, "^", 2) && contains(arg(u, 0), x) && ! num_sym(arg(u, 1))
	    && ! num_value(arg(u, 1), & dd))
		{
		TList l = {0};
		int i, ne = 0;
		summands_to(arg(u, 0), & l, 0);
		for (i = 0; i < l.n; i++)
			if (contains(l.t[i], x)) ne++;
		tl_free(& l);
		if (ne > 1) return 0;
		}
	if (is_head(u, "^", 2) && ! contains(arg(u, 0), x))
		{
		s->flag = 1;
		return expo_add(s, arg(u, 0), arg(u, 1), x);
		}
	if (is_hyp(u)) return expo_add(s, s->ee, arg(u, 0), x);
	n = term_nargs(u);
	for (k = 0; k < n; k++)
		if (! expo_test(arg(u, k), x, s)) return 0;
	return 1;
}

/* g and the factors k_i = c_i/g; 0 if the c_i have no common measure */
static Node * expo_gcd (ExpoState * s)
{
	double p, q, gp = 0, gq = 1, v;
	int i;
	for (i = 0; i < s->n; i++)
		if (! num_value(s->c[i], & v) || ! rat_approx(fabs(v), & p, & q)) break;
		else
			{
			double a = gp, b = p, t;
			while (b != 0) { t = fmod(a, b); a = b; b = t; }	/* gcd of numerators */
			gp = a;
			a = gq; b = q;
			while (b != 0) { t = fmod(a, b); a = b; b = t; }
			gq = gq / a * q;				/* lcm of denominators */
			}
	if (i == s->n) return gp > 0 ? mk_num_ex(gp / gq, 1) : NULL;
	for (i = 1; i < s->n; i++)		/* symbolic: all the same */
		if (! tequal(s->c[i], s->c[0])) return NULL;
	return tcpy(s->c[0]);
}

static Node * expo_k (Node * c, Node * g)	/* c/g */
{
	double a, b;
	if (num_value(c, & a) && num_value(g, & b)) return mk_num_ex(a / b, 1);
	return mk_int(1);			/* symbolic: c = g */
}

static Node * expo_repl (Node * u, Node * x, Node * g, ExpoState * s)
{
	Node * c0, * c1, * t, * r;
	int k, n;
	u = deref(u);
	if (! contains(u, x)) return tcpy(u);
	if ((is_head(u, "^", 2) && ! contains(arg(u, 0), x)) || is_hyp(u))
		{
		Node * base = is_hyp(u) ? s->ee : arg(u, 0);
		linear_parts(is_hyp(u) ? arg(u, 0) : arg(u, 1), x, & c0, & c1);
		t = mk_pow(tcpy(x), expo_k(c1, g));		/* F^(c0 + c1 x) = F^c0 x^k */
		delete(c1);
		if (is_zero(c0)) delete(c0);
		else t = mk_mul(mk_pow(tcpy(base), c0), t);
		if (! is_hyp(u)) return t;
		{
		const char * h = role_of(TERM_HEAD(u));
		Node * half = mk_num_ex(0.5, 1), * ti = mk_pow(tcpy(t), mk_int(-1));
		if (! strcmp(h, "sinh")) r = mk_mul(half, mk_add(t, mk_neg(ti)));
		else if (! strcmp(h, "cosh")) r = mk_mul(half, mk_add(t, ti));
		else
			{
			Node * plus = mk_add(tcpy(t), tcpy(ti)), * minus = mk_add(t, mk_neg(ti));
			delete(half);
			if (! strcmp(h, "tanh")) r = mk_mul(minus, mk_pow(plus, mk_int(-1)));
			else if (! strcmp(h, "coth")) r = mk_mul(plus, mk_pow(minus, mk_int(-1)));
			else if (! strcmp(h, "sech")) { delete(minus); r = mk_mul(mk_int(2), mk_pow(plus, mk_int(-1))); }
			else { delete(plus); r = mk_mul(mk_int(2), mk_pow(minus, mk_int(-1))); }
			}
		return r;
		}
		}
	n = term_nargs(u);
	{
	Node * args = NULL, ** tail = & args;
	for (k = 0; k < n; k++)
		{
		Node * c = expo_repl(arg(u, k), x, g, s);
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

/* functionofexponentialq(u, x): Rubi's FunctionOfExponentialQ, the test of
 * substexp: u is a function of F^(c x), with an explicit exponential */
static Node * s_functionofexponentialq (Node * a[], int n, Symbol * f)
{
	ExpoState s = {0};
	Symbol * es = role_find("eE");
	int i, ok;
	if (n != 2) return NULL;
	s.ee = es ? mknod(Const, (Node *) es, NULL) : NULL;
	ok = expo_test(a[0], a[1], & s) && s.flag && s.n > 0;
	for (i = 0; i < s.n; i++) delete(s.c[i]);
	delete(s.ee);
	return mk_bool(ok, f);
}

static Node * s_substexp (Node * a[], int n, Symbol * f)
{
	ExpoState s = {0};
	Symbol * es = role_find("eE");
	Node * g = NULL, * w, * v, * fac, * r = NULL;
	int i;
	if (n != 2) return NULL;
	s.ee = es ? mknod(Const, (Node *) es, NULL) : NULL;
	if (expo_test(a[0], a[1], & s) && s.flag && s.n > 0 && (g = expo_gcd(& s)))
		{
		Node * t = expo_repl(a[0], a[1], g, & s);
		w = mk_mul(collect_deep(t), mk_pow(tcpy(a[1]), mk_int(-1)));	/* SimplifyIntegrand */
		delete(t);
		v = mk_pow(tcpy(s.base), mk_mul(tcpy(g), tcpy(a[1])));
		if (s.ee && tequal(s.base, s.ee))			/* 1/(g ln F) */
			fac = mk_pow(tcpy(g), mk_int(-1));
		else
			fac = mk_pow(mk_mul(tcpy(g), mk_f1("ln", tcpy(s.base))), mk_int(-1));
		r = mk_mul(fac, mk_f3("intsubst", w, tcpy(a[1]), v));
		delete(g);
		}
	for (i = 0; i < s.n; i++) delete(s.c[i]);
	delete(s.ee);
	return r;
}

/* ---- binomsum(u, x): Rubi 1.1.3.1/2, x^m/(a+b*x^n) by partial fractions ----
 * For an odd n, or n = 2 mod 4, and 0 <= m < n-1: with r/s = Rt[a/b, n]
 * (or Rt[-a/b, n] if a/b < 0) the denominator splits into linear and
 * quadratic factors with the coefficients cos(j*pi/n). Rubi writes these
 * rules with Module, CompoundExpression and Sum; here they are one helper
 * that gives c * (sum of the integrals), or NULL if u has not that form. */

static Node * cos_pi (long p, long q)	/* cos(p/q*pi), exact for q = 1..6 */
{
	long g, a = labs(p), b = q;
	Node * r5;
	Symbol * ps;
	while (b) { long t = a % b; a = b; b = t; }
	g = a ? a : 1;
	p /= g; q /= g;
	p %= 2 * q; if (p < 0) p += 2 * q;	/* p/q in [0, 2) */
	if (p > q) p = 2 * q - p;		/* cos(pi*(2-t)) = cos(pi*t) */
	switch (q)
		{
		case 1: return mk_int(p == 0 ? 1 : -1);
		case 2: return mk_int(0);
		case 3: return mk_num_ex(p == 1 ? 0.5 : -0.5, 1);
		case 4: return mk_mul(mk_int(p == 1 ? 1 : -1), mk_pow(mk_int(2), mk_num_ex(-0.5, 1)));
		case 6: return mk_mul(mk_num_ex(p == 1 ? 0.5 : -0.5, 1), mk_pow(mk_int(3), mk_num_ex(0.5, 1)));
		case 5:
			r5 = mk_pow(mk_int(5), mk_num_ex(0.5, 1));
			if (p == 1) return mk_mul(mk_num_ex(0.25, 1), mk_add(mk_int(1), r5));
			if (p == 2) return mk_mul(mk_num_ex(0.25, 1), mk_add(r5, mk_int(-1)));
			if (p == 3) return mk_mul(mk_num_ex(0.25, 1), mk_add(mk_int(1), mk_neg(r5)));
			return mk_mul(mk_num_ex(-0.25, 1), mk_add(mk_int(1), r5));
		}
	ps = role_find("pi");
	if (! ps) return mk_num(cos(M_PI * p / q));
	return mk_f1("cos", mk_mul(mk_num_ex((double) p / q, 1), mknod(Const, (Node *) ps, NULL)));
}

/* Int[(r*cm + sg*s*cm1*x)/(r^2 + sg*2*r*s*c1*x + s^2*x^2), x] (takes cm, cm1, c1) */
static Node * bs_quad (Node * r, Node * s, Node * cm, Node * cm1, Node * c1, int sg, int sgq, Node * x)
{
	Node * num = mk_add(mk_mul(tcpy(r), cm), mk_mul(mk_int(sg), mk_mul(mk_mul(tcpy(s), cm1), tcpy(x))));
	Node * den = mk_add(mk_add(mk_pow(tcpy(r), mk_int(2)),
	                           mk_mul(mk_int(2 * sgq), mk_mul(mk_mul(mk_mul(tcpy(r), tcpy(s)), c1), tcpy(x)))),
	                    mk_mul(mk_pow(tcpy(s), mk_int(2)), mk_pow(tcpy(x), mk_int(2))));
	return mk_f2("Int", mk_mul(num, mk_pow(den, mk_int(-1))), tcpy(x));
}

static Node * s_binomsum (Node * a[], int n, Symbol * f)
{
	Node * x, * num, * den, * c = NULL, * pa = NULL, * pb = NULL, * pn = NULL;
	Node * q = NULL, * r = NULL, * s = NULL, * fac, * sum = NULL, * lin, * res = NULL, * ra[2];
	double m, dn;
	long nn, mm, k;
	int pos;
	if (n != 2) return NULL;
	x = a[1];
	num = numden(a[0], 0);
	den = numden(a[0], 1);
	if (! monomial(num, x, & c, & m) || m != floor(m) || m < 0
	    || ! bparts(den, x, & pa, & pb, & pn) || ! is_num(pn, & dn) || dn != floor(dn))
		goto out;
	nn = (long) dn; mm = (long) m;
	if (mm >= nn - 1) goto out;
	if (! ((nn % 2 == 1 && nn >= (mm > 0 ? 3 : 5)) || (nn % 4 == 2 && nn >= 6 && mm % 2 == 0)))
		goto out;
	{
	Node * ab = mk_mul(tcpy(pa), mk_pow(tcpy(pb), mk_int(-1)));
	pos = posaux(ab);
	ra[0] = pos ? ab : mk_neg(ab);
	ra[1] = mk_int(nn);
	q = s_rt(ra, 2, f);
	delete(ra[0]); delete(ra[1]);
	}
	if (! q || term_has_nan(q)) goto out;
	r = numden(q, 0);
	s = numden(q, 1);
	/* fac = 2*r^(m+1)/(a*n*s^m) */
	fac = mk_mul(mk_mul(mk_int(2), mk_pow(tcpy(r), mk_int(mm + 1))),
	             mk_pow(mk_mul(mk_mul(tcpy(pa), mk_int(nn)), mk_pow(tcpy(s), mk_int(mm))), mk_int(-1)));
	if (nn % 2 == 1)
		{
		for (k = 1; k <= (nn - 1) / 2; k++)
			{
			long j = 2 * k - 1;
			Node * t = pos ? bs_quad(r, s, cos_pi(j * mm, nn), cos_pi(j * (mm + 1), nn), cos_pi(j, nn), -1, -1, x)
			               : bs_quad(r, s, cos_pi(j * mm, nn), cos_pi(j * (mm + 1), nn), cos_pi(j, nn), 1, 1, x);
			sum = sum ? mk_add(sum, t) : t;
			}
		/* pos: -(-r)^(m+1)/(a n s^m) Int[1/(r+s x)] + fac*sum;
		 * neg: r^(m+1)/(a n s^m) Int[1/(r-s x)] - 2(-r)^(m+1)/(a n s^m) sum */
		lin = mk_f2("Int", mk_pow(mk_add(tcpy(r), mk_mul(mk_int(pos ? 1 : -1), mk_mul(tcpy(s), tcpy(x)))), mk_int(-1)), tcpy(x));
		{
		/* separate statements: the constructors take (and may free) their
		 * arguments, and C does not fix the order of evaluation */
		Node * base = mk_pow(mk_mul(mk_mul(tcpy(pa), mk_int(nn)), mk_pow(tcpy(s), mk_int(mm))), mk_int(-1));
		Node * c1, * c2;
		if (pos)
			{
			c1 = mk_mul(mk_int(-1), mk_mul(mk_pow(mk_neg(tcpy(r)), mk_int(mm + 1)), base));
			c2 = fac;
			}
		else
			{
			c1 = mk_mul(mk_pow(tcpy(r), mk_int(mm + 1)), tcpy(base));
			c2 = mk_mul(mk_mul(mk_int(-2), mk_pow(mk_neg(tcpy(r)), mk_int(mm + 1))), base);
			delete(fac);
			}
		res = mk_add(mk_mul(c1, lin), mk_mul(c2, sum));
		}
		}
	else
		{
		for (k = 1; k <= (nn - 2) / 4; k++)
			{
			long j = pos ? 2 * k - 1 : 2 * k;
			Node * t1 = bs_quad(r, s, cos_pi(j * mm, nn), cos_pi(j * (mm + 1), nn), cos_pi(j, nn), -1, -1, x);
			Node * t2 = bs_quad(r, s, cos_pi(j * mm, nn), cos_pi(j * (mm + 1), nn), cos_pi(j, nn), 1, 1, x);
			Node * t = mk_add(t1, t2);
			sum = sum ? mk_add(sum, t) : t;
			}
		/* pos: 2(-1)^(m/2) r^(m+2)/(a n s^m) Int[1/(r^2+s^2 x^2)]; neg: 2 r^(m+2)/(a n s^m) Int[1/(r^2-s^2 x^2)] */
		lin = mk_f2("Int", mk_pow(mk_add(mk_pow(tcpy(r), mk_int(2)),
		                                 mk_mul(mk_int(pos ? 1 : -1), mk_mul(mk_pow(tcpy(s), mk_int(2)), mk_pow(tcpy(x), mk_int(2))))),
		                          mk_int(-1)), tcpy(x));
		res = mk_add(mk_mul(mk_mul(mk_mul(mk_int(pos && (mm / 2) % 2 ? -2 : 2), mk_pow(tcpy(r), mk_int(mm + 2))),
		                           mk_pow(mk_mul(mk_mul(tcpy(pa), mk_int(nn)), mk_pow(tcpy(s), mk_int(mm))), mk_int(-1))), lin),
		             mk_mul(fac, sum));
		}
	res = mk_mul(tcpy(c), res);
out:
	delete(num); delete(den); delete(c); delete(pa); delete(pb); delete(pn);
	delete(q); delete(r); delete(s);
	return res;
}

/* ---- functionofq(v, u, x [, pure]), substfor(h, v, u, x) ----
 * Rubi's FunctionOfQ and SubstFor: u is a function of v (in x) if every
 * occurrence of x in u lies in v. For v = d*g(w) with a trig or hyperbolic
 * function g, the other functions of the same w also count where they are
 * functions of g: with s = sin(w), csc = 1/s, cos^(2m) = (1-s^2)^m,
 * tan^(2m) = s^(2m) (1-s^2)^-m, ... ("pure": only g and 1/g).
 * substfor(h, v, u, x) is h*u with v replaced by x; NULL if u is no
 * function of v. */

typedef struct { const char * h; int dir, pexp, a; } TrigRel;	/* h^2m = P^(pexp m) g^(2 a m) */
static const struct { const char * g; int c0, c2; TrigRel rel[6]; } trig_fam[] = {
	{ "sin", 1, -1, { {"sin",1,0,0}, {"csc",-1,0,0}, {"cos",0,1,0}, {"sec",0,-1,0}, {"tan",0,-1,1}, {"cot",0,1,-1} } },
	{ "cos", 1, -1, { {"cos",1,0,0}, {"sec",-1,0,0}, {"sin",0,1,0}, {"csc",0,-1,0}, {"tan",0,1,-1}, {"cot",0,-1,1} } },
	{ "tan", 1, 1, { {"tan",1,0,0}, {"cot",-1,0,0}, {"sec",0,1,0}, {"cos",0,-1,0}, {"sin",0,-1,1}, {"csc",0,1,-1} } },
	{ "cot", 1, 1, { {"cot",1,0,0}, {"tan",-1,0,0}, {"csc",0,1,0}, {"sin",0,-1,0}, {"cos",0,-1,1}, {"sec",0,1,-1} } },
	{ "sinh", 1, 1, { {"sinh",1,0,0}, {"csch",-1,0,0}, {"cosh",0,1,0}, {"sech",0,-1,0}, {"tanh",0,-1,1}, {"coth",0,1,-1} } },
	{ "cosh", -1, 1, { {"cosh",1,0,0}, {"sech",-1,0,0}, {"sinh",0,1,0}, {"csch",0,-1,0}, {"tanh",0,1,-1}, {"coth",0,-1,1} } },
	{ "tanh", 1, -1, { {"tanh",1,0,0}, {"coth",-1,0,0}, {"sech",0,1,0}, {"cosh",0,-1,0}, {"sinh",0,-1,1}, {"csch",0,1,-1} } },
	{ "coth", -1, 1, { {"coth",1,0,0}, {"tanh",-1,0,0}, {"csch",0,1,0}, {"sinh",0,-1,0}, {"cosh",0,-1,1}, {"sech",0,1,-1} } },
};
#define NFAM ((int) (sizeof(trig_fam) / sizeof(trig_fam[0])))

typedef struct {
	Node * core;		/* g(w), or v itself */
	Node * S;		/* the replacement of core: x/d */
	int fam;		/* index in trig_fam, or -1 */
	int pure, ok;
} FunOf;

static const TrigRel * fo_rel (FunOf * st, Node * t)	/* t = h(w) of the family? */
{
	int i;
	t = deref(t);
	if (st->fam < 0 || ! t || t->type != Func || term_nargs(t) != 1
	    || ! tequal(arg(t, 0), arg(st->core, 0))) return NULL;
	for (i = 0; i < 6; i++)
		if (is_head(t, trig_fam[st->fam].rel[i].h, 1)) return & trig_fam[st->fam].rel[i];
	return NULL;
}

static Node * fo_repl (Node * u, Node * x, FunOf * st)
{
	const TrigRel * r;
	Node * t = NULL;
	double e = 1;
	int k, n;
	u = deref(u);
	if (! st->ok) return NULL;
	if (! contains(u, x)) return tcpy(u);
	if (tequal(u, st->core)) return tcpy(st->S);
	if ((r = fo_rel(st, u)) != NULL
	    || (is_head(u, "^", 2) && (r = fo_rel(st, arg(u, 0))) != NULL
	        && num_value(arg(u, 1), & e) && e == floor(e)))
		{
		if (r->dir)				/* g or 1/g */
			return mk_pow(tcpy(st->S), mk_int(r->dir * e));
		if (st->pure || fmod(e, 2.0) != 0) { st->ok = 0; return NULL; }
		t = mk_add(mk_int(trig_fam[st->fam].c0),
			mk_mul(mk_int(trig_fam[st->fam].c2), mk_pow(tcpy(st->S), mk_int(2))));
		t = mk_pow(t, mk_int(r->pexp * e / 2));
		if (r->a) t = mk_mul(t, mk_pow(tcpy(st->S), mk_int(r->a * e)));
		return t;
		}
	if (u->type != Func) { st->ok = 0; return NULL; }	/* x itself */
	n = term_nargs(u);
	{
	Node * args = NULL, ** tail = & args;
	for (k = 0; k < n; k++)
		{
		Node * c = fo_repl(arg(u, k), x, st);
		if (! st->ok) { delete(args); delete(c); return NULL; }
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

/* v = d*core with d free of x; NULL (no state) if v has no such form */
static int fo_init (FunOf * st, Node * v, Node * x, int pure)
{
	TList l = {0};
	Node * d = NULL;
	int i, nf = 0;
	st->core = NULL; st->S = NULL; st->fam = -1; st->pure = pure; st->ok = 1;
	factors_to(v, & l);
	for (i = 0; i < l.n; i++)
		if (contains(l.t[i], x)) { st->core = l.t[i]; nf++; }
		else d = d ? mk_mul(d, tcpy(l.t[i])) : tcpy(l.t[i]);
	l.n = 0;
	tl_free(& l);
	if (nf != 1) { delete(d); return 0; }
	st->core = deref(st->core);
	st->S = d ? mk_mul(tcpy(x), mk_pow(d, mk_int(-1))) : tcpy(x);
	if (st->core->type == Func && term_nargs(st->core) == 1)
		for (i = 0; i < NFAM; i++)
			if (is_head(st->core, trig_fam[i].g, 1)) st->fam = i;
	return 1;
}

static Node * s_functionofq (Node * a[], int n, Symbol * f)	/* (v, u, x [, pure]) */
{
	FunOf st;
	Node * r;
	double p = 0;
	if (n != 3 && n != 4) return NULL;
	if (n == 4) num_value(a[3], & p);
	if (! contains(a[1], a[2]) || ! fo_init(& st, a[0], a[2], p != 0))
		return mk_bool(0, f);
	r = fo_repl(a[1], a[2], & st);
	delete(r);
	delete(st.S);
	return mk_bool(st.ok, f);
}

static Node * s_substfor (Node * a[], int n, Symbol * f)	/* ([h,] v, u, x) */
{
	FunOf st;
	Node * r;
	int o = n - 3;				/* without h: h = 1 */
	if ((n != 3 && n != 4) || ! fo_init(& st, a[o], a[o + 2], 0)) return NULL;
	r = fo_repl(a[o + 1], a[o + 2], & st);
	delete(st.S);
	if (! st.ok) return NULL;
	return n == 4 ? mk_mul(tcpy(a[0]), r) : r;
}

/* ---- derivdivides(y, u, x), falseq(u): Rubi's DerivativeDivides ----
 * the quotient q = u/y' if it is free of x (then Int[u*f(y)] is
 * q*Subst[Int[f(x)],x,y]); else derivdivides stays unevaluated, and
 * falseq, Rubi's FalseQ, is true for such an unevaluated helper. */

static Node * quotient_free (Node * u, Node * v, Node * x)	/* u/v if free of x */
{
	Node * t = mk_mul(tcpy(u), mk_pow(tcpy(v), mk_int(-1)));
	Node * q = simp_product(t), * c = NULL, * d;
	TList lu = {0}, lv = {0}, ld = {0};
	int j;
	delete(t);
	if (! contains(q, x)) return q;
	delete(q);
	expand_to(u, & lu);			/* sums: u = c*v with a constant c? */
	expand_to(v, & lv);
	for (j = 0; j < lv.n && ! c && lu.n > 0; j++)
		{
		t = mk_mul(tcpy(lu.t[0]), mk_pow(tcpy(lv.t[j]), mk_int(-1)));
		c = simp_product(t);
		delete(t);
		if (contains(c, x)) { delete(c); c = NULL; }
		}
	tl_free(& lu);
	tl_free(& lv);
	if (! c) return NULL;
	d = mk_add(tcpy(u), mk_neg(mk_mul(tcpy(c), tcpy(v))));
	expand_to(d, & ld);
	delete(d);
	d = tl_collect(& ld);
	if (is_zero(d)) { delete(d); return c; }
	delete(d);
	delete(c);
	return NULL;
}

/* ---- substfracpow(u, x): Rubi's SubstForFractionalPowerOfLinear ----
 * u contains powers (a+b*x)^(p/q) of one linear function; with n the least
 * common multiple of the q and t = (a+b*x)^(1/n):
 *   Int(u, x) = n/b * Subst[Int[t^(n-1)*u(x -> (t^n-a)/b), t], t, (a+b*x)^(1/n)].
 * NULL if u has no such powers. */

typedef struct {
	Node * lin;		/* a+b*x, a node of u */
	long n;			/* lcm of the denominators */
	int ok;
	Node * X, * T;		/* replacements of x and of lin^(1/n) */
} FracPow;

static long lcm_l (long a, long b)
{
	long x = a, y = b, t;
	while (y) { t = x % y; x = y; y = t; }
	return a / x * b;
}

static void fp_scan (Node * u, Node * x, FracPow * s)
{
	double e, p, q;
	int k, n;
	u = deref(u);
	if (! s->ok || ! contains(u, x) || u->type != Func) return;
	if (is_head(u, "^", 2) && ! contains(arg(u, 1), x) && num_value(arg(u, 1), & e)
	    && e != floor(e) && rat_approx(e, & p, & q) && q <= 12)
		{
		Node * c[MAXDEG];
		int deg;
		if (s->lin)
			{
			if (! tequal(s->lin, arg(u, 0))) s->ok = 0;
			else s->n = lcm_l(s->n, (long) q);
			return;
			}
		if (! poly_coeffs(arg(u, 0), x, c, & deg)) { s->ok = 0; return; }
		for (k = 0; k <= deg; k++) delete(c[k]);
		if (deg != 1) { s->ok = 0; return; }
		s->lin = arg(u, 0);
		s->n = (long) q;
		return;
		}
	n = term_nargs(u);
	for (k = 0; k < n; k++) fp_scan(arg(u, k), x, s);
}

static Node * fp_repl (Node * u, Node * x, FracPow * s)
{
	double e;
	int k, n;
	u = deref(u);
	if (! contains(u, x)) return tcpy(u);
	if (tequal(u, x)) return tcpy(s->X);
	if (is_head(u, "^", 2) && tequal(arg(u, 0), s->lin) && num_value(arg(u, 1), & e))
		return mk_pow(tcpy(s->T), mk_int(e * s->n));		/* (a+bx)^(p/q) = t^(p n/q) */
	if (u->type != Func) return tcpy(u);
	n = term_nargs(u);
	{
	Node * args = NULL, ** tail = & args;
	for (k = 0; k < n; k++)
		{
		Node * c = fp_repl(arg(u, k), x, s);
		if (k < n - 1) { * tail = mknod(Terms, c, NULL); tail = & (* tail)->r; }
		else * tail = c;
		}
	return mknod(Func, u->l, args);
	}
}

static Node * s_substfracpow (Node * a[], int n, Symbol * f)
{
	FracPow s = { NULL, 1, 1, NULL, NULL };
	Node * c[MAXDEG], * w, * r;
	int deg;
	if (n != 2) return NULL;
	fp_scan(a[0], a[1], & s);
	if (! s.ok || ! s.lin || s.n < 2 || ! poly_coeffs(s.lin, a[1], c, & deg)) return NULL;
	/* x = (t^n - a)/b with t written as x */
	s.T = a[1];
	s.X = mk_mul(mk_add(mk_pow(tcpy(a[1]), mk_int(s.n)), mk_neg(tcpy(c[0]))),
		mk_pow(tcpy(c[1]), mk_int(-1)));
	w = mk_mul(mk_pow(tcpy(a[1]), mk_int(s.n - 1)), fp_repl(a[0], a[1], & s));
	r = mk_mul(mk_mul(mk_int(s.n), mk_pow(c[1], mk_int(-1))),
		mk_f3("intsubst", w, tcpy(a[1]), mk_pow(tcpy(s.lin), mk_num_ex(1.0 / s.n, 1))));
	delete(c[0]);
	delete(s.X);
	return r;
}

/* ---- substsqrtquad(u, x): Euler's substitutions (Rubi's
 * FunctionOfSquareRootOfQuadratic) for u rational in x and sqrt(q),
 * q = a + b*x + c*x^2 with numbers a, b, c:
 *   c > 0: t = sqrt(c)*x + sqrt(q), x = (t^2-a)/(b+2 sqrt(c) t),
 *          sqrt(q) = (a sqrt(c) + b t + sqrt(c) t^2)/(b + 2 sqrt(c) t)
 *   a > 0: t = (sqrt(q) - sqrt(a))/x, x = (2 sqrt(a) t - b)/(c - t^2),
 *          sqrt(q) = (c sqrt(a) - b t + sqrt(a) t^2)/(c - t^2)
 * and Int(u, x) = 2*Subst[Int[u(x, sqrt(q))*sqrt(q)(t)/den(t), t], t, ...]
 * with den = b + 2 sqrt(c) t, resp. c - t^2. NULL otherwise. */

typedef struct {
	Node * q;		/* the quadratic under the root, a node of u */
	int ok;
	Node * X, * R;		/* replacements of x and of sqrt(q) */
} SqrtQuad;

static void sq_scan (Node * u, Node * x, SqrtQuad * s)
{
	double e;
	int k, n;
	u = deref(u);
	if (! s->ok || ! contains(u, x)) return;
	if (tequal(u, x)) return;
	if (u->type != Func) { s->ok = 0; return; }
	if (is_head(u, "^", 2) && ! contains(arg(u, 1), x) && num_value(arg(u, 1), & e))
		{
		if (e == floor(e)) { sq_scan(arg(u, 0), x, s); return; }
		if (2 * e != floor(2 * e)) { s->ok = 0; return; }	/* only half integers */
		if (s->q) { if (! tequal(s->q, arg(u, 0))) s->ok = 0; return; }
		{
		Node * c[MAXDEG];
		int deg;
		if (! poly_coeffs(arg(u, 0), x, c, & deg)) { s->ok = 0; return; }
		for (k = 0; k <= deg; k++) delete(c[k]);
		if (deg != 2) { s->ok = 0; return; }
		}
		s->q = arg(u, 0);
		return;
		}
	if (! is_head(u, "+", 2) && ! is_head(u, "*", 2) && ! is_head(u, "-", 2)
	    && ! is_head(u, "/", 2) && ! is_head(u, "-", 1)) { s->ok = 0; return; }
	n = term_nargs(u);
	for (k = 0; k < n; k++) sq_scan(arg(u, k), x, s);
}

static Node * sq_repl (Node * u, Node * x, SqrtQuad * s)
{
	double e;
	int k, n;
	u = deref(u);
	if (! contains(u, x)) return tcpy(u);
	if (tequal(u, x)) return tcpy(s->X);
	if (is_head(u, "^", 2) && tequal(arg(u, 0), s->q) && num_value(arg(u, 1), & e))
		return mk_pow(tcpy(s->R), mk_int(2 * e));		/* q^(k/2) = sqrt(q)^k */
	n = term_nargs(u);
	{
	Node * args = NULL, ** tail = & args;
	for (k = 0; k < n; k++)
		{
		Node * c = sq_repl(arg(u, k), x, s);
		if (k < n - 1) { * tail = mknod(Terms, c, NULL); tail = & (* tail)->r; }
		else * tail = c;
		}
	return mknod(Func, u->l, args);
	}
}

static Node * root2 (Node * c)		/* sqrt of a positive number, exact if possible */
{
	Symbol * r = num_sym(c) && is_exact(c) ? exact_root(num_sym(c), 2) : NULL;
	if (r) return mknod(Const, (Node *) r, NULL);
	return mk_pow(tcpy(c), mk_num_ex(0.5, 1));
}

static Node * s_substsqrtquad (Node * a[], int n, Symbol * f)
{
	SqrtQuad s = { NULL, 1, NULL, NULL };
	Node * c[MAXDEG], * x, * t, * den, * w, * r;
	double va, vb, vc;
	int deg;
	if (n != 2) return NULL;
	x = a[1];
	sq_scan(a[0], x, & s);
	if (! s.ok || ! s.q || ! poly_coeffs(s.q, x, c, & deg)) return NULL;
	if (! num_value(c[0], & va) || ! num_value(c[1], & vb) || ! num_value(c[2], & vc))
		{ delete(c[0]); delete(c[1]); delete(c[2]); return NULL; }
	if (vc > 0)
		{
		Node * sc = root2(c[2]);
		den = mk_add(tcpy(c[1]), mk_mul(mk_mul(mk_int(2), tcpy(sc)), tcpy(x)));
		s.X = mk_mul(mk_add(mk_pow(tcpy(x), mk_int(2)), mk_neg(tcpy(c[0]))),
			mk_pow(tcpy(den), mk_int(-1)));
		s.R = mk_mul(mk_add(mk_add(mk_mul(tcpy(c[0]), tcpy(sc)), mk_mul(tcpy(c[1]), tcpy(x))),
				mk_mul(tcpy(sc), mk_pow(tcpy(x), mk_int(2)))),
			mk_pow(tcpy(den), mk_int(-1)));
		t = mk_add(mk_mul(tcpy(sc), tcpy(x)), mk_pow(tcpy(s.q), mk_num_ex(0.5, 1)));
		delete(sc);
		}
	else if (va > 0)
		{
		Node * sa = root2(c[0]);
		den = mk_add(tcpy(c[2]), mk_neg(mk_pow(tcpy(x), mk_int(2))));
		s.X = mk_mul(mk_add(mk_mul(mk_mul(mk_int(2), tcpy(sa)), tcpy(x)), mk_neg(tcpy(c[1]))),
			mk_pow(tcpy(den), mk_int(-1)));
		s.R = mk_mul(mk_add(mk_add(mk_mul(tcpy(c[2]), tcpy(sa)), mk_neg(mk_mul(tcpy(c[1]), tcpy(x)))),
				mk_mul(tcpy(sa), mk_pow(tcpy(x), mk_int(2)))),
			mk_pow(tcpy(den), mk_int(-1)));
		t = mk_mul(mk_add(mk_pow(tcpy(s.q), mk_num_ex(0.5, 1)), mk_neg(tcpy(sa))),
			mk_pow(tcpy(x), mk_int(-1)));
		delete(sa);
		}
	else
		{ delete(c[0]); delete(c[1]); delete(c[2]); return NULL; }
	/* integrand in t (written as x): u(X, R) * R / den * 2 */
	w = mk_mul(mk_mul(sq_repl(a[0], x, & s), tcpy(s.R)), mk_pow(den, mk_int(-1)));
	r = mk_mul(mk_int(2), mk_f3("intsubst", w, tcpy(x), t));
	delete(s.X); delete(s.R);
	delete(c[0]); delete(c[1]); delete(c[2]);
	return r;
}

static Node * s_derivdivides (Node * a[], int n, Symbol * f)
{
	Node * y, * u, * x, * dy, * q;
	double dgy, dgu;
	if (n != 3) return NULL;
	y = a[0]; u = a[1]; x = a[2];
	if (! contains(y, x)) return NULL;
	if (poly_info(y, x, & dgy, -1, NULL))
		{
		Node * c0 = NULL;
		int ax = dgy == 1 && poly_info(y, x, & dgu, 0, & c0) && is_zero(c0);
		delete(c0);
		if (ax) return NULL;			/* a*x: Rubi says False */
		if (! poly_info(u, x, & dgu, -1, NULL) || dgu != dgy - 1) return NULL;
		}
	if (! (dy = deriv(y, x))) return NULL;
	if (is_zero(dy)) { delete(dy); return NULL; }
	q = quotient_free(u, dy, x);
	delete(dy);
	return q;
}

static Node * s_falseq (Node * a[], int n, Symbol * f)
{
	Node * t;
	double v;
	if (n != 1) return NULL;
	t = deref(a[0]);
	if (t && t->type == Func && builtin(t->l)) return mk_bool(1, f);	/* not applicable */
	return mk_bool(is_num(t, & v) && v == 0, f);
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
		double m, k;
		if (num_is(b, 0)) { delete(t); * p = mk_int(1); return; }
		if (num_is(b, 1)) keep = a;
		/* (u^m)^k = u^(m*k) for integers m, k, e.g. (b^-1)^-1 = b */
		else if (is_head(a, "^", 2) && num_value(arg(a, 1), & m) && m == floor(m)
		         && num_value(b, & k) && k == floor(k))
			{
			Node * r = mk_pow(tcpy(arg(a, 0)), mk_int(m * k));
			delete(t);
			* p = r;
			term_simplify_trivial(p);
			return;
			}
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

static Node * s_matchq (Node * a[], int n, Symbol * f);
static Node * s_normform (Node * a[], int n, Symbol * f);
static Node * s_listq (Node * a[], int n, Symbol * f);
static Node * s_length (Node * a[], int n, Symbol * f);
static Node * s_part (Node * a[], int n, Symbol * f);
static Node * s_first (Node * a[], int n, Symbol * f);
static Node * s_last (Node * a[], int n, Symbol * f);
static Node * s_rest (Node * a[], int n, Symbol * f);
static Node * s_most (Node * a[], int n, Symbol * f);
static Node * s_append (Node * a[], int n, Symbol * f);
static Node * s_prepend (Node * a[], int n, Symbol * f);
static Node * s_join (Node * a[], int n, Symbol * f);
static Node * s_reverse (Node * a[], int n, Symbol * f);
static Node * s_range (Node * a[], int n, Symbol * f);
static Node * s_table (Node * a[], int n, Symbol * f);
static Node * s_select (Node * a[], int n, Symbol * f);
static Node * s_total (Node * a[], int n, Symbol * f);

/* ---- functions defined by a rule list: FUNC f ... ATT RULES alglist ----
 * f(a1,..,an) is calculated as REWR f(a1,..,an) : alglist. If the result
 * still is a call of f, f does not apply (the call stays as it is). While
 * the rule list works on a call of f, f is not calculated again: the rules
 * themselves rewrite the inner calls. This puts knowledge of the library
 * (derivatives, trig identities, ...) into rules instead of C tables. */

#define MAXRULEFN 64
static struct { Symbol * f; Node * algs; int active; } rulefn[MAXRULEFN];
static int nrulefn = 0;

void rules_fn_register (Symbol * f, Node * algs)
{
	int i;
	for (i = 0; i < nrulefn; i++)
		if (rulefn[i].f == f) break;
	if (i == nrulefn)
		{
		if (nrulefn == MAXRULEFN) { printfErr("ATT RULES : too many functions\n"); return; }
		nrulefn++;
		}
	rulefn[i].f = f;
	rulefn[i].algs = algs;
	rulefn[i].active = 0;
}

static Node * s_rules (Node * a[], int n, Symbol * f)
{
	Node * args = NULL, * t;
	int i, k;
	for (k = 0; k < nrulefn; k++)
		if (urs_fkt(rulefn[k].f) == urs_fkt(f)) break;
	if (k == nrulefn || rulefn[k].active || n < 1) return NULL;
	for (i = n - 1; i >= 0; i--)		/* the call f(a1,..,an) */
		args = args ? mknod(Terms, tcpy(a[i]), args) : tcpy(a[i]);
	t = mknod(Func, (Node *) f, args);
	rulefn[k].active = 1;
	{
	void * outer = rewrite_push();	/* maybe in a condition of an outer rule */
	rewrite_begin();
	t = solve(t, rulefn[k].algs);
	rewrite_end();
	rewrite_pop(outer);
	}
	rulefn[k].active = 0;
	t = deref(t);
	if (t && t->type == Func && urs_fkt(TERM_HEAD(t)) == urs_fkt(f))
		{
		delete(t);			/* unchanged: not applicable */
		return NULL;
		}
	return t;
}

s_function * rules_sfkt (void)
{
	return s_rules;
}

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
	{ "nonsumq",         s_nonsumq },
	{ "gtq",             s_gtq },
	{ "ltq",             s_ltq },
	{ "geq",             s_geq },
	{ "leq",             s_leq },
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
	{ "removecontent",   s_removecontent },
	{ "trignorm",        s_trignorm },
	{ "trigexpand",      s_trigexpand },
	{ "substfracpow",    s_substfracpow },
	{ "substsqrtquad",   s_substsqrtquad },
	{ "expandtosum",     s_expandtosum },
	{ "polyquotient",    s_polyquotient },
	{ "polyremainder",   s_polyremainder },
	{ "normpoly",        s_normpoly },
	{ "collect",         s_collect },
	{ "hyp2exp", s_hyp2exp },
	{ "substexp", s_substexp },
	{ "functionofexponentialq", s_functionofexponentialq },
	{ "binomsum", s_binomsum },
	{ "matchq", s_matchq },
	{ "normform", s_normform },
	{ "listq", s_listq },		/* lists (inc/list) */
	{ "length", s_length },
	{ "part", s_part },
	{ "first", s_first },
	{ "last", s_last },
	{ "rest", s_rest },
	{ "most", s_most },
	{ "append", s_append },
	{ "prepend", s_prepend },
	{ "join", s_join },
	{ "reverse", s_reverse },
	{ "range", s_range },
	{ "table", s_table },
	{ "select", s_select },
	{ "total", s_total },
	{ "functionofq", s_functionofq },
	{ "substfor", s_substfor },
	{ "derivdivides", s_derivdivides },
	{ "falseq", s_falseq },
	{ "intsubst", s_substint },
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

static int has_builtin (Node * t)	/* is a builtin call somewhere in t? */
{
	t = deref(t);
	if (! t || t->type == SYM_TYPE || t->type == Const) return 0;
	if (t->type == Func && builtin(t->l)) return 1;
	return has_builtin(t->l) || has_builtin(t->r);
}

/* matchq(u, pattern [, cond]): Rubi's MatchQ, with the matcher of the rule
 * lists (listmatch.c). Declared with HOLD: the pattern and the condition
 * arrive unevaluated (the condition refers to the pattern variables), u is
 * calculated here. */
static Node * s_matchq (Node * a[], int n, Symbol * f)
{
	Node * u;
	int ok;
	if (n != 2 && n != 3) return NULL;
	u = has_builtin(a[0]) ? tcalc(tcpy(a[0])) : NULL;
	ok = lm_matchq(a[1], u ? deref(u) : a[0], n == 3 ? a[2] : NULL);
	delete(u);
	return mk_bool(ok, f);
}


/* ---- lists (inc/list): list(a,b,c) and the empty list nil ----
 * A list is a term with the head "list", as Mathematica's List: its
 * elements and the results have the sort real, so that lists nest freely
 * (the sort of part(m,1) cannot be known before the list is there). The
 * functions work on the term structure and stay unevaluated if an argument
 * is no list. Roles "list" and "nil". */

#define MAXLIST 4096

static int is_nil (Node * t)
{
	Symbol * s = role_find("nil");
	t = deref(t);
	return s && t && ((Symbol *) t == s || (t->type == Const && (Symbol *) t->l == s)
	                  || (t->type == SYM_TYPE && (Symbol *) t == s));
}

static int is_list (Node * t)
{
	return is_head(t, "list", -1) || is_nil(t);
}

static int list_len (Node * t)
{
	return is_nil(t) ? 0 : term_nargs(deref(t));
}

static Node * mk_list (Node * e[], int n)	/* takes the elements */
{
	Node * args;
	int i;
	if (n == 0)
		{
		Symbol * s = role_find("nil");
		if (! s) fatal("symfkt : nil is not declared (inc/list)");
		return mknod(Const, (Node *) s, NULL);
		}
	args = e[n - 1];
	for (i = n - 2; i >= 0; i--)
		args = mknod(Terms, e[i], args);
	return mknod(Func, (Node *) getsymbol(fsym("list"), args), args);
}

/* the elements of l (copies) into e; their number, or -1 */
static int list_elems (Node * l, Node * e[], int max)
{
	int i, n;
	if (! is_list(l)) return -1;
	n = list_len(l);
	if (n > max) return -1;
	for (i = 0; i < n; i++) e[i] = tcpy(arg(deref(l), i));
	return n;
}

static int index_of (Node * t, int n, int * k)	/* 1-based, negative from the end */
{
	double v;
	if (! is_num(t, & v) || v != floor(v) || v == 0) return 0;
	* k = v > 0 ? (int) v - 1 : n + (int) v;
	return * k >= 0 && * k < n;
}

static Node * s_listq (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return mk_bool(is_list(a[0]), f);
}

static Node * s_length (Node * a[], int n, Symbol * f)
{
	if (n != 1 || ! is_list(a[0])) return NULL;
	return mk_int(list_len(a[0]));
}

static Node * s_part (Node * a[], int n, Symbol * f)	/* part(l, i, j, ...) */
{
	Node * t = a[0];
	int i, k;
	if (n < 2) return NULL;
	for (i = 1; i < n; i++)
		{
		if (! is_list(t) || ! index_of(a[i], list_len(t), & k)) return NULL;
		t = arg(deref(t), k);
		}
	return tcpy(t);
}

static Node * list_slice (Node * l, int from, int to)	/* elements from..to-1 */
{
	Node * e[MAXLIST];
	int i, n;
	if (! is_list(l) || (n = list_len(l)) == 0 || n > MAXLIST) return NULL;
	for (i = from; i < to; i++) e[i - from] = tcpy(arg(deref(l), i));
	return mk_list(e, to - from);
}

static Node * s_first (Node * a[], int n, Symbol * f)
{
	if (n != 1 || ! is_list(a[0]) || list_len(a[0]) == 0) return NULL;
	return tcpy(arg(deref(a[0]), 0));
}

static Node * s_last (Node * a[], int n, Symbol * f)
{
	if (n != 1 || ! is_list(a[0]) || list_len(a[0]) == 0) return NULL;
	return tcpy(arg(deref(a[0]), list_len(a[0]) - 1));
}

static Node * s_rest (Node * a[], int n, Symbol * f)
{
	if (n != 1 || ! is_list(a[0]) || list_len(a[0]) == 0) return NULL;
	return list_slice(a[0], 1, list_len(a[0]));
}

static Node * s_most (Node * a[], int n, Symbol * f)
{
	if (n != 1 || ! is_list(a[0]) || list_len(a[0]) == 0) return NULL;
	return list_slice(a[0], 0, list_len(a[0]) - 1);
}

static Node * s_append (Node * a[], int n, Symbol * f)
{
	Node * e[MAXLIST];
	int m;
	if (n != 2 || (m = list_elems(a[0], e, MAXLIST - 1)) < 0) return NULL;
	e[m++] = tcpy(a[1]);
	return mk_list(e, m);
}

static Node * s_prepend (Node * a[], int n, Symbol * f)
{
	Node * e[MAXLIST];
	int m;
	if (n != 2 || (m = list_elems(a[0], e + 1, MAXLIST - 1)) < 0) return NULL;
	e[0] = tcpy(a[1]);
	return mk_list(e, m + 1);
}

static Node * s_join (Node * a[], int n, Symbol * f)
{
	Node * e[MAXLIST];
	int i, m = 0, k;
	for (i = 0; i < n; i++)
		if (! is_list(a[i])) return NULL;
	for (i = 0; i < n; i++)
		{
		if ((k = list_elems(a[i], e + m, MAXLIST - m)) < 0)
			{
			while (m > 0) delete(e[--m]);
			return NULL;
			}
		m += k;
		}
	return mk_list(e, m);
}

static Node * s_reverse (Node * a[], int n, Symbol * f)
{
	Node * e[MAXLIST], * r[MAXLIST];
	int i, m;
	if (n != 1 || (m = list_elems(a[0], e, MAXLIST)) < 0) return NULL;
	for (i = 0; i < m; i++) r[i] = e[m - 1 - i];
	return mk_list(r, m);
}

static Node * s_range (Node * a[], int n, Symbol * f)	/* range(n), range(a,b), range(a,b,d) */
{
	Node * e[MAXLIST];
	double lo = 1, hi, d = 1, v;
	int m = 0, ex = 1, i;
	if (n < 1 || n > 3) return NULL;
	for (i = 0; i < n; i++)
		{
		if (! is_num(a[i], & v)) return NULL;
		if (! is_exact(a[i])) ex = 0;
		}
	if (n == 1) is_num(a[0], & hi);
	else { is_num(a[0], & lo); is_num(a[1], & hi); }
	if (n == 3) is_num(a[2], & d);
	if (d == 0 || (hi - lo) / d >= MAXLIST) return NULL;
	for (v = lo; d > 0 ? v <= hi + 1e-12 : v >= hi - 1e-12; v += d)
		e[m++] = mk_num_ex(v, ex);
	return mk_list(e, m);
}

/* the elements of a list argument of a HOLD function: calculated first */
static Node * held_list (Node * t, Node ** own)
{
	* own = has_builtin(t) ? tcalc(tcpy(t)) : NULL;
	return * own ? deref(* own) : t;
}

static Node * s_table (Node * a[], int n, Symbol * f)	/* table(body, x, l or n) */
{
	Node * e[MAXLIST], * own, * l, * r = NULL;
	int i, m;
	double v;
	if (n != 3) return NULL;
	l = held_list(a[2], & own);
	if (is_num(l, & v))			/* table(body, x, n): x = 1..n */
		{
		Node * ra[1];
		ra[0] = l;
		r = s_range(ra, 1, f);
		delete(own);
		if (! r) return NULL;
		own = r;
		l = r;
		}
	if ((m = list_elems(l, e, MAXLIST)) < 0) { delete(own); return NULL; }
	for (i = 0; i < m; i++)
		{
		Node * t = replace(a[0], a[1], e[i]);
		delete(e[i]);
		e[i] = tcalc(t);
		}
	delete(own);
	return mk_list(e, m);
}

static Node * s_select (Node * a[], int n, Symbol * f)	/* select(l, x, cond) */
{
	Node * e[MAXLIST], * own, * l;
	int i, m, k = 0;
	if (n != 3) return NULL;
	l = held_list(a[0], & own);
	if ((m = list_elems(l, e, MAXLIST)) < 0) { delete(own); return NULL; }
	delete(own);
	for (i = 0; i < m; i++)
		{
		Node * c = tcalc(replace(a[2], a[1], e[i]));
		if (isnt_zero(c)) e[k++] = e[i];	/* true (bool) or a number != 0 */
		else delete(e[i]);
		delete(c);
		}
	return mk_list(e, k);
}

static Node * s_total (Node * a[], int n, Symbol * f)
{
	Node * e[MAXLIST], * r = NULL;
	int i, m;
	if (n != 1 || (m = list_elems(a[0], e, MAXLIST)) < 0) return NULL;
	for (i = 0; i < m; i++) r = r ? mk_add(r, e[i]) : e[i];
	return r ? r : mk_int(0);
}

/* ---- profile of the helpers: REWRITE_PROFILE=1 in the environment ----
 * counts the calls of each symbolic helper and their time (including the
 * helpers called inside), and the time of the rule list matcher; printed
 * at the end of the program. Without the variable it costs one test. */

#include <time.h>

#define MAXPROF 256
static struct { const char * name; long calls; double secs; } prof[MAXPROF];
static int nprof = 0, prof_on = -1;
double prof_match_secs = 0;		/* listmatch.c */
long prof_match_calls = 0;

static double prof_now (void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, & ts);
	return ts.tv_sec + 1e-9 * ts.tv_nsec;
}

static void prof_report (void)
{
	int i, j;
	for (i = 1; i < nprof; i++)		/* by time, the largest first */
		for (j = i; j > 0 && prof[j].secs > prof[j - 1].secs; j--)
			{
			const char * n = prof[j].name; long c = prof[j].calls; double t = prof[j].secs;
			prof[j] = prof[j - 1];
			prof[j - 1].name = n; prof[j - 1].calls = c; prof[j - 1].secs = t;
			}
	fprintf(stderr, "\nprofile (REWRITE_PROFILE): rule list matching %.3f s in %ld calls\n",
	        prof_match_secs, prof_match_calls);
	fprintf(stderr, "%-24s %10s %10s\n", "helper", "calls", "seconds");
	for (i = 0; i < nprof && i < 30; i++)
		fprintf(stderr, "%-24s %10ld %10.3f\n", prof[i].name, prof[i].calls, prof[i].secs);
}

int profiling (void)
{
	if (prof_on < 0)
		{
		const char * e = getenv("REWRITE_PROFILE");
		prof_on = e && * e && * e != '0';
		if (prof_on) atexit(prof_report);
		}
	return prof_on;
}

double profile_now (void) { return prof_now(); }

void profile_add (const char * name, double secs);

static void prof_add (const char * name, double secs)
{
	int i;
	for (i = 0; i < nprof; i++)
		if (prof[i].name == name || ! strcmp(prof[i].name, name)) break;
	if (i == nprof)
		{
		if (nprof == MAXPROF) return;
		prof[nprof].name = name; prof[nprof].calls = 0; prof[nprof].secs = 0;
		nprof++;
		}
	prof[i].calls++;
	prof[i].secs += secs;
}

void profile_add (const char * name, double secs)
{
	prof_add(name, secs);
}

Node * call_builtin (Node * term)
{
	Symbol * f = TERM_HEAD(term);
	Node * args[MAXARGS], * own[MAXARGS], * a;
	int n = 0, i;
	Node * res;
	/* nested calls first, as in sumq(expandintegrand(u,x)): a condition is
	 * calculated top-down (realcalk), which passes them unevaluated */
	for (a = TERM_ARGS(term); a && n < MAXARGS; a = ARGS_NEXT(a))
		{
		Node * t = deref(ARGS_ITEM(a));
		/* HOLD (matchq): a pattern and its condition stay as they are */
		own[n] = builtin(f) != 2 && has_builtin(t) ? tcalc(tcpy(t)) : NULL;
		args[n] = own[n] ? deref(own[n]) : t;
		n++;
		}
	if (profiling())
		{
		double t0 = prof_now();
		res = ((s_function *) value(f))(args, n, f);
		prof_add(name(f), prof_now() - t0);
		}
	else
		res = ((s_function *) value(f))(args, n, f);
	for (i = 0; i < n; i++) delete(own[i]);
	retype_term(res);	/* function variants matching the sorts of the new arguments */
	return res;
}
