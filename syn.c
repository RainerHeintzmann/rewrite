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


#include <string.h> /* fuer memcpy,strcmp */
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


#line 114 "syn.tab.c"

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
  YYSYMBOL_Id = 61,                        /* Id  */
  YYSYMBOL_String = 62,                    /* String  */
  YYSYMBOL_Sort = 63,                      /* Sort  */
  YYSYMBOL_Alg = 64,                       /* Alg  */
  YYSYMBOL_Term = 65,                      /* Term  */
  YYSYMBOL_La1 = 66,                       /* La1  */
  YYSYMBOL_La2 = 67,                       /* La2  */
  YYSYMBOL_La3 = 68,                       /* La3  */
  YYSYMBOL_La4 = 69,                       /* La4  */
  YYSYMBOL_La5 = 70,                       /* La5  */
  YYSYMBOL_Ru = 71,                        /* Ru  */
  YYSYMBOL_Ra = 72,                        /* Ra  */
  YYSYMBOL_Func = 73,                      /* Func  */
  YYSYMBOL_Const = 74,                     /* Const  */
  YYSYMBOL_Var = 75,                       /* Var  */
  YYSYMBOL_Bra = 76,                       /* Bra  */
  YYSYMBOL_Bra1 = 77,                      /* Bra1  */
  YYSYMBOL_Bra2 = 78,                      /* Bra2  */
  YYSYMBOL_Terms = 79,                     /* Terms  */
  YYSYMBOL_Form = 80,                      /* Form  */
  YYSYMBOL_Sorts = 81,                     /* Sorts  */
  YYSYMBOL_Functs = 82,                    /* Functs  */
  YYSYMBOL_Forms = 83,                     /* Forms  */
  YYSYMBOL_Algs = 84,                      /* Algs  */
  YYSYMBOL_Cond2 = 85,                     /* Cond2  */
  YYSYMBOL_Cond = 86,                      /* Cond  */
  YYSYMBOL_87_n_ = 87,                     /* '\n'  */
  YYSYMBOL_88_ = 88,                       /* ':'  */
  YYSYMBOL_89_ = 89,                       /* ','  */
  YYSYMBOL_90_ = 90,                       /* '('  */
  YYSYMBOL_91_ = 91,                       /* ')'  */
  YYSYMBOL_92_ = 92,                       /* ';'  */
  YYSYMBOL_93_ = 93,                       /* '{'  */
  YYSYMBOL_94_ = 94,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_prog = 96,                      /* prog  */
  YYSYMBOL_line = 97,                      /* line  */
  YYSYMBOL_definition = 98,                /* definition  */
  YYSYMBOL_idlist = 99,                    /* idlist  */
  YYSYMBOL_att = 100,                      /* att  */
  YYSYMBOL_101_1 = 101,                    /* $@1  */
  YYSYMBOL_namedId = 102,                  /* namedId  */
  YYSYMBOL_VORRANG = 103,                  /* VORRANG  */
  YYSYMBOL_condition = 104,                /* condition  */
  YYSYMBOL_condfunc = 105,                 /* condfunc  */
  YYSYMBOL_instructions = 106,             /* instructions  */
  YYSYMBOL_tinstructions = 107,            /* tinstructions  */
  YYSYMBOL_oinstructions = 108,            /* oinstructions  */
  YYSYMBOL_d_list = 109,                   /* d_list  */
  YYSYMBOL_instruction = 110,              /* instruction  */
  YYSYMBOL_111_2 = 111,                    /* $@2  */
  YYSYMBOL_aninstruction = 112,            /* aninstruction  */
  YYSYMBOL_step = 113,                     /* step  */
  YYSYMBOL_prntexpr = 114,                 /* prntexpr  */
  YYSYMBOL_prntlist = 115,                 /* prntlist  */
  YYSYMBOL_alglist = 116,                  /* alglist  */
  YYSYMBOL_Alg2 = 117,                     /* Alg2  */
  YYSYMBOL_sortlist = 118,                 /* sortlist  */
  YYSYMBOL_vsortlist = 119,                /* vsortlist  */
  YYSYMBOL_func = 120,                     /* func  */
  YYSYMBOL_funclist = 121,                 /* funclist  */
  YYSYMBOL_term = 122,                     /* term  */
  YYSYMBOL_termlist = 123,                 /* termlist  */
  YYSYMBOL_formula = 124,                  /* formula  */
  YYSYMBOL_vinstr = 125,                   /* vinstr  */
  YYSYMBOL_cformula = 126,                 /* cformula  */
  YYSYMBOL_formlist = 127                  /* formlist  */
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
#define YYFINAL  136
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   673

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   341


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
      87,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      90,    91,     2,     2,    89,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    88,    92,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,    94,     2,     2,     2,     2,
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
      85,    86
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    84,    86,    94,    97,   101,   107,   118,
     119,   120,   122,   124,   126,   127,   128,   129,   130,   132,
     133,   135,   136,   144,   145,   156,   156,   159,   160,   161,
     162,   163,   164,   165,   168,   169,   170,   171,   172,   173,
     174,   175,   177,   178,   180,   181,   182,   183,   185,   186,
     188,   189,   191,   196,   197,   199,   200,   201,   201,   207,
     210,   212,   214,   224,   225,   226,   227,   228,   230,   231,
     232,   233,   234,   235,   241,   242,   243,   244,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   261,
     264,   265,   267,   268,   270,   271,   273,   274,   276,   277,
     279,   280,   282,   283,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   296,   297,   299,   301,   302,   303,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   319,   321,   323,   325,   327,   330,   331,
     333,   335,   336,   338,   340,   343
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
  "STEPS", "Id", "String", "Sort", "Alg", "Term", "La1", "La2", "La3",
  "La4", "La5", "Ru", "Ra", "Func", "Const", "Var", "Bra", "Bra1", "Bra2",
  "Terms", "Form", "Sorts", "Functs", "Forms", "Algs", "Cond2", "Cond",
  "'\\n'", "':'", "','", "'('", "')'", "';'", "'{'", "'}'", "$accept",
  "prog", "line", "definition", "idlist", "att", "$@1", "namedId",
  "VORRANG", "condition", "condfunc", "instructions", "tinstructions",
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

