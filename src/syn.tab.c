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
#include "userfkt.h"
#include "nodes.h"
#include "expand.h"
#include "symfkt.h"
#include "numsort.h"

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
  YYSYMBOL_CST = 3,                        /* CST  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
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
  YYSYMBOL_NUM = 15,                       /* NUM  */
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
  YYSYMBOL_KOMMU = 28,                     /* KOMMU  */
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
  YYSYMBOL_Id = 65,                        /* Id  */
  YYSYMBOL_String = 66,                    /* String  */
  YYSYMBOL_Sort = 67,                      /* Sort  */
  YYSYMBOL_Alg = 68,                       /* Alg  */
  YYSYMBOL_Term = 69,                      /* Term  */
  YYSYMBOL_La1 = 70,                       /* La1  */
  YYSYMBOL_La2 = 71,                       /* La2  */
  YYSYMBOL_La3 = 72,                       /* La3  */
  YYSYMBOL_La4 = 73,                       /* La4  */
  YYSYMBOL_La5 = 74,                       /* La5  */
  YYSYMBOL_Ru = 75,                        /* Ru  */
  YYSYMBOL_Ra = 76,                        /* Ra  */
  YYSYMBOL_Func = 77,                      /* Func  */
  YYSYMBOL_Const = 78,                     /* Const  */
  YYSYMBOL_Var = 79,                       /* Var  */
  YYSYMBOL_Bra = 80,                       /* Bra  */
  YYSYMBOL_Bra1 = 81,                      /* Bra1  */
  YYSYMBOL_Bra2 = 82,                      /* Bra2  */
  YYSYMBOL_Terms = 83,                     /* Terms  */
  YYSYMBOL_Form = 84,                      /* Form  */
  YYSYMBOL_Sorts = 85,                     /* Sorts  */
  YYSYMBOL_Functs = 86,                    /* Functs  */
  YYSYMBOL_Forms = 87,                     /* Forms  */
  YYSYMBOL_Algs = 88,                      /* Algs  */
  YYSYMBOL_Cond2 = 89,                     /* Cond2  */
  YYSYMBOL_Cond = 90,                      /* Cond  */
  YYSYMBOL_91_n_ = 91,                     /* '\n'  */
  YYSYMBOL_92_ = 92,                       /* ':'  */
  YYSYMBOL_93_ = 93,                       /* ','  */
  YYSYMBOL_94_ = 94,                       /* '('  */
  YYSYMBOL_95_ = 95,                       /* ')'  */
  YYSYMBOL_96_ = 96,                       /* ';'  */
  YYSYMBOL_97_ = 97,                       /* '{'  */
  YYSYMBOL_98_ = 98,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 99,                  /* $accept  */
  YYSYMBOL_prog = 100,                     /* prog  */
  YYSYMBOL_line = 101,                     /* line  */
  YYSYMBOL_definition = 102,               /* definition  */
  YYSYMBOL_idlist = 103,                   /* idlist  */
  YYSYMBOL_att = 104,                      /* att  */
  YYSYMBOL_105_1 = 105,                    /* $@1  */
  YYSYMBOL_namedId = 106,                  /* namedId  */
  YYSYMBOL_VORRANG = 107,                  /* VORRANG  */
  YYSYMBOL_condition = 108,                /* condition  */
  YYSYMBOL_condfunc = 109,                 /* condfunc  */
  YYSYMBOL_instructions = 110,             /* instructions  */
  YYSYMBOL_tinstructions = 111,            /* tinstructions  */
  YYSYMBOL_oinstructions = 112,            /* oinstructions  */
  YYSYMBOL_d_list = 113,                   /* d_list  */
  YYSYMBOL_instruction = 114,              /* instruction  */
  YYSYMBOL_115_2 = 115,                    /* $@2  */
  YYSYMBOL_aninstruction = 116,            /* aninstruction  */
  YYSYMBOL_step = 117,                     /* step  */
  YYSYMBOL_prntexpr = 118,                 /* prntexpr  */
  YYSYMBOL_prntlist = 119,                 /* prntlist  */
  YYSYMBOL_alglist = 120,                  /* alglist  */
  YYSYMBOL_Alg2 = 121,                     /* Alg2  */
  YYSYMBOL_sortlist = 122,                 /* sortlist  */
  YYSYMBOL_vsortlist = 123,                /* vsortlist  */
  YYSYMBOL_func = 124,                     /* func  */
  YYSYMBOL_funclist = 125,                 /* funclist  */
  YYSYMBOL_term = 126,                     /* term  */
  YYSYMBOL_termlist = 127,                 /* termlist  */
  YYSYMBOL_formula = 128,                  /* formula  */
  YYSYMBOL_vinstr = 129,                   /* vinstr  */
  YYSYMBOL_cformula = 130,                 /* cformula  */
  YYSYMBOL_formlist = 131                  /* formlist  */
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
#define YYFINAL  140
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   680

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  99
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  152
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  322

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   345


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
      91,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      94,    95,     2,     2,    93,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    92,    96,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    97,     2,    98,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    85,    85,    86,    88,    96,    99,   103,   109,   120,
     121,   122,   124,   126,   128,   130,   132,   133,   134,   135,
     136,   138,   139,   141,   142,   150,   151,   162,   164,   166,
     168,   168,   171,   172,   173,   174,   175,   176,   177,   180,
     181,   182,   183,   184,   185,   186,   187,   189,   190,   192,
     193,   194,   195,   197,   198,   200,   201,   203,   208,   209,
     211,   212,   213,   213,   219,   222,   224,   226,   236,   237,
     238,   239,   240,   242,   243,   244,   245,   246,   247,   253,
     254,   255,   256,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   275,   278,   279,   281,
     282,   284,   285,   287,   288,   290,   291,   293,   294,   296,
     297,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   310,   311,   313,   315,   316,   317,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     333,   335,   337,   339,   341,   344,   345,   347,   349,   350,
     352,   354,   357
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
  "\"end of file\"", "error", "\"invalid token\"", "CST", "VAR", "SORT",
  "FUNC", "ALG", "SPEC", "ADDSPEC", "REWR", "PRT", "GRAPH", "PFEIL",
  "TERM", "NUM", "ATT", "IS", "EQ", "INFO", "LA1", "LA2", "LA3", "LA4",
  "LA5", "LOCAL", "RU", "RA", "KOMMU", "LB", "IN", "NIN", "PARAM", "FOR",
  "TO", "STEP", "DO", "DBG", "LAST", "BRA", "OTHER", "DATA", "OUT", "INC",
  "EXE", "VARPAR", "SYS", "IF", "ELSE", "WHILE", "PRTNUM", "LIFT", "QUIT",
  "RETURN", "OPT", "COMM", "DEFAULT", "RIGHT", "SUBSORT", "INTNUM",
  "STEPS", "SYMBOLIC", "HOLD", "RULES", "SHOW", "Id", "String", "Sort",
  "Alg", "Term", "La1", "La2", "La3", "La4", "La5", "Ru", "Ra", "Func",
  "Const", "Var", "Bra", "Bra1", "Bra2", "Terms", "Form", "Sorts",
  "Functs", "Forms", "Algs", "Cond2", "Cond", "'\\n'", "':'", "','", "'('",
  "')'", "';'", "'{'", "'}'", "$accept", "prog", "line", "definition",
  "idlist", "att", "$@1", "namedId", "VORRANG", "condition", "condfunc",
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

