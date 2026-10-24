/*
 *	expand.c (2026)
 *
 *	Optional pattern parts, commutative operators and condition lists,
 *	see expand.h. A rule whose left side contains optional meta variables
 *	or commutative operators is expanded into all its variants when it is
 *	defined. Every variant is an ordinary rule for the matcher (forms.c).
 *
 *	Example: with  OPT Ka,Kb   DEFAULT + = 0   DEFAULT * = 1   COMM +,*
 *	the pattern  Ka+Kb*Xv  stands for
 *	    Ka+Kb*Xv,  Kb*Xv+Ka,  Ka+Xv*Kb, ...   (commutative orders)
 *	    Kb*Xv      with Ka = 0                (Ka missing)
 *	    Ka+Xv      with Kb = 1                (Kb missing)
 *	    Xv         with Ka = 0, Kb = 1
 *	The values of missing variables are put into the right side, the
 *	condition and the DO block of each variant.
 */

#include <string.h>
#include <stdlib.h>

#include "inout.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "node.h"
#include "forms.h"
#include "nodes.h"
#include "expand.h"

extern const char * numbername;	/* node.c: name of all number symbols */
void declare (Node * np);			/* defs.c */

#define MAXTAB 128

static Symbol * opt_vars[MAXTAB];		/* optional meta variables */
static int n_opt = 0;

static const char * comm_names[MAXTAB];	/* commutative functions (by name) */
static int n_comm = 0;

static struct {
	const char * name;	/* function name */
	Node * value;			/* default value (term) */
	BOOLEAN right_only;	/* only the right operand may be missing */
} defaults[MAXTAB];
static int n_def = 0;

/* ---------------- statements ---------------- */

static void mark_optional (Symbol * sp)
{
	int i;
	if (lexval(sp) != Var)
		{
		printfErr("error : OPT %s : only meta variables (VAR, NUM) can be optional !\n",name(sp));
		return;
		}
	for (i = 0; i < n_opt; i++)
		if (opt_vars[i] == sp) return;
	if (n_opt >= MAXTAB) fatal("OPT : too many optional variables");
	opt_vars[n_opt++] = sp;
}

void opt_fkt (Node * np)		/* FUNC(opt_fkt, idlist); without list: clear */
{
	Node * l;
	if (! INSTR_PAR(np)) { n_opt = 0; return; }
	for (l = INSTR_PAR(np); l->type == Id; l = l->r)
		mark_optional((Symbol *) l->l);
	mark_optional((Symbol *) l);
}

static void mark_comm (Symbol * sp)
{
	int i;
	for (i = 0; i < n_comm; i++)
		if (strcmp(comm_names[i],name(sp)) == 0) return;
	if (n_comm >= MAXTAB) fatal("COMM : too many functions");
	comm_names[n_comm++] = name(sp);
}

void comm_fkt (Node * np)		/* FUNC(comm_fkt, funclist); without list: clear */
{
	Node * l;
	if (! INSTR_PAR(np)) { n_comm = 0; return; }
	for (l = INSTR_PAR(np); l->type == Functs; l = l->r)
		mark_comm((Symbol *) l->l);
	mark_comm((Symbol *) l);
}

void default_fkt (Node * np)	/* FUNC(default_fkt, PARAM(PARAM(f, right_only), value)) */
{
	Symbol * f;
	BOOLEAN right;
	int i;
	if (! INSTR_PAR(np))		/* DEFAULT without arguments: clear */
		{
		for (i = 0; i < n_def; i++)
			delete(defaults[i].value);
		n_def = 0;
		return;
		}
	f     = (Symbol *) np->r->l->l;
	right = (np->r->l->r != NULL);
	for (i = 0; i < n_def; i++)
		if (strcmp(defaults[i].name,name(f)) == 0) break;
	if (i == n_def)
		{
		if (n_def >= MAXTAB) fatal("DEFAULT : too many functions");
		n_def++;
		}
	else
		delete(defaults[i].value);
	defaults[i].name       = name(f);
	defaults[i].value      = np->r->r;
	defaults[i].right_only = right;
	np->r->r = NULL;	/* value is kept in the table */
}

BOOLEAN and_cond (Node * np)	/* PARAM(Cond, Cond) */
{
	return COND_CALL(np->l) && COND_CALL(np->r);
}

/* ---------------- helpers ---------------- */

static BOOLEAN is_optional (Node * n)
{
	int i;
	if (! n || n->type != SYM_TYPE) return FALSE;
	for (i = 0; i < n_opt; i++)
		if ((Node *) opt_vars[i] == n) return TRUE;
	return FALSE;
}

