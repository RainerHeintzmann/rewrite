/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 9 "syn.y" /* yacc.c:339  */


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


#line 105 "syn.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syn.tab.h".  */
#ifndef YY_YY_SYN_TAB_H_INCLUDED
# define YY_YY_SYN_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 48 "syn.y" /* yacc.c:355  */

	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	

#line 233 "syn.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYN_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 250 "syn.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  122
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   610

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  278

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   334

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    78,    78,    79,    81,    89,    92,    96,   102,   113,
     114,   115,   117,   118,   119,   120,   121,   123,   124,   126,
     127,   135,   136,   137,   137,   140,   141,   142,   143,   144,
     145,   146,   149,   150,   151,   152,   153,   154,   155,   156,
     158,   160,   161,   162,   163,   165,   166,   168,   169,   171,
     176,   177,   179,   180,   181,   181,   187,   190,   192,   194,
     204,   205,   206,   207,   208,   210,   211,   212,   213,   214,
     215,   221,   222,   223,   224,   229,   230,   231,   232,   234,
     235,   237,   238,   240,   241,   243,   244,   246,   247,   249,
     250,   252,   253,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   269,   271,   272,   273,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     289,   291,   293,   295,   297,   300,   301,   303,   305,   306,
     308,   310,   313
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CST", "VAR", "SORT", "FUNC", "ALG",
  "SPEC", "ADDSPEC", "REWR", "PRT", "GRAPH", "PFEIL", "TERM", "NUM", "ATT",
  "IS", "EQ", "INFO", "LA1", "LA2", "LA3", "LA4", "LA5", "LOCAL", "RU",
  "RA", "KOMMU", "LB", "IN", "NIN", "PARAM", "FOR", "TO", "STEP", "DO",
  "DBG", "LAST", "BRA", "OTHER", "DATA", "OUT", "INC", "EXE", "VARPAR",
  "SYS", "IF", "ELSE", "WHILE", "PRTNUM", "LIFT", "QUIT", "RETURN", "Id",
  "String", "Sort", "Alg", "Term", "La1", "La2", "La3", "La4", "La5", "Ru",
  "Ra", "Func", "Const", "Var", "Bra", "Bra1", "Bra2", "Terms", "Form",
  "Sorts", "Functs", "Forms", "Algs", "Cond2", "Cond", "'\\n'", "':'",
  "','", "'('", "')'", "';'", "'{'", "'}'", "$accept", "prog", "line",
  "definition", "idlist", "att", "$@1", "namedId", "VORRANG", "condition",
  "condfunc", "instructions", "tinstructions", "oinstructions", "d_list",
  "instruction", "$@2", "aninstruction", "step", "prntexpr", "prntlist",
  "alglist", "Alg2", "sortlist", "vsortlist", "func", "term", "termlist",
  "formula", "vinstr", "cformula", "formlist", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
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

#define YYPACT_NINF -234

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-234)))

#define YYTABLE_NINF -30

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
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

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
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

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -234,  -234,   253,  -215,    34,  -233,  -234,    -4,  -234,   -23,
    -234,  -110,    87,  -234,    26,   -89,  -234,  -234,  -234,  -234,
       1,  -134,  -234,    91,  -138,    20,    -7,   -36,    84,    81,
    -234,   181
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    44,    45,    46,    69,   259,   271,    70,   252,   101,
     102,    47,   166,   167,   273,    48,   121,    49,   256,    50,
      51,   216,   186,   180,   181,    71,    52,   118,   188,   220,
     189,   190
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
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

static const yytype_int16 yycheck[] =
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
static const yytype_uint8 yystos[] =
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

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 81 "syn.y" /* yacc.c:1646  */
    {Node * temp;
														if ((yyvsp[-1].y_nod)) { temp = mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod));
															is_running();
															CALLFUNCT(temp);
															is_not_running();
															delete(temp);}
														}
#line 1598 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "syn.y" /* yacc.c:1646  */
    {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1606 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 92 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod)=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1615 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 96 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufkt(name((yyvsp[0].y_sym))))))));	}