#define YYPACT_NINF (-249)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-32)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     339,   567,   567,   567,   567,   567,   -43,   -34,   456,   294,
     567,   584,    -9,   567,   456,   -30,  -249,     6,   596,   -19,
       7,    22,   596,    24,    -2,    -2,    25,     4,  -249,   456,
     567,   596,   550,     8,    30,    33,  -249,    80,   456,   456,
     456,   456,   456,   474,    -5,  -249,   456,   456,   456,  -249,
     248,  -249,  -249,    13,    11,  -249,    16,  -249,   486,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,    18,    20,  -249,    27,  -249,
      28,  -249,    29,    31,  -249,    35,   448,  -249,    36,   -51,
      37,    46,  -249,   115,  -249,    49,    38,  -249,  -249,  -249,
    -249,    52,  -249,    40,    41,    42,   456,   339,    60,   339,
    -249,   456,   486,  -249,    61,  -249,   596,   123,    63,   137,
      92,   138,   162,     9,    89,    19,     3,   456,  -249,   456,
     456,   397,    87,    88,    -6,   339,  -249,  -249,  -249,   339,
     294,   456,   456,   456,   456,   456,  -249,   456,   104,   567,
     105,   107,   372,   405,   -48,   108,   109,    84,   456,    86,
     107,  -249,   456,   456,   456,   436,   129,    -2,  -249,    97,
     596,   160,   456,   116,   128,  -249,   456,   486,   514,   111,
     486,   121,   456,  -249,  -249,  -249,  -249,   106,   122,  -249,
    -249,   162,     9,    89,    19,     3,     3,  -249,  -249,  -249,
     127,   165,   212,    -2,  -249,   423,  -249,   150,   125,   190,
    -249,  -249,  -249,   -48,  -249,  -249,  -249,   166,   202,   107,
     227,   152,   153,   154,  -249,   339,  -249,   207,  -249,   456,
     486,   230,  -249,   527,  -249,  -249,  -249,  -249,   339,   107,
    -249,   184,   456,   158,   -48,   456,   339,  -249,   161,   456,
     247,   198,  -249,  -249,  -249,  -249,   176,   486,   214,   -48,
    -249,  -249,   197,   190,  -249,  -249,   486,  -249,   215,   387,
     216,   261,   456,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,   261,  -249,   191,   456,   246,   261,   502,  -249,
     192,  -249,   232,   486,   339,  -249,  -249,  -249,  -249,  -249,
    -249,    43,   204,   218,    43,   339,  -249,  -249
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
      84,    86,    87,     0,     0,     0,    93,   116,     0,     0,
       0,     0,     0,     0,   118,   120,     0,     0,     0,    57,
      63,     2,    56,     0,    48,    55,    94,    68,    92,    27,
      31,    32,    33,   105,   106,   107,   108,   109,   111,   110,
     104,    28,    29,   112,   113,     0,    21,    30,     0,    18,
       0,    19,     0,     0,   116,   118,     0,    70,     0,    10,
       0,     0,    66,     0,    79,     0,     0,    72,    73,    71,
      65,     0,    64,     0,     0,     0,     0,    63,    42,    63,
      69,     0,    81,    83,   114,    85,     0,     0,     0,     0,
       0,     0,   124,   125,   126,   127,   128,     0,   123,     0,
       0,   138,     0,     0,     0,    63,     1,     3,     4,    63,
       0,     0,     0,     0,     0,     0,   122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,     0,     0,     0,     0,    60,     0,    59,     0,
       0,     0,     0,     0,     0,    80,     0,    74,     0,     0,
      76,     0,     0,   129,   130,   121,    52,     0,    50,    49,
      95,   132,   133,   134,   135,   136,   137,    14,    22,     9,
     100,   102,     0,     0,    98,     0,    15,    96,     0,   141,
     145,    16,    17,     0,    67,    20,    13,     0,     0,     0,
       0,     0,     0,     0,    47,    63,    43,     0,   115,     0,
      88,     0,    12,     0,   131,   119,   139,    58,    63,     0,
     103,     0,     0,     0,     0,     0,    63,   143,     0,     0,
       0,     0,    44,    45,    46,    61,     0,    89,     0,     0,
      51,   101,    34,   141,    99,    97,   140,   142,     0,    90,
       0,    23,     0,    11,    75,    35,    36,    37,    38,    39,
      41,    40,    23,   144,     0,     0,     0,    23,     0,     6,
       0,     5,     0,    91,    63,     8,    25,    24,    78,     7,
      62,     0,    53,     0,     0,    63,    54,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -249,  -249,   255,  -248,    15,  -214,  -249,    -4,  -249,   -23,
    -249,  -120,    73,  -249,    23,  -104,  -249,  -249,  -249,  -249,
      -1,  -148,  -249,    81,  -149,    -8,   142,    -7,   -35,    77,
      65,  -249,   173
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    50,    51,    52,    75,   289,   301,    76,   282,   107,
     108,    53,   187,   188,   303,    54,   135,    55,   286,    56,
      57,   243,   207,   201,   202,    77,   115,    58,   132,   209,
     247,   210,   211
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,    86,   109,   166,   206,   168,   214,    93,    87,    92,
      96,   220,   133,   129,   101,   186,   204,    78,    79,   189,
      81,    82,   112,   114,   117,    88,    90,   103,   104,   105,
      83,   122,   123,   124,   125,   126,   128,   -31,   -31,   131,
     131,   134,   213,    97,    94,   113,     1,     2,     3,     4,
       5,     6,     7,   302,    91,    98,   302,    10,    11,    12,
     141,   142,   143,   144,   145,   146,   147,    95,   291,    99,
     250,   118,   130,   295,   146,   147,   169,   143,   144,   145,
     146,   147,    17,    18,   100,   185,   102,   110,   106,   145,
     146,   147,   179,   119,   111,   181,   265,   120,   121,   165,
     138,    33,    34,   139,   131,   140,   148,   157,   171,   149,
     159,   274,   130,   161,   177,   150,   151,   152,   186,   153,
     178,   255,   180,   131,   155,   156,   160,   221,   222,   223,
     162,   163,   164,   158,   191,   192,   193,   194,   195,   190,
     196,   172,   267,   245,   226,   208,   208,   236,   176,   167,
     170,   218,   173,   174,   175,   131,   131,   131,   144,   145,
     146,   147,   114,   183,   198,   230,   184,   197,   199,   233,
     200,   215,   216,   217,   219,   131,    16,   225,   229,   231,
     242,   141,   142,   143,   144,   145,   146,   147,   227,   232,
     300,   141,   142,   143,   144,   145,   146,   147,   134,   235,
     237,   307,   234,    84,    38,    39,    40,    41,    42,   238,
     240,    43,    85,    45,    46,    47,   239,   275,   276,   277,
     278,   279,   257,   280,   281,   241,   246,   248,    48,   142,
     143,   144,   145,   146,   147,   208,   249,   290,   266,   244,
     251,   256,   269,   252,   253,   254,   258,   262,   136,   264,
     268,     1,     2,     3,     4,     5,     6,     7,     8,     9,
     270,   271,    10,    11,    12,   131,   272,    13,   141,   142,
     143,   144,   145,   146,   147,   273,   284,   288,   293,   287,
     292,    14,   294,   298,   297,    15,    16,    17,    18,    19,
      20,    21,    22,   299,    23,    24,   304,    25,    26,    27,
      28,    29,    30,    31,    32,   137,    33,    34,    35,   305,
      36,   260,   228,    37,    38,    39,    40,    41,    42,   263,
     261,    43,    44,    45,    46,    47,   212,   306,   283,     0,
       0,     0,    16,     0,     0,     0,     0,     0,    48,     0,
       0,    49,     1,     2,     3,     4,     5,     6,     7,     8,
       9,     0,     0,    10,    11,    12,    36,     0,    13,    84,
      38,    39,    40,    41,    42,     0,     0,    43,    85,    45,
      46,    47,    14,     0,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,    48,    23,    24,     0,    25,    26,
      27,    28,    29,    30,    31,    32,     0,    33,    34,    35,
       0,    36,     0,     0,    37,    38,    39,    40,    41,    42,
      16,     0,    43,    44,    45,    46,    47,     0,     0,   203,
       0,     0,   285,     0,     0,     0,     0,     0,     0,    48,
       0,     0,    49,     0,     0,     0,   204,    84,    38,    39,
      40,    41,    42,    16,     0,    43,    85,    45,    46,    47,
       0,     0,   203,   141,   142,   143,   144,   145,   146,   147,
       0,    16,   205,   141,   142,   143,   144,   145,   146,   147,
      84,    38,    39,    40,    41,    42,     0,     0,    43,    85,
      45,    46,    47,     0,     0,     0,   182,   204,    84,    38,
      39,    40,    41,    42,    16,    48,    43,    85,    45,    46,
      47,     0,   141,   142,   143,   144,   145,   146,   147,     0,
       0,     0,    16,   205,   141,   142,   143,   144,   145,   146,
     147,    84,    38,    39,    40,    41,    42,   224,     0,    43,
      85,    45,    46,    47,     0,     0,   154,     0,     0,    84,
      38,    39,    40,    41,    42,     0,    48,    43,    85,    45,
      46,    47,   141,   142,   143,   144,   145,   146,   147,     0,
       0,     0,     0,    59,   127,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     141,   142,   143,   144,   145,   146,   147,     0,     0,     0,
       0,     0,   296,   141,   142,   143,   144,   145,   146,   147,
       0,     0,     0,   182,     0,   185,     0,   116,     0,     0,
       0,     0,     0,     0,     0,   259,    63,    64,    65,    66,
      67,    68,    69,    70,     0,     0,    73,    74,    59,     0,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    59,     0,    89,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    63,    64,    65,    66,    67,    68,    69,    70,
       0,     0,    73,    74
};

