
/*  A Bison parser, made from syn.y  */

#define YYBISON 1  /* Identify Bison output.  */

#define	CST	258
#define	VAR	259
#define	SORT	260
#define	FUNC	261
#define	ALG	262
#define	SPEC	263
#define	ADDSPEC	264
#define	REWR	265
#define	PRT	266
#define	GRAPH	267
#define	PFEIL	268
#define	TERM	269
#define	NUM	270
#define	ATT	271
#define	IS	272
#define	EQ	273
#define	LA1	274
#define	LA2	275
#define	LA3	276
#define	LA4	277
#define	LA5	278
#define	LOCAL	279
#define	RU	280
#define	RA	281
#define	KOMMU	282
#define	LB	283
#define	IN	284
#define	NIN	285
#define	PARAM	286
#define	FOR	287
#define	TO	288
#define	STEP	289
#define	DO	290
#define	DBG	291
#define	LAST	292
#define	BRA	293
#define	OTHER	294
#define	DATA	295
#define	OUT	296
#define	INC	297
#define	EXE	298
#define	VARPAR	299
#define	SYS	300
#define	IF	301
#define	ELSE	302
#define	WHILE	303
#define	PRTNUM	304
#define	LIFT	305
#define	QUIT	306
#define	RETURN	307
#define	Id	308
#define	String	309
#define	Sort	310
#define	Alg	311
#define	Term	312
#define	La1	313
#define	La2	314
#define	La3	315
#define	La4	316
#define	La5	317
#define	Ru	318
#define	Ra	319
#define	Func	320
#define	Const	321
#define	Var	322
#define	Bra	323
#define	Bra1	324
#define	Bra2	325
#define	Terms	326
#define	Form	327
#define	Sorts	328
#define	Functs	329
#define	Forms	330
#define	Algs	331
#define	Cond2	332
#define	Cond	333

#line 9 "syn.y"


#include <string.h> /* fuer memcpy,strcmp */
#include <stdlib.h>

#include "inout.h"
#include "run.h"
#include "sym.h" 
#include "sync.h"
#include "defs.h"
#include "userfkt.h"

#ifdef BISON
#include "unix.h"
#endif

extern int  yylex   (void);
extern void yyerror (const char *);

extern Symbol * lastterm;  /* sync.c */

Node * nphilf;

#ifdef DEBUG
Node *  mknod_debug _6a ((a,b,c,x,y,z), int a, Node * b ,Node * c,char * x,char * y ,char * z)
{
	DEBG((4,"syn.y : mknod ( %s,%s,%s)\n",x,y,z));
	return mknod(a,b,c);
}
#define mknod(a,b,c)	mknod_debug(a,b,c,#a,#b,#c)
#endif

#define DECLARE(Idlist,lexv,rtps,atps,hasv)   \
mknod(FUNC,(Node *) declare, \
	mknod(lexv,Idlist, \
	mknod(hasv,rtps,atps)))


#line 48 "syn.y"
typedef union	{
	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __STDC__
#define const
#endif



#define	YYFINAL		273
#define	YYFLAG		-32768
#define	YYNTBASE	87

#define YYTRANSLATE(x) ((unsigned)(x) <= 333 ? yytranslate[x] : 118)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    79,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    82,
    83,     2,     2,    81,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    80,    84,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    85,     2,    86,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     8,    17,    25,    35,    44,    49,    52,
    57,    62,    67,    72,    77,    80,    83,    88,    90,    94,
    96,    98,   100,   104,   105,   108,   109,   116,   118,   120,
   122,   124,   126,   128,   130,   131,   133,   135,   137,   139,
   141,   143,   145,   147,   152,   157,   162,   166,   168,   172,
   174,   178,   180,   182,   184,   186,   190,   192,   194,   195,
   200,   204,   208,   214,   224,   225,   228,   231,   236,   238,
   241,   244,   247,   250,   253,   257,   264,   268,   272,   281,
   284,   287,   289,   290,   293,   295,   297,   299,   303,   305,
   309,   311,   315,   317,   321,   323,   326,   328,   330,   332,
   334,   336,   338,   340,   342,   344,   346,   348,   352,   354,
   356,   358,   360,   364,   367,   370,   373,   376,   379,   382,
   385,   389,   393,   398,   402,   406,   410,   414,   418,   422,
   424,   428,   432,   433,   436,   439,   444
};

#endif

