/*
 *	tsearch.c -- 2.1 Apr 22 16:48:37 1991
 *	Copyright (c) 1987-1991 Axel T. Schreiner
 *
 *	tsearch() using binary threaded trees
 *	ANSI-ized
 */

#include "tsearch.h"

/*
 *	internal search function
 *
 *	tfnd()	*tfnd()	*parent	*c
 *	----------------------------------------------------
 *	0	?	0	?	error: rootp was 0
 *	----------------------------------------------------
 *	!=0	0	0	?	empty tree
 *	!=0	0	!=0	<0	l(*parent) == tfnd()
 *	!=0	0	!=0	>0	r(*parent) == tfnd()
 *	!=0	!=0	!=0	>0	r(*parent) == tfnd()
 *	----------------------------------------------------
 *	!=0	!=0	0	0	key(*tfnd()) == k
 *	!=0	!=0	!=0	0	?(parent) == tfnd()
 */

const void * const * _tfnd _5a ((k, rootp, cmp, parent, c),
	const void * k,			/* user's information */
	const void * const * rootp,	/* -> -> first Node */
	int (* cmp) _2p (const void *, const void *),
	const void ** parent,		/* output */
	int * c)
{
	*parent = 0;
	if (rootp				/* else _tfnd() == 0 */
	    && *rootp)				/* else *_tfnd() == 0 */
		for (;;)			/* *_tfnd() != 0 */
		{	if ((*c = (* cmp)(k, key(*rootp))) == 0)
				break;		/* *c == 0 */
			*parent = *rootp;
			if (*c < 0)
			{	rootp = (const void * const *) & l(*parent);
				if (! *rootp)
					break;
			}
			else
			{	rootp = (const void * const *) & rptr(*parent);
				if (rtag(*parent))
					break;
			}
		}
	return rootp;
}

/*
 *	search function
 */

void ** tsearch _3a ((k, rootp, cmp),	/* -> key, -> old key, or NULL */
	const void * k,			/* user's information */
	const void ** rootp,		/* -> -> first Node */
	int (* cmp) _2p (const void *, const void *))
{	void * p;
	const void * parent; int c;
	void * malloc _1p (unsigned);

	if (rootp = (const void **) _tfnd(k, rootp, cmp, & parent, & c))
		if (* rootp && c == 0)
			return & key(* rootp);
		else if (p = malloc(sizeof(Node)))
		{	key(p) = (void *) k;
			l(p) = 0;
			if (parent && c > 0)
			{	rptr(p) = r(parent);
				rptr(parent) = p, rtag(parent) = 0;
			}
			else
			{	rptr(p) = (void *) parent;
				* rootp = p;
			}
			rtag(p) = 1;
			return & key(p);
		}
	return 0;
}

#ifdef	TEST
/*
 *	test driver
 */

#include <stdio.h>
#include <string.h>
#include "main.h"

static const void * root;		/* tree */

static void show _2a ((pp, kind), void ** pp, VISIT kind)
{
	printf("%s ", (char *) *pp);
}

MAIN
{	void ** cpp;
	typedef int (* cmp) _2p (const void *, const void *);

	IFANY
	{	ARG 'c':		/* -c clear */
			printf("clear\t"), tfree(& root, show), putchar('\n');
		ARG 'd': PARM		/* -d object to delete */
			cpp = tdelete(*argv, & root, (cmp) strcmp);
			printf("del %s\t%s\n", *argv, cpp? *cpp: "??");
			NEXTOPT
		ARG 'e':		/* -e endorder output */
			printf("end\t"), tend(root, show), putchar('\n');
		ARG 'f': PARM		/* -f object to find */
			cpp = tfind(*argv, & root, (cmp) strcmp);
			printf("find %s\t%s\n", *argv, cpp? *cpp: "??");
			NEXTOPT
		ARG 'i':		/* -i in(post)order output */
			printf("post\t"), tpost(root, show), putchar('\n');
		ARG 'p':		/* -p preorder output */
			printf("pre\t"), tpre(root, show), putchar('\n');
		OTHER
			puts("tsearch [-piec] [-d x] [-f x] [x] ...");
			exit(1);
		ANY			/* object to enter */
			cpp = tsearch(*argv, & root, (cmp) strcmp);
			printf("add %s\t%s\n", *argv, cpp? *cpp: "??");
	}
	return 0;
}
#endif
