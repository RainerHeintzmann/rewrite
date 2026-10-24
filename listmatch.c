/*
 *	listmatch.c (2026)
 *
 *	Rule lists with a backtracking matcher, see listmatch.h.
 *
 *	Meta variables are bound exactly as in forms.c: the header of the Var
 *	symbol is overwritten with the matched term node, and an entry in the
 *	chain var_chain records it. Unlike forms.c, a failed attempt only undoes
 *	the bindings made since its own checkpoint, so alternatives can be tried
 *	(commutative orders, optional operands) and the rest of the pattern and
 *	the condition are checked for each alternative.
 */

#include <string.h>
#include <stdlib.h>

#include "inout.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "node.h"
#include "nodes.h"
#include "sync.h"		/* IS_follows */
#include "listmatch.h"
#include "symfkt.h"		/* term_equal */
#include "numsort.h"		/* var_sort_ok */

extern Node var_chain;		/* run.c */
extern Node * chain_pos;	/* run.c */

/* ---------------- settings of the current rule list ---------------- */

static Node * cur_settings;	/* PARAM(optvars, PARAM(commfuncs, defaults)) */
static Node * cur_res;		/* result part of the rule being tried */

static BOOLEAN is_optional (Node * n)	/* unbound optional meta variable */
{
	Node * l;
	if (! n || n->type != SYM_TYPE || lexval((Symbol *) n) != Var || ! cur_settings)
		return FALSE;
	for (l = cur_settings->l; l; l = l->r)
		if (l->l == n) return TRUE;
	return FALSE;
}

static BOOLEAN in_optlist (Node * n)	/* optional meta variable, bound or not */
{
	Node * l;
	if (! n || ! cur_settings) return FALSE;
	for (l = cur_settings->l; l; l = l->r)
		if (l->l == n) return TRUE;
	return FALSE;
}

/* an optional variable that is already bound to its default value d may be
 * missing again: in (e. + f.*x) ... (e. + f.*x) the second x needs e = 0 */
static BOOLEAN bound_to_default (Node * n, Node * d)
{
	return in_optlist(n) && n->type != SYM_TYPE && term_equal(n, d);
}

static BOOLEAN is_comm (Node * f)	/* f: Func node */
{
	Node * l;
	if (! cur_settings || ! cur_settings->r) return FALSE;
	for (l = cur_settings->r->l; l; l = l->r)
		if (strcmp(name((Symbol *) l->l), name(TERM_HEAD(f))) == 0) return TRUE;
	return FALSE;
}

/* defaults: PARAM(PARAM(PARAM(fsym, value), rightflag), next) */
static Node * default_of (Node * f, BOOLEAN * right_only)
{
	Node * l;
	if (! cur_settings || ! cur_settings->r) return NULL;
	for (l = cur_settings->r->r; l; l = l->r)
		if (strcmp(name((Symbol *) l->l->l->l), name(TERM_HEAD(f))) == 0)
			{
			* right_only = (l->l->r != NULL);
			return l->l->l->r;
			}
	return NULL;
}

/* ---------------- bindings ---------------- */

static void bind (Node * var, Node * t)
{
	chain_pos = chain_pos->l = mknod(CHAIN, NULL, NULL);
	chain_pos->r = var;
	var->type = t->type;
	var->l = t->l;
	var->r = t->r;
}

static void restore_to (Node * cp)	/* undo all bindings made after cp */
{
	restore(cp->l);
	cp->l = NULL;
	chain_pos = cp;
}

/* ---------------- matching with continuation ---------------- */

typedef struct Goal Goal;
struct Goal {
	Node * p;	/* pattern */
	Node * t;	/* term */
	Goal * next;
};

static BOOLEAN lm_solve (Goal * g);

static BOOLEAN goal (Node * p, Node * t, Goal * next)
{
	Goal g;
	g.p = p; g.t = t; g.next = next;
	return lm_solve(& g);
}

static BOOLEAN goal2 (Node * p1, Node * t1, Node * p2, Node * t2, Goal * next)
{
	Goal g1, g2;
	g2.p = p2; g2.t = t2; g2.next = next;
	g1.p = p1; g1.t = t1; g1.next = & g2;
	return lm_solve(& g1);
}

static Symbol * sym_of (Node * t)	/* symbol of a constant term */
{
	if (t->type == Const) return (Symbol *) t->l;
	if (t->type == SYM_TYPE) return (Symbol *) t;
	return NULL;
}

