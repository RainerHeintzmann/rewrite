#ifndef	RUN_H
#define	RUN_H

/*
 *	run.h V1.00
 *	Copyright (c) Rainer Heintzmann 1992
 *
 *	function prototypes and Node structure
 */

#include "ansi.h"
#include "fatal.h"

typedef struct Node Node;
struct Node {
	int	type;				/* type of the node */
	Node * l, * r;			/* operands */
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
Node * realcalc_sort (void);
void * realcalc (Node * term, int * perr);
void delete _1p (Node * );
Node * tcopy _1p(Node *);
Node * tcalc _1p(Node *);
Node * calculate _1p(Node *);
extern int calc_exact_only;   /* 2026: 1: no real value for 2^(1/2) */
void print	_1p(Node *);
Node * solve	_2p(Node * ,Node *);
Node * rewrite _2p(Node * ,Node *);
void rewrite_begin (void);   /* 2026: step limit for REWR */
void steps_fn (Node * np);  /* 2026: STEPS Alg "file": show the solution steps */
void rewrite_end (void);
void * rewrite_push (void);  /* 2026: nested REWR (ATT RULES): set the outer state aside */
void rewrite_pop (void * p);
extern long max_rewrite_steps;
extern long max_term_depth;

/* condition functions */

void prt_num(Node *);

BOOLEAN truefunc      _1p (Node *);
BOOLEAN lower_between _1p (Node *);
BOOLEAN in_tree       _1p (Node *);
BOOLEAN not_in_tree   _1p (Node *);
BOOLEAN isnt_zero		  _1p (Node *);
#endif

/* 2026: Ctrl-C stops the running REWR or loop (run.c) */
#include <signal.h>
extern volatile sig_atomic_t rw_interrupted;
void on_interrupt (int sig);
