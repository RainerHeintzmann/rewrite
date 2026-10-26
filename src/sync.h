#ifndef SYNC_H
#define SYNC_H

/*
 *	sync.h V1.00
 *	Copyright (c) Rainer Heintzmann 1992
 *
 *	function prototypes for parser run-time routines
 */

#include <stdio.h>    /* for readinput(FILE * fp); */

extern void include (const char *);

extern void rebuild_mat(void);

extern void termlist_is_termlist(Node * np);

extern void sequence (Node * np);						/* executes instructions one after another */

extern BOOLEAN rm_term_in(Node *,Node **); /* skips 'to_remove' */

extern int termassign2 (Node * toass, Node * froass);

extern Node * get_type(Node * np);

extern void termassign (Node * np);

extern void history_store (Node * np);

extern void printterm (Node * np);
extern void typeof_fn (Node * np);		/* 2026: TYPEOF term */
extern void typeof_func (Node * np);	/* 2026: TYPEOF f */
void console_utf8 (void);			/* 2026: console.c */
const char * windows_home (void);	/* 2026: console.c */
void print_variants (Symbol * f);	/* 2026: TYPEOF f, ?f */

extern void printstring (Node * np);

extern void printnl (Node * np);

extern void setdebug (Node * np);

extern void numassign2 (Node * froass,Symbol * toass);

extern void numassign (Node * np);   /* sets or deletes a number */

extern void while_fn (Node * np);

extern void if_fn (Node * np);

extern void for_loop (Node * np);

extern void changeout (Node * np);

extern void readdata (Node * np);

extern void changedata (Node * np);

extern void system_fn (Node * np);

extern void include_fn (Node * np);

extern void info_fn (Node * np);

extern void rewrite_ass_fn (Node * np);

extern void rewrite_fn (Node * np);

extern void quit_fn (Node * np);

extern BOOLEAN IS_follows (Symbol * from,Symbol * to);
extern BOOLEAN variant_fits (Symbol * t,Symbol * p);	/* 2026: + : real,real fits + : number,number */

extern Symbol * IS_search (Symbol * from,Symbol * to);

extern BOOLEAN lock_rtypes (Symbol * which,Symbol * from,Node ** chain);

extern Symbol * getsymbol (Symbol * symbol,Node * termlist); /* picks, among symbols of the same name, the one with the right arguments */
extern Symbol * getsymbol_widen (Symbol * symbol,Node * termlist); /* 2026: with SUBSORT extension, NULL if none fits */
extern void retype_term (Node * t);  /* 2026: choose variants according to the sorts of the arguments */
extern void retype_node (Node * t);  /* 2026: the same, only for this node */

extern int read_input (FILE * fp);

extern void include (const char * cp);

#endif
