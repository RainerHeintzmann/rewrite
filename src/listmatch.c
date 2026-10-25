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

/* ---------------- regrouping of commutative operators ----------------
 * Mathematica's Times is flat: a pattern u*(a+b*f(x)) matches x^2*f(x)*g
 * with u = x^2*g. The terms here are binary trees, so for a commutative
 * operator the factors of a nested product are split into two groups in
 * every way, and each group becomes a temporary product. The bindings of
 * the meta variables point into these nodes until the result of the rule
 * is built; they are freed at the next outermost match_list call. */

#define MAXFLAT 6
static Node ** arena = NULL;
static int arena_n = 0, arena_cap = 0;
static int ml_depth = 0;

static Node * arena_node (int type, Node * l, Node * r)
{
	Node * n = mknod(type, l, r);
	if (arena_n == arena_cap)
		{
		arena_cap = arena_cap ? 2 * arena_cap : 64;
		arena = (Node **) realloc(arena, arena_cap * sizeof(Node *));
		if (! arena) fatal("listmatch : no room");
		}
	arena[arena_n++] = n;
	return n;
}

static void arena_free (void)
{
	while (arena_n > 0) delnod(arena[--arena_n]);
}

/* the operands of nested t = f1 h f2 h ..., or -1 if more than MAXFLAT */
static int flatten (Node * t, const char * h, Node ** f, int n)
{
	if (n < 0) return n;
	if (t->type == Func && term_nargs(t) == 2 && strcmp(name(TERM_HEAD(t)), h) == 0)
		return flatten(term_arg(t, 1), h, f, flatten(term_arg(t, 0), h, f, n));
	if (n == MAXFLAT) return -1;
	f[n] = t;
	return n + 1;
}

static Node * group (Node * head, Node ** f, int n, unsigned mask)	/* subset */
{
	Node * r = NULL;
	int i;
	for (i = 0; i < n; i++)
		if (mask & (1u << i))
			r = r ? arena_node(Func, head, arena_node(Terms, r, f[i])) : f[i];
	return r;
}

static BOOLEAN regroup (Node * p, Node * t, Goal * next);

static Node mq_end;	/* last goal of matchq: t is its condition */

