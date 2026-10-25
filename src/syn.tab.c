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
  YYSYMBOL_Id = 64,                        /* Id  */
  YYSYMBOL_String = 65,                    /* String  */
  YYSYMBOL_Sort = 66,                      /* Sort  */
  YYSYMBOL_Alg = 67,                       /* Alg  */
  YYSYMBOL_Term = 68,                      /* Term  */
  YYSYMBOL_La1 = 69,                       /* La1  */
  YYSYMBOL_La2 = 70,                       /* La2  */
  YYSYMBOL_La3 = 71,                       /* La3  */
  YYSYMBOL_La4 = 72,                       /* La4  */
  YYSYMBOL_La5 = 73,                       /* La5  */
  YYSYMBOL_Ru = 74,                        /* Ru  */
  YYSYMBOL_Ra = 75,                        /* Ra  */
  YYSYMBOL_Func = 76,                      /* Func  */
  YYSYMBOL_Const = 77,                     /* Const  */
  YYSYMBOL_Var = 78,                       /* Var  */
  YYSYMBOL_Bra = 79,                       /* Bra  */
  YYSYMBOL_Bra1 = 80,                      /* Bra1  */
  YYSYMBOL_Bra2 = 81,                      /* Bra2  */
  YYSYMBOL_Terms = 82,                     /* Terms  */
  YYSYMBOL_Form = 83,                      /* Form  */
  YYSYMBOL_Sorts = 84,                     /* Sorts  */
  YYSYMBOL_Functs = 85,                    /* Functs  */
  YYSYMBOL_Forms = 86,                     /* Forms  */
  YYSYMBOL_Algs = 87,                      /* Algs  */
  YYSYMBOL_Cond2 = 88,                     /* Cond2  */
  YYSYMBOL_Cond = 89,                      /* Cond  */
  YYSYMBOL_90_n_ = 90,                     /* '\n'  */
  YYSYMBOL_91_ = 91,                       /* ':'  */
  YYSYMBOL_92_ = 92,                       /* ','  */
  YYSYMBOL_93_ = 93,                       /* '('  */
  YYSYMBOL_94_ = 94,                       /* ')'  */
  YYSYMBOL_95_ = 95,                       /* ';'  */
  YYSYMBOL_96_ = 96,                       /* '{'  */
  YYSYMBOL_97_ = 97,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 98,                  /* $accept  */
  YYSYMBOL_prog = 99,                      /* prog  */
  YYSYMBOL_line = 100,                     /* line  */
  YYSYMBOL_definition = 101,               /* definition  */
  YYSYMBOL_idlist = 102,                   /* idlist  */
  YYSYMBOL_att = 103,                      /* att  */
  YYSYMBOL_104_1 = 104,                    /* $@1  */
  YYSYMBOL_namedId = 105,                  /* namedId  */
  YYSYMBOL_VORRANG = 106,                  /* VORRANG  */
  YYSYMBOL_condition = 107,                /* condition  */
  YYSYMBOL_condfunc = 108,                 /* condfunc  */
  YYSYMBOL_instructions = 109,             /* instructions  */
  YYSYMBOL_tinstructions = 110,            /* tinstructions  */
  YYSYMBOL_oinstructions = 111,            /* oinstructions  */
  YYSYMBOL_d_list = 112,                   /* d_list  */
  YYSYMBOL_instruction = 113,              /* instruction  */
  YYSYMBOL_114_2 = 114,                    /* $@2  */
  YYSYMBOL_aninstruction = 115,            /* aninstruction  */
  YYSYMBOL_step = 116,                     /* step  */
  YYSYMBOL_prntexpr = 117,                 /* prntexpr  */
  YYSYMBOL_prntlist = 118,                 /* prntlist  */
  YYSYMBOL_alglist = 119,                  /* alglist  */
  YYSYMBOL_Alg2 = 120,                     /* Alg2  */
  YYSYMBOL_sortlist = 121,                 /* sortlist  */
  YYSYMBOL_vsortlist = 122,                /* vsortlist  */
  YYSYMBOL_func = 123,                     /* func  */
  YYSYMBOL_funclist = 124,                 /* funclist  */
  YYSYMBOL_term = 125,                     /* term  */
  YYSYMBOL_termlist = 126,                 /* termlist  */
  YYSYMBOL_formula = 127,                  /* formula  */
  YYSYMBOL_vinstr = 128,                   /* vinstr  */
  YYSYMBOL_cformula = 129,                 /* cformula  */
  YYSYMBOL_formlist = 130                  /* formlist  */
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
#define YYFINAL  138
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   670

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  318

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   344


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
      90,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      93,    94,     2,     2,    92,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    91,    95,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    96,     2,    97,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    85,    85,    86,    88,    96,    99,   103,   109,   120,
     121,   122,   124,   126,   128,   129,   130,   131,   132,   134,
     135,   137,   138,   146,   147,   158,   160,   162,   164,   164,
     167,   168,   169,   170,   171,   172,   173,   176,   177,   178,
     179,   180,   181,   182,   183,   185,   186,   188,   189,   190,
     191,   193,   194,   196,   197,   199,   204,   205,   207,   208,
     209,   209,   215,   218,   220,   222,   232,   233,   234,   235,
     236,   238,   239,   240,   241,   242,   243,   249,   250,   251,
     252,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   271,   274,   275,   277,   278,   280,
     281,   283,   284,   286,   287,   289,   290,   292,   293,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   306,
     307,   309,   311,   312,   313,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   329,   331,
     333,   335,   337,   340,   341,   343,   345,   346,   348,   350,
     353
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
  "STEPS", "SYMBOLIC", "HOLD", "RULES", "Id", "String", "Sort", "Alg",
  "Term", "La1", "La2", "La3", "La4", "La5", "Ru", "Ra", "Func", "Const",
  "Var", "Bra", "Bra1", "Bra2", "Terms", "Form", "Sorts", "Functs",
  "Forms", "Algs", "Cond2", "Cond", "'\\n'", "':'", "','", "'('", "')'",
  "';'", "'{'", "'}'", "$accept", "prog", "line", "definition", "idlist",
  "att", "$@1", "namedId", "VORRANG", "condition", "condfunc",
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

