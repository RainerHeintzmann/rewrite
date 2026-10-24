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


#line 113 "syn.tab.c"

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
  YYSYMBOL_Id = 58,                        /* Id  */
  YYSYMBOL_String = 59,                    /* String  */
  YYSYMBOL_Sort = 60,                      /* Sort  */
  YYSYMBOL_Alg = 61,                       /* Alg  */
  YYSYMBOL_Term = 62,                      /* Term  */
  YYSYMBOL_La1 = 63,                       /* La1  */
  YYSYMBOL_La2 = 64,                       /* La2  */
  YYSYMBOL_La3 = 65,                       /* La3  */
  YYSYMBOL_La4 = 66,                       /* La4  */
  YYSYMBOL_La5 = 67,                       /* La5  */
  YYSYMBOL_Ru = 68,                        /* Ru  */
  YYSYMBOL_Ra = 69,                        /* Ra  */
  YYSYMBOL_Func = 70,                      /* Func  */
  YYSYMBOL_Const = 71,                     /* Const  */
  YYSYMBOL_Var = 72,                       /* Var  */
  YYSYMBOL_Bra = 73,                       /* Bra  */
  YYSYMBOL_Bra1 = 74,                      /* Bra1  */
  YYSYMBOL_Bra2 = 75,                      /* Bra2  */
  YYSYMBOL_Terms = 76,                     /* Terms  */
  YYSYMBOL_Form = 77,                      /* Form  */
  YYSYMBOL_Sorts = 78,                     /* Sorts  */
  YYSYMBOL_Functs = 79,                    /* Functs  */
  YYSYMBOL_Forms = 80,                     /* Forms  */
  YYSYMBOL_Algs = 81,                      /* Algs  */
  YYSYMBOL_Cond2 = 82,                     /* Cond2  */
  YYSYMBOL_Cond = 83,                      /* Cond  */
  YYSYMBOL_84_n_ = 84,                     /* '\n'  */
  YYSYMBOL_85_ = 85,                       /* ':'  */
  YYSYMBOL_86_ = 86,                       /* ','  */
  YYSYMBOL_87_ = 87,                       /* '('  */
  YYSYMBOL_88_ = 88,                       /* ')'  */
  YYSYMBOL_89_ = 89,                       /* ';'  */
  YYSYMBOL_90_ = 90,                       /* '{'  */
  YYSYMBOL_91_ = 91,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 92,                  /* $accept  */
  YYSYMBOL_prog = 93,                      /* prog  */
  YYSYMBOL_line = 94,                      /* line  */
  YYSYMBOL_definition = 95,                /* definition  */
  YYSYMBOL_idlist = 96,                    /* idlist  */
  YYSYMBOL_att = 97,                       /* att  */
  YYSYMBOL_98_1 = 98,                      /* $@1  */
  YYSYMBOL_namedId = 99,                   /* namedId  */
  YYSYMBOL_VORRANG = 100,                  /* VORRANG  */
  YYSYMBOL_condition = 101,                /* condition  */
  YYSYMBOL_condfunc = 102,                 /* condfunc  */
  YYSYMBOL_instructions = 103,             /* instructions  */
  YYSYMBOL_tinstructions = 104,            /* tinstructions  */
  YYSYMBOL_oinstructions = 105,            /* oinstructions  */
  YYSYMBOL_d_list = 106,                   /* d_list  */
  YYSYMBOL_instruction = 107,              /* instruction  */
  YYSYMBOL_108_2 = 108,                    /* $@2  */
  YYSYMBOL_aninstruction = 109,            /* aninstruction  */
  YYSYMBOL_step = 110,                     /* step  */
  YYSYMBOL_prntexpr = 111,                 /* prntexpr  */
  YYSYMBOL_prntlist = 112,                 /* prntlist  */
  YYSYMBOL_alglist = 113,                  /* alglist  */
  YYSYMBOL_Alg2 = 114,                     /* Alg2  */
  YYSYMBOL_sortlist = 115,                 /* sortlist  */
  YYSYMBOL_vsortlist = 116,                /* vsortlist  */
  YYSYMBOL_func = 117,                     /* func  */
  YYSYMBOL_funclist = 118,                 /* funclist  */
  YYSYMBOL_term = 119,                     /* term  */
  YYSYMBOL_termlist = 120,                 /* termlist  */
  YYSYMBOL_formula = 121,                  /* formula  */
  YYSYMBOL_vinstr = 122,                   /* vinstr  */
  YYSYMBOL_cformula = 123,                 /* cformula  */
  YYSYMBOL_formlist = 124                  /* formlist  */
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
#define YYFINAL  130
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   624

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  295

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   338


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
      84,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      87,    88,     2,     2,    86,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    85,    89,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    90,     2,    91,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    82,    82,    83,    85,    93,    96,   100,   106,   117,
     118,   119,   121,   122,   123,   124,   125,   127,   128,   130,
     131,   139,   140,   151,   151,   154,   155,   156,   157,   158,
     159,   160,   163,   164,   165,   166,   167,   168,   169,   170,
     172,   173,   175,   176,   177,   178,   180,   181,   183,   184,
     186,   191,   192,   194,   195,   196,   196,   202,   205,   207,
     209,   219,   220,   221,   222,   223,   225,   226,   227,   228,
     229,   230,   236,   237,   238,   239,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   255,   258,   259,   261,
     262,   264,   265,   267,   268,   270,   271,   273,   274,   276,
     277,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   290,   291,   293,   295,   296,   297,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     313,   315,   317,   319,   321,   324,   325,   327,   329,   330,
     332,   334,   337
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
  "RETURN", "OPT", "COMM", "DEFAULT", "RIGHT", "Id", "String", "Sort",
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