static const short yyrhs[] = {    88,
     0,    87,    88,     0,    97,    79,     0,     6,    93,    80,
   110,    13,    55,    94,    91,     0,    39,   111,    80,   110,
    13,    55,    91,     0,    16,    55,    53,    81,    53,    81,
    53,    81,    53,     0,    38,    53,    53,    80,   110,    13,
    55,    91,     0,     4,    90,    80,    55,     0,    15,    55,
     0,    15,    90,    80,    55,     0,     3,    90,    80,    55,
     0,     8,    56,    80,   107,     0,     8,    56,    80,   117,
     0,     9,    56,    80,   117,     0,     5,    90,     0,     7,
    90,     0,    14,    90,    80,    55,     0,    93,     0,    93,
    81,    90,     0,    66,     0,    57,     0,     0,     0,     0,
    81,     0,     0,     0,    16,    93,     0,     0,    16,    82,
    92,   100,    83,   101,     0,    53,     0,    66,     0,    67,
     0,   111,     0,    55,     0,    56,     0,    57,     0,     0,
    19,     0,    20,     0,    21,     0,    22,     0,    23,     0,
    26,     0,    25,     0,    96,     0,    28,    82,   113,    83,
     0,    29,    82,   113,    83,     0,    30,    82,   113,    83,
     0,    82,   112,    83,     0,   101,     0,   101,    84,    97,
     0,    99,     0,    99,    79,    98,     0,    97,     0,    79,
     0,    84,     0,    89,     0,    89,    84,   100,     0,   103,
     0,    89,     0,     0,    85,   102,    98,    86,     0,    48,
    95,   101,     0,    46,    95,   101,     0,    46,    95,   101,
    47,   101,     0,    32,   112,    18,   112,    33,   112,   104,
    35,   101,     0,     0,    45,    54,     0,    42,    54,     0,
    10,   112,    80,   107,     0,   106,     0,    49,    54,     0,
    11,   106,     0,    41,    54,     0,    40,    54,     0,    40,
    66,     0,    57,    18,   112,     0,    57,    18,    10,   112,
    80,   107,     0,    66,    18,   112,     0,    43,   111,    53,
     0,    50,    82,   113,    83,    33,    82,   113,    83,     0,
    36,    66,     0,    52,   112,     0,    51,     0,     0,    34,
   112,     0,   112,     0,    54,     0,   105,     0,   105,    81,
   106,     0,   108,     0,   108,    81,   107,     0,    56,     0,
    82,   107,    83,     0,    55,     0,    55,    81,   109,     0,
   109,     0,   109,    44,     0,    65,     0,    58,     0,    59,
     0,    60,     0,    61,     0,    62,     0,    64,     0,    63,
     0,    68,     0,    69,     0,   111,     0,   111,    81,     0,
     0,    57,     0,    37,     0,    66,     0,    67,     0,    82,
   112,    83,     0,   112,    63,     0,    65,   112,     0,    58,
   112,     0,    59,   112,     0,    60,   112,     0,    61,   112,
     0,    62,   112,     0,    68,   113,    68,     0,    69,   113,
    70,     0,    65,    82,   113,    83,     0,   112,    58,   112,
     0,   112,    59,   112,     0,   112,    60,   112,     0,   112,
    61,   112,     0,   112,    62,   112,     0,   112,    64,   112,
     0,   112,     0,   112,    81,   113,     0,   112,    18,   112,
     0,     0,    35,   101,     0,   114,   115,     0,    46,    95,
   114,   115,     0,   116,     0
};

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    78,    79,    81,    89,    92,    96,   102,   113,   114,   115,
   117,   118,   119,   120,   121,   123,   124,   126,   127,   129,
   130,   132,   133,   135,   136,   137,   138,   140,   141,   142,
   143,   144,   145,   146,   149,   150,   151,   152,   153,   154,
   155,   156,   158,   160,   161,   162,   163,   165,   166,   168,
   169,   171,   173,   174,   176,   177,   179,   180,   181,   182,
   187,   190,   192,   194,   204,   205,   206,   207,   209,   210,
   211,   212,   213,   214,   220,   221,   222,   223,   228,   229,
   230,   231,   233,   234,   236,   237,   239,   240,   242,   243,
   245,   246,   248,   249,   251,   252,   254,   255,   256,   257,
   258,   259,   260,   261,   262,   263,   265,   266,   268,   270,
   271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
   281,   282,   283,   284,   286,   288,   290,   292,   294,   297,
   298,   300,   302,   303,   305,   307,   310
};

static const char * const yytname[] = {   "$","error","$illegal.","CST","VAR",
"SORT","FUNC","ALG","SPEC","ADDSPEC","REWR","PRT","GRAPH","PFEIL","TERM","NUM",
"ATT","IS","EQ","LA1","LA2","LA3","LA4","LA5","LOCAL","RU","RA","KOMMU","LB",
"IN","NIN","PARAM","FOR","TO","STEP","DO","DBG","LAST","BRA","OTHER","DATA",
"OUT","INC","EXE","VARPAR","SYS","IF","ELSE","WHILE","PRTNUM","LIFT","QUIT",
"RETURN","Id","String","Sort","Alg","Term","La1","La2","La3","La4","La5","Ru",
"Ra","Func","Const","Var","Bra","Bra1","Bra2","Terms","Form","Sorts","Functs",
"Forms","Algs","Cond2","Cond","'\\n'","':'","','","'('","')'","';'","'{'","'}'",
"prog","line","definition","idlist","att","@1","namedId","VORRANG","condition",
"condfunc","instructions","tinstructions","oinstructions","d_list","instruction",
"@2","aninstruction","step","prntexpr","prntlist","alglist","Alg2","sortlist",
"vsortlist","func","term","termlist","formula","vinstr","cformula","formlist",
"formula"
};
#endif

static const short yyr1[] = {     0,
    87,    87,    88,    89,    89,    89,    89,    89,    89,    89,
    89,    89,    89,    89,    89,    89,    89,    90,    90,    -1,
    -1,    -1,    -1,    91,    91,    92,    91,    93,    93,    93,
    93,    93,    93,    93,    94,    94,    94,    94,    94,    94,
    94,    94,    95,    96,    96,    96,    96,    97,    97,    98,
    98,    99,    -1,    -1,   100,   100,   101,   101,   102,   101,
   101,   101,   101,   101,   103,   103,   103,   103,   103,   103,
   103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
   103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
   108,   108,   109,   109,   110,   110,   111,   111,   111,   111,
   111,   111,   111,   111,   111,   111,    -1,    -1,   112,   112,
   112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
   112,   112,   112,   112,   112,   112,   112,   112,   112,   113,
   113,   114,   115,   115,   116,   116,   117
};

static const short yyr2[] = {     0,
     1,     2,     2,     8,     7,     9,     8,     4,     2,     4,
     4,     4,     4,     4,     2,     2,     4,     1,     3,     1,
     1,     1,     3,     0,     2,     0,     6,     1,     1,     1,
     1,     1,     1,     1,     0,     1,     1,     1,     1,     1,
     1,     1,     1,     4,     4,     4,     3,     1,     3,     1,
     3,     1,     1,     1,     1,     3,     1,     1,     0,     4,
     3,     3,     5,     9,     0,     2,     2,     4,     1,     2,
     2,     2,     2,     2,     3,     6,     3,     3,     8,     2,
     2,     1,     0,     2,     1,     1,     1,     3,     1,     3,
     1,     3,     1,     3,     1,     2,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
     1,     1,     3,     2,     2,     2,     2,     2,     2,     2,
     3,     3,     4,     3,     3,     3,     3,     3,     3,     1,
     3,     3,     0,     2,     2,     4,     1
};

