#ifndef NODES_H
#define NODES_H

/*
 *	nodes.h (2026)
 *
 *	Named access to the node structures built by the parser (syn.y).
 *	All trees use the binary node of run.h (type, l, r). These macros only
 *	give the fields names; they expand to the same expressions as before,
 *	so the memory layout is unchanged.
 *
 *	Benannter Zugriff auf die Knotenstrukturen aus syn.y. Das Speicher-
 *	layout bleibt gleich, die Makros dokumentieren es.
 */

#include "run.h"

/* ------------------------------------------------------------------
 *	Terms (mathematical expressions)
 *
 *	Func node : type Func, l = function symbol, r = arguments
 *	Const node: type Const, l = constant symbol, r = NULL
 *	arguments : a single argument stands directly in r;
 *	            several arguments form a chain Terms(a1, Terms(a2, a3)),
 *	            the last argument stands directly in the last r.
 *	Var and Term symbols stand directly in the tree (type SYM_TYPE).
 *	See term_nargs, term_arg, term_argp in run.c for argument access.
 * ------------------------------------------------------------------ */

#define TERM_HEAD(t)       ((Symbol *) (t)->l)   /* Func/Const: symbol */
#define TERM_ARGS(t)       ((t)->r)              /* Func: argument list */
#define TERM_CONTENT(sp)   (((Node *) (sp))->l)  /* Term symbol: stored term */

int     term_nargs (Node * t);          /* number of arguments of a Func node */
Node *  term_arg   (Node * t, int i);   /* argument i (0 based) or NULL */
Node ** term_argp  (Node * t, int i);   /* address of argument i, or NULL */

/* Iteration over an argument list (needs syn.h for Terms):
 *	for (a = TERM_ARGS(t); a; a = ARGS_NEXT(a))  ... ARGS_ITEM(a) ... */
#define ARGS_ITEM(a)       ((a)->type == Terms ? (a)->l : (a))
#define ARGS_NEXT(a)       ((a)->type == Terms ? (a)->r : (Node *) NULL)

/* ------------------------------------------------------------------
 *	Instructions: FUNC node, l = C function, r = parameters
 * ------------------------------------------------------------------ */

#define INSTR_FN(np)       ((np)->l)
#define INSTR_PAR(np)      ((np)->r)

/* conditions: Cond node, l = C function returning BOOLEAN, r = argument */
#define COND_FN(c)         ((c)->l)
#define COND_ARG(c)        ((c)->r)
#define COND_CALL(c)       (((BOOLEAN (*) (Node *)) COND_FN(c)) (COND_ARG(c)))

/* PRT list with new line:  FUNC(printnl, FUNC(sequence, list)) */
#define PRINTNL_SEQ(np)    ((np)->r)

/* Term = term, Const = term:  FUNC(f, PARAM(target, term)) */
#define ASSIGN_TARGET(np)  ((np)->r->l)
#define ASSIGN_TERM(np)    ((np)->r->r)

/* WHILE cond body:  FUNC(while_fkt, PARAM(cond, body)) */
#define WHILE_COND(np)     ((np)->r->l)
#define WHILE_BODY(np)     ((np)->r->r)

/* IF cond then [ELSE else]:  FUNC(if_fkt, PARAM(cond, PARAM(then, else))) */
#define IF_COND(np)        ((np)->r->l)
#define IF_THEN(np)        ((np)->r->r->l)
#define IF_ELSE(np)        ((np)->r->r->r)

/* FOR var = from TO to STEP step DO body:
 *	FUNC(forschleife, PARAM(PARAM(from, to), PARAM(PARAM(step, var), body))) */
#define FOR_FROM(np)       ((np)->r->l->l)
#define FOR_TO(np)         ((np)->r->l->r)
#define FOR_STEP(np)       ((np)->r->r->l->l)
#define FOR_VAR(np)        ((np)->r->r->l->r)
#define FOR_BODY(np)       ((np)->r->r->r)

/* REWR term : algs:  FUNC(rewrite_fkt, PARAM(term, algs)) */
#define REWR_TERM(np)      ((np)->r->l)
#define REWR_ALGS(np)      ((np)->r->r)