static const yytype_int16 yycheck[] =
{
       4,     8,    25,   107,   152,   109,   154,    14,     9,    13,
      18,   160,    47,    18,    22,   135,    64,     2,     3,   139,
       5,    64,    29,    31,    32,    10,    11,    29,    30,    31,
      64,    38,    39,    40,    41,    42,    43,    88,    89,    46,
      47,    48,    90,    62,    74,    30,     3,     4,     5,     6,
       7,     8,     9,   301,    63,    74,   304,    14,    15,    16,
      66,    67,    68,    69,    70,    71,    72,    61,   282,    62,
     219,    63,    77,   287,    71,    72,   111,    68,    69,    70,
      71,    72,    39,    40,    62,    91,    62,    62,    90,    70,
      71,    72,   127,    63,    90,   130,   244,    64,    18,   106,
      87,    58,    59,    92,   111,    89,    88,    61,   116,    89,
      61,   259,    77,    61,   121,    88,    88,    88,   238,    88,
     127,   225,   129,   130,    88,    88,    88,   162,   163,   164,
      90,    90,    90,    18,   141,   142,   143,   144,   145,   140,
     147,    18,   246,    18,   167,   152,   153,   182,    10,    89,
      89,   158,    89,    16,    62,   162,   163,   164,    69,    70,
      71,    72,   170,    76,   149,   172,    78,    63,    63,   176,
      63,    63,    63,    89,    88,   182,    38,    48,    18,    63,
     203,    66,    67,    68,    69,    70,    71,    72,    91,    61,
     294,    66,    67,    68,    69,    70,    71,    72,   205,    78,
      94,   305,    91,    65,    66,    67,    68,    69,    70,    87,
      45,    73,    74,    75,    76,    77,    89,    20,    21,    22,
      23,    24,   229,    26,    27,    13,    36,    61,    90,    67,
      68,    69,    70,    71,    72,   242,    34,   272,   245,    89,
      13,    34,   249,    91,    91,    91,    16,    63,     0,    91,
      89,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      13,    63,    14,    15,    16,   272,    90,    19,    66,    67,
      68,    69,    70,    71,    72,    61,    61,    16,   285,    63,
      89,    33,    36,    91,   288,    37,    38,    39,    40,    41,
      42,    43,    44,    61,    46,    47,    92,    49,    50,    51,
      52,    53,    54,    55,    56,    50,    58,    59,    60,    91,
      62,   238,   170,    65,    66,    67,    68,    69,    70,   242,
     239,    73,    74,    75,    76,    77,   153,   304,   263,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    93,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    14,    15,    16,    62,    -1,    19,    65,
      66,    67,    68,    69,    70,    -1,    -1,    73,    74,    75,
      76,    77,    33,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    90,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    62,    -1,    -1,    65,    66,    67,    68,    69,    70,
      38,    -1,    73,    74,    75,    76,    77,    -1,    -1,    47,
      -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    -1,    93,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    69,    70,    38,    -1,    73,    74,    75,    76,    77,
      -1,    -1,    47,    66,    67,    68,    69,    70,    71,    72,
      -1,    38,    90,    66,    67,    68,    69,    70,    71,    72,
      65,    66,    67,    68,    69,    70,    -1,    -1,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    89,    64,    65,    66,
      67,    68,    69,    70,    38,    90,    73,    74,    75,    76,
      77,    -1,    66,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    38,    90,    66,    67,    68,    69,    70,    71,
      72,    65,    66,    67,    68,    69,    70,    91,    -1,    73,
      74,    75,    76,    77,    -1,    -1,    88,    -1,    -1,    65,
      66,    67,    68,    69,    70,    -1,    90,    73,    74,    75,
      76,    77,    66,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    61,    90,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    90,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    89,    -1,    91,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    76,    77,    61,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    61,    -1,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    76,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    58,    59,    60,    62,    65,    66,    67,
      68,    69,    70,    73,    74,    75,    76,    77,    90,    93,
      96,    97,    98,   106,   110,   112,   114,   115,   122,    61,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    99,   102,   120,    99,    99,
     102,    99,    64,    64,    65,    74,   122,   115,    99,    63,
      99,    63,   102,   122,    74,    61,   120,    62,    74,    62,
      62,   120,    62,    29,    30,    31,    90,   104,   105,   104,
      62,    90,   122,    99,   120,   121,    57,   120,    63,    63,
      64,    18,   122,   122,   122,   122,   122,    90,   122,    18,
      77,   122,   123,   123,   122,   111,     0,    97,    87,    92,
      89,    66,    67,    68,    69,    70,    71,    72,    88,    89,
      88,    88,    88,    88,    88,    88,    88,    61,    18,    61,
      88,    61,    90,    90,    90,   122,   110,    89,   110,   123,
      89,   120,    18,    89,    16,    62,    10,   122,   122,   123,
     122,   123,    89,    76,    78,    91,   106,   107,   108,   106,
     115,   122,   122,   122,   122,   122,   122,    63,    99,    63,
      63,   118,   119,    47,    64,    90,   116,   117,   122,   124,
     126,   127,   127,    90,   116,    63,    63,    89,   122,    88,
     119,   123,   123,   123,    91,    48,   104,    91,   121,    18,
     122,    63,    61,   122,    91,    78,   123,    94,    87,    89,
      45,    13,   104,   116,    89,    18,    36,   125,    61,    34,
     119,    13,    91,    91,    91,   110,    34,   122,    16,    88,
     107,   118,    63,   124,    91,   116,   122,   110,    89,   122,
      13,    63,    90,    61,   116,    20,    21,    22,    23,    24,
      26,    27,   103,   125,    61,    35,   113,    63,    16,   100,
     123,   100,    89,   122,    36,   100,    90,   102,    91,    61,
     110,   101,    98,   109,    92,    91,   109,   110
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    95,    96,    96,    97,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    99,    99,   100,   100,   101,   100,   102,   102,   102,
     102,   102,   102,   102,   103,   103,   103,   103,   103,   103,
     103,   103,   104,   104,   105,   105,   105,   105,   106,   106,
     107,   107,   108,   109,   109,   110,   110,   111,   110,   110,
     110,   110,   110,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     113,   113,   114,   114,   115,   115,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   123,   123,
     124,   125,   125,   126,   126,   127
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     8,     7,     9,     8,     4,
       2,     6,     4,     4,     4,     4,     4,     4,     2,     2,
       4,     1,     3,     0,     2,     0,     6,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     4,     4,     3,     1,     3,
       1,     3,     1,     1,     3,     1,     1,     0,     4,     3,
       3,     5,     9,     0,     2,     2,     2,     4,     1,     2,
       2,     2,     2,     2,     3,     6,     3,     3,     8,     2,
       3,     2,     1,     2,     1,     2,     1,     1,     4,     5,
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
#line 86 "syn.y"
                                    {Node * temp;
														if ((yyvsp[-1].y_nod)) { temp = mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod));
															is_running();
															CALLFUNCT(temp);
															is_not_running();
															delete(temp);}
														}
