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
#include "help.h"	/* 2026: HELP */
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


#line 117 "syn.tab.c"

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
  YYSYMBOL_MAXSTEPS = 61,                  /* MAXSTEPS  */
  YYSYMBOL_MAXDEPTH = 62,                  /* MAXDEPTH  */
  YYSYMBOL_SYMBOLIC = 63,                  /* SYMBOLIC  */
  YYSYMBOL_HOLD = 64,                      /* HOLD  */
  YYSYMBOL_RULES = 65,                     /* RULES  */
  YYSYMBOL_SHOW = 66,                      /* SHOW  */
  YYSYMBOL_REALNUM = 67,                   /* REALNUM  */
  YYSYMBOL_TYPEOF = 68,                    /* TYPEOF  */
  YYSYMBOL_HELP = 69,                      /* HELP  */
  YYSYMBOL_ALIAS = 70,                     /* ALIAS  */
  YYSYMBOL_Id = 71,                        /* Id  */
  YYSYMBOL_String = 72,                    /* String  */
  YYSYMBOL_Sort = 73,                      /* Sort  */
  YYSYMBOL_Alg = 74,                       /* Alg  */
  YYSYMBOL_Term = 75,                      /* Term  */
  YYSYMBOL_La1 = 76,                       /* La1  */
  YYSYMBOL_La2 = 77,                       /* La2  */
  YYSYMBOL_La3 = 78,                       /* La3  */
  YYSYMBOL_La4 = 79,                       /* La4  */
  YYSYMBOL_La5 = 80,                       /* La5  */
  YYSYMBOL_Ru = 81,                        /* Ru  */
  YYSYMBOL_Ra = 82,                        /* Ra  */
  YYSYMBOL_Func = 83,                      /* Func  */
  YYSYMBOL_Const = 84,                     /* Const  */
  YYSYMBOL_Var = 85,                       /* Var  */
  YYSYMBOL_Bra = 86,                       /* Bra  */
  YYSYMBOL_Bra1 = 87,                      /* Bra1  */
  YYSYMBOL_Bra2 = 88,                      /* Bra2  */
  YYSYMBOL_Terms = 89,                     /* Terms  */
  YYSYMBOL_Form = 90,                      /* Form  */
  YYSYMBOL_Sorts = 91,                     /* Sorts  */
  YYSYMBOL_Functs = 92,                    /* Functs  */
  YYSYMBOL_Forms = 93,                     /* Forms  */
  YYSYMBOL_Algs = 94,                      /* Algs  */
  YYSYMBOL_Cond2 = 95,                     /* Cond2  */
  YYSYMBOL_Cond = 96,                      /* Cond  */
  YYSYMBOL_97_n_ = 97,                     /* '\n'  */
  YYSYMBOL_98_ = 98,                       /* ':'  */
  YYSYMBOL_99_ = 99,                       /* ','  */
  YYSYMBOL_100_ = 100,                     /* '('  */
  YYSYMBOL_101_ = 101,                     /* ')'  */
  YYSYMBOL_102_ = 102,                     /* ';'  */
  YYSYMBOL_103_ = 103,                     /* '{'  */
  YYSYMBOL_104_ = 104,                     /* '}'  */
  YYSYMBOL_YYACCEPT = 105,                 /* $accept  */
  YYSYMBOL_prog = 106,                     /* prog  */
  YYSYMBOL_line = 107,                     /* line  */
  YYSYMBOL_definition = 108,               /* definition  */
  YYSYMBOL_idlist = 109,                   /* idlist  */
  YYSYMBOL_att = 110,                      /* att  */
  YYSYMBOL_111_1 = 111,                    /* $@1  */
  YYSYMBOL_namedId = 112,                  /* namedId  */
  YYSYMBOL_PRECEDENCE = 113,               /* PRECEDENCE  */
  YYSYMBOL_condition = 114,                /* condition  */
  YYSYMBOL_condfunc = 115,                 /* condfunc  */
  YYSYMBOL_instructions = 116,             /* instructions  */
  YYSYMBOL_tinstructions = 117,            /* tinstructions  */
  YYSYMBOL_oinstructions = 118,            /* oinstructions  */
  YYSYMBOL_d_list = 119,                   /* d_list  */
  YYSYMBOL_instruction = 120,              /* instruction  */
  YYSYMBOL_121_2 = 121,                    /* $@2  */
  YYSYMBOL_aninstruction = 122,            /* aninstruction  */
  YYSYMBOL_step = 123,                     /* step  */
  YYSYMBOL_prntexpr = 124,                 /* prntexpr  */
  YYSYMBOL_prntlist = 125,                 /* prntlist  */
  YYSYMBOL_alglist = 126,                  /* alglist  */
  YYSYMBOL_Alg2 = 127,                     /* Alg2  */
  YYSYMBOL_sortlist = 128,                 /* sortlist  */
  YYSYMBOL_vsortlist = 129,                /* vsortlist  */
  YYSYMBOL_func = 130,                     /* func  */
  YYSYMBOL_funclist = 131,                 /* funclist  */
  YYSYMBOL_term = 132,                     /* term  */
  YYSYMBOL_termlist = 133,                 /* termlist  */
  YYSYMBOL_formula = 134,                  /* formula  */
  YYSYMBOL_vinstr = 135,                   /* vinstr  */
  YYSYMBOL_cformula = 136,                 /* cformula  */
  YYSYMBOL_formlist = 137                  /* formlist  */
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
#define YYFINAL  160
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   729

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  105
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  345

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   351


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
      97,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     100,   101,     2,     2,    99,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    98,   102,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   103,     2,   104,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,    87,    89,    97,   100,   104,   110,   121,
     122,   123,   125,   127,   129,   131,   133,   135,   136,   137,
     138,   139,   140,   141,   142,   144,   145,   147,   148,   156,
     157,   168,   170,   172,   174,   174,   177,   178,   179,   180,
     181,   182,   183,   186,   187,   188,   189,   190,   191,   192,
     193,   195,   196,   198,   199,   200,   201,   203,   204,   206,
     207,   209,   214,   215,   217,   218,   219,   219,   225,   228,
     230,   232,   242,   243,   244,   245,   246,   248,   249,   250,
     251,   252,   253,   259,   260,   261,   262,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   286,   289,   290,   292,   293,
     295,   296,   298,   299,   301,   302,   304,   305,   307,   308,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     321,   322,   324,   326,   327,   328,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   344,
     346,   348,   350,   352,   355,   356,   358,   360,   361,   363,
     365,   368
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
  "STEPS", "MAXSTEPS", "MAXDEPTH", "SYMBOLIC", "HOLD", "RULES", "SHOW",
  "REALNUM", "TYPEOF", "HELP", "ALIAS", "Id", "String", "Sort", "Alg",
  "Term", "La1", "La2", "La3", "La4", "La5", "Ru", "Ra", "Func", "Const",
  "Var", "Bra", "Bra1", "Bra2", "Terms", "Form", "Sorts", "Functs",
  "Forms", "Algs", "Cond2", "Cond", "'\\n'", "':'", "','", "'('", "')'",
  "';'", "'{'", "'}'", "$accept", "prog", "line", "definition", "idlist",
  "att", "$@1", "namedId", "PRECEDENCE", "condition", "condfunc",
  "instructions", "tinstructions", "oinstructions", "d_list",
  "instruction", "$@2", "aninstruction", "step", "prntexpr", "prntlist",
  "alglist", "Alg2", "sortlist", "vsortlist", "func", "funclist", "term",
  "termlist", "formula", "vinstr", "cformula", "formlist", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-306)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     429,   642,   642,   642,   642,   642,   -53,   -37,   516,   462,
     642,   642,     4,   642,   516,    -1,  -306,     7,   623,   -34,
       8,    12,   623,    20,    -2,    -2,    25,     0,  -306,   516,
     642,   623,   373,    26,    28,    31,    18,    29,    37,   623,
      39,   -19,    42,    44,  -306,    99,   516,   516,   516,   516,
     516,   548,    -5,  -306,   516,   516,   516,  -306,   328,  -306,
    -306,    22,    21,  -306,    23,  -306,   443,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,    36,    38,  -306,    45,  -306,    47,  -306,
      59,    67,  -306,    33,   531,  -306,    73,    74,    53,  -306,
     156,  -306,    64,    75,  -306,  -306,  -306,  -306,    65,  -306,
      76,    77,    78,   516,   429,    84,   429,  -306,   516,   443,
    -306,    85,  -306,   623,   167,    88,   180,   132,  -306,  -306,
     187,   190,  -306,   516,   516,   516,   516,   516,   548,   516,
     516,  -306,   443,   135,   191,   115,   540,   -27,    -6,    14,
     -12,   516,  -306,   516,   516,   342,   124,   123,   182,   429,
    -306,  -306,  -306,   429,   462,   516,   516,   516,   516,   516,
    -306,   516,   139,   642,   140,   150,   227,   480,   -28,   151,
     152,   131,   516,   141,   150,  -306,   516,   516,   516,   240,
     200,    -2,  -306,   148,   623,   233,   516,   181,   184,  -306,
     185,   196,  -306,   198,   516,   443,     9,   174,   443,   188,
     516,  -306,  -306,  -306,  -306,   173,   171,  -306,  -306,   540,
     -27,    -6,    14,   -12,   -12,  -306,  -306,  -306,   179,   239,
     272,    -2,  -306,   498,  -306,   199,   164,   250,  -306,  -306,
    -306,   -28,  -306,  -306,  -306,   216,   274,   150,   282,   223,
     224,   225,  -306,   429,  -306,   263,  -306,   516,   443,   283,
    -306,  -306,  -306,  -306,   616,  -306,  -306,  -306,  -306,   429,
     150,  -306,   256,   516,   244,   -28,   516,   429,  -306,   201,
     516,   327,   273,  -306,  -306,  -306,  -306,   248,   443,   278,
     -28,  -306,  -306,   128,   250,  -306,  -306,   443,  -306,   286,
     212,   285,   343,   516,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,   343,  -306,   261,   516,   326,   343,   576,
    -306,   262,  -306,   293,   443,   429,  -306,   604,   -28,  -306,
    -306,  -306,  -306,  -306,   642,  -306,  -306,   213,  -306,   271,
     275,   213,   429,  -306,  -306
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      72,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,     0,
     100,   102,   103,     0,     0,     0,    90,    92,    95,     0,
       0,     0,     0,     0,   109,   132,     0,     0,     0,     0,
       0,     0,   134,   136,     0,     0,     0,    66,    72,     2,
      65,     0,    57,    64,   110,    77,   108,    36,    40,    41,
      42,   121,   122,   123,   124,   125,   127,   126,   120,    37,
      38,   128,   129,     0,    27,    39,     0,    24,     0,    25,
       0,     0,   132,   134,     0,    79,     0,     0,     0,    75,
       0,    88,     0,     0,    81,    82,    80,    74,     0,    73,
       0,     0,     0,     0,    72,    51,    72,    78,     0,    97,
      99,   130,   101,     0,     0,     0,     0,     0,    89,    91,
       0,    14,    10,   121,   122,   123,   124,   125,   120,   128,
     129,    19,    18,     0,     0,     0,   140,   141,   142,   143,
     144,     0,   139,     0,     0,   154,     0,     0,     0,    72,
       1,     3,     4,    72,     0,     0,     0,     0,     0,     0,
     138,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    86,     0,     0,     0,     0,
      69,     0,    68,     0,     0,     0,     0,     0,     0,    93,
       0,     0,    20,     0,     0,    83,     0,     0,    85,     0,
       0,   145,   146,   137,    61,     0,    59,    58,   111,   148,
     149,   150,   151,   152,   153,    17,    28,     9,   116,   118,
       0,     0,   114,     0,    21,   112,     0,   157,   161,    22,
      23,     0,    76,    26,    16,     0,     0,     0,     0,     0,
       0,     0,    56,    72,    52,     0,   131,     0,   104,    12,
      15,    94,    13,    96,     0,   147,   135,   155,    67,    72,
       0,   119,     0,     0,     0,     0,     0,    72,   159,     0,
       0,     0,     0,    53,    54,    55,    70,     0,   105,     0,
       0,    60,   117,    43,   157,   115,   113,   156,   158,     0,
     106,     0,    29,     0,    11,    84,    44,    45,    46,    47,
      48,    50,    49,    29,   160,     0,     0,     0,    29,     0,
       6,     0,     5,     0,   107,    72,     8,     0,     0,    34,
      30,    87,     7,    71,     0,    31,    32,     0,    33,    62,
       0,     0,    72,    63,    35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -306,  -306,   334,  -305,    15,  -283,  -306,    -4,  -306,   -23,
    -306,  -148,   116,  -306,    52,  -111,  -306,  -306,  -306,  -306,
       3,  -172,  -306,   129,  -168,    -8,   207,    -7,   -47,   136,
     108,  -306,   249
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    58,    59,    60,    83,   320,   337,    84,   313,   114,
     115,    61,   215,   216,   340,    62,   159,    63,   317,    64,
      65,   274,   235,   229,   230,    85,   122,    66,   156,   237,
     278,   238,   239
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      88,    94,   116,   190,   234,   192,   242,   100,   157,    99,
     103,   214,    95,   153,   108,   217,   248,    86,    87,    16,
      89,    90,   119,   121,   124,    96,    97,   110,   111,   112,
     322,   131,   339,   141,   142,   326,   339,    91,   104,   146,
     147,   148,   149,   150,   152,   120,   232,   155,   155,   158,
     105,   167,   168,   169,   170,   171,    92,   133,   134,   135,
     136,   137,    76,    77,   138,    93,    53,   139,   140,   170,
     171,   193,   241,   168,   169,   170,   171,    98,   102,   281,
     106,    56,   154,   101,   107,   165,   166,   167,   168,   169,
     170,   171,   109,   157,   169,   170,   171,   117,   113,   125,
     118,   126,   128,   296,   207,   127,   189,   209,   210,   130,
     213,   155,   132,   129,   143,   195,   144,   145,   305,   162,
     154,   214,   164,   163,   181,   204,   146,   147,   148,   149,
     150,   152,   155,   155,   172,   183,   185,   173,   205,   249,
     250,   251,   286,   174,   206,   175,   208,   155,   306,   307,
     308,   309,   310,    16,   311,   312,   336,   176,   219,   220,
     221,   222,   223,   267,   224,   177,   298,   218,   254,   236,
     236,   179,   180,   184,   182,   246,   186,   187,   188,   155,
     155,   155,   276,   191,   194,   196,   121,   197,   226,   258,
      92,    46,    47,    48,    49,    50,   198,   264,    51,    93,
      53,    54,    55,   155,   199,   200,   201,   202,   273,   203,
     211,   212,   225,   227,   333,    56,     1,     2,     3,     4,
       5,     6,     7,   228,   243,   244,   158,    10,    11,    12,
     245,   344,   165,   166,   167,   168,   169,   170,   171,   247,
     165,   166,   167,   168,   169,   170,   171,   316,   253,   255,
     288,   257,    17,    18,   259,   260,   321,   261,   165,   166,
     167,   168,   169,   170,   171,    16,   236,   262,   269,   297,
     263,    33,    34,   300,   231,   265,   266,   268,   270,    39,
      40,    41,    42,   213,   271,   272,   277,   279,   165,   166,
     167,   168,   169,   170,   171,   282,   155,   287,   275,   289,
     299,   232,    92,    46,    47,    48,    49,    50,   280,   324,
      51,    93,    53,    54,    55,   330,   165,   166,   167,   168,
     169,   170,   171,   335,   283,   284,   285,   233,   160,   293,
     338,     1,     2,     3,     4,     5,     6,     7,     8,     9,
     301,   252,    10,    11,    12,   295,   302,    13,   303,   304,
     165,   166,   167,   168,   169,   170,   171,   315,   318,   319,
     323,    14,   325,   331,   332,    15,    16,    17,    18,    19,
      20,    21,    22,   341,    23,    24,   342,    25,    26,    27,
      28,    29,    30,    31,    32,   291,    33,    34,    35,    36,
      37,    38,   161,   343,    39,    40,    41,    42,    43,   292,
      44,   256,   314,    45,    46,    47,    48,    49,    50,   294,
       0,    51,    52,    53,    54,    55,     0,     0,   165,   166,
     167,   168,   169,   170,   171,     0,   240,     0,    56,     0,
     123,    57,     1,     2,     3,     4,     5,     6,     7,     8,
       9,   210,     0,    10,    11,    12,     0,     0,    13,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    81,
      82,     0,    14,     0,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,     0,    23,    24,     0,    25,    26,
      27,    28,    29,    30,    31,    32,     0,    33,    34,    35,
      36,    37,    38,     0,     0,    39,    40,    41,    42,    43,
      16,    44,     0,     0,    45,    46,    47,    48,    49,    50,
       0,     0,    51,    52,    53,    54,    55,     0,    16,   165,
     166,   167,   168,   169,   170,   171,     0,   231,     0,    56,
       0,     0,    57,     0,    44,     0,    16,    92,    46,    47,
      48,    49,    50,     0,     0,    51,    93,    53,    54,    55,
       0,     0,     0,     0,    16,    92,    46,    47,    48,    49,
      50,     0,    56,    51,    93,    53,    54,    55,     0,     0,
       0,     0,   232,    92,    46,    47,    48,    49,    50,     0,
      56,    51,    93,    53,    54,    55,    16,     0,     0,     0,
       0,    92,    46,    47,    48,    49,    50,     0,   233,    51,
      93,    53,    54,    55,     0,     0,     0,   165,   166,   167,
     168,   169,   170,   171,     0,     0,    56,   166,   167,   168,
     169,   170,   171,    92,    46,    47,    48,    49,    50,   178,
       0,    51,    93,    53,    54,    55,     0,     0,     0,   327,
       0,   328,     0,     0,     0,     0,     0,    67,   151,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,     0,     0,   334,     0,
       0,     0,     0,     0,     0,    67,   329,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,   165,   166,   167,   168,   169,   170,   171,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    81,
      82,     0,     0,    67,   290,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
       4,     8,    25,   114,   176,   116,   178,    14,    55,    13,
      18,   159,     9,    18,    22,   163,   184,     2,     3,    38,
       5,    74,    29,    31,    32,    10,    11,    29,    30,    31,
     313,    39,   337,    41,    41,   318,   341,    74,    72,    46,
      47,    48,    49,    50,    51,    30,    74,    54,    55,    56,
      84,    78,    79,    80,    81,    82,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    81,
      82,   118,   100,    79,    80,    81,    82,    73,    71,   247,
      72,   100,    87,    84,    72,    76,    77,    78,    79,    80,
      81,    82,    72,   140,    80,    81,    82,    72,   100,    73,
     100,    73,    84,   275,   151,    74,   113,   154,    99,    72,
     101,   118,    73,    84,    72,   123,    72,    18,   290,    97,
      87,   269,    99,   102,    71,    10,   133,   134,   135,   136,
     137,   138,   139,   140,    98,    71,    71,    99,   145,   186,
     187,   188,   253,    98,   151,    98,   153,   154,    20,    21,
      22,    23,    24,    38,    26,    27,   328,    98,   165,   166,
     167,   168,   169,   210,   171,    98,   277,   164,   191,   176,
     177,    98,    98,    98,    18,   182,   100,   100,   100,   186,
     187,   188,    18,    99,    99,    18,   194,    99,   173,   196,
      75,    76,    77,    78,    79,    80,    16,   204,    83,    84,
      85,    86,    87,   210,    72,    18,    16,    72,   231,    18,
      86,    88,    73,    73,   325,   100,     3,     4,     5,     6,
       7,     8,     9,    73,    73,    73,   233,    14,    15,    16,
      99,   342,    76,    77,    78,    79,    80,    81,    82,    98,
      76,    77,    78,    79,    80,    81,    82,    35,    48,   101,
     257,    18,    39,    40,    73,    71,   303,    72,    76,    77,
      78,    79,    80,    81,    82,    38,   273,    71,    97,   276,
      72,    58,    59,   280,    47,   101,    88,   104,    99,    66,
      67,    68,    69,   101,    45,    13,    36,    71,    76,    77,
      78,    79,    80,    81,    82,    13,   303,    34,    99,    16,
      99,    74,    75,    76,    77,    78,    79,    80,    34,   316,
      83,    84,    85,    86,    87,   319,    76,    77,    78,    79,
      80,    81,    82,   327,   101,   101,   101,   100,     0,    73,
     334,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      13,   101,    14,    15,    16,   101,    73,    19,   100,    71,
      76,    77,    78,    79,    80,    81,    82,    71,    73,    16,
      99,    33,    36,   101,    71,    37,    38,    39,    40,    41,
      42,    43,    44,   102,    46,    47,   101,    49,    50,    51,
      52,    53,    54,    55,    56,   269,    58,    59,    60,    61,
      62,    63,    58,   341,    66,    67,    68,    69,    70,   270,
      72,   194,   294,    75,    76,    77,    78,    79,    80,   273,
      -1,    83,    84,    85,    86,    87,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    -1,   177,    -1,   100,    -1,
      57,   103,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    99,    -1,    14,    15,    16,    -1,    -1,    19,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    86,
      87,    -1,    33,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      38,    72,    -1,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    83,    84,    85,    86,    87,    -1,    38,    76,
      77,    78,    79,    80,    81,    82,    -1,    47,    -1,   100,
      -1,    -1,   103,    -1,    72,    -1,    38,    75,    76,    77,
      78,    79,    80,    -1,    -1,    83,    84,    85,    86,    87,
      -1,    -1,    -1,    -1,    38,    75,    76,    77,    78,    79,
      80,    -1,   100,    83,    84,    85,    86,    87,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    -1,
     100,    83,    84,    85,    86,    87,    38,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,   100,    83,
      84,    85,    86,    87,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,   100,    77,    78,    79,
      80,    81,    82,    75,    76,    77,    78,    79,    80,    98,
      -1,    83,    84,    85,    86,    87,    -1,    -1,    -1,    63,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    71,   100,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    71,   100,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    76,    77,    78,    79,    80,    81,    82,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    86,
      87,    -1,    -1,    71,    98,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    58,    59,    60,    61,    62,    63,    66,
      67,    68,    69,    70,    72,    75,    76,    77,    78,    79,
      80,    83,    84,    85,    86,    87,   100,   103,   106,   107,
     108,   116,   120,   122,   124,   125,   132,    71,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,   109,   112,   130,   109,   109,   112,   109,
      74,    74,    75,    84,   132,   125,   109,   109,    73,   112,
     132,    84,    71,   130,    72,    84,    72,    72,   130,    72,
      29,    30,    31,   100,   114,   115,   114,    72,   100,   132,
     109,   130,   131,    57,   130,    73,    73,    74,    84,    84,
      72,   130,    73,    76,    77,    78,    79,    80,    83,    86,
      87,   130,   132,    72,    72,    18,   132,   132,   132,   132,
     132,   100,   132,    18,    87,   132,   133,   133,   132,   121,
       0,   107,    97,   102,    99,    76,    77,    78,    79,    80,
      81,    82,    98,    99,    98,    98,    98,    98,    98,    98,
      98,    71,    18,    71,    98,    71,   100,   100,   100,   132,
     120,    99,   120,   133,    99,   130,    18,    99,    16,    72,
      18,    16,    72,    18,    10,   132,   132,   133,   132,   133,
      99,    86,    88,   101,   116,   117,   118,   116,   125,   132,
     132,   132,   132,   132,   132,    73,   109,    73,    73,   128,
     129,    47,    74,   100,   126,   127,   132,   134,   136,   137,
     137,   100,   126,    73,    73,    99,   132,    98,   129,   133,
     133,   133,   101,    48,   114,   101,   131,    18,   132,    73,
      71,    72,    71,    72,   132,   101,    88,   133,   104,    97,
      99,    45,    13,   114,   126,    99,    18,    36,   135,    71,
      34,   129,    13,   101,   101,   101,   120,    34,   132,    16,
      98,   117,   128,    73,   134,   101,   126,   132,   120,    99,
     132,    13,    73,   100,    71,   126,    20,    21,    22,    23,
      24,    26,    27,   113,   135,    71,    35,   123,    73,    16,
     110,   133,   110,    99,   132,    36,   110,    63,    65,   100,
     112,   101,    71,   120,    64,   112,   126,   111,   112,   108,
     119,   102,   101,   119,   120
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   105,   106,   106,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   109,   109,   110,
     110,   110,   110,   110,   111,   110,   112,   112,   112,   112,
     112,   112,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   114,   114,   115,   115,   115,   115,   116,   116,   117,
     117,   118,   119,   119,   120,   120,   121,   120,   120,   120,
     120,   120,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   123,   123,   124,   124,
     125,   125,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   133,   133,   134,   135,   135,   136,
     136,   137
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     8,     7,     9,     8,     4,
       2,     6,     4,     4,     2,     4,     4,     4,     2,     2,
       3,     4,     4,     4,     2,     2,     4,     1,     3,     0,
       2,     3,     3,     4,     0,     6,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     4,     4,     4,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     0,     4,     3,     3,
       5,     9,     0,     2,     2,     2,     4,     1,     2,     2,
       2,     2,     2,     3,     6,     3,     3,     8,     2,     2,
       1,     2,     1,     3,     4,     1,     4,     2,     1,     2,
       1,     2,     1,     1,     4,     5,     0,     2,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     4,     1,     3,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     4,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     0,     2,     2,
       4,     1
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
#line 89 "syn.y"
                                    {Node * temp;
														if ((yyvsp[-1].y_nod)) { temp = mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod));
															is_running();
															CALLFUNCT(temp);
															is_not_running();
															delete(temp);}
														}