/* Term = REWR term : algs:  FUNC(rewrite_ass_fkt, PARAM(Term, PARAM(term, algs))) */
#define REWRASS_TARGET(np) ((np)->r->l)
#define REWRASS_TERM(np)   ((np)->r->r->l)
#define REWRASS_ALGS(np)   ((np)->r->r->r)

/* LIFT (from) TO (to):  FUNC(termlist_is_termlist, PARAM(to, from)) */
#define LIFT_TO(np)        ((np)->r->l)
#define LIFT_FROM(np)      ((np)->r->r)

/* declarations (CONST, VAR, FUNC, ...):
 *	FUNC(declare, lexv-node(idlist, hasv-node(rtypes, atypes)))
 *	The node types themselves hold lexv and hasv. After a declaration at
 *	top level both are set to PARAM and rtypes/atypes to NULL. */
#define DECL_LEXNODE(np)   ((np)->r)
#define DECL_IDLIST(np)    ((np)->r->l)
#define DECL_LEXV(np)      ((np)->r->type)
#define DECL_HASVNODE(np)  ((np)->r->r)
#define DECL_HASV(np)      ((np)->r->r->type)
#define DECL_RTYPES(np)    ((np)->r->r->l)
#define DECL_ATYPES(np)    ((np)->r->r->r)

/* BRA open close:  FUNC(set_brackets, PARAM(open, close)) */
#define BRK_OPEN(np)       ((np)->r->l)
#define BRK_CLOSE(np)      ((np)->r->r)

/* OTHER f : sorts >> sort att:
 *	FUNC(other_fkt, PARAM(f, PARAM(sorts, PARAM(sort, att)))) */
#define OTHER_SYM(np)      ((np)->r->l)
#define OTHER_SORTS(np)    ((np)->r->r->l)
#define OTHER_RTYPE(np)    ((np)->r->r->r->l)
#define OTHER_ATT(np)      ((np)->r->r->r->r)

/* attach C function or user function to f:  FUNC(att_fkt, PARAM(f, att)) */
#define ATTF_SYM(np)       ((np)->r->l)
#define ATTF_ATT(np)       ((np)->r->r)

/* ATT sort show,cmp,cpy,del:
 *	FUNC(att_sort, PARAM(sort, PARAM(show, PARAM(cmp, PARAM(cpy, del))))) */
#define ATTS_SORT(np)      ((np)->r->l)
#define ATTS_SHOW(np)      ((np)->r->r->l)
#define ATTS_CMP(np)       ((np)->r->r->r->l)
#define ATTS_CPY(np)       ((np)->r->r->r->r->l)
#define ATTS_DEL(np)       ((np)->r->r->r->r->r)

/* SPEC / ADDSPEC alg : ...:  FUNC(f, PARAM(alg, list)) */
#define SPEC_ALG(np)       ((np)->r->l)
#define SPEC_LIST(np)      ((np)->r->r)

/* rule list: Forms(rule, next), rule: Form(lhs, result)
 *	result: PARAM(Cond2(cond, rhs), do-block) */
#define FORM_LHS(f)        ((f)->l)
#define FORM_RES(f)        ((f)->r)
#define RES_COND(e)        ((e)->l->l)
#define RES_RHS(e)         ((e)->l->r)
#define RES_DO(e)          ((e)->r)
#define COND2_COND(c)      ((c)->l)
#define COND2_RHS(c)       ((c)->r)

/* local symbols in blocks:  FUNC(set_locals_seq, PARAM(list, instruction)) */
#define LOCALS_LIST(np)    ((np)->r->l)
#define LOCALS_INSTR(np)   ((np)->r->r)

/* user function (ATT ( argdefs ) instruction): value = PARAM(argdefs, body) */
#define UFUNC_ARGDEFS(v)   ((v)->l)
#define UFUNC_BODY(v)      ((v)->r)

/* ATT name: ATT node, l = C function */
#define ATT_CFUNC(a)       ((a)->l)

#endif /* NODES_H */
