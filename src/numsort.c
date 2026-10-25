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
#include "userfkt.h"
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

void subsort_def (Node * np)		/* FUNC(subsort_def, PARAM(from, PARAM(to, conv))) */
{
	Node * p = np->r;
	Node * from = p->l, * to = p->r->l;
	u_function * conv = (u_function *) p->r->r;
	int i = find_pair(from, to);
	p->r->r = NULL;				/* not a node: must not be deleted */
	if (! conv)
		{
		ErrorMsg("SUBSORT needs a C conversion function (ATT name)\n");
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
}

void intnum_def (Node * np)		/* FUNC(intnum_def, PARAM(sort, read function)) */
{
	Node * p = np->r;
	intsort = (Symbol *) p->l;
	intread = (u_function *) p->r;
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

int sort_dist (Node * from, Node * to)
{
	return shortest(from, to, NULL);
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
		w = (sub[i].conv)(arg);
		if (v != value && del(sub[i].from))	/* intermediate value */
			((void (*) (void *)) del(sub[i].from)) (v);
		v = w;
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
