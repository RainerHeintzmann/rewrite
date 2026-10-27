#ifndef	SYM_H
#define	SYM_H

/*
 *	sym.h V1.00
 *	Framework 1991 Axel T. Schreiner
 *  Symbol structure 1992 Rainer Heintzmann
 *	Symbol table
 */

#include "run.h"

typedef	struct {
	char * name;
	int    yylex;
	} Reserved;

typedef struct Symbol Symbol;
struct Symbol{            /* CAUTION: instances in node.c and sync.c */
	Node	node;	            /* for later term rewriting, and to distinguish nodes in the tree */
	char *	name;
	int		yylex;
	Node *	rtypes,	        /* result types */
 		   *	atypes;	        /* argument types */
	int		hasval;		        /* value present */
	void * value;           /* pointer to a value of any type (for Func: function pointer) */
	Symbol * oldvals;       /* pointer to the list of overwritten values of any type */
	int		exe_always;       /* always execute the function ?! */
  Symbol * orig_func;				/* for user function pointers */
  Symbol * bracket;       /* links a left bracket with its matching right bracket (BRACKET function)*/
  Symbol * variants;         /* links functions of the same name but with different argument types */
  Symbol * IS_chain;      /* links functions and constants of the same result type (the sort is the anchor) */
  Symbol * IS_link; /* links functions and constants that were assigned with 'term IS term'  */
	int		def_in_blk;       /* block level in which it was defined */
	int		builtin;          /* 2026: symbolic C function (symfn.c), gets terms instead of numbers */
	void *	showfn;           /* 2026: print function of a function (SHOW f ATT name), see tprint */
	int		valued;           /* 2026: for a sort: values of it can arise (see sort_valued) */
	int		sortno;           /* 2026: for a sort: its index in the sort_dist cache + 1 (numsort.c) */
	const char * role;        /* 2026: the role of a function, valid if role_gen is current (symfn.c) */
	int		role_gen;
};

#define NOFLAG		0
#define COMMFLAG 	1

#define SYM_TYPE	((int) 0)
#define OR_TYPE	((int) 556)       /* forms.c */
#define REPL_TYPE	((int) 557)   /* forms.c */
#define CHAIN	555               /* for run.c,forms.c */
#define RULELIST	((int) 558)  /* 2026: rule list with backtracking (listmatch.c) */

#define lexval(p_sym)	((p_sym) -> yylex)
#define type(p_sym)	( (((p_sym) -> yylex) == Var) ? "Var" : \
											(((p_sym) -> yylex) == Const) ? "Const" : \
											(((p_sym) -> yylex) == Func) ? "Function" : \
											(((p_sym) -> yylex) == La1) ? "Function La1" : \
											(((p_sym) -> yylex) == La2) ? "Function La2" : \
											(((p_sym) -> yylex) == La3) ? "Function La3" : \
											(((p_sym) -> yylex) == La4) ? "Function La4" : \
											(((p_sym) -> yylex) == La5) ? "Function La5" : \
											(((p_sym) -> yylex) == Ra) ? "Function Ra" : \
											(((p_sym) -> yylex) == Ru) ? "Function Ru" : \
											(((p_sym) -> yylex) == Bra) ? "equal brackets" : \
											(((p_sym) -> yylex) == Bra1) ? "unequal brackets" : \
											(((p_sym) -> yylex) == Id) ? "Id" : \
											(((p_sym) -> yylex) == Alg) ? "Alg" : \
											(((p_sym) -> yylex) == Sort) ? "Sort" : \
											(((p_sym) -> yylex) == Term) ? "Term" : "Unknown !!?")

#define name(p_sym)		((p_sym) -> name)
#define rtypes(p_sym)	((p_sym) -> rtypes)
#define atypes(p_sym)	((p_sym) -> atypes)
#define exe_always(p_sym)	(((Symbol *) (p_sym)) -> exe_always)
#define hasval(p_sym)	(((Symbol *) (p_sym)) -> hasval)
#define value(p_sym)	(((Symbol *) (p_sym)) -> value)
#define oldvals(p_sym)	(((Symbol *) (p_sym)) -> oldvals) /* must not be redefined, otherwise rec_build_list in defs.c no longer works ! */
#define bracket(p_sym)	(((Symbol *) (p_sym)) -> bracket)
#define variants(p_sym)	(((Symbol *) (p_sym)) -> variants)
#define IS_chain(p_sym)	(((Symbol *) (p_sym)) -> IS_chain) /* used by function,const,sort */
#define IS_link(p_sym)	(((Symbol *) (p_sym)) -> IS_link) /* used by function,const,sort */
#define orig_func(p_sym)	(((Symbol *) (p_sym)) -> orig_func) /* only for functions */
#define defined_in_block(p_sym)	(((Symbol *) (p_sym)) -> def_in_blk) /* only for terms,constants,functions */
/* 2026: a sort has numerical values if something makes them: ATT sort,
   REALNUM, INTNUM, a SUBSORT conversion from a sort with values, or a function
   with a numerical C function or a defining term of this result sort.
   Purely symbolic sorts (ring, the lists of inc/list) have none. */
#define sort_valued(p_sym)	(((Symbol *) (p_sym)) -> valued)
#define showfn(p_sym)	(((Symbol *) (p_sym)) -> showfn) /* 2026: SHOW */
#define builtin(p_sym)	(((Symbol *) (p_sym)) -> builtin) /* symbolic C function */

#define show(p_sym)	(((Symbol *) (p_sym)) -> value) /* redefined for SORT (showfkt.) */
#define cmp(p_sym)	(((Symbol *) (p_sym)) -> rtypes) /* redefined for SORT (comparefkt.) */
#define cpy(p_sym)	(((Symbol *) (p_sym)) -> atypes) /* redefined for SORT (copyfkt.) */
#define del(p_sym)	(((Symbol *) (p_sym)) -> bracket) /* redefined for SORT (deletefkt.) */

#define CPYNUM(term,value)          (((void * (*) (void *)) cpy(rtypes((Symbol *)(term)))) ((void *) (value)))
#define SHOWNUM(term,value)         (((void * (*) (void *)) show(rtypes((Symbol *)(term)))) ((void *) (value)))
#define CMPNUM(term,value1,value2)  (((int (*) (void *,void *)) cmp(rtypes((Symbol *)(term)))) ((void *) (value1),(void *) (value2)))
#define DELNUM(term,value)          (((void (*) (void *)) del(rtypes((Symbol *)(term)))) ((void *) (value)))

#define CALLFUNCT(term)							(((void (*) (Node *)) term->l) (term))

int lookup _1p (const char *);		/* returns the yylex() value */
void lookup_string (const char * name);	/* 2026: the symbol of a string, also of a keyword text */
Symbol * find_symbol (const char * name);
void for_all_symbols (void (* fn) (Symbol *));	/* 2026: fn for every name */
void alias_def (const char * from, const char * to);	/* 2026: ALIAS "from" = "to" */  /* 2026: look up a symbol, NULL if unknown */
void focus (Symbol * sp);
void restore _1p (Node *);

#define RESTORE	 \
		{ restore(var_chain.l);		/* restore the symbol table (includes: free(chain)) */ \
		chain_pos = & var_chain;	/* (type = SYM_TYPE), delete chain */  \
		var_chain.l = NULL; }

#endif
