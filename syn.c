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
  YYSYMBOL_Id = 60,                        /* Id  */
  YYSYMBOL_String = 61,                    /* String  */
  YYSYMBOL_Sort = 62,                      /* Sort  */
  YYSYMBOL_Alg = 63,                       /* Alg  */
  YYSYMBOL_Term = 64,                      /* Term  */
  YYSYMBOL_La1 = 65,                       /* La1  */
  YYSYMBOL_La2 = 66,                       /* La2  */
  YYSYMBOL_La3 = 67,                       /* La3  */
  YYSYMBOL_La4 = 68,                       /* La4  */
  YYSYMBOL_La5 = 69,                       /* La5  */
  YYSYMBOL_Ru = 70,                        /* Ru  */
  YYSYMBOL_Ra = 71,                        /* Ra  */
  YYSYMBOL_Func = 72,                      /* Func  */
  YYSYMBOL_Const = 73,                     /* Const  */
  YYSYMBOL_Var = 74,                       /* Var  */
  YYSYMBOL_Bra = 75,                       /* Bra  */
  YYSYMBOL_Bra1 = 76,                      /* Bra1  */
  YYSYMBOL_Bra2 = 77,                      /* Bra2  */
  YYSYMBOL_Terms = 78,                     /* Terms  */
  YYSYMBOL_Form = 79,                      /* Form  */
  YYSYMBOL_Sorts = 80,                     /* Sorts  */
  YYSYMBOL_Functs = 81,                    /* Functs  */
  YYSYMBOL_Forms = 82,                     /* Forms  */
  YYSYMBOL_Algs = 83,                      /* Algs  */
  YYSYMBOL_Cond2 = 84,                     /* Cond2  */
  YYSYMBOL_Cond = 85,                      /* Cond  */
  YYSYMBOL_86_n_ = 86,                     /* '\n'  */
  YYSYMBOL_87_ = 87,                       /* ':'  */
  YYSYMBOL_88_ = 88,                       /* ','  */
  YYSYMBOL_89_ = 89,                       /* '('  */
  YYSYMBOL_90_ = 90,                       /* ')'  */
  YYSYMBOL_91_ = 91,                       /* ';'  */
  YYSYMBOL_92_ = 92,                       /* '{'  */
  YYSYMBOL_93_ = 93,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 94,                  /* $accept  */
  YYSYMBOL_prog = 95,                      /* prog  */
  YYSYMBOL_line = 96,                      /* line  */
  YYSYMBOL_definition = 97,                /* definition  */
  YYSYMBOL_idlist = 98,                    /* idlist  */
  YYSYMBOL_att = 99,                       /* att  */
  YYSYMBOL_100_1 = 100,                    /* $@1  */
  YYSYMBOL_namedId = 101,                  /* namedId  */
  YYSYMBOL_VORRANG = 102,                  /* VORRANG  */
  YYSYMBOL_condition = 103,                /* condition  */
  YYSYMBOL_condfunc = 104,                 /* condfunc  */
  YYSYMBOL_instructions = 105,             /* instructions  */
  YYSYMBOL_tinstructions = 106,            /* tinstructions  */
  YYSYMBOL_oinstructions = 107,            /* oinstructions  */
  YYSYMBOL_d_list = 108,                   /* d_list  */
  YYSYMBOL_instruction = 109,              /* instruction  */
  YYSYMBOL_110_2 = 110,                    /* $@2  */
  YYSYMBOL_aninstruction = 111,            /* aninstruction  */
  YYSYMBOL_step = 112,                     /* step  */
  YYSYMBOL_prntexpr = 113,                 /* prntexpr  */
  YYSYMBOL_prntlist = 114,                 /* prntlist  */
  YYSYMBOL_alglist = 115,                  /* alglist  */
  YYSYMBOL_Alg2 = 116,                     /* Alg2  */
  YYSYMBOL_sortlist = 117,                 /* sortlist  */
  YYSYMBOL_vsortlist = 118,                /* vsortlist  */
  YYSYMBOL_func = 119,                     /* func  */
  YYSYMBOL_funclist = 120,                 /* funclist  */
  YYSYMBOL_term = 121,                     /* term  */
  YYSYMBOL_termlist = 122,                 /* termlist  */
  YYSYMBOL_formula = 123,                  /* formula  */
  YYSYMBOL_vinstr = 124,                   /* vinstr  */
  YYSYMBOL_cformula = 125,                 /* cformula  */
  YYSYMBOL_formlist = 126                  /* formlist  */
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
#define YYFINAL  134
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   649

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  305

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   340


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
      86,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      89,    90,     2,     2,    88,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    87,    91,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,    93,     2,     2,     2,     2,
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
      85
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
     251,   252,   253,   254,   255,   256,   257,   258,   260,   263,
     264,   266,   267,   269,   270,   272,   273,   275,   276,   278,
     279,   281,   282,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   295,   296,   298,   300,   301,   302,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   318,   320,   322,   324,   326,   329,   330,   332,
     334,   335,   337,   339,   342
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
  "RETURN", "OPT", "COMM", "DEFAULT", "RIGHT", "SUBSORT", "INTNUM", "Id",
  "String", "Sort", "Alg", "Term", "La1", "La2", "La3", "La4", "La5", "Ru",
  "Ra", "Func", "Const", "Var", "Bra", "Bra1", "Bra2", "Terms", "Form",
  "Sorts", "Functs", "Forms", "Algs", "Cond2", "Cond", "'\\n'", "':'",
  "','", "'('", "')'", "';'", "'{'", "'}'", "$accept", "prog", "line",
  "definition", "idlist", "att", "$@1", "namedId", "VORRANG", "condition",
  "condfunc", "instructions", "tinstructions", "oinstructions", "d_list",
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

