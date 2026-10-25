#ifndef EXPAND_H
#define EXPAND_H

/*
 *	expand.h (2026)
 *
 *	Optional pattern parts, commutative operators and combined conditions.
 *	Rules defined while OPT, DEFAULT or COMM are active go into a rule list
 *	with a backtracking matcher (listmatch.c); all other rules into the
 *	rule tree of forms.c as before.
 *
 *	OPT A,B          meta variables A,B may be missing in a pattern
 *	DEFAULT + = 0    a missing operand of + means 0 (both sides)
 *	DEFAULT RIGHT ^ = 1   a missing right operand of ^ means 1
 *	COMM +,*         patterns with + and * also match with swapped operands
 *	IF c1, c2 ...    several conditions, all must hold
 */

#include "run.h"

void    opt_fkt     (Node * np);   /* OPT idlist */
void    comm_fkt    (Node * np);   /* COMM funclist */
void    default_fkt (Node * np);   /* DEFAULT [RIGHT] f = value */
BOOLEAN and_cond    (Node * np);   /* condition list c1, c2 */

/* adds a rule to the rules of an algebra: to a rule list (listmatch.c) if
 * OPT, DEFAULT or COMM are active, otherwise to the rule tree (forms.c) */
Node *  add_rule (Node * lhs, Node * res, Node * tree);

#endif