static BOOLEAN lm_solve (Goal * g)
{
	Node * p, * t, * d;
	BOOLEAN right_only = FALSE;
	Symbol * ts;

	if (! g)			/* everything matched: check the condition */
		return COND_CALL(RES_COND(cur_res));
	if (g->p == & mq_end)		/* matchq: its own condition */
		return ! g->t || isnt_zero(g->t);

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
			if (n == 2 && is_comm(p) && regroup(p, t, g->next))	/* other groups */
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

/* see above (regrouping): splits whose groups cannot have a head the
 * pattern operands allow are skipped without matching */
static BOOLEAN regroup (Node * p, Node * t, Goal * next)
{
	Node * f[MAXFLAT];
	HeadSet ha = {0}, hb = {0};
	unsigned mask, all, left;
	const char * h = name(TERM_HEAD(t));
	int nl = flatten(term_arg(t, 0), h, f, 0);	/* the split already tried */
	int n = flatten(t, h, f, 0);
	if (n < 3 || nl < 0) return FALSE;
	heads_of(term_arg(p, 0), & ha);
	heads_of(term_arg(p, 1), & hb);
	all = (1u << n) - 1;
	left = (1u << nl) - 1;
	for (mask = 1; mask < all; mask++)
		{
		unsigned rest = all & ~mask;
		if (mask == left || rest == left) continue;
		if (! hs_has(& ha, (mask & (mask - 1)) ? h : head_name(f[__builtin_ctz(mask)]))
		    || ! hs_has(& hb, (rest & (rest - 1)) ? h : head_name(f[__builtin_ctz(rest)])))
			continue;
		if (goal2(term_arg(p, 0), group(t->l, f, n, mask),
		          term_arg(p, 1), group(t->l, f, n, rest), next))
			return TRUE;
		}
	return FALSE;
}

#define MAXCACHE 8

/* candidate rules for one combination of term head and first-argument head */
typedef struct {
	const char * top, * first;	/* head names (NULL: none) */
	int n;
	int * idx;			/* indices of the candidate rules, ascending */
} Cand;

static long generation = 0;		/* counts rulelist_add calls */

static struct {
	Node * list;
	long gen;			/* generation when built */
	int count;
	RuleInfo * info;
	Node ** items;			/* the rules of the list in order */
	Cand * cand;
	int ncand, capcand;
} cache[MAXCACHE];

static void cache_clear (int k)
{
	int j;
	for (j = 0; j < cache[k].ncand; j++) free(cache[k].cand[j].idx);
	free(cache[k].cand);
	free(cache[k].info);
	free(cache[k].items);
	cache[k].cand = NULL; cache[k].ncand = cache[k].capcand = 0;
	cache[k].info = NULL; cache[k].items = NULL;
}

static int rule_info (Node * list)	/* cache entry of the list; uses cur_settings */
{
	Node * it;
	int count = 0, i, k;
	for (k = 0; k < MAXCACHE; k++)
		if (cache[k].list == list) break;
	if (k < MAXCACHE && cache[k].gen == generation) return k;
	if (k == MAXCACHE)		/* new entry (replace the first one if full) */
		{
		for (k = 0; k < MAXCACHE && cache[k].list; k++)
			;
		if (k == MAXCACHE) k = 0;
		}
	cache_clear(k);
	for (it = list->l; it; it = it->r) count++;
	cache[k].list = list;
	cache[k].gen = generation;
	cache[k].count = count;
	cache[k].info = (RuleInfo *) calloc(count ? count : 1, sizeof(RuleInfo));
	cache[k].items = (Node **) calloc(count ? count : 1, sizeof(Node *));
	if (! cache[k].info || ! cache[k].items) fatal("listmatch : no room");
	for (i = 0, it = list->l; it; it = it->r, i++)
		{
		Node * lhs = FORM_LHS(it->l);
		RuleInfo * r = & cache[k].info[i];
		BOOLEAN ro;
		cache[k].items[i] = it;
		heads_of(lhs, & r->top);
		/* first argument only if the head itself cannot change or swap */
		if (lhs && lhs->type == Func && term_nargs(lhs) >= 1
		    && ! is_comm(lhs) && ! default_of(lhs, & ro))
			{
			r->use_first = 1;
			heads_of(term_arg(lhs, 0), & r->first);
			}
		}
	return k;
}

static int same_name (const char * a, const char * b)
{
	return a == b || (a && b && strcmp(a, b) == 0);
}

/* the candidate rules for a term with head th and first-argument head fh:
 * computed once per combination, then taken from the cache */
static Cand * candidates (int k, const char * th, const char * fh)
{
	Cand * c;
	int j, i;
	for (j = 0; j < cache[k].ncand; j++)
		if (same_name(cache[k].cand[j].top, th) && same_name(cache[k].cand[j].first, fh))
			return & cache[k].cand[j];
	if (cache[k].ncand == cache[k].capcand)
		{
		cache[k].capcand = cache[k].capcand ? 2 * cache[k].capcand : 16;
		cache[k].cand = (Cand *) realloc(cache[k].cand, cache[k].capcand * sizeof(Cand));
		if (! cache[k].cand) fatal("listmatch : no room");
		}
	c = & cache[k].cand[cache[k].ncand++];
	c->top = th; c->first = fh; c->n = 0;
	c->idx = (int *) malloc((cache[k].count ? cache[k].count : 1) * sizeof(int));
	if (! c->idx) fatal("listmatch : no room");
	for (i = 0; i < cache[k].count; i++)
		{
		RuleInfo * r = & cache[k].info[i];
		if (! hs_has(& r->top, th)) continue;
		if (r->use_first && fh && ! hs_has(& r->first, fh)) continue;
		c->idx[c->n++] = i;
		}
	return c;
}

int lm_start = 0, lm_last = -1;

static Node * match_rules (Node * term, Node * list);

Node * match_list (Node * term, Node * list)
{
	Node * r, * settings = cur_settings, * res = cur_res;
	double t0 = 0;
	if (ml_depth == 0) arena_free();	/* the last result is built by now */
	if (ml_depth == 0 && profiling()) t0 = profile_now();
	ml_depth++;
	r = match_rules(term, list);
	ml_depth--;
	if (ml_depth == 0 && t0 > 0)		/* outermost only (REWRITE_PROFILE) */
		{
		prof_match_secs += profile_now() - t0;
		prof_match_calls++;
		}
	if (ml_depth > 0)		/* nested (ATT RULES in a condition): the outer list again */
		{
		cur_settings = settings;
		cur_res = res;
		}
	return r;
}

static Node * match_rules (Node * term, Node * list)
{
	Cand * c;
	const char * th, * fh = NULL;
	int k, j, start = lm_start;
	lm_start = 0;			/* nested calls (conditions) start at 0 */
	cur_settings = list->r;
	k = rule_info(list);
	th = head_name(term);
	if (term && term->type == Func && term_nargs(term) >= 1)
		fh = head_name(term_arg(term, 0));
	c = candidates(k, th, fh);
	for (j = 0; j < c->n; j++)
		{
		int i = c->idx[j];
		Node * cp, * it;
		if (i < start) continue;
		it = cache[k].items[i];
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

/* ---------------- matchq ----------------
 * Rubi's MatchQ[u, pattern /; cond]: does term match pattern (with the
 * settings of the current rule list: optional operands, commutativity), and
 * is cond true for the bindings? The bindings are undone afterwards, so the
 * pattern variables must be others than those of the rule being tried. */
BOOLEAN lm_matchq (Node * pattern, Node * term, Node * cond)
{
	Node * cp = chain_pos, * res = cur_res;
	Goal end;
	BOOLEAN ok;
	end.p = & mq_end; end.t = cond; end.next = NULL;
	ok = goal(pattern, term, & end);
	restore_to(cp);
	cur_res = res;
	return ok;
}

/* last element of each rule list, so that adding a rule does not walk the list */
#define MAXTAILS 32
static struct { Node * list, * tail; } tails[MAXTAILS];

Node * rulelist_add (Node * list, Node * lhs, Node * res, Node * settings)
{
	Node * item = mknod(PARAM, mknod(Form, lhs, res), NULL), * l = NULL;
	int t;
	generation++;
	if (! list)
		{
		list = mknod(RULELIST, NULL, NULL);
		for (t = 0; t < MAXTAILS; t++)	/* a freed list may have had this address */
			if (tails[t].list == list) tails[t].tail = NULL;
		}
	if (settings)
		{
		delete(list->r);		/* latest settings apply to the whole list */
		list->r = settings;
		}
	for (t = 0; t < MAXTAILS; t++)
		if (tails[t].list == list) break;
	if (! list->l)
		list->l = item;
	else
		{
		if (t < MAXTAILS && tails[t].tail && ! tails[t].tail->r)
			l = tails[t].tail;
		else
			for (l = list->l; l->r; l = l->r)
				;
		l->r = item;
		}
	if (t == MAXTAILS)			/* new entry (replace the first one if full) */
		{
		for (t = 0; t < MAXTAILS && tails[t].list; t++)
			;
		if (t == MAXTAILS) t = 0;
		tails[t].list = list;
		}
	tails[t].tail = item;
	return list;
}