#define YYPACT_NINF (-248)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     395,   573,   573,   573,   573,   573,   -21,    22,   253,   188,
     573,   590,   -22,   573,   253,   -28,  -248,     2,   537,   -27,
       3,    27,   537,    30,    -2,    -2,    32,     6,  -248,   253,
     573,   537,   510,    46,    51,    52,    53,  -248,   103,   253,
     253,   253,   253,   253,   347,    -5,  -248,   253,   253,   253,
    -248,   301,  -248,  -248,    36,    37,  -248,    35,  -248,   443,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,    43,    39,  -248,    44,
    -248,    59,  -248,    61,    63,  -248,    64,   523,  -248,    65,
      19,    69,    79,  -248,    13,  -248,    91,    70,  -248,  -248,
    -248,  -248,    98,  -248,    72,    75,    76,   253,   395,    71,
     395,  -248,   253,   443,  -248,    78,  -248,   537,   153,    87,
     164,   116,   174,     1,   422,   102,    29,    33,    40,   253,
    -248,   253,   253,   499,   123,   122,   318,   395,  -248,  -248,
    -248,   395,   188,   253,   253,   253,   253,   253,  -248,   253,
     138,   573,   142,   143,   144,   207,   -46,   152,   161,   127,
     253,   137,   143,  -248,   253,   253,   253,   484,   181,    -2,
    -248,   139,   537,   214,   253,   168,   171,  -248,   173,   253,
     443,   471,   147,   443,   155,   253,  -248,  -248,  -248,  -248,
     146,   154,  -248,  -248,   422,   102,    29,    33,    40,    40,
    -248,  -248,  -248,   156,   202,   238,    -2,  -248,   431,  -248,
     160,   115,   219,  -248,  -248,  -248,   -46,  -248,  -248,  -248,
     198,   -18,   143,   250,   176,   177,   178,  -248,   395,  -248,
     239,  -248,   253,   443,   258,  -248,  -248,   530,  -248,  -248,
    -248,  -248,   395,   143,  -248,   223,   253,   196,   -46,   253,
     395,  -248,   200,   253,   280,   228,  -248,  -248,  -248,  -248,
     204,   443,   231,   -46,  -248,  -248,    38,   219,  -248,  -248,
     443,  -248,   234,   408,   233,   286,   253,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,   286,  -248,   221,   253,
     278,   286,   459,  -248,   224,  -248,   255,   443,   395,  -248,
     556,   -46,  -248,  -248,  -248,  -248,  -248,   573,  -248,  -248,
     191,  -248,   232,   241,   191,   395,  -248,  -248
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    87,     0,
      89,    91,    92,     0,     0,     0,    85,    98,   121,     0,
       0,     0,     0,     0,     0,   123,   125,     0,     0,     0,
      60,    66,     2,    59,     0,    51,    58,    99,    71,    97,
      30,    34,    35,    36,   110,   111,   112,   113,   114,   116,
     115,   109,    31,    32,   117,   118,     0,    21,    33,     0,
      18,     0,    19,     0,     0,   121,   123,     0,    73,     0,
      10,     0,     0,    69,     0,    82,     0,     0,    75,    76,
      74,    68,     0,    67,     0,     0,     0,     0,    66,    45,
      66,    72,     0,    86,    88,   119,    90,     0,     0,     0,
       0,     0,     0,     0,   129,   130,   131,   132,   133,     0,
     128,     0,     0,   143,     0,     0,     0,    66,     1,     3,
       4,    66,     0,     0,     0,     0,     0,     0,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    80,     0,     0,     0,     0,    63,     0,
      62,     0,     0,     0,     0,     0,     0,    83,     0,     0,
      77,     0,     0,    79,     0,     0,   134,   135,   126,    55,
       0,    53,    52,   100,   137,   138,   139,   140,   141,   142,
      14,    22,     9,   105,   107,     0,     0,   103,     0,    15,
     101,     0,   146,   150,    16,    17,     0,    70,    20,    13,
       0,     0,     0,     0,     0,     0,     0,    50,    66,    46,
       0,   120,     0,    93,     0,    12,    84,     0,   136,   124,
     144,    61,    66,     0,   108,     0,     0,     0,     0,     0,
      66,   148,     0,     0,     0,     0,    47,    48,    49,    64,
       0,    94,     0,     0,    54,   106,    37,   146,   104,   102,
     145,   147,     0,    95,     0,    23,     0,    11,    78,    38,
      39,    40,    41,    42,    44,    43,    23,   149,     0,     0,
       0,    23,     0,     6,     0,     5,     0,    96,    66,     8,
       0,     0,    28,    24,    81,     7,    65,     0,    25,    26,
       0,    27,    56,     0,     0,    66,    57,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -248,  -248,   277,  -247,    15,  -243,  -248,    -4,  -248,   -23,
    -248,  -122,    94,  -248,    23,  -105,  -248,  -248,  -248,  -248,
      -1,  -150,  -248,   106,  -132,    -8,   186,    -7,   -36,   117,
      97,  -248,   210
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    51,    52,    53,    76,   293,   310,    77,   286,   108,
     109,    54,   190,   191,   313,    55,   137,    56,   290,    57,
      58,   247,   210,   204,   205,    78,   116,    59,   134,   212,
     251,   213,   214
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      81,    87,   110,   168,   209,   170,   217,    94,    88,    93,
      97,   179,   135,   131,   102,   189,   253,    79,    80,   192,
      82,   207,   113,   115,   118,    89,    91,   104,   105,   106,
     223,   160,   124,   125,   126,   127,   128,   130,    98,    16,
     133,   133,   136,   295,    92,   114,    83,   216,   299,    95,
      99,   143,   144,   145,   146,   147,   148,   149,   279,   280,
     281,   282,   283,   312,   284,   285,    96,   312,   100,    85,
      39,    40,    41,    42,    43,   132,   171,    44,    86,    46,
      47,    48,   143,   144,   145,   146,   147,   148,   149,    84,
     254,   107,   101,   182,    49,   103,   184,   111,   269,   112,
     167,   146,   147,   148,   149,   133,   147,   148,   149,   173,
     -34,   -34,   119,   278,   148,   149,   180,   120,   122,   121,
     189,   123,   181,   259,   183,   133,   140,   142,   224,   225,
     226,   151,   141,   249,   150,   152,   194,   195,   196,   197,
     198,   193,   199,   159,   132,   271,   229,   211,   211,   240,
     153,   309,   154,   221,   155,   161,   157,   133,   133,   133,
     158,   162,   163,   169,   115,   164,   201,   233,   165,   166,
     172,   174,   237,   145,   146,   147,   148,   149,   133,   175,
     176,   177,    16,   246,   143,   144,   145,   146,   147,   148,
     149,   206,   178,   306,     1,     2,     3,     4,     5,     6,
       7,   136,   186,   187,   200,    10,    11,    12,   202,   203,
     317,   207,    85,    39,    40,    41,    42,    43,   218,   220,
      44,    86,    46,    47,    48,   261,    16,   219,   222,   228,
      17,    18,   232,   230,   234,   235,   239,   208,   236,   211,
     294,   238,   270,   241,   242,    16,   273,   244,   243,    33,
      34,   245,   248,    37,   206,   250,    85,    39,    40,    41,
      42,    43,   252,   255,    44,    86,    46,    47,    48,   133,
     256,   257,   258,   260,   262,    85,    39,    40,    41,    42,
      43,    49,   297,    44,    86,    46,    47,    48,   303,   266,
     268,    16,   272,   274,   275,   277,   308,   276,   288,   291,
      49,   138,   292,   311,     1,     2,     3,     4,     5,     6,
       7,     8,     9,   296,   298,    10,    11,    12,   304,   305,
      13,    85,    39,    40,    41,    42,    43,   314,   139,    44,
      86,    46,    47,    48,    14,   315,   264,   316,    15,    16,
      17,    18,    19,    20,    21,    22,    49,    23,    24,   265,
      25,    26,    27,    28,    29,    30,    31,    32,   231,    33,
      34,    35,    36,   267,   287,   215,    37,     0,     0,    38,
      39,    40,    41,    42,    43,     0,     0,    44,    45,    46,
      47,    48,     0,     0,     0,    16,     0,   143,   144,   145,
     146,   147,   148,   149,    49,     0,     0,    50,     1,     2,
       3,     4,     5,     6,     7,     8,     9,     0,     0,    10,
      11,    12,   188,     0,    13,    85,    39,    40,    41,    42,
      43,     0,     0,    44,    86,    46,    47,    48,    14,     0,
       0,     0,    15,    16,    17,    18,    19,    20,    21,    22,
     129,    23,    24,   289,    25,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,    36,     0,     0,     0,
      37,     0,     0,    38,    39,    40,    41,    42,    43,    16,
       0,    44,    45,    46,    47,    48,     0,   143,   144,   145,
     146,   147,   148,   149,     0,     0,     0,     0,    49,     0,
       0,    50,   144,   145,   146,   147,   148,   149,   207,    85,
      39,    40,    41,    42,    43,     0,     0,    44,    86,    46,
      47,    48,   143,   144,   145,   146,   147,   148,   149,     0,
     300,     0,   301,    60,   208,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     143,   144,   145,   146,   147,   148,   149,     0,     0,     0,
       0,     0,   302,   143,   144,   145,   146,   147,   148,   149,
       0,     0,     0,   185,     0,   188,     0,   117,   143,   144,
     145,   146,   147,   148,   149,     0,     0,     0,   227,    64,
      65,    66,    67,    68,    69,    70,    71,     0,     0,    74,
      75,   185,   143,   144,   145,   146,   147,   148,   149,   143,
     144,   145,   146,   147,   148,   149,    64,    65,    66,    67,
      68,    69,    70,    71,   156,     0,    74,    75,   307,     0,
      60,   263,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    60,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    60,     0,    90,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

