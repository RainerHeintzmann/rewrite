/* A Bison parser, made from syn.y, by GNU bison 1.75.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON	1

/* Pure parsers.  */
#define YYPURE	0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CST = 258,
     VAR = 259,
     SORT = 260,
     FUNC = 261,
     ALG = 262,
     SPEC = 263,
     ADDSPEC = 264,
     REWR = 265,
     PRT = 266,
     GRAPH = 267,
     PFEIL = 268,
     TERM = 269,
     NUM = 270,
     ATT = 271,
     IS = 272,
     EQ = 273,
     INFO = 274,
     LA1 = 275,
     LA2 = 276,
     LA3 = 277,
     LA4 = 278,
     LA5 = 279,
     LOCAL = 280,
     RU = 281,
     RA = 282,
     KOMMU = 283,
     LB = 284,
     IN = 285,
     NIN = 286,
     PARAM = 287,
     FOR = 288,
     TO = 289,
     STEP = 290,
     DO = 291,
     DBG = 292,
     LAST = 293,
     BRA = 294,
     OTHER = 295,
     DATA = 296,
     OUT = 297,
     INC = 298,
     EXE = 299,
     VARPAR = 300,
     SYS = 301,
     IF = 302,
     ELSE = 303,
     WHILE = 304,
     PRTNUM = 305,
     LIFT = 306,
     QUIT = 307,
     RETURN = 308,
     Id = 309,
     String = 310,
     Sort = 311,
     Alg = 312,
     Term = 313,
     La1 = 314,
     La2 = 315,
     La3 = 316,
     La4 = 317,
     La5 = 318,
     Ru = 319,
     Ra = 320,
     Func = 321,
     Const = 322,
     Var = 323,
     Bra = 324,
     Bra1 = 325,
     Bra2 = 326,
     Terms = 327,
     Form = 328,
     Sorts = 329,
     Functs = 330,
     Forms = 331,
     Algs = 332,
     Cond2 = 333,
     Cond = 334
   };
#endif
#define CST 258
#define VAR 259
#define SORT 260
#define FUNC 261
#define ALG 262
#define SPEC 263
#define ADDSPEC 264
#define REWR 265
#define PRT 266
#define GRAPH 267
#define PFEIL 268
#define TERM 269
#define NUM 270
#define ATT 271
#define IS 272
#define EQ 273
#define INFO 274
#define LA1 275
#define LA2 276
#define LA3 277
#define LA4 278
#define LA5 279
#define LOCAL 280
#define RU 281
#define RA 282
#define KOMMU 283
#define LB 284
#define IN 285
#define NIN 286
#define PARAM 287
#define FOR 288
#define TO 289
#define STEP 290
#define DO 291
#define DBG 292
#define LAST 293
#define BRA 294
#define OTHER 295
#define DATA 296
#define OUT 297
#define INC 298
#define EXE 299
#define VARPAR 300
#define SYS 301
#define IF 302
#define ELSE 303
#define WHILE 304
#define PRTNUM 305
#define LIFT 306
#define QUIT 307
#define RETURN 308
#define Id 309
#define String 310
#define Sort 311
#define Alg 312
#define Term 313
#define La1 314
#define La2 315
#define La3 316
#define La4 317
#define La5 318
#define Ru 319
#define Ra 320
#define Func 321
#define Const 322
#define Var 323
#define Bra 324
#define Bra1 325
#define Bra2 326
#define Terms 327
#define Form 328
#define Sorts 329
#define Functs 330
#define Forms 331
#define Algs 332
#define Cond2 333
#define Cond 334




/* Copy the first part of user declarations.  */
#line 3 "syn.y"


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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#ifndef YYSTYPE
#line 42 "syn.y"
typedef union {
	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	} yystype;
/* Line 193 of /usr/share/bison/yacc.c.  */
#line 277 "syn.tab.c"
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

#ifndef YYLTYPE
typedef struct yyltype
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} yyltype;
# define YYLTYPE yyltype
# define YYLTYPE_IS_TRIVIAL 1
#endif

/* Copy the second part of user declarations.  */


/* Line 213 of /usr/share/bison/yacc.c.  */
#line 298 "syn.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];	\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  122
#define YYLAST   610

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  32
/* YYNRULES -- Number of rules. */
#define YYNRULES  132
/* YYNRULES -- Number of states. */
#define YYNSTATES  278

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   334