static BOOLEAN is_comm (Node * f)		/* f: Func node */
{
	int i;
	for (i = 0; i < n_comm; i++)
		if (strcmp(comm_names[i],name(TERM_HEAD(f))) == 0) return TRUE;
	return FALSE;
}

static Node * default_of (Node * f, BOOLEAN * right_only)
{
	int i;
	for (i = 0; i < n_def; i++)
		if (strcmp(defaults[i].name,name(TERM_HEAD(f))) == 0)
			{
			* right_only = defaults[i].right_only;
			return defaults[i].value;
			}
	return NULL;
}

/* does the left side need any expansion? */
static BOOLEAN needs_expansion (Node * n)
{
	if (! n) return FALSE;
	if (n->type == SYM_TYPE) return FALSE;
	if (n->type == Const) return FALSE;
	if (n->type == Func)
		{
		Node * a = TERM_ARGS(n);
		if (is_comm(n)) return TRUE;
		if (a && a->type == Terms && (is_optional(a->l) || is_optional(a->r)))
			{
			BOOLEAN r;
			if (default_of(n,&r)) return TRUE;
			}
		return needs_expansion(a);
		}
	return needs_expansion(n->l) || needs_expansion(n->r);
}

/* copy of a pattern tree: new inner nodes, symbols are shared */
static Node * ncopy (Node * n)
{
	if (! n || n->type == SYM_TYPE) return n;
	if (n->type == Func || n->type == Const)
		return mknod(n->type, n->l, ncopy(n->r));
	return mknod(n->type, ncopy(n->l), ncopy(n->r));
}

static void nfree (Node * n)		/* frees a tree made by ncopy */
{
	if (! n || n->type == SYM_TYPE) return;
	if (n->type != Func && n->type != Const)
		nfree(n->l);
	nfree(n->r);
	delnod(n);
}

static BOOLEAN nequal (Node * a, Node * b)
{
	if (a == b) return TRUE;
	if (! a || ! b) return FALSE;
	if (a->type != b->type) return FALSE;
	if (a->type == SYM_TYPE) return FALSE;
	if (a->type == Const) return symeq((Symbol *) a->l, (Symbol *) b->l);
	if (a->type == Func && a->l != b->l) return FALSE;
	if (a->type != Func && ! nequal(a->l, b->l)) return FALSE;
	return nequal(a->r, b->r);
}

/* bindings: PARAM(PARAM(var, value), next) */
static Node * bind_copy (Node * b)
{
	if (! b) return NULL;
	return mknod(PARAM, mknod(PARAM, b->l->l, b->l->r), bind_copy(b->r));
}

static Node * bind_append (Node * a, Node * b)	/* copy of a followed by copy of b */
{
	Node * c = bind_copy(a), * p;
	if (! c) return bind_copy(b);
	for (p = c; p->r; p = p->r)
		;
	p->r = bind_copy(b);
	return c;
}

static void bind_free (Node * b)
{
	while (b)
		{
		Node * n = b->r;
		delnod(b->l);
		delnod(b);
		b = n;
		}
}

static Node * bind_lookup (Node * b, Node * var)
{
	for ( ; b; b = b->r)
		if (b->l->l == var) return b->l->r;
	return NULL;
}

/* ---------------- variants ---------------- */

typedef struct Variant Variant;
struct Variant {
	Node * tree;		/* left side */
	Node * binds;		/* values of missing optional variables */
	Variant * next;
};

static Variant * vnew (Node * tree, Node * binds, Variant * next)
{
	Variant * v = (Variant *) malloc(sizeof(Variant));
	if (! v) fatal("expand : no room");
	v->tree = tree; v->binds = binds; v->next = next;
	return v;
}

static void vfree (Variant * v)
{
	while (v)
		{
		Variant * n = v->next;
		nfree(v->tree);
		bind_free(v->binds);
		free(v);
		v = n;
		}
}

static Variant * vreverse (Variant * v)
{
	Variant * r = NULL;
	while (v)
		{
		Variant * n = v->next;
		v->next = r;
		r = v;
		v = n;
		}
	return r;
}

