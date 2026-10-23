#ifndef	_TSEARCH_H
#define	_TSEARCH_H

/*
 *	tsearch.h -- 2.1 Apr 22 15:39:58 1991
 *	Copyright (c) 1987-1991 Axel T. Schreiner
 *
 *	tsearch() using binary threaded trees, header file
 *	ANSI-ized, private to library
 */

#include <search.h>

#if	1

typedef struct Node Node;		/* search tree element */
	struct Node {
		void * _key;		/* user's information */
		Node * _l, * _r;	/* tree */
		char _rtag;		/* marks thread */
	};

#define	key(p)	(((Node *) p) -> _key)		/* access _key */
#define	l(p)	(((Node *) p) -> _l)		/* access _l */
#define	r(p)	(((const Node *) p) -> _r)	/* fetch _r */
#define	rtag(p)	(((Node *) p) -> _rtag)		/* access thread bit */
#define	rptr(p)	(((Node *) p) -> _r)		/* store _r */

const void * const * _tfnd			/* internal: tsearch.c */
	_5p (const void *, const void * const *,
	int (*)(const void *, const void *), const void **, int *);

#else	/* bit-fiddling no longer supported */

	#ifdef	M_XENIX

	#ifdef	M_SDATA		/* assert sizeof(Int) == sizeof(char *) */
		typedef	int Int;
	#else
		typedef long Int;
	#endif

	typedef struct {	/* assert _bit is unused bit of (char *) */
		unsigned _bit: 1;
		} Bit;
	#define	BITMASK	(~1)	/* assert clears _bit in (char *) */
				/* assert: pointer assign does not set _bit */

	typedef struct node {			/* search tree element */
		char * _key;			/* user's information */
		struct node * _l;		/* left link */
		union {
			struct node * _ptr;	/* right link or thread */
			Int _i;			/* for fiddling */
			Bit _tag;		/* thread bit */
			} _r;
		} Node;

	#define	key(p)	((p) -> _key)		/* access _key */
	#define	l(p)	((p) -> _l)		/* access _l */
	#define	rtag(p)	((p) -> _r._tag._bit)	/* access thread bit */
						/* fetch _r._ptr */
	#define	r(p)	((Node *)((p) -> _r._i & BITMASK))
	#define	rptr(p)	((p) -> _r._ptr)	/* store; clears thread */

	#endif

#endif
#endif