static const short yydefact[] = {    65,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   110,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    82,     0,    86,   109,
     0,     0,     0,     0,     0,     0,   111,   112,     0,     0,
     0,    59,    65,     1,    58,     0,    48,    57,    87,    69,
    85,    28,    32,    33,    34,    98,    99,   100,   101,   102,
   104,   103,    97,    29,    30,   105,   106,     0,    18,    31,
     0,    15,     0,    16,     0,     0,   109,   111,     0,    71,
     0,     9,     0,     0,     0,    80,     0,     0,    73,    74,
    72,    67,     0,    66,     0,     0,     0,     0,    65,    43,
    65,    70,     0,    81,     0,   116,   117,   118,   119,   120,
     0,   115,     0,   130,     0,     0,     0,    65,     2,     3,
    65,     0,     0,     0,     0,     0,     0,   114,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    78,     0,     0,     0,     0,    62,    61,     0,
     0,    75,     0,     0,    77,     0,   121,   122,   113,    52,
     0,    50,    49,    88,   124,   125,   126,   127,   128,   129,
    11,    19,     8,    93,    95,     0,     0,    91,     0,    12,
    89,     0,   133,   137,    13,    14,     0,    68,    17,    10,
     0,     0,     0,     0,     0,     0,     0,    47,    65,     0,
     0,   123,   131,    60,    65,     0,    96,     0,     0,     0,
     0,     0,    65,   135,     0,     0,     0,     0,    44,    45,
    46,    63,     0,     0,    51,    94,    35,   133,    92,    90,
   132,   134,     0,    83,     0,    24,     0,    76,    36,    37,
    38,    39,    40,    42,    41,    24,   136,     0,     0,     0,
    24,     0,     5,     0,     4,     0,    84,    65,     7,    26,
    25,    79,     6,    64,     0,    55,     0,     0,    65,    56,
    27,     0,     0
};

static const short yydefgoto[] = {    43,
    44,    45,    68,   253,   265,    69,   246,    99,   100,    46,
   161,   162,   267,    47,   118,    48,   250,    49,    50,   210,
   181,   175,   176,    70,    51,   115,   183,   214,   184,   185
};

static const short yypact[] = {   296,
   493,   493,   493,   493,   493,   -47,     1,   409,   347,   493,
   510,     3,   409,     9,-32768,    26,   522,    11,    36,    43,
   522,    45,   -10,   -10,    51,    25,-32768,   409,-32768,    91,
   409,   409,   409,   409,   409,   427,    96,-32768,   409,   409,
   409,-32768,   213,-32768,-32768,    29,    31,-32768,    44,-32768,
   309,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    46,    53,-32768,
    55,-32768,    56,-32768,    60,    62,-32768,-32768,   363,-32768,
    65,    14,    66,    94,    24,-32768,    95,    98,-32768,-32768,
-32768,-32768,   117,-32768,    89,   106,   114,   409,   296,-32768,
   296,-32768,   409,   309,    -6,    97,    90,    68,    39,    10,
   409,-32768,   409,   -14,   108,   107,   225,   296,-32768,-32768,
   296,   347,   409,   409,   409,   409,   409,-32768,   409,   124,
   493,   144,   145,   329,   373,   -13,   146,   148,   126,   409,
   128,   145,-32768,   409,   409,   409,   257,   163,-32768,   132,
   409,   309,   131,   142,   309,   409,-32768,-32768,-32768,-32768,
   125,   147,-32768,-32768,    97,    90,    68,    39,    10,    10,
-32768,-32768,-32768,   157,   195,   227,   -10,-32768,   391,-32768,
   160,   123,   208,-32768,-32768,-32768,   -13,-32768,-32768,-32768,
   191,   173,   145,   233,   164,   174,   177,-32768,   296,   235,
   467,-32768,-32768,-32768,   296,   145,-32768,   211,   409,   186,
   -13,   409,   296,-32768,   196,   409,   263,   254,-32768,-32768,
-32768,-32768,   231,   -13,-32768,-32768,   271,   208,-32768,-32768,
   309,-32768,   261,   -23,   267,   307,   409,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   307,-32768,   243,   409,   290,
   307,   455,-32768,   244,-32768,   273,   309,   296,-32768,-32768,
-32768,-32768,-32768,-32768,   159,   245,   247,   159,   296,-32768,
-32768,   331,-32768
};

static const short yypgoto[] = {-32768,
   300,  -176,    12,  -180,-32768,    -4,-32768,   -22,-32768,  -105,
   154,-32768,    81,   -89,-32768,-32768,-32768,-32768,    -1,  -131,
-32768,   168,  -112,    47,    -7,   -33,   143,   149,-32768,   216
};


#define	YYLAST		591