#line 1559 "syn.tab.c"
    break;

  case 5: /* definition: FUNC namedId ':' vsortlist PFEIL Sort PRECEDENCE att  */
#line 97 "syn.y"
                                                                       {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fn,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1567 "syn.tab.c"
    break;

  case 6: /* definition: OTHER func ':' vsortlist PFEIL Sort att  */
#line 100 "syn.y"
                                                                  { (yyval.y_nod)=mknod(FUNC,(Node *) other_fn,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1576 "syn.tab.c"
    break;

  case 7: /* definition: ATT Sort Id ',' Id ',' Id ',' Id  */
#line 104 "syn.y"
                                                           { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufn(name((yyvsp[0].y_sym))))))));	}
#line 1587 "syn.tab.c"
    break;

  case 8: /* definition: BRA Id Id ':' vsortlist PFEIL Sort att  */
#line 110 "syn.y"
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
#line 1603 "syn.tab.c"
    break;

  case 9: /* definition: PAT idlist ':' Sort  */
#line 121 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1609 "syn.tab.c"
    break;

  case 10: /* definition: REALNUM Sort  */
#line 122 "syn.y"
                                                                                 {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* sets numbertype for mknum */}
#line 1615 "syn.tab.c"
    break;

  case 11: /* definition: SUBSORT Sort ',' Sort ATT Id  */