#define YYPACT_NINF (-248)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-30)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     284,   508,   508,   508,   508,   508,    -3,     0,   381,   242,
     508,   525,   -15,   508,   381,    -9,  -248,    18,   537,    20,
      -2,    19,   537,    21,   -10,   -10,    23,     2,  -248,   381,
     508,   537,   491,  -248,    66,   381,   381,   381,   381,   381,
     399,   -14,  -248,   381,   381,   381,  -248,   196,  -248,  -248,
       3,    11,  -248,    16,  -248,   549,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,    22,    17,  -248,    25,  -248,    27,  -248,    28,
      36,  -248,    31,   -16,  -248,    38,   -59,    39,    48,  -248,
     109,  -248,    51,    40,  -248,  -248,  -248,  -248,    57,  -248,
      49,    55,    56,   381,   284,    58,   284,  -248,   381,   549,
    -248,    60,  -248,   537,    67,     1,   555,   373,    26,    30,
     -34,   381,  -248,   381,   381,   465,    53,    72,   301,   284,
    -248,  -248,  -248,   284,   242,   381,   381,   381,   381,   381,
    -248,   381,    88,   508,    92,    93,   314,   344,   -47,    94,
      95,    71,   381,    73,    93,  -248,   381,   381,   381,   452,
     121,   -10,  -248,    82,   537,   161,   381,   381,   549,   439,
     102,   549,   119,   381,  -248,  -248,  -248,  -248,   104,   113,
    -248,  -248,   555,   373,    26,    30,   -34,   -34,  -248,  -248,
    -248,   122,   164,   201,   -10,  -248,   362,  -248,   132,   210,
     183,  -248,  -248,  -248,   -47,  -248,  -248,  -248,   162,   329,
      93,   208,   135,   137,   138,  -248,   284,  -248,   198,  -248,
     381,   549,   478,  -248,  -248,  -248,  -248,   284,    93,  -248,
     170,   381,   153,   -47,   381,   284,  -248,   158,   381,   241,
     197,  -248,  -248,  -248,  -248,   169,   549,   -47,  -248,  -248,
     141,   183,  -248,  -248,   549,  -248,   206,   415,   212,   265,
     381,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,   265,
    -248,   199,   381,   246,   265,   427,  -248,   209,  -248,   226,
     549,   284,  -248,  -248,  -248,  -248,  -248,  -248,   177,   207,
     214,   177,   284,  -248,  -248
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    79,     0,
      81,    83,    84,    90,   113,     0,     0,     0,     0,     0,
       0,   115,   117,     0,     0,     0,    55,    61,     2,    54,
       0,    46,    53,    91,    66,    89,    25,    29,    30,    31,
     102,   103,   104,   105,   106,   108,   107,   101,    26,    27,
     109,   110,     0,    19,    28,     0,    16,     0,    17,     0,
       0,   113,   115,     0,    68,     0,    10,     0,     0,    64,
       0,    77,     0,     0,    70,    71,    69,    63,     0,    62,
       0,     0,     0,     0,    61,    40,    61,    67,     0,    78,
      80,   111,    82,     0,     0,     0,   121,   122,   123,   124,
     125,     0,   120,     0,     0,   135,     0,     0,     0,    61,
       1,     3,     4,    61,     0,     0,     0,     0,     0,     0,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,     0,     0,     0,     0,
      58,     0,    57,     0,     0,     0,     0,     0,    72,     0,
       0,    74,     0,     0,   126,   127,   118,    50,     0,    48,
      47,    92,   129,   130,   131,   132,   133,   134,    12,    20,
       9,    97,    99,     0,     0,    95,     0,    13,    93,     0,
     138,   142,    14,    15,     0,    65,    18,    11,     0,     0,
       0,     0,     0,     0,     0,    45,    61,    41,     0,   112,
       0,    85,     0,   128,   116,   136,    56,    61,     0,   100,
       0,     0,     0,     0,     0,    61,   140,     0,     0,     0,
       0,    42,    43,    44,    59,     0,    86,     0,    49,    98,
      32,   138,    96,    94,   137,   139,     0,    87,     0,    21,
       0,    73,    33,    34,    35,    36,    37,    39,    38,    21,
     141,     0,     0,     0,    21,     0,     6,     0,     5,     0,
      88,    61,     8,    23,    22,    76,     7,    60,     0,    51,
       0,     0,    61,    52,    24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -248,  -248,   263,  -247,    13,  -215,  -248,    -4,  -248,   -23,
    -248,  -116,    84,  -248,    29,   -94,  -248,  -248,  -248,  -248,
      -1,  -143,  -248,    90,  -129,    24,   155,    -7,   -38,   101,
      91,  -248,   194
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    47,    48,    49,    72,   276,   288,    73,   269,   104,
     105,    50,   178,   179,   290,    51,   129,    52,   273,    53,
      54,   232,   198,   192,   193,    74,   112,    55,   126,   200,
     236,   201,   202
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    83,   106,   197,   123,   205,   127,    90,    84,    89,
     160,   167,   162,   177,   195,    75,    76,   180,    78,   100,
     101,   102,   109,    85,    87,   211,   -29,   -29,   116,   117,
     118,   119,   120,   122,   140,   141,   125,   125,   128,    16,
     204,   289,    93,   110,   289,    88,    98,   135,   136,   137,
     138,   139,   140,   141,   278,   111,   114,    96,    79,   282,
     124,    80,    91,    81,    35,    36,    37,    38,    39,   148,
     163,    40,    82,    42,    43,    44,    92,   103,    97,    94,
      99,   239,   107,   170,   115,   166,   172,   132,    45,   108,
     253,    95,   138,   139,   140,   141,   159,   139,   140,   141,
     133,   125,   134,   143,   261,   124,   151,   142,   168,   153,
     144,   177,   145,   146,   169,   155,   171,   125,   212,   213,
     214,   147,   244,   149,   150,   154,   174,   152,   182,   183,
     184,   185,   186,   181,   187,   225,   156,   165,   217,   199,
     199,   255,   157,   158,   161,   209,   164,   175,   188,   125,
     125,   125,   190,   191,   206,   207,   189,   208,   210,   221,
     222,   262,   263,   264,   265,   266,   125,   267,   268,   216,
     218,   231,   135,   136,   137,   138,   139,   140,   141,   220,
       1,     2,     3,     4,     5,     6,     7,   287,   111,   128,
     223,    10,    11,    12,   224,   226,   130,   227,   294,     1,
       2,     3,     4,     5,     6,     7,     8,     9,   228,   229,
      10,    11,    12,   246,   230,    13,    17,    18,   233,   235,
     237,   240,   277,   241,   199,   242,   243,   254,   234,    14,
     250,   257,   245,    15,    16,    17,    18,    19,    20,    21,
      22,   252,    23,    24,   256,    25,    26,    27,    28,    29,
      30,    31,    32,   125,   258,    33,   260,   259,    34,    35,
      36,    37,    38,    39,   271,   280,    40,    41,    42,    43,
      44,   284,   274,   135,   136,   137,   138,   139,   140,   141,
      16,   275,   281,    45,   286,   279,    46,     1,     2,     3,
       4,     5,     6,     7,     8,     9,   291,   285,    10,    11,
      12,    33,   292,    13,    81,    35,    36,    37,    38,    39,
     131,   248,    40,    82,    42,    43,    44,    14,   249,   219,
     293,    15,    16,    17,    18,    19,    20,    21,    22,    45,
      23,    24,   251,    25,    26,    27,    28,    29,    30,    31,
      32,   203,   270,    33,     0,     0,    34,    35,    36,    37,
      38,    39,    16,     0,    40,    41,    42,    43,    44,     0,
       0,   194,     0,   238,   135,   136,   137,   138,   139,   140,
     141,    45,     0,     0,    46,   195,    81,    35,    36,    37,
      38,    39,    16,     0,    40,    82,    42,    43,    44,   176,
       0,   194,   135,   136,   137,   138,   139,   140,   141,     0,
      16,   196,     0,     0,     0,     0,    81,    35,    36,    37,
      38,    39,     0,     0,    40,    82,    42,    43,    44,    16,
       0,     0,     0,   195,    81,    35,    36,    37,    38,    39,
       0,    45,    40,    82,    42,    43,    44,    16,   137,   138,
     139,   140,   141,    81,    35,    36,    37,    38,    39,   196,
     272,    40,    82,    42,    43,    44,     0,     0,     0,     0,
       0,    81,    35,    36,    37,    38,    39,     0,    45,    40,
      82,    42,    43,    44,     0,     0,     0,     0,   135,   136,
     137,   138,   139,   140,   141,    56,   121,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,   135,   136,   137,   138,   139,   140,   141,     0,
       0,     0,     0,     0,   283,   135,   136,   137,   138,   139,
     140,   141,     0,     0,     0,   173,     0,   176,   135,   136,
     137,   138,   139,   140,   141,     0,     0,     0,     0,     0,
     215,   135,   136,   137,   138,   139,   140,   141,   113,     0,
       0,   173,     0,     0,    60,    61,    62,    63,    64,    65,
      66,    67,     0,   247,    70,    71,    56,     0,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    56,     0,    86,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
      70,    71,   135,   136,   137,   138,   139,   140,   141,   136,
     137,   138,   139,   140,   141
};

