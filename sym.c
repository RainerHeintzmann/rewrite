/*
 *	sym.c V1.00
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *	Grundgeruesst : Prof. Axel T. Schreiner
 *
 *  Symbolverwaltung fuer 'rewrite'
 *	Symboltabelle: binaerer Baum
 *	reservierte Worte: Suchtabelle
 */

#include "search.h"
#include <string.h>

#include "inout.h"
#include "fatal.h"
#include "sym.h"
#include "syn.h"
#include "node.h" /* fuer mksym */

extern YYSTYPE yylval;

static const Reserved words [] = {	/* sortiert */
	{ "%",      LAST },
	{ "++",     VARPAR },
	{ "=",     	EQ },
	{ ">>",     PFEIL },
	{ "ADDSPEC",ADDSPEC },
	{ "ALG",    ALG },
	{ "ATT",    ATT },
	{ "BRA",    BRA },
	{ "CONST",  CST },
	{ "DATA",   DATA },  /* Einlesen von Daten-files */
	{ "DEBUG",  DBG },
	{ "DO",     DO },
	{ "ELSE",   ELSE },
	{ "EXE",    EXE },
	{ "FOR",    FOR },
	{ "FUNC",   FUNC },
	{ "GRAPH",  GRAPH },
	{ "IF",     IF  },
	{ "IN",     IN  },
	{ "INC",    INC },      /* Include */
	{ "INFO",   INFO },
	{ "IS",     IS  },
	{ "LA1",    LA1  },			/* Linksassoziativ */
	{ "LA2",    LA2  },
	{ "LA3",    LA3  },
	{ "LA4",    LA4  },
	{ "LA5",    LA5  },
	{ "LB",     LB  },
	{ "LIFT",   LIFT  },
	{ "LOCAL",  LOCAL },
	{ "NIN",    NIN },
	{ "NUM",    NUM },
	{ "OTHER",  OTHER },
	{ "OUT",    OUT },
	{ "PRT",    PRT },
	{ "PRTNUM", PRTNUM },
	{ "QUIT",   QUIT },
	{ "RA",		  RA  },  			/* Rechtsassoziativ */
	{ "RETURN", RETURN },
	{ "REWR",   REWR },
	{ "RU",     RU  },			/* Rechtsunaer */
	{ "SORT",   SORT },
	{ "SPEC",   SPEC },
	{ "STEP",   STEP },
	{ "SYS",    SYS },
	{ "TERM",   TERM },
	{ "TO",     TO },
	{ "VAR",    VAR },
	{ "WHILE",  WHILE }
};

#define	DIM(x)	(sizeof(x) / sizeof(x[0]))

static const void * root = NULL; /* Wurzel fuer benutzer-Symbole */


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
	void * bsearch _5p (const void *, const void *, unsigned, unsigned,
				int (*) _2p (const void *, const void *));

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

	if ((* pp) == (& s))	/* nicht gefunden */
  		(* pp) = mksym(Id,name);

	yylval.y_sym = * pp;

	return lexval(* pp);
}

void focus (Symbol * sp)
{
	Symbol ** pp;
	if (! (pp = (Symbol **) tsearch(sp, & root, scmp)))
		fatal("focus: no room");

	DEBG((20,"focus %s,%p -> %p\n",name(sp),(* pp),sp));

	if ((* pp) == sp)	/* gleiches gefunden */
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
		delnod(ochain); /* Erst weiter dann free ! */
		}
}

