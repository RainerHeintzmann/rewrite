/*
 *	numsort.c (2026)
 *
 *	Subsorts of numbers (widening) and integer literals, see numsort.h.
 */

#include <stdlib.h>
#include <string.h>

#include "inout.h"
#include "fatal.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "node.h"
#include "nodes.h"
#include "userfn.h"
#include "numsort.h"
#include "exact.h"

void ErrorMsg (const char * s);		/* sync.c */

#define MAXSUB 32

static struct {
	Node * from, * to;		/* sorts */
	u_function * conv;		/* value of 'from' -> value of 'to' */
} sub[MAXSUB];
static int nsub = 0;

static Symbol * intsort = NULL;		/* sort of integer literals */
static u_function * intread = NULL;	/* text -> value */

static int find_pair (Node * from, Node * to)	/* index of from < to, or -1 */
{
	int i;
	for (i = 0; i < nsub; i++)
		if (sub[i].from == from && sub[i].to == to) return i;
	return -1;
}

static void dcache_clear (void);	/* 2026: the sort_dist cache, below */

void subsort_def (Node * np)		/* FUNC(subsort_def, PARAM(from, PARAM(to, conv))) */
{
	Node * p = np->r;
	Node * from = p->l, * to = p->r->l;
	u_function * conv = (u_function *) p->r->r;
	int i = find_pair(from, to);
	p->r->r = NULL;				/* not a node: must not be deleted */
	if (! conv && sort_valued(to))	/* 2026: without ATT: 'to' has no values */
		{
		ErrorMsg("SUBSORT into a sort with values needs a C conversion function (ATT name)\n");
		return;
		}
	if (from == to || sort_dist(to, from) >= 0)
		{
		ErrorMsg("SUBSORT would make a cycle of sorts\n");
		return;
		}
	if (i < 0)
		{
		if (nsub == MAXSUB) fatal("SUBSORT : too many subsorts");
		i = nsub++;
		}
	sub[i].from = from;
	sub[i].to = to;
	sub[i].conv = conv;
	dcache_clear();		/* the distances change */
	if (conv && sort_valued(from)) sort_valued(to) = TRUE;	/* values are converted into to */
}

void intnum_def (Node * np)		/* FUNC(intnum_def, PARAM(sort, read function)) */
{
	Node * p = np->r;
	intsort = (Symbol *) p->l;
	intread = (u_function *) p->r;
	sort_valued(intsort) = TRUE;
	p->r = NULL;				/* not a node: must not be deleted */
	if (! intread)
		{
		ErrorMsg("INTNUM needs a C function that reads the number (ATT name)\n");
		intsort = NULL;
		}
}

/* shortest path from 'from' to 'to' in the graph of subsorts (a sort may
 * have several wider sorts): number of steps, and the first edge of each
 * node on the path in via[] (index into sub[]) */
static int shortest (Node * from, Node * to, int * via)
{
	Node * queue[MAXSUB + 1];
	int dist[MAXSUB + 1], prev[MAXSUB + 1], head = 0, tail = 0, i, k;
	if (! from || ! to) return -1;
	if (from == to) return 0;
	queue[tail] = from; dist[tail] = 0; prev[tail] = -1; tail++;
	while (head < tail)
		{
		Node * s = queue[head];
		for (i = 0; i < nsub; i++)
			{
			if (sub[i].from != s) continue;
			for (k = 0; k < tail; k++)
				if (queue[k] == sub[i].to) break;
			if (k < tail) continue;		/* already reached */
			if (tail > MAXSUB) return -1;
			queue[tail] = sub[i].to; dist[tail] = dist[head] + 1; prev[tail] = head;
			if (via) via[tail] = i;
			if (sub[i].to == to)
				{
				if (via)			/* path: edges in order, end with -1 */
					{
					int path[MAXSUB + 1], n = 0, j = tail;
					while (prev[j] >= 0) { path[n++] = via[j]; j = prev[j]; }
					for (j = 0; j < n; j++) via[j] = path[n - 1 - j];
					via[n] = -1;
					}
				return dist[tail];
				}
			tail++;
			}
		head++;
		}
	return -1;
}