#define YYPACT_NINF (-208)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-32)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     335,   537,   537,   537,   537,   537,   -44,   -26,   449,   291,
     537,   554,   -18,   537,   449,   -27,  -208,    13,   566,   -25,
      22,    31,   566,    32,    12,    12,    35,     8,  -208,   449,
     537,   566,   520,    37,    38,  -208,    84,   449,   449,   449,
     449,   449,   467,    -6,  -208,   449,   449,   449,  -208,   245,
    -208,  -208,    20,    17,  -208,    21,  -208,   578,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,    24,    29,  -208,    39,  -208,    40,
    -208,    42,    43,  -208,    49,   382,  -208,    44,   -59,    50,
      79,  -208,     9,  -208,    86,    60,  -208,  -208,  -208,  -208,
      88,  -208,    61,    62,    63,   449,   335,    69,   335,  -208,
     449,   578,  -208,    70,  -208,   566,   141,    76,   149,   118,
     391,   440,   -12,    45,    11,   449,  -208,   449,   449,   350,
      92,    91,    -2,   335,  -208,  -208,  -208,   335,   291,   449,
     449,   449,   449,   449,  -208,   449,   108,   537,   109,   111,
     367,   399,   -42,   112,   113,    90,   449,    89,   111,  -208,
     449,   449,   449,   257,   131,    12,  -208,    99,   566,   162,
     449,   119,   136,   449,   578,   156,   107,   578,   121,   449,
    -208,  -208,  -208,  -208,   122,   130,  -208,  -208,   391,   440,
     -12,    45,    11,    11,  -208,  -208,  -208,   129,   173,   207,
      12,  -208,   417,  -208,   140,   143,   193,  -208,  -208,  -208,
     -42,  -208,  -208,  -208,   170,   135,   111,   220,   144,   147,
     148,  -208,   335,  -208,   206,  -208,   449,   578,   225,  -208,
     432,  -208,  -208,  -208,  -208,   335,   111,  -208,   180,   449,
     153,   -42,   449,   335,  -208,   159,   449,   244,   196,  -208,
    -208,  -208,  -208,   174,   578,   205,   -42,  -208,  -208,   524,
     193,  -208,  -208,   578,  -208,   213,   201,   212,   260,   449,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,   260,
    -208,   189,   449,   243,   260,   495,  -208,   190,  -208,   230,
     578,   335,  -208,  -208,  -208,  -208,  -208,  -208,    46,   202,
     215,    46,   335,  -208,  -208
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    81,     0,
      83,    85,    86,     0,     0,    92,   115,     0,     0,     0,
       0,     0,     0,   117,   119,     0,     0,     0,    57,    63,
       2,    56,     0,    48,    55,    93,    68,    91,    27,    31,
      32,    33,   104,   105,   106,   107,   108,   110,   109,   103,
      28,    29,   111,   112,     0,    21,    30,     0,    18,     0,
      19,     0,     0,   115,   117,     0,    70,     0,    10,     0,
       0,    66,     0,    79,     0,     0,    72,    73,    71,    65,
       0,    64,     0,     0,     0,     0,    63,    42,    63,    69,
       0,    80,    82,   113,    84,     0,     0,     0,     0,     0,
     123,   124,   125,   126,   127,     0,   122,     0,     0,   137,
       0,     0,     0,    63,     1,     3,     4,    63,     0,     0,
       0,     0,     0,     0,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
       0,     0,     0,     0,    60,     0,    59,     0,     0,     0,
       0,     0,     0,     0,    74,     0,     0,    76,     0,     0,
     128,   129,   120,    52,     0,    50,    49,    94,   131,   132,
     133,   134,   135,   136,    14,    22,     9,    99,   101,     0,
       0,    97,     0,    15,    95,     0,   140,   144,    16,    17,
       0,    67,    20,    13,     0,     0,     0,     0,     0,     0,
       0,    47,    63,    43,     0,   114,     0,    87,     0,    12,
       0,   130,   118,   138,    58,    63,     0,   102,     0,     0,
       0,     0,     0,    63,   142,     0,     0,     0,     0,    44,
      45,    46,    61,     0,    88,     0,     0,    51,   100,    34,
     140,    98,    96,   139,   141,     0,    89,     0,    23,     0,
      11,    75,    35,    36,    37,    38,    39,    41,    40,    23,
     143,     0,     0,     0,    23,     0,     6,     0,     5,     0,
      90,    63,     8,    25,    24,    78,     7,    62,     0,    53,
       0,     0,    63,    54,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -208,  -208,   253,  -207,    15,  -195,  -208,    -4,  -208,   -23,
    -208,  -122,    72,  -208,    14,  -103,  -208,  -208,  -208,  -208,
       7,  -146,  -208,    80,  -145,    -8,   163,    -7,   -38,    93,
      48,  -208,   179
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    49,    50,    51,    74,   286,   298,    75,   279,   106,
     107,    52,   184,   185,   300,    53,   133,    54,   283,    55,
      56,   240,   204,   198,   199,    76,   114,    57,   130,   206,
     244,   207,   208
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    85,   108,   164,   203,   166,   211,    92,   131,    91,
      95,   183,   127,   217,   100,   186,    86,    77,    78,    81,
      80,   201,   111,   113,   116,    87,    89,   156,   -31,   -31,
     120,   121,   122,   123,   124,   126,    96,    82,   129,   129,
     132,   102,   103,   104,    90,   112,    93,   210,    97,     1,
       2,     3,     4,     5,     6,     7,   142,   143,   144,   145,
      10,    11,    12,   139,   140,   141,   142,   143,   144,   145,
     128,   247,   167,    94,   139,   140,   141,   142,   143,   144,
     145,   144,   145,    98,   288,    17,    18,   176,   182,   292,
     178,   299,    99,   101,   299,   262,   109,   110,   163,   117,
     118,   105,   119,   129,    33,    34,   136,   169,   137,   138,
     271,   146,   174,   183,   143,   144,   145,   147,   175,   252,
     177,   129,   218,   219,   220,   128,   148,   149,   173,   150,
     151,   153,   188,   189,   190,   191,   192,   154,   193,   155,
     264,   233,   223,   205,   205,   187,   157,   158,   159,   215,
     160,   161,   162,   129,   129,   129,    16,   165,   168,   170,
     113,   242,   195,   227,   171,   172,   230,   180,   181,   246,
     194,   196,   129,   197,   212,   213,   216,   239,   214,   222,
     226,   228,    83,    37,    38,    39,    40,    41,   297,   224,
      42,    84,    44,    45,    46,   132,   229,   231,   232,   304,
     139,   140,   141,   142,   143,   144,   145,    47,   139,   140,
     141,   142,   143,   144,   145,   234,   235,   236,   237,   254,
     238,   139,   140,   141,   142,   143,   144,   145,   241,   243,
     245,   287,   205,   248,   249,   263,   282,   250,   251,   266,
     253,   255,   259,   261,   179,   134,   182,   265,     1,     2,
       3,     4,     5,     6,     7,     8,     9,   267,   268,    10,
      11,    12,   129,   269,    13,   270,   139,   140,   141,   142,
     143,   144,   145,   281,   284,   290,   285,   289,    14,   291,
     295,   294,    15,    16,    17,    18,    19,    20,    21,    22,
     296,    23,    24,   301,    25,    26,    27,    28,    29,    30,
      31,    32,   135,    33,    34,   302,    35,   257,   280,    36,
      37,    38,    39,    40,    41,   303,   258,    42,    43,    44,
      45,    46,   139,   140,   141,   142,   143,   144,   145,    16,
     209,   225,   260,     0,    47,     0,     0,    48,     1,     2,
       3,     4,     5,     6,     7,     8,     9,   221,     0,    10,
      11,    12,    35,     0,    13,    83,    37,    38,    39,    40,
      41,     0,     0,    42,    84,    44,    45,    46,    14,     0,
       0,     0,    15,    16,    17,    18,    19,    20,    21,    22,
      47,    23,    24,     0,    25,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,     0,    35,     0,     0,    36,
      37,    38,    39,    40,    41,    16,     0,    42,    43,    44,
      45,    46,     0,     0,   200,   139,   140,   141,   142,   143,
     144,   145,     0,     0,    47,     0,     0,    48,     0,     0,
     201,    83,    37,    38,    39,    40,    41,    16,   179,    42,
      84,    44,    45,    46,     0,     0,   200,   139,   140,   141,
     142,   143,   144,   145,     0,    16,   202,   140,   141,   142,
     143,   144,   145,    83,    37,    38,    39,    40,    41,   152,
       0,    42,    84,    44,    45,    46,     0,     0,     0,     0,
     201,    83,    37,    38,    39,    40,    41,    16,    47,    42,
      84,    44,    45,    46,     0,     0,     0,   139,   140,   141,
     142,   143,   144,   145,     0,    16,   202,   141,   142,   143,
     144,   145,     0,    83,    37,    38,    39,    40,    41,   256,
       0,    42,    84,    44,    45,    46,     0,     0,     0,     0,
       0,    83,    37,    38,    39,    40,    41,     0,    47,    42,
      84,    44,    45,    46,   272,   273,   274,   275,   276,     0,
     277,   278,     0,     0,     0,    58,   125,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     0,     0,     0,     0,     0,   115,     0,     0,
       0,     0,     0,     0,   293,    62,    63,    64,    65,    66,
      67,    68,    69,     0,     0,    72,    73,    58,     0,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    58,     0,    88,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    62,    63,    64,    65,    66,    67,    68,    69,     0,
       0,    72,    73,   139,   140,   141,   142,   143,   144,   145
};

