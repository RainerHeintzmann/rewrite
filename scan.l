%{
/*
 *	scan.l V1.00
 *	Copyright (c)  Rainer Heintzmann (1992)
 *
 *  Skanner fuer 'rewrite'
 */

#include "fatal.h"
#include "run.h"		/* Node */
#include "sym.h"		/* Symbol */
#include "syn.h"		/* Number */
#include "node.h"		/* mknum */

#ifdef	FLEX_SCANNER

#include <string.h>
#include <stdlib.h>

#undef	YY_INPUT
#define	YY_INPUT(buf, result, limit)	result = flex_input(buf, limit)

extern YYSTYPE yylval;

static int flex_input _2p (char *, int);

#else

#undef	input
#undef	output
#undef	unput

static int input _0p (void), output _1p (int), unput _1p (int);
static int i;
#endif


%}

alfa	([a-zA-Z_])
digit ([0-9])
numb  ({digit}*"."?{digit}+([eE][\+\-]?{digit}+)?)
alnum	(['%'$?a-zA-Z_0-9\])
sp_ops ([><&|=*/^!§`\\])
sp_ops1 ([\[\]])
sp_ops2 ([\-\+])
%%

"\""[^"\""]*"\""	{ int i;
				  	for (i=1;yytext[i]!=0;i++)
						;
				  	yytext[i-1]=0;
					lookup(& yytext[1]); /* damit Speicher reserviert wird */
					return String;}

{sp_ops}*	{ return lookup(yytext); }	/* Id, etc */
{sp_ops1}*	{ return lookup(yytext); }	/* Id, etc */
{sp_ops2}*	{ return lookup(yytext); }	/* Id, etc */
{numb}	   { double * value;
              Symbol * sp;
				  value = (double *) malloc(sizeof(double));
				  if (! value)
						fatal("lex: no room for making real-number !\n");

              sscanf(yytext,"%lf",value); /* bekommt Pointer auf value */
    			  sp=mknum((void *) value,NULL); /* Std.Num-Type */

             yylval.y_sym = sp;
	          return lexval(sp);
	         }  
{alnum}*		{ return lookup(yytext); }	/* Id, etc */

"#".*$	;			/* #... ignorieren */
[ \t]	;			/* Zwischenraum ignorieren */

\n	|
.	return (int) yytext[0];	/* 'x' fuer yyparse() */

%%

/*
 *	Zeilen-Schnittstelle
 */

static const char * buf, * bp;	/* aktuelle Zeile */
#ifdef	FLEX_SCANNER
static int avail;		/* # Zeichen uebrig */
#endif

void lexi_buf _1a ((cp), const char * cp)
{
	buf = bp = cp;
#ifdef	FLEX_SCANNER
	avail = strlen(buf);
	yy_init = 1;		/* (re-) initialisiert scanner */
#endif
}

#ifdef	FLEX_SCANNER

static int flex_input _2a ((buf, lim), char * buf, int lim)
{	int n;

	if (! avail)
		return YY_NULL;

	n = lim >= avail ? avail : lim;
	strncpy(buf, bp, n);
	bp += n, avail -= n;
	return n;
}

#else

static int input _0a (void)
{	char ch;

	if (ch = * bp)
		++ bp;
	return ch & 255;
}

static int output _1a ((ch), int ch)
{
	fatal("unexpected scan output 0%o", ch & 255);
}

static int unput _1a ((ch), int ch)
{
	if (ch)
	{	if (bp > buf && * -- bp == ch)
			return ch & 255;
	}
	else if (ch == *bp)
		return ch;

	fatal("unexpected scan unput 0%o", ch & 255);
}

#endif