static const yytype_int16 yycheck[] =
{
       4,     8,    25,   108,   154,   110,   156,    14,     9,    13,
      18,    10,    48,    18,    22,   137,    34,     2,     3,   141,
       5,    67,    29,    31,    32,    10,    11,    29,    30,    31,
     162,    18,    39,    40,    41,    42,    43,    44,    65,    38,
      47,    48,    49,   286,    66,    30,    67,    93,   291,    77,
      77,    69,    70,    71,    72,    73,    74,    75,    20,    21,
      22,    23,    24,   310,    26,    27,    64,   314,    65,    68,
      69,    70,    71,    72,    73,    80,   112,    76,    77,    78,
      79,    80,    69,    70,    71,    72,    73,    74,    75,    67,
     222,    93,    65,   129,    93,    65,   132,    65,   248,    93,
     107,    72,    73,    74,    75,   112,    73,    74,    75,   117,
      91,    92,    66,   263,    74,    75,   123,    66,    65,    67,
     242,    18,   129,   228,   131,   132,    90,    92,   164,   165,
     166,    92,    95,    18,    91,    91,   143,   144,   145,   146,
     147,   142,   149,    64,    80,   250,   169,   154,   155,   185,
      91,   301,    91,   160,    91,    64,    91,   164,   165,   166,
      91,    91,    64,    92,   172,    93,   151,   174,    93,    93,
      92,    18,   179,    71,    72,    73,    74,    75,   185,    92,
      16,    65,    38,   206,    69,    70,    71,    72,    73,    74,
      75,    47,    18,   298,     3,     4,     5,     6,     7,     8,
       9,   208,    79,    81,    66,    14,    15,    16,    66,    66,
     315,    67,    68,    69,    70,    71,    72,    73,    66,    92,
      76,    77,    78,    79,    80,   232,    38,    66,    91,    48,
      39,    40,    18,    94,    66,    64,    81,    93,    65,   246,
     276,    94,   249,    97,    90,    38,   253,    45,    92,    58,
      59,    13,    92,    65,    47,    36,    68,    69,    70,    71,
      72,    73,    64,    13,    76,    77,    78,    79,    80,   276,
      94,    94,    94,    34,    16,    68,    69,    70,    71,    72,
      73,    93,   289,    76,    77,    78,    79,    80,   292,    66,
      94,    38,    92,    13,    66,    64,   300,    93,    64,    66,
      93,     0,    16,   307,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    92,    36,    14,    15,    16,    94,    64,
      19,    68,    69,    70,    71,    72,    73,    95,    51,    76,
      77,    78,    79,    80,    33,    94,   242,   314,    37,    38,
      39,    40,    41,    42,    43,    44,    93,    46,    47,   243,
      49,    50,    51,    52,    53,    54,    55,    56,   172,    58,
      59,    60,    61,   246,   267,   155,    65,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    38,    -1,    69,    70,    71,
      72,    73,    74,    75,    93,    -1,    -1,    96,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    14,
      15,    16,    94,    -1,    19,    68,    69,    70,    71,    72,
      73,    -1,    -1,    76,    77,    78,    79,    80,    33,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      93,    46,    47,    35,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    61,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    70,    71,    72,    73,    38,
      -1,    76,    77,    78,    79,    80,    -1,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    96,    70,    71,    72,    73,    74,    75,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    76,    77,    78,
      79,    80,    69,    70,    71,    72,    73,    74,    75,    -1,
      61,    -1,    63,    64,    93,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      69,    70,    71,    72,    73,    74,    75,    -1,    -1,    -1,
      -1,    -1,    93,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    92,    -1,    94,    -1,    57,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    94,    69,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    79,
      80,    92,    69,    70,    71,    72,    73,    74,    75,    69,
      70,    71,    72,    73,    74,    75,    69,    70,    71,    72,
      73,    74,    75,    76,    91,    -1,    79,    80,    62,    -1,
      64,    91,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    64,    -1,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    64,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    58,    59,    60,    61,    65,    68,    69,
      70,    71,    72,    73,    76,    77,    78,    79,    80,    93,
      96,    99,   100,   101,   109,   113,   115,   117,   118,   125,
      64,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   102,   105,   123,   102,
     102,   105,   102,    67,    67,    68,    77,   125,   118,   102,
      66,   102,    66,   105,   125,    77,    64,   123,    65,    77,
      65,    65,   123,    65,    29,    30,    31,    93,   107,   108,
     107,    65,    93,   125,   102,   123,   124,    57,   123,    66,
      66,    67,    65,    18,   125,   125,   125,   125,   125,    93,
     125,    18,    80,   125,   126,   126,   125,   114,     0,   100,
      90,    95,    92,    69,    70,    71,    72,    73,    74,    75,
      91,    92,    91,    91,    91,    91,    91,    91,    91,    64,
      18,    64,    91,    64,    93,    93,    93,   125,   113,    92,
     113,   126,    92,   123,    18,    92,    16,    65,    18,    10,
     125,   125,   126,   125,   126,    92,    79,    81,    94,   109,
     110,   111,   109,   118,   125,   125,   125,   125,   125,   125,
      66,   102,    66,    66,   121,   122,    47,    67,    93,   119,
     120,   125,   127,   129,   130,   130,    93,   119,    66,    66,
      92,   125,    91,   122,   126,   126,   126,    94,    48,   107,
      94,   124,    18,   125,    66,    64,    65,   125,    94,    81,
     126,    97,    90,    92,    45,    13,   107,   119,    92,    18,
      36,   128,    64,    34,   122,    13,    94,    94,    94,   113,
      34,   125,    16,    91,   110,   121,    66,   127,    94,   119,
     125,   113,    92,   125,    13,    66,    93,    64,   119,    20,
      21,    22,    23,    24,    26,    27,   106,   128,    64,    35,
     116,    66,    16,   103,   126,   103,    92,   125,    36,   103,
      61,    63,    93,   105,    94,    64,   113,    62,   105,   119,
     104,   105,   101,   112,    95,    94,   112,   113
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,    99,   100,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   102,   102,   103,   103,   103,   103,   103,   104,   103,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   108,   108,   108,
     108,   109,   109,   110,   110,   111,   112,   112,   113,   113,
     114,   113,   113,   113,   113,   113,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   124,
     124,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   126,   126,   127,   128,   128,   129,   129,
     130
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     8,     7,     9,     8,     4,
       2,     6,     4,     4,     4,     4,     4,     4,     2,     2,
       4,     1,     3,     0,     2,     3,     3,     4,     0,     6,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     4,     4,
       3,     1,     3,     1,     3,     1,     1,     3,     1,     1,
       0,     4,     3,     3,     5,     9,     0,     2,     2,     2,
       4,     1,     2,     2,     2,     2,     2,     3,     6,     3,
       3,     8,     2,     3,     4,     1,     2,     1,     2,     1,
       2,     1,     1,     4,     5,     0,     2,     1,     1,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     4,     1,     3,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     4,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     0,     2,     2,     4,
       1
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
#line 1527 "syn.tab.c"
    break;

  case 5: /* definition: FUNC namedId ':' vsortlist PFEIL Sort VORRANG att  */
#line 96 "syn.y"
                                                                    {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1535 "syn.tab.c"
    break;

  case 6: /* definition: OTHER func ':' vsortlist PFEIL Sort att  */
#line 99 "syn.y"
                                                                  { (yyval.y_nod)=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1544 "syn.tab.c"
    break;

  case 7: /* definition: ATT Sort Id ',' Id ',' Id ',' Id  */
#line 103 "syn.y"
                                                           { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufkt(name((yyvsp[0].y_sym))))))));	}
