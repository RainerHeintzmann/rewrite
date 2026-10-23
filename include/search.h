#ifndef	_SEARCH_H
#define	_SEARCH_H

/*
 *	search.h -- 1.2 Apr 23 07:27:43 1991
 *	Copyright (c) 1991 Axel T. Schreiner
 *
 *	definitions for tsearch() and hsearch() family
 *	ANSI-ized
 */

#include "ansi.h"

/*
 *	hsearch()
 */

typedef struct { char * key, * data; } ENTRY;
typedef enum { FIND, ENTER } ACTION;

void	hdestroy	_0p (void);
int	hcreate		_1p (unsigned);
ENTRY *	hsearch		_2p (ENTRY, ACTION);

/*
 *	tsearch()
 */

typedef enum { preorder, postorder, endorder, leaf } VISIT;

/*
 *	System V stuff
 */

void ** tsearch	_3p (const void *, const void **,		/* find/add */
			int (*)(const void *, const void *));
void **	tfind	_3p (const void *, const void * const *,	/* find/NULL */
			int (*)(const void *, const void *));
void **	tdelete	_3p (const void *, const void **,		/* remove */
			int (*)(const void *, const void *));
void	twalk	_2p (const void *,				/* traverse */
			void (*)(void **, VISIT, int));

/*
 *	frills
 */

void **	tload	_2p (const void * (*)(void), const void **);	/* force add */

								/* traverse */
void	tend	_2p (const void *, void (*)(void **, VISIT));
void	tpost	_2p (const void *, void (*)(void **, VISIT));
void	tpre	_2p (const void *, void (*)(void **, VISIT));

void **	tfirst	_1p (const void *);				/* loop */
void ** tnext	_3p (const void *, const void * const *,
			int (*)(const void *, const void *));

#endif
