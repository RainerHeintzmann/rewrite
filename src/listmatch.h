#ifndef LISTMATCH_H
#define LISTMATCH_H

/*
 *	listmatch.h (2026)
 *
 *	Rule lists with a backtracking matcher. Rules defined while OPT,
 *	DEFAULT or COMM are active are stored in an ordered list (like Rubi)
 *	instead of the merged rule tree of forms.c. The matcher tries all
 *	argument orders of commutative operators and fills in missing optional
 *	operands; the condition of a rule is part of the match, so a failed
 *	condition makes it try the next possibility.
 *
 *	RULELIST node:  l = rules: PARAM(Form(lhs, result), next)
 *	                r = settings: PARAM(optvars, PARAM(commfuncs, defaults))
 */

#include "run.h"

/* adds a rule (left side, result as built by the parser) to a rule list */
Node * rulelist_add (Node * list, Node * lhs, Node * res, Node * settings);

/* first rule of the list that matches term (with its condition), or NULL;
 * the meta variables stay bound as with match() of forms.c */
Node * match_list (Node * term, Node * list);

/* MatchQ[term, pattern /; cond] (cond may be NULL); the bindings are undone */
BOOLEAN lm_matchq (Node * pattern, Node * term, Node * cond);

/* lm_start: the next match_list call starts with this rule (then reset to 0);
 * lm_last: index of the rule found by the last successful match_list call.
 * Used to skip a rule whose result equals the term (no progress). */
extern int lm_start, lm_last;

#endif