#define YYPACT_NINF (-239)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-37)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     400,   564,   564,   564,   564,   564,   -43,    -2,   351,   210,
     564,   581,     0,   564,   351,    -6,  -239,    19,   593,   -39,
      16,    22,   593,    31,   -13,   -13,    33,    -9,  -239,   351,
     564,   593,   501,    38,    40,    32,    42,   593,  -239,    91,
     351,   351,   351,   351,   351,   448,   -16,  -239,   351,   351,
     351,  -239,   305,  -239,  -239,    20,    21,  -239,    23,  -239,
     528,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,
    -239,  -239,  -239,  -239,  -239,  -239,  -239,    44,    27,  -239,
      45,  -239,    53,  -239,    59,    62,  -239,    34,   514,  -239,
      65,   -61,    66,    47,  -239,   135,  -239,    99,    73,  -239,
    -239,  -239,  -239,   102,  -239,    74,    82,    83,   351,   400,
      85,   400,  -239,   351,   528,  -239,    86,  -239,   593,   162,
      89,   167,   119,   168,   171,   146,   604,    98,    17,    28,
     -20,   351,  -239,   351,   351,   490,   109,   106,   322,   400,
    -239,  -239,  -239,   400,   210,   351,   351,   351,   351,   351,
    -239,   351,   124,   564,   125,   126,   191,   256,   -40,   127,
     128,   104,   351,   110,   126,  -239,   351,   351,   351,   417,
     150,   -13,  -239,   117,   593,   183,   351,   136,   149,  -239,
     155,   157,   351,   528,     3,   137,   528,   148,   351,  -239,
    -239,  -239,  -239,   133,   142,  -239,  -239,   604,    98,    17,
      28,   -20,   -20,  -239,  -239,  -239,   141,   192,   223,   -13,
    -239,   430,  -239,   151,   181,   203,  -239,  -239,  -239,   -40,
    -239,  -239,  -239,   176,   -26,   126,   229,   152,   154,   163,
    -239,   400,  -239,   211,  -239,   351,   528,   250,  -239,  -239,
    -239,   521,  -239,  -239,  -239,  -239,   400,   126,  -239,   200,
     351,   179,   -40,   351,   400,  -239,   182,   351,   264,   226,
    -239,  -239,  -239,  -239,   184,   528,   230,   -40,  -239,  -239,
     108,   203,  -239,  -239,   528,  -239,   231,   460,   232,   281,
     351,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,
     281,  -239,   205,   351,   265,   281,   476,  -239,   207,  -239,
     241,   528,   400,  -239,   547,   -40,  -239,  -239,  -239,  -239,
    -239,   564,  -239,  -239,    55,  -239,   221,   227,    55,   400,
    -239,  -239
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,     0,
      91,    93,    94,     0,     0,     0,    87,     0,   100,   123,
       0,     0,     0,     0,     0,     0,   125,   127,     0,     0,
       0,    62,    68,     2,    61,     0,    53,    60,   101,    73,
      99,    32,    36,    37,    38,   112,   113,   114,   115,   116,
     118,   117,   111,    33,    34,   119,   120,     0,    23,    35,
       0,    20,     0,    21,     0,     0,   123,   125,     0,    75,
       0,    10,     0,     0,    71,     0,    84,     0,     0,    77,
      78,    76,    70,     0,    69,     0,     0,     0,     0,    68,
      47,    68,    74,     0,    88,    90,   121,    92,     0,     0,
       0,     0,     0,     0,    13,     0,   131,   132,   133,   134,
     135,     0,   130,     0,     0,   145,     0,     0,     0,    68,
       1,     3,     4,    68,     0,     0,     0,     0,     0,     0,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      65,     0,    64,     0,     0,     0,     0,     0,     0,    85,
       0,     0,     0,    79,     0,     0,    81,     0,     0,   136,
     137,   128,    57,     0,    55,    54,   102,   139,   140,   141,
     142,   143,   144,    16,    24,     9,   107,   109,     0,     0,
     105,     0,    17,   103,     0,   148,   152,    18,    19,     0,
      72,    22,    15,     0,     0,     0,     0,     0,     0,     0,
      52,    68,    48,     0,   122,     0,    95,     0,    14,    86,
      12,     0,   138,   126,   146,    63,    68,     0,   110,     0,
       0,     0,     0,     0,    68,   150,     0,     0,     0,     0,
      49,    50,    51,    66,     0,    96,     0,     0,    56,   108,
      39,   148,   106,   104,   147,   149,     0,    97,     0,    25,
       0,    11,    80,    40,    41,    42,    43,    44,    46,    45,
      25,   151,     0,     0,     0,    25,     0,     6,     0,     5,
       0,    98,    68,     8,     0,     0,    30,    26,    83,     7,
      67,     0,    27,    28,     0,    29,    58,     0,     0,    68,
      59,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -239,  -239,   266,  -231,    10,  -238,  -239,    -4,  -239,   -19,
    -239,  -113,    77,  -239,    13,  -106,  -239,  -239,  -239,  -239,
       2,  -105,  -239,    92,  -145,    -8,   158,    -7,   -45,    90,
      70,  -239,   196
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    52,    53,    54,    77,   297,   314,    78,   290,   109,
     110,    55,   193,   194,   317,    56,   139,    57,   294,    58,
      59,   251,   213,   207,   208,    79,   117,    60,   136,   215,
     255,   216,   217
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      82,    88,   133,   170,   137,   172,   111,    95,   257,    94,
      98,    89,    80,    81,   103,    83,   105,   106,   107,   226,
      90,    92,   114,   116,   119,    84,   192,    99,   210,   124,
     195,   -36,   -36,   126,   127,   128,   129,   130,   132,   100,
     115,   135,   135,   138,   145,   146,   147,   148,   149,   150,
     151,   212,   299,   220,   219,   150,   151,   303,     1,     2,
       3,     4,     5,     6,     7,   134,    85,    93,   173,    10,
      11,    12,    96,   145,   146,   147,   148,   149,   150,   151,
     258,   108,   101,   316,    97,   113,   185,   316,   102,   187,
     148,   149,   150,   151,    17,    18,   188,   104,   191,   112,
     122,   169,   149,   150,   151,   120,   135,   121,   123,   125,
     175,   142,   161,    33,    34,   134,   144,   143,   183,    37,
     153,   227,   228,   229,   184,   263,   186,   135,   283,   284,
     285,   286,   287,   192,   288,   289,   152,   154,   197,   198,
     199,   200,   201,   244,   202,   155,   196,   273,   275,   214,
     214,   156,   232,   162,   157,   224,   182,   159,   160,   135,
     135,   135,   282,   204,   163,   164,   116,   165,   166,   236,
     147,   148,   149,   150,   151,   241,   167,   168,   171,   174,
     176,   135,   177,   178,    16,   179,   180,   181,   190,   189,
     250,   203,   205,   206,   221,   222,   310,   223,   231,   253,
     313,   235,   225,   237,   138,   145,   146,   147,   148,   149,
     150,   151,   233,   321,   238,    86,    40,    41,    42,    43,
      44,   239,   240,    45,    87,    47,    48,    49,   265,    16,
     243,   245,   242,   246,   247,   298,   249,   248,   209,   254,
      50,   256,   259,   214,   252,   264,   274,   260,    16,   261,
     277,   145,   146,   147,   148,   149,   150,   151,   262,   210,
      86,    40,    41,    42,    43,    44,   266,   270,    45,    87,
      47,    48,    49,   135,   272,   276,    38,   278,   280,    86,
      40,    41,    42,    43,    44,   211,   301,    45,    87,    47,
      48,    49,   307,   279,    16,   281,   292,   296,   300,   295,
     312,   302,   308,   209,    50,   140,   309,   315,     1,     2,
       3,     4,     5,     6,     7,     8,     9,   318,   141,    10,
      11,    12,   319,   268,    13,    86,    40,    41,    42,    43,
      44,   320,   234,    45,    87,    47,    48,    49,    14,   269,
     271,   291,    15,    16,    17,    18,    19,    20,    21,    22,
      50,    23,    24,   218,    25,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,    36,     0,     0,    37,
       0,    38,     0,     0,    39,    40,    41,    42,    43,    44,
       0,     0,    45,    46,    47,    48,    49,     0,     0,    16,
       0,     0,   145,   146,   147,   148,   149,   150,   151,    50,
       0,     0,    51,     1,     2,     3,     4,     5,     6,     7,
       8,     9,     0,     0,    10,    11,    12,   191,     0,    13,
      86,    40,    41,    42,    43,    44,     0,     0,    45,    87,
      47,    48,    49,    14,     0,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    50,    23,    24,     0,    25,
      26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
      35,    36,     0,     0,    37,     0,    38,     0,    16,    39,
      40,    41,    42,    43,    44,     0,     0,    45,    46,    47,
      48,    49,     0,     0,     0,     0,    16,   145,   146,   147,
     148,   149,   150,   151,    50,   293,     0,    51,   210,    86,
      40,    41,    42,    43,    44,     0,     0,    45,    87,    47,
      48,    49,   230,     0,     0,     0,     0,    86,    40,    41,
      42,    43,    44,     0,   211,    45,    87,    47,    48,    49,
     145,   146,   147,   148,   149,   150,   151,   304,     0,   305,
       0,    61,   131,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,   118,     0,
     145,   146,   147,   148,   149,   150,   151,     0,     0,     0,
     306,    65,    66,    67,    68,    69,    70,    71,    72,     0,
       0,    75,    76,   188,   145,   146,   147,   148,   149,   150,
     151,   145,   146,   147,   148,   149,   150,   151,   145,   146,
     147,   148,   149,   150,   151,     0,   158,     0,     0,   311,
       0,     0,    61,   267,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    61,
       0,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    61,     0,    91,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    65,    66,    67,    68,    69,    70,    71,
      72,     0,     0,    75,    76,   146,   147,   148,   149,   150,
     151
};