#line 1626 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 102 "syn.y" /* yacc.c:1646  */
    {Node * fkts;  /* Klammern */
							            				if (((yyvsp[-6].y_sym))==((yyvsp[-5].y_sym)))
							            					fkts=mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_sym),Bra,(Node *) (yyvsp[-1].y_sym),(yyvsp[-3].y_nod),FALSE),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) (yyvsp[-6].y_sym),(yyvsp[0].y_nod))),NULL));
											            else
								             				fkts=mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_sym),Bra1,(Node *) (yyvsp[-1].y_sym),(yyvsp[-3].y_nod),FALSE),
                                       mknod(PARAM,DECLARE((Node *) (yyvsp[-5].y_sym),Bra2,(Node *) (yyvsp[-1].y_sym),(yyvsp[-3].y_nod),FALSE),
                                       mknod(PARAM, mknod(FUNC,(Node *) set_brackets,mknod(PARAM,(Node *) (yyvsp[-6].y_sym),(Node *) (yyvsp[-5].y_sym))),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) (yyvsp[-6].y_sym),(yyvsp[0].y_nod))),NULL))));
																	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,fkts);
																	}
#line 1642 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 113 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1648 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 114 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* setzt numbertype fuer mknum */}
#line 1654 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 115 "syn.y" /* yacc.c:1646  */
    { /* Variablen fuer Numerische Zahlen */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1661 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 117 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1667 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 118 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1673 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 119 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1679 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 120 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1685 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 121 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1691 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 123 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1697 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 124 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1703 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 126 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1709 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 127 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1715 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 135 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = NULL;}
#line 1721 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 136 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = mknod(ATT,(Node *) give_ufkt(name((Symbol *) (yyvsp[0].y_nod))),NULL);}
#line 1727 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 137 "syn.y" /* yacc.c:1646  */
    {block_begin();no_protect();}
#line 1733 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 138 "syn.y" /* yacc.c:1646  */
    {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1739 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 140 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1745 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 141 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1751 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 142 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1757 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 143 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1763 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 144 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1769 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 145 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1775 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 146 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1781 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 149 "syn.y" /* yacc.c:1646  */
    {(yyval.y_int) = Func;}
#line 1787 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 150 "syn.y" /* yacc.c:1646  */
    {(yyval.y_int) = La1;	/* Linksassoziativ */}
#line 1793 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 151 "syn.y" /* yacc.c:1646  */
    {(yyval.y_int) = La2;	/* Linksassoziativ */}
#line 1799 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 152 "syn.y" /* yacc.c:1646  */
    {(yyval.y_int) = La3;	/* Linksassoziativ */}
#line 1805 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 153 "syn.y" /* yacc.c:1646  */
    {(yyval.y_int) = La4;	/* Linksassoziativ */}
#line 1811 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 154 "syn.y" /* yacc.c:1646  */
    {(yyval.y_int) = La5;	/* Linksassoziativ */}
#line 1817 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 155 "syn.y" /* yacc.c:1646  */
    {(yyval.y_int) = Ra;  	/* Rechtsassoziativ */}
#line 1823 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 156 "syn.y" /* yacc.c:1646  */
    {(yyval.y_int) = Ru;	  /* Rechts Unaer */}
#line 1829 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 158 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1835 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 160 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1841 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 161 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1847 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 162 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1853 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 163 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1859 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 165 "syn.y" /* yacc.c:1646  */
    {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1865 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 166 "syn.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1871 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 168 "syn.y" /* yacc.c:1646  */
    {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1877 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 169 "syn.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1883 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 171 "syn.y" /* yacc.c:1646  */
    {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1889 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 176 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1895 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 177 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1901 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 179 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Locale Variablen pruefen ! */ }
#line 1907 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 180 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1913 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 181 "syn.y" /* yacc.c:1646  */
    {block_begin();no_protect();}
#line 1919 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 182 "syn.y" /* yacc.c:1646  */
    {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 1929 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 187 "syn.y" /* yacc.c:1646  */
    {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* wird dann $3 */)));
																		merk->r->r = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1936 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 190 "syn.y" /* yacc.c:1646  */
    {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		merk->r->r->l = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1943 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 192 "syn.y" /* yacc.c:1646  */
    {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		merk->r->r->l = (yyvsp[-2].y_nod);merk->r->r->r = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1950 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 195 "syn.y" /* yacc.c:1646  */
    {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) forschleife,
																mknod(PARAM,
																	mknod(PARAM,(yyvsp[-5].y_nod),(yyvsp[-3].y_nod)),
																	mknod(PARAM,
																		mknod(PARAM,(yyvsp[-2].y_nod),(Node *) ((yyvsp[-7].y_nod))),
																		NULL /* $9 */) )));	
														merk->r->r->r = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1962 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 204 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=NULL;}
#line 1968 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 205 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) system_fkt,(Node *) ((yyvsp[0].y_sym)));}
#line 1974 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 206 "syn.y" /* yacc.c:1646  */
    {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fkt,(Node *) ((yyvsp[0].y_sym))); }