#line 1516 "syn.tab.c"
    break;

  case 5: /* definition: FUNC namedId ':' vsortlist PFEIL Sort VORRANG att  */
#line 94 "syn.y"
                                                                    {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1524 "syn.tab.c"
    break;

  case 6: /* definition: OTHER func ':' vsortlist PFEIL Sort att  */
#line 97 "syn.y"
                                                                  { (yyval.y_nod)=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1533 "syn.tab.c"
    break;

  case 7: /* definition: ATT Sort Id ',' Id ',' Id ',' Id  */
#line 101 "syn.y"
                                                           { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufkt(name((yyvsp[0].y_sym))))))));	}
#line 1544 "syn.tab.c"
    break;

  case 8: /* definition: BRA Id Id ':' vsortlist PFEIL Sort att  */
#line 107 "syn.y"
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
#line 1560 "syn.tab.c"
    break;

  case 9: /* definition: VAR idlist ':' Sort  */
#line 118 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1566 "syn.tab.c"
    break;

  case 10: /* definition: NUM Sort  */
#line 119 "syn.y"
                                                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* setzt numbertype fuer mknum */}
#line 1572 "syn.tab.c"
    break;

  case 11: /* definition: SUBSORT Sort ',' Sort ATT Id  */
#line 120 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: Untersorte */
										      mknod(PARAM,(Node *) (yyvsp[-4].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufkt(name((yyvsp[0].y_sym))))));}