static const yytype_int16 yycheck[] =
{
       4,     8,    18,   109,    49,   111,    25,    14,    34,    13,
      18,     9,     2,     3,    22,     5,    29,    30,    31,   164,
      10,    11,    29,    31,    32,    68,   139,    66,    68,    37,
     143,    92,    93,    40,    41,    42,    43,    44,    45,    78,
      30,    48,    49,    50,    70,    71,    72,    73,    74,    75,
      76,   156,   290,   158,    94,    75,    76,   295,     3,     4,
       5,     6,     7,     8,     9,    81,    68,    67,   113,    14,
      15,    16,    78,    70,    71,    72,    73,    74,    75,    76,
     225,    94,    66,   314,    65,    94,   131,   318,    66,   134,
      73,    74,    75,    76,    39,    40,    93,    66,    95,    66,
      68,   108,    74,    75,    76,    67,   113,    67,    66,    18,
     118,    91,    65,    58,    59,    81,    93,    96,   125,    64,
      93,   166,   167,   168,   131,   231,   133,   134,    20,    21,
      22,    23,    24,   246,    26,    27,    92,    92,   145,   146,
     147,   148,   149,   188,   151,    92,   144,   252,   254,   156,
     157,    92,   171,    18,    92,   162,    10,    92,    92,   166,
     167,   168,   267,   153,    65,    92,   174,    65,    94,   176,
      72,    73,    74,    75,    76,   182,    94,    94,    93,    93,
      18,   188,    93,    16,    38,    66,    18,    16,    82,    80,
     209,    67,    67,    67,    67,    67,   302,    93,    48,    18,
     305,    18,    92,    67,   211,    70,    71,    72,    73,    74,
      75,    76,    95,   319,    65,    69,    70,    71,    72,    73,
      74,    66,    65,    77,    78,    79,    80,    81,   235,    38,
      82,    98,    95,    91,    93,   280,    13,    45,    47,    36,
      94,    65,    13,   250,    93,    34,   253,    95,    38,    95,
     257,    70,    71,    72,    73,    74,    75,    76,    95,    68,
      69,    70,    71,    72,    73,    74,    16,    67,    77,    78,
      79,    80,    81,   280,    95,    93,    66,    13,    94,    69,
      70,    71,    72,    73,    74,    94,   293,    77,    78,    79,
      80,    81,   296,    67,    38,    65,    65,    16,    93,    67,
     304,    36,    95,    47,    94,     0,    65,   311,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    96,    52,    14,
      15,    16,    95,   246,    19,    69,    70,    71,    72,    73,
      74,   318,   174,    77,    78,    79,    80,    81,    33,   247,
     250,   271,    37,    38,    39,    40,    41,    42,    43,    44,
      94,    46,    47,   157,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    61,    -1,    -1,    64,
      -1,    66,    -1,    -1,    69,    70,    71,    72,    73,    74,
      -1,    -1,    77,    78,    79,    80,    81,    -1,    -1,    38,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    94,
      -1,    -1,    97,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    14,    15,    16,    95,    -1,    19,
      69,    70,    71,    72,    73,    74,    -1,    -1,    77,    78,
      79,    80,    81,    33,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    94,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    61,    -1,    -1,    64,    -1,    66,    -1,    38,    69,
      70,    71,    72,    73,    74,    -1,    -1,    77,    78,    79,
      80,    81,    -1,    -1,    -1,    -1,    38,    70,    71,    72,
      73,    74,    75,    76,    94,    35,    -1,    97,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    77,    78,    79,
      80,    81,    95,    -1,    -1,    -1,    -1,    69,    70,    71,
      72,    73,    74,    -1,    94,    77,    78,    79,    80,    81,
      70,    71,    72,    73,    74,    75,    76,    61,    -1,    63,
      -1,    65,    94,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    57,    -1,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    -1,
      94,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    80,    81,    93,    70,    71,    72,    73,    74,    75,
      76,    70,    71,    72,    73,    74,    75,    76,    70,    71,
      72,    73,    74,    75,    76,    -1,    92,    -1,    -1,    62,
      -1,    -1,    65,    92,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    65,
      -1,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    65,    -1,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    80,    81,    71,    72,    73,    74,    75,
      76
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    58,    59,    60,    61,    64,    66,    69,
      70,    71,    72,    73,    74,    77,    78,    79,    80,    81,
      94,    97,   100,   101,   102,   110,   114,   116,   118,   119,
     126,    65,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,   103,   106,   124,
     103,   103,   106,   103,    68,    68,    69,    78,   126,   119,
     103,    67,   103,    67,   106,   126,    78,    65,   124,    66,
      78,    66,    66,   124,    66,    29,    30,    31,    94,   108,
     109,   108,    66,    94,   126,   103,   124,   125,    57,   124,
      67,    67,    68,    66,   124,    18,   126,   126,   126,   126,
     126,    94,   126,    18,    81,   126,   127,   127,   126,   115,
       0,   101,    91,    96,    93,    70,    71,    72,    73,    74,
      75,    76,    92,    93,    92,    92,    92,    92,    92,    92,
      92,    65,    18,    65,    92,    65,    94,    94,    94,   126,
     114,    93,   114,   127,    93,   124,    18,    93,    16,    66,
      18,    16,    10,   126,   126,   127,   126,   127,    93,    80,
      82,    95,   110,   111,   112,   110,   119,   126,   126,   126,
     126,   126,   126,    67,   103,    67,    67,   122,   123,    47,
      68,    94,   120,   121,   126,   128,   130,   131,   131,    94,
     120,    67,    67,    93,   126,    92,   123,   127,   127,   127,
      95,    48,   108,    95,   125,    18,   126,    67,    65,    66,
      65,   126,    95,    82,   127,    98,    91,    93,    45,    13,
     108,   120,    93,    18,    36,   129,    65,    34,   123,    13,
      95,    95,    95,   114,    34,   126,    16,    92,   111,   122,
      67,   128,    95,   120,   126,   114,    93,   126,    13,    67,
      94,    65,   120,    20,    21,    22,    23,    24,    26,    27,
     107,   129,    65,    35,   117,    67,    16,   104,   127,   104,
      93,   126,    36,   104,    61,    63,    94,   106,    95,    65,
     114,    62,   106,   120,   105,   106,   102,   113,    96,    95,
     113,   114
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    99,   100,   100,   101,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   103,   103,   104,   104,   104,   104,   104,
     105,   104,   106,   106,   106,   106,   106,   106,   106,   107,
     107,   107,   107,   107,   107,   107,   107,   108,   108,   109,
     109,   109,   109,   110,   110,   111,   111,   112,   113,   113,
     114,   114,   115,   114,   114,   114,   114,   114,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     123,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   127,   127,   128,   129,   129,
     130,   130,   131
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     8,     7,     9,     8,     4,
       2,     6,     4,     2,     4,     4,     4,     4,     4,     4,
       2,     2,     4,     1,     3,     0,     2,     3,     3,     4,
       0,     6,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       4,     4,     3,     1,     3,     1,     3,     1,     1,     3,
       1,     1,     0,     4,     3,     3,     5,     9,     0,     2,
       2,     2,     4,     1,     2,     2,     2,     2,     2,     3,
       6,     3,     3,     8,     2,     3,     4,     1,     2,     1,
       2,     1,     2,     1,     1,     4,     5,     0,     2,     1,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     4,     1,     3,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     4,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     0,     2,
       2,     4,     1
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
#line 1533 "syn.tab.c"
    break;

  case 5: /* definition: FUNC namedId ':' vsortlist PFEIL Sort VORRANG att  */
#line 96 "syn.y"
                                                                    {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1541 "syn.tab.c"
    break;

  case 6: /* definition: OTHER func ':' vsortlist PFEIL Sort att  */
#line 99 "syn.y"
                                                                  { (yyval.y_nod)=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1550 "syn.tab.c"
    break;

  case 7: /* definition: ATT Sort Id ',' Id ',' Id ',' Id  */
#line 103 "syn.y"
                                                           { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufkt(name((yyvsp[0].y_sym))))))));	}