/* 2026: sort_dist is asked for every argument of every variant when a
   variant is chosen, and the search through the subsort graph was the most
   expensive part of it: the distances are kept, until a SUBSORT changes the
   graph. A sort gets an index in its symbol (sortno). */
#define MAXSORTS 128
static signed char dcache[MAXSORTS][MAXSORTS];	/* -2: not known yet */
static Symbol * dsorts[MAXSORTS];
static int ndsorts = 0;

static void dcache_clear (void)
{
	int i;
	for (i = 0; i < ndsorts; i++) dsorts[i]->sortno = 0;
	ndsorts = 0;
}

static int sort_index (Symbol * s)		/* -1 if the cache is full */
{
	int i;
	if (s->sortno > 0) return s->sortno - 1;
	if (ndsorts == MAXSORTS) return -1;
	i = ndsorts++;
	dsorts[i] = s;
	s->sortno = i + 1;
	memset(dcache[i], -2, sizeof dcache[i]);
	for (i = 0; i < ndsorts; i++) dcache[i][ndsorts - 1] = -2;
	return ndsorts - 1;
}

int sort_dist (Node * from, Node * to)
{
	int i, j;
	if (! from || ! to) return -1;
	if (from == to) return 0;
	i = sort_index((Symbol *) from);
	j = sort_index((Symbol *) to);
	if (i < 0 || j < 0) return shortest(from, to, NULL);
	if (dcache[i][j] == -2) dcache[i][j] = (signed char) shortest(from, to, NULL);
	return dcache[i][j];
}

/* 2026: a term of a sort without values (not sort_valued, e.g. a list
   [1,2,3] of inc/list) as a value of the sort 'to', if a SUBSORT path
   leads there: the first conversion of the path gets the values of the
   arguments of the term, as numbers of the standard sort (REALNUM), e.g.
   SUBSORT vector,rvector ATT constr_vec. NULL if this is not possible. */
void * term_convert (Node * term, Node * to)
{
	void * args[MAXARGS], * v;
	Node * a, * from, * nt = get_numbertype();
	int via[MAXSUB + 2], n = 0, i, err = FALSE;
	if (! term || term->type != Func || ! to || ! nt) return NULL;
	from = rtypes(TERM_HEAD(term));
	if (! from || sort_valued(from) || shortest(from, to, via) <= 0) return NULL;
	for (a = TERM_ARGS(term); a && n < MAXARGS - 1; a = ARGS_NEXT(a))
		{
		Node * s;
		v = realcalc(ARGS_ITEM(a), & err);
		s = realcalc_sort();
		if (err || ! v || ! s) { err = TRUE; break; }
		if (s != nt)		/* an element as a standard number */
			{
			void * w = sort_dist(s, nt) > 0 ? sort_convert(v, s, nt) : NULL;
			((void (*) (void *)) del(s)) (v);
			if (! w) { err = TRUE; break; }
			v = w;
			}
		args[n++] = v;
		}
	args[n] = NULL;
	v = (err || a) ? NULL : (sub[via[0]].conv)(args);
	for (i = 0; i < n; i++)
		((void (*) (void *)) del(nt)) (args[i]);
	if (v && via[1] >= 0)		/* the rest of the path */
		{
		void * w = sort_convert(v, sub[via[0]].to, to);
		((void (*) (void *)) del(sub[via[0]].to)) (v);
		v = w;
		}
	return v;
}

void * sort_convert (void * value, Node * from, Node * to)
{
	void * v = value, * arg[2];
	int via[MAXSUB + 2], j;
	if (from == to) return ((void * (*) (void *)) cpy(from)) (value);
	if (shortest(from, to, via) < 0) return NULL;
	for (j = 0; via[j] >= 0; j++)
		{
		int i = via[j];
		void * w;
		arg[0] = v; arg[1] = NULL;
		w = sub[i].conv ? (sub[i].conv)(arg) : NULL;	/* none: a sort without values */
		if (v != value && del(sub[i].from))	/* intermediate value */
			((void (*) (void *)) del(sub[i].from)) (v);
		v = w;
		if (! v) break;
		}
	return v;
}