#line 1555 "syn.tab.c"
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
#line 1571 "syn.tab.c"
    break;

  case 9: /* definition: VAR idlist ':' Sort  */
#line 120 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1577 "syn.tab.c"
    break;

  case 10: /* definition: NUM Sort  */
#line 121 "syn.y"
                                                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* sets numbertype for mknum */}
#line 1583 "syn.tab.c"
    break;

  case 11: /* definition: SUBSORT Sort ',' Sort ATT Id  */
#line 122 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort */
										      mknod(PARAM,(Node *) (yyvsp[-4].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufkt(name((yyvsp[0].y_sym))))));}
#line 1590 "syn.tab.c"
    break;

  case 12: /* definition: INTNUM Sort ATT Id  */
#line 124 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) intnum_def,    /* 2026: sort of integers */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufkt(name((yyvsp[0].y_sym)))));}
#line 1597 "syn.tab.c"
    break;

  case 13: /* definition: NUM idlist ':' Sort  */
#line 126 "syn.y"
                                                                 { /* Variables for numeric numbers */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1604 "syn.tab.c"
    break;

  case 14: /* definition: CST idlist ':' Sort  */
#line 128 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1610 "syn.tab.c"
    break;

  case 15: /* definition: SPEC Alg ':' alglist  */
#line 129 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1616 "syn.tab.c"
    break;

  case 16: /* definition: SPEC Alg ':' formlist  */
#line 130 "syn.y"
                                                         {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1622 "syn.tab.c"
    break;

  case 17: /* definition: ADDSPEC Alg ':' formlist  */
#line 131 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1628 "syn.tab.c"
    break;

  case 18: /* definition: SORT idlist  */
#line 132 "syn.y"
                                                                             {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1634 "syn.tab.c"
    break;

  case 19: /* definition: ALG idlist  */
#line 134 "syn.y"
                                                     {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1640 "syn.tab.c"
    break;

  case 20: /* definition: TERM idlist ':' Sort  */
#line 135 "syn.y"
                                                   {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1646 "syn.tab.c"
    break;

  case 21: /* idlist: namedId  */
#line 137 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1652 "syn.tab.c"
    break;

  case 22: /* idlist: namedId ',' idlist  */
#line 138 "syn.y"
                                                        {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1658 "syn.tab.c"
    break;

  case 23: /* att: %empty  */
#line 146 "syn.y"
                                        { (yyval.y_nod) = NULL;}
#line 1664 "syn.tab.c"
    break;

  case 24: /* att: ATT namedId  */
#line 147 "syn.y"
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
#line 1680 "syn.tab.c"
    break;

  case 25: /* att: ATT SYMBOLIC namedId  */
#line 158 "syn.y"
                                                        { /* 2026: symbolic C function (symfkt.c): gets terms */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 0); }
#line 1687 "syn.tab.c"
    break;

  case 26: /* att: ATT RULES alglist  */
#line 160 "syn.y"
                                                { /* 2026: function defined by a rule list: f(..) is REWR f(..) : alglist */
			                  (yyval.y_nod) = mknod(ATT,(Node *) rules_sfkt(),mknod(PARAM,(yyvsp[0].y_nod),NULL)); }
#line 1694 "syn.tab.c"
    break;

  case 27: /* att: ATT SYMBOLIC HOLD namedId  */
#line 162 "syn.y"
                                                        { /* 2026: plus arguments unevaluated (matchq) */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 1); }
#line 1701 "syn.tab.c"
    break;

  case 28: /* $@1: %empty  */
#line 164 "syn.y"
                                          {block_begin();no_protect();}
#line 1707 "syn.tab.c"
    break;

  case 29: /* att: ATT '(' $@1 d_list ')' instruction  */
#line 165 "syn.y"
                                                                                        {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1713 "syn.tab.c"
    break;

  case 30: /* namedId: Id  */
#line 167 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1719 "syn.tab.c"
    break;

  case 31: /* namedId: Const  */
#line 168 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1725 "syn.tab.c"
    break;

  case 32: /* namedId: Var  */
#line 169 "syn.y"
                         { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1731 "syn.tab.c"
    break;

  case 33: /* namedId: func  */
#line 170 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1737 "syn.tab.c"
    break;

  case 34: /* namedId: Sort  */
#line 171 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1743 "syn.tab.c"
    break;

  case 35: /* namedId: Alg  */
#line 172 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1749 "syn.tab.c"
    break;

  case 36: /* namedId: Term  */
#line 173 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1755 "syn.tab.c"
    break;

  case 37: /* VORRANG: %empty  */
#line 176 "syn.y"
                                                        {(yyval.y_int) = Func;}
#line 1761 "syn.tab.c"
    break;

  case 38: /* VORRANG: LA1  */
#line 177 "syn.y"
                                                                        {(yyval.y_int) = La1;	/* Left-associative */}
#line 1767 "syn.tab.c"
    break;

  case 39: /* VORRANG: LA2  */
#line 178 "syn.y"
                                                                        {(yyval.y_int) = La2;	/* Left-associative */}
#line 1773 "syn.tab.c"
    break;

  case 40: /* VORRANG: LA3  */
#line 179 "syn.y"
                                                                        {(yyval.y_int) = La3;	/* Left-associative */}
#line 1779 "syn.tab.c"
    break;

  case 41: /* VORRANG: LA4  */
#line 180 "syn.y"
                                                                        {(yyval.y_int) = La4;	/* Left-associative */}
#line 1785 "syn.tab.c"
    break;

  case 42: /* VORRANG: LA5  */
#line 181 "syn.y"
                                                                        {(yyval.y_int) = La5;	/* Left-associative */}
#line 1791 "syn.tab.c"
    break;

  case 43: /* VORRANG: RA  */
#line 182 "syn.y"
                                                                        {(yyval.y_int) = Ra;  	/* Right-associative */}
#line 1797 "syn.tab.c"
    break;

  case 44: /* VORRANG: RU  */
#line 183 "syn.y"
                                                                        {(yyval.y_int) = Ru;	  /* Right unary */}
#line 1803 "syn.tab.c"
    break;

  case 45: /* condition: condfunc  */
#line 185 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1809 "syn.tab.c"
    break;

  case 46: /* condition: condfunc ',' condition  */
#line 186 "syn.y"
                                                        {(yyval.y_nod) = mknod(Cond,(Node *) and_cond,mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod)));}
#line 1815 "syn.tab.c"
    break;

  case 47: /* condfunc: LB '(' termlist ')'  */
#line 188 "syn.y"
                              {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1821 "syn.tab.c"
    break;

  case 48: /* condfunc: IN '(' termlist ')'  */
#line 189 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1827 "syn.tab.c"
    break;

  case 49: /* condfunc: NIN '(' termlist ')'  */
#line 190 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1833 "syn.tab.c"
    break;

  case 50: /* condfunc: '(' term ')'  */
#line 191 "syn.y"
                                                                        {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1839 "syn.tab.c"
    break;

  case 51: /* instructions: instruction  */
#line 193 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1845 "syn.tab.c"
    break;

  case 52: /* instructions: instruction ';' instructions  */
#line 194 "syn.y"
                                                                                       {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1851 "syn.tab.c"
    break;

  case 53: /* tinstructions: oinstructions  */
#line 196 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1857 "syn.tab.c"
    break;

  case 54: /* tinstructions: oinstructions '\n' tinstructions  */
#line 197 "syn.y"
                                                                                                                {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1863 "syn.tab.c"
    break;

  case 55: /* oinstructions: instructions  */
#line 199 "syn.y"
                                                {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1869 "syn.tab.c"
    break;

  case 56: /* d_list: definition  */
#line 204 "syn.y"
                                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1875 "syn.tab.c"
    break;

  case 57: /* d_list: definition ';' d_list  */
#line 205 "syn.y"
                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1881 "syn.tab.c"
    break;

  case 58: /* instruction: aninstruction  */
#line 207 "syn.y"
                                {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Check local variables ! */ }
#line 1887 "syn.tab.c"
    break;

  case 59: /* instruction: definition  */
#line 208 "syn.y"
                                                                        {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1893 "syn.tab.c"
    break;

  case 60: /* $@2: %empty  */
#line 209 "syn.y"
                                                                                                        {block_begin();no_protect();}
#line 1899 "syn.tab.c"
    break;

  case 61: /* instruction: '{' $@2 tinstructions '}'  */
#line 210 "syn.y"
                                                                        {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 1909 "syn.tab.c"
    break;

  case 62: /* instruction: WHILE condition instruction  */
#line 215 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* then becomes $3 */)));
																		WHILE_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1916 "syn.tab.c"
    break;

  case 63: /* instruction: IF condition instruction  */
#line 218 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		IF_THEN(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1923 "syn.tab.c"
    break;

  case 64: /* instruction: IF condition instruction ELSE instruction  */
#line 220 "syn.y"
                                                                        {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(merk) = (yyvsp[-2].y_nod);IF_ELSE(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1930 "syn.tab.c"
    break;

  case 65: /* instruction: FOR term EQ term TO term step DO instruction  */
#line 223 "syn.y"
                                                                                                                {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) forschleife,
																mknod(PARAM,
																	mknod(PARAM,(yyvsp[-5].y_nod),(yyvsp[-3].y_nod)),
																	mknod(PARAM,
																		mknod(PARAM,(yyvsp[-2].y_nod),(Node *) ((yyvsp[-7].y_nod))),
																		NULL /* $9 */) )));	
														FOR_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1942 "syn.tab.c"
    break;

  case 66: /* aninstruction: %empty  */
#line 232 "syn.y"
                                        {(yyval.y_nod)=NULL;}
#line 1948 "syn.tab.c"
    break;

  case 67: /* aninstruction: SYS String  */
#line 233 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) system_fkt,(Node *) ((yyvsp[0].y_sym)));}
#line 1954 "syn.tab.c"
    break;

  case 68: /* aninstruction: INC String  */
#line 234 "syn.y"
                                                                        {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fkt,(Node *) ((yyvsp[0].y_sym))); }
#line 1960 "syn.tab.c"
    break;

  case 69: /* aninstruction: INFO namedId  */
#line 235 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) info_fkt,(Node *) ((yyvsp[0].y_nod))); }
#line 1966 "syn.tab.c"
    break;

  case 70: /* aninstruction: REWR term ':' alglist  */
#line 236 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 1973 "syn.tab.c"
    break;

  case 71: /* aninstruction: prntlist  */
#line 238 "syn.y"
                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 1979 "syn.tab.c"
    break;

  case 72: /* aninstruction: PRTNUM String  */
#line 239 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 1985 "syn.tab.c"
    break;

  case 73: /* aninstruction: PRT prntlist  */
#line 240 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* without \n */ }
#line 1991 "syn.tab.c"
    break;

  case 74: /* aninstruction: OUT String  */
#line 241 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 1997 "syn.tab.c"
    break;

  case 75: /* aninstruction: DATA String  */
#line 242 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 2003 "syn.tab.c"
    break;

  case 76: /* aninstruction: DATA Const  */
#line 243 "syn.y"
                                                                        {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 2014 "syn.tab.c"
    break;

  case 77: /* aninstruction: Term EQ term  */
#line 249 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 2020 "syn.tab.c"
    break;

  case 78: /* aninstruction: Term EQ REWR term ':' alglist  */
#line 250 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 2026 "syn.tab.c"
    break;

  case 79: /* aninstruction: Const EQ term  */
#line 251 "syn.y"
                                                        { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 2032 "syn.tab.c"
    break;

  case 80: /* aninstruction: EXE func Id  */
#line 252 "syn.y"
                                                        {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufkt(name((yyvsp[0].y_sym)));
 													}
#line 2042 "syn.tab.c"
    break;

  case 81: /* aninstruction: LIFT '(' termlist ')' TO '(' termlist ')'  */
#line 257 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 2048 "syn.tab.c"
    break;

  case 82: /* aninstruction: DBG Const  */
#line 258 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 2054 "syn.tab.c"
    break;

  case 83: /* aninstruction: STEPS Alg String  */
#line 259 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) steps_fkt,mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2060 "syn.tab.c"
    break;

  case 84: /* aninstruction: SYMBOLIC String EQ String  */
#line 260 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fkt,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2066 "syn.tab.c"
    break;

  case 85: /* aninstruction: SYMBOLIC  */
#line 261 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fkt,NULL);  /* delete roles */}
#line 2072 "syn.tab.c"
    break;

  case 86: /* aninstruction: RETURN term  */
#line 262 "syn.y"
                                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) return_fkt,(yyvsp[0].y_nod));}
#line 2078 "syn.tab.c"
    break;

  case 87: /* aninstruction: QUIT  */
#line 263 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fkt,NULL);}
#line 2084 "syn.tab.c"
    break;

  case 88: /* aninstruction: OPT idlist  */
#line 264 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,(yyvsp[0].y_nod));}
#line 2090 "syn.tab.c"
    break;

  case 89: /* aninstruction: OPT  */
#line 265 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,NULL);   /* delete */}
#line 2096 "syn.tab.c"
    break;

  case 90: /* aninstruction: COMM funclist  */
#line 266 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,(yyvsp[0].y_nod));}
#line 2102 "syn.tab.c"
    break;

  case 91: /* aninstruction: COMM  */
#line 267 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,NULL);  /* delete */}
#line 2108 "syn.tab.c"
    break;

  case 92: /* aninstruction: DEFAULT  */
#line 268 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,NULL); /* delete */}
#line 2114 "syn.tab.c"
    break;

  case 93: /* aninstruction: DEFAULT func EQ term  */
#line 269 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),NULL),(yyvsp[0].y_nod)));}
#line 2121 "syn.tab.c"
    break;

  case 94: /* aninstruction: DEFAULT RIGHT func EQ term  */
#line 271 "syn.y"
                                                     {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),mknod(PARAM,NULL,NULL)),(yyvsp[0].y_nod)));}
#line 2128 "syn.tab.c"
    break;

  case 95: /* step: %empty  */
#line 274 "syn.y"
                        {(yyval.y_nod)=(Node *) NULL;}
#line 2134 "syn.tab.c"
    break;

  case 96: /* step: STEP term  */
#line 275 "syn.y"
                                        {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2140 "syn.tab.c"
    break;

  case 97: /* prntexpr: term  */
#line 277 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2146 "syn.tab.c"
    break;

  case 98: /* prntexpr: String  */
#line 278 "syn.y"
                                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2152 "syn.tab.c"
    break;

  case 99: /* prntlist: prntexpr  */
#line 280 "syn.y"
                                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2158 "syn.tab.c"
    break;

  case 100: /* prntlist: prntexpr ',' prntlist  */
#line 281 "syn.y"
                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2164 "syn.tab.c"
    break;

  case 101: /* alglist: Alg2  */
#line 283 "syn.y"
                                                                {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2170 "syn.tab.c"
    break;

  case 102: /* alglist: Alg2 ',' alglist  */
#line 284 "syn.y"
                                                        {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2176 "syn.tab.c"
    break;

  case 103: /* Alg2: Alg  */
#line 286 "syn.y"
                                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2182 "syn.tab.c"
    break;

  case 104: /* Alg2: '(' alglist ')'  */
#line 287 "syn.y"
                                                                {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2188 "syn.tab.c"
    break;

  case 105: /* sortlist: Sort  */
#line 289 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2194 "syn.tab.c"
    break;

  case 106: /* sortlist: Sort ',' sortlist  */
#line 290 "syn.y"
                                                                {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2200 "syn.tab.c"
    break;

  case 107: /* vsortlist: sortlist  */
#line 292 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2206 "syn.tab.c"
    break;

  case 108: /* vsortlist: sortlist VARPAR  */
#line 293 "syn.y"
                                                                        {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2212 "syn.tab.c"
    break;

  case 109: /* func: Func  */
#line 295 "syn.y"
                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2218 "syn.tab.c"
    break;

  case 110: /* func: La1  */
#line 296 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2224 "syn.tab.c"
    break;

  case 111: /* func: La2  */
#line 297 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2230 "syn.tab.c"
    break;

  case 112: /* func: La3  */
#line 298 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2236 "syn.tab.c"
    break;

  case 113: /* func: La4  */
#line 299 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2242 "syn.tab.c"
    break;

  case 114: /* func: La5  */
#line 300 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2248 "syn.tab.c"
    break;

  case 115: /* func: Ra  */
#line 301 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2254 "syn.tab.c"
    break;

  case 116: /* func: Ru  */
#line 302 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2260 "syn.tab.c"
    break;

  case 117: /* func: Bra  */
#line 303 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2266 "syn.tab.c"
    break;

  case 118: /* func: Bra1  */
#line 304 "syn.y"
                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2272 "syn.tab.c"
    break;

  case 119: /* funclist: func  */
#line 306 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2278 "syn.tab.c"
    break;

  case 120: /* funclist: func ',' funclist  */
#line 307 "syn.y"
                                                        {(yyval.y_nod) = mknod(Functs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2284 "syn.tab.c"
    break;

  case 121: /* term: Term  */
#line 309 "syn.y"
                                                                        {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); does not remember dependencies and does not work in blocks */ 
														}
#line 2291 "syn.tab.c"
    break;

  case 122: /* term: LAST  */
#line 311 "syn.y"
                                                                                        {(yyval.y_nod) = (Node *) lastterm;}
#line 2297 "syn.tab.c"
    break;

  case 123: /* term: Const  */
#line 312 "syn.y"
                                                                                        {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2303 "syn.tab.c"
    break;

  case 124: /* term: Const Bra1 termlist Bra2  */
#line 313 "syn.y"
                                                   {nphilf=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),nphilf), nphilf);}
#line 2310 "syn.tab.c"
    break;

  case 125: /* term: Var  */
#line 315 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2316 "syn.tab.c"
    break;

  case 126: /* term: '(' term ')'  */
#line 316 "syn.y"
                                                    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2322 "syn.tab.c"
    break;

  case 127: /* term: term Ru  */
#line 317 "syn.y"
                                                                      {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2328 "syn.tab.c"
    break;

  case 128: /* term: Func term  */
#line 318 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2334 "syn.tab.c"
    break;

  case 129: /* term: La1 term  */
#line 319 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2340 "syn.tab.c"
    break;

  case 130: /* term: La2 term  */
#line 320 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2346 "syn.tab.c"
    break;

  case 131: /* term: La3 term  */
#line 321 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2352 "syn.tab.c"
    break;

  case 132: /* term: La4 term  */
#line 322 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2358 "syn.tab.c"
    break;

  case 133: /* term: La5 term  */
#line 323 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2364 "syn.tab.c"
    break;

  case 134: /* term: Bra termlist Bra  */
#line 324 "syn.y"
                                                  {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2370 "syn.tab.c"
    break;

  case 135: /* term: Bra1 termlist Bra2  */
#line 325 "syn.y"
                                                {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2376 "syn.tab.c"
    break;

  case 136: /* term: Func '(' termlist ')'  */
#line 326 "syn.y"
                                                        {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2382 "syn.tab.c"
    break;

  case 137: /* term: term La1 term  */
#line 327 "syn.y"
                                                    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2389 "syn.tab.c"
    break;

  case 138: /* term: term La2 term  */
#line 329 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2396 "syn.tab.c"
    break;

  case 139: /* term: term La3 term  */
#line 331 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2403 "syn.tab.c"
    break;

  case 140: /* term: term La4 term  */
#line 333 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2410 "syn.tab.c"
    break;

  case 141: /* term: term La5 term  */
#line 335 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2417 "syn.tab.c"
    break;

  case 142: /* term: term Ra term  */
#line 337 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2424 "syn.tab.c"
    break;

  case 143: /* termlist: term  */
#line 340 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2430 "syn.tab.c"
    break;

  case 144: /* termlist: term ',' termlist  */
#line 341 "syn.y"
                                                        {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2436 "syn.tab.c"
    break;

  case 145: /* formula: term EQ term  */
#line 343 "syn.y"
                                        {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2442 "syn.tab.c"
    break;

  case 146: /* vinstr: %empty  */
#line 345 "syn.y"
                                                                {(yyval.y_nod) = NULL;}
#line 2448 "syn.tab.c"
    break;

  case 147: /* vinstr: DO instruction  */
#line 346 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2454 "syn.tab.c"
    break;

  case 148: /* cformula: formula vinstr  */
#line 348 "syn.y"
                                                                        {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2461 "syn.tab.c"
    break;

  case 149: /* cformula: IF condition formula vinstr  */
#line 350 "syn.y"
                                               {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2468 "syn.tab.c"
    break;

  case 150: /* formlist: cformula  */
#line 353 "syn.y"
                                                                {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL serves for hooking in further formulas !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. because of SPEC real : A+B=C;a=3 */
															}
#line 2476 "syn.tab.c"
    break;


#line 2480 "syn.tab.c"

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

#line 357 "syn.y"


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