#define YYTRANSLATE(X) \
  ((unsigned)(X) <= YYMAXUTOK ? yytranslate[X] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      80,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      83,    84,     2,     2,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    81,    85,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,     2,    87,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    20,    28,    38,    47,
      52,    55,    60,    65,    70,    75,    80,    83,    86,    91,
      93,    97,    98,   101,   102,   109,   111,   113,   115,   117,
     119,   121,   123,   124,   126,   128,   130,   132,   134,   136,
     138,   140,   145,   150,   155,   159,   161,   165,   167,   171,
     173,   175,   179,   181,   183,   184,   189,   193,   197,   203,
     213,   214,   217,   220,   223,   228,   230,   233,   236,   239,
     242,   245,   249,   256,   260,   264,   273,   276,   279,   281,
     282,   285,   287,   289,   291,   295,   297,   301,   303,   307,
     309,   313,   315,   318,   320,   322,   324,   326,   328,   330,
     332,   334,   336,   338,   340,   342,   344,   349,   351,   355,
     358,   361,   364,   367,   370,   373,   376,   380,   384,   389,
     393,   397,   401,   405,   409,   413,   415,   419,   423,   424,
     427,   430,   435
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      89,     0,    -1,    90,    -1,    89,    90,    -1,    99,    80,
      -1,     6,    95,    81,   112,    13,    56,    96,    93,    -1,
      40,   113,    81,   112,    13,    56,    93,    -1,    16,    56,
      54,    82,    54,    82,    54,    82,    54,    -1,    39,    54,
      54,    81,   112,    13,    56,    93,    -1,     4,    92,    81,
      56,    -1,    15,    56,    -1,    15,    92,    81,    56,    -1,
       3,    92,    81,    56,    -1,     8,    57,    81,   109,    -1,
       8,    57,    81,   119,    -1,     9,    57,    81,   119,    -1,
       5,    92,    -1,     7,    92,    -1,    14,    92,    81,    56,
      -1,    95,    -1,    95,    82,    92,    -1,    -1,    16,    95,
      -1,    -1,    16,    83,    94,   102,    84,   103,    -1,    54,
      -1,    67,    -1,    68,    -1,   113,    -1,    56,    -1,    57,
      -1,    58,    -1,    -1,    20,    -1,    21,    -1,    22,    -1,
      23,    -1,    24,    -1,    27,    -1,    26,    -1,    98,    -1,
      29,    83,   115,    84,    -1,    30,    83,   115,    84,    -1,
      31,    83,   115,    84,    -1,    83,   114,    84,    -1,   103,
      -1,   103,    85,    99,    -1,   101,    -1,   101,    80,   100,
      -1,    99,    -1,    91,    -1,    91,    85,   102,    -1,   105,
      -1,    91,    -1,    -1,    86,   104,   100,    87,    -1,    49,
      97,   103,    -1,    47,    97,   103,    -1,    47,    97,   103,
      48,   103,    -1,    33,   114,    18,   114,    34,   114,   106,
      36,   103,    -1,    -1,    46,    55,    -1,    43,    55,    -1,
      19,    95,    -1,    10,   114,    81,   109,    -1,   108,    -1,
      50,    55,    -1,    11,   108,    -1,    42,    55,    -1,    41,
      55,    -1,    41,    67,    -1,    58,    18,   114,    -1,    58,
      18,    10,   114,    81,   109,    -1,    67,    18,   114,    -1,
      44,   113,    54,    -1,    51,    83,   115,    84,    34,    83,
     115,    84,    -1,    37,    67,    -1,    53,   114,    -1,    52,
      -1,    -1,    35,   114,    -1,   114,    -1,    55,    -1,   107,
      -1,   107,    82,   108,    -1,   110,    -1,   110,    82,   109,
      -1,    57,    -1,    83,   109,    84,    -1,    56,    -1,    56,
      82,   111,    -1,   111,    -1,   111,    45,    -1,    66,    -1,
      59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,
      65,    -1,    64,    -1,    69,    -1,    70,    -1,    58,    -1,
      38,    -1,    67,    -1,    67,    70,   115,    71,    -1,    68,
      -1,    83,   114,    84,    -1,   114,    64,    -1,    66,   114,
      -1,    59,   114,    -1,    60,   114,    -1,    61,   114,    -1,
      62,   114,    -1,    63,   114,    -1,    69,   115,    69,    -1,
      70,   115,    71,    -1,    66,    83,   115,    84,    -1,   114,
      59,   114,    -1,   114,    60,   114,    -1,   114,    61,   114,
      -1,   114,    62,   114,    -1,   114,    63,   114,    -1,   114,
      65,   114,    -1,   114,    -1,   114,    82,   115,    -1,   114,
      18,   114,    -1,    -1,    36,   103,    -1,   116,   117,    -1,
      47,    97,   116,   117,    -1,   118,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    72,    72,    73,    75,    83,    86,    90,    96,   107,
     108,   109,   111,   112,   113,   114,   115,   117,   118,   120,
     121,   129,   130,   131,   131,   134,   135,   136,   137,   138,
     139,   140,   143,   144,   145,   146,   147,   148,   149,   150,
     152,   154,   155,   156,   157,   159,   160,   162,   163,   165,
     170,   171,   173,   174,   175,   175,   181,   184,   186,   188,
     198,   199,   200,   201,   202,   204,   205,   206,   207,   208,
     209,   215,   216,   217,   218,   223,   224,   225,   226,   228,
     229,   231,   232,   234,   235,   237,   238,   240,   241,   243,
     244,   246,   247,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   263,   265,   266,   267,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     283,   285,   287,   289,   291,   294,   295,   297,   299,   300,
     302,   304,   307
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CST", "VAR", "SORT", "FUNC", "ALG", 
  "SPEC", "ADDSPEC", "REWR", "PRT", "GRAPH", "PFEIL", "TERM", "NUM", 
  "ATT", "IS", "EQ", "INFO", "LA1", "LA2", "LA3", "LA4", "LA5", "LOCAL", 
  "RU", "RA", "KOMMU", "LB", "IN", "NIN", "PARAM", "FOR", "TO", "STEP", 
  "DO", "DBG", "LAST", "BRA", "OTHER", "DATA", "OUT", "INC", "EXE", 
  "VARPAR", "SYS", "IF", "ELSE", "WHILE", "PRTNUM", "LIFT", "QUIT", 
  "RETURN", "Id", "String", "Sort", "Alg", "Term", "La1", "La2", "La3", 
  "La4", "La5", "Ru", "Ra", "Func", "Const", "Var", "Bra", "Bra1", "Bra2", 
  "Terms", "Form", "Sorts", "Functs", "Forms", "Algs", "Cond2", "Cond", 
  "'\\n'", "':'", "','", "'('", "')'", "';'", "'{'", "'}'", "$accept", 
  "prog", "line", "definition", "idlist", "att", "@1", "namedId", 
  "VORRANG", "condition", "condfunc", "instructions", "tinstructions", 
  "oinstructions", "d_list", "instruction", "@2", "aninstruction", "step", 
  "prntexpr", "prntlist", "alglist", "Alg2", "sortlist", "vsortlist", 
  "func", "term", "termlist", "formula", "vinstr", "cformula", "formlist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
      10,    58,    44,    40,    41,    59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    88,    89,    89,    90,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    92,
      92,    93,    93,    94,    93,    95,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    96,    96,    96,    96,    96,
      97,    98,    98,    98,    98,    99,    99,   100,   100,   101,
     102,   102,   103,   103,   104,   103,   103,   103,   103,   103,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   106,
     106,   107,   107,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   115,   115,   116,   117,   117,
     118,   118,   119
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     2,     8,     7,     9,     8,     4,
       2,     4,     4,     4,     4,     4,     2,     2,     4,     1,
       3,     0,     2,     0,     6,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     4,     3,     1,     3,     1,     3,     1,
       1,     3,     1,     1,     0,     4,     3,     3,     5,     9,
       0,     2,     2,     2,     4,     1,     2,     2,     2,     2,
       2,     3,     6,     3,     3,     8,     2,     2,     1,     0,
       2,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     4,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     0,     2,
       2,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    78,     0,
      82,   103,     0,     0,     0,     0,     0,     0,   105,   107,
       0,     0,     0,    54,    60,     2,    53,     0,    45,    52,
      83,    65,    81,    25,    29,    30,    31,    94,    95,    96,
      97,    98,   100,    99,    93,    26,    27,   101,   102,     0,
      19,    28,     0,    16,     0,    17,     0,     0,   103,   105,
       0,    67,     0,    10,     0,     0,    63,     0,    76,     0,
       0,    69,    70,    68,    62,     0,    61,     0,     0,     0,
       0,    60,    40,    60,    66,     0,    77,     0,   111,   112,
     113,   114,   115,     0,   110,     0,     0,   125,     0,     0,
       0,    60,     1,     3,     4,    60,     0,     0,     0,     0,
       0,     0,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    74,     0,     0,
       0,     0,    57,    56,     0,     0,    71,     0,     0,    73,
       0,     0,   116,   117,   108,    49,     0,    47,    46,    84,
     119,   120,   121,   122,   123,   124,    12,    20,     9,    89,
      91,     0,     0,    87,     0,    13,    85,     0,   128,   132,
      14,    15,     0,    64,    18,    11,     0,     0,     0,     0,
       0,     0,     0,    44,    60,     0,     0,   118,   106,   126,
      55,    60,     0,    92,     0,     0,     0,     0,     0,    60,
     130,     0,     0,     0,     0,    41,    42,    43,    58,     0,
       0,    48,    90,    32,   128,    88,    86,   127,   129,     0,
      79,     0,    21,     0,    72,    33,    34,    35,    36,    37,
      39,    38,    21,   131,     0,     0,     0,    21,     0,     6,
       0,     5,     0,    80,    60,     8,    23,    22,    75,     7,
      59,     0,    50,     0,     0,    60,    51,    24
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    44,    45,    46,    69,   259,   271,    70,   252,   101,
     102,    47,   166,   167,   273,    48,   121,    49,   256,    50,
      51,   216,   186,   180,   181,    71,    52,   118,   188,   220,
     189,   190
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -234
static const short yypact[] =
{
     302,   505,   505,   505,   505,   505,   -44,   -25,   389,   264,
     505,   522,   -35,   505,   389,   -20,  -234,    14,   534,    -9,
      16,    36,   534,    37,   -13,   -13,    39,    12,  -234,   389,
    -234,    79,   389,   389,   389,   389,   389,   407,   -15,  -234,
     389,   389,   389,  -234,   218,  -234,  -234,    19,    22,  -234,
      28,  -234,   315,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,    30,
      46,  -234,    38,  -234,    48,  -234,    54,    57,  -234,    63,
     472,  -234,    59,   -41,    64,    80,  -234,     2,  -234,    90,
      65,  -234,  -234,  -234,  -234,    93,  -234,    72,    73,    74,
     389,   302,  -234,   302,  -234,   389,   315,   129,   545,    88,
      40,    53,    17,   389,  -234,   389,   389,   465,    89,    97,
     179,   302,  -234,  -234,  -234,   302,   264,   389,   389,   389,
     389,   389,  -234,   389,   114,   505,   115,   116,   335,   353,
     -26,   117,   118,    94,   389,   104,   116,  -234,   389,   389,
     389,   230,   145,  -234,   110,   389,   315,   119,   120,   315,
     131,   389,  -234,  -234,  -234,  -234,   113,   125,  -234,  -234,
     545,    88,    40,    53,    17,    17,  -234,  -234,  -234,   124,
     164,   197,   -13,  -234,   371,  -234,   132,    25,   177,  -234,
    -234,  -234,   -26,  -234,  -234,  -234,   162,   -11,   116,   204,
     135,   136,   146,  -234,   302,   201,   479,  -234,  -234,  -234,
    -234,   302,   116,  -234,   175,   389,   161,   -26,   389,   302,
    -234,   165,   389,   233,   193,  -234,  -234,  -234,  -234,   167,
     -26,  -234,  -234,    52,   177,  -234,  -234,   315,  -234,   198,
     101,   210,   237,   389,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,   237,  -234,   190,   389,   238,   237,   440,  -234,
     191,  -234,   228,   315,   302,  -234,  -234,  -234,  -234,  -234,
    -234,   477,   211,   199,   477,   302,  -234,  -234
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -234,  -234,   253,  -215,    34,  -233,  -234,    -4,  -234,   -23,
    -234,  -110,    87,  -234,    26,   -89,  -234,  -234,  -234,  -234,
       1,  -134,  -234,    91,  -138,    20,    -7,   -36,    84,    81,
    -234,   181
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, parse error.  */
#define YYTABLE_NINF -30
static const short yytable[] =
{
      74,    80,   103,   115,   185,   119,   193,    87,   199,    86,
      81,   165,   152,    76,   153,   168,    97,    98,    99,   261,
     144,    85,   106,   222,   265,   108,   109,   110,   111,   112,
     114,   183,    77,   117,   117,   120,    72,    73,    90,    75,
     -29,   -29,    95,   218,    82,    84,    91,    88,   127,   128,
     129,   130,   131,   132,   133,   116,   272,   192,    92,   272,
     223,   127,   128,   129,   130,   131,   132,   133,    89,   154,
     100,    93,   245,   246,   247,   248,   249,   158,   250,   251,
     160,   132,   133,   236,   127,   128,   129,   130,   131,   132,
     133,    94,    96,   151,   104,   105,   244,   107,   117,   124,
     156,   165,   130,   131,   132,   133,   157,   125,   159,   117,
     126,   134,   200,   201,   202,   228,   131,   132,   133,   136,
     170,   171,   172,   173,   174,   209,   175,   169,   135,   137,
     238,   187,   187,   116,   143,   138,   255,   197,   139,   155,
     141,   117,   117,   117,   145,   142,   146,   147,   206,   129,
     130,   131,   132,   133,   117,   148,   149,   150,   162,   215,
     127,   128,   129,   130,   131,   132,   133,    16,   163,   177,
     176,   178,   179,   194,   195,   270,   196,   120,   127,   128,
     129,   130,   131,   132,   133,   198,   277,    78,    32,    33,
      34,    35,    36,   204,   205,    37,    79,    39,    40,    41,
     210,   161,   208,   164,   207,   211,   212,   260,   187,   213,
     214,   237,    42,   219,   217,   240,   221,   224,   122,   225,
     226,     1,     2,     3,     4,     5,     6,     7,     8,     9,
     227,   233,    10,    11,    12,   229,   117,    13,   127,   128,
     129,   130,   131,   132,   133,   235,   241,   239,   263,   242,
     243,    14,   254,   258,   267,    15,    16,    17,    18,    19,
      20,    21,    22,   164,    23,    24,   257,    25,    26,    27,
      28,    29,   262,    30,   264,   268,    31,    32,    33,    34,
      35,    36,   269,   275,    37,    38,    39,    40,    41,   127,
     128,   129,   130,   131,   132,   133,   274,   123,   231,   234,
     276,    42,    16,   232,    43,     1,     2,     3,     4,     5,
       6,     7,     8,     9,   203,   253,    10,    11,    12,    30,
     191,    13,    78,    32,    33,    34,    35,    36,     0,     0,
      37,    79,    39,    40,    41,    14,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    42,    23,    24,
       0,    25,    26,    27,    28,    29,     0,    30,     0,     0,
      31,    32,    33,    34,    35,    36,     0,     0,    37,    38,
      39,    40,    41,    16,   127,   128,   129,   130,   131,   132,
     133,     0,   182,     0,     0,    42,     0,     0,    43,     0,
       0,    16,   183,    78,    32,    33,    34,    35,    36,     0,
     182,    37,    79,    39,    40,    41,     0,     0,     0,    16,
       0,    78,    32,    33,    34,    35,    36,     0,   184,    37,
      79,    39,    40,    41,     0,     0,     0,    16,   183,    78,
      32,    33,    34,    35,    36,     0,    42,    37,    79,    39,
      40,    41,     0,     0,     0,    16,     0,    78,    32,    33,
      34,    35,    36,     0,   184,    37,    79,    39,    40,    41,
       0,     0,     0,     0,     0,    78,    32,    33,    34,    35,
      36,     0,    42,    37,    79,    39,    40,    41,     0,     0,
       1,     2,     3,     4,     5,     6,     7,     0,     0,     0,
     113,    10,    11,    12,    53,     0,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,     0,     0,     0,     0,     0,    17,    18,     0,     0,
       0,     0,     0,   266,   127,   128,   129,   130,   131,   132,
     133,   127,   128,   129,   130,   131,   132,   133,   127,   128,
     129,   130,   131,   132,   133,     0,     0,   161,     0,     0,
       0,     0,     0,   140,     0,     0,     0,     0,     0,    53,
     230,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    53,     0,    83,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    57,    58,    59,    60,    61,    62,    63,
      64,     0,     0,    67,    68,   128,   129,   130,   131,   132,
     133
};

static const short yycheck[] =
{
       4,     8,    25,    18,   138,    41,   140,    14,   146,    13,
       9,   121,   101,    57,   103,   125,    29,    30,    31,   252,
      18,    56,    29,    34,   257,    32,    33,    34,    35,    36,
      37,    57,    57,    40,    41,    42,     2,     3,    18,     5,
      81,    82,    22,    18,    10,    11,    55,    67,    59,    60,
      61,    62,    63,    64,    65,    70,   271,    83,    67,   274,
     198,    59,    60,    61,    62,    63,    64,    65,    54,   105,
      83,    55,    20,    21,    22,    23,    24,   113,    26,    27,
     116,    64,    65,   217,    59,    60,    61,    62,    63,    64,
      65,    55,    55,   100,    55,    83,   230,    18,   105,    80,
     107,   211,    62,    63,    64,    65,   113,    85,   115,   116,
      82,    81,   148,   149,   150,   204,    63,    64,    65,    81,
     127,   128,   129,   130,   131,   161,   133,   126,    82,    81,
     219,   138,   139,    70,    54,    81,    35,   144,    81,    10,
      81,   148,   149,   150,    54,    81,    81,    54,   155,    61,
      62,    63,    64,    65,   161,    83,    83,    83,    69,   182,
      59,    60,    61,    62,    63,    64,    65,    38,    71,   135,
      56,    56,    56,    56,    56,   264,    82,   184,    59,    60,
      61,    62,    63,    64,    65,    81,   275,    58,    59,    60,
      61,    62,    63,    48,    84,    66,    67,    68,    69,    70,
      87,    82,    71,    84,    84,    80,    82,   243,   215,    45,
      13,   218,    83,    36,    82,   222,    54,    13,     0,    84,
      84,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      84,    56,    14,    15,    16,    34,   243,    19,    59,    60,
      61,    62,    63,    64,    65,    84,    13,    82,   255,    56,
      83,    33,    54,    16,   258,    37,    38,    39,    40,    41,
      42,    43,    44,    84,    46,    47,    56,    49,    50,    51,
      52,    53,    82,    55,    36,    84,    58,    59,    60,    61,
      62,    63,    54,    84,    66,    67,    68,    69,    70,    59,
      60,    61,    62,    63,    64,    65,    85,    44,   211,   215,
     274,    83,    38,   212,    86,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    84,   234,    14,    15,    16,    55,
     139,    19,    58,    59,    60,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    33,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    83,    46,    47,
      -1,    49,    50,    51,    52,    53,    -1,    55,    -1,    -1,
      58,    59,    60,    61,    62,    63,    -1,    -1,    66,    67,
      68,    69,    70,    38,    59,    60,    61,    62,    63,    64,
      65,    -1,    47,    -1,    -1,    83,    -1,    -1,    86,    -1,
      -1,    38,    57,    58,    59,    60,    61,    62,    63,    -1,
      47,    66,    67,    68,    69,    70,    -1,    -1,    -1,    38,
      -1,    58,    59,    60,    61,    62,    63,    -1,    83,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    38,    57,    58,
      59,    60,    61,    62,    63,    -1,    83,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    38,    -1,    58,    59,    60,
      61,    62,    63,    -1,    83,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    -1,    83,    66,    67,    68,    69,    70,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,    -1,
      83,    14,    15,    16,    54,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    -1,    -1,    83,    59,    60,    61,    62,    63,    64,
      65,    59,    60,    61,    62,    63,    64,    65,    59,    60,
      61,    62,    63,    64,    65,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    -1,    54,
      81,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    54,    -1,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    69,    70,    60,    61,    62,    63,    64,
      65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      55,    58,    59,    60,    61,    62,    63,    66,    67,    68,
      69,    70,    83,    86,    89,    90,    91,    99,   103,   105,
     107,   108,   114,    54,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    92,
      95,   113,    92,    92,    95,    92,    57,    57,    58,    67,
     114,   108,    92,    56,    92,    56,    95,   114,    67,    54,
     113,    55,    67,    55,    55,   113,    55,    29,    30,    31,
      83,    97,    98,    97,    55,    83,   114,    18,   114,   114,
     114,   114,   114,    83,   114,    18,    70,   114,   115,   115,
     114,   104,     0,    90,    80,    85,    82,    59,    60,    61,
      62,    63,    64,    65,    81,    82,    81,    81,    81,    81,
      81,    81,    81,    54,    18,    54,    81,    54,    83,    83,
      83,   114,   103,   103,   115,    10,   114,   114,   115,   114,
     115,    82,    69,    71,    84,    99,   100,   101,    99,   108,
     114,   114,   114,   114,   114,   114,    56,    92,    56,    56,
     111,   112,    47,    57,    83,   109,   110,   114,   116,   118,
     119,   119,    83,   109,    56,    56,    82,   114,    81,   112,
     115,   115,   115,    84,    48,    84,   114,    84,    71,   115,
      87,    80,    82,    45,    13,    97,   109,    82,    18,    36,
     117,    54,    34,   112,    13,    84,    84,    84,   103,    34,
      81,   100,   111,    56,   116,    84,   109,   114,   103,    82,
     114,    13,    56,    83,   109,    20,    21,    22,    23,    24,
      26,    27,    96,   117,    54,    35,   106,    56,    16,    93,
     115,    93,    82,   114,    36,    93,    83,    95,    84,    54,
     103,    94,    91,   102,    85,    84,   102,   103
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)           \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#define YYLEX	yylex ()

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*-----------------------------.
| Print this symbol on YYOUT.  |
`-----------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yysymprint (FILE* yyout, int yytype, YYSTYPE yyvalue)
#else
yysymprint (yyout, yytype, yyvalue)
    FILE* yyout;
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyout, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyout, yytoknum[yytype], yyvalue);
# endif
    }
  else
    YYFPRINTF (yyout, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyout, ")");
}
#endif /* YYDEBUG. */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yydestruct (int yytype, YYSTYPE yyvalue)
#else
yydestruct (yytype, yyvalue)
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  switch (yytype)
    {
      default:
        break;
    }
}



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of parse errors so far.  */
int yynerrs;


int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with.  */

  if (yychar <= 0)		/* This means end of input.  */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more.  */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

      /* We have to keep this `#if YYDEBUG', since we use variables
	 which are defined only if `YYDEBUG' is set.  */
      YYDPRINTF ((stderr, "Next token is "));
      YYDSYMPRINT ((stderr, yychar1, yylval));
      YYDPRINTF ((stderr, "\n"));
    }

  /* If the proper action on seeing token YYCHAR1 is to reduce or to
     detect an error, take that action.  */
  yyn += yychar1;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yychar1)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];



#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn - 1, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] >= 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif
  switch (yyn)
    {
        case 4:
#line 75 "syn.y"
    {Node * temp;
														if (yyvsp[-1].y_nod) { temp = mknod(FUNC,(Node *) sequence,yyvsp[-1].y_nod);
															is_running();
															CALLFUNCT(temp);
															is_not_running();
															delete(temp);}
														}
    break;

  case 5:
#line 83 "syn.y"
    {	yyval.y_nod=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) yyvsp[-6].y_nod,yyvsp[-1].y_int,(Node *) yyvsp[-2].y_sym,yyvsp[-4].y_nod,FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) yyvsp[-6].y_nod,yyvsp[0].y_nod)),NULL)));}
    break;

  case 6:
#line 86 "syn.y"
    { yyval.y_nod=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) yyvsp[-5].y_nod,
                                              mknod(PARAM,yyvsp[-3].y_nod,
                                              mknod(PARAM,(Node *) yyvsp[-1].y_sym,yyvsp[0].y_nod))));}
    break;

  case 7:
#line 90 "syn.y"
    { yyval.y_nod=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) yyvsp[-7].y_sym,
                                              mknod(PARAM,(Node *) give_ufkt(name(yyvsp[-6].y_sym)),
                                              mknod(PARAM,(Node *) give_ufkt(name(yyvsp[-4].y_sym)),
                                              mknod(PARAM,(Node *) give_ufkt(name(yyvsp[-2].y_sym)),
                                              (Node *) give_ufkt(name(yyvsp[0].y_sym)))))));	}
    break;

  case 8:
#line 96 "syn.y"
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
																	}
    break;

  case 9:
#line 107 "syn.y"
    {yyval.y_nod=DECLARE(yyvsp[-2].y_nod,Var,(Node *) yyvsp[0].y_sym,NULL,FALSE);}
    break;

  case 10:
#line 108 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) set_numbertype,(Node *) (yyvsp[0].y_sym)); /* setzt numbertype fuer mknum */}
    break;

  case 11:
#line 109 "syn.y"
    { /* Variablen fuer Numerische Zahlen */
									                yyval.y_nod=DECLARE(yyvsp[-2].y_nod,Var,(Node *) yyvsp[0].y_sym,NULL,TRUE);}
    break;

  case 12:
#line 111 "syn.y"
    {yyval.y_nod=DECLARE(yyvsp[-2].y_nod,Const,(Node *) yyvsp[0].y_sym,NULL,FALSE);}
    break;

  case 13:
#line 112 "syn.y"
    {yyval.y_nod = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) yyvsp[-2].y_sym,(Node *) yyvsp[0].y_nod));}
    break;

  case 14:
#line 113 "syn.y"
    {yyval.y_nod = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) yyvsp[-2].y_sym,yyvsp[0].y_nod));	}
    break;

  case 15:
#line 114 "syn.y"
    {yyval.y_nod = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) yyvsp[-2].y_sym,yyvsp[0].y_nod));}
    break;

  case 16:
#line 115 "syn.y"
    {yyval.y_nod=DECLARE(yyvsp[0].y_nod,Sort,NULL,NULL,FALSE);}
    break;

  case 17:
#line 117 "syn.y"
    {yyval.y_nod=DECLARE(yyvsp[0].y_nod,Alg,NULL,NULL,FALSE);}
    break;

  case 18:
#line 118 "syn.y"
    {yyval.y_nod=DECLARE(yyvsp[-2].y_nod,Term,(Node *) yyvsp[0].y_sym,NULL,FALSE);}
    break;

  case 19:
#line 120 "syn.y"
    {yyval.y_nod = yyvsp[0].y_nod;}
    break;

  case 20:
#line 121 "syn.y"
    {yyval.y_nod = mknod(Id,yyvsp[-2].y_nod,yyvsp[0].y_nod);}
    break;

  case 21:
#line 129 "syn.y"
    { yyval.y_nod = NULL;}
    break;

  case 22:
#line 130 "syn.y"
    { yyval.y_nod = mknod(ATT,(Node *) give_ufkt(name((Symbol *) yyvsp[0].y_nod)),NULL);}
    break;

  case 23:
#line 131 "syn.y"
    {block_begin();no_protect();}
    break;

  case 24:
#line 132 "syn.y"
    {protect();block_end();yyval.y_nod =mknod(PARAM,yyvsp[-2].y_nod,yyvsp[0].y_nod);}
    break;

  case 25:
#line 134 "syn.y"
    { yyval.y_nod = (Node *) yyvsp[0].y_sym;}
    break;

  case 26:
#line 135 "syn.y"
    { yyval.y_nod = (Node *) yyvsp[0].y_sym;}
    break;

  case 27:
#line 136 "syn.y"
    { yyval.y_nod = (Node *) yyvsp[0].y_sym;}
    break;

  case 28:
#line 137 "syn.y"
    { yyval.y_nod = (Node *) yyvsp[0].y_nod;}
    break;

  case 29:
#line 138 "syn.y"
    { yyval.y_nod = (Node *) yyvsp[0].y_sym;}
    break;

  case 30:
#line 139 "syn.y"
    { yyval.y_nod = (Node *) yyvsp[0].y_sym;}
    break;

  case 31:
#line 140 "syn.y"
    { yyval.y_nod = (Node *) yyvsp[0].y_sym;}
    break;

  case 32:
#line 143 "syn.y"
    {yyval.y_int = Func;}
    break;

  case 33:
#line 144 "syn.y"
    {yyval.y_int = La1;	/* Linksassoziativ */}
    break;

  case 34:
#line 145 "syn.y"
    {yyval.y_int = La2;	/* Linksassoziativ */}
    break;

  case 35:
#line 146 "syn.y"
    {yyval.y_int = La3;	/* Linksassoziativ */}
    break;

  case 36:
#line 147 "syn.y"
    {yyval.y_int = La4;	/* Linksassoziativ */}
    break;

  case 37:
#line 148 "syn.y"
    {yyval.y_int = La5;	/* Linksassoziativ */}
    break;

  case 38:
#line 149 "syn.y"
    {yyval.y_int = Ra;  	/* Rechtsassoziativ */}
    break;

  case 39:
#line 150 "syn.y"
    {yyval.y_int = Ru;	  /* Rechts Unaer */}
    break;

  case 40:
#line 152 "syn.y"
    {yyval.y_nod = yyvsp[0].y_nod;}
    break;

  case 41:
#line 154 "syn.y"
    {yyval.y_nod = mknod(Cond,(Node *) lower_between,yyvsp[-1].y_nod);}
    break;

  case 42:
#line 155 "syn.y"
    {yyval.y_nod = mknod(Cond,(Node *) in_tree,yyvsp[-1].y_nod);}
    break;

  case 43:
#line 156 "syn.y"
    {yyval.y_nod = mknod(Cond,(Node *) not_in_tree,yyvsp[-1].y_nod);}
    break;

  case 44:
#line 157 "syn.y"
    {yyval.y_nod = mknod(Cond,(Node *) isnt_zero,yyvsp[-1].y_nod);}
    break;

  case 45:
#line 159 "syn.y"
    {if (yyvsp[0].y_nod) yyval.y_nod = mknod(PARAM,yyvsp[0].y_nod,NULL); else yyval.y_nod=NULL;}
    break;

  case 46:
#line 160 "syn.y"
    {if (yyvsp[-2].y_nod) yyval.y_nod = mknod(PARAM,yyvsp[-2].y_nod,yyvsp[0].y_nod);else yyval.y_nod=yyvsp[0].y_nod;}
    break;

  case 47:
#line 162 "syn.y"
    {if (yyvsp[0].y_nod) yyval.y_nod = mknod(PARAM,yyvsp[0].y_nod,NULL); else yyval.y_nod=NULL;}
    break;

  case 48:
#line 163 "syn.y"
    {if (yyvsp[-2].y_nod) yyval.y_nod = mknod(PARAM,yyvsp[-2].y_nod,yyvsp[0].y_nod);else yyval.y_nod=yyvsp[0].y_nod;}
    break;

  case 49:
#line 165 "syn.y"
    {if(yyvsp[0].y_nod) yyval.y_nod=mknod(FUNC,(Node *) sequence,yyvsp[0].y_nod); else yyval.y_nod=yyvsp[0].y_nod;}
    break;

  case 50:
#line 170 "syn.y"
    {yyval.y_nod = mknod(PARAM,in_block_def(yyvsp[0].y_nod),NULL);}
    break;

  case 51:
#line 171 "syn.y"
    {yyval.y_nod = mknod(PARAM,in_block_def(yyvsp[-2].y_nod),yyvsp[0].y_nod);}
    break;

  case 52:
#line 173 "syn.y"
    {yyval.y_nod = in_block_instruct(yyvsp[0].y_nod); /* Locale Variablen pruefen ! */ }
    break;

  case 53:
#line 174 "syn.y"
    {yyval.y_nod = in_block_def(yyvsp[0].y_nod);}
    break;

  case 54:
#line 175 "syn.y"
    {block_begin();no_protect();}
    break;

  case 55:
#line 176 "syn.y"
    {protect();block_end();
																yyval.y_nod=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,yyvsp[-1].y_nod),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
    break;

  case 56:
#line 181 "syn.y"
    {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,yyvsp[-1].y_nod,NULL /* wird dann $3 */)));
																		merk->r->r = yyvsp[0].y_nod;yyval.y_nod=rtw;}
    break;

  case 57:
#line 184 "syn.y"
    {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,yyvsp[-1].y_nod,mknod(PARAM,NULL,NULL))));
																		merk->r->r->l = yyvsp[0].y_nod;yyval.y_nod=rtw;}
    break;

  case 58:
#line 186 "syn.y"
    {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,yyvsp[-3].y_nod,mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		merk->r->r->l = yyvsp[-2].y_nod;merk->r->r->r = yyvsp[0].y_nod;yyval.y_nod=rtw;}
    break;

  case 59:
#line 189 "syn.y"
    {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) forschleife,
																mknod(PARAM,
																	mknod(PARAM,yyvsp[-5].y_nod,yyvsp[-3].y_nod),
																	mknod(PARAM,
																		mknod(PARAM,yyvsp[-2].y_nod,(Node *) (yyvsp[-7].y_nod)),
																		NULL /* $9 */) )));	
														merk->r->r->r = yyvsp[0].y_nod;yyval.y_nod=rtw;}
    break;

  case 60:
#line 198 "syn.y"
    {yyval.y_nod=NULL;}
    break;

  case 61:
#line 199 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) system_fkt,(Node *) (yyvsp[0].y_sym));}
    break;

  case 62:
#line 200 "syn.y"
    {/* include(name($2));$$=NULL;*/ yyval.y_nod=mknod(FUNC,(Node *) include_fkt,(Node *) (yyvsp[0].y_sym)); }
    break;

  case 63:
#line 201 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) info_fkt,(Node *) (yyvsp[0].y_nod)); }
    break;

  case 64:
#line 202 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod)));
														 rtypes(lastterm)=get_type(yyvsp[-2].y_nod);}
    break;

  case 65:
#line 204 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,yyvsp[0].y_nod));}
    break;

  case 66:
#line 205 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) prt_num,(Node *) (yyvsp[0].y_sym));}
    break;

  case 67:
#line 206 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) sequence,yyvsp[0].y_nod); /* ohne \n */ }
    break;

  case 68:
#line 207 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) changeout,(Node *) (yyvsp[0].y_sym));}
    break;

  case 69:
#line 208 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) changedata,(Node *) (yyvsp[0].y_sym));}
    break;

  case 70:
#line 209 "syn.y"
    {if (rtypes(yyvsp[0].y_sym) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               yyval.y_nod=NULL;}
                             else
                               yyval.y_nod=mknod(FUNC,(Node *) readdata,(Node *) (yyvsp[0].y_sym));
                            }
    break;

  case 71:
#line 215 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),yyvsp[0].y_nod));}
    break;

  case 72:
#line 216 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) yyvsp[-5].y_sym,mknod(PARAM,(Node *) yyvsp[-2].y_nod,(Node *) yyvsp[0].y_nod)));}
    break;

  case 73:
#line 217 "syn.y"
    { yyval.y_nod=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
    break;

  case 74:
#line 218 "syn.y"
    {yyval.y_nod = NULL;
																exe_always(yyvsp[-1].y_nod)=TRUE;
																hasval(yyvsp[-1].y_nod) = TRUE;
																value(yyvsp[-1].y_nod)  = (Node *) give_ufkt(name(yyvsp[0].y_sym));
 													}
    break;

  case 75:
#line 223 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) yyvsp[-1].y_nod,(Node *) yyvsp[-5].y_nod));}
    break;

  case 76:
#line 224 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) setdebug,(Node *) (yyvsp[0].y_sym));}
    break;

  case 77:
#line 225 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) return_fkt,yyvsp[0].y_nod);}
    break;

  case 78:
#line 226 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) quit_fkt,NULL);}
    break;

  case 79:
#line 228 "syn.y"
    {yyval.y_nod=(Node *) NULL;}
    break;

  case 80:
#line 229 "syn.y"
    {yyval.y_nod=yyvsp[0].y_nod;}
    break;

  case 81:
#line 231 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) printterm,yyvsp[0].y_nod); rtypes(lastterm)=get_type(yyvsp[0].y_nod);}
    break;

  case 82:
#line 232 "syn.y"
    {yyval.y_nod=mknod(FUNC,(Node *) printstring,(Node *) (yyvsp[0].y_sym));}
    break;

  case 83:
#line 234 "syn.y"
    {yyval.y_nod=mknod(PARAM,yyvsp[0].y_nod,NULL);}
    break;

  case 84:
#line 235 "syn.y"
    {yyval.y_nod=mknod(PARAM,yyvsp[-2].y_nod,yyvsp[0].y_nod);}
    break;

  case 85:
#line 237 "syn.y"
    {yyval.y_nod = mknod(Algs,(yyvsp[0].y_nod),NULL);}
    break;

  case 86:
#line 238 "syn.y"
    {yyval.y_nod = mknod(Algs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
    break;

  case 87:
#line 240 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 88:
#line 241 "syn.y"
    {yyval.y_nod = mknod(Alg,(yyvsp[-1].y_nod),NULL);}
    break;

  case 89:
#line 243 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 90:
#line 244 "syn.y"
    {yyval.y_nod = mknod(Sorts,(Node *) (yyvsp[-2].y_sym),yyvsp[0].y_nod);}
    break;

  case 91:
#line 246 "syn.y"
    {yyval.y_nod = yyvsp[0].y_nod;}
    break;

  case 92:
#line 247 "syn.y"
    {yyval.y_nod = mknod(VARPAR,(Node *) (yyvsp[-1].y_nod),NULL);}
    break;

  case 93:
#line 249 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 94:
#line 250 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 95:
#line 251 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 96:
#line 252 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 97:
#line 253 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 98:
#line 254 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 99:
#line 255 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 100:
#line 256 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 101:
#line 257 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 102:
#line 258 "syn.y"
    {yyval.y_nod = (Node *) (yyvsp[0].y_sym);}
    break;

  case 103:
#line 263 "syn.y"
    {	yyval.y_nod = (Node *) yyvsp[0].y_sym; /* tcopy(); merkt sich keine Abhaengigkeiten und funktioniert nicht in Bloecken */ 
														}
    break;

  case 104:
#line 265 "syn.y"
    {yyval.y_nod = (Node *) lastterm;}
    break;

  case 105:
#line 266 "syn.y"
    {yyval.y_nod = mknod(Const,(Node *) (yyvsp[0].y_sym),NULL);}
    break;

  case 106:
#line 267 "syn.y"
    {nphilf=mknod(Terms,mknod(Const,(Node *) (yyvsp[-3].y_sym),NULL),yyvsp[-1].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-2].y_sym),nphilf), nphilf);}
    break;

  case 107:
#line 269 "syn.y"
    {yyval.y_nod = (Node *) yyvsp[0].y_sym;}
    break;

  case 108:
#line 270 "syn.y"
    {yyval.y_nod = yyvsp[-1].y_nod;}
    break;

  case 109:
#line 271 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[0].y_sym),(yyvsp[-1].y_nod)), (yyvsp[-1].y_nod) ); }
    break;

  case 110:
#line 272 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); }
    break;

  case 111:
#line 273 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); }
    break;

  case 112:
#line 274 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); }
    break;

  case 113:
#line 275 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); }
    break;

  case 114:
#line 276 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); }
    break;

  case 115:
#line 277 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),(yyvsp[0].y_nod)), (yyvsp[0].y_nod) ); }
    break;

  case 116:
#line 278 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-2].y_sym),(yyvsp[-1].y_nod)), (yyvsp[-1].y_nod) ); }
    break;

  case 117:
#line 279 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-2].y_sym),(yyvsp[-1].y_nod)), (yyvsp[-1].y_nod) ); }
    break;

  case 118:
#line 280 "syn.y"
    {yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-3].y_sym),(yyvsp[-1].y_nod)),(yyvsp[-1].y_nod));}
    break;

  case 119:
#line 281 "syn.y"
    {nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);}
    break;

  case 120:
#line 283 "syn.y"
    {nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);}
    break;

  case 121:
#line 285 "syn.y"
    {nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);}
    break;

  case 122:
#line 287 "syn.y"
    {nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);}
    break;

  case 123:
#line 289 "syn.y"
    {nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);}
    break;

  case 124:
#line 291 "syn.y"
    {nphilf=mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);
														 yyval.y_nod = mknod(Func,(Node *) getsymbol((yyvsp[-1].y_sym),nphilf),nphilf);}
    break;

  case 125:
#line 294 "syn.y"
    {yyval.y_nod = yyvsp[0].y_nod;}
    break;

  case 126:
#line 295 "syn.y"
    {yyval.y_nod = mknod(Terms,yyvsp[-2].y_nod,yyvsp[0].y_nod);}
    break;

  case 127:
#line 297 "syn.y"
    {yyval.y_nod = mknod(Form,yyvsp[-2].y_nod,yyvsp[0].y_nod);}
    break;

  case 128:
#line 299 "syn.y"
    {yyval.y_nod = NULL;}
    break;

  case 129:
#line 300 "syn.y"
    {yyval.y_nod = yyvsp[0].y_nod;}
    break;

  case 130:
#line 302 "syn.y"
    {((yyvsp[-1].y_nod)->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),(yyvsp[-1].y_nod)->r),
																									 yyvsp[0].y_nod);yyval.y_nod = yyvsp[-1].y_nod;}
    break;

  case 131:
#line 304 "syn.y"
    {((yyvsp[-1].y_nod)->r)=mknod(PARAM,mknod(Cond2,yyvsp[-2].y_nod,(yyvsp[-1].y_nod)->r),
																									 yyvsp[0].y_nod);yyval.y_nod = yyvsp[-1].y_nod;}
    break;

  case 132:
#line 307 "syn.y"
    {yyval.y_nod = mknod(Forms,yyvsp[0].y_nod,NULL); /* NULL dient zum Einhaengen weiterer Formeln !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. wegen SPEC real : A+B=C;a=3 */
															}
    break;


    }

/* Line 1016 of /usr/share/bison/yacc.c.  */
#line 2138 "syn.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyssp > yyss)
	    {
	      YYDPRINTF ((stderr, "Error: popping "));
	      YYDSYMPRINT ((stderr,
			    yystos[*yyssp],
			    *yyvsp));
	      YYDPRINTF ((stderr, "\n"));
	      yydestruct (yystos[*yyssp], *yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yydestruct (yychar1, yylval);
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDPRINTF ((stderr, "Error: popping "));
      YYDSYMPRINT ((stderr,
		    yystos[*yyssp], *yyvsp));
      YYDPRINTF ((stderr, "\n"));

      yydestruct (yystos[yystate], *yyvsp);
      yyvsp--;
      yystate = *--yyssp;


#if YYDEBUG
      if (yydebug)
	{
	  short *yyssp1 = yyss - 1;
	  YYFPRINTF (stderr, "Error: state stack now");
	  while (yyssp1 != yyssp)
	    YYFPRINTF (stderr, " %d", *++yyssp1);
	  YYFPRINTF (stderr, "\n");
	}
#endif
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 311 "syn.y"


