/*
 *	sym.c V1.00
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *	Framework : Prof. Axel T. Schreiner
 *
 *  Symbol management for 'rewrite'
 *	symbol table: binary tree
 *	reserved words: search table
 */

#include "search.h"
#include <stdlib.h> /* bsearch */
#include <string.h>

#include "inout.h"
#include "fatal.h"
#include "sym.h"
#include "syn.h"
#include "node.h" /* for mksym */

extern YYSTYPE yylval;

static const Reserved words [] = {	/* sorted */
	{ "%",      LAST },
	{ "++",     VARPAR },
	{ "=",     	EQ },
	{ ">>",     PFEIL },
	{ "ADDSPEC",ADDSPEC },
	{ "ALG",    ALG },
	{ "ATT",    ATT },
	{ "BRA",    BRA },
	{ "COMM",   COMM },     /* commutative functions (2026) */
	{ "CONST",  CST },
	{ "DATA",   DATA },  /* reading data files */
	{ "DEBUG",  DBG },
	{ "DEFAULT",DEFAULT },  /* value of missing operands (2026) */
	{ "DO",     DO },
	{ "ELSE",   ELSE },
	{ "EXE",    EXE },
	{ "FOR",    FOR },
	{ "FUNC",   FUNC },
	{ "GRAPH",  GRAPH },
	{ "HOLD",   HOLD },     /* ATT SYMBOLIC HOLD: arguments unevaluated (2026) */
	{ "IF",     IF  },
	{ "IN",     IN  },
	{ "INC",    INC },      /* Include */
	{ "INFO",   INFO },
	{ "INTNUM", INTNUM },   /* sort of integer literals (2026) */
	{ "IS",     IS  },
	{ "LA1",    LA1  },			/* left-associative */
	{ "LA2",    LA2  },
	{ "LA3",    LA3  },
	{ "LA4",    LA4  },
	{ "LA5",    LA5  },
	{ "LB",     LB  },
	{ "LIFT",   LIFT  },
	{ "LOCAL",  LOCAL },
	{ "NIN",    NIN },
	{ "NUM",    NUM },
	{ "OPT",    OPT },      /* optional meta variables (2026) */
	{ "OTHER",  OTHER },
	{ "OUT",    OUT },
	{ "PRT",    PRT },
	{ "PRTNUM", PRTNUM },
	{ "QUIT",   QUIT },
	{ "RA",		  RA  },  			/* right-associative */
	{ "RETURN", RETURN },
	{ "REWR",   REWR },
	{ "RIGHT",  RIGHT },    /* DEFAULT RIGHT (2026) */
	{ "RU",     RU  },			/* right-unary */
	{ "SORT",   SORT },
	{ "SPEC",   SPEC },
	{ "STEP",   STEP },
	{ "STEPS",  STEPS },    /* solution steps of a rule list (2026) */
	{ "SUBSORT",SUBSORT },  /* subsort with conversion (2026) */
	{ "SYMBOLIC",SYMBOLIC },/* ATT SYMBOLIC: C function on terms (2026) */
	{ "SYS",    SYS },
	{ "TERM",   TERM },
	{ "TO",     TO },
	{ "VAR",    VAR },
	{ "WHILE",  WHILE }
};

#define	DIM(x)	(sizeof(x) / sizeof(x[0]))

static const void * root = NULL; /* root for user symbols */


static int rcmp _2a ((a, b), const void * a, const void * b)
{
	return strcmp(((Reserved *) a)->name,((Reserved *) b)->name);
}

static int scmp _2a ((va, vb), const void * va, const void * vb)
{
#define	a	((const Symbol *) va)
#define	b	((const Symbol *) vb)
	return strcmp(name(a),name(b));
#undef	a
#undef	b
}

int lookup _1a ((name), const char * name)
{	Reserved r, * rp;

	Symbol s, ** pp;

	name(& r) = (char *)  name;
	if (rp = (Reserved *) bsearch (& r, words, DIM(words), sizeof r, rcmp))
		{
		DEBG((4,"DB : lookup : found reserved : %s\n",rp-> name));
		return lexval(rp);
		}

	name(& s) = (char *) name;
	if (! (pp = (Symbol **) tsearch(& s, & root, scmp)))
		fatal("lookup: no room");

	if ((* pp) == (& s))	/* not found */
  		(* pp) = mksym(Id,name);

	yylval.y_sym = * pp;

	return lexval(* pp);
}

/* 2026: look up the symbol of a name without creating it (NULL if unknown) */
Symbol * find_symbol (const char * name)
{
	Symbol s, ** pp;
	name(& s) = (char *) name;
	pp = (Symbol **) tfind(& s, (const void * const *) & root, scmp);
	return pp ? * pp : (Symbol *) NULL;
}

void focus (Symbol * sp)
{
	Symbol ** pp;
	if (! (pp = (Symbol **) tsearch(sp, & root, scmp)))
		fatal("focus: no room");

	DEBG((20,"focus %s,%p -> %p\n",name(sp),(* pp),sp));

	if ((* pp) == sp)	/* found an equal one */
			fatal ("Internal error: Symbol already focused");
	(* pp) = sp;
}

void	restore _1a ((chain),Node * chain)
{
Node * ochain;
	while (chain != NULL)
		{
		if (lexval((Symbol *) chain->r) == Sort)
			{
			IS_Verbindung(chain->r) = (Symbol *) NULL;
			DEBG((4,"restoring Sort: %s\n",((Symbol *) chain->r)->name));
			}
		else
			{
			((Symbol *) chain->r)->node.type = SYM_TYPE;
			DEBG((4,"restoring Variable: %s\n",((Symbol *) chain->r)->name));
			}
		ochain=chain;
		chain=chain->l;
		delnod(ochain); /* first advance, then free ! */
		}
}

