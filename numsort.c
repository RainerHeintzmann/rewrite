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

static int find_sub (Node * from)	/* index of the widening of 'from', or -1 */
{
	int i;
	for (i = 0; i < nsub; i++)
		if (sub[i].from == from) return i;
	return -1;
}

void subsort_def (Node * np)		/* FUNC(subsort_def, PARAM(from, PARAM(to, conv))) */
{
	Node * p = np->r;
	Node * from = p->l, * to = p->r->l;
	u_function * conv = (u_function *) p->r->r;
	int i = find_sub(from);
	p->r->r = NULL;				/* not a node: must not be deleted */
	if (! conv)
		{
		ErrorMsg("SUBSORT needs a C conversion function (ATT name)\n");
		return;
		}
	if (sort_dist(to, from) >= 0)
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

int sort_dist (Node * from, Node * to)
{
	int d = 0, i;
	while (from)
		{
		if (from == to) return d;
		if ((i = find_sub(from)) < 0) return -1;
		from = sub[i].to;
		if (++d > MAXSUB) return -1;
		}
	return -1;
}

void * sort_convert (void * value, Node * from, Node * to)
{
	void * v = value, * arg[2];
	Node * s = from;
	int i;
	if (sort_dist(from, to) < 0) return NULL;
	if (from == to) return ((void * (*) (void *)) cpy(from)) (value);
	while (s != to)
		{
		i = find_sub(s);
		arg[0] = v; arg[1] = NULL;
		{
		void * w = (sub[i].conv)(arg);
		if (v != value && del(s))		/* intermediate value */
			((void (*) (void *)) del(s)) (v);
		v = w;
		}
		s = sub[i].to;
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

static Node * ratsort (void)		/* the sort above the integer sort */
{
	int i;
	if (! intsort) return NULL;
	i = find_sub((Node *) intsort);
	return (i < 0) ? NULL : sub[i].to;
}

BOOLEAN exact_numbers (void)
{
	return intsort != NULL && ratsort() != NULL;
}

Symbol * make_exact (long long p, long long q)
{
	if (! exact_numbers() || q == 0) return NULL;
	if (q == 1) return mknum(int_from_ll(p), (Node *) intsort);
	return mknum(rat_from_ll(p, q), ratsort());
}

BOOLEAN num_exact (Symbol * s)
{
	Node * nt = get_numbertype();
	return s && rtypes(s) != nt && sort_dist(rtypes(s), nt) > 0;
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

Node * arg_sort (Node * a)
{
	if (! a) return NULL;
	if (a->type == SYM_TYPE) return rtypes((Symbol *) a);
	if (a->type == Terms) return NULL;
	return rtypes((Symbol *) a->l);
}