#line 123 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort */
										      mknod(PARAM,(Node *) (yyvsp[-4].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufn(name((yyvsp[0].y_sym))))));}
#line 1622 "syn.tab.c"
    break;

  case 12: /* definition: SUBSORT Sort ',' Sort  */
#line 125 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort of a sort without values */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),mknod(PARAM,(Node *) (yyvsp[0].y_sym),NULL)));}
#line 1629 "syn.tab.c"
    break;

  case 13: /* definition: SHOW func ATT Id  */
#line 127 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) show_def,      /* 2026: print function */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) give_pfn(name((yyvsp[0].y_sym)))));}
#line 1636 "syn.tab.c"
    break;

  case 14: /* definition: SHOW func  */
#line 129 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) show_def,      /* 2026: the usual printing again */
										      mknod(PARAM,(Node *) (yyvsp[0].y_nod),NULL));}
#line 1643 "syn.tab.c"
    break;

  case 15: /* definition: INTNUM Sort ATT Id  */
#line 131 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) intnum_def,    /* 2026: sort of integers */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufn(name((yyvsp[0].y_sym)))));}
#line 1650 "syn.tab.c"
    break;

  case 16: /* definition: NUMPAT idlist ':' Sort  */
#line 133 "syn.y"
                                                                 { /* pattern variables for numbers */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1657 "syn.tab.c"
    break;

  case 17: /* definition: SYM idlist ':' Sort  */
#line 135 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1663 "syn.tab.c"
    break;

  case 18: /* definition: TYPEOF term  */
#line 136 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) typeof_fn,(yyvsp[0].y_nod));}
#line 1669 "syn.tab.c"
    break;

  case 19: /* definition: TYPEOF func  */
#line 137 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) typeof_func,(Node *) (yyvsp[0].y_nod));}
#line 1675 "syn.tab.c"
    break;

  case 20: /* definition: HELP String String  */
#line 138 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) help_def,mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 1681 "syn.tab.c"
    break;

  case 21: /* definition: SPEC Alg ':' alglist  */
#line 139 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1687 "syn.tab.c"
    break;

  case 22: /* definition: SPEC Alg ':' formlist  */
#line 140 "syn.y"
                                                         {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1693 "syn.tab.c"
    break;

  case 23: /* definition: ADDSPEC Alg ':' formlist  */
#line 141 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1699 "syn.tab.c"
    break;

  case 24: /* definition: SORT idlist  */
#line 142 "syn.y"
                                                                             {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1705 "syn.tab.c"
    break;

  case 25: /* definition: ALG idlist  */
#line 144 "syn.y"
                                                     {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1711 "syn.tab.c"
    break;

  case 26: /* definition: TERM idlist ':' Sort  */
#line 145 "syn.y"
                                                   {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1717 "syn.tab.c"
    break;

  case 27: /* idlist: namedId  */
#line 147 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1723 "syn.tab.c"
    break;

  case 28: /* idlist: namedId ',' idlist  */
#line 148 "syn.y"
                                                        {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1729 "syn.tab.c"
    break;

  case 29: /* att: %empty  */
#line 156 "syn.y"
                                        { (yyval.y_nod) = NULL;}
#line 1735 "syn.tab.c"
    break;

  case 30: /* att: ATT namedId  */
#line 157 "syn.y"
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
#line 1751 "syn.tab.c"
    break;

  case 31: /* att: ATT SYMBOLIC namedId  */
#line 168 "syn.y"
                                                        { /* 2026: symbolic C function (symfn.c): gets terms */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 0); }
#line 1758 "syn.tab.c"
    break;

  case 32: /* att: ATT RULES alglist  */
#line 170 "syn.y"
                                                { /* 2026: function defined by a rule list: f(..) is REWR f(..) : alglist */
			                  (yyval.y_nod) = mknod(ATT,(Node *) rules_sfn(),mknod(PARAM,(yyvsp[0].y_nod),NULL)); }
#line 1765 "syn.tab.c"
    break;

  case 33: /* att: ATT SYMBOLIC HOLD namedId  */
#line 172 "syn.y"
                                                        { /* 2026: plus arguments unevaluated (matchq) */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 1); }
#line 1772 "syn.tab.c"
    break;

  case 34: /* $@1: %empty  */
#line 174 "syn.y"
                                          {block_begin();no_protect();}
#line 1778 "syn.tab.c"
    break;

  case 35: /* att: ATT '(' $@1 d_list ')' instruction  */
#line 175 "syn.y"
                                                                                        {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1784 "syn.tab.c"
    break;

  case 36: /* namedId: Id  */
#line 177 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1790 "syn.tab.c"
    break;

  case 37: /* namedId: Const  */
#line 178 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1796 "syn.tab.c"
    break;

  case 38: /* namedId: Var  */
#line 179 "syn.y"
                         { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1802 "syn.tab.c"
    break;

  case 39: /* namedId: func  */
#line 180 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1808 "syn.tab.c"
    break;

  case 40: /* namedId: Sort  */
#line 181 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1814 "syn.tab.c"
    break;

  case 41: /* namedId: Alg  */
#line 182 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1820 "syn.tab.c"
    break;

  case 42: /* namedId: Term  */
#line 183 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1826 "syn.tab.c"
    break;

  case 43: /* PRECEDENCE: %empty  */
#line 186 "syn.y"
                                                                {(yyval.y_int) = Func;}
#line 1832 "syn.tab.c"
    break;

  case 44: /* PRECEDENCE: LA1  */
#line 187 "syn.y"
                                                                        {(yyval.y_int) = La1;	/* Left-associative */}
#line 1838 "syn.tab.c"
    break;

  case 45: /* PRECEDENCE: LA2  */
#line 188 "syn.y"
                                                                        {(yyval.y_int) = La2;	/* Left-associative */}
#line 1844 "syn.tab.c"
    break;

  case 46: /* PRECEDENCE: LA3  */
#line 189 "syn.y"
                                                                        {(yyval.y_int) = La3;	/* Left-associative */}
#line 1850 "syn.tab.c"
    break;

  case 47: /* PRECEDENCE: LA4  */
#line 190 "syn.y"
                                                                        {(yyval.y_int) = La4;	/* Left-associative */}
#line 1856 "syn.tab.c"
    break;

  case 48: /* PRECEDENCE: LA5  */
#line 191 "syn.y"
                                                                        {(yyval.y_int) = La5;	/* Left-associative */}
#line 1862 "syn.tab.c"
    break;

  case 49: /* PRECEDENCE: RA  */
#line 192 "syn.y"
                                                                        {(yyval.y_int) = Ra;  	/* Right-associative */}
#line 1868 "syn.tab.c"
    break;

  case 50: /* PRECEDENCE: RU  */
#line 193 "syn.y"
                                                                        {(yyval.y_int) = Ru;	  /* Right unary */}
#line 1874 "syn.tab.c"
    break;

  case 51: /* condition: condfunc  */
#line 195 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1880 "syn.tab.c"
    break;

  case 52: /* condition: condfunc ',' condition  */
#line 196 "syn.y"
                                                        {(yyval.y_nod) = mknod(Cond,(Node *) and_cond,mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod)));}
#line 1886 "syn.tab.c"
    break;

  case 53: /* condfunc: LB '(' termlist ')'  */
#line 198 "syn.y"
                              {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1892 "syn.tab.c"
    break;

  case 54: /* condfunc: IN '(' termlist ')'  */
#line 199 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1898 "syn.tab.c"
    break;

  case 55: /* condfunc: NIN '(' termlist ')'  */
#line 200 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1904 "syn.tab.c"
    break;

  case 56: /* condfunc: '(' term ')'  */
#line 201 "syn.y"
                                                                        {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1910 "syn.tab.c"
    break;

  case 57: /* instructions: instruction  */
#line 203 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1916 "syn.tab.c"
    break;

  case 58: /* instructions: instruction ';' instructions  */
#line 204 "syn.y"
                                                                                       {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1922 "syn.tab.c"
    break;

  case 59: /* tinstructions: oinstructions  */
#line 206 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1928 "syn.tab.c"
    break;

  case 60: /* tinstructions: oinstructions '\n' tinstructions  */
#line 207 "syn.y"
                                                                                                                {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1934 "syn.tab.c"
    break;

  case 61: /* oinstructions: instructions  */
#line 209 "syn.y"
                                                {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1940 "syn.tab.c"
    break;

  case 62: /* d_list: definition  */
#line 214 "syn.y"
                                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1946 "syn.tab.c"
    break;

  case 63: /* d_list: definition ';' d_list  */
#line 215 "syn.y"
                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1952 "syn.tab.c"
    break;

  case 64: /* instruction: aninstruction  */
#line 217 "syn.y"
                                {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Check local variables ! */ }
#line 1958 "syn.tab.c"
    break;

  case 65: /* instruction: definition  */
#line 218 "syn.y"
                                                                        {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1964 "syn.tab.c"
    break;

  case 66: /* $@2: %empty  */
#line 219 "syn.y"
                                                                                                        {block_begin();no_protect();}
#line 1970 "syn.tab.c"
    break;

  case 67: /* instruction: '{' $@2 tinstructions '}'  */
#line 220 "syn.y"
                                                                        {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 1980 "syn.tab.c"
    break;

  case 68: /* instruction: WHILE condition instruction  */
#line 225 "syn.y"
                                                        {Node * memo,* rtw=in_block_instruct(memo=mknod(FUNC,(Node *) while_fn,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* then becomes $3 */)));
																		WHILE_BODY(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1987 "syn.tab.c"
    break;

  case 69: /* instruction: IF condition instruction  */
#line 228 "syn.y"
                                                        {Node * memo,* rtw=in_block_instruct(memo=mknod(FUNC,(Node *) if_fn,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		IF_THEN(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1994 "syn.tab.c"
    break;

  case 70: /* instruction: IF condition instruction ELSE instruction  */
#line 230 "syn.y"
                                                                        {Node * memo,* rtw = in_block_instruct(memo=mknod(FUNC,(Node *) if_fn,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(memo) = (yyvsp[-2].y_nod);IF_ELSE(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 2001 "syn.tab.c"
    break;

  case 71: /* instruction: FOR term EQ term TO term step DO instruction  */
#line 233 "syn.y"
                                                                                                                {Node * memo,* rtw = in_block_instruct(memo=mknod(FUNC,(Node *) for_loop,
																mknod(PARAM,
																	mknod(PARAM,(yyvsp[-5].y_nod),(yyvsp[-3].y_nod)),
																	mknod(PARAM,
																		mknod(PARAM,(yyvsp[-2].y_nod),(Node *) ((yyvsp[-7].y_nod))),
																		NULL /* $9 */) )));	
														FOR_BODY(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 2013 "syn.tab.c"
    break;

  case 72: /* aninstruction: %empty  */
#line 242 "syn.y"
                                        {(yyval.y_nod)=NULL;}
#line 2019 "syn.tab.c"
    break;

  case 73: /* aninstruction: SYS String  */
#line 243 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) system_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2025 "syn.tab.c"
    break;

  case 74: /* aninstruction: INC String  */
#line 244 "syn.y"
                                                                        {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fn,(Node *) ((yyvsp[0].y_sym))); }
#line 2031 "syn.tab.c"
    break;

  case 75: /* aninstruction: INFO namedId  */
#line 245 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) info_fn,(Node *) ((yyvsp[0].y_nod))); }
#line 2037 "syn.tab.c"
    break;

  case 76: /* aninstruction: REWR term ':' alglist  */
#line 246 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fn,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 2044 "syn.tab.c"
    break;

  case 77: /* aninstruction: prntlist  */
#line 248 "syn.y"
                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 2050 "syn.tab.c"
    break;

  case 78: /* aninstruction: PRTNUM String  */
#line 249 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 2056 "syn.tab.c"
    break;

  case 79: /* aninstruction: PRT prntlist  */
#line 250 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* without \n */ }
#line 2062 "syn.tab.c"
    break;

  case 80: /* aninstruction: OUT String  */
#line 251 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 2068 "syn.tab.c"
    break;

  case 81: /* aninstruction: DATA String  */
#line 252 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 2074 "syn.tab.c"
    break;

  case 82: /* aninstruction: DATA Const  */
#line 253 "syn.y"
                                                                        {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 2085 "syn.tab.c"
    break;

  case 83: /* aninstruction: Term EQ term  */
#line 259 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 2091 "syn.tab.c"
    break;

  case 84: /* aninstruction: Term EQ REWR term ':' alglist  */
#line 260 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fn,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 2097 "syn.tab.c"
    break;

  case 85: /* aninstruction: Const EQ term  */
#line 261 "syn.y"
                                                        { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 2103 "syn.tab.c"
    break;

  case 86: /* aninstruction: EXE func Id  */
#line 262 "syn.y"
                                                        {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufn(name((yyvsp[0].y_sym)));
 													}
#line 2113 "syn.tab.c"
    break;

  case 87: /* aninstruction: LIFT '(' termlist ')' TO '(' termlist ')'  */
#line 267 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 2119 "syn.tab.c"
    break;

  case 88: /* aninstruction: DBG Const  */
#line 268 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 2125 "syn.tab.c"
    break;

  case 89: /* aninstruction: MAXSTEPS Const  */
#line 269 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) maxsteps_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2131 "syn.tab.c"
    break;

  case 90: /* aninstruction: MAXSTEPS  */
#line 270 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) maxsteps_fn,NULL);}
#line 2137 "syn.tab.c"
    break;

  case 91: /* aninstruction: MAXDEPTH Const  */
#line 271 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) maxdepth_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2143 "syn.tab.c"
    break;

  case 92: /* aninstruction: MAXDEPTH  */
#line 272 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) maxdepth_fn,NULL);}
#line 2149 "syn.tab.c"
    break;

  case 93: /* aninstruction: STEPS Alg String  */
#line 273 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) steps_fn,mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2155 "syn.tab.c"
    break;

  case 94: /* aninstruction: SYMBOLIC String EQ String  */
#line 274 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fn,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2161 "syn.tab.c"
    break;

  case 95: /* aninstruction: SYMBOLIC  */
#line 275 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fn,NULL);  /* delete roles */}
#line 2167 "syn.tab.c"
    break;

  case 96: /* aninstruction: ALIAS String EQ String  */
#line 276 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) alias_fn,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2173 "syn.tab.c"
    break;

  case 97: /* aninstruction: RETURN term  */
#line 277 "syn.y"
                                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) return_fn,(yyvsp[0].y_nod));}
#line 2179 "syn.tab.c"
    break;

  case 98: /* aninstruction: QUIT  */
#line 278 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fn,NULL);}
#line 2185 "syn.tab.c"
    break;

  case 99: /* aninstruction: OPT idlist  */
#line 279 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fn,(yyvsp[0].y_nod));}
#line 2191 "syn.tab.c"
    break;

  case 100: /* aninstruction: OPT  */
#line 280 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fn,NULL);   /* delete */}
#line 2197 "syn.tab.c"
    break;

  case 101: /* aninstruction: COMM funclist  */
#line 281 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fn,(yyvsp[0].y_nod));}
#line 2203 "syn.tab.c"
    break;

  case 102: /* aninstruction: COMM  */
#line 282 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fn,NULL);  /* delete */}
#line 2209 "syn.tab.c"
    break;

  case 103: /* aninstruction: DEFAULT  */
#line 283 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,NULL); /* delete */}
#line 2215 "syn.tab.c"
    break;

  case 104: /* aninstruction: DEFAULT func EQ term  */
#line 284 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),NULL),(yyvsp[0].y_nod)));}
#line 2222 "syn.tab.c"
    break;

  case 105: /* aninstruction: DEFAULT RIGHT func EQ term  */
#line 286 "syn.y"
                                                     {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),mknod(PARAM,NULL,NULL)),(yyvsp[0].y_nod)));}
#line 2229 "syn.tab.c"
    break;

  case 106: /* step: %empty  */
#line 289 "syn.y"
                        {(yyval.y_nod)=(Node *) NULL;}
#line 2235 "syn.tab.c"
    break;

  case 107: /* step: STEP term  */
#line 290 "syn.y"
                                        {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2241 "syn.tab.c"
    break;

  case 108: /* prntexpr: term  */
#line 292 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2247 "syn.tab.c"
    break;

  case 109: /* prntexpr: String  */
#line 293 "syn.y"
                                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2253 "syn.tab.c"
    break;

  case 110: /* prntlist: prntexpr  */
#line 295 "syn.y"
                                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2259 "syn.tab.c"
    break;

  case 111: /* prntlist: prntexpr ',' prntlist  */
#line 296 "syn.y"
                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2265 "syn.tab.c"
    break;

  case 112: /* alglist: Alg2  */
#line 298 "syn.y"
                                                                {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2271 "syn.tab.c"
    break;

  case 113: /* alglist: Alg2 ',' alglist  */
#line 299 "syn.y"
                                                        {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2277 "syn.tab.c"
    break;

  case 114: /* Alg2: Alg  */
#line 301 "syn.y"
                                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2283 "syn.tab.c"
    break;

  case 115: /* Alg2: '(' alglist ')'  */
#line 302 "syn.y"
                                                                {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2289 "syn.tab.c"
    break;

  case 116: /* sortlist: Sort  */
#line 304 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2295 "syn.tab.c"
    break;

  case 117: /* sortlist: Sort ',' sortlist  */
#line 305 "syn.y"
                                                                {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2301 "syn.tab.c"
    break;

  case 118: /* vsortlist: sortlist  */
#line 307 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2307 "syn.tab.c"
    break;

  case 119: /* vsortlist: sortlist VARPAR  */
#line 308 "syn.y"
                                                                        {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2313 "syn.tab.c"
    break;

  case 120: /* func: Func  */
#line 310 "syn.y"
                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2319 "syn.tab.c"
    break;

  case 121: /* func: La1  */
#line 311 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2325 "syn.tab.c"
    break;

  case 122: /* func: La2  */
#line 312 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2331 "syn.tab.c"
    break;

  case 123: /* func: La3  */
#line 313 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2337 "syn.tab.c"
    break;

  case 124: /* func: La4  */
#line 314 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2343 "syn.tab.c"
    break;

  case 125: /* func: La5  */
#line 315 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2349 "syn.tab.c"
    break;

  case 126: /* func: Ra  */
#line 316 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2355 "syn.tab.c"
    break;

  case 127: /* func: Ru  */
#line 317 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2361 "syn.tab.c"
    break;

  case 128: /* func: Bra  */
#line 318 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2367 "syn.tab.c"
    break;

  case 129: /* func: Bra1  */
#line 319 "syn.y"
                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2373 "syn.tab.c"
    break;

  case 130: /* funclist: func  */
#line 321 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2379 "syn.tab.c"
    break;

  case 131: /* funclist: func ',' funclist  */
#line 322 "syn.y"
                                                        {(yyval.y_nod) = mknod(Functs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2385 "syn.tab.c"
    break;

  case 132: /* term: Term  */
#line 324 "syn.y"
                                                                        {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); does not remember dependencies and does not work in blocks */ 
														}
#line 2392 "syn.tab.c"
    break;

  case 133: /* term: LAST  */
#line 326 "syn.y"
                                                                                        {(yyval.y_nod) = (Node *) lastterm;}
#line 2398 "syn.tab.c"
    break;

  case 134: /* term: Const  */
#line 327 "syn.y"
                                                                                        {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2404 "syn.tab.c"
    break;

  case 135: /* term: Const Bra1 termlist Bra2  */
#line 328 "syn.y"
                                                   {np_aux=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),np_aux), np_aux);}
#line 2411 "syn.tab.c"
    break;

  case 136: /* term: Var  */
#line 330 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2417 "syn.tab.c"
    break;

  case 137: /* term: '(' term ')'  */
#line 331 "syn.y"
                                                    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2423 "syn.tab.c"
    break;

  case 138: /* term: term Ru  */
#line 332 "syn.y"
                                                                      {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2429 "syn.tab.c"
    break;

  case 139: /* term: Func term  */
#line 333 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2435 "syn.tab.c"
    break;

  case 140: /* term: La1 term  */
#line 334 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2441 "syn.tab.c"
    break;

  case 141: /* term: La2 term  */
#line 335 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2447 "syn.tab.c"
    break;

  case 142: /* term: La3 term  */
#line 336 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2453 "syn.tab.c"
    break;

  case 143: /* term: La4 term  */
#line 337 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2459 "syn.tab.c"
    break;

  case 144: /* term: La5 term  */
#line 338 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2465 "syn.tab.c"
    break;

  case 145: /* term: Bra termlist Bra  */
#line 339 "syn.y"
                                                  {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2471 "syn.tab.c"
    break;

  case 146: /* term: Bra1 termlist Bra2  */
#line 340 "syn.y"
                                                {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2477 "syn.tab.c"
    break;

  case 147: /* term: Func '(' termlist ')'  */
#line 341 "syn.y"
                                                        {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2483 "syn.tab.c"
    break;

  case 148: /* term: term La1 term  */
#line 342 "syn.y"
                                                    {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2490 "syn.tab.c"
    break;

  case 149: /* term: term La2 term  */
#line 344 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2497 "syn.tab.c"
    break;

  case 150: /* term: term La3 term  */
#line 346 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2504 "syn.tab.c"
    break;

  case 151: /* term: term La4 term  */
#line 348 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2511 "syn.tab.c"
    break;

  case 152: /* term: term La5 term  */
#line 350 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2518 "syn.tab.c"
    break;

  case 153: /* term: term Ra term  */
#line 352 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2525 "syn.tab.c"
    break;

  case 154: /* termlist: term  */
#line 355 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2531 "syn.tab.c"
    break;

  case 155: /* termlist: term ',' termlist  */
#line 356 "syn.y"
                                                        {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2537 "syn.tab.c"
    break;

  case 156: /* formula: term EQ term  */
#line 358 "syn.y"
                                        {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2543 "syn.tab.c"
    break;

  case 157: /* vinstr: %empty  */
#line 360 "syn.y"
                                                                {(yyval.y_nod) = NULL;}
#line 2549 "syn.tab.c"
    break;

  case 158: /* vinstr: DO instruction  */
#line 361 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2555 "syn.tab.c"
    break;

  case 159: /* cformula: formula vinstr  */
#line 363 "syn.y"
                                                                        {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2562 "syn.tab.c"
    break;

  case 160: /* cformula: IF condition formula vinstr  */
#line 365 "syn.y"
                                               {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2569 "syn.tab.c"
    break;

  case 161: /* formlist: cformula  */
#line 368 "syn.y"
                                                                {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL serves for hooking in further formulas !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. because of SPEC real : A+B=C;a=3 */
															}
#line 2577 "syn.tab.c"
    break;


#line 2581 "syn.tab.c"

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

#line 372 "syn.y"


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