static const short yytable[] = {    73,
    79,   101,   180,   151,   188,    85,   116,    80,    75,   148,
   249,   149,   160,    71,    72,   163,    74,    95,    96,    97,
   104,    81,    83,   106,   107,   108,   109,   110,   112,   194,
    15,   114,   114,   117,   123,   124,   125,   126,   127,   128,
   129,   140,   178,   123,   124,   125,   126,   127,   128,   129,
    77,    31,    32,    33,    34,    35,    76,    84,    36,    78,
    38,    39,    40,    88,    89,   255,   156,    93,   187,   150,
   259,    98,   128,   129,    86,    41,    90,   154,    87,   230,
   217,   123,   124,   125,   126,   127,   128,   129,   266,    91,
   147,   266,   238,   -32,   -32,   114,    92,   152,    94,   160,
   127,   128,   129,   153,   102,   155,   103,   120,   105,   222,
   195,   196,   197,   113,   121,   165,   166,   167,   168,   169,
   164,   170,   203,   232,   122,   130,   182,   182,   126,   127,
   128,   129,   192,   131,   132,   133,   114,   114,   114,   134,
   212,   135,   172,   201,   137,   138,   139,   141,   114,   125,
   126,   127,   128,   129,   209,   124,   125,   126,   127,   128,
   129,     1,     2,     3,     4,     5,     6,     7,   264,   143,
   144,   117,    10,    11,    12,   157,   158,   142,   171,   271,
   123,   124,   125,   126,   127,   128,   129,   145,   123,   124,
   125,   126,   127,   128,   129,   146,    16,    17,   173,   174,
   189,   182,   190,   254,   231,   216,   191,   193,   234,   199,
   204,   156,   272,   159,   200,     1,     2,     3,     4,     5,
     6,     7,     8,     9,   202,   205,    10,    11,    12,   114,
   123,   124,   125,   126,   127,   128,   129,   206,   207,   208,
   211,   257,   213,   215,    13,   218,   219,   261,    14,    15,
    16,    17,    18,    19,    20,    21,   220,    22,    23,   221,
    24,    25,    26,    27,    28,   227,    29,   223,   229,    30,
    31,    32,    33,    34,    35,   235,   233,    36,    37,    38,
    39,    40,   123,   124,   125,   126,   127,   128,   129,   239,
   240,   241,   242,   243,    41,   244,   245,    42,     1,     2,
     3,     4,     5,     6,     7,     8,     9,   159,   236,    10,
    11,    12,   237,   248,   123,   124,   125,   126,   127,   128,
   129,   251,   252,   256,   258,   263,   262,    13,   268,   269,
   273,    14,    15,    16,    17,    18,    19,    20,    21,   198,
    22,    23,   119,    24,    25,    26,    27,    28,   270,    29,
   186,   228,    30,    31,    32,    33,    34,    35,   225,     0,
    36,    37,    38,    39,    40,    15,   123,   124,   125,   126,
   127,   128,   129,   226,   177,     0,   247,    41,     0,     0,
    42,     0,     0,    15,   178,    77,    31,    32,    33,    34,
    35,     0,     0,    36,    78,    38,    39,    40,     0,     0,
    29,     0,     0,    77,    31,    32,    33,    34,    35,    15,
   179,    36,    78,    38,    39,    40,     0,     0,   177,     0,
   123,   124,   125,   126,   127,   128,   129,    15,    41,    77,
    31,    32,    33,    34,    35,     0,     0,    36,    78,    38,
    39,    40,   136,     0,     0,    15,   178,    77,    31,    32,
    33,    34,    35,     0,    41,    36,    78,    38,    39,    40,
     0,     0,     0,    15,     0,    77,    31,    32,    33,    34,
    35,     0,   179,    36,    78,    38,    39,    40,     0,     0,
     0,     0,     0,    77,    31,    32,    33,    34,    35,     0,
    41,    36,    78,    38,    39,    40,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    52,   111,    53,
    54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,    67,   123,   124,   125,   126,   127,   128,
   129,     0,     0,     0,     0,     0,   260,     0,     0,     0,
     0,     0,     0,     0,     0,    52,   224,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    52,     0,    82,    54,    55,    56,    57,    58,
    59,    60,    61,    62,    63,    64,    65,    66,    67,    56,
    57,    58,    59,    60,    61,    62,    63,     0,     0,    66,
    67
};