static BOOLEAN bind_and_go (Node * var, Node * t, Goal * next)
{
	Node * cp = chain_pos;
	bind(var, t);
	if (lm_solve(next)) return TRUE;
	restore_to(cp);
	return FALSE;
}

static BOOLEAN lm_solve (Goal * g)
{
	Node * p, * t, * d;
	BOOLEAN right_only = FALSE;
	Symbol * ts;

	if (! g)			/* everything matched: check the condition */
		return COND_CALL(RES_COND(cur_res));

	p = g->p;
	t = g->t;
	if (p == t) return lm_solve(g->next);
	if (! p || ! t) return FALSE;

	if (p->type == SYM_TYPE)
		{
		Symbol * ps = (Symbol *) p;
		if (lexval(ps) == Term && p->l)		/* term variable: its content */
			return goal(p->l, t, g->next);
		if (lexval(ps) == Var)			/* unbound meta variable */
			{
			if (t->type != Const && t->type != Func) return FALSE;
			if (! var_sort_ok(rtypes(ps), t)) return FALSE;	/* subsorts (nonneg, ...) */
			if (hasval(ps))			/* NUM: only numbers */
				if (t->type != Const || ! hasval(t->l) || lexval((Symbol *) t->l) != Const)
					return FALSE;
			return bind_and_go(p, t, g->next);
			}
		ts = sym_of(t);
		return ts && symeq(ps, ts) && lm_solve(g->next);
		}

	if (p->type == Const)
		{
		ts = sym_of(t);
		return ts && symeq((Symbol *) p->l, ts) && lm_solve(g->next);
		}

	if (p->type == Func)
		{
		int n = term_nargs(p);
		if (t->type == Func && term_nargs(t) == n
		    && IS_follows(TERM_HEAD(t), TERM_HEAD(p)))
			{
			if (goal(TERM_ARGS(p), TERM_ARGS(t), g->next))
				return TRUE;
			if (n == 2 && is_comm(p)		/* swapped operands */
			    && goal2(term_arg(p, 0), term_arg(t, 1), term_arg(p, 1), term_arg(t, 0), g->next))
				return TRUE;
			}
		if (n == 2 && (d = default_of(p, & right_only)))	/* missing operand */
			{
			Node * A = term_arg(p, 0), * B = term_arg(p, 1);
			Node * cp = chain_pos;
			if (! right_only && is_optional(A))
				{
				bind(A, d);
				if (goal(B, t, g->next)) return TRUE;
				restore_to(cp);
				}
			else if (! right_only && bound_to_default(A, d))
				{
				if (goal(B, t, g->next)) return TRUE;
				}
			if (is_optional(B))
				{
				bind(B, d);
				if (goal(A, t, g->next)) return TRUE;
				restore_to(cp);
				}
			else if (bound_to_default(B, d))
				{
				if (goal(A, t, g->next)) return TRUE;
				}
			}
		return FALSE;
		}

	/* argument lists (Terms) and other nodes: both parts */
	if (p->type != t->type) return FALSE;
	return goal2(p->l, t->l, p->r, t->r, g->next);
}

/* ---------------- quick precheck: possible heads of a pattern ----------------
 * For every rule the function names that a matching term (and its first
 * argument) can have are computed once. A missing optional operand can
 * change the head: (a.+b.*x)^m. also matches x. Rules whose heads do not
 * fit are skipped without running the matcher. */

#define MAXHEADS 24
#define HEAD_ATOM "#atom"

typedef struct {
	int any;				/* any head possible */
	int n;
	const char * h[MAXHEADS];
} HeadSet;

typedef struct {
	HeadSet top, first;	/* heads of the term and of its first argument */
	int use_first;
} RuleInfo;

static void hs_add (HeadSet * s, const char * h)
{
	int i;
	for (i = 0; i < s->n; i++)
		if (strcmp(s->h[i], h) == 0) return;
	if (s->n < MAXHEADS) s->h[s->n++] = h;
	else s->any = 1;
}

