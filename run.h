#ifndef	RUN_H
#define	RUN_H

/*
 *	run.h V1.00
 *	Copyright (c) Rainer Heintzmann 1992
 *
 *	Funktionsprototypen und Node-struktur
 */

#include "ansi.h"
#include "fatal.h"

typedef struct Node Node;
struct Node {
	int	type;				/* Typ des Knotens */
	Node * l, * r;			/* Operanden */
};

typedef int BOOLEAN ;

#define FALSE	0
#define TRUE	(! FALSE)
#define IS_FUNCTION(lexvalue) ((lexvalue == Func) || \
                               (lexvalue == La1)  || \
                               (lexvalue == La2)  || \
                               (lexvalue == La3)  || \
                               (lexvalue == La4)  || \
                               (lexvalue == La5)  || \
                               (lexvalue == Ra)   || \
                               (lexvalue == Ru)   || \
                               (lexvalue == Bra)  || \
                               (lexvalue == Bra1)    )

void tprint _2p(Node *,int);

Node * mknod _3p (int,Node *,Node *);
void set_numbertype(Node * np);
Node * get_numbertype(void);
void delete _1p (Node * );
Node * tcopy _1p(Node *);
Node * tcalc _1p(Node *);
Node * calkulate _1p(Node *);
void print	_1p(Node *);
Node * solve	_2p(Node * ,Node *);
Node * rewrite _2p(Node * ,Node *);
void rewrite_begin (void);   /* 2026: Schrittbegrenzung fuer REWR */
void rewrite_end (void);
extern long max_rewrite_steps;

/* Condition-Funktionen */

void prt_num(Node *);

BOOLEAN truefunc      _1p (Node *);
BOOLEAN lower_between _1p (Node *);
BOOLEAN in_tree       _1p (Node *);
BOOLEAN not_in_tree   _1p (Node *);
BOOLEAN isnt_zero		  _1p (Node *);
#endif