static const yytype_int16 yycheck[] =
{
       4,     8,    25,   106,   150,   108,   152,    14,    46,    13,
      18,   133,    18,   158,    22,   137,     9,     2,     3,    63,
       5,    63,    29,    31,    32,    10,    11,    18,    87,    88,
      37,    38,    39,    40,    41,    42,    61,    63,    45,    46,
      47,    29,    30,    31,    62,    30,    73,    89,    73,     3,
       4,     5,     6,     7,     8,     9,    68,    69,    70,    71,
      14,    15,    16,    65,    66,    67,    68,    69,    70,    71,
      76,   216,   110,    60,    65,    66,    67,    68,    69,    70,
      71,    70,    71,    61,   279,    39,    40,   125,    90,   284,
     128,   298,    61,    61,   301,   241,    61,    89,   105,    62,
      62,    89,    18,   110,    58,    59,    86,   115,    91,    88,
     256,    87,   119,   235,    69,    70,    71,    88,   125,   222,
     127,   128,   160,   161,   162,    76,    87,    87,    10,    87,
      87,    87,   139,   140,   141,   142,   143,    87,   145,    60,
     243,   179,   165,   150,   151,   138,    60,    87,    60,   156,
      89,    89,    89,   160,   161,   162,    38,    88,    88,    18,
     168,    18,   147,   170,    88,    16,   173,    75,    77,    34,
      62,    62,   179,    62,    62,    62,    87,   200,    88,    48,
      18,    62,    64,    65,    66,    67,    68,    69,   291,    90,
      72,    73,    74,    75,    76,   202,    60,    90,    77,   302,
      65,    66,    67,    68,    69,    70,    71,    89,    65,    66,
      67,    68,    69,    70,    71,    93,    86,    88,    45,   226,
      13,    65,    66,    67,    68,    69,    70,    71,    88,    36,
      60,   269,   239,    13,    90,   242,    35,    90,    90,   246,
      34,    16,    62,    90,    88,     0,    90,    88,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    13,    62,    14,
      15,    16,   269,    89,    19,    60,    65,    66,    67,    68,
      69,    70,    71,    60,    62,   282,    16,    88,    33,    36,
      90,   285,    37,    38,    39,    40,    41,    42,    43,    44,
      60,    46,    47,    91,    49,    50,    51,    52,    53,    54,
      55,    56,    49,    58,    59,    90,    61,   235,   260,    64,
      65,    66,    67,    68,    69,   301,   236,    72,    73,    74,
      75,    76,    65,    66,    67,    68,    69,    70,    71,    38,
     151,   168,   239,    -1,    89,    -1,    -1,    92,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    90,    -1,    14,
      15,    16,    61,    -1,    19,    64,    65,    66,    67,    68,
      69,    -1,    -1,    72,    73,    74,    75,    76,    33,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      89,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    -1,    61,    -1,    -1,    64,
      65,    66,    67,    68,    69,    38,    -1,    72,    73,    74,
      75,    76,    -1,    -1,    47,    65,    66,    67,    68,    69,
      70,    71,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    38,    88,    72,
      73,    74,    75,    76,    -1,    -1,    47,    65,    66,    67,
      68,    69,    70,    71,    -1,    38,    89,    66,    67,    68,
      69,    70,    71,    64,    65,    66,    67,    68,    69,    87,
      -1,    72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    38,    89,    72,
      73,    74,    75,    76,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    -1,    38,    89,    67,    68,    69,
      70,    71,    -1,    64,    65,    66,    67,    68,    69,    87,
      -1,    72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    -1,    89,    72,
      73,    74,    75,    76,    20,    21,    22,    23,    24,    -1,
      26,    27,    -1,    -1,    -1,    60,    89,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    75,    76,    60,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      -1,    75,    76,    65,    66,    67,    68,    69,    70,    71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    58,    59,    61,    64,    65,    66,    67,
      68,    69,    72,    73,    74,    75,    76,    89,    92,    95,
      96,    97,   105,   109,   111,   113,   114,   121,    60,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    98,   101,   119,    98,    98,   101,
      98,    63,    63,    64,    73,   121,   114,    98,    62,    98,
      62,   101,   121,    73,    60,   119,    61,    73,    61,    61,
     119,    61,    29,    30,    31,    89,   103,   104,   103,    61,
      89,   121,    98,   119,   120,    57,   119,    62,    62,    18,
     121,   121,   121,   121,   121,    89,   121,    18,    76,   121,
     122,   122,   121,   110,     0,    96,    86,    91,    88,    65,
      66,    67,    68,    69,    70,    71,    87,    88,    87,    87,
      87,    87,    87,    87,    87,    60,    18,    60,    87,    60,
      89,    89,    89,   121,   109,    88,   109,   122,    88,   119,
      18,    88,    16,    10,   121,   121,   122,   121,   122,    88,
      75,    77,    90,   105,   106,   107,   105,   114,   121,   121,
     121,   121,   121,   121,    62,    98,    62,    62,   117,   118,
      47,    63,    89,   115,   116,   121,   123,   125,   126,   126,
      89,   115,    62,    62,    88,   121,    87,   118,   122,   122,
     122,    90,    48,   103,    90,   120,    18,   121,    62,    60,
     121,    90,    77,   122,    93,    86,    88,    45,    13,   103,
     115,    88,    18,    36,   124,    60,    34,   118,    13,    90,
      90,    90,   109,    34,   121,    16,    87,   106,   117,    62,
     123,    90,   115,   121,   109,    88,   121,    13,    62,    89,
      60,   115,    20,    21,    22,    23,    24,    26,    27,   102,
     124,    60,    35,   112,    62,    16,    99,   122,    99,    88,
     121,    36,    99,    89,   101,    90,    60,   109,   100,    97,
     108,    91,    90,   108,   109
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    94,    95,    95,    96,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    98,    98,    99,    99,   100,    99,   101,   101,   101,
     101,   101,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   104,   104,   104,   104,   105,   105,
     106,   106,   107,   108,   108,   109,   109,   110,   109,   109,
     109,   109,   109,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   113,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   122,   122,   123,
     124,   124,   125,   125,   126
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
       2,     1,     2,     1,     2,     1,     1,     4,     5,     0,
       2,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     4,     1,
       3,     2,     2,     2,     2,     2,     2,     2,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       0,     2,     2,     4,     1
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
#line 1508 "syn.tab.c"
    break;

  case 5: /* definition: FUNC namedId ':' vsortlist PFEIL Sort VORRANG att  */
#line 94 "syn.y"
                                                                    {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1516 "syn.tab.c"
    break;

  case 6: /* definition: OTHER func ':' vsortlist PFEIL Sort att  */
#line 97 "syn.y"
                                                                  { (yyval.y_nod)=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1525 "syn.tab.c"
    break;

  case 7: /* definition: ATT Sort Id ',' Id ',' Id ',' Id  */
#line 101 "syn.y"
                                                           { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufkt(name((yyvsp[0].y_sym))))))));	}
