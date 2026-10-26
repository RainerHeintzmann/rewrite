/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 9 "syn.y"


#include <string.h> /* for memcpy,strcmp */
#include <stdlib.h>

#include "inout.h"
#include "run.h"
#include "sym.h" 
#include "sync.h"
#include "defs.h"
#include "userfn.h"
#include "nodes.h"
#include "expand.h"
#include "symfn.h"
#include "numsort.h"

#ifdef BISON
#include "unix.h"
#endif

extern int  yylex   (void);
extern void yyerror (const char *);

extern Symbol * lastterm;  /* sync.c */

Node * np_aux;

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

static Node * sym_att (Node * id, int hold);	/* below */


#line 116 "syn.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syn.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SYM = 3,                        /* SYM  */
  YYSYMBOL_PAT = 4,                        /* PAT  */
  YYSYMBOL_SORT = 5,                       /* SORT  */
  YYSYMBOL_FUNC = 6,                       /* FUNC  */
  YYSYMBOL_ALG = 7,                        /* ALG  */
  YYSYMBOL_SPEC = 8,                       /* SPEC  */
  YYSYMBOL_ADDSPEC = 9,                    /* ADDSPEC  */
  YYSYMBOL_REWR = 10,                      /* REWR  */
  YYSYMBOL_PRT = 11,                       /* PRT  */
  YYSYMBOL_GRAPH = 12,                     /* GRAPH  */
  YYSYMBOL_PFEIL = 13,                     /* PFEIL  */
  YYSYMBOL_TERM = 14,                      /* TERM  */
  YYSYMBOL_NUMPAT = 15,                    /* NUMPAT  */
  YYSYMBOL_ATT = 16,                       /* ATT  */
  YYSYMBOL_IS = 17,                        /* IS  */
  YYSYMBOL_EQ = 18,                        /* EQ  */
  YYSYMBOL_INFO = 19,                      /* INFO  */
  YYSYMBOL_LA1 = 20,                       /* LA1  */
  YYSYMBOL_LA2 = 21,                       /* LA2  */
  YYSYMBOL_LA3 = 22,                       /* LA3  */
  YYSYMBOL_LA4 = 23,                       /* LA4  */
  YYSYMBOL_LA5 = 24,                       /* LA5  */
  YYSYMBOL_LOCAL = 25,                     /* LOCAL  */
  YYSYMBOL_RU = 26,                        /* RU  */
  YYSYMBOL_RA = 27,                        /* RA  */
  YYSYMBOL_COMMU = 28,                     /* COMMU  */
  YYSYMBOL_LB = 29,                        /* LB  */
  YYSYMBOL_IN = 30,                        /* IN  */
  YYSYMBOL_NIN = 31,                       /* NIN  */
  YYSYMBOL_PARAM = 32,                     /* PARAM  */
  YYSYMBOL_FOR = 33,                       /* FOR  */
  YYSYMBOL_TO = 34,                        /* TO  */
  YYSYMBOL_STEP = 35,                      /* STEP  */
  YYSYMBOL_DO = 36,                        /* DO  */
  YYSYMBOL_DBG = 37,                       /* DBG  */
  YYSYMBOL_LAST = 38,                      /* LAST  */
  YYSYMBOL_BRA = 39,                       /* BRA  */
  YYSYMBOL_OTHER = 40,                     /* OTHER  */
  YYSYMBOL_DATA = 41,                      /* DATA  */
  YYSYMBOL_OUT = 42,                       /* OUT  */
  YYSYMBOL_INC = 43,                       /* INC  */
  YYSYMBOL_EXE = 44,                       /* EXE  */
  YYSYMBOL_VARPAR = 45,                    /* VARPAR  */
  YYSYMBOL_SYS = 46,                       /* SYS  */
  YYSYMBOL_IF = 47,                        /* IF  */
  YYSYMBOL_ELSE = 48,                      /* ELSE  */
  YYSYMBOL_WHILE = 49,                     /* WHILE  */
  YYSYMBOL_PRTNUM = 50,                    /* PRTNUM  */
  YYSYMBOL_LIFT = 51,                      /* LIFT  */
  YYSYMBOL_QUIT = 52,                      /* QUIT  */
  YYSYMBOL_RETURN = 53,                    /* RETURN  */
  YYSYMBOL_OPT = 54,                       /* OPT  */
  YYSYMBOL_COMM = 55,                      /* COMM  */
  YYSYMBOL_DEFAULT = 56,                   /* DEFAULT  */
  YYSYMBOL_RIGHT = 57,                     /* RIGHT  */
  YYSYMBOL_SUBSORT = 58,                   /* SUBSORT  */
  YYSYMBOL_INTNUM = 59,                    /* INTNUM  */
  YYSYMBOL_STEPS = 60,                     /* STEPS  */
  YYSYMBOL_SYMBOLIC = 61,                  /* SYMBOLIC  */
  YYSYMBOL_HOLD = 62,                      /* HOLD  */
  YYSYMBOL_RULES = 63,                     /* RULES  */
  YYSYMBOL_SHOW = 64,                      /* SHOW  */
  YYSYMBOL_REALNUM = 65,                   /* REALNUM  */
  YYSYMBOL_TYPEOF = 66,                    /* TYPEOF  */
  YYSYMBOL_Id = 67,                        /* Id  */
  YYSYMBOL_String = 68,                    /* String  */
  YYSYMBOL_Sort = 69,                      /* Sort  */
  YYSYMBOL_Alg = 70,                       /* Alg  */
  YYSYMBOL_Term = 71,                      /* Term  */
  YYSYMBOL_La1 = 72,                       /* La1  */
  YYSYMBOL_La2 = 73,                       /* La2  */
  YYSYMBOL_La3 = 74,                       /* La3  */
  YYSYMBOL_La4 = 75,                       /* La4  */
  YYSYMBOL_La5 = 76,                       /* La5  */
  YYSYMBOL_Ru = 77,                        /* Ru  */
  YYSYMBOL_Ra = 78,                        /* Ra  */
  YYSYMBOL_Func = 79,                      /* Func  */
  YYSYMBOL_Const = 80,                     /* Const  */
  YYSYMBOL_Var = 81,                       /* Var  */
  YYSYMBOL_Bra = 82,                       /* Bra  */
  YYSYMBOL_Bra1 = 83,                      /* Bra1  */
  YYSYMBOL_Bra2 = 84,                      /* Bra2  */
  YYSYMBOL_Terms = 85,                     /* Terms  */
  YYSYMBOL_Form = 86,                      /* Form  */
  YYSYMBOL_Sorts = 87,                     /* Sorts  */
  YYSYMBOL_Functs = 88,                    /* Functs  */
  YYSYMBOL_Forms = 89,                     /* Forms  */
  YYSYMBOL_Algs = 90,                      /* Algs  */
  YYSYMBOL_Cond2 = 91,                     /* Cond2  */
  YYSYMBOL_Cond = 92,                      /* Cond  */
  YYSYMBOL_93_n_ = 93,                     /* '\n'  */
  YYSYMBOL_94_ = 94,                       /* ':'  */
  YYSYMBOL_95_ = 95,                       /* ','  */
  YYSYMBOL_96_ = 96,                       /* '('  */
  YYSYMBOL_97_ = 97,                       /* ')'  */
  YYSYMBOL_98_ = 98,                       /* ';'  */
  YYSYMBOL_99_ = 99,                       /* '{'  */
  YYSYMBOL_100_ = 100,                     /* '}'  */
  YYSYMBOL_YYACCEPT = 101,                 /* $accept  */
  YYSYMBOL_prog = 102,                     /* prog  */
  YYSYMBOL_line = 103,                     /* line  */
  YYSYMBOL_definition = 104,               /* definition  */
  YYSYMBOL_idlist = 105,                   /* idlist  */
  YYSYMBOL_att = 106,                      /* att  */
  YYSYMBOL_107_1 = 107,                    /* $@1  */
  YYSYMBOL_namedId = 108,                  /* namedId  */
  YYSYMBOL_PRECEDENCE = 109,               /* PRECEDENCE  */
  YYSYMBOL_condition = 110,                /* condition  */
  YYSYMBOL_condfunc = 111,                 /* condfunc  */
  YYSYMBOL_instructions = 112,             /* instructions  */
  YYSYMBOL_tinstructions = 113,            /* tinstructions  */
  YYSYMBOL_oinstructions = 114,            /* oinstructions  */
  YYSYMBOL_d_list = 115,                   /* d_list  */
  YYSYMBOL_instruction = 116,              /* instruction  */
  YYSYMBOL_117_2 = 117,                    /* $@2  */
  YYSYMBOL_aninstruction = 118,            /* aninstruction  */
  YYSYMBOL_step = 119,                     /* step  */
  YYSYMBOL_prntexpr = 120,                 /* prntexpr  */
  YYSYMBOL_prntlist = 121,                 /* prntlist  */
  YYSYMBOL_alglist = 122,                  /* alglist  */
  YYSYMBOL_Alg2 = 123,                     /* Alg2  */
  YYSYMBOL_sortlist = 124,                 /* sortlist  */
  YYSYMBOL_vsortlist = 125,                /* vsortlist  */
  YYSYMBOL_func = 126,                     /* func  */
  YYSYMBOL_funclist = 127,                 /* funclist  */
  YYSYMBOL_term = 128,                     /* term  */
  YYSYMBOL_termlist = 129,                 /* termlist  */
  YYSYMBOL_formula = 130,                  /* formula  */
  YYSYMBOL_vinstr = 131,                   /* vinstr  */
  YYSYMBOL_cformula = 132,                 /* cformula  */
  YYSYMBOL_formlist = 133                  /* formlist  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  152
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   715

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  101
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  334

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   347


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      93,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      96,    97,     2,     2,    95,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    94,    98,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    99,     2,   100,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    85,    85,    86,    88,    96,    99,   103,   109,   120,
     121,   122,   124,   126,   128,   130,   132,   134,   135,   136,
     137,   138,   139,   140,   142,   143,   145,   146,   154,   155,
     166,   168,   170,   172,   172,   175,   176,   177,   178,   179,
     180,   181,   184,   185,   186,   187,   188,   189,   190,   191,
     193,   194,   196,   197,   198,   199,   201,   202,   204,   205,
     207,   212,   213,   215,   216,   217,   217,   223,   226,   228,
     230,   240,   241,   242,   243,   244,   246,   247,   248,   249,
     250,   251,   257,   258,   259,   260,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   279,
     282,   283,   285,   286,   288,   289,   291,   292,   294,   295,
     297,   298,   300,   301,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   314,   315,   317,   319,   320,   321,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   337,   339,   341,   343,   345,   348,   349,
     351,   353,   354,   356,   358,   361
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SYM", "PAT", "SORT",
  "FUNC", "ALG", "SPEC", "ADDSPEC", "REWR", "PRT", "GRAPH", "PFEIL",
  "TERM", "NUMPAT", "ATT", "IS", "EQ", "INFO", "LA1", "LA2", "LA3", "LA4",
  "LA5", "LOCAL", "RU", "RA", "COMMU", "LB", "IN", "NIN", "PARAM", "FOR",
  "TO", "STEP", "DO", "DBG", "LAST", "BRA", "OTHER", "DATA", "OUT", "INC",
  "EXE", "VARPAR", "SYS", "IF", "ELSE", "WHILE", "PRTNUM", "LIFT", "QUIT",
  "RETURN", "OPT", "COMM", "DEFAULT", "RIGHT", "SUBSORT", "INTNUM",
  "STEPS", "SYMBOLIC", "HOLD", "RULES", "SHOW", "REALNUM", "TYPEOF", "Id",
  "String", "Sort", "Alg", "Term", "La1", "La2", "La3", "La4", "La5", "Ru",
  "Ra", "Func", "Const", "Var", "Bra", "Bra1", "Bra2", "Terms", "Form",
  "Sorts", "Functs", "Forms", "Algs", "Cond2", "Cond", "'\\n'", "':'",
  "','", "'('", "')'", "';'", "'{'", "'}'", "$accept", "prog", "line",
  "definition", "idlist", "att", "$@1", "namedId", "PRECEDENCE",
  "condition", "condfunc", "instructions", "tinstructions",
  "oinstructions", "d_list", "instruction", "$@2", "aninstruction", "step",
  "prntexpr", "prntlist", "alglist", "Alg2", "sortlist", "vsortlist",
  "func", "funclist", "term", "termlist", "formula", "vinstr", "cformula",
  "formlist", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-240)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     414,   620,   620,   620,   620,   620,   -56,   -53,   510,   363,
     620,   620,   -42,   620,   510,   -38,  -240,    -3,   632,   -34,
       4,     5,   632,    13,   -26,   -26,    19,    -2,  -240,   510,
     620,   632,   204,     2,    24,    26,    29,   632,    31,   192,
    -240,    90,   510,   510,   510,   510,   510,   537,    12,  -240,
     510,   510,   510,  -240,   317,  -240,  -240,    21,    14,  -240,
      16,  -240,   431,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,    25,
      33,  -240,    35,  -240,    37,  -240,    38,    43,  -240,    57,
     527,  -240,    48,    50,    79,  -240,   127,  -240,    80,    54,
    -240,  -240,  -240,  -240,    82,  -240,    61,    63,    70,   510,
     414,    73,   414,  -240,   510,   431,  -240,    74,  -240,   632,
     152,    87,   168,   117,   177,   170,  -240,   510,   510,   510,
     510,   510,   537,   510,   510,  -240,   431,     3,   101,   114,
      28,   -25,   -16,   510,  -240,   510,   510,   331,   115,   122,
     233,   414,  -240,  -240,  -240,   414,   363,   510,   510,   510,
     510,   510,  -240,   510,   138,   620,   139,   140,   445,   464,
     -46,   141,   144,   119,   510,   121,   140,  -240,   510,   510,
     510,   265,   178,   -26,  -240,   128,   632,   206,   510,   158,
     161,  -240,   163,   172,   510,   431,   218,   146,   431,   157,
     510,  -240,  -240,  -240,  -240,   142,   151,  -240,  -240,   101,
     114,    28,   -25,   -16,   -16,  -240,  -240,  -240,   150,   201,
     243,   -26,  -240,   491,  -240,   162,   145,   223,  -240,  -240,
    -240,   -46,  -240,  -240,  -240,   193,   160,   140,   271,   200,
     202,   203,  -240,   414,  -240,   255,  -240,   510,   431,   285,
    -240,  -240,  -240,   577,  -240,  -240,  -240,  -240,   414,   140,
    -240,   234,   510,   205,   -46,   510,   414,  -240,   219,   510,
     303,   249,  -240,  -240,  -240,  -240,   238,   431,   262,   -46,
    -240,  -240,   325,   223,  -240,  -240,   431,  -240,   268,   176,
     275,   337,   510,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,   337,  -240,   270,   510,   338,   337,   565,  -240,
     282,  -240,   313,   431,   414,  -240,   603,   -46,  -240,  -240,
    -240,  -240,  -240,   620,  -240,  -240,    51,  -240,   286,   289,
      51,   414,  -240,  -240
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
      94,    96,    97,     0,     0,     0,    90,     0,     0,     0,
     103,   126,     0,     0,     0,     0,     0,     0,   128,   130,
       0,     0,     0,    65,    71,     2,    64,     0,    56,    63,
     104,    76,   102,    35,    39,    40,    41,   115,   116,   117,
     118,   119,   121,   120,   114,    36,    37,   122,   123,     0,
      26,    38,     0,    23,     0,    24,     0,     0,   126,   128,
       0,    78,     0,     0,     0,    74,     0,    87,     0,     0,
      80,    81,    79,    73,     0,    72,     0,     0,     0,     0,
      71,    50,    71,    77,     0,    91,    93,   124,    95,     0,
       0,     0,     0,     0,     0,    14,    10,   115,   116,   117,
     118,   119,   114,   122,   123,    19,    18,     0,   134,   135,
     136,   137,   138,     0,   133,     0,     0,   148,     0,     0,
       0,    71,     1,     3,     4,    71,     0,     0,     0,     0,
       0,     0,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,     0,     0,
       0,     0,    68,     0,    67,     0,     0,     0,     0,     0,
       0,    88,     0,     0,     0,    82,     0,     0,    84,     0,
       0,   139,   140,   131,    60,     0,    58,    57,   105,   142,
     143,   144,   145,   146,   147,    17,    27,     9,   110,   112,
       0,     0,   108,     0,    20,   106,     0,   151,   155,    21,
      22,     0,    75,    25,    16,     0,     0,     0,     0,     0,
       0,     0,    55,    71,    51,     0,   125,     0,    98,    12,
      15,    89,    13,     0,   141,   129,   149,    66,    71,     0,
     113,     0,     0,     0,     0,     0,    71,   153,     0,     0,
       0,     0,    52,    53,    54,    69,     0,    99,     0,     0,
      59,   111,    42,   151,   109,   107,   150,   152,     0,   100,
       0,    28,     0,    11,    83,    43,    44,    45,    46,    47,
      49,    48,    28,   154,     0,     0,     0,    28,     0,     6,
       0,     5,     0,   101,    71,     8,     0,     0,    33,    29,
      86,     7,    70,     0,    30,    31,     0,    32,    61,     0,
       0,    71,    62,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -240,  -240,   333,  -238,    18,  -239,  -240,    -4,  -240,   -23,
    -240,  -140,   136,  -240,    65,  -102,  -240,  -240,  -240,  -240,
       9,  -121,  -240,   143,  -157,    -6,   224,    -7,   -45,   149,
     129,  -240,   245
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    54,    55,    56,    79,   309,   326,    80,   302,   110,
     111,    57,   205,   206,   329,    58,   151,    59,   306,    60,
      61,   263,   225,   219,   220,    81,   118,    62,   148,   227,
     267,   228,   229
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    90,   112,   106,   107,   108,   149,    96,   182,    95,
     184,   204,    99,   194,    86,   207,   104,    87,    91,   238,
      82,    83,   115,    85,   222,   117,   120,    94,    92,    93,
     145,   125,   136,   135,   100,   138,   139,   140,   141,   142,
     144,    16,    97,   147,   147,   150,   101,   224,   116,   232,
     231,   161,   162,   163,     1,     2,     3,     4,     5,     6,
       7,   162,   163,   311,    98,    10,    11,    12,   315,   185,
     109,   121,   102,   103,    88,    42,    43,    44,    45,    46,
     270,   105,    47,    89,    49,    50,    51,   113,   328,   149,
      17,    18,   328,   122,   114,   146,   123,   124,   197,    52,
     126,   199,   181,   160,   161,   162,   163,   147,   137,    33,
      34,   156,   155,   187,   154,    37,    38,    39,   204,   164,
     138,   139,   140,   141,   142,   144,   147,   147,   165,   166,
     195,   167,   168,   239,   240,   241,   196,   169,   198,   147,
     146,   275,   171,   285,   172,   174,   173,   175,   176,   177,
     209,   210,   211,   212,   213,   256,   214,   178,   294,   179,
     244,   226,   226,   265,   287,   208,   180,   236,   183,   186,
     188,   147,   147,   147,   158,   159,   160,   161,   162,   163,
     117,   248,   189,   216,   190,   191,   193,   253,   159,   160,
     161,   162,   163,   147,   269,   192,   325,   201,   262,   157,
     158,   159,   160,   161,   162,   163,   202,   215,   217,   218,
     233,   305,   322,   234,   235,   237,   150,   157,   158,   159,
     160,   161,   162,   163,   247,   245,   243,   249,   250,   333,
      16,   251,   157,   158,   159,   160,   161,   162,   163,   252,
     277,   255,   257,   254,   258,   259,   260,   310,   157,   158,
     159,   160,   161,   162,   163,   226,   261,   264,   286,   266,
     268,   119,   289,    88,   127,   128,   129,   130,   131,    72,
      73,   132,    89,    49,   133,   134,    67,    68,    69,    70,
      71,    72,    73,    74,   271,   147,    77,    78,    52,   276,
     157,   158,   159,   160,   161,   162,   163,   272,   313,   273,
     274,   278,   284,   282,   319,   157,   158,   159,   160,   161,
     162,   163,   324,   200,   288,   203,   290,   152,   291,   327,
       1,     2,     3,     4,     5,     6,     7,     8,     9,   293,
     203,    10,    11,    12,   292,   304,    13,   157,   158,   159,
     160,   161,   162,   163,   307,   295,   296,   297,   298,   299,
      14,   300,   301,   308,    15,    16,    17,    18,    19,    20,
      21,    22,   242,    23,    24,   312,    25,    26,    27,    28,
      29,    30,    31,    32,   314,    33,    34,    35,    36,   320,
     321,    37,    38,    39,   330,    40,   331,   153,    41,    42,
      43,    44,    45,    46,   280,   332,    47,    48,    49,    50,
      51,    16,   281,   157,   158,   159,   160,   161,   162,   163,
     246,   283,   303,    52,   230,     0,    53,     1,     2,     3,
       4,     5,     6,     7,     8,     9,   200,     0,    10,    11,
      12,    40,     0,    13,    88,    42,    43,    44,    45,    46,
       0,     0,    47,    89,    49,    50,    51,    14,     0,     0,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    52,
      23,    24,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,    33,    34,    35,    36,     0,     0,    37,    38,
      39,     0,    40,    16,     0,    41,    42,    43,    44,    45,
      46,     0,   221,    47,    48,    49,    50,    51,     0,     0,
       0,     0,    16,   157,   158,   159,   160,   161,   162,   163,
      52,   221,     0,    53,     0,   222,    88,    42,    43,    44,
      45,    46,     0,     0,    47,    89,    49,    50,    51,    16,
       0,     0,     0,     0,     0,    88,    42,    43,    44,    45,
      46,   223,     0,    47,    89,    49,    50,    51,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,   222,    88,    42,    43,    44,    45,    46,     0,     0,
      47,    89,    49,    50,    51,    16,     0,     0,     0,     0,
       0,    88,    42,    43,    44,    45,    46,   223,     0,    47,
      89,    49,    50,    51,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,   163,    52,     0,    88,    42,
      43,    44,    45,    46,     0,     0,    47,    89,    49,    50,
      51,   170,     0,     0,     0,     0,   316,     0,   317,     0,
       0,     0,    63,   143,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,   157,
     158,   159,   160,   161,   162,   163,     0,     0,     0,     0,
       0,   318,     0,     0,     0,   323,     0,     0,     0,     0,
      63,   279,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    63,     0,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    67,    68,    69,    70,    71,    72,
      73,    74,     0,     0,    77,    78
};

static const yytype_int16 yycheck[] =
{
       4,     8,    25,    29,    30,    31,    51,    14,   110,    13,
     112,   151,    18,    10,    70,   155,    22,    70,     9,   176,
       2,     3,    29,     5,    70,    31,    32,    69,    10,    11,
      18,    37,    39,    39,    68,    42,    43,    44,    45,    46,
      47,    38,    80,    50,    51,    52,    80,   168,    30,   170,
      96,    76,    77,    78,     3,     4,     5,     6,     7,     8,
       9,    77,    78,   302,    67,    14,    15,    16,   307,   114,
      96,    69,    68,    68,    71,    72,    73,    74,    75,    76,
     237,    68,    79,    80,    81,    82,    83,    68,   326,   134,
      39,    40,   330,    69,    96,    83,    70,    68,   143,    96,
      69,   146,   109,    75,    76,    77,    78,   114,    18,    58,
      59,    95,    98,   119,    93,    64,    65,    66,   258,    94,
     127,   128,   129,   130,   131,   132,   133,   134,    95,    94,
     137,    94,    94,   178,   179,   180,   143,    94,   145,   146,
      83,   243,    94,   264,    94,    18,    67,    67,    94,    67,
     157,   158,   159,   160,   161,   200,   163,    96,   279,    96,
     183,   168,   169,    18,   266,   156,    96,   174,    95,    95,
      18,   178,   179,   180,    73,    74,    75,    76,    77,    78,
     186,   188,    95,   165,    16,    68,    16,   194,    74,    75,
      76,    77,    78,   200,    34,    18,   317,    82,   221,    72,
      73,    74,    75,    76,    77,    78,    84,    69,    69,    69,
      69,    35,   314,    69,    95,    94,   223,    72,    73,    74,
      75,    76,    77,    78,    18,    97,    48,    69,    67,   331,
      38,    68,    72,    73,    74,    75,    76,    77,    78,    67,
     247,    84,   100,    97,    93,    95,    45,   292,    72,    73,
      74,    75,    76,    77,    78,   262,    13,    95,   265,    36,
      67,    57,   269,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    72,    73,    74,    75,
      76,    77,    78,    79,    13,   292,    82,    83,    96,    34,
      72,    73,    74,    75,    76,    77,    78,    97,   305,    97,
      97,    16,    97,    69,   308,    72,    73,    74,    75,    76,
      77,    78,   316,    95,    95,    97,    13,     0,    69,   323,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    67,
      97,    14,    15,    16,    96,    67,    19,    72,    73,    74,
      75,    76,    77,    78,    69,    20,    21,    22,    23,    24,
      33,    26,    27,    16,    37,    38,    39,    40,    41,    42,
      43,    44,    97,    46,    47,    95,    49,    50,    51,    52,
      53,    54,    55,    56,    36,    58,    59,    60,    61,    97,
      67,    64,    65,    66,    98,    68,    97,    54,    71,    72,
      73,    74,    75,    76,   258,   330,    79,    80,    81,    82,
      83,    38,   259,    72,    73,    74,    75,    76,    77,    78,
     186,   262,   283,    96,   169,    -1,    99,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    95,    -1,    14,    15,
      16,    68,    -1,    19,    71,    72,    73,    74,    75,    76,
      -1,    -1,    79,    80,    81,    82,    83,    33,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    96,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    61,    -1,    -1,    64,    65,
      66,    -1,    68,    38,    -1,    71,    72,    73,    74,    75,
      76,    -1,    47,    79,    80,    81,    82,    83,    -1,    -1,
      -1,    -1,    38,    72,    73,    74,    75,    76,    77,    78,
      96,    47,    -1,    99,    -1,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    79,    80,    81,    82,    83,    38,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    96,    -1,    79,    80,    81,    82,    83,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,    81,    82,    83,    38,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    96,    -1,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    96,    -1,    71,    72,
      73,    74,    75,    76,    -1,    -1,    79,    80,    81,    82,
      83,    94,    -1,    -1,    -1,    -1,    61,    -1,    63,    -1,
      -1,    -1,    67,    96,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    72,
      73,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      67,    94,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    67,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    72,    73,    74,    75,    76,    77,
      78,    79,    -1,    -1,    82,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    58,    59,    60,    61,    64,    65,    66,
      68,    71,    72,    73,    74,    75,    76,    79,    80,    81,
      82,    83,    96,    99,   102,   103,   104,   112,   116,   118,
     120,   121,   128,    67,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,   105,
     108,   126,   105,   105,   108,   105,    70,    70,    71,    80,
     128,   121,   105,   105,    69,   108,   128,    80,    67,   126,
      68,    80,    68,    68,   126,    68,    29,    30,    31,    96,
     110,   111,   110,    68,    96,   128,   105,   126,   127,    57,
     126,    69,    69,    70,    68,   126,    69,    72,    73,    74,
      75,    76,    79,    82,    83,   126,   128,    18,   128,   128,
     128,   128,   128,    96,   128,    18,    83,   128,   129,   129,
     128,   117,     0,   103,    93,    98,    95,    72,    73,    74,
      75,    76,    77,    78,    94,    95,    94,    94,    94,    94,
      94,    94,    94,    67,    18,    67,    94,    67,    96,    96,
      96,   128,   116,    95,   116,   129,    95,   126,    18,    95,
      16,    68,    18,    16,    10,   128,   128,   129,   128,   129,
      95,    82,    84,    97,   112,   113,   114,   112,   121,   128,
     128,   128,   128,   128,   128,    69,   105,    69,    69,   124,
     125,    47,    70,    96,   122,   123,   128,   130,   132,   133,
     133,    96,   122,    69,    69,    95,   128,    94,   125,   129,
     129,   129,    97,    48,   110,    97,   127,    18,   128,    69,
      67,    68,    67,   128,    97,    84,   129,   100,    93,    95,
      45,    13,   110,   122,    95,    18,    36,   131,    67,    34,
     125,    13,    97,    97,    97,   116,    34,   128,    16,    94,
     113,   124,    69,   130,    97,   122,   128,   116,    95,   128,
      13,    69,    96,    67,   122,    20,    21,    22,    23,    24,
      26,    27,   109,   131,    67,    35,   119,    69,    16,   106,
     129,   106,    95,   128,    36,   106,    61,    63,    96,   108,
      97,    67,   116,    62,   108,   122,   107,   108,   104,   115,
      98,    97,   115,   116
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   101,   102,   102,   103,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   106,   106,
     106,   106,   106,   107,   106,   108,   108,   108,   108,   108,
     108,   108,   109,   109,   109,   109,   109,   109,   109,   109,
     110,   110,   111,   111,   111,   111,   112,   112,   113,   113,
     114,   115,   115,   116,   116,   117,   116,   116,   116,   116,
     116,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     119,   119,   120,   120,   121,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   127,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   129,   129,
     130,   131,   131,   132,   132,   133
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     8,     7,     9,     8,     4,
       2,     6,     4,     4,     2,     4,     4,     4,     2,     2,
       4,     4,     4,     2,     2,     4,     1,     3,     0,     2,
       3,     3,     4,     0,     6,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     4,     4,     3,     1,     3,     1,     3,
       1,     1,     3,     1,     1,     0,     4,     3,     3,     5,
       9,     0,     2,     2,     2,     4,     1,     2,     2,     2,
       2,     2,     3,     6,     3,     3,     8,     2,     3,     4,
       1,     2,     1,     2,     1,     2,     1,     1,     4,     5,
       0,     2,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     4,
       1,     3,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     4,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     0,     2,     2,     4,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 4: /* line: instructions '\n'  */
