/*
 *	tload.c -- 2.1 Apr 22 17:45:57 1991
 *	Copyright (c) 1987-1991 Axel T. Schreiner
 *
 *	load tree in in(post)order, sorted input makes minimal height
 *	ANSI-ized
 */

#include "tsearch.h"

static const void * load _3a ((getkey, corner, level),
	const void * (* getkey) _0p (void),
	const void * corner,
	int level)
{	const void * p, * root;
	int tag, h = -1;		/* not in tree */
	void * calloc _2p (unsigned, unsigned);
	void free _1p (void *);

	if (! (root = calloc(1, sizeof(Node))))
		return 0;
	if (! (key(root) = (void *) (* getkey)()))
	{	free((void *) root);
		return 0;
	}
	if (corner)
	{	l(root) = r(corner);
		rptr(corner) = (void *) root, rtag(corner) = 1;
		corner = 0;
	}
	while (++ h < level
	       && (p = load(getkey, corner, h)))
	{	corner = p;
		if (rtag(corner))
			break;
	}
	if (corner)
		rptr(root) = r(corner), rtag(root) = 0;
	else
		corner = root;
	tag = h < level || rtag(corner);
	rptr(corner) = (void *) root, rtag(corner) = tag;
	return corner;
}

void ** tload _2a ((getkey, rootp),
	const void * (* getkey) _0p (void),
	const void ** rootp)
{	int level = 0;
	const void * p;

	if (rootp)
	{	*rootp = 0;
		while (p = load(getkey, *rootp, level++))
		{	*rootp = p;
			if (rtag(p))
				break;
		}
		if (p = *rootp)
		{	*rootp = r(p);
			rptr(p) = 0, rtag(p) = 1;
			return & key(p);
		}
	}
	return 0;
}

#ifdef	TEST
/*
 *	test driver
 */

#include <stdio.h>
#include "main.h"

static char ** keys;
static void * root;

static void * getkey _0a (void)
{
	return *keys++;
}

static void show _2a ((pp, kind), void ** pp, VISIT kind)
{
	printf("%s ", (char *) *pp);
}

MAIN
{	void ** cpp;

	keys = ++ argv;
	cpp = tload(getkey, & root);
	printf("load\t%s\n", cpp? (char *) *cpp: "??");
	printf("pre\t"), tpre(root, show), putchar('\n');
	printf("post\t"), tpost(root, show), putchar('\n');
	printf("end\t"), tend(root, show), putchar('\n');
	return 0;
}
#endif