static const short yycheck[] = {     4,
     8,    24,   134,    10,   136,    13,    40,     9,    56,    99,
    34,   101,   118,     2,     3,   121,     5,    28,    29,    30,
    28,    10,    11,    31,    32,    33,    34,    35,    36,   142,
    37,    39,    40,    41,    58,    59,    60,    61,    62,    63,
    64,    18,    56,    58,    59,    60,    61,    62,    63,    64,
    57,    58,    59,    60,    61,    62,    56,    55,    65,    66,
    67,    68,    69,    17,    54,   246,    81,    21,    82,   103,
   251,    82,    63,    64,    66,    82,    66,   111,    53,   211,
   193,    58,    59,    60,    61,    62,    63,    64,   265,    54,
    98,   268,   224,    80,    81,   103,    54,   105,    54,   205,
    62,    63,    64,   111,    54,   113,    82,    79,    18,   199,
   144,   145,   146,    18,    84,   123,   124,   125,   126,   127,
   122,   129,   156,   213,    81,    80,   134,   135,    61,    62,
    63,    64,   140,    81,    80,    80,   144,   145,   146,    80,
    18,    80,   131,   151,    80,    80,    53,    53,   156,    60,
    61,    62,    63,    64,   177,    59,    60,    61,    62,    63,
    64,     3,     4,     5,     6,     7,     8,     9,   258,    53,
    82,   179,    14,    15,    16,    68,    70,    80,    55,   269,
    58,    59,    60,    61,    62,    63,    64,    82,    58,    59,
    60,    61,    62,    63,    64,    82,    38,    39,    55,    55,
    55,   209,    55,   237,   212,    33,    81,    80,   216,    47,
    86,    81,     0,    83,    83,     3,     4,     5,     6,     7,
     8,     9,    10,    11,    83,    79,    14,    15,    16,   237,
    58,    59,    60,    61,    62,    63,    64,    81,    44,    13,
    81,   249,    35,    53,    32,    13,    83,   252,    36,    37,
    38,    39,    40,    41,    42,    43,    83,    45,    46,    83,
    48,    49,    50,    51,    52,    55,    54,    33,    83,    57,
    58,    59,    60,    61,    62,    13,    81,    65,    66,    67,
    68,    69,    58,    59,    60,    61,    62,    63,    64,    19,
    20,    21,    22,    23,    82,    25,    26,    85,     3,     4,
     5,     6,     7,     8,     9,    10,    11,    83,    55,    14,
    15,    16,    82,    53,    58,    59,    60,    61,    62,    63,
    64,    55,    16,    81,    35,    53,    83,    32,    84,    83,
     0,    36,    37,    38,    39,    40,    41,    42,    43,    83,
    45,    46,    43,    48,    49,    50,    51,    52,   268,    54,
   135,   209,    57,    58,    59,    60,    61,    62,   205,    -1,
    65,    66,    67,    68,    69,    37,    58,    59,    60,    61,
    62,    63,    64,   206,    46,    -1,   228,    82,    -1,    -1,
    85,    -1,    -1,    37,    56,    57,    58,    59,    60,    61,
    62,    -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,
    54,    -1,    -1,    57,    58,    59,    60,    61,    62,    37,
    82,    65,    66,    67,    68,    69,    -1,    -1,    46,    -1,
    58,    59,    60,    61,    62,    63,    64,    37,    82,    57,
    58,    59,    60,    61,    62,    -1,    -1,    65,    66,    67,
    68,    69,    80,    -1,    -1,    37,    56,    57,    58,    59,
    60,    61,    62,    -1,    82,    65,    66,    67,    68,    69,
    -1,    -1,    -1,    37,    -1,    57,    58,    59,    60,    61,
    62,    -1,    82,    65,    66,    67,    68,    69,    -1,    -1,
    -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    -1,
    82,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    82,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    58,    59,    60,    61,    62,    63,
    64,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    53,    80,    55,    56,    57,
    58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
    68,    69,    53,    -1,    55,    56,    57,    58,    59,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    58,
    59,    60,    61,    62,    63,    64,    65,    -1,    -1,    68,
    69
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/gnu/lib/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#define YYLEX		yylex(&yylval, &yylloc)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 169 "/usr/local/gnu/lib/bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
#ifdef YYLSP_NEEDED
		 &yyls1, size * sizeof (*yylsp),
#endif
		 &yystacksize);

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
#line 81 "syn.y"
{Node * temp;
														if (yyvsp[-1].y_nod) { temp = mknod(FUNC,(Node *) sequence,yyvsp[-1].y_nod);
															is_running();
															CALLFUNCT(temp);
															is_not_running();
															delete(temp);}
														;
    break;}
case 4:
#line 89 "syn.y"
{	yyval.y_nod=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) yyvsp[-6].y_nod,yyvsp[-1].y_int,(Node *) yyvsp[-2].y_sym,yyvsp[-4].y_nod,FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) yyvsp[-6].y_nod,yyvsp[0].y_nod)),NULL)));;
    break;}
case 5:
#line 92 "syn.y"
{ yyval.y_nod=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) yyvsp[-5].y_nod,
                                              mknod(PARAM,yyvsp[-3].y_nod,
                                              mknod(PARAM,(Node *) yyvsp[-1].y_sym,yyvsp[0].y_nod))));;
    break;}
case 6:
#line 96 "syn.y"
{ yyval.y_nod=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) yyvsp[-7].y_sym,
                                              mknod(PARAM,(Node *) give_ufkt(name(yyvsp[-6].y_sym)),
                                              mknod(PARAM,(Node *) give_ufkt(name(yyvsp[-4].y_sym)),
                                              mknod(PARAM,(Node *) give_ufkt(name(yyvsp[-2].y_sym)),
                                              (Node *) give_ufkt(name(yyvsp[0].y_sym)))))));	;
    break;}
case 7:
#line 102 "syn.y"
{Node * fkts;  /* Klammern */
							            				if ((yyvsp[-6].y_sym)==(yyvsp[-5].y_sym))
							            					fkts=mknod(PARAM,DECLARE((Node *) yyvsp[-6].y_sym,Bra,(Node *) yyvsp[-1].y_sym,yyvsp[-3].y_nod,FALSE),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) yyvsp[-6].y_sym,yyvsp[0].y_nod)),NULL));
											            else
								             				fkts=mknod(PARAM,DECLARE((Node *) yyvsp[-6].y_sym,Bra1,(Node *) yyvsp[-1].y_sym,yyvsp[-3].y_nod,FALSE),
                                       mknod(PARAM,DECLARE((Node *) yyvsp[-5].y_sym,Bra2,(Node *) yyvsp[-1].y_sym,yyvsp[-3].y_nod,FALSE),
                                       mknod(PARAM, mknod(FUNC,(Node *) set_brackets,mknod(PARAM,(Node *) yyvsp[-6].y_sym,(Node *) yyvsp[-5].y_sym)),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) yyvsp[-6].y_sym,yyvsp[0].y_nod)),NULL))));
																	yyval.y_nod=mknod(FUNC,(Node *) sequence,fkts);
																	;
    break;}
case 8:
#line 113 "syn.y"
{yyval.y_nod=DECLARE(yyvsp[-2].y_nod,Var,(Node *) yyvsp[0].y_sym,NULL,FALSE);;
    break;}
case 9:
#line 114 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) set_numbertype,(Node *) (yyvsp[0].y_sym)); /* setzt numbertype fuer mknum */;
    break;}
case 10:
#line 115 "syn.y"
{ /* Variablen fuer Numerische Zahlen */
									                yyval.y_nod=DECLARE(yyvsp[-2].y_nod,Var,(Node *) yyvsp[0].y_sym,NULL,TRUE);;
    break;}
case 11:
#line 117 "syn.y"
{yyval.y_nod=DECLARE(yyvsp[-2].y_nod,Const,(Node *) yyvsp[0].y_sym,NULL,FALSE);;
    break;}