Symbol * int_literal (const char * text)
{
	void * arg[2], * v;
	if (! intsort) return NULL;
	arg[0] = (void *) text; arg[1] = NULL;
	v = intread(arg);
	if (! v) return NULL;
	return mknum(v, (Node *) intsort);
}

static Node * named_sort (const char * n)	/* a declared sort of that name */
{
	Symbol * s = find_symbol(n);
	return (s && lexval(s) == Sort) ? (Node *) s : NULL;
}

static Node * ratsort (void)		/* the sort of fractions */
{
	return intsort ? named_sort("rational") : NULL;
}

static Node * integersort (void)	/* the sort of all integers (negative too) */
{
	Node * z = named_sort("integer");
	return z ? z : (Node *) intsort;
}

BOOLEAN sort_exact (Node * s)		/* integer, rational, natural: exact numbers */
{
	Node * rs = ratsort();
	return rs && s && sort_dist(s, rs) >= 0;
}

BOOLEAN exact_numbers (void)
{
	return intsort != NULL && ratsort() != NULL;
}

Symbol * make_exact (long long p, long long q)
{
	if (! exact_numbers() || q == 0) return NULL;
	if (q == 1)	/* literal sort (natural) for p >= 0 if it holds them */
		{
		Node * s = (p >= 0) ? (Node *) intsort : integersort();
		return mknum(int_from_ll(p), s);	/* natural and integer: both mpz */
		}
	return mknum(rat_from_ll(p, q), ratsort());
}

BOOLEAN num_exact (Symbol * s)		/* natural, integer, rational: below rational */
{
	Node * r = ratsort();
	return s && r && sort_dist(rtypes(s), r) >= 0;
}

Symbol * exact_root (Symbol * s, long k)
{
	void * q, * r;
	Node * rs = ratsort();
	if (! num_exact(s) || ! rs) return NULL;
	q = sort_convert(value(s), rtypes(s), rs);
	if (! q) return NULL;
	r = rat_root_exact(q, k);
	((void (*) (void *)) del(rs)) (q);
	return r ? mknum(r, rs) : NULL;
}

BOOLEAN num_to_double (Symbol * num, double * v)
{
	Node * nt = get_numbertype();
	void * w;
	if (! num || ! hasval(num) || ! value(num)) return FALSE;
	if (rtypes(num) == nt)
		{
		* v = * (double *) value(num);
		return TRUE;
		}
	if (sort_dist(rtypes(num), nt) < 0) return FALSE;
	w = sort_convert(value(num), rtypes(num), nt);
	if (! w) return FALSE;
	* v = * (double *) w;
	((void (*) (void *)) del(nt)) (w);
	return TRUE;
}

BOOLEAN sort_top (Node * s)		/* no wider sort (number, bool, ...) */
{
	int i;
	for (i = 0; i < nsub; i++)
		if (sub[i].from == s) return FALSE;
	return TRUE;
}

BOOLEAN var_sort_ok (Node * vsort, Node * term)
{
	int i;
	Node * s;
	for (i = 0; i < nsub; i++)		/* only sorts that are subsorts of another */
		if (sub[i].from == vsort) break;
	if (i == nsub) return TRUE;
	s = arg_sort(term);
	return s == NULL || sort_dist(s, vsort) >= 0;
}

Node * arg_sort (Node * a)
{
	if (! a) return NULL;
	if (a->type == SYM_TYPE) return rtypes((Symbol *) a);
	if (a->type == Terms) return NULL;
	return rtypes((Symbol *) a->l);
}

void * exact_to_rat (Symbol * s)
{
	Node * rs = ratsort();
	if (! num_exact(s) || ! rs) return NULL;
	return sort_convert(value(s), rtypes(s), rs);
}

Symbol * make_exact_rat (void * q)
{
	Node * rs = ratsort();
	if (! rs) { del_rat(q); return NULL; }
	if (rat_is_integer(q))
		{
		Node * s = (rat_sgn(q) >= 0) ? (Node *) intsort : integersort();
		void * z = rat_numer(q);
		del_rat(q);
		return mknum(z, s);
		}
	return mknum(q, rs);
}
