/*
 *	bsearch.c -- 1.1 Apr 23 07:34:47 1991
 *	Copyright (c) 1987-1991 Axel T. Schreiner
 *
 *	bsearch() -- binary search
 *	ANSI-ized, note the const-pun
 */

#include "ansi.h"

void * bsearch _5a ((key, _base, nel, width, cmp),
	const void * key, const void * _base, unsigned nel, unsigned width,
	int (* cmp) _2p (const void *, const void *))
{
#define	base	((const char *) _base)
	const char * lim = base + nel * width, * mid, * high;
	int c;

	for (high = lim - width; base <= high; nel >>= 1)
	{	mid = base + (nel >> 1) * width;
		if ((c = (* cmp)(key, mid)) < 0)
			high = mid - width;
		else if (c > 0)
			_base = (void *) (mid + width), -- nel;
		else
			return (void *) mid;
	}
	return 0;
#undef	base
}