case 12:
#line 118 "syn.y"
{yyval.y_nod = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) yyvsp[-2].y_sym,(Node *) yyvsp[0].y_nod));;
    break;}
case 13:
#line 119 "syn.y"
{yyval.y_nod = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) yyvsp[-2].y_sym,yyvsp[0].y_nod));	;
    break;}
case 14:
#line 120 "syn.y"
{yyval.y_nod = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) yyvsp[-2].y_sym,yyvsp[0].y_nod));;
    break;}
case 15:
#line 121 "syn.y"
{yyval.y_nod=DECLARE(yyvsp[0].y_nod,Sort,NULL,NULL,FALSE);;
    break;}
case 16:
#line 123 "syn.y"
{yyval.y_nod=DECLARE(yyvsp[0].y_nod,Alg,NULL,NULL,FALSE);;
    break;}
case 17:
#line 124 "syn.y"
{yyval.y_nod=DECLARE(yyvsp[-2].y_nod,Term,(Node *) yyvsp[0].y_sym,NULL,FALSE);;
    break;}
case 18:
#line 126 "syn.y"
{yyval.y_nod = yyvsp[0].y_nod;;
    break;}
case 19:
#line 127 "syn.y"
{yyval.y_nod = mknod(Id,yyvsp[-2].y_nod,yyvsp[0].y_nod);;
    break;}
case 20:
#line 129 "syn.y"
{yyval.y_nod=(Node *) yyvsp[0].y_sym;;
    break;}
case 21:
#line 130 "syn.y"
{yyval.y_nod=(Node *) yyvsp[0].y_sym;;
    break;}
case 22:
#line 132 "syn.y"
{yyval.y_nod = mknod(PARAM,(Node *) yyvsp[0].y_nod,NULL);;
    break;}
case 23:
#line 133 "syn.y"
{yyval.y_nod = mknod(PARAM,(Node *) yyvsp[-2].y_nod,yyvsp[0].y_nod);;
    break;}
case 24:
#line 135 "syn.y"
{ yyval.y_nod = NULL;;
    break;}
case 25:
#line 136 "syn.y"
{ yyval.y_nod = mknod(ATT,(Node *) give_ufkt(name((Symbol *) yyvsp[0].y_nod)),NULL);;
    break;}
case 26:
#line 137 "syn.y"
{block_begin();no_protect();;
    break;}
case 27:
#line 138 "syn.y"
{protect();block_end();yyval.y_nod =mknod(PARAM,yyvsp[-2].y_nod,yyvsp[0].y_nod);;
    break;}
case 28:
#line 140 "syn.y"
{ yyval.y_nod = (Node *) yyvsp[0].y_sym;;
    break;}
case 29:
#line 141 "syn.y"
{ yyval.y_nod = (Node *) yyvsp[0].y_sym;;
    break;}
case 30:
#line 142 "syn.y"
{ yyval.y_nod = (Node *) yyvsp[0].y_sym;;
    break;}
case 31:
#line 143 "syn.y"
{ yyval.y_nod = (Node *) yyvsp[0].y_nod;;
    break;}
case 32:
#line 144 "syn.y"
{ yyval.y_nod = (Node *) yyvsp[0].y_sym;;
    break;}
case 33:
#line 145 "syn.y"
{ yyval.y_nod = (Node *) yyvsp[0].y_sym;;
    break;}
case 34:
#line 146 "syn.y"
{ yyval.y_nod = (Node *) yyvsp[0].y_sym;;
    break;}
case 35:
#line 149 "syn.y"
{yyval.y_int = Func;;
    break;}
case 36:
#line 150 "syn.y"
{yyval.y_int = La1;	/* Linksassoziativ */;
    break;}
case 37:
#line 151 "syn.y"
{yyval.y_int = La2;	/* Linksassoziativ */;
    break;}
case 38:
#line 152 "syn.y"
{yyval.y_int = La3;	/* Linksassoziativ */;
    break;}
case 39:
#line 153 "syn.y"
{yyval.y_int = La4;	/* Linksassoziativ */;
    break;}
case 40:
#line 154 "syn.y"
{yyval.y_int = La5;	/* Linksassoziativ */;
    break;}
case 41:
#line 155 "syn.y"
{yyval.y_int = Ra;  	/* Rechtsassoziativ */;
    break;}
case 42:
#line 156 "syn.y"
{yyval.y_int = Ru;	  /* Rechts Unaer */;
    break;}
case 43:
#line 158 "syn.y"
{yyval.y_nod = yyvsp[0].y_nod;;
    break;}
case 44:
#line 160 "syn.y"
{yyval.y_nod = mknod(Cond,(Node *) lower_between,yyvsp[-1].y_nod);;
    break;}
case 45:
#line 161 "syn.y"
{yyval.y_nod = mknod(Cond,(Node *) in_tree,yyvsp[-1].y_nod);;
    break;}
case 46:
#line 162 "syn.y"
{yyval.y_nod = mknod(Cond,(Node *) not_in_tree,yyvsp[-1].y_nod);;
    break;}
case 47:
#line 163 "syn.y"
{yyval.y_nod = mknod(Cond,(Node *) isnt_zero,yyvsp[-1].y_nod);;
    break;}
case 48:
#line 165 "syn.y"
{if (yyvsp[0].y_nod) yyval.y_nod = mknod(PARAM,yyvsp[0].y_nod,NULL); else yyval.y_nod=NULL;;
    break;}
case 49:
#line 166 "syn.y"
{if (yyvsp[-2].y_nod) yyval.y_nod = mknod(PARAM,yyvsp[-2].y_nod,yyvsp[0].y_nod);else yyval.y_nod=yyvsp[0].y_nod;;
    break;}