static const yytype_int16 yycheck[] =
{
       4,     8,    25,   146,    18,   148,    44,    14,     9,    13,
     104,    10,   106,   129,    61,     2,     3,   133,     5,    29,
      30,    31,    29,    10,    11,   154,    85,    86,    35,    36,
      37,    38,    39,    40,    68,    69,    43,    44,    45,    38,
      87,   288,    18,    30,   291,    60,    22,    63,    64,    65,
      66,    67,    68,    69,   269,    31,    32,    59,    61,   274,
      74,    61,    71,    62,    63,    64,    65,    66,    67,    85,
     108,    70,    71,    72,    73,    74,    58,    87,    59,    59,
      59,   210,    59,   121,    18,    18,   124,    84,    87,    87,
     233,    71,    66,    67,    68,    69,   103,    67,    68,    69,
      89,   108,    86,    86,   247,    74,    58,    85,   115,    58,
      85,   227,    85,    85,   121,    58,   123,   124,   156,   157,
     158,    85,   216,    85,    85,    85,    73,    18,   135,   136,
     137,   138,   139,   134,   141,   173,    87,   113,   161,   146,
     147,   235,    87,    87,    86,   152,    86,    75,    60,   156,
     157,   158,    60,    60,    60,    60,   143,    86,    85,   166,
     167,    20,    21,    22,    23,    24,   173,    26,    27,    48,
      88,   194,    63,    64,    65,    66,    67,    68,    69,    18,
       3,     4,     5,     6,     7,     8,     9,   281,   164,   196,
      88,    14,    15,    16,    75,    91,     0,    84,   292,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    86,    45,
      14,    15,    16,   220,    13,    19,    39,    40,    86,    36,
      58,    13,   260,    88,   231,    88,    88,   234,    18,    33,
      60,   238,    34,    37,    38,    39,    40,    41,    42,    43,
      44,    88,    46,    47,    86,    49,    50,    51,    52,    53,
      54,    55,    56,   260,    13,    59,    87,    60,    62,    63,
      64,    65,    66,    67,    58,   272,    70,    71,    72,    73,
      74,   275,    60,    63,    64,    65,    66,    67,    68,    69,
      38,    16,    36,    87,    58,    86,    90,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    89,    88,    14,    15,
      16,    59,    88,    19,    62,    63,    64,    65,    66,    67,
      47,   227,    70,    71,    72,    73,    74,    33,   228,   164,
     291,    37,    38,    39,    40,    41,    42,    43,    44,    87,
      46,    47,   231,    49,    50,    51,    52,    53,    54,    55,
      56,   147,   251,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    38,    -1,    70,    71,    72,    73,    74,    -1,
      -1,    47,    -1,    34,    63,    64,    65,    66,    67,    68,
      69,    87,    -1,    -1,    90,    61,    62,    63,    64,    65,
      66,    67,    38,    -1,    70,    71,    72,    73,    74,    88,
      -1,    47,    63,    64,    65,    66,    67,    68,    69,    -1,
      38,    87,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    -1,    70,    71,    72,    73,    74,    38,
      -1,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      -1,    87,    70,    71,    72,    73,    74,    38,    65,    66,
      67,    68,    69,    62,    63,    64,    65,    66,    67,    87,
      35,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    87,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    58,    87,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    63,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    87,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    86,    -1,    88,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      88,    63,    64,    65,    66,    67,    68,    69,    57,    -1,
      -1,    86,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    85,    73,    74,    58,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      73,    74,    63,    64,    65,    66,    67,    68,    69,    64,
      65,    66,    67,    68,    69
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    59,    62,    63,    64,    65,    66,    67,
      70,    71,    72,    73,    74,    87,    90,    93,    94,    95,
     103,   107,   109,   111,   112,   119,    58,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    96,    99,   117,    96,    96,    99,    96,    61,
      61,    62,    71,   119,   112,    96,    60,    96,    60,    99,
     119,    71,    58,   117,    59,    71,    59,    59,   117,    59,
      29,    30,    31,    87,   101,   102,   101,    59,    87,   119,
      96,   117,   118,    57,   117,    18,   119,   119,   119,   119,
     119,    87,   119,    18,    74,   119,   120,   120,   119,   108,
       0,    94,    84,    89,    86,    63,    64,    65,    66,    67,
      68,    69,    85,    86,    85,    85,    85,    85,    85,    85,
      85,    58,    18,    58,    85,    58,    87,    87,    87,   119,
     107,    86,   107,   120,    86,   117,    18,    10,   119,   119,
     120,   119,   120,    86,    73,    75,    88,   103,   104,   105,
     103,   112,   119,   119,   119,   119,   119,   119,    60,    96,
      60,    60,   115,   116,    47,    61,    87,   113,   114,   119,
     121,   123,   124,   124,    87,   113,    60,    60,    86,   119,
      85,   116,   120,   120,   120,    88,    48,   101,    88,   118,
      18,   119,   119,    88,    75,   120,    91,    84,    86,    45,
      13,   101,   113,    86,    18,    36,   122,    58,    34,   116,
      13,    88,    88,    88,   107,    34,   119,    85,   104,   115,
      60,   121,    88,   113,   119,   107,    86,   119,    13,    60,
      87,   113,    20,    21,    22,    23,    24,    26,    27,   100,
     122,    58,    35,   110,    60,    16,    97,   120,    97,    86,
     119,    36,    97,    87,    99,    88,    58,   107,    98,    95,
     106,    89,    88,   106,   107
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    92,    93,    93,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    96,
      96,    97,    97,    98,    97,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     101,   101,   102,   102,   102,   102,   103,   103,   104,   104,
     105,   106,   106,   107,   107,   108,   107,   107,   107,   107,
     107,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   120,   120,   121,   122,   122,
     123,   123,   124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     8,     7,     9,     8,     4,
       2,     4,     4,     4,     4,     4,     2,     2,     4,     1,
       3,     0,     2,     0,     6,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     4,     4,     3,     1,     3,     1,     3,
       1,     1,     3,     1,     1,     0,     4,     3,     3,     5,
       9,     0,     2,     2,     2,     4,     1,     2,     2,     2,
       2,     2,     3,     6,     3,     3,     8,     2,     2,     1,
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
#line 85 "syn.y"
                                    {Node * temp;
														if ((yyvsp[-1].y_nod)) { temp = mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod));
															is_running();
															CALLFUNCT(temp);
															is_not_running();
															delete(temp);}
														}