#line 1536 "syn.tab.c"
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
#line 1552 "syn.tab.c"
    break;

  case 9: /* definition: VAR idlist ':' Sort  */
#line 118 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1558 "syn.tab.c"
    break;

  case 10: /* definition: NUM Sort  */
#line 119 "syn.y"
                                                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* setzt numbertype fuer mknum */}
#line 1564 "syn.tab.c"
    break;

  case 11: /* definition: SUBSORT Sort ',' Sort ATT Id  */
#line 120 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: Untersorte */
										      mknod(PARAM,(Node *) (yyvsp[-4].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufkt(name((yyvsp[0].y_sym))))));}
#line 1571 "syn.tab.c"
    break;

  case 12: /* definition: INTNUM Sort ATT Id  */
#line 122 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) intnum_def,    /* 2026: Sorte ganzer Zahlen */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufkt(name((yyvsp[0].y_sym)))));}
#line 1578 "syn.tab.c"
    break;

  case 13: /* definition: NUM idlist ':' Sort  */
#line 124 "syn.y"
                                                                 { /* Variablen fuer Numerische Zahlen */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1585 "syn.tab.c"
    break;

  case 14: /* definition: CST idlist ':' Sort  */
#line 126 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1591 "syn.tab.c"
    break;

  case 15: /* definition: SPEC Alg ':' alglist  */
#line 127 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1597 "syn.tab.c"
    break;

  case 16: /* definition: SPEC Alg ':' formlist  */
#line 128 "syn.y"
                                                         {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1603 "syn.tab.c"
    break;

  case 17: /* definition: ADDSPEC Alg ':' formlist  */
#line 129 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1609 "syn.tab.c"
    break;

  case 18: /* definition: SORT idlist  */
#line 130 "syn.y"
                                                                             {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1615 "syn.tab.c"
    break;

  case 19: /* definition: ALG idlist  */
#line 132 "syn.y"
                                                     {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1621 "syn.tab.c"
    break;

  case 20: /* definition: TERM idlist ':' Sort  */
#line 133 "syn.y"
                                                   {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1627 "syn.tab.c"
    break;

  case 21: /* idlist: namedId  */
#line 135 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1633 "syn.tab.c"
    break;

  case 22: /* idlist: namedId ',' idlist  */
#line 136 "syn.y"
                                                        {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1639 "syn.tab.c"
    break;

  case 23: /* att: %empty  */
#line 144 "syn.y"
                                        { (yyval.y_nod) = NULL;}
#line 1645 "syn.tab.c"
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
#line 1661 "syn.tab.c"
    break;

  case 25: /* $@1: %empty  */
#line 156 "syn.y"
                                          {block_begin();no_protect();}
#line 1667 "syn.tab.c"
    break;

  case 26: /* att: ATT '(' $@1 d_list ')' instruction  */
#line 157 "syn.y"
                                                                                        {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1673 "syn.tab.c"
    break;

  case 27: /* namedId: Id  */
#line 159 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1679 "syn.tab.c"
    break;

  case 28: /* namedId: Const  */
#line 160 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1685 "syn.tab.c"
    break;

  case 29: /* namedId: Var  */
#line 161 "syn.y"
                         { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1691 "syn.tab.c"
    break;

  case 30: /* namedId: func  */
#line 162 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1697 "syn.tab.c"
    break;

  case 31: /* namedId: Sort  */
#line 163 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1703 "syn.tab.c"
    break;

  case 32: /* namedId: Alg  */
#line 164 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1709 "syn.tab.c"
    break;

  case 33: /* namedId: Term  */
#line 165 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1715 "syn.tab.c"
    break;

  case 34: /* VORRANG: %empty  */
#line 168 "syn.y"
                                                        {(yyval.y_int) = Func;}
#line 1721 "syn.tab.c"
    break;

  case 35: /* VORRANG: LA1  */
#line 169 "syn.y"
                                                                        {(yyval.y_int) = La1;	/* Linksassoziativ */}
#line 1727 "syn.tab.c"
    break;

  case 36: /* VORRANG: LA2  */
#line 170 "syn.y"
                                                                        {(yyval.y_int) = La2;	/* Linksassoziativ */}
#line 1733 "syn.tab.c"
    break;

  case 37: /* VORRANG: LA3  */
#line 171 "syn.y"
                                                                        {(yyval.y_int) = La3;	/* Linksassoziativ */}
#line 1739 "syn.tab.c"
    break;

  case 38: /* VORRANG: LA4  */
#line 172 "syn.y"
                                                                        {(yyval.y_int) = La4;	/* Linksassoziativ */}
#line 1745 "syn.tab.c"
    break;

  case 39: /* VORRANG: LA5  */
#line 173 "syn.y"
                                                                        {(yyval.y_int) = La5;	/* Linksassoziativ */}
#line 1751 "syn.tab.c"
    break;

  case 40: /* VORRANG: RA  */
#line 174 "syn.y"
                                                                        {(yyval.y_int) = Ra;  	/* Rechtsassoziativ */}
#line 1757 "syn.tab.c"
    break;

  case 41: /* VORRANG: RU  */
#line 175 "syn.y"
                                                                        {(yyval.y_int) = Ru;	  /* Rechts Unaer */}
#line 1763 "syn.tab.c"
    break;

  case 42: /* condition: condfunc  */
#line 177 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1769 "syn.tab.c"
    break;

  case 43: /* condition: condfunc ',' condition  */
#line 178 "syn.y"
                                                        {(yyval.y_nod) = mknod(Cond,(Node *) and_cond,mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod)));}
#line 1775 "syn.tab.c"
    break;

  case 44: /* condfunc: LB '(' termlist ')'  */
#line 180 "syn.y"
                              {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1781 "syn.tab.c"
    break;

  case 45: /* condfunc: IN '(' termlist ')'  */
#line 181 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1787 "syn.tab.c"
    break;

  case 46: /* condfunc: NIN '(' termlist ')'  */
#line 182 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1793 "syn.tab.c"
    break;

  case 47: /* condfunc: '(' term ')'  */
#line 183 "syn.y"
                                                                        {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1799 "syn.tab.c"
    break;

  case 48: /* instructions: instruction  */
#line 185 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1805 "syn.tab.c"
    break;

  case 49: /* instructions: instruction ';' instructions  */
#line 186 "syn.y"
                                                                                       {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1811 "syn.tab.c"
    break;

  case 50: /* tinstructions: oinstructions  */
#line 188 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1817 "syn.tab.c"
    break;

  case 51: /* tinstructions: oinstructions '\n' tinstructions  */
#line 189 "syn.y"
                                                                                                                {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1823 "syn.tab.c"
    break;

  case 52: /* oinstructions: instructions  */
#line 191 "syn.y"
                                                {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1829 "syn.tab.c"
    break;

  case 53: /* d_list: definition  */
#line 196 "syn.y"
                                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1835 "syn.tab.c"
    break;

  case 54: /* d_list: definition ';' d_list  */
#line 197 "syn.y"
                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1841 "syn.tab.c"
    break;

  case 55: /* instruction: aninstruction  */
#line 199 "syn.y"
                                {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Locale Variablen pruefen ! */ }
#line 1847 "syn.tab.c"
    break;

  case 56: /* instruction: definition  */
#line 200 "syn.y"
                                                                        {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1853 "syn.tab.c"
    break;

  case 57: /* $@2: %empty  */
#line 201 "syn.y"
                                                                                                        {block_begin();no_protect();}
#line 1859 "syn.tab.c"
    break;

  case 58: /* instruction: '{' $@2 tinstructions '}'  */
#line 202 "syn.y"
                                                                        {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 1869 "syn.tab.c"
    break;

  case 59: /* instruction: WHILE condition instruction  */
#line 207 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* wird dann $3 */)));
																		WHILE_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1876 "syn.tab.c"
    break;

  case 60: /* instruction: IF condition instruction  */
#line 210 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		IF_THEN(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1883 "syn.tab.c"
    break;

  case 61: /* instruction: IF condition instruction ELSE instruction  */
#line 212 "syn.y"
                                                                        {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(merk) = (yyvsp[-2].y_nod);IF_ELSE(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1890 "syn.tab.c"
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
#line 1902 "syn.tab.c"
    break;

  case 63: /* aninstruction: %empty  */
#line 224 "syn.y"
                                {(yyval.y_nod)=NULL;}
#line 1908 "syn.tab.c"
    break;

  case 64: /* aninstruction: SYS String  */
#line 225 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) system_fkt,(Node *) ((yyvsp[0].y_sym)));}
#line 1914 "syn.tab.c"
    break;

  case 65: /* aninstruction: INC String  */
#line 226 "syn.y"
                                                                        {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fkt,(Node *) ((yyvsp[0].y_sym))); }
#line 1920 "syn.tab.c"
    break;

  case 66: /* aninstruction: INFO namedId  */
#line 227 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) info_fkt,(Node *) ((yyvsp[0].y_nod))); }
#line 1926 "syn.tab.c"
    break;

  case 67: /* aninstruction: REWR term ':' alglist  */
#line 228 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 1933 "syn.tab.c"
    break;

  case 68: /* aninstruction: prntlist  */
#line 230 "syn.y"
                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 1939 "syn.tab.c"
    break;

  case 69: /* aninstruction: PRTNUM String  */
#line 231 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 1945 "syn.tab.c"
    break;

  case 70: /* aninstruction: PRT prntlist  */
#line 232 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* ohne \n */ }
#line 1951 "syn.tab.c"
    break;

  case 71: /* aninstruction: OUT String  */
#line 233 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 1957 "syn.tab.c"
    break;

  case 72: /* aninstruction: DATA String  */
#line 234 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 1963 "syn.tab.c"
    break;

  case 73: /* aninstruction: DATA Const  */
#line 235 "syn.y"
                                                                        {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 1974 "syn.tab.c"
    break;

  case 74: /* aninstruction: Term EQ term  */
#line 241 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 1980 "syn.tab.c"
    break;

  case 75: /* aninstruction: Term EQ REWR term ':' alglist  */
#line 242 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 1986 "syn.tab.c"
    break;

  case 76: /* aninstruction: Const EQ term  */
#line 243 "syn.y"
                                                        { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 1992 "syn.tab.c"
    break;

  case 77: /* aninstruction: EXE func Id  */
#line 244 "syn.y"
                                                        {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufkt(name((yyvsp[0].y_sym)));
 													}
#line 2002 "syn.tab.c"
    break;

  case 78: /* aninstruction: LIFT '(' termlist ')' TO '(' termlist ')'  */
#line 249 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 2008 "syn.tab.c"
    break;

  case 79: /* aninstruction: DBG Const  */
#line 250 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 2014 "syn.tab.c"
    break;

  case 80: /* aninstruction: RETURN term  */
#line 251 "syn.y"
                                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) return_fkt,(yyvsp[0].y_nod));}
#line 2020 "syn.tab.c"
    break;

  case 81: /* aninstruction: QUIT  */
#line 252 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fkt,NULL);}
#line 2026 "syn.tab.c"
    break;

  case 82: /* aninstruction: OPT idlist  */
#line 253 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,(yyvsp[0].y_nod));}
#line 2032 "syn.tab.c"
    break;

  case 83: /* aninstruction: OPT  */
#line 254 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,NULL);   /* loeschen */}
#line 2038 "syn.tab.c"
    break;

  case 84: /* aninstruction: COMM funclist  */
#line 255 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,(yyvsp[0].y_nod));}
#line 2044 "syn.tab.c"
    break;

  case 85: /* aninstruction: COMM  */
#line 256 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,NULL);  /* loeschen */}
#line 2050 "syn.tab.c"
    break;

  case 86: /* aninstruction: DEFAULT  */
#line 257 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,NULL); /* loeschen */}
#line 2056 "syn.tab.c"
    break;

  case 87: /* aninstruction: DEFAULT func EQ term  */
#line 258 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),NULL),(yyvsp[0].y_nod)));}
#line 2063 "syn.tab.c"
    break;

  case 88: /* aninstruction: DEFAULT RIGHT func EQ term  */
#line 260 "syn.y"
                                                     {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),mknod(PARAM,NULL,NULL)),(yyvsp[0].y_nod)));}
#line 2070 "syn.tab.c"
    break;

  case 89: /* step: %empty  */
#line 263 "syn.y"
                        {(yyval.y_nod)=(Node *) NULL;}
#line 2076 "syn.tab.c"
    break;

  case 90: /* step: STEP term  */
#line 264 "syn.y"
                                        {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2082 "syn.tab.c"
    break;

  case 91: /* prntexpr: term  */
#line 266 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2088 "syn.tab.c"
    break;

  case 92: /* prntexpr: String  */
#line 267 "syn.y"
                                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2094 "syn.tab.c"
    break;

  case 93: /* prntlist: prntexpr  */
#line 269 "syn.y"
                                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2100 "syn.tab.c"
    break;

  case 94: /* prntlist: prntexpr ',' prntlist  */
#line 270 "syn.y"
                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2106 "syn.tab.c"
    break;

  case 95: /* alglist: Alg2  */
#line 272 "syn.y"
                                                                {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2112 "syn.tab.c"
    break;

  case 96: /* alglist: Alg2 ',' alglist  */
#line 273 "syn.y"
                                                        {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2118 "syn.tab.c"
    break;

  case 97: /* Alg2: Alg  */
#line 275 "syn.y"
                                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2124 "syn.tab.c"
    break;

  case 98: /* Alg2: '(' alglist ')'  */
#line 276 "syn.y"
                                                                {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2130 "syn.tab.c"
    break;

  case 99: /* sortlist: Sort  */
#line 278 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2136 "syn.tab.c"
    break;

  case 100: /* sortlist: Sort ',' sortlist  */
#line 279 "syn.y"
                                                                {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2142 "syn.tab.c"
    break;

  case 101: /* vsortlist: sortlist  */
#line 281 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2148 "syn.tab.c"
    break;

  case 102: /* vsortlist: sortlist VARPAR  */
#line 282 "syn.y"
                                                                        {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2154 "syn.tab.c"
    break;

  case 103: /* func: Func  */
#line 284 "syn.y"
                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2160 "syn.tab.c"
    break;

  case 104: /* func: La1  */
#line 285 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2166 "syn.tab.c"
    break;

  case 105: /* func: La2  */
#line 286 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2172 "syn.tab.c"
    break;

  case 106: /* func: La3  */
#line 287 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2178 "syn.tab.c"
    break;

  case 107: /* func: La4  */
#line 288 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2184 "syn.tab.c"
    break;

  case 108: /* func: La5  */
#line 289 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2190 "syn.tab.c"
    break;

  case 109: /* func: Ra  */
#line 290 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2196 "syn.tab.c"
    break;

  case 110: /* func: Ru  */
#line 291 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2202 "syn.tab.c"
    break;

  case 111: /* func: Bra  */
#line 292 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2208 "syn.tab.c"
    break;

  case 112: /* func: Bra1  */
#line 293 "syn.y"
                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2214 "syn.tab.c"
    break;

  case 113: /* funclist: func  */
#line 295 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2220 "syn.tab.c"
    break;

  case 114: /* funclist: func ',' funclist  */
#line 296 "syn.y"
                                                        {(yyval.y_nod) = mknod(Functs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2226 "syn.tab.c"
    break;

  case 115: /* term: Term  */
#line 298 "syn.y"
                                                                        {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); merkt sich keine Abhaengigkeiten und funktioniert nicht in Bloecken */ 
														}
#line 2233 "syn.tab.c"
    break;

  case 116: /* term: LAST  */
#line 300 "syn.y"
                                                                                        {(yyval.y_nod) = (Node *) lastterm;}
#line 2239 "syn.tab.c"
    break;

  case 117: /* term: Const  */
#line 301 "syn.y"
                                                                                        {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2245 "syn.tab.c"
    break;

  case 118: /* term: Const Bra1 termlist Bra2  */
#line 302 "syn.y"
                                                   {nphilf=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),nphilf), nphilf);}
#line 2252 "syn.tab.c"
    break;

  case 119: /* term: Var  */
#line 304 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2258 "syn.tab.c"
    break;

  case 120: /* term: '(' term ')'  */
#line 305 "syn.y"
                                                    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2264 "syn.tab.c"
    break;

  case 121: /* term: term Ru  */
#line 306 "syn.y"
                                                                      {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2270 "syn.tab.c"
    break;

  case 122: /* term: Func term  */
#line 307 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2276 "syn.tab.c"
    break;

  case 123: /* term: La1 term  */
#line 308 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2282 "syn.tab.c"
    break;

  case 124: /* term: La2 term  */
#line 309 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2288 "syn.tab.c"
    break;

  case 125: /* term: La3 term  */
#line 310 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2294 "syn.tab.c"
    break;

  case 126: /* term: La4 term  */
#line 311 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2300 "syn.tab.c"
    break;

  case 127: /* term: La5 term  */
#line 312 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2306 "syn.tab.c"
    break;

  case 128: /* term: Bra termlist Bra  */
#line 313 "syn.y"
                                                  {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2312 "syn.tab.c"
    break;

  case 129: /* term: Bra1 termlist Bra2  */
#line 314 "syn.y"
                                                {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2318 "syn.tab.c"
    break;

  case 130: /* term: Func '(' termlist ')'  */
#line 315 "syn.y"
                                                        {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2324 "syn.tab.c"
    break;

  case 131: /* term: term La1 term  */
#line 316 "syn.y"
                                                    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2331 "syn.tab.c"
    break;

  case 132: /* term: term La2 term  */
#line 318 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2338 "syn.tab.c"
    break;

  case 133: /* term: term La3 term  */
#line 320 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2345 "syn.tab.c"
    break;

  case 134: /* term: term La4 term  */
#line 322 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2352 "syn.tab.c"
    break;

  case 135: /* term: term La5 term  */
#line 324 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2359 "syn.tab.c"
    break;

  case 136: /* term: term Ra term  */
#line 326 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2366 "syn.tab.c"
    break;

  case 137: /* termlist: term  */
#line 329 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2372 "syn.tab.c"
    break;

  case 138: /* termlist: term ',' termlist  */
#line 330 "syn.y"
                                                        {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2378 "syn.tab.c"
    break;

  case 139: /* formula: term EQ term  */
#line 332 "syn.y"
                                        {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2384 "syn.tab.c"
    break;

  case 140: /* vinstr: %empty  */
#line 334 "syn.y"
                                                                {(yyval.y_nod) = NULL;}
#line 2390 "syn.tab.c"
    break;

  case 141: /* vinstr: DO instruction  */
#line 335 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2396 "syn.tab.c"
    break;

  case 142: /* cformula: formula vinstr  */
#line 337 "syn.y"
                                                                        {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2403 "syn.tab.c"
    break;

  case 143: /* cformula: IF condition formula vinstr  */
#line 339 "syn.y"
                                               {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2410 "syn.tab.c"
    break;

  case 144: /* formlist: cformula  */
#line 342 "syn.y"
                                                                {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL dient zum Einhaengen weiterer Formeln !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. wegen SPEC real : A+B=C;a=3 */
															}
#line 2418 "syn.tab.c"
    break;


#line 2422 "syn.tab.c"

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

#line 346 "syn.y"