#line 88 "syn.y"
                                    {Node * temp;
														if ((yyvsp[-1].y_nod)) { temp = mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod));
															is_running();
															CALLFUNCT(temp);
															is_not_running();
															delete(temp);}
														}
#line 1545 "syn.tab.c"
    break;

  case 5: /* definition: FUNC namedId ':' vsortlist PFEIL Sort PRECEDENCE att  */
#line 96 "syn.y"
                                                                       {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fn,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1553 "syn.tab.c"
    break;

  case 6: /* definition: OTHER func ':' vsortlist PFEIL Sort att  */
#line 99 "syn.y"
                                                                  { (yyval.y_nod)=mknod(FUNC,(Node *) other_fn,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1562 "syn.tab.c"
    break;

  case 7: /* definition: ATT Sort Id ',' Id ',' Id ',' Id  */
#line 103 "syn.y"
                                                           { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufn(name((yyvsp[0].y_sym))))))));	}
#line 1573 "syn.tab.c"
    break;

  case 8: /* definition: BRA Id Id ':' vsortlist PFEIL Sort att  */
#line 109 "syn.y"
                                                                            {Node * fnlist;  /* Brackets */
							            				if (((yyvsp[-6].y_sym))==((yyvsp[-5].y_sym)))
							            					fnlist=mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_sym),Bra,(Node *) (yyvsp[-1].y_sym),(yyvsp[-3].y_nod),FALSE),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fn,mknod(PARAM,(Node *) (yyvsp[-6].y_sym),(yyvsp[0].y_nod))),NULL));
											            else
								             				fnlist=mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_sym),Bra1,(Node *) (yyvsp[-1].y_sym),(yyvsp[-3].y_nod),FALSE),
                                       mknod(PARAM,DECLARE((Node *) (yyvsp[-5].y_sym),Bra2,(Node *) (yyvsp[-1].y_sym),(yyvsp[-3].y_nod),FALSE),
                                       mknod(PARAM, mknod(FUNC,(Node *) set_brackets,mknod(PARAM,(Node *) (yyvsp[-6].y_sym),(Node *) (yyvsp[-5].y_sym))),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fn,mknod(PARAM,(Node *) (yyvsp[-6].y_sym),(yyvsp[0].y_nod))),NULL))));
																	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,fnlist);
																	}