#line 1497 "syn.tab.c"
    break;

  case 5: /* definition: FUNC namedId ':' vsortlist PFEIL Sort VORRANG att  */
#line 93 "syn.y"
                                                                    {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1505 "syn.tab.c"
    break;

  case 6: /* definition: OTHER func ':' vsortlist PFEIL Sort att  */
#line 96 "syn.y"
                                                                  { (yyval.y_nod)=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1514 "syn.tab.c"
    break;

  case 7: /* definition: ATT Sort Id ',' Id ',' Id ',' Id  */
#line 100 "syn.y"
                                                           { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufkt(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufkt(name((yyvsp[0].y_sym))))))));	}
#line 1525 "syn.tab.c"
    break;

  case 8: /* definition: BRA Id Id ':' vsortlist PFEIL Sort att  */
#line 106 "syn.y"
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
#line 1541 "syn.tab.c"
    break;

  case 9: /* definition: VAR idlist ':' Sort  */
#line 117 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1547 "syn.tab.c"
    break;

  case 10: /* definition: NUM Sort  */
#line 118 "syn.y"
                                                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* setzt numbertype fuer mknum */}
#line 1553 "syn.tab.c"
    break;

  case 11: /* definition: NUM idlist ':' Sort  */
#line 119 "syn.y"
                                                                 { /* Variablen fuer Numerische Zahlen */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1560 "syn.tab.c"
    break;

  case 12: /* definition: CST idlist ':' Sort  */
#line 121 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1566 "syn.tab.c"
    break;

  case 13: /* definition: SPEC Alg ':' alglist  */
#line 122 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1572 "syn.tab.c"
    break;

  case 14: /* definition: SPEC Alg ':' formlist  */
#line 123 "syn.y"
                                                         {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1578 "syn.tab.c"
    break;

  case 15: /* definition: ADDSPEC Alg ':' formlist  */
#line 124 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1584 "syn.tab.c"
    break;

  case 16: /* definition: SORT idlist  */
#line 125 "syn.y"
                                                                             {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1590 "syn.tab.c"
    break;

  case 17: /* definition: ALG idlist  */
#line 127 "syn.y"
                                                     {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1596 "syn.tab.c"
    break;

  case 18: /* definition: TERM idlist ':' Sort  */
#line 128 "syn.y"
                                                   {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1602 "syn.tab.c"
    break;

  case 19: /* idlist: namedId  */
#line 130 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1608 "syn.tab.c"
    break;

  case 20: /* idlist: namedId ',' idlist  */
#line 131 "syn.y"
                                                        {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1614 "syn.tab.c"
    break;

  case 21: /* att: %empty  */
#line 139 "syn.y"
                                        { (yyval.y_nod) = NULL;}
#line 1620 "syn.tab.c"
    break;

  case 22: /* att: ATT namedId  */
#line 140 "syn.y"
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
#line 1636 "syn.tab.c"
    break;

  case 23: /* $@1: %empty  */
#line 151 "syn.y"
                                          {block_begin();no_protect();}
#line 1642 "syn.tab.c"
    break;

  case 24: /* att: ATT '(' $@1 d_list ')' instruction  */
#line 152 "syn.y"
                                                                                        {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1648 "syn.tab.c"
    break;

  case 25: /* namedId: Id  */
#line 154 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1654 "syn.tab.c"
    break;

  case 26: /* namedId: Const  */
#line 155 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1660 "syn.tab.c"
    break;

  case 27: /* namedId: Var  */
#line 156 "syn.y"
                         { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1666 "syn.tab.c"
    break;

  case 28: /* namedId: func  */
#line 157 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1672 "syn.tab.c"
    break;

  case 29: /* namedId: Sort  */
#line 158 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1678 "syn.tab.c"
    break;

  case 30: /* namedId: Alg  */
#line 159 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1684 "syn.tab.c"
    break;

  case 31: /* namedId: Term  */
#line 160 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1690 "syn.tab.c"
    break;

  case 32: /* VORRANG: %empty  */
#line 163 "syn.y"
                                                        {(yyval.y_int) = Func;}
#line 1696 "syn.tab.c"
    break;

  case 33: /* VORRANG: LA1  */
#line 164 "syn.y"
                                                                        {(yyval.y_int) = La1;	/* Linksassoziativ */}
#line 1702 "syn.tab.c"
    break;

  case 34: /* VORRANG: LA2  */
#line 165 "syn.y"
                                                                        {(yyval.y_int) = La2;	/* Linksassoziativ */}
#line 1708 "syn.tab.c"
    break;

  case 35: /* VORRANG: LA3  */
#line 166 "syn.y"
                                                                        {(yyval.y_int) = La3;	/* Linksassoziativ */}
#line 1714 "syn.tab.c"
    break;

  case 36: /* VORRANG: LA4  */
#line 167 "syn.y"
                                                                        {(yyval.y_int) = La4;	/* Linksassoziativ */}
#line 1720 "syn.tab.c"
    break;

  case 37: /* VORRANG: LA5  */
#line 168 "syn.y"
                                                                        {(yyval.y_int) = La5;	/* Linksassoziativ */}
#line 1726 "syn.tab.c"
    break;

  case 38: /* VORRANG: RA  */
#line 169 "syn.y"
                                                                        {(yyval.y_int) = Ra;  	/* Rechtsassoziativ */}
#line 1732 "syn.tab.c"
    break;

  case 39: /* VORRANG: RU  */
#line 170 "syn.y"
                                                                        {(yyval.y_int) = Ru;	  /* Rechts Unaer */}
#line 1738 "syn.tab.c"
    break;

  case 40: /* condition: condfunc  */
#line 172 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1744 "syn.tab.c"
    break;

  case 41: /* condition: condfunc ',' condition  */
#line 173 "syn.y"
                                                        {(yyval.y_nod) = mknod(Cond,(Node *) and_cond,mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod)));}
#line 1750 "syn.tab.c"
    break;

  case 42: /* condfunc: LB '(' termlist ')'  */
#line 175 "syn.y"
                              {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1756 "syn.tab.c"
    break;

  case 43: /* condfunc: IN '(' termlist ')'  */
#line 176 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1762 "syn.tab.c"
    break;

  case 44: /* condfunc: NIN '(' termlist ')'  */
#line 177 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1768 "syn.tab.c"
    break;

  case 45: /* condfunc: '(' term ')'  */
#line 178 "syn.y"
                                                                        {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1774 "syn.tab.c"
    break;

  case 46: /* instructions: instruction  */
#line 180 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1780 "syn.tab.c"
    break;

  case 47: /* instructions: instruction ';' instructions  */
#line 181 "syn.y"
                                                                                       {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1786 "syn.tab.c"
    break;

  case 48: /* tinstructions: oinstructions  */
#line 183 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1792 "syn.tab.c"
    break;

  case 49: /* tinstructions: oinstructions '\n' tinstructions  */
#line 184 "syn.y"
                                                                                                                {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1798 "syn.tab.c"
    break;

  case 50: /* oinstructions: instructions  */
#line 186 "syn.y"
                                                {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1804 "syn.tab.c"
    break;

  case 51: /* d_list: definition  */
#line 191 "syn.y"
                                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1810 "syn.tab.c"
    break;

  case 52: /* d_list: definition ';' d_list  */
#line 192 "syn.y"
                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1816 "syn.tab.c"
    break;

  case 53: /* instruction: aninstruction  */
#line 194 "syn.y"
                                {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Locale Variablen pruefen ! */ }
#line 1822 "syn.tab.c"
    break;

  case 54: /* instruction: definition  */
#line 195 "syn.y"
                                                                        {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1828 "syn.tab.c"
    break;

  case 55: /* $@2: %empty  */
#line 196 "syn.y"
                                                                                                        {block_begin();no_protect();}
#line 1834 "syn.tab.c"
    break;

  case 56: /* instruction: '{' $@2 tinstructions '}'  */
#line 197 "syn.y"
                                                                        {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 1844 "syn.tab.c"
    break;

  case 57: /* instruction: WHILE condition instruction  */
#line 202 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* wird dann $3 */)));
																		WHILE_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1851 "syn.tab.c"
    break;

  case 58: /* instruction: IF condition instruction  */
#line 205 "syn.y"
                                                        {Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		IF_THEN(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1858 "syn.tab.c"
    break;

  case 59: /* instruction: IF condition instruction ELSE instruction  */
#line 207 "syn.y"
                                                                        {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(merk) = (yyvsp[-2].y_nod);IF_ELSE(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1865 "syn.tab.c"
    break;

  case 60: /* instruction: FOR term EQ term TO term step DO instruction  */
#line 210 "syn.y"
                                                                                                                {Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) forschleife,
																mknod(PARAM,
																	mknod(PARAM,(yyvsp[-5].y_nod),(yyvsp[-3].y_nod)),
																	mknod(PARAM,
																		mknod(PARAM,(yyvsp[-2].y_nod),(Node *) ((yyvsp[-7].y_nod))),
																		NULL /* $9 */) )));	
														FOR_BODY(merk) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 1877 "syn.tab.c"
    break;

  case 61: /* aninstruction: %empty  */
#line 219 "syn.y"
                                {(yyval.y_nod)=NULL;}
#line 1883 "syn.tab.c"
    break;

  case 62: /* aninstruction: SYS String  */
#line 220 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) system_fkt,(Node *) ((yyvsp[0].y_sym)));}
#line 1889 "syn.tab.c"
    break;

  case 63: /* aninstruction: INC String  */
#line 221 "syn.y"
                                                                        {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fkt,(Node *) ((yyvsp[0].y_sym))); }
#line 1895 "syn.tab.c"
    break;

  case 64: /* aninstruction: INFO namedId  */
#line 222 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) info_fkt,(Node *) ((yyvsp[0].y_nod))); }
#line 1901 "syn.tab.c"
    break;

  case 65: /* aninstruction: REWR term ':' alglist  */
#line 223 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 1908 "syn.tab.c"
    break;

  case 66: /* aninstruction: prntlist  */
#line 225 "syn.y"
                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 1914 "syn.tab.c"
    break;

  case 67: /* aninstruction: PRTNUM String  */
#line 226 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 1920 "syn.tab.c"
    break;

  case 68: /* aninstruction: PRT prntlist  */
#line 227 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* ohne \n */ }
#line 1926 "syn.tab.c"
    break;

  case 69: /* aninstruction: OUT String  */
#line 228 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 1932 "syn.tab.c"
    break;

  case 70: /* aninstruction: DATA String  */
#line 229 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 1938 "syn.tab.c"
    break;

  case 71: /* aninstruction: DATA Const  */
#line 230 "syn.y"
                                                                        {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 1949 "syn.tab.c"
    break;

  case 72: /* aninstruction: Term EQ term  */
#line 236 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 1955 "syn.tab.c"
    break;

  case 73: /* aninstruction: Term EQ REWR term ':' alglist  */
#line 237 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 1961 "syn.tab.c"
    break;

  case 74: /* aninstruction: Const EQ term  */
#line 238 "syn.y"
                                                        { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 1967 "syn.tab.c"
    break;

  case 75: /* aninstruction: EXE func Id  */
#line 239 "syn.y"
                                                        {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufkt(name((yyvsp[0].y_sym)));
 													}
#line 1977 "syn.tab.c"
    break;

  case 76: /* aninstruction: LIFT '(' termlist ')' TO '(' termlist ')'  */
#line 244 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 1983 "syn.tab.c"
    break;

  case 77: /* aninstruction: DBG Const  */
#line 245 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 1989 "syn.tab.c"
    break;

  case 78: /* aninstruction: RETURN term  */
#line 246 "syn.y"
                                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) return_fkt,(yyvsp[0].y_nod));}
#line 1995 "syn.tab.c"
    break;

  case 79: /* aninstruction: QUIT  */
#line 247 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fkt,NULL);}
#line 2001 "syn.tab.c"
    break;

  case 80: /* aninstruction: OPT idlist  */
#line 248 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,(yyvsp[0].y_nod));}
#line 2007 "syn.tab.c"
    break;

  case 81: /* aninstruction: OPT  */
#line 249 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fkt,NULL);   /* loeschen */}
#line 2013 "syn.tab.c"
    break;

  case 82: /* aninstruction: COMM funclist  */
#line 250 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,(yyvsp[0].y_nod));}
#line 2019 "syn.tab.c"
    break;

  case 83: /* aninstruction: COMM  */
#line 251 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fkt,NULL);  /* loeschen */}
#line 2025 "syn.tab.c"
    break;

  case 84: /* aninstruction: DEFAULT  */
#line 252 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,NULL); /* loeschen */}
#line 2031 "syn.tab.c"
    break;

  case 85: /* aninstruction: DEFAULT func EQ term  */
#line 253 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),NULL),(yyvsp[0].y_nod)));}
#line 2038 "syn.tab.c"
    break;

  case 86: /* aninstruction: DEFAULT RIGHT func EQ term  */
#line 255 "syn.y"
                                                     {(yyval.y_nod)=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),mknod(PARAM,NULL,NULL)),(yyvsp[0].y_nod)));}
#line 2045 "syn.tab.c"
    break;

  case 87: /* step: %empty  */
#line 258 "syn.y"
                        {(yyval.y_nod)=(Node *) NULL;}
#line 2051 "syn.tab.c"
    break;

  case 88: /* step: STEP term  */
#line 259 "syn.y"
                                        {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2057 "syn.tab.c"
    break;

  case 89: /* prntexpr: term  */
#line 261 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2063 "syn.tab.c"
    break;

  case 90: /* prntexpr: String  */
#line 262 "syn.y"
                                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2069 "syn.tab.c"
    break;

  case 91: /* prntlist: prntexpr  */
#line 264 "syn.y"
                                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2075 "syn.tab.c"
    break;

  case 92: /* prntlist: prntexpr ',' prntlist  */
#line 265 "syn.y"
                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2081 "syn.tab.c"
    break;

  case 93: /* alglist: Alg2  */
#line 267 "syn.y"
                                                                {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2087 "syn.tab.c"
    break;

  case 94: /* alglist: Alg2 ',' alglist  */
#line 268 "syn.y"
                                                        {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2093 "syn.tab.c"
    break;

  case 95: /* Alg2: Alg  */
#line 270 "syn.y"
                                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2099 "syn.tab.c"
    break;

  case 96: /* Alg2: '(' alglist ')'  */
#line 271 "syn.y"
                                                                {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2105 "syn.tab.c"
    break;

  case 97: /* sortlist: Sort  */
#line 273 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2111 "syn.tab.c"
    break;

  case 98: /* sortlist: Sort ',' sortlist  */
#line 274 "syn.y"
                                                                {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2117 "syn.tab.c"
    break;

  case 99: /* vsortlist: sortlist  */
#line 276 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2123 "syn.tab.c"
    break;

  case 100: /* vsortlist: sortlist VARPAR  */
#line 277 "syn.y"
                                                                        {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2129 "syn.tab.c"
    break;

  case 101: /* func: Func  */
#line 279 "syn.y"
                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2135 "syn.tab.c"
    break;

  case 102: /* func: La1  */
#line 280 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2141 "syn.tab.c"
    break;

  case 103: /* func: La2  */
#line 281 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2147 "syn.tab.c"
    break;

  case 104: /* func: La3  */
#line 282 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2153 "syn.tab.c"
    break;

  case 105: /* func: La4  */
#line 283 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2159 "syn.tab.c"
    break;

  case 106: /* func: La5  */
#line 284 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2165 "syn.tab.c"
    break;

  case 107: /* func: Ra  */
#line 285 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2171 "syn.tab.c"
    break;

  case 108: /* func: Ru  */
#line 286 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2177 "syn.tab.c"
    break;

  case 109: /* func: Bra  */
#line 287 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2183 "syn.tab.c"
    break;

  case 110: /* func: Bra1  */
#line 288 "syn.y"
                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2189 "syn.tab.c"
    break;

  case 111: /* funclist: func  */
#line 290 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2195 "syn.tab.c"
    break;

  case 112: /* funclist: func ',' funclist  */
#line 291 "syn.y"
                                                        {(yyval.y_nod) = mknod(Functs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2201 "syn.tab.c"
    break;

  case 113: /* term: Term  */
#line 293 "syn.y"
                                                                        {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); merkt sich keine Abhaengigkeiten und funktioniert nicht in Bloecken */ 
														}
#line 2208 "syn.tab.c"
    break;

  case 114: /* term: LAST  */
#line 295 "syn.y"
                                                                                        {(yyval.y_nod) = (Node *) lastterm;}
#line 2214 "syn.tab.c"
    break;

  case 115: /* term: Const  */
#line 296 "syn.y"
                                                                                        {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2220 "syn.tab.c"
    break;

  case 116: /* term: Const Bra1 termlist Bra2  */
#line 297 "syn.y"
                                                   {nphilf=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),nphilf), nphilf);}
#line 2227 "syn.tab.c"
    break;

  case 117: /* term: Var  */
#line 299 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2233 "syn.tab.c"
    break;

  case 118: /* term: '(' term ')'  */
#line 300 "syn.y"
                                                    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2239 "syn.tab.c"
    break;

  case 119: /* term: term Ru  */
#line 301 "syn.y"
                                                                      {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2245 "syn.tab.c"
    break;

  case 120: /* term: Func term  */
#line 302 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2251 "syn.tab.c"
    break;

  case 121: /* term: La1 term  */
#line 303 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2257 "syn.tab.c"
    break;

  case 122: /* term: La2 term  */
#line 304 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2263 "syn.tab.c"
    break;

  case 123: /* term: La3 term  */
#line 305 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2269 "syn.tab.c"
    break;

  case 124: /* term: La4 term  */
#line 306 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2275 "syn.tab.c"
    break;

  case 125: /* term: La5 term  */
#line 307 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2281 "syn.tab.c"
    break;

  case 126: /* term: Bra termlist Bra  */
#line 308 "syn.y"
                                                  {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2287 "syn.tab.c"
    break;

  case 127: /* term: Bra1 termlist Bra2  */
#line 309 "syn.y"
                                                {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2293 "syn.tab.c"
    break;

  case 128: /* term: Func '(' termlist ')'  */
#line 310 "syn.y"
                                                        {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2299 "syn.tab.c"
    break;

  case 129: /* term: term La1 term  */
#line 311 "syn.y"
                                                    {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2306 "syn.tab.c"
    break;

  case 130: /* term: term La2 term  */
#line 313 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2313 "syn.tab.c"
    break;

  case 131: /* term: term La3 term  */
#line 315 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2320 "syn.tab.c"
    break;

  case 132: /* term: term La4 term  */
#line 317 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2327 "syn.tab.c"
    break;

  case 133: /* term: term La5 term  */
#line 319 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2334 "syn.tab.c"
    break;

  case 134: /* term: term Ra term  */
#line 321 "syn.y"
                                                                {nphilf=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),nphilf),nphilf);}
#line 2341 "syn.tab.c"
    break;

  case 135: /* termlist: term  */
#line 324 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2347 "syn.tab.c"
    break;

  case 136: /* termlist: term ',' termlist  */
#line 325 "syn.y"
                                                        {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2353 "syn.tab.c"
    break;

  case 137: /* formula: term EQ term  */
#line 327 "syn.y"
                                        {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2359 "syn.tab.c"
    break;

  case 138: /* vinstr: %empty  */
#line 329 "syn.y"
                                                                {(yyval.y_nod) = NULL;}
#line 2365 "syn.tab.c"
    break;

  case 139: /* vinstr: DO instruction  */
#line 330 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2371 "syn.tab.c"
    break;

  case 140: /* cformula: formula vinstr  */
#line 332 "syn.y"
                                                                        {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2378 "syn.tab.c"
    break;

  case 141: /* cformula: IF condition formula vinstr  */
#line 334 "syn.y"
                                               {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2385 "syn.tab.c"
    break;

  case 142: /* formlist: cformula  */
#line 337 "syn.y"
                                                                {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL dient zum Einhaengen weiterer Formeln !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. wegen SPEC real : A+B=C;a=3 */
															}
#line 2393 "syn.tab.c"
    break;


#line 2397 "syn.tab.c"

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

#line 341 "syn.y"

