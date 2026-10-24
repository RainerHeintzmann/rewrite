#ifndef	SYM_H
#define	SYM_H

/*
 *	sym.h V1.00
 *	Grundgruesst 1991 Axel T. Schreiner
 *  Symbolstruktur 1992 Rainer Heintzmann 
 *	Symboltabelle
 */

#include "run.h"

typedef	struct {
	char * name;
	int    yylex;
	} Reserved;

typedef struct Symbol Symbol;
struct Symbol{            /* ACHTUNG: Instanzen in node.c und sync.c */
	Node	node;	            /* Fuer spaetere Termersetzung ,und zur Unterscheidung im Baum */
	char *	name;
	int		yylex;
	Node *	rtypes,	        /* result types */
 		   *	atypes;	        /* argument types */
	int		hasval;		        /* Wert vorhanden */
	void * value;           /* Zeiger auf Wert beliebigen Types (bei Func Funktionszeiger) */
	Symbol * oldvals;       /* Zeiger auf Liste ueberschriebener Werte beliebigen Types */
	int		exe_always;       /* Funktion immer ausfuehren ?! */
  Symbol * urs_fkt;				/* Fuer Benutzer-Funktionszeiger */
  Symbol * klammer;       /* verkettet linke Klammer mit zugehoeriger rechten Klammer (BRACKET-Fkt.)*/
  Symbol * kette;         /* verkettet Funktionen gleichen Namen aber mit unterschiedlichen Argumenttypen miteinander */
  Symbol * IS_kette;      /* verkettet Funktionen,Constanten gleichen Resultattyps miteinander (Sort ist Anker) */
  Symbol * IS_Verbindung; /* verkettet Funktionen und Constanten, die mit 'term IS term' zugewiesen wurden, miteinander  */
	int		def_in_blk;       /* Blockstufe in der es definiert wurde */
	int		builtin;          /* 2026: symbolische C-Funktion (symfkt.c), bekommt Terme statt Zahlen */
};

#define NOFLAG		0
#define KOMMFLAG 	1

#define SYM_TYPE	((int) 0)
#define OR_TYPE	((int) 556)       /* forms.c */
#define ERSETZ_TYPE	((int) 557)   /* forms.c */
#define CHAIN	555               /* Fuer run.c,forms.c */

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
#define oldvals(p_sym)	(((Symbol *) (p_sym)) -> oldvals) /* darf nicht ueberdefiniert werden, sonst laeft rec_build_list in defs.c nicht mehr ! */
#define klammer(p_sym)	(((Symbol *) (p_sym)) -> klammer)
#define kette(p_sym)	(((Symbol *) (p_sym)) -> kette)
#define IS_kette(p_sym)	(((Symbol *) (p_sym)) -> IS_kette) /* Benutzt von Funktion,Const,Sort */
#define IS_Verbindung(p_sym)	(((Symbol *) (p_sym)) -> IS_Verbindung) /* Benutzt von Funktion,Const,Sort */
#define urs_fkt(p_sym)	(((Symbol *) (p_sym)) -> urs_fkt) /* Nur fuer Funktionen */
#define defined_in_block(p_sym)	(((Symbol *) (p_sym)) -> def_in_blk) /* Nur fuer Terme,Constanten,Functionen */
#define builtin(p_sym)	(((Symbol *) (p_sym)) -> builtin) /* symbolische C-Funktion */

#define show(p_sym)	(((Symbol *) (p_sym)) -> value) /* ueberdefinier fuer SORT (showfkt.) */
#define cmp(p_sym)	(((Symbol *) (p_sym)) -> rtypes) /* ueberdefinier fuer SORT (comparefkt.) */
#define cpy(p_sym)	(((Symbol *) (p_sym)) -> atypes) /* ueberdefinier fuer SORT (copyfkt.) */
#define del(p_sym)	(((Symbol *) (p_sym)) -> klammer) /* ueberdefinier fuer SORT (deletefkt.) */

#define CPYNUM(term,value)          (((void * (*) (void *)) cpy(rtypes((Symbol *)(term)))) ((void *) (value)))
#define SHOWNUM(term,value)         (((void * (*) (void *)) show(rtypes((Symbol *)(term)))) ((void *) (value)))
#define CMPNUM(term,value1,value2)  (((int (*) (void *,void *)) cmp(rtypes((Symbol *)(term)))) ((void *) (value1),(void *) (value2)))
#define DELNUM(term,value)          (((void (*) (void *)) del(rtypes((Symbol *)(term)))) ((void *) (value)))

#define CALLFUNCT(term)							(((void (*) (Node *)) term->l) (term))

int lookup _1p (const char *);		/* liefert yylex() Wert */
Symbol * find_symbol (const char * name);  /* 2026: Symbol suchen, NULL wenn unbekannt */
void focus (Symbol * sp);
void restore _1p (Node *);

#define RESTORE	 \
		{ restore(var_chain.l);		/* Symboltabelle restaurieren (enthaelt : free(chain)) */ \
		chain_pos = & var_chain;	/* (type = SYM_TYPE), chain loeschen */  \
		var_chain.l = NULL; }

#endif