#line 1561 "syn.tab.c"
    break;

  case 8: /* definition: BRA Id Id ':' vsortlist PFEIL Sort att  */
#line 109 "syn.y"
                                                                            {Node * fkts;  /* Brackets */
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
#line 1577 "syn.tab.c"
    break;

  case 9: /* definition: VAR idlist ':' Sort  */
#line 120 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1583 "syn.tab.c"
    break;

  case 10: /* definition: NUM Sort  */
#line 121 "syn.y"
                                                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* sets numbertype for mknum */}
#line 1589 "syn.tab.c"
    break;

  case 11: /* definition: SUBSORT Sort ',' Sort ATT Id  */
#line 122 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort */
										      mknod(PARAM,(Node *) (yyvsp[-4].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufkt(name((yyvsp[0].y_sym))))));}
#line 1596 "syn.tab.c"
    break;

  case 12: /* definition: SHOW func ATT Id  */
#line 124 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) show_def,      /* 2026: print function */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) give_pfkt(name((yyvsp[0].y_sym)))));}
#line 1603 "syn.tab.c"
    break;

  case 13: /* definition: SHOW func  */
#line 126 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) show_def,      /* 2026: the usual printing again */
										      mknod(PARAM,(Node *) (yyvsp[0].y_nod),NULL));}
