%{
/*
 *	scan.l V1.00
 *	Copyright (c)  Rainer Heintzmann (1992)
 *
 *  Scanner for 'rewrite'
 */

#include "fatal.h"
#include "run.h"		/* Node */
#include "sym.h"		/* Symbol */
#include "syn.h"		/* Number */
#include "node.h"		/* mknum */
#include "numsort.h"		/* int_literal (2026) */
#include "inout.h"		/* printfErr (2026) */
#include "latex.h"		/* \alpha -> alpha (2026) */

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


/* 2026: the length of the Unicode operator character at s (0 if none):
   these are tokens of their own, like the brackets, so that a≤b is a, ≤, b.
   Mathematical signs (× ÷ · ± ¬), arrows and the mathematical operators,
   but not the names among them (∂ ∇ ∞, the sums and integrals). Their
   meaning comes from the libraries (ALIAS "≤" = "<="). */
static int unicode_op (const unsigned char * s)
{
	unsigned c;
	if (s[0] == 0xC2 || s[0] == 0xC3)
		{
		c = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
		return (c == 0xAC || c == 0xB1 || c == 0xB7 || c == 0xD7 || c == 0xF7) ? 2 : 0;
		}
	if (s[0] != 0xE2 || (s[1] & 0xC0) != 0x80 || (s[2] & 0xC0) != 0x80) return 0;
	c = ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
	if (c >= 0x2190 && c <= 0x21FF) return 3;			/* arrows */
	if (c >= 0x2200 && c <= 0x22FF)					/* mathematical operators */
		return (c == 0x2202 || (c >= 0x2205 && c <= 0x2207) || (c >= 0x220F && c <= 0x2211)
		        || c == 0x221E || (c >= 0x222B && c <= 0x2233)) ? 0 : 3;
	if (c >= 0x2A00 && c <= 0x2AFF)					/* supplemental ones */
		return (c >= 0x2A0B && c <= 0x2A1C) ? 0 : 3;
	return 0;
}

/* the token of the number literal text */
static int number_token (const char * text)
{
	double * value;
	Symbol * sp;
	if (strspn(text, "0123456789") == strlen(text)
	    && (sp = int_literal(text)) != NULL)	/* 2026: integer number (INTNUM) */
		{
		yylval.y_sym = sp;
		return lexval(sp);
		}
	if (! get_numbertype())	/* 2026: no sort for it yet */
		{
		printfErr("number %s : no sort for number literals (REALNUM sort, e.g. INC \"inc/all\")\n", text);
		return (int) text[0];	/* a syntax error */
		}
	value = (double *) malloc(sizeof(double));
	if (! value)
		fatal("lex: no room for making real-number !\n");
	sscanf(text, "%lf", value);
	sp = mknum((void *) value, NULL);	/* std. number type */
	yylval.y_sym = sp;
	return lexval(sp);
}

static int is_number_text (const char * text)	/* 2026: 3 or 2.5 before an operator (3×4) */
{
	char * end;
	if (! (* text >= '0' && * text <= '9') && * text != '.') return 0;
	strtod(text, & end);
	return * end == 0;
}

%}

alfa	([a-zA-Z_])
digit ([0-9])
numb  ({digit}*"."?{digit}+([eE][\+\-]?{digit}+)?)
	/* 2026: the bytes of UTF-8 characters are letters (names like alpha) */
alnum	(['%'$?a-zA-Z_0-9\x80-\xff])
sp_ops ([><&|=*/^!`\\])
sp_ops1 ([\[\]])
sp_ops2 ([\-\+])
%%

"\""[^"\""]*"\""	{ int i;
				  	for (i=1;yytext[i]!=0;i++)
						;
				  	yytext[i-1]=0;
					lookup_string(& yytext[1]); /* so that memory is allocated (2026: also for keywords) */
					return String;}

{sp_ops}*	{ return lookup(yytext); }	/* Id, etc */
{sp_ops1}	{ return lookup(yytext); }	/* 2026: one bracket per token: [[1,2],[3,4]] */
{sp_ops2}*	{ return lookup(yytext); }	/* Id, etc */
{numb}		{ return number_token(yytext); }
{alnum}*		{ int i, n = 0;		/* 2026: up to a Unicode operator, or that alone */
			  for (i = 0; yytext[i] && ! (n = unicode_op((unsigned char *) yytext + i)); i++)
				;
			  if (n) yyless(i ? i : n);
			  if (n && is_number_text(yytext)) return number_token(yytext);
			  return lookup(yytext); }	/* Id, etc */

"#".*$	;			/* ignore #... */
[ \t]	;			/* ignore white space */

\n	|
.	return (int) yytext[0];	/* 'x' for yyparse() */

%%

/*
 *	Line interface
 */

static const char * buf, * bp;	/* current line */
#ifdef	FLEX_SCANNER
static int avail;		/* # characters left */
#endif

static char * converted = NULL;	/* 2026: the line with the LaTeX-like names replaced */

void lexi_buf _1a ((cp), const char * cp)
{
	free(converted);
	converted = latex_convert(cp);	/* \alpha -> the character (latex.c) */
	if (converted) cp = converted;
	buf = bp = cp;
#ifdef	FLEX_SCANNER
	avail = strlen(buf);
	yyrestart(yyin);	/* (re-) initializes the scanner (modern flex: yy_init=1 means "already initialized") */
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