#line 1589 "syn.tab.c"
    break;

  case 9: /* definition: PAT idlist ':' Sort  */
#line 120 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1595 "syn.tab.c"
    break;

  case 10: /* definition: REALNUM Sort  */
#line 121 "syn.y"
                                                                                 {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* sets numbertype for mknum */}
#line 1601 "syn.tab.c"
    break;

  case 11: /* definition: SUBSORT Sort ',' Sort ATT Id  */
#line 122 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort */
										      mknod(PARAM,(Node *) (yyvsp[-4].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufn(name((yyvsp[0].y_sym))))));}
#line 1608 "syn.tab.c"
    break;

  case 12: /* definition: SUBSORT Sort ',' Sort  */
#line 124 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort of a sort without values */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),mknod(PARAM,(Node *) (yyvsp[0].y_sym),NULL)));}
#line 1615 "syn.tab.c"
    break;

  case 13: /* definition: SHOW func ATT Id  */
#line 126 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) show_def,      /* 2026: print function */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) give_pfn(name((yyvsp[0].y_sym)))));}
#line 1622 "syn.tab.c"
    break;

  case 14: /* definition: SHOW func  */
#line 128 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) show_def,      /* 2026: the usual printing again */
										      mknod(PARAM,(Node *) (yyvsp[0].y_nod),NULL));}
