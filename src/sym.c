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
	{ "ALIAS",  ALIAS },    /* ALIAS "×" = "*": another name of a symbol (2026) */
	{ "ATT",    ATT },
	{ "AUTOSYM", AUTOSYM }, /* AUTOSYM real: new names are declared (2026) */
	{ "BRA",    BRA },
	{ "COMM",   COMM },     /* commutative functions (2026) */
	{ "DATA",   DATA },  /* reading data files */
	{ "DEBUG",  DBG },
	{ "DEFAULT",DEFAULT },  /* value of missing operands (2026) */
	{ "DO",     DO },
	{ "ELSE",   ELSE },
	{ "EXE",    EXE },
	{ "FOR",    FOR },
	{ "FUNC",   FUNC },
	{ "GRAPH",  GRAPH },
	{ "HELP",   HELP },     /* HELP "name" "text": help for ?name (2026) */
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
	{ "MAXDEPTH", MAXDEPTH },   /* limits of REWR (2026) */
	{ "MAXSTEPS", MAXSTEPS },
	{ "NIN",    NIN },
	{ "NUMPAT", NUMPAT },   /* pattern variables for numbers (2026, formerly NUM) */
	{ "OPT",    OPT },      /* optional meta variables (2026) */
	{ "OTHER",  OTHER },
	{ "OUT",    OUT },
	{ "PAT",    PAT },      /* pattern variables (2026, formerly VAR) */
	{ "PRETTY", PRETTY },  /* PRETTY 1: output with Unicode, x², √x, π (2026) */
	{ "PRT",    PRT },
	{ "PRTNUM", PRTNUM },
	{ "QUIT",   QUIT },
	{ "RA",		  RA  },  			/* right-associative */
	{ "REALNUM",REALNUM },  /* sort of the other number literals (2026, formerly NUM sort) */
	{ "RETURN", RETURN },
	{ "REWR",   REWR },
	{ "RIGHT",  RIGHT },    /* DEFAULT RIGHT (2026) */
	{ "RU",     RU  },			/* right-unary */
	{ "RULES",  RULES },    /* ATT RULES alglist: function defined by a rule list (2026) */
	{ "SHOW",   SHOW },     /* SHOW f ATT name: print function of f (2026) */
	{ "SORT",   SORT },
	{ "SPEC",   SPEC },
	{ "STEP",   STEP },
	{ "STEPS",  STEPS },    /* solution steps of a rule list (2026) */
	{ "SUBSORT",SUBSORT },  /* subsort with conversion (2026) */
	{ "SYM",    SYM },      /* symbols, with or without a value (2026, formerly CONST) */
	{ "SYMBOLIC",SYMBOLIC },/* ATT SYMBOLIC: C function on terms (2026) */
	{ "SYS",    SYS },
	{ "TERM",   TERM },
	{ "TO",     TO },
	{ "TYPEOF", TYPEOF },   /* TYPEOF term: its sort (2026) */
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

/* 2026: ALIAS "×" = "*": the name × is read as *. The libraries give the
   Unicode operators (≤, ×, ...) their meaning this way. With SHOW
   (ALIAS "π" = "pi" SHOW) it is also the name printed by PRETTY 1. */
#define MAXALIAS 128
static struct { char * from, * to; int show; } aliases[MAXALIAS];
static int naliases = 0;

const char * print_alias (const char * name)	/* the SHOW alias of name, or NULL */
{
	int i;
	for (i = naliases - 1; i >= 0; i--)
		if (aliases[i].show && strcmp(aliases[i].to, name) == 0) return aliases[i].from;
	return NULL;
}

void alias_def (const char * from, const char * to, int show)
{
	int i;
	for (i = 0; i < naliases; i++)
		if (strcmp(aliases[i].from, from) == 0) break;
	if (i == naliases)
		{
		if (naliases == MAXALIAS) { printfErr("ALIAS : too many aliases\n"); return; }
		aliases[naliases++].from = strdup(from);
		}
	else
		free(aliases[i].to);
	aliases[i].to = strdup(to);
	aliases[i].show = show;
}

static const char * unalias (const char * name)
{
	int i;
	for (i = 0; i < naliases; i++)
		if (strcmp(aliases[i].from, name) == 0) return aliases[i].to;
	return name;
}

int lookup _1a ((name), const char * name)
{	Reserved r, * rp;

	Symbol s, ** pp;

	name = unalias(name);
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

/* 2026: the symbol of a string "...", also if its text is a keyword
   (HELP "REWR" "..."); lookup would return the keyword without a symbol */
void lookup_string (const char * name)
{
	Symbol s, ** pp;

	name(& s) = (char *) name;
	if (! (pp = (Symbol **) tsearch(& s, & root, scmp)))
		fatal("lookup: no room");
	if ((* pp) == (& s))	/* not found */
  		(* pp) = mksym(Id,name);
	yylval.y_sym = * pp;
}

/* 2026: look up the symbol of a name without creating it (NULL if unknown) */
Symbol * find_symbol (const char * name)
{
	Symbol s, ** pp;
	name(& s) = (char *) name;
	pp = (Symbol **) tfind(& s, (const void * const *) & root, scmp);
	return pp ? * pp : (Symbol *) NULL;
}

/* 2026: fn for every name in the symbol table (TYPEOF of a sort or rule set) */
static void (* walk_fn) (Symbol *);

static void walk_visit (void ** node, VISIT which, int depth)
{
	if (which == postorder || which == leaf) walk_fn(* (Symbol **) node);
}

void for_all_symbols (void (* fn) (Symbol *))
{
	walk_fn = fn;
	twalk(root, walk_visit);
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
			IS_link(chain->r) = (Symbol *) NULL;
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