case 50:
#line 168 "syn.y"
{if (yyvsp[0].y_nod) yyval.y_nod = mknod(PARAM,yyvsp[0].y_nod,NULL); else yyval.y_nod=NULL;;
    break;}
case 51:
#line 169 "syn.y"
{if (yyvsp[-2].y_nod) yyval.y_nod = mknod(PARAM,yyvsp[-2].y_nod,yyvsp[0].y_nod);else yyval.y_nod=yyvsp[0].y_nod;;
    break;}
case 52:
#line 171 "syn.y"
{if(yyvsp[0].y_nod) yyval.y_nod=mknod(FUNC,(Node *) sequence,yyvsp[0].y_nod); else yyval.y_nod=yyvsp[0].y_nod;;
    break;}
case 53:
#line 173 "syn.y"
{/* oder ; , bringt aber shift-reduce conflicts wegen alglist: Alg;alglist */;
    break;}
case 55:
#line 176 "syn.y"
{yyval.y_nod = mknod(PARAM,in_block_def(yyvsp[0].y_nod),NULL);;
    break;}
case 56:
#line 177 "syn.y"
{yyval.y_nod = mknod(PARAM,in_block_def(yyvsp[-2].y_nod),yyvsp[0].y_nod);;
    break;}
case 57:
#line 179 "syn.y"
{yyval.y_nod = in_block_instruct(yyvsp[0].y_nod); /* Locale Variablen pruefen ! */ ;
    break;}
case 58:
#line 180 "syn.y"
{yyval.y_nod = in_block_def(yyvsp[0].y_nod);;
    break;}
case 59:
#line 181 "syn.y"
{block_begin();no_protect();;
    break;}
case 60:
#line 182 "syn.y"
{protect();block_end();
																yyval.y_nod=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,yyvsp[-1].y_nod),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));;
    break;}
case 61:
#line 187 "syn.y"
{Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,yyvsp[-1].y_nod,NULL /* wird dann $3 */)));
																		merk->r->r = yyvsp[0].y_nod;yyval.y_nod=rtw;;
    break;}
case 62:
#line 190 "syn.y"
{Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,yyvsp[-1].y_nod,mknod(PARAM,NULL,NULL))));
																		merk->r->r->l = yyvsp[0].y_nod;yyval.y_nod=rtw;;
    break;}
case 63:
#line 192 "syn.y"
{Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,yyvsp[-3].y_nod,mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		merk->r->r->l = yyvsp[-2].y_nod;merk->r->r->r = yyvsp[0].y_nod;yyval.y_nod=rtw;;
    break;}
case 64:
#line 195 "syn.y"
{Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) forschleife,
																mknod(PARAM,
																	mknod(PARAM,yyvsp[-5].y_nod,yyvsp[-3].y_nod),
																	mknod(PARAM,
																		mknod(PARAM,yyvsp[-2].y_nod,(Node *) (yyvsp[-7].y_nod)),
																		NULL /* $9 */) )));	
														merk->r->r->r = yyvsp[0].y_nod;yyval.y_nod=rtw;;
    break;}
case 65:
#line 204 "syn.y"
{yyval.y_nod=NULL;;
    break;}
case 66:
#line 205 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) system_fkt,(Node *) (yyvsp[0].y_sym));;
    break;}
case 67:
#line 206 "syn.y"
{/* include(name($2));$$=NULL;*/ yyval.y_nod=mknod(FUNC,(Node *) include_fkt,(Node *) (yyvsp[0].y_sym)); ;
    break;}
case 68:
#line 207 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod)));
														 rtypes(lastterm)=get_type(yyvsp[-2].y_nod);;
    break;}
case 69:
#line 209 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,yyvsp[0].y_nod));;
    break;}
case 70:
#line 210 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) prt_num,(Node *) (yyvsp[0].y_sym));;
    break;}
case 71:
#line 211 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) sequence,yyvsp[0].y_nod); /* ohne \n */ ;
    break;}
case 72:
#line 212 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) changeout,(Node *) (yyvsp[0].y_sym));;
    break;}
case 73:
#line 213 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) changedata,(Node *) (yyvsp[0].y_sym));;
    break;}
case 74:
#line 214 "syn.y"
{if (rtypes(yyvsp[0].y_sym) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               yyval.y_nod=NULL;}
                             else
                               yyval.y_nod=mknod(FUNC,(Node *) readdata,(Node *) (yyvsp[0].y_sym));
                            ;
    break;}
case 75:
#line 220 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),yyvsp[0].y_nod));;
    break;}
case 76:
#line 221 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) yyvsp[-5].y_sym,mknod(PARAM,(Node *) yyvsp[-2].y_nod,(Node *) yyvsp[0].y_nod)));;
    break;}
case 77:
#line 222 "syn.y"
{ yyval.y_nod=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));;
    break;}
case 78:
#line 223 "syn.y"
{yyval.y_nod = NULL;
																exe_always(yyvsp[-1].y_nod)=TRUE;
																hasval(yyvsp[-1].y_nod) = TRUE;
																value(yyvsp[-1].y_nod)  = (Node *) give_ufkt(name(yyvsp[0].y_sym));
 													;
    break;}
case 79:
#line 228 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) yyvsp[-1].y_nod,(Node *) yyvsp[-5].y_nod));;
    break;}
case 80:
#line 229 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) setdebug,(Node *) (yyvsp[0].y_sym));;
    break;}
case 81:
#line 230 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) return_fkt,yyvsp[0].y_nod);;
    break;}
case 82:
#line 231 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) quit_fkt,NULL);;
    break;}
case 83:
#line 233 "syn.y"
{yyval.y_nod=(Node *) NULL;;
    break;}
case 84:
#line 234 "syn.y"
{yyval.y_nod=yyvsp[0].y_nod;;
    break;}