#line 1629 "syn.tab.c"
    break;

  case 15: /* definition: INTNUM Sort ATT Id  */
#line 130 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) intnum_def,    /* 2026: sort of integers */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufn(name((yyvsp[0].y_sym)))));}
#line 1636 "syn.tab.c"
    break;

  case 16: /* definition: NUMPAT idlist ':' Sort  */
#line 132 "syn.y"
                                                                 { /* pattern variables for numbers */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1643 "syn.tab.c"
    break;

  case 17: /* definition: SYM idlist ':' Sort  */
#line 134 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1649 "syn.tab.c"
    break;

  case 18: /* definition: TYPEOF term  */
#line 135 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) typeof_fn,(yyvsp[0].y_nod));}
#line 1655 "syn.tab.c"
    break;

  case 19: /* definition: TYPEOF func  */
#line 136 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) typeof_func,(Node *) (yyvsp[0].y_nod));}
#line 1661 "syn.tab.c"
    break;

  case 20: /* definition: SPEC Alg ':' alglist  */
#line 137 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1667 "syn.tab.c"
    break;

  case 21: /* definition: SPEC Alg ':' formlist  */
#line 138 "syn.y"
                                                         {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1673 "syn.tab.c"
    break;

  case 22: /* definition: ADDSPEC Alg ':' formlist  */
#line 139 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1679 "syn.tab.c"
    break;

  case 23: /* definition: SORT idlist  */
#line 140 "syn.y"
                                                                             {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1685 "syn.tab.c"
    break;

  case 24: /* definition: ALG idlist  */
#line 142 "syn.y"
                                                     {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1691 "syn.tab.c"
    break;

  case 25: /* definition: TERM idlist ':' Sort  */
#line 143 "syn.y"
                                                   {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1697 "syn.tab.c"
    break;

  case 26: /* idlist: namedId  */
#line 145 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1703 "syn.tab.c"
    break;

  case 27: /* idlist: namedId ',' idlist  */
#line 146 "syn.y"
                                                        {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1709 "syn.tab.c"
    break;

  case 28: /* att: %empty  */
#line 154 "syn.y"
                                        { (yyval.y_nod) = NULL;}
#line 1715 "syn.tab.c"
    break;

  case 29: /* att: ATT namedId  */
#line 155 "syn.y"
                                                { /* numeric C function (userfn.c), otherwise symbolic (symfn.c) */
			                  u_function * u = give_ufn_quiet(name((Symbol *) (yyvsp[0].y_nod)));
			                  s_function * s = u ? NULL : give_sfn(name((Symbol *) (yyvsp[0].y_nod)));
			                  if (u)
			                    (yyval.y_nod) = mknod(ATT,(Node *) u,NULL);
			                  else if (s)
			                    (yyval.y_nod) = mknod(ATT,(Node *) s,mknod(PARAM,NULL,NULL)); /* r: symbolic */
			                  else
			                    { printfErr(" --ERROR ATT : C-Function %s not Implemented \n",name((Symbol *) (yyvsp[0].y_nod)));
			                      (yyval.y_nod) = mknod(ATT,NULL,NULL); }
			                }
#line 1731 "syn.tab.c"
    break;

  case 30: /* att: ATT SYMBOLIC namedId  */
#line 166 "syn.y"
                                                        { /* 2026: symbolic C function (symfn.c): gets terms */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 0); }
#line 1738 "syn.tab.c"
    break;

  case 31: /* att: ATT RULES alglist  */
#line 168 "syn.y"
                                                { /* 2026: function defined by a rule list: f(..) is REWR f(..) : alglist */
			                  (yyval.y_nod) = mknod(ATT,(Node *) rules_sfn(),mknod(PARAM,(yyvsp[0].y_nod),NULL)); }
#line 1745 "syn.tab.c"
    break;

  case 32: /* att: ATT SYMBOLIC HOLD namedId  */
#line 170 "syn.y"
                                                        { /* 2026: plus arguments unevaluated (matchq) */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 1); }
#line 1752 "syn.tab.c"
    break;

  case 33: /* $@1: %empty  */
#line 172 "syn.y"
                                          {block_begin();no_protect();}
#line 1758 "syn.tab.c"
    break;

  case 34: /* att: ATT '(' $@1 d_list ')' instruction  */
#line 173 "syn.y"
                                                                                        {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1764 "syn.tab.c"
    break;

  case 35: /* namedId: Id  */
#line 175 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1770 "syn.tab.c"
    break;

  case 36: /* namedId: Const  */
#line 176 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1776 "syn.tab.c"
    break;

  case 37: /* namedId: Var  */
#line 177 "syn.y"
                         { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1782 "syn.tab.c"
    break;

  case 38: /* namedId: func  */
#line 178 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1788 "syn.tab.c"
    break;

  case 39: /* namedId: Sort  */
#line 179 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1794 "syn.tab.c"
    break;

  case 40: /* namedId: Alg  */
#line 180 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1800 "syn.tab.c"
    break;

  case 41: /* namedId: Term  */
#line 181 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1806 "syn.tab.c"
    break;

  case 42: /* PRECEDENCE: %empty  */
#line 184 "syn.y"
                                                                {(yyval.y_int) = Func;}
#line 1812 "syn.tab.c"
    break;

  case 43: /* PRECEDENCE: LA1  */
#line 185 "syn.y"
                                                                        {(yyval.y_int) = La1;	/* Left-associative */}
#line 1818 "syn.tab.c"
    break;

  case 44: /* PRECEDENCE: LA2  */
#line 186 "syn.y"
                                                                        {(yyval.y_int) = La2;	/* Left-associative */}
#line 1824 "syn.tab.c"
    break;

  case 45: /* PRECEDENCE: LA3  */
#line 187 "syn.y"
                                                                        {(yyval.y_int) = La3;	/* Left-associative */}
#line 1830 "syn.tab.c"
    break;

  case 46: /* PRECEDENCE: LA4  */
#line 188 "syn.y"
                                                                        {(yyval.y_int) = La4;	/* Left-associative */}
#line 1836 "syn.tab.c"
    break;

  case 47: /* PRECEDENCE: LA5  */
#line 189 "syn.y"
                                                                        {(yyval.y_int) = La5;	/* Left-associative */}
#line 1842 "syn.tab.c"
    break;

  case 48: /* PRECEDENCE: RA  */
#line 190 "syn.y"
                                                                        {(yyval.y_int) = Ra;  	/* Right-associative */}
#line 1848 "syn.tab.c"
    break;

  case 49: /* PRECEDENCE: RU  */
#line 191 "syn.y"
                                                                        {(yyval.y_int) = Ru;	  /* Right unary */}
#line 1854 "syn.tab.c"
    break;

  case 50: /* condition: condfunc  */
#line 193 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1860 "syn.tab.c"
    break;

  case 51: /* condition: condfunc ',' condition  */
#line 194 "syn.y"
                                                        {(yyval.y_nod) = mknod(Cond,(Node *) and_cond,mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod)));}
#line 1866 "syn.tab.c"
    break;

  case 52: /* condfunc: LB '(' termlist ')'  */
#line 196 "syn.y"
                              {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1872 "syn.tab.c"
    break;

  case 53: /* condfunc: IN '(' termlist ')'  */
#line 197 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1878 "syn.tab.c"
    break;

  case 54: /* condfunc: NIN '(' termlist ')'  */
#line 198 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1884 "syn.tab.c"
    break;

  case 55: /* condfunc: '(' term ')'  */
#line 199 "syn.y"
                                                                        {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1890 "syn.tab.c"
    break;

  case 56: /* instructions: instruction  */
#line 201 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1896 "syn.tab.c"
    break;

  case 57: /* instructions: instruction ';' instructions  */
#line 202 "syn.y"
                                                                                       {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1902 "syn.tab.c"
    break;

  case 58: /* tinstructions: oinstructions  */
#line 204 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1908 "syn.tab.c"
    break;

  case 59: /* tinstructions: oinstructions '\n' tinstructions  */
#line 205 "syn.y"
                                                                                                                {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1914 "syn.tab.c"
    break;

  case 60: /* oinstructions: instructions  */
#line 207 "syn.y"
                                                {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1920 "syn.tab.c"
    break;

  case 61: /* d_list: definition  */
#line 212 "syn.y"
                                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1926 "syn.tab.c"
    break;

  case 62: /* d_list: definition ';' d_list  */
#line 213 "syn.y"
                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1932 "syn.tab.c"
    break;

  case 63: /* instruction: aninstruction  */
#line 215 "syn.y"
                                {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Check local variables ! */ }
#line 1938 "syn.tab.c"
    break;

  case 64: /* instruction: definition  */
#line 216 "syn.y"
                                                                        {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1944 "syn.tab.c"
    break;

  case 65: /* $@2: %empty  */
#line 217 "syn.y"
                                                                                                        {block_begin();no_protect();}
#line 1950 "syn.tab.c"
    break;

  case 66: /* instruction: '{' $@2 tinstructions '}'  */
#line 218 "syn.y"
                                                                        {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 1960 "syn.tab.c"
    break;

  case 67: /* instruction: WHILE condition instruction  */
#line 223 "syn.y"
                                                        {Node * memo,* rtw=in_block_instruct(memo=mknod(FUNC,(Node *) while_fn,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* then becomes $3 */)));
																		WHILE_BODY(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1967 "syn.tab.c"
    break;

  case 68: /* instruction: IF condition instruction  */
#line 226 "syn.y"
                                                        {Node * memo,* rtw=in_block_instruct(memo=mknod(FUNC,(Node *) if_fn,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		IF_THEN(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1974 "syn.tab.c"
    break;

  case 69: /* instruction: IF condition instruction ELSE instruction  */
#line 228 "syn.y"
                                                                        {Node * memo,* rtw = in_block_instruct(memo=mknod(FUNC,(Node *) if_fn,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(memo) = (yyvsp[-2].y_nod);IF_ELSE(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1981 "syn.tab.c"
    break;

  case 70: /* instruction: FOR term EQ term TO term step DO instruction  */
#line 231 "syn.y"
                                                                                                                {Node * memo,* rtw = in_block_instruct(memo=mknod(FUNC,(Node *) for_loop,
																mknod(PARAM,
																	mknod(PARAM,(yyvsp[-5].y_nod),(yyvsp[-3].y_nod)),
																	mknod(PARAM,
																		mknod(PARAM,(yyvsp[-2].y_nod),(Node *) ((yyvsp[-7].y_nod))),
																		NULL /* $9 */) )));	
														FOR_BODY(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1993 "syn.tab.c"
    break;

  case 71: /* aninstruction: %empty  */
#line 240 "syn.y"
                                        {(yyval.y_nod)=NULL;}
#line 1999 "syn.tab.c"
    break;

  case 72: /* aninstruction: SYS String  */
#line 241 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) system_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2005 "syn.tab.c"
    break;

  case 73: /* aninstruction: INC String  */
#line 242 "syn.y"
                                                                        {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fn,(Node *) ((yyvsp[0].y_sym))); }
#line 2011 "syn.tab.c"
    break;

  case 74: /* aninstruction: INFO namedId  */
#line 243 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) info_fn,(Node *) ((yyvsp[0].y_nod))); }
#line 2017 "syn.tab.c"
    break;

  case 75: /* aninstruction: REWR term ':' alglist  */
#line 244 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fn,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 2024 "syn.tab.c"
    break;

  case 76: /* aninstruction: prntlist  */
#line 246 "syn.y"
                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 2030 "syn.tab.c"
    break;

  case 77: /* aninstruction: PRTNUM String  */
#line 247 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 2036 "syn.tab.c"
    break;

  case 78: /* aninstruction: PRT prntlist  */
#line 248 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* without \n */ }
#line 2042 "syn.tab.c"
    break;

  case 79: /* aninstruction: OUT String  */
#line 249 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 2048 "syn.tab.c"
    break;

  case 80: /* aninstruction: DATA String  */
#line 250 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 2054 "syn.tab.c"
    break;

  case 81: /* aninstruction: DATA Const  */
#line 251 "syn.y"
                                                                        {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 2065 "syn.tab.c"
    break;

  case 82: /* aninstruction: Term EQ term  */
#line 257 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 2071 "syn.tab.c"
    break;

  case 83: /* aninstruction: Term EQ REWR term ':' alglist  */
#line 258 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fn,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 2077 "syn.tab.c"
    break;

  case 84: /* aninstruction: Const EQ term  */
#line 259 "syn.y"
                                                        { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 2083 "syn.tab.c"
    break;

  case 85: /* aninstruction: EXE func Id  */
#line 260 "syn.y"
                                                        {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufn(name((yyvsp[0].y_sym)));
 													}
#line 2093 "syn.tab.c"
    break;

  case 86: /* aninstruction: LIFT '(' termlist ')' TO '(' termlist ')'  */
#line 265 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 2099 "syn.tab.c"
    break;

  case 87: /* aninstruction: DBG Const  */
#line 266 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 2105 "syn.tab.c"
    break;

  case 88: /* aninstruction: STEPS Alg String  */
#line 267 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) steps_fn,mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2111 "syn.tab.c"
    break;

  case 89: /* aninstruction: SYMBOLIC String EQ String  */
#line 268 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fn,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2117 "syn.tab.c"
    break;

  case 90: /* aninstruction: SYMBOLIC  */
#line 269 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fn,NULL);  /* delete roles */}
#line 2123 "syn.tab.c"
    break;

  case 91: /* aninstruction: RETURN term  */
#line 270 "syn.y"
                                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) return_fn,(yyvsp[0].y_nod));}
#line 2129 "syn.tab.c"
    break;

  case 92: /* aninstruction: QUIT  */
#line 271 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fn,NULL);}
#line 2135 "syn.tab.c"
    break;

  case 93: /* aninstruction: OPT idlist  */
#line 272 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fn,(yyvsp[0].y_nod));}
#line 2141 "syn.tab.c"
    break;

  case 94: /* aninstruction: OPT  */
#line 273 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fn,NULL);   /* delete */}
#line 2147 "syn.tab.c"
    break;

  case 95: /* aninstruction: COMM funclist  */
#line 274 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fn,(yyvsp[0].y_nod));}
#line 2153 "syn.tab.c"
    break;

  case 96: /* aninstruction: COMM  */
#line 275 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fn,NULL);  /* delete */}
#line 2159 "syn.tab.c"
    break;

  case 97: /* aninstruction: DEFAULT  */
#line 276 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,NULL); /* delete */}
#line 2165 "syn.tab.c"
    break;

  case 98: /* aninstruction: DEFAULT func EQ term  */
#line 277 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),NULL),(yyvsp[0].y_nod)));}
#line 2172 "syn.tab.c"
    break;

  case 99: /* aninstruction: DEFAULT RIGHT func EQ term  */
#line 279 "syn.y"
                                                     {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),mknod(PARAM,NULL,NULL)),(yyvsp[0].y_nod)));}
#line 2179 "syn.tab.c"
    break;

  case 100: /* step: %empty  */
#line 282 "syn.y"
                        {(yyval.y_nod)=(Node *) NULL;}
#line 2185 "syn.tab.c"
    break;

  case 101: /* step: STEP term  */
#line 283 "syn.y"
                                        {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2191 "syn.tab.c"
    break;

  case 102: /* prntexpr: term  */
#line 285 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2197 "syn.tab.c"
    break;

  case 103: /* prntexpr: String  */
#line 286 "syn.y"
                                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2203 "syn.tab.c"
    break;

  case 104: /* prntlist: prntexpr  */
#line 288 "syn.y"
                                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2209 "syn.tab.c"
    break;

  case 105: /* prntlist: prntexpr ',' prntlist  */
#line 289 "syn.y"
                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2215 "syn.tab.c"
    break;

  case 106: /* alglist: Alg2  */
#line 291 "syn.y"
                                                                {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2221 "syn.tab.c"
    break;

  case 107: /* alglist: Alg2 ',' alglist  */
#line 292 "syn.y"
                                                        {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2227 "syn.tab.c"
    break;

  case 108: /* Alg2: Alg  */
#line 294 "syn.y"
                                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2233 "syn.tab.c"
    break;

  case 109: /* Alg2: '(' alglist ')'  */
#line 295 "syn.y"
                                                                {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2239 "syn.tab.c"
    break;

  case 110: /* sortlist: Sort  */
#line 297 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2245 "syn.tab.c"
    break;

  case 111: /* sortlist: Sort ',' sortlist  */
#line 298 "syn.y"
                                                                {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2251 "syn.tab.c"
    break;

  case 112: /* vsortlist: sortlist  */
#line 300 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2257 "syn.tab.c"
    break;

  case 113: /* vsortlist: sortlist VARPAR  */
#line 301 "syn.y"
                                                                        {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2263 "syn.tab.c"
    break;

  case 114: /* func: Func  */
#line 303 "syn.y"
                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2269 "syn.tab.c"
    break;

  case 115: /* func: La1  */
#line 304 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2275 "syn.tab.c"
    break;

  case 116: /* func: La2  */
#line 305 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2281 "syn.tab.c"
    break;

  case 117: /* func: La3  */
#line 306 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2287 "syn.tab.c"
    break;

  case 118: /* func: La4  */
#line 307 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2293 "syn.tab.c"
    break;

  case 119: /* func: La5  */
#line 308 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2299 "syn.tab.c"
    break;

  case 120: /* func: Ra  */
#line 309 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2305 "syn.tab.c"
    break;

  case 121: /* func: Ru  */
#line 310 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2311 "syn.tab.c"
    break;

  case 122: /* func: Bra  */
#line 311 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2317 "syn.tab.c"
    break;

  case 123: /* func: Bra1  */
#line 312 "syn.y"
                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2323 "syn.tab.c"
    break;

  case 124: /* funclist: func  */
#line 314 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2329 "syn.tab.c"
    break;

  case 125: /* funclist: func ',' funclist  */
#line 315 "syn.y"
                                                        {(yyval.y_nod) = mknod(Functs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2335 "syn.tab.c"
    break;

  case 126: /* term: Term  */
#line 317 "syn.y"
                                                                        {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); does not remember dependencies and does not work in blocks */ 
														}
#line 2342 "syn.tab.c"
    break;

  case 127: /* term: LAST  */
#line 319 "syn.y"
                                                                                        {(yyval.y_nod) = (Node *) lastterm;}
#line 2348 "syn.tab.c"
    break;

  case 128: /* term: Const  */
#line 320 "syn.y"
                                                                                        {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2354 "syn.tab.c"
    break;

  case 129: /* term: Const Bra1 termlist Bra2  */
#line 321 "syn.y"
                                                   {np_aux=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),np_aux), np_aux);}
#line 2361 "syn.tab.c"
    break;

  case 130: /* term: Var  */
#line 323 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2367 "syn.tab.c"
    break;

  case 131: /* term: '(' term ')'  */
#line 324 "syn.y"
                                                    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2373 "syn.tab.c"
    break;

  case 132: /* term: term Ru  */
#line 325 "syn.y"
                                                                      {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2379 "syn.tab.c"
    break;

  case 133: /* term: Func term  */
#line 326 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2385 "syn.tab.c"
    break;

  case 134: /* term: La1 term  */
#line 327 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2391 "syn.tab.c"
    break;

  case 135: /* term: La2 term  */
#line 328 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2397 "syn.tab.c"
    break;

  case 136: /* term: La3 term  */
#line 329 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2403 "syn.tab.c"
    break;

  case 137: /* term: La4 term  */
#line 330 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2409 "syn.tab.c"
    break;

  case 138: /* term: La5 term  */
#line 331 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2415 "syn.tab.c"
    break;

  case 139: /* term: Bra termlist Bra  */
#line 332 "syn.y"
                                                  {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2421 "syn.tab.c"
    break;

  case 140: /* term: Bra1 termlist Bra2  */
#line 333 "syn.y"
                                                {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2427 "syn.tab.c"
    break;

  case 141: /* term: Func '(' termlist ')'  */
#line 334 "syn.y"
                                                        {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2433 "syn.tab.c"
    break;

  case 142: /* term: term La1 term  */
#line 335 "syn.y"
                                                    {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2440 "syn.tab.c"
    break;

  case 143: /* term: term La2 term  */
#line 337 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2447 "syn.tab.c"
    break;

  case 144: /* term: term La3 term  */
#line 339 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2454 "syn.tab.c"
    break;

  case 145: /* term: term La4 term  */
#line 341 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2461 "syn.tab.c"
    break;

  case 146: /* term: term La5 term  */
#line 343 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2468 "syn.tab.c"
    break;

  case 147: /* term: term Ra term  */
#line 345 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2475 "syn.tab.c"
    break;

  case 148: /* termlist: term  */
#line 348 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2481 "syn.tab.c"
    break;

  case 149: /* termlist: term ',' termlist  */
#line 349 "syn.y"
                                                        {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2487 "syn.tab.c"
    break;

  case 150: /* formula: term EQ term  */
#line 351 "syn.y"
                                        {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2493 "syn.tab.c"
    break;

  case 151: /* vinstr: %empty  */
#line 353 "syn.y"
                                                                {(yyval.y_nod) = NULL;}
#line 2499 "syn.tab.c"
    break;

  case 152: /* vinstr: DO instruction  */
#line 354 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2505 "syn.tab.c"
    break;

  case 153: /* cformula: formula vinstr  */
#line 356 "syn.y"
                                                                        {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2512 "syn.tab.c"
    break;

  case 154: /* cformula: IF condition formula vinstr  */
#line 358 "syn.y"
                                               {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2519 "syn.tab.c"
    break;

  case 155: /* formlist: cformula  */
#line 361 "syn.y"
                                                                {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL serves for hooking in further formulas !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. because of SPEC real : A+B=C;a=3 */
															}
#line 2527 "syn.tab.c"
    break;


#line 2531 "syn.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 365 "syn.y"


/* 2026: ATT SYMBOLIC [HOLD] name: a symbolic C function (symfn.c), which
   gets the argument terms; with HOLD they are passed unevaluated */
static Node * sym_att (Node * id, int hold)
{
	s_function * s = give_sfn(name((Symbol *) id));
	if (! s)
		{
		printfErr(" --ERROR ATT SYMBOLIC : C-Function %s not Implemented \n",name((Symbol *) id));
		return mknod(ATT,NULL,NULL);
		}
	return mknod(ATT,(Node *) s,mknod(PARAM,NULL,hold ? mknod(PARAM,NULL,NULL) : NULL));
}