#line 1610 "syn.tab.c"
    break;

  case 14: /* definition: INTNUM Sort ATT Id  */
#line 128 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) intnum_def,    /* 2026: sort of integers */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufkt(name((yyvsp[0].y_sym)))));}
#line 1617 "syn.tab.c"
    break;

  case 15: /* definition: NUM idlist ':' Sort  */
#line 130 "syn.y"
                                                                 { /* Variables for numeric numbers */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1624 "syn.tab.c"
    break;

  case 16: /* definition: CST idlist ':' Sort  */
#line 132 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1630 "syn.tab.c"
    break;

  case 17: /* definition: SPEC Alg ':' alglist  */
#line 133 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1636 "syn.tab.c"
    break;

  case 18: /* definition: SPEC Alg ':' formlist  */
#line 134 "syn.y"
                                                         {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1642 "syn.tab.c"
    break;

  case 19: /* definition: ADDSPEC Alg ':' formlist  */
#line 135 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1648 "syn.tab.c"
    break;

  case 20: /* definition: SORT idlist  */
#line 136 "syn.y"
                                                                             {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1654 "syn.tab.c"
    break;

  case 21: /* definition: ALG idlist  */
#line 138 "syn.y"
                                                     {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1660 "syn.tab.c"
    break;

  case 22: /* definition: TERM idlist ':' Sort  */
#line 139 "syn.y"
                                                   {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1666 "syn.tab.c"
    break;

  case 23: /* idlist: namedId  */
#line 141 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1672 "syn.tab.c"
    break;

  case 24: /* idlist: namedId ',' idlist  */
#line 142 "syn.y"
                                                        {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1678 "syn.tab.c"
    break;

  case 25: /* att: %empty  */
#line 150 "syn.y"
                                        { (yyval.y_nod) = NULL;}
#line 1684 "syn.tab.c"
    break;

  case 26: /* att: ATT namedId  */
#line 151 "syn.y"
                                                { /* numeric C function (userfkt.c), otherwise symbolic (symfkt.c) */
			                  u_function * u = give_ufkt_quiet(name((Symbol *) (yyvsp[0].y_nod)));
			                  s_function * s = u ? NULL : give_sfkt(name((Symbol *) (yyvsp[0].y_nod)));
			                  if (u)
			                    (yyval.y_nod) = mknod(ATT,(Node *) u,NULL);
			                  else if (s)
			                    (yyval.y_nod) = mknod(ATT,(Node *) s,mknod(PARAM,NULL,NULL)); /* r: symbolic */
			                  else
			                    { printfErr(" --ERROR ATT : C-Function %s not Implemented \n",name((Symbol *) (yyvsp[0].y_nod)));
			                      (yyval.y_nod) = mknod(ATT,NULL,NULL); }
			                }
#line 1700 "syn.tab.c"
    break;

  case 27: /* att: ATT SYMBOLIC namedId  */
#line 162 "syn.y"
                                                        { /* 2026: symbolic C function (symfkt.c): gets terms */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 0); }
#line 1707 "syn.tab.c"
    break;

  case 28: /* att: ATT RULES alglist  */
#line 164 "syn.y"
                                                { /* 2026: function defined by a rule list: f(..) is REWR f(..) : alglist */
			                  (yyval.y_nod) = mknod(ATT,(Node *) rules_sfkt(),mknod(PARAM,(yyvsp[0].y_nod),NULL)); }
#line 1714 "syn.tab.c"
    break;

  case 29: /* att: ATT SYMBOLIC HOLD namedId  */
#line 166 "syn.y"
                                                        { /* 2026: plus arguments unevaluated (matchq) */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 1); }
#line 1721 "syn.tab.c"
    break;

  case 30: /* $@1: %empty  */
#line 168 "syn.y"
                                          {block_begin();no_protect();}
#line 1727 "syn.tab.c"
    break;

  case 31: /* att: ATT '(' $@1 d_list ')' instruction  */
#line 169 "syn.y"
                                                                                        {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1733 "syn.tab.c"
    break;

  case 32: /* namedId: Id  */
#line 171 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1739 "syn.tab.c"
    break;

  case 33: /* namedId: Const  */
#line 172 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1745 "syn.tab.c"
    break;

  case 34: /* namedId: Var  */
#line 173 "syn.y"
                         { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1751 "syn.tab.c"
    break;

  case 35: /* namedId: func  */
#line 174 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1757 "syn.tab.c"
    break;

  case 36: /* namedId: Sort  */
#line 175 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1763 "syn.tab.c"
    break;

  case 37: /* namedId: Alg  */
#line 176 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1769 "syn.tab.c"
    break;

  case 38: /* namedId: Term  */
#line 177 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1775 "syn.tab.c"
    break;

  case 39: /* VORRANG: %empty  */
#line 180 "syn.y"
                                                        {(yyval.y_int) = Func;}
#line 1781 "syn.tab.c"
    break;

  case 40: /* VORRANG: LA1  */
#line 181 "syn.y"
                                                                        {(yyval.y_int) = La1;	/* Left-associative */}
#line 1787 "syn.tab.c"
    break;

  case 41: /* VORRANG: LA2  */
#line 182 "syn.y"
                                                                        {(yyval.y_int) = La2;	/* Left-associative */}
#line 1793 "syn.tab.c"
    break;

  case 42: /* VORRANG: LA3  */
#line 183 "syn.y"
                                                                        {(yyval.y_int) = La3;	/* Left-associative */}
#line 1799 "syn.tab.c"
    break;

  case 43: /* VORRANG: LA4  */
#line 184 "syn.y"
                                                                        {(yyval.y_int) = La4;	/* Left-associative */}
#line 1805 "syn.tab.c"
    break;

  case 44: /* VORRANG: LA5  */
#line 185 "syn.y"
                                                                        {(yyval.y_int) = La5;	/* Left-associative */}
#line 1811 "syn.tab.c"
    break;

  case 45: /* VORRANG: RA  */
#line 186 "syn.y"
                                                                        {(yyval.y_int) = Ra;  	/* Right-associative */}
#line 1817 "syn.tab.c"
    break;

  case 46: /* VORRANG: RU  */
#line 187 "syn.y"
                                                                        {(yyval.y_int) = Ru;	  /* Right unary */}
#line 1823 "syn.tab.c"
    break;

  case 47: /* condition: condfunc  */
#line 189 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1829 "syn.tab.c"
    break;

  case 48: /* condition: condfunc ',' condition  */
#line 190 "syn.y"
                                                        {(yyval.y_nod) = mknod(Cond,(Node *) and_cond,mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod)));}
#line 1835 "syn.tab.c"
    break;

  case 49: /* condfunc: LB '(' termlist ')'  */
#line 192 "syn.y"
                              {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1841 "syn.tab.c"
    break;

  case 50: /* condfunc: IN '(' termlist ')'  */
#line 193 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1847 "syn.tab.c"
    break;

  case 51: /* condfunc: NIN '(' termlist ')'  */
#line 194 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1853 "syn.tab.c"
    break;

  case 52: /* condfunc: '(' term ')'  */
#line 195 "syn.y"
                                                                        {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1859 "syn.tab.c"
    break;

  case 53: /* instructions: instruction  */
#line 197 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1865 "syn.tab.c"
    break;

  case 54: /* instructions: instruction ';' instructions  */
#line 198 "syn.y"
                                                                                       {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1871 "syn.tab.c"
    break;

  case 55: /* tinstructions: oinstructions  */
#line 200 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1877 "syn.tab.c"
    break;

  case 56: /* tinstructions: oinstructions '\n' tinstructions  */
#line 201 "syn.y"
                                                                                                                {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1883 "syn.tab.c"
    break;

  case 57: /* oinstructions: instructions  */
#line 203 "syn.y"
                                                {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1889 "syn.tab.c"
    break;

  case 58: /* d_list: definition  */
#line 208 "syn.y"
                                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1895 "syn.tab.c"
    break;

  case 59: /* d_list: definition ';' d_list  */
#line 209 "syn.y"
                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1901 "syn.tab.c"
    break;

  case 60: /* instruction: aninstruction  */
#line 211 "syn.y"
                                {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Check local variables ! */ }
#line 1907 "syn.tab.c"
    break;

  case 61: /* instruction: definition  */
#line 212 "syn.y"
                                                                        {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1913 "syn.tab.c"
    break;

  case 62: /* $@2: %empty  */
#line 213 "syn.y"
                                                                                                        {block_begin();no_protect();}
#line 1919 "syn.tab.c"
    break;

  case 63: /* instruction: '{' $@2 tinstructions '}'  */
#line 214 "syn.y"
                                                                        {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 1929 "syn.tab.c"
    break;

  case 64: /* instruction: WHILE condition instruction  */
#line 219 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* then becomes $3 */)));
																		WHILE_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1936 "syn.tab.c"
    break;

  case 65: /* instruction: IF condition instruction  */
#line 222 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		IF_THEN(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1943 "syn.tab.c"
    break;

  case 66: /* instruction: IF condition instruction ELSE instruction  */
#line 224 "syn.y"
                                                                        {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(merk) = (yyvsp[-2].y_nod);IF_ELSE(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1950 "syn.tab.c"
    break;

  case 67: /* instruction: FOR term EQ term TO term step DO instruction  */
#line 227 "syn.y"
                                                                                                                {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) forschleife,
																mknod(PARAM,
																	mknod(PARAM,(yyvsp[-5].y_nod),(yyvsp[-3].y_nod)),
																	mknod(PARAM,
																		mknod(PARAM,(yyvsp[-2].y_nod),(Node *) ((yyvsp[-7].y_nod))),
																		NULL /* $9 */) )));	
														FOR_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1962 "syn.tab.c"
    break;

  case 68: /* aninstruction: %empty  */
#line 236 "syn.y"
                                        {(yyval.y_nod)=NULL;}
#line 1968 "syn.tab.c"
    break;

  case 69: /* aninstruction: SYS String  */
#line 237 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) system_fkt,(Node *) ((yyvsp[0].y_sym)));}
#line 1974 "syn.tab.c"
    break;

  case 70: /* aninstruction: INC String  */
#line 238 "syn.y"
                                                                        {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fkt,(Node *) ((yyvsp[0].y_sym))); }
#line 1980 "syn.tab.c"
    break;

  case 71: /* aninstruction: INFO namedId  */
#line 239 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) info_fkt,(Node *) ((yyvsp[0].y_nod))); }
#line 1986 "syn.tab.c"
    break;

  case 72: /* aninstruction: REWR term ':' alglist  */
#line 240 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 1993 "syn.tab.c"
    break;

  case 73: /* aninstruction: prntlist  */
#line 242 "syn.y"
                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 1999 "syn.tab.c"
    break;

  case 74: /* aninstruction: PRTNUM String  */
#line 243 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 2005 "syn.tab.c"
    break;

  case 75: /* aninstruction: PRT prntlist  */
#line 244 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* without \n */ }
#line 2011 "syn.tab.c"
    break;

  case 76: /* aninstruction: OUT String  */
#line 245 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 2017 "syn.tab.c"
    break;

  case 77: /* aninstruction: DATA String  */
#line 246 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 2023 "syn.tab.c"
    break;

  case 78: /* aninstruction: DATA Const  */
#line 247 "syn.y"
                                                                        {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 2034 "syn.tab.c"
    break;

  case 79: /* aninstruction: Term EQ term  */
#line 253 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 2040 "syn.tab.c"
    break;

  case 80: /* aninstruction: Term EQ REWR term ':' alglist  */
#line 254 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 2046 "syn.tab.c"
    break;

  case 81: /* aninstruction: Const EQ term  */
#line 255 "syn.y"
                                                        { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 2052 "syn.tab.c"
    break;

  case 82: /* aninstruction: EXE func Id  */
#line 256 "syn.y"
                                                        {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufkt(name((yyvsp[0].y_sym)));
 													}
#line 2062 "syn.tab.c"
    break;

  case 83: /* aninstruction: LIFT '(' termlist ')' TO '(' termlist ')'  */
#line 261 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 2068 "syn.tab.c"
    break;

  case 84: /* aninstruction: DBG Const  */
#line 262 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 2074 "syn.tab.c"
    break;

  case 85: /* aninstruction: STEPS Alg String  */
#line 263 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) steps_fkt,mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2080 "syn.tab.c"
    break;

  case 86: /* aninstruction: SYMBOLIC String EQ String  */
#line 264 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fkt,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2086 "syn.tab.c"
    break;

  case 87: /* aninstruction: SYMBOLIC  */
#line 265 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fkt,NULL);  /* delete roles */}
#line 2092 "syn.tab.c"
    break;

  case 88: /* aninstruction: RETURN term  */
#line 266 "syn.y"
                                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) return_fkt,(yyvsp[0].y_nod));}
#line 2098 "syn.tab.c"
    break;

  case 89: /* aninstruction: QUIT  */
#line 267 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fkt,NULL);}
#line 2104 "syn.tab.c"
    break;

  case 90: /* aninstruction: OPT idlist  */
#line 268 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,(yyvsp[0].y_nod));}
#line 2110 "syn.tab.c"
    break;

  case 91: /* aninstruction: OPT  */
#line 269 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,NULL);   /* delete */}
#line 2116 "syn.tab.c"
    break;

  case 92: /* aninstruction: COMM funclist  */
#line 270 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,(yyvsp[0].y_nod));}
#line 2122 "syn.tab.c"
    break;

  case 93: /* aninstruction: COMM  */
#line 271 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,NULL);  /* delete */}
#line 2128 "syn.tab.c"
    break;

  case 94: /* aninstruction: DEFAULT  */
#line 272 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,NULL); /* delete */}
#line 2134 "syn.tab.c"
    break;

  case 95: /* aninstruction: DEFAULT func EQ term  */
#line 273 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),NULL),(yyvsp[0].y_nod)));}
#line 2141 "syn.tab.c"
    break;

  case 96: /* aninstruction: DEFAULT RIGHT func EQ term  */
#line 275 "syn.y"
                                                     {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),mknod(PARAM,NULL,NULL)),(yyvsp[0].y_nod)));}
#line 2148 "syn.tab.c"
    break;

  case 97: /* step: %empty  */
#line 278 "syn.y"
                        {(yyval.y_nod)=(Node *) NULL;}
#line 2154 "syn.tab.c"
    break;

  case 98: /* step: STEP term  */
#line 279 "syn.y"
                                        {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2160 "syn.tab.c"
    break;

  case 99: /* prntexpr: term  */
#line 281 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2166 "syn.tab.c"
    break;

  case 100: /* prntexpr: String  */
#line 282 "syn.y"
                                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2172 "syn.tab.c"
    break;

  case 101: /* prntlist: prntexpr  */
#line 284 "syn.y"
                                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2178 "syn.tab.c"
    break;

  case 102: /* prntlist: prntexpr ',' prntlist  */
#line 285 "syn.y"
                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2184 "syn.tab.c"
    break;

  case 103: /* alglist: Alg2  */
#line 287 "syn.y"
                                                                {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2190 "syn.tab.c"
    break;

  case 104: /* alglist: Alg2 ',' alglist  */
#line 288 "syn.y"
                                                        {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2196 "syn.tab.c"
    break;

  case 105: /* Alg2: Alg  */
#line 290 "syn.y"
                                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2202 "syn.tab.c"
    break;

  case 106: /* Alg2: '(' alglist ')'  */
#line 291 "syn.y"
                                                                {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2208 "syn.tab.c"
    break;

  case 107: /* sortlist: Sort  */
#line 293 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2214 "syn.tab.c"
    break;

  case 108: /* sortlist: Sort ',' sortlist  */
#line 294 "syn.y"
                                                                {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2220 "syn.tab.c"
    break;

  case 109: /* vsortlist: sortlist  */
#line 296 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2226 "syn.tab.c"
    break;

  case 110: /* vsortlist: sortlist VARPAR  */
#line 297 "syn.y"
                                                                        {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2232 "syn.tab.c"
    break;

  case 111: /* func: Func  */
#line 299 "syn.y"
                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2238 "syn.tab.c"
    break;

  case 112: /* func: La1  */
#line 300 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2244 "syn.tab.c"
    break;

  case 113: /* func: La2  */
#line 301 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2250 "syn.tab.c"
    break;

  case 114: /* func: La3  */
#line 302 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2256 "syn.tab.c"
    break;

  case 115: /* func: La4  */
#line 303 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2262 "syn.tab.c"
    break;

  case 116: /* func: La5  */
#line 304 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2268 "syn.tab.c"
    break;

  case 117: /* func: Ra  */
#line 305 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2274 "syn.tab.c"
    break;

  case 118: /* func: Ru  */
#line 306 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2280 "syn.tab.c"
    break;

  case 119: /* func: Bra  */
#line 307 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2286 "syn.tab.c"
    break;

  case 120: /* func: Bra1  */
#line 308 "syn.y"
                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2292 "syn.tab.c"
    break;

  case 121: /* funclist: func  */
#line 310 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2298 "syn.tab.c"
    break;

  case 122: /* funclist: func ',' funclist  */
#line 311 "syn.y"
                                                        {(yyval.y_nod) = mknod(Functs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2304 "syn.tab.c"
    break;

  case 123: /* term: Term  */
#line 313 "syn.y"
                                                                        {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); does not remember dependencies and does not work in blocks */ 
														}
#line 2311 "syn.tab.c"
    break;

  case 124: /* term: LAST  */
#line 315 "syn.y"
                                                                                        {(yyval.y_nod) = (Node *) lastterm;}
#line 2317 "syn.tab.c"
    break;

  case 125: /* term: Const  */
#line 316 "syn.y"
                                                                                        {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2323 "syn.tab.c"
    break;

  case 126: /* term: Const Bra1 termlist Bra2  */
#line 317 "syn.y"
                                                   {nphilf=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),nphilf), nphilf);}
#line 2330 "syn.tab.c"
    break;

  case 127: /* term: Var  */
#line 319 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2336 "syn.tab.c"
    break;

  case 128: /* term: '(' term ')'  */
#line 320 "syn.y"
                                                    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2342 "syn.tab.c"
    break;

  case 129: /* term: term Ru  */
#line 321 "syn.y"
                                                                      {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2348 "syn.tab.c"
    break;

  case 130: /* term: Func term  */
#line 322 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2354 "syn.tab.c"
    break;

  case 131: /* term: La1 term  */
#line 323 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2360 "syn.tab.c"
    break;

  case 132: /* term: La2 term  */
#line 324 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2366 "syn.tab.c"
    break;

  case 133: /* term: La3 term  */
#line 325 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2372 "syn.tab.c"
    break;

  case 134: /* term: La4 term  */
#line 326 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2378 "syn.tab.c"
    break;

  case 135: /* term: La5 term  */
#line 327 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2384 "syn.tab.c"
    break;

  case 136: /* term: Bra termlist Bra  */
#line 328 "syn.y"
                                                  {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2390 "syn.tab.c"
    break;

  case 137: /* term: Bra1 termlist Bra2  */
#line 329 "syn.y"
                                                {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2396 "syn.tab.c"
    break;

  case 138: /* term: Func '(' termlist ')'  */
#line 330 "syn.y"
                                                        {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2402 "syn.tab.c"
    break;

  case 139: /* term: term La1 term  */
#line 331 "syn.y"
                                                    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2409 "syn.tab.c"
    break;

  case 140: /* term: term La2 term  */
#line 333 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2416 "syn.tab.c"
    break;

  case 141: /* term: term La3 term  */
#line 335 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2423 "syn.tab.c"
    break;

  case 142: /* term: term La4 term  */
#line 337 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2430 "syn.tab.c"
    break;

  case 143: /* term: term La5 term  */
#line 339 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2437 "syn.tab.c"
    break;

  case 144: /* term: term Ra term  */
#line 341 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2444 "syn.tab.c"
    break;

  case 145: /* termlist: term  */
#line 344 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2450 "syn.tab.c"
    break;

  case 146: /* termlist: term ',' termlist  */
#line 345 "syn.y"
                                                        {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2456 "syn.tab.c"
    break;

  case 147: /* formula: term EQ term  */
#line 347 "syn.y"
                                        {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2462 "syn.tab.c"
    break;

  case 148: /* vinstr: %empty  */
#line 349 "syn.y"
                                                                {(yyval.y_nod) = NULL;}
#line 2468 "syn.tab.c"
    break;

  case 149: /* vinstr: DO instruction  */
#line 350 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2474 "syn.tab.c"
    break;

  case 150: /* cformula: formula vinstr  */
#line 352 "syn.y"
                                                                        {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2481 "syn.tab.c"
    break;

  case 151: /* cformula: IF condition formula vinstr  */
#line 354 "syn.y"
                                               {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2488 "syn.tab.c"
    break;

  case 152: /* formlist: cformula  */
#line 357 "syn.y"
                                                                {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL serves for hooking in further formulas !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. because of SPEC real : A+B=C;a=3 */
															}
#line 2496 "syn.tab.c"
    break;


#line 2500 "syn.tab.c"

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

#line 361 "syn.y"


/* 2026: ATT SYMBOLIC [HOLD] name: a symbolic C function (symfkt.c), which
   gets the argument terms; with HOLD they are passed unevaluated */
static Node * sym_att (Node * id, int hold)
{
	s_function * s = give_sfkt(name((Symbol *) id));
	if (! s)
		{
		printfErr(" --ERROR ATT SYMBOLIC : C-Function %s not Implemented \n",name((Symbol *) id));
		return mknod(ATT,NULL,NULL);
		}
	return mknod(ATT,(Node *) s,mknod(PARAM,NULL,hold ? mknod(PARAM,NULL,NULL) : NULL));
}