static void heads_of (Node * p, HeadSet * s)
{
	if (! p) { s->any = 1; return; }
	if (p->type == SYM_TYPE)
		{
		if (lexval((Symbol *) p) == Term && p->l) heads_of(p->l, s);
		else if (lexval((Symbol *) p) == Var) s->any = 1;
		else hs_add(s, HEAD_ATOM);
		return;
		}
	if (p->type == Const) { hs_add(s, HEAD_ATOM); return; }
	if (p->type != Func) { s->any = 1; return; }
	hs_add(s, name(TERM_HEAD(p)));
	if (term_nargs(p) == 2)
		{
		BOOLEAN right_only = FALSE;
		if (default_of(p, & right_only))
			{
			if (! right_only && is_optional(term_arg(p, 0))) heads_of(term_arg(p, 1), s);
			if (is_optional(term_arg(p, 1))) heads_of(term_arg(p, 0), s);
			}
		}
}

static const char * head_name (Node * t)
{
	if (! t) return NULL;
	if (t->type == Func) return name(TERM_HEAD(t));
	if (t->type == Const || t->type == SYM_TYPE) return HEAD_ATOM;
	return NULL;
}

static int hs_has (HeadSet * s, const char * h)
{
	int i;
	if (s->any || ! h) return 1;
	for (i = 0; i < s->n; i++)
		if (strcmp(s->h[i], h) == 0) return 1;
	return 0;
}

#define MAXCACHE 8
static struct { Node * list; int count; RuleInfo * info; } cache[MAXCACHE];

static RuleInfo * rule_info (Node * list)	/* uses cur_settings of the list */
{
	Node * it;
	int count = 0, i, k;
	for (it = list->l; it; it = it->r) count++;
	for (k = 0; k < MAXCACHE; k++)
		if (cache[k].list == list) break;
	if (k < MAXCACHE && cache[k].count == count) return cache[k].info;
	if (k == MAXCACHE)		/* new entry (replace the first one if full) */
		{
		for (k = 0; k < MAXCACHE && cache[k].list; k++)
			;
		if (k == MAXCACHE) k = 0;
		}
	free(cache[k].info);
	cache[k].list = list;
	cache[k].count = count;
	cache[k].info = (RuleInfo *) calloc(count ? count : 1, sizeof(RuleInfo));
	if (! cache[k].info) fatal("listmatch : no room");
	for (i = 0, it = list->l; it; it = it->r, i++)
		{
		Node * lhs = FORM_LHS(it->l);
		RuleInfo * r = & cache[k].info[i];
		BOOLEAN ro;
		heads_of(lhs, & r->top);
		/* first argument only if the head itself cannot change or swap */
		if (lhs && lhs->type == Func && term_nargs(lhs) >= 1
		    && ! is_comm(lhs) && ! default_of(lhs, & ro))
			{
			r->use_first = 1;
			heads_of(term_arg(lhs, 0), & r->first);
			}
		}
	return cache[k].info;
}

int lm_start = 0, lm_last = -1;

Node * match_list (Node * term, Node * list)
{
	Node * it;
	RuleInfo * info;
	const char * th, * fh = NULL;
	int i, start = lm_start;
	lm_start = 0;			/* nested calls (conditions) start at 0 */
	cur_settings = list->r;
	info = rule_info(list);
	th = head_name(term);
	if (term && term->type == Func && term_nargs(term) >= 1)
		fh = head_name(term_arg(term, 0));
	for (i = 0, it = list->l; it; it = it->r, i++)
		{
		Node * cp;
		if (i < start) continue;
		if (! hs_has(& info[i].top, th)) continue;
		if (info[i].use_first && fh && ! hs_has(& info[i].first, fh)) continue;
		cp = chain_pos;
		cur_res = FORM_RES(it->l);
		if (goal(FORM_LHS(it->l), term, NULL))
			{
			DEBG((2,"[rule %d: ", i));
			DBFK(2,print(FORM_LHS(it->l)));
			DEBG((2," = "));
			DBFK(2,print(RES_RHS(cur_res)));
			DEBG((2,"]\n"));
			lm_last = i;
			return cur_res;
			}
		restore_to(cp);
		}
	return NULL;
}

Node * rulelist_add (Node * list, Node * lhs, Node * res, Node * settings)
{
	Node * item = mknod(PARAM, mknod(Form, lhs, res), NULL), * l;
	if (! list)
		list = mknod(RULELIST, NULL, NULL);
	if (settings)
		{
		delete(list->r);		/* latest settings apply to the whole list */
		list->r = settings;
		}
	if (! list->l)
		list->l = item;
	else
		{
		for (l = list->l; l->r; l = l->r)
			;
		l->r = item;
		}
	return list;
}