case 85:
#line 236 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) printterm,yyvsp[0].y_nod); rtypes(lastterm)=get_type(yyvsp[0].y_nod);;
    break;}
case 86:
#line 237 "syn.y"
{yyval.y_nod=mknod(FUNC,(Node *) printstring,(Node *) (yyvsp[0].y_sym));;
    break;}
case 87:
#line 239 "syn.y"
{yyval.y_nod=mknod(PARAM,yyvsp[0].y_nod,NULL);;
    break;}
case 88:
#line 240 "syn.y"
{yyval.y_nod=mknod(PARAM,yyvsp[-2].y_nod,yyvsp[0].y_nod);;
    break;}
case 89:
#line 242 "syn.y"
{yyval.y_nod = mknod(Algs,(yyvsp[0].y_nod),NULL);;
    break;}
case 90:
#line 243 "syn.y"
{yyval.y_nod = mknod(Algs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));;
    break;}
case 91:
#line 245 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 92:
#line 246 "syn.y"
{yyval.y_nod = mknod(Alg,(yyvsp[-1].y_nod),NULL);;
    break;}
case 93:
#line 248 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 94:
#line 249 "syn.y"
{yyval.y_nod = mknod(Sorts,(Node *) (yyvsp[-2].y_sym),yyvsp[0].y_nod);;
    break;}
case 95:
#line 251 "syn.y"
{yyval.y_nod = yyvsp[0].y_nod;;
    break;}
case 96:
#line 252 "syn.y"
{yyval.y_nod = mknod(VARPAR,(Node *) (yyvsp[-1].y_nod),NULL);;
    break;}
case 97:
#line 254 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 98:
#line 255 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 99:
#line 256 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 100:
#line 257 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 101:
#line 258 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 102:
#line 259 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 103:
#line 260 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 104:
#line 261 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 105:
#line 262 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 106:
#line 263 "syn.y"
{yyval.y_nod = (Node *) (yyvsp[0].y_sym);;
    break;}
case 107:
#line 265 "syn.y"
{yyval.y_nod = yyvsp[0].y_nod;;
    break;}
case 108:
#line 266 "syn.y"
{yyval.y_nod = mknod(Functs,yyvsp[-2].y_nod,yyvsp[0].y_nod);;
    break;}
case 109:
#line 268 "syn.y"
{	yyval.y_nod = (Node *) yyvsp[0].y_sym; /* tcopy(); merkt sich keine Abhaengigkeiten und funktioniert nicht in Bloecken */ 
														;
    break;}
case 110:
#line 270 "syn.y"
{yyval.y_nod = (Node *) lastterm;;
    break;}
case 111:
#line 271 "syn.y"
{yyval.y_nod = mknod(Const,(Node *) (yyvsp[0].y_sym),NULL);;
    break;}
case 112:
#line 272 "syn.y"
{yyval.y_nod = (Node *) yyvsp[0].y_sym;;
    break;}
case 113:
#line 273 "syn.y"
{yyval.y_nod = yyvsp[-1].y_nod;;
    break;}
case 114:
#line 274 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[0].y_sym),(yyvsp[-1].y_nod)), (yyvsp[-1].y_nod) ); ;
    break;}
case 115:
#line 275 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); ;
    break;}
case 116:
#line 276 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); ;
    break;}
case 117:
#line 277 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); ;
    break;}
case 118:
#line 278 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); ;
    break;}
case 119:
#line 279 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); ;
    break;}
case 120:
#line 280 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); ;
    break;}
case 121:
#line 281 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-2].y_sym),(yyvsp[-1].y_nod)), (yyvsp[-1].y_nod) ); ;
    break;}
case 122:
#line 282 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-2].y_sym),(yyvsp[-1].y_nod)), (yyvsp[-1].y_nod) ); ;
    break;}
case 123:
#line 283 "syn.y"
{yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-3].y_sym),(yyvsp[-1].y_nod)),(yyvsp[-1].y_nod));;
    break;}
case 124:
#line 284 "syn.y"
{nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);;
    break;}
case 125:
#line 286 "syn.y"
{nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);;
    break;}
case 126:
#line 288 "syn.y"
{nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);;
    break;}
case 127:
#line 290 "syn.y"
{nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);;
    break;}
case 128:
#line 292 "syn.y"
{nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);;
    break;}
case 129:
#line 294 "syn.y"
{nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);;
    break;}
case 130:
#line 297 "syn.y"
{yyval.y_nod = yyvsp[0].y_nod;;
    break;}
case 131:
#line 298 "syn.y"
{yyval.y_nod = mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);;
    break;}
case 132:
#line 300 "syn.y"
{yyval.y_nod = mknod(Form,yyvsp[-2].y_nod,yyvsp[0].y_nod);;
    break;}
case 133:
#line 302 "syn.y"
{yyval.y_nod = NULL;;
    break;}
case 134:
#line 303 "syn.y"
{yyval.y_nod = yyvsp[0].y_nod;;
    break;}
case 135:
#line 305 "syn.y"
{((yyvsp[-1].y_nod)->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),(yyvsp[-1].y_nod)->r),
																									 yyvsp[0].y_nod);yyval.y_nod = yyvsp[-1].y_nod;;
    break;}
case 136:
#line 307 "syn.y"
{((yyvsp[-1].y_nod)->r)=mknod(PARAM,mknod(Cond2,yyvsp[-2].y_nod,(yyvsp[-1].y_nod)->r),
																									 yyvsp[0].y_nod);yyval.y_nod = yyvsp[-1].y_nod;;
    break;}
case 137:
#line 310 "syn.y"
{yyval.y_nod = mknod(Forms,yyvsp[0].y_nod,NULL); /* NULL dient zum Einhaengen weiterer Formeln !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. wegen SPEC real : A+B=C;a=3 */
															;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 442 "/usr/local/gnu/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 314 "syn.y"