#line 1579 "syn.tab.c"
    break;

  case 12: /* definition: INTNUM Sort ATT Id  */
#line 122 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) intnum_def,    /* 2026: Sorte ganzer Zahlen */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufkt(name((yyvsp[0].y_sym)))));}
#line 1586 "syn.tab.c"
    break;

  case 13: /* definition: NUM idlist ':' Sort  */
#line 124 "syn.y"
                                                                 { /* Variablen fuer Numerische Zahlen */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1593 "syn.tab.c"
    break;

  case 14: /* definition: CST idlist ':' Sort  */
#line 126 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1599 "syn.tab.c"
    break;

  case 15: /* definition: SPEC Alg ':' alglist  */
#line 127 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1605 "syn.tab.c"
    break;

  case 16: /* definition: SPEC Alg ':' formlist  */
#line 128 "syn.y"
                                                         {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1611 "syn.tab.c"
    break;

  case 17: /* definition: ADDSPEC Alg ':' formlist  */
#line 129 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1617 "syn.tab.c"
    break;

  case 18: /* definition: SORT idlist  */
#line 130 "syn.y"
                                                                             {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1623 "syn.tab.c"
    break;

  case 19: /* definition: ALG idlist  */
#line 132 "syn.y"
                                                     {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1629 "syn.tab.c"
    break;

  case 20: /* definition: TERM idlist ':' Sort  */
#line 133 "syn.y"
                                                   {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1635 "syn.tab.c"
    break;

  case 21: /* idlist: namedId  */
#line 135 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1641 "syn.tab.c"
    break;

  case 22: /* idlist: namedId ',' idlist  */
#line 136 "syn.y"
                                                        {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1647 "syn.tab.c"
    break;

  case 23: /* att: %empty  */
#line 144 "syn.y"
                                        { (yyval.y_nod) = NULL;}
#line 1653 "syn.tab.c"
    break;

  case 24: /* att: ATT namedId  */
#line 145 "syn.y"
                                                { /* numerische C-Funktion (userfkt.c), sonst symbolische (symfkt.c) */
			                  u_function * u = give_ufkt_quiet(name((Symbol *) (yyvsp[0].y_nod)));
			                  s_function * s = u ? NULL : give_sfkt(name((Symbol *) (yyvsp[0].y_nod)));
			                  if (u)
			                    (yyval.y_nod) = mknod(ATT,(Node *) u,NULL);
			                  else if (s)
			                    (yyval.y_nod) = mknod(ATT,(Node *) s,mknod(PARAM,NULL,NULL)); /* r: symbolisch */
			                  else
			                    { printfErr(" --ERROR ATT : C-Function %s not Implemented \n",name((Symbol *) (yyvsp[0].y_nod)));
			                      (yyval.y_nod) = mknod(ATT,NULL,NULL); }
			                }
#line 1669 "syn.tab.c"
    break;

  case 25: /* $@1: %empty  */
#line 156 "syn.y"
                                          {block_begin();no_protect();}
#line 1675 "syn.tab.c"
    break;

  case 26: /* att: ATT '(' $@1 d_list ')' instruction  */
#line 157 "syn.y"
                                                                                        {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1681 "syn.tab.c"
    break;

  case 27: /* namedId: Id  */
#line 159 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1687 "syn.tab.c"
    break;

  case 28: /* namedId: Const  */
#line 160 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1693 "syn.tab.c"
    break;

  case 29: /* namedId: Var  */
#line 161 "syn.y"
                         { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1699 "syn.tab.c"
    break;

  case 30: /* namedId: func  */
#line 162 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1705 "syn.tab.c"
    break;

  case 31: /* namedId: Sort  */
#line 163 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1711 "syn.tab.c"
    break;

  case 32: /* namedId: Alg  */
#line 164 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1717 "syn.tab.c"
    break;

  case 33: /* namedId: Term  */
#line 165 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1723 "syn.tab.c"
    break;

  case 34: /* VORRANG: %empty  */
#line 168 "syn.y"
                                                        {(yyval.y_int) = Func;}
#line 1729 "syn.tab.c"
    break;

  case 35: /* VORRANG: LA1  */
#line 169 "syn.y"
                                                                        {(yyval.y_int) = La1;	/* Linksassoziativ */}
#line 1735 "syn.tab.c"
    break;

  case 36: /* VORRANG: LA2  */
#line 170 "syn.y"
                                                                        {(yyval.y_int) = La2;	/* Linksassoziativ */}
#line 1741 "syn.tab.c"
    break;

  case 37: /* VORRANG: LA3  */
#line 171 "syn.y"
                                                                        {(yyval.y_int) = La3;	/* Linksassoziativ */}
#line 1747 "syn.tab.c"
    break;

  case 38: /* VORRANG: LA4  */
#line 172 "syn.y"
                                                                        {(yyval.y_int) = La4;	/* Linksassoziativ */}
#line 1753 "syn.tab.c"
    break;

  case 39: /* VORRANG: LA5  */
#line 173 "syn.y"
                                                                        {(yyval.y_int) = La5;	/* Linksassoziativ */}
#line 1759 "syn.tab.c"
    break;

  case 40: /* VORRANG: RA  */
#line 174 "syn.y"
                                                                        {(yyval.y_int) = Ra;  	/* Rechtsassoziativ */}
#line 1765 "syn.tab.c"
    break;

  case 41: /* VORRANG: RU  */
#line 175 "syn.y"
                                                                        {(yyval.y_int) = Ru;	  /* Rechts Unaer */}
#line 1771 "syn.tab.c"
    break;

  case 42: /* condition: condfunc  */
#line 177 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1777 "syn.tab.c"
    break;

  case 43: /* condition: condfunc ',' condition  */
#line 178 "syn.y"
                                                        {(yyval.y_nod) = mknod(Cond,(Node *) and_cond,mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod)));}
#line 1783 "syn.tab.c"
    break;

  case 44: /* condfunc: LB '(' termlist ')'  */
#line 180 "syn.y"
                              {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1789 "syn.tab.c"
    break;

  case 45: /* condfunc: IN '(' termlist ')'  */
#line 181 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1795 "syn.tab.c"
    break;

  case 46: /* condfunc: NIN '(' termlist ')'  */
#line 182 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1801 "syn.tab.c"
    break;

  case 47: /* condfunc: '(' term ')'  */
#line 183 "syn.y"
                                                                        {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1807 "syn.tab.c"
    break;

  case 48: /* instructions: instruction  */
#line 185 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1813 "syn.tab.c"
    break;

  case 49: /* instructions: instruction ';' instructions  */
#line 186 "syn.y"
                                                                                       {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1819 "syn.tab.c"
    break;

  case 50: /* tinstructions: oinstructions  */
#line 188 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1825 "syn.tab.c"
    break;

  case 51: /* tinstructions: oinstructions '\n' tinstructions  */
#line 189 "syn.y"
                                                                                                                {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1831 "syn.tab.c"
    break;

  case 52: /* oinstructions: instructions  */
#line 191 "syn.y"
                                                {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1837 "syn.tab.c"
    break;

  case 53: /* d_list: definition  */
#line 196 "syn.y"
                                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1843 "syn.tab.c"
    break;

  case 54: /* d_list: definition ';' d_list  */
#line 197 "syn.y"
                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1849 "syn.tab.c"
    break;

  case 55: /* instruction: aninstruction  */
#line 199 "syn.y"
                                {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Locale Variablen pruefen ! */ }
#line 1855 "syn.tab.c"
    break;

  case 56: /* instruction: definition  */
#line 200 "syn.y"
                                                                        {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1861 "syn.tab.c"
    break;

  case 57: /* $@2: %empty  */
#line 201 "syn.y"
                                                                                                        {block_begin();no_protect();}
#line 1867 "syn.tab.c"
    break;

  case 58: /* instruction: '{' $@2 tinstructions '}'  */
#line 202 "syn.y"
                                                                        {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 1877 "syn.tab.c"
    break;

  case 59: /* instruction: WHILE condition instruction  */
#line 207 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* wird dann $3 */)));
																		WHILE_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1884 "syn.tab.c"
    break;

  case 60: /* instruction: IF condition instruction  */
#line 210 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		IF_THEN(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1891 "syn.tab.c"
    break;

  case 61: /* instruction: IF condition instruction ELSE instruction  */
#line 212 "syn.y"
                                                                        {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(merk) = (yyvsp[-2].y_nod);IF_ELSE(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1898 "syn.tab.c"
    break;

  case 62: /* instruction: FOR term EQ term TO term step DO instruction  */
#line 215 "syn.y"
                                                                                                                {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) forschleife,
																mknod(PARAM,
																	mknod(PARAM,(yyvsp[-5].y_nod),(yyvsp[-3].y_nod)),
																	mknod(PARAM,
																		mknod(PARAM,(yyvsp[-2].y_nod),(Node *) ((yyvsp[-7].y_nod))),
																		NULL /* $9 */) )));	
														FOR_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1910 "syn.tab.c"
    break;

  case 63: /* aninstruction: %empty  */
#line 224 "syn.y"
                                {(yyval.y_nod)=NULL;}
#line 1916 "syn.tab.c"
    break;

  case 64: /* aninstruction: SYS String  */
#line 225 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) system_fkt,(Node *) ((yyvsp[0].y_sym)));}
#line 1922 "syn.tab.c"
    break;

  case 65: /* aninstruction: INC String  */
#line 226 "syn.y"
                                                                        {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fkt,(Node *) ((yyvsp[0].y_sym))); }
#line 1928 "syn.tab.c"
    break;

  case 66: /* aninstruction: INFO namedId  */
#line 227 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) info_fkt,(Node *) ((yyvsp[0].y_nod))); }
#line 1934 "syn.tab.c"
    break;

  case 67: /* aninstruction: REWR term ':' alglist  */
#line 228 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 1941 "syn.tab.c"
    break;

  case 68: /* aninstruction: prntlist  */
#line 230 "syn.y"
                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 1947 "syn.tab.c"
    break;

  case 69: /* aninstruction: PRTNUM String  */
#line 231 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 1953 "syn.tab.c"
    break;

  case 70: /* aninstruction: PRT prntlist  */
#line 232 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* ohne \n */ }
#line 1959 "syn.tab.c"
    break;

  case 71: /* aninstruction: OUT String  */
#line 233 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 1965 "syn.tab.c"
    break;

  case 72: /* aninstruction: DATA String  */
#line 234 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 1971 "syn.tab.c"
    break;

  case 73: /* aninstruction: DATA Const  */
#line 235 "syn.y"
                                                                        {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 1982 "syn.tab.c"
    break;

  case 74: /* aninstruction: Term EQ term  */
#line 241 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 1988 "syn.tab.c"
    break;

  case 75: /* aninstruction: Term EQ REWR term ':' alglist  */
#line 242 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 1994 "syn.tab.c"
    break;

  case 76: /* aninstruction: Const EQ term  */
#line 243 "syn.y"
                                                        { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 2000 "syn.tab.c"
    break;

  case 77: /* aninstruction: EXE func Id  */
#line 244 "syn.y"
                                                        {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufkt(name((yyvsp[0].y_sym)));
 													}
#line 2010 "syn.tab.c"
    break;

  case 78: /* aninstruction: LIFT '(' termlist ')' TO '(' termlist ')'  */
#line 249 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 2016 "syn.tab.c"
    break;

  case 79: /* aninstruction: DBG Const  */
#line 250 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 2022 "syn.tab.c"
    break;

  case 80: /* aninstruction: STEPS Alg String  */
#line 251 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) steps_fkt,mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2028 "syn.tab.c"
    break;

  case 81: /* aninstruction: RETURN term  */
#line 252 "syn.y"
                                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) return_fkt,(yyvsp[0].y_nod));}
#line 2034 "syn.tab.c"
    break;

  case 82: /* aninstruction: QUIT  */
#line 253 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fkt,NULL);}
#line 2040 "syn.tab.c"
    break;

  case 83: /* aninstruction: OPT idlist  */
#line 254 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,(yyvsp[0].y_nod));}
#line 2046 "syn.tab.c"
    break;

  case 84: /* aninstruction: OPT  */
#line 255 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,NULL);   /* loeschen */}
#line 2052 "syn.tab.c"
    break;

  case 85: /* aninstruction: COMM funclist  */
#line 256 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,(yyvsp[0].y_nod));}
#line 2058 "syn.tab.c"
    break;

  case 86: /* aninstruction: COMM  */
#line 257 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,NULL);  /* loeschen */}
#line 2064 "syn.tab.c"
    break;

  case 87: /* aninstruction: DEFAULT  */
#line 258 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,NULL); /* loeschen */}
#line 2070 "syn.tab.c"
    break;

  case 88: /* aninstruction: DEFAULT func EQ term  */
#line 259 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),NULL),(yyvsp[0].y_nod)));}
#line 2077 "syn.tab.c"
    break;

  case 89: /* aninstruction: DEFAULT RIGHT func EQ term  */
#line 261 "syn.y"
                                                     {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),mknod(PARAM,NULL,NULL)),(yyvsp[0].y_nod)));}
#line 2084 "syn.tab.c"
    break;

  case 90: /* step: %empty  */
#line 264 "syn.y"
                        {(yyval.y_nod)=(Node *) NULL;}
#line 2090 "syn.tab.c"
    break;

  case 91: /* step: STEP term  */
#line 265 "syn.y"
                                        {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2096 "syn.tab.c"
    break;

  case 92: /* prntexpr: term  */
#line 267 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2102 "syn.tab.c"
    break;

  case 93: /* prntexpr: String  */
#line 268 "syn.y"
                                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2108 "syn.tab.c"
    break;

  case 94: /* prntlist: prntexpr  */
#line 270 "syn.y"
                                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2114 "syn.tab.c"
    break;

  case 95: /* prntlist: prntexpr ',' prntlist  */
#line 271 "syn.y"
                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2120 "syn.tab.c"
    break;

  case 96: /* alglist: Alg2  */
#line 273 "syn.y"
                                                                {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2126 "syn.tab.c"
    break;

  case 97: /* alglist: Alg2 ',' alglist  */
#line 274 "syn.y"
                                                        {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2132 "syn.tab.c"
    break;

  case 98: /* Alg2: Alg  */
#line 276 "syn.y"
                                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2138 "syn.tab.c"
    break;

  case 99: /* Alg2: '(' alglist ')'  */
#line 277 "syn.y"
                                                                {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2144 "syn.tab.c"
    break;

  case 100: /* sortlist: Sort  */
#line 279 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2150 "syn.tab.c"
    break;

  case 101: /* sortlist: Sort ',' sortlist  */
#line 280 "syn.y"
                                                                {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2156 "syn.tab.c"
    break;

  case 102: /* vsortlist: sortlist  */
#line 282 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2162 "syn.tab.c"
    break;

  case 103: /* vsortlist: sortlist VARPAR  */
#line 283 "syn.y"
                                                                        {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2168 "syn.tab.c"
    break;

  case 104: /* func: Func  */
#line 285 "syn.y"
                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2174 "syn.tab.c"
    break;

  case 105: /* func: La1  */
#line 286 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2180 "syn.tab.c"
    break;

  case 106: /* func: La2  */
#line 287 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2186 "syn.tab.c"
    break;

  case 107: /* func: La3  */
#line 288 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2192 "syn.tab.c"
    break;

  case 108: /* func: La4  */
#line 289 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2198 "syn.tab.c"
    break;

  case 109: /* func: La5  */
#line 290 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2204 "syn.tab.c"
    break;

  case 110: /* func: Ra  */
#line 291 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2210 "syn.tab.c"
    break;

  case 111: /* func: Ru  */
#line 292 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2216 "syn.tab.c"
    break;

  case 112: /* func: Bra  */
#line 293 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2222 "syn.tab.c"
    break;

  case 113: /* func: Bra1  */
#line 294 "syn.y"
                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2228 "syn.tab.c"
    break;

  case 114: /* funclist: func  */
#line 296 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2234 "syn.tab.c"
    break;

  case 115: /* funclist: func ',' funclist  */
#line 297 "syn.y"
                                                        {(yyval.y_nod) = mknod(Functs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2240 "syn.tab.c"
    break;

  case 116: /* term: Term  */
#line 299 "syn.y"
                                                                        {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); merkt sich keine Abhaengigkeiten und funktioniert nicht in Bloecken */ 
														}
#line 2247 "syn.tab.c"
    break;

  case 117: /* term: LAST  */
#line 301 "syn.y"
                                                                                        {(yyval.y_nod) = (Node *) lastterm;}
#line 2253 "syn.tab.c"
    break;

  case 118: /* term: Const  */
#line 302 "syn.y"
                                                                                        {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2259 "syn.tab.c"
    break;

  case 119: /* term: Const Bra1 termlist Bra2  */
#line 303 "syn.y"
                                                   {nphilf=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),nphilf), nphilf);}
#line 2266 "syn.tab.c"
    break;

  case 120: /* term: Var  */
#line 305 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2272 "syn.tab.c"
    break;

  case 121: /* term: '(' term ')'  */
#line 306 "syn.y"
                                                    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2278 "syn.tab.c"
    break;

  case 122: /* term: term Ru  */
#line 307 "syn.y"
                                                                      {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2284 "syn.tab.c"
    break;

  case 123: /* term: Func term  */
#line 308 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2290 "syn.tab.c"
    break;

  case 124: /* term: La1 term  */
#line 309 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2296 "syn.tab.c"
    break;

  case 125: /* term: La2 term  */
#line 310 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2302 "syn.tab.c"
    break;

  case 126: /* term: La3 term  */
#line 311 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2308 "syn.tab.c"
    break;

  case 127: /* term: La4 term  */
#line 312 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2314 "syn.tab.c"
    break;

  case 128: /* term: La5 term  */
#line 313 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2320 "syn.tab.c"
    break;

  case 129: /* term: Bra termlist Bra  */
#line 314 "syn.y"
                                                  {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2326 "syn.tab.c"
    break;

  case 130: /* term: Bra1 termlist Bra2  */
#line 315 "syn.y"
                                                {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2332 "syn.tab.c"
    break;

  case 131: /* term: Func '(' termlist ')'  */
#line 316 "syn.y"
                                                        {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2338 "syn.tab.c"
    break;

  case 132: /* term: term La1 term  */
#line 317 "syn.y"
                                                    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2345 "syn.tab.c"
    break;

  case 133: /* term: term La2 term  */
#line 319 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2352 "syn.tab.c"
    break;

  case 134: /* term: term La3 term  */
#line 321 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2359 "syn.tab.c"
    break;

  case 135: /* term: term La4 term  */
#line 323 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2366 "syn.tab.c"
    break;

  case 136: /* term: term La5 term  */
#line 325 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2373 "syn.tab.c"
    break;

  case 137: /* term: term Ra term  */
#line 327 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2380 "syn.tab.c"
    break;

  case 138: /* termlist: term  */
#line 330 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2386 "syn.tab.c"
    break;

  case 139: /* termlist: term ',' termlist  */
#line 331 "syn.y"
                                                        {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2392 "syn.tab.c"
    break;

  case 140: /* formula: term EQ term  */
#line 333 "syn.y"
                                        {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2398 "syn.tab.c"
    break;

  case 141: /* vinstr: %empty  */
#line 335 "syn.y"
                                                                {(yyval.y_nod) = NULL;}
#line 2404 "syn.tab.c"
    break;

  case 142: /* vinstr: DO instruction  */
#line 336 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2410 "syn.tab.c"
    break;

  case 143: /* cformula: formula vinstr  */
#line 338 "syn.y"
                                                                        {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2417 "syn.tab.c"
    break;

  case 144: /* cformula: IF condition formula vinstr  */
#line 340 "syn.y"
                                               {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2424 "syn.tab.c"
    break;

  case 145: /* formlist: cformula  */
#line 343 "syn.y"
                                                                {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL dient zum Einhaengen weiterer Formeln !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. wegen SPEC real : A+B=C;a=3 */
															}
#line 2432 "syn.tab.c"
    break;


#line 2436 "syn.tab.c"

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

#line 347 "syn.y"