#line 1980 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 207 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) info_fkt,(Node *) ((yyvsp[0].y_nod))); }
#line 1986 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 208 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 1993 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 210 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 1999 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 211 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 2005 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 212 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* ohne \n */ }
#line 2011 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 213 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 2017 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 214 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 2023 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 215 "syn.y" /* yacc.c:1646  */
    {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 2034 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 221 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 2040 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 222 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 2046 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 223 "syn.y" /* yacc.c:1646  */
    { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 2052 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 224 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufkt(name((yyvsp[0].y_sym)));
 													}
#line 2062 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 229 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 2068 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 230 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 2074 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 231 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) return_fkt,(yyvsp[0].y_nod));}
#line 2080 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 232 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fkt,NULL);}
#line 2086 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 234 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=(Node *) NULL;}
#line 2092 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 235 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2098 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 237 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2104 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 238 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2110 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 240 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2116 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 241 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2122 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 243 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2128 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 244 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2134 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 246 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2140 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 247 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2146 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 249 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2152 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 250 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2158 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 252 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2164 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 253 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2170 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 255 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2176 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 256 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2182 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 257 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2188 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 258 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2194 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 259 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2200 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 260 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2206 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 261 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2212 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 262 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2218 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 263 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2224 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 264 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2230 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 269 "syn.y" /* yacc.c:1646  */
    {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); merkt sich keine Abhaengigkeiten und funktioniert nicht in Bloecken */ 
														}
#line 2237 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 271 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) lastterm;}
#line 2243 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 272 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2249 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 273 "syn.y" /* yacc.c:1646  */
    {nphilf=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),nphilf), nphilf);}
#line 2256 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 275 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2262 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 276 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2268 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 277 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2274 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 278 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2280 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 279 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2286 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 280 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2292 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 281 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2298 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 282 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2304 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 283 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2310 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 284 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2316 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 285 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2322 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 286 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2328 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 287 "syn.y" /* yacc.c:1646  */
    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2335 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 289 "syn.y" /* yacc.c:1646  */
    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2342 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 291 "syn.y" /* yacc.c:1646  */
    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2349 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 293 "syn.y" /* yacc.c:1646  */
    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2356 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 295 "syn.y" /* yacc.c:1646  */
    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2363 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 297 "syn.y" /* yacc.c:1646  */
    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2370 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 300 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2376 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 301 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2382 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 303 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2388 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 305 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = NULL;}
#line 2394 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 306 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2400 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 308 "syn.y" /* yacc.c:1646  */
    {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2407 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 310 "syn.y" /* yacc.c:1646  */
    {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2414 "syn.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 313 "syn.y" /* yacc.c:1646  */
    {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL dient zum Einhaengen weiterer Formeln !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. wegen SPEC real : A+B=C;a=3 */
															}
#line 2422 "syn.tab.c" /* yacc.c:1646  */
    break;


#line 2426 "syn.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 317 "syn.y" /* yacc.c:1906  */