static Variant * expand (Node * n)
{
	Variant * res = NULL, * va, * vb, * vl, * vr;

	if (! n || n->type == SYM_TYPE || n->type == Const)
		return vnew(ncopy(n), NULL, NULL);

	if (n->type == Func)
		{
		Node * args = TERM_ARGS(n);
		if (args && args->type == Terms && args->r && args->r->type != Terms)
			{ /* binary function f(A,B) */
			Node * A = args->l, * B = args->r, * d;
			BOOLEAN right_only = FALSE;
			Variant * VA = expand(A), * VB = expand(B);

			for (va = VA; va; va = va->next)
				for (vb = VB; vb; vb = vb->next)
					{
					res = vnew(mknod(Func, n->l, mknod(Terms, ncopy(va->tree), ncopy(vb->tree))),
					           bind_append(va->binds, vb->binds), res);
					if (is_comm(n) && ! nequal(va->tree, vb->tree))
						res = vnew(mknod(Func, n->l, mknod(Terms, ncopy(vb->tree), ncopy(va->tree))),
						           bind_append(vb->binds, va->binds), res);
					}

			if ((d = default_of(n, & right_only)))
				{
				if (! right_only && is_optional(A) && ! is_optional(B))
					for (vb = VB; vb; vb = vb->next)
						{
						Node * b = mknod(PARAM, mknod(PARAM, A, d), NULL);
						res = vnew(ncopy(vb->tree), bind_append(vb->binds, b), res);
						bind_free(b);
						}
				if (is_optional(B) && ! is_optional(A))
					for (va = VA; va; va = va->next)
						{
						Node * b = mknod(PARAM, mknod(PARAM, B, d), NULL);
						res = vnew(ncopy(va->tree), bind_append(va->binds, b), res);
						bind_free(b);
						}
				}
			vfree(VA);
			vfree(VB);
			return vreverse(res);
			}
		/* other functions: expand the argument list */
		vr = expand(args);
		for (vb = vr; vb; vb = vb->next)
			res = vnew(mknod(Func, n->l, ncopy(vb->tree)), bind_copy(vb->binds), res);
		vfree(vr);
		return vreverse(res);
		}

	/* other nodes (Terms lists): all combinations of both children */
	vl = expand(n->l);
	vr = expand(n->r);
	for (va = vl; va; va = va->next)
		for (vb = vr; vb; vb = vb->next)
			res = vnew(mknod(n->type, ncopy(va->tree), ncopy(vb->tree)),
			           bind_append(va->binds, vb->binds), res);
	vfree(vl);
	vfree(vr);
	return vreverse(res);
}

/* ---------------- copies for the rule tree ---------------- */

static Symbol * clone_number (Symbol * sp)
{
	return mknum(CPYNUM(sp, value(sp)), rtypes(sp));
}

/* Full copy of a rule part (left side, right side, condition, DO block).
 * Bound optional variables are replaced by their values, numbers are
 * cloned so that no two rules share a number symbol. */
static Node * subst_copy (Node * n, Node * binds)
{
	Node * v;
	if (! n) return NULL;
	switch (n->type)
		{
		case SYM_TYPE:
			if ((v = bind_lookup(binds, n)))
				return subst_copy(v, NULL);
			if (name((Symbol *) n) == numbername)
				return (Node *) clone_number((Symbol *) n);
			return n;		/* symbols are shared */
		case Const:
			if (name((Symbol *) n->l) == numbername)
				return mknod(Const, (Node *) clone_number((Symbol *) n->l), NULL);
			return mknod(Const, n->l, NULL);
		case Func:
			return mknod(Func, n->l, subst_copy(n->r, binds));
		case FUNC:			/* l is a C function */
			if (n->l == (Node *) declare && n->r)
				{ /* FUNC(declare, lexv(idlist, hasv(rtypes, atypes))) */
				Node * hv = n->r->r;
				return mknod(FUNC, n->l,
				        mknod(n->r->type, subst_copy(n->r->l, binds),
				          hv ? mknod(hv->type, hv->l, subst_copy(hv->r, binds)) : NULL));
				}
			return mknod(FUNC, n->l, subst_copy(n->r, binds));
		case Cond:			/* l is a C function */
		case ATT:
			return mknod(n->type, n->l, subst_copy(n->r, binds));
		default:
			return mknod(n->type, subst_copy(n->l, binds), subst_copy(n->r, binds));
		}
}

Node * add_rule_variants (Node * lhs, Node * res, Node * tree)
{
	Variant * vars, * v;
	int count = 0;

	if (! needs_expansion(lhs))
		return merge(lhs, res, tree);		/* unchanged behaviour */

	vars = expand(lhs);
	for (v = vars; v; v = v->next)
		{
		tree = merge(subst_copy(v->tree, v->binds), subst_copy(res, v->binds), tree);
		count++;
		}
	DEBG((2,"rule expanded into %d variants\n", count));
	vfree(vars);
	delete(lhs);	/* the variants are copies */
	delete(res);
	return tree;
}
