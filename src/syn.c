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
  YYSYMBOL_AUTOSYM = 71,                   /* AUTOSYM  */
  YYSYMBOL_PRETTY = 72,                    /* PRETTY  */
  YYSYMBOL_PLOT = 73,                      /* PLOT  */
  YYSYMBOL_Id = 74,                        /* Id  */
  YYSYMBOL_String = 75,                    /* String  */
  YYSYMBOL_Sort = 76,                      /* Sort  */
  YYSYMBOL_Alg = 77,                       /* Alg  */
  YYSYMBOL_Term = 78,                      /* Term  */
  YYSYMBOL_La1 = 79,                       /* La1  */
  YYSYMBOL_La2 = 80,                       /* La2  */
  YYSYMBOL_La3 = 81,                       /* La3  */
  YYSYMBOL_La4 = 82,                       /* La4  */
  YYSYMBOL_La5 = 83,                       /* La5  */
  YYSYMBOL_Ru = 84,                        /* Ru  */
  YYSYMBOL_Ra = 85,                        /* Ra  */
  YYSYMBOL_Func = 86,                      /* Func  */
  YYSYMBOL_Const = 87,                     /* Const  */
  YYSYMBOL_Var = 88,                       /* Var  */
  YYSYMBOL_Bra = 89,                       /* Bra  */
  YYSYMBOL_Bra1 = 90,                      /* Bra1  */
  YYSYMBOL_Bra2 = 91,                      /* Bra2  */
  YYSYMBOL_Terms = 92,                     /* Terms  */
  YYSYMBOL_Form = 93,                      /* Form  */
  YYSYMBOL_Sorts = 94,                     /* Sorts  */
  YYSYMBOL_Functs = 95,                    /* Functs  */
  YYSYMBOL_Forms = 96,                     /* Forms  */
  YYSYMBOL_Algs = 97,                      /* Algs  */
  YYSYMBOL_Cond2 = 98,                     /* Cond2  */
  YYSYMBOL_Cond = 99,                      /* Cond  */
  YYSYMBOL_100_n_ = 100,                   /* '\n'  */
  YYSYMBOL_101_ = 101,                     /* ':'  */
  YYSYMBOL_102_ = 102,                     /* ','  */
  YYSYMBOL_103_ = 103,                     /* '('  */
  YYSYMBOL_104_ = 104,                     /* ')'  */
  YYSYMBOL_105_ = 105,                     /* ';'  */
  YYSYMBOL_106_ = 106,                     /* '{'  */
  YYSYMBOL_107_ = 107,                     /* '}'  */
  YYSYMBOL_YYACCEPT = 108,                 /* $accept  */
  YYSYMBOL_prog = 109,                     /* prog  */
  YYSYMBOL_line = 110,                     /* line  */
  YYSYMBOL_definition = 111,               /* definition  */
  YYSYMBOL_idlist = 112,                   /* idlist  */
  YYSYMBOL_att = 113,                      /* att  */
  YYSYMBOL_114_1 = 114,                    /* $@1  */
  YYSYMBOL_namedId = 115,                  /* namedId  */
  YYSYMBOL_PRECEDENCE = 116,               /* PRECEDENCE  */
  YYSYMBOL_condition = 117,                /* condition  */
  YYSYMBOL_condfunc = 118,                 /* condfunc  */
  YYSYMBOL_instructions = 119,             /* instructions  */
  YYSYMBOL_tinstructions = 120,            /* tinstructions  */
  YYSYMBOL_oinstructions = 121,            /* oinstructions  */
  YYSYMBOL_d_list = 122,                   /* d_list  */
  YYSYMBOL_instruction = 123,              /* instruction  */
  YYSYMBOL_124_2 = 124,                    /* $@2  */
  YYSYMBOL_aninstruction = 125,            /* aninstruction  */
  YYSYMBOL_step = 126,                     /* step  */
  YYSYMBOL_prntexpr = 127,                 /* prntexpr  */
  YYSYMBOL_prntlist = 128,                 /* prntlist  */
  YYSYMBOL_alglist = 129,                  /* alglist  */
  YYSYMBOL_Alg2 = 130,                     /* Alg2  */
  YYSYMBOL_sortlist = 131,                 /* sortlist  */
  YYSYMBOL_vsortlist = 132,                /* vsortlist  */
  YYSYMBOL_func = 133,                     /* func  */
  YYSYMBOL_funclist = 134,                 /* funclist  */
  YYSYMBOL_term = 135,                     /* term  */
  YYSYMBOL_termlist = 136,                 /* termlist  */
  YYSYMBOL_formula = 137,                  /* formula  */
  YYSYMBOL_vinstr = 138,                   /* vinstr  */
  YYSYMBOL_cformula = 139,                 /* cformula  */
  YYSYMBOL_formlist = 140                  /* formlist  */
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
#define YYFINAL  172
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   770

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  173
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  361

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   354


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
     100,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     103,   104,     2,     2,   102,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   101,   105,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   106,     2,   107,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,    87,    89,    97,   100,   104,   110,   121,
     122,   123,   125,   127,   129,   131,   133,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   146,   147,   149,
     150,   158,   159,   170,   172,   174,   176,   176,   179,   180,
     181,   182,   183,   184,   185,   188,   189,   190,   191,   192,
     193,   194,   195,   197,   198,   200,   201,   202,   203,   205,
     206,   208,   209,   211,   216,   217,   219,   220,   221,   221,
     227,   230,   232,   234,   244,   245,   246,   247,   248,   250,
     251,   252,   253,   254,   255,   261,   262,   263,   264,   267,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   298,   301,   302,   304,   305,
     307,   308,   310,   311,   313,   314,   316,   317,   319,   320,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     333,   334,   336,   338,   339,   340,   342,   343,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   360,   362,   364,   366,   368,   371,   372,   374,   376,
     377,   379,   381,   384
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
  "REALNUM", "TYPEOF", "HELP", "ALIAS", "AUTOSYM", "PRETTY", "PLOT", "Id",
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

#define YYPACT_NINF (-319)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     448,   680,   680,   680,   680,   680,   -50,   -36,   606,   523,
     680,   680,   -22,   680,   606,     0,  -319,    15,   389,   -49,
      18,    21,   389,    23,   -12,   -12,    32,     5,  -319,   606,
     680,   389,   123,    19,    34,    35,    26,    27,    43,   389,
      52,   486,    44,    54,    55,    30,    57,   -15,  -319,   126,
     606,   606,   606,   606,   606,   624,     7,  -319,   606,   606,
     606,  -319,   344,  -319,  -319,    47,    48,  -319,    53,  -319,
     465,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,  -319,    56,    66,  -319,
      68,  -319,    77,  -319,    84,    85,    51,  -319,    99,   192,
    -319,    89,    93,   122,  -319,    -2,  -319,   125,    96,  -319,
    -319,  -319,  -319,   136,  -319,    97,   111,   113,   606,   448,
     116,   448,  -319,   606,   465,  -319,   137,  -319,   389,   223,
     140,   236,   178,  -319,  -319,   243,   247,  -319,  -319,  -319,
     606,   606,   606,   606,   606,   624,   606,   606,  -319,   465,
     193,   260,  -319,  -319,  -319,   606,   606,   141,    20,   245,
     -26,     1,   -35,   606,  -319,   606,   606,   287,   180,   188,
     166,   448,  -319,  -319,  -319,   448,   523,   606,   606,   606,
     606,   606,  -319,   606,   204,   680,   207,   209,   505,   569,
     -48,   210,   211,   187,   606,   212,   209,  -319,   606,   606,
     606,   253,   263,   -12,  -319,   217,   389,   296,   606,   239,
     242,  -319,   248,   250,  -319,   265,   465,   237,   606,   465,
     -10,   238,   465,   231,   606,  -319,  -319,  -319,  -319,   249,
     261,  -319,  -319,    20,   245,   -26,     1,   -35,   -35,  -319,
    -319,  -319,   241,   300,   349,   -12,  -319,   587,  -319,   262,
      42,   329,  -319,  -319,  -319,   -48,  -319,  -319,  -319,   299,
      81,   209,   361,   271,   272,   274,  -319,   448,  -319,   345,
    -319,   606,   465,   364,  -319,  -319,  -319,   326,  -319,   359,
    -319,  -319,  -319,  -319,   448,   209,  -319,   325,   606,   304,
     -48,   606,   448,  -319,   307,   606,   407,   352,  -319,  -319,
    -319,  -319,   318,   465,   355,  -319,   -48,  -319,  -319,    41,
     329,  -319,  -319,   465,  -319,   362,   153,   369,   419,   606,
    -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,   419,
    -319,   335,   606,   410,   419,   652,  -319,   357,  -319,   374,
     465,   448,  -319,   218,   -48,  -319,  -319,  -319,  -319,  -319,
     680,  -319,  -319,   251,  -319,   360,   372,   251,   448,  -319,
    -319
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   143,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,     0,
     110,   112,   113,     0,     0,     0,    93,    95,   104,     0,
       0,     0,     0,     0,    97,    99,   101,   147,   119,   142,
       0,     0,     0,     0,     0,     0,   144,   146,     0,     0,
       0,    68,    74,     2,    67,     0,    59,    66,   120,    79,
     118,    38,    42,    43,    44,   131,   132,   133,   134,   135,
     137,   136,   130,    39,    40,   138,   139,     0,    29,    41,
       0,    26,     0,    27,     0,     0,   147,   142,   144,     0,
      81,     0,     0,     0,    77,     0,    91,     0,     0,    83,
      84,    82,    76,     0,    75,     0,     0,     0,     0,    74,
      53,    74,    80,     0,   107,   109,   140,   111,     0,     0,
       0,     0,     0,    92,    94,     0,    14,    10,    21,    20,
     131,   132,   133,   134,   135,   130,   138,   139,    19,    18,
       0,     0,    96,    98,   100,     0,     0,     0,   152,   153,
     154,   155,   156,     0,   151,     0,     0,   166,     0,     0,
       0,    74,     1,     3,     4,    74,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,     0,     0,
       0,     0,    71,     0,    70,     0,     0,     0,     0,     0,
       0,   102,     0,     0,    22,     0,    88,     0,     0,    85,
       0,     0,    87,     0,     0,   157,   158,   149,    63,     0,
      61,    60,   121,   160,   161,   162,   163,   164,   165,    17,
      30,     9,   126,   128,     0,     0,   124,     0,    23,   122,
       0,   169,   173,    24,    25,     0,    78,    28,    16,     0,
       0,     0,     0,     0,     0,     0,    58,    74,    54,     0,
     141,     0,   114,    12,    15,   103,    13,   105,   148,     0,
     159,   145,   167,    69,    74,     0,   129,     0,     0,     0,
       0,     0,    74,   171,     0,     0,     0,     0,    55,    56,
      57,    72,     0,   115,     0,   106,     0,    62,   127,    45,
     169,   125,   123,   168,   170,     0,   116,     0,    31,     0,
      11,    86,    46,    47,    48,    49,    50,    52,    51,    31,
     172,     0,     0,     0,    31,     0,     6,     0,     5,     0,
     117,    74,     8,     0,     0,    36,    32,    90,     7,    73,
       0,    33,    34,     0,    35,    64,     0,     0,    74,    65,
      37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -319,  -319,   387,  -318,    10,  -292,  -319,    -4,  -319,   -20,
    -319,  -139,   182,  -319,   120,  -115,  -319,  -319,  -319,  -319,
      -1,  -160,  -319,   195,  -185,    -8,   276,    -7,   -57,   196,
     173,  -319,   316
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    62,    63,    64,    87,   336,   353,    88,   329,   119,
     120,    65,   229,   230,   356,    66,   171,    67,   333,    68,
      69,   289,   249,   243,   244,    89,   127,    70,   168,   251,
     293,   252,   253
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      92,    99,   169,   155,   202,   121,   204,   105,   100,   104,
     108,   262,    90,    91,   113,    93,   194,   115,   116,   117,
     101,   102,   124,   126,   129,   165,   109,    94,   248,   246,
     256,   136,   228,   148,   149,   355,   231,   338,   110,   355,
     125,    95,   342,   158,   159,   160,   161,   162,   164,   182,
     183,   167,   167,   170,   103,   255,   180,   181,   182,   183,
     291,   322,   323,   324,   325,   326,   205,   327,   328,   177,
     178,   179,   180,   181,   182,   183,   296,   177,   178,   179,
     180,   181,   182,   183,   181,   182,   183,   106,   156,   107,
     169,   118,   224,   111,   227,   130,   112,   166,   114,   217,
     178,   179,   180,   181,   182,   183,   221,   122,   123,   223,
     131,   201,   132,   133,   134,   295,   167,   153,   135,   150,
     207,   177,   178,   179,   180,   181,   182,   183,   137,   151,
     312,   152,   154,   158,   159,   160,   161,   162,   164,   167,
     167,   263,   264,   265,   157,   228,   321,   174,   216,   167,
     219,   218,   301,   175,   156,   176,   220,   184,   222,   167,
     177,   178,   179,   180,   181,   182,   183,   282,   185,   186,
     233,   234,   235,   236,   237,   232,   238,   314,   187,    16,
     128,   250,   250,   268,   352,   188,   189,   260,   332,   166,
     191,   167,   167,   167,   192,   240,   193,   196,   126,   195,
     198,   272,    75,    76,    77,    78,    79,    80,    81,    82,
     197,   279,    85,    86,   199,    96,   200,   167,   203,    97,
      50,    51,    52,    53,    54,   288,   349,    55,    98,    57,
      58,    59,   177,   178,   179,   180,   181,   182,   183,   206,
     170,   208,   209,   360,    60,   177,   178,   179,   180,   181,
     182,   183,   210,   211,     1,     2,     3,     4,     5,     6,
       7,   212,   337,   213,   303,    10,    11,    12,   214,   225,
     227,   177,   178,   179,   180,   181,   182,   183,   215,   226,
     239,   250,   350,   241,   313,   242,   257,   258,   316,   259,
      17,    18,    71,   190,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    33,
      34,   267,   167,   261,   271,   273,   274,    39,    40,    41,
      42,   269,   281,   275,   276,   340,   179,   180,   181,   182,
     183,   346,   177,   178,   179,   180,   181,   182,   183,   351,
     277,   278,   280,   285,   172,   286,   354,     1,     2,     3,
       4,     5,     6,     7,     8,     9,   283,   266,    10,    11,
      12,   284,   287,    13,   290,   292,   177,   178,   179,   180,
     181,   182,   183,   294,   297,   298,   299,    14,   300,   302,
     304,    15,    16,    17,    18,    19,    20,    21,    22,   224,
      23,    24,   305,    25,    26,    27,    28,    29,    30,    31,
      32,   309,    33,    34,    35,    36,    37,    38,   311,   315,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
     317,   319,    49,    50,    51,    52,    53,    54,   318,   320,
      55,    56,    57,    58,    59,   335,   331,   339,   177,   178,
     179,   180,   181,   182,   183,   334,   341,    60,   348,   173,
      61,     1,     2,     3,     4,     5,     6,     7,     8,     9,
     306,   347,    10,    11,    12,   357,   307,    13,    75,    76,
      77,    78,    79,    80,    81,    82,   358,   359,    85,    86,
     308,    14,   270,   330,   310,    15,    16,    17,    18,    19,
      20,    21,    22,     0,    23,    24,     0,    25,    26,    27,
      28,    29,    30,    31,    32,   254,    33,    34,    35,    36,
      37,    38,     0,     0,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    16,     0,    49,    50,    51,    52,
      53,    54,     0,     0,    55,    56,    57,    58,    59,     0,
       0,     0,     0,    16,   177,   178,   179,   180,   181,   182,
     183,    60,   245,     0,    61,     0,     0,     0,     0,     0,
      96,    16,   138,   139,    97,   140,   141,   142,   143,   144,
      80,    81,   145,    98,    57,   146,   147,     0,     0,    96,
       0,     0,   246,    97,    50,    51,    52,    53,    54,    60,
       0,    55,    98,    57,    58,    59,     0,    96,    48,     0,
       0,    97,    50,    51,    52,    53,    54,    16,   247,    55,
      98,    57,    58,    59,     0,     0,   245,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,    16,     0,     0,    97,    50,    51,
      52,    53,    54,     0,     0,    55,    98,    57,    58,    59,
       0,    96,    16,     0,   246,    97,    50,    51,    52,    53,
      54,     0,    60,    55,    98,    57,    58,    59,     0,     0,
      96,     0,     0,     0,    97,    50,    51,    52,    53,    54,
     247,     0,    55,    98,    57,    58,    59,     0,    96,     0,
       0,     0,    97,    50,    51,    52,    53,    54,     0,    60,
      55,    98,    57,    58,    59,   343,     0,   344,     0,     0,
       0,     0,     0,     0,     0,     0,    71,   163,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,   345,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86
};

static const yytype_int16 yycheck[] =
{
       4,     8,    59,    18,   119,    25,   121,    14,     9,    13,
      18,   196,     2,     3,    22,     5,    18,    29,    30,    31,
      10,    11,    29,    31,    32,    18,    75,    77,   188,    77,
     190,    39,   171,    41,    41,   353,   175,   329,    87,   357,
      30,    77,   334,    50,    51,    52,    53,    54,    55,    84,
      85,    58,    59,    60,    76,   103,    82,    83,    84,    85,
      18,    20,    21,    22,    23,    24,   123,    26,    27,    79,
      80,    81,    82,    83,    84,    85,   261,    79,    80,    81,
      82,    83,    84,    85,    83,    84,    85,    87,   103,    74,
     147,   103,   102,    75,   104,    76,    75,    90,    75,   156,
      80,    81,    82,    83,    84,    85,   163,    75,   103,   166,
      76,   118,    77,    87,    87,    34,   123,    87,    75,    75,
     128,    79,    80,    81,    82,    83,    84,    85,    76,    75,
     290,    76,    75,   140,   141,   142,   143,   144,   145,   146,
     147,   198,   199,   200,    18,   284,   306,   100,   155,   156,
     157,    10,   267,   105,   103,   102,   163,   101,   165,   166,
      79,    80,    81,    82,    83,    84,    85,   224,   102,   101,
     177,   178,   179,   180,   181,   176,   183,   292,   101,    38,
      57,   188,   189,   203,   344,   101,   101,   194,    35,    90,
     101,   198,   199,   200,   101,   185,    74,   101,   206,    74,
     103,   208,    79,    80,    81,    82,    83,    84,    85,    86,
      74,   218,    89,    90,   103,    74,   103,   224,   102,    78,
      79,    80,    81,    82,    83,   245,   341,    86,    87,    88,
      89,    90,    79,    80,    81,    82,    83,    84,    85,   102,
     247,    18,   102,   358,   103,    79,    80,    81,    82,    83,
      84,    85,    16,    75,     3,     4,     5,     6,     7,     8,
       9,    18,   319,    16,   271,    14,    15,    16,    75,    89,
     104,    79,    80,    81,    82,    83,    84,    85,    18,    91,
      76,   288,    64,    76,   291,    76,    76,    76,   295,   102,
      39,    40,    74,   101,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    58,
      59,    48,   319,   101,    18,    76,    74,    66,    67,    68,
      69,   104,    91,    75,    74,   332,    81,    82,    83,    84,
      85,   335,    79,    80,    81,    82,    83,    84,    85,   343,
      75,   104,   104,   102,     0,    45,   350,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   107,   104,    14,    15,
      16,   100,    13,    19,   102,    36,    79,    80,    81,    82,
      83,    84,    85,    74,    13,   104,   104,    33,   104,    34,
      16,    37,    38,    39,    40,    41,    42,    43,    44,   102,
      46,    47,    66,    49,    50,    51,    52,    53,    54,    55,
      56,    76,    58,    59,    60,    61,    62,    63,   104,   102,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      13,   103,    78,    79,    80,    81,    82,    83,    76,    74,
      86,    87,    88,    89,    90,    16,    74,   102,    79,    80,
      81,    82,    83,    84,    85,    76,    36,   103,    74,    62,
     106,     3,     4,     5,     6,     7,     8,     9,    10,    11,
     101,   104,    14,    15,    16,   105,   284,    19,    79,    80,
      81,    82,    83,    84,    85,    86,   104,   357,    89,    90,
     285,    33,   206,   310,   288,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,   189,    58,    59,    60,    61,
      62,    63,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    38,    -1,    78,    79,    80,    81,
      82,    83,    -1,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    38,    79,    80,    81,    82,    83,    84,
      85,   103,    47,    -1,   106,    -1,    -1,    -1,    -1,    -1,
      74,    38,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    -1,    -1,    74,
      -1,    -1,    77,    78,    79,    80,    81,    82,    83,   103,
      -1,    86,    87,    88,    89,    90,    -1,    74,    75,    -1,
      -1,    78,    79,    80,    81,    82,    83,    38,   103,    86,
      87,    88,    89,    90,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    38,    -1,    -1,    78,    79,    80,
      81,    82,    83,    -1,    -1,    86,    87,    88,    89,    90,
      -1,    74,    38,    -1,    77,    78,    79,    80,    81,    82,
      83,    -1,   103,    86,    87,    88,    89,    90,    -1,    -1,
      74,    -1,    -1,    -1,    78,    79,    80,    81,    82,    83,
     103,    -1,    86,    87,    88,    89,    90,    -1,    74,    -1,
      -1,    -1,    78,    79,    80,    81,    82,    83,    -1,   103,
      86,    87,    88,    89,    90,    63,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,   103,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,   103,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    15,    16,    19,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    46,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    58,    59,    60,    61,    62,    63,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    78,
      79,    80,    81,    82,    83,    86,    87,    88,    89,    90,
     103,   106,   109,   110,   111,   119,   123,   125,   127,   128,
     135,    74,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,   112,   115,   133,
     112,   112,   115,   112,    77,    77,    74,    78,    87,   135,
     128,   112,   112,    76,   115,   135,    87,    74,   133,    75,
      87,    75,    75,   133,    75,    29,    30,    31,   103,   117,
     118,   117,    75,   103,   135,   112,   133,   134,    57,   133,
      76,    76,    77,    87,    87,    75,   133,    76,    76,    77,
      79,    80,    81,    82,    83,    86,    89,    90,   133,   135,
      75,    75,    76,    87,    75,    18,   103,    18,   135,   135,
     135,   135,   135,   103,   135,    18,    90,   135,   136,   136,
     135,   124,     0,   110,   100,   105,   102,    79,    80,    81,
      82,    83,    84,    85,   101,   102,   101,   101,   101,   101,
     101,   101,   101,    74,    18,    74,   101,    74,   103,   103,
     103,   135,   123,   102,   123,   136,   102,   133,    18,   102,
      16,    75,    18,    16,    75,    18,   135,   136,    10,   135,
     135,   136,   135,   136,   102,    89,    91,   104,   119,   120,
     121,   119,   128,   135,   135,   135,   135,   135,   135,    76,
     112,    76,    76,   131,   132,    47,    77,   103,   129,   130,
     135,   137,   139,   140,   140,   103,   129,    76,    76,   102,
     135,   101,   132,   136,   136,   136,   104,    48,   117,   104,
     134,    18,   135,    76,    74,    75,    74,    75,   104,   135,
     104,    91,   136,   107,   100,   102,    45,    13,   117,   129,
     102,    18,    36,   138,    74,    34,   132,    13,   104,   104,
     104,   123,    34,   135,    16,    66,   101,   120,   131,    76,
     137,   104,   129,   135,   123,   102,   135,    13,    76,   103,
      74,   129,    20,    21,    22,    23,    24,    26,    27,   116,
     138,    74,    35,   126,    76,    16,   113,   136,   113,   102,
     135,    36,   113,    63,    65,   103,   115,   104,    74,   123,
      64,   115,   129,   114,   115,   111,   122,   105,   104,   122,
     123
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   108,   109,   109,   110,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   114,   113,   115,   115,
     115,   115,   115,   115,   115,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   117,   118,   118,   118,   118,   119,
     119,   120,   120,   121,   122,   122,   123,   123,   124,   123,
     123,   123,   123,   123,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   132,   132,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     134,   134,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   136,   136,   137,   138,
     138,   139,   139,   140
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     8,     7,     9,     8,     4,
       2,     6,     4,     4,     2,     4,     4,     4,     2,     2,
       2,     2,     3,     4,     4,     4,     2,     2,     4,     1,
       3,     0,     2,     3,     3,     4,     0,     6,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     4,     4,     4,     3,     1,
       3,     1,     3,     1,     1,     3,     1,     1,     0,     4,
       3,     3,     5,     9,     0,     2,     2,     2,     4,     1,
       2,     2,     2,     2,     2,     3,     6,     3,     3,     3,
       8,     2,     2,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     3,     4,     1,     4,     5,     2,     1,     2,
       1,     2,     1,     1,     4,     5,     0,     2,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     4,     1,     1,     4,     3,
       2,     2,     2,     2,     2,     2,     2,     3,     3,     4,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     0,
       2,     2,     4,     1
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
#line 1582 "syn.tab.c"
    break;

  case 5: /* definition: FUNC namedId ':' vsortlist PFEIL Sort PRECEDENCE att  */
#line 97 "syn.y"
                                                                       {	(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) (yyvsp[-6].y_nod),(yyvsp[-1].y_int),(Node *) (yyvsp[-2].y_sym),(yyvsp[-4].y_nod),FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fn,mknod(PARAM,(Node *) (yyvsp[-6].y_nod),(yyvsp[0].y_nod))),NULL)));}
#line 1590 "syn.tab.c"
    break;

  case 6: /* definition: OTHER func ':' vsortlist PFEIL Sort att  */
#line 100 "syn.y"
                                                                  { (yyval.y_nod)=mknod(FUNC,(Node *) other_fn,
                                              mknod(PARAM,(Node *) (yyvsp[-5].y_nod),
                                              mknod(PARAM,(yyvsp[-3].y_nod),
                                              mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(yyvsp[0].y_nod)))));}
#line 1599 "syn.tab.c"
    break;

  case 7: /* definition: ATT Sort Id ',' Id ',' Id ',' Id  */
#line 104 "syn.y"
                                                           { (yyval.y_nod)=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) (yyvsp[-7].y_sym),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-6].y_sym))),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-4].y_sym))),
                                              mknod(PARAM,(Node *) give_ufn(name((yyvsp[-2].y_sym))),
                                              (Node *) give_ufn(name((yyvsp[0].y_sym))))))));	}
#line 1610 "syn.tab.c"
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
#line 1626 "syn.tab.c"
    break;

  case 9: /* definition: PAT idlist ':' Sort  */
#line 121 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1632 "syn.tab.c"
    break;

  case 10: /* definition: REALNUM Sort  */
#line 122 "syn.y"
                                                                                 {(yyval.y_nod)=mknod(FUNC,(Node *) set_numbertype,(Node *) ((yyvsp[0].y_sym))); /* sets numbertype for mknum */}
#line 1638 "syn.tab.c"
    break;

  case 11: /* definition: SUBSORT Sort ',' Sort ATT Id  */
#line 123 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort */
										      mknod(PARAM,(Node *) (yyvsp[-4].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufn(name((yyvsp[0].y_sym))))));}
#line 1645 "syn.tab.c"
    break;

  case 12: /* definition: SUBSORT Sort ',' Sort  */
#line 125 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort of a sort without values */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),mknod(PARAM,(Node *) (yyvsp[0].y_sym),NULL)));}
#line 1652 "syn.tab.c"
    break;

  case 13: /* definition: SHOW func ATT Id  */
#line 127 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) show_def,      /* 2026: print function */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) give_pfn(name((yyvsp[0].y_sym)))));}
#line 1659 "syn.tab.c"
    break;

  case 14: /* definition: SHOW func  */
#line 129 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) show_def,      /* 2026: the usual printing again */
										      mknod(PARAM,(Node *) (yyvsp[0].y_nod),NULL));}
#line 1666 "syn.tab.c"
    break;

  case 15: /* definition: INTNUM Sort ATT Id  */
#line 131 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) intnum_def,    /* 2026: sort of integers */
										      mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) give_ufn(name((yyvsp[0].y_sym)))));}
#line 1673 "syn.tab.c"
    break;

  case 16: /* definition: NUMPAT idlist ':' Sort  */
#line 133 "syn.y"
                                                                 { /* pattern variables for numbers */
									                (yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Var,(Node *) (yyvsp[0].y_sym),NULL,TRUE);}
#line 1680 "syn.tab.c"
    break;

  case 17: /* definition: SYM idlist ':' Sort  */
#line 135 "syn.y"
                                                                 {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Const,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1686 "syn.tab.c"
    break;

  case 18: /* definition: TYPEOF term  */
#line 136 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) typeof_fn,(yyvsp[0].y_nod));}
#line 1692 "syn.tab.c"
    break;

  case 19: /* definition: TYPEOF func  */
#line 137 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) typeof_func,(Node *) (yyvsp[0].y_nod));}
#line 1698 "syn.tab.c"
    break;

  case 20: /* definition: TYPEOF Alg  */
#line 138 "syn.y"
                                                         {typeof_alg((yyvsp[0].y_sym)); (yyval.y_nod)=NULL;}
#line 1704 "syn.tab.c"
    break;

  case 21: /* definition: TYPEOF Sort  */
#line 139 "syn.y"
                                                         {typeof_sort((yyvsp[0].y_sym)); (yyval.y_nod)=NULL;}
#line 1710 "syn.tab.c"
    break;

  case 22: /* definition: HELP String String  */
#line 140 "syn.y"
                                                         {(yyval.y_nod)=mknod(FUNC,(Node *) help_def,mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 1716 "syn.tab.c"
    break;

  case 23: /* definition: SPEC Alg ':' alglist  */
#line 141 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_nod)));}
#line 1722 "syn.tab.c"
    break;

  case 24: /* definition: SPEC Alg ':' formlist  */
#line 142 "syn.y"
                                                         {(yyval.y_nod) = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));	}
#line 1728 "syn.tab.c"
    break;

  case 25: /* definition: ADDSPEC Alg ':' formlist  */
#line 143 "syn.y"
                                                   {(yyval.y_nod) = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(yyvsp[0].y_nod)));}
#line 1734 "syn.tab.c"
    break;

  case 26: /* definition: SORT idlist  */
#line 144 "syn.y"
                                                                             {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Sort,NULL,NULL,FALSE);}
#line 1740 "syn.tab.c"
    break;

  case 27: /* definition: ALG idlist  */
#line 146 "syn.y"
                                                     {(yyval.y_nod)=DECLARE((yyvsp[0].y_nod),Alg,NULL,NULL,FALSE);}
#line 1746 "syn.tab.c"
    break;

  case 28: /* definition: TERM idlist ':' Sort  */
#line 147 "syn.y"
                                                   {(yyval.y_nod)=DECLARE((yyvsp[-2].y_nod),Term,(Node *) (yyvsp[0].y_sym),NULL,FALSE);}
#line 1752 "syn.tab.c"
    break;

  case 29: /* idlist: namedId  */
#line 149 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1758 "syn.tab.c"
    break;

  case 30: /* idlist: namedId ',' idlist  */
#line 150 "syn.y"
                                                        {(yyval.y_nod) = mknod(Id,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1764 "syn.tab.c"
    break;

  case 31: /* att: %empty  */
#line 158 "syn.y"
                                        { (yyval.y_nod) = NULL;}
#line 1770 "syn.tab.c"
    break;

  case 32: /* att: ATT namedId  */
#line 159 "syn.y"
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
#line 1786 "syn.tab.c"
    break;

  case 33: /* att: ATT SYMBOLIC namedId  */
#line 170 "syn.y"
                                                        { /* 2026: symbolic C function (symfn.c): gets terms */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 0); }
#line 1793 "syn.tab.c"
    break;

  case 34: /* att: ATT RULES alglist  */
#line 172 "syn.y"
                                                { /* 2026: function defined by a rule list: f(..) is REWR f(..) : alglist */
			                  (yyval.y_nod) = mknod(ATT,(Node *) rules_sfn(),mknod(PARAM,(yyvsp[0].y_nod),NULL)); }
#line 1800 "syn.tab.c"
    break;

  case 35: /* att: ATT SYMBOLIC HOLD namedId  */
#line 174 "syn.y"
                                                        { /* 2026: plus arguments unevaluated (matchq) */
			                  (yyval.y_nod) = sym_att((yyvsp[0].y_nod), 1); }
#line 1807 "syn.tab.c"
    break;

  case 36: /* $@1: %empty  */
#line 176 "syn.y"
                                          {block_begin();no_protect();}
#line 1813 "syn.tab.c"
    break;

  case 37: /* att: ATT '(' $@1 d_list ')' instruction  */
#line 177 "syn.y"
                                                                                        {protect();block_end();(yyval.y_nod) =mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 1819 "syn.tab.c"
    break;

  case 38: /* namedId: Id  */
#line 179 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1825 "syn.tab.c"
    break;

  case 39: /* namedId: Const  */
#line 180 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1831 "syn.tab.c"
    break;

  case 40: /* namedId: Var  */
#line 181 "syn.y"
                         { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1837 "syn.tab.c"
    break;

  case 41: /* namedId: func  */
#line 182 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_nod);}
#line 1843 "syn.tab.c"
    break;

  case 42: /* namedId: Sort  */
#line 183 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1849 "syn.tab.c"
    break;

  case 43: /* namedId: Alg  */
#line 184 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1855 "syn.tab.c"
    break;

  case 44: /* namedId: Term  */
#line 185 "syn.y"
                       { (yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 1861 "syn.tab.c"
    break;

  case 45: /* PRECEDENCE: %empty  */
#line 188 "syn.y"
                                                                {(yyval.y_int) = Func;}
#line 1867 "syn.tab.c"
    break;

  case 46: /* PRECEDENCE: LA1  */
#line 189 "syn.y"
                                                                        {(yyval.y_int) = La1;	/* Left-associative */}
#line 1873 "syn.tab.c"
    break;

  case 47: /* PRECEDENCE: LA2  */
#line 190 "syn.y"
                                                                        {(yyval.y_int) = La2;	/* Left-associative */}
#line 1879 "syn.tab.c"
    break;

  case 48: /* PRECEDENCE: LA3  */
#line 191 "syn.y"
                                                                        {(yyval.y_int) = La3;	/* Left-associative */}
#line 1885 "syn.tab.c"
    break;

  case 49: /* PRECEDENCE: LA4  */
#line 192 "syn.y"
                                                                        {(yyval.y_int) = La4;	/* Left-associative */}
#line 1891 "syn.tab.c"
    break;

  case 50: /* PRECEDENCE: LA5  */
#line 193 "syn.y"
                                                                        {(yyval.y_int) = La5;	/* Left-associative */}
#line 1897 "syn.tab.c"
    break;

  case 51: /* PRECEDENCE: RA  */
#line 194 "syn.y"
                                                                        {(yyval.y_int) = Ra;  	/* Right-associative */}
#line 1903 "syn.tab.c"
    break;

  case 52: /* PRECEDENCE: RU  */
#line 195 "syn.y"
                                                                        {(yyval.y_int) = Ru;	  /* Right unary */}
#line 1909 "syn.tab.c"
    break;

  case 53: /* condition: condfunc  */
#line 197 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 1915 "syn.tab.c"
    break;

  case 54: /* condition: condfunc ',' condition  */
#line 198 "syn.y"
                                                        {(yyval.y_nod) = mknod(Cond,(Node *) and_cond,mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod)));}
#line 1921 "syn.tab.c"
    break;

  case 55: /* condfunc: LB '(' termlist ')'  */
#line 200 "syn.y"
                              {(yyval.y_nod) = mknod(Cond,(Node *) lower_between,(yyvsp[-1].y_nod));}
#line 1927 "syn.tab.c"
    break;

  case 56: /* condfunc: IN '(' termlist ')'  */
#line 201 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) in_tree,(yyvsp[-1].y_nod));}
#line 1933 "syn.tab.c"
    break;

  case 57: /* condfunc: NIN '(' termlist ')'  */
#line 202 "syn.y"
                                                {(yyval.y_nod) = mknod(Cond,(Node *) not_in_tree,(yyvsp[-1].y_nod));}
#line 1939 "syn.tab.c"
    break;

  case 58: /* condfunc: '(' term ')'  */
#line 203 "syn.y"
                                                                        {(yyval.y_nod) = mknod(Cond,(Node *) isnt_zero,(yyvsp[-1].y_nod));}
#line 1945 "syn.tab.c"
    break;

  case 59: /* instructions: instruction  */
#line 205 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1951 "syn.tab.c"
    break;

  case 60: /* instructions: instruction ';' instructions  */
#line 206 "syn.y"
                                                                                       {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1957 "syn.tab.c"
    break;

  case 61: /* tinstructions: oinstructions  */
#line 208 "syn.y"
                                {if ((yyvsp[0].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[0].y_nod),NULL); else (yyval.y_nod)=NULL;}
#line 1963 "syn.tab.c"
    break;

  case 62: /* tinstructions: oinstructions '\n' tinstructions  */
#line 209 "syn.y"
                                                                                                                {if ((yyvsp[-2].y_nod)) (yyval.y_nod) = mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1969 "syn.tab.c"
    break;

  case 63: /* oinstructions: instructions  */
#line 211 "syn.y"
                                                {if((yyvsp[0].y_nod)) (yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); else (yyval.y_nod)=(yyvsp[0].y_nod);}
#line 1975 "syn.tab.c"
    break;

  case 64: /* d_list: definition  */
#line 216 "syn.y"
                                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[0].y_nod)),NULL);}
#line 1981 "syn.tab.c"
    break;

  case 65: /* d_list: definition ';' d_list  */
#line 217 "syn.y"
                                                 {(yyval.y_nod) = mknod(PARAM,in_block_def((yyvsp[-2].y_nod)),(yyvsp[0].y_nod));}
#line 1987 "syn.tab.c"
    break;

  case 66: /* instruction: aninstruction  */
#line 219 "syn.y"
                                {(yyval.y_nod) = in_block_instruct((yyvsp[0].y_nod)); /* Check local variables ! */ }
#line 1993 "syn.tab.c"
    break;

  case 67: /* instruction: definition  */
#line 220 "syn.y"
                                                                        {(yyval.y_nod) = in_block_def((yyvsp[0].y_nod));}
#line 1999 "syn.tab.c"
    break;

  case 68: /* $@2: %empty  */
#line 221 "syn.y"
                                                                                                        {block_begin();no_protect();}
#line 2005 "syn.tab.c"
    break;

  case 69: /* instruction: '{' $@2 tinstructions '}'  */
#line 222 "syn.y"
                                                                        {protect();block_end();
																(yyval.y_nod)=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,(yyvsp[-1].y_nod)),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
#line 2015 "syn.tab.c"
    break;

  case 70: /* instruction: WHILE condition instruction  */
#line 227 "syn.y"
                                                        {Node * memo,* rtw=in_block_instruct(memo=mknod(FUNC,(Node *) while_fn,mknod(PARAM,(yyvsp[-1].y_nod),NULL /* then becomes $3 */)));
																		WHILE_BODY(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 2022 "syn.tab.c"
    break;

  case 71: /* instruction: IF condition instruction  */
#line 230 "syn.y"
                                                        {Node * memo,* rtw=in_block_instruct(memo=mknod(FUNC,(Node *) if_fn,mknod(PARAM,(yyvsp[-1].y_nod),mknod(PARAM,NULL,NULL))));
																		IF_THEN(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 2029 "syn.tab.c"
    break;

  case 72: /* instruction: IF condition instruction ELSE instruction  */
#line 232 "syn.y"
                                                                        {Node * memo,* rtw = in_block_instruct(memo=mknod(FUNC,(Node *) if_fn,mknod(PARAM,(yyvsp[-3].y_nod),mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(memo) = (yyvsp[-2].y_nod);IF_ELSE(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 2036 "syn.tab.c"
    break;

  case 73: /* instruction: FOR term EQ term TO term step DO instruction  */
#line 235 "syn.y"
                                                                                                                {Node * memo,* rtw = in_block_instruct(memo=mknod(FUNC,(Node *) for_loop,
																mknod(PARAM,
																	mknod(PARAM,(yyvsp[-5].y_nod),(yyvsp[-3].y_nod)),
																	mknod(PARAM,
																		mknod(PARAM,(yyvsp[-2].y_nod),(Node *) ((yyvsp[-7].y_nod))),
																		NULL /* $9 */) )));	
														FOR_BODY(memo) = (yyvsp[0].y_nod);(yyval.y_nod)=rtw;}
#line 2048 "syn.tab.c"
    break;

  case 74: /* aninstruction: %empty  */
#line 244 "syn.y"
                                        {(yyval.y_nod)=NULL;}
#line 2054 "syn.tab.c"
    break;

  case 75: /* aninstruction: SYS String  */
#line 245 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) system_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2060 "syn.tab.c"
    break;

  case 76: /* aninstruction: INC String  */
#line 246 "syn.y"
                                                                        {/* include(name($2));$$=NULL;*/ (yyval.y_nod)=mknod(FUNC,(Node *) include_fn,(Node *) ((yyvsp[0].y_sym))); }
#line 2066 "syn.tab.c"
    break;

  case 77: /* aninstruction: INFO namedId  */
#line 247 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) info_fn,(Node *) ((yyvsp[0].y_nod))); }
#line 2072 "syn.tab.c"
    break;

  case 78: /* aninstruction: REWR term ':' alglist  */
#line 248 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_fn,mknod(PARAM,(Node *) ((yyvsp[-2].y_nod)),(Node *) ((yyvsp[0].y_nod))));
														 rtypes(lastterm)=get_type((yyvsp[-2].y_nod));}
#line 2079 "syn.tab.c"
    break;

  case 79: /* aninstruction: prntlist  */
#line 250 "syn.y"
                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)));}
#line 2085 "syn.tab.c"
    break;

  case 80: /* aninstruction: PRTNUM String  */
#line 251 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) prt_num,(Node *) ((yyvsp[0].y_sym)));}
#line 2091 "syn.tab.c"
    break;

  case 81: /* aninstruction: PRT prntlist  */
#line 252 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) sequence,(yyvsp[0].y_nod)); /* without \n */ }
#line 2097 "syn.tab.c"
    break;

  case 82: /* aninstruction: OUT String  */
#line 253 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changeout,(Node *) ((yyvsp[0].y_sym)));}
#line 2103 "syn.tab.c"
    break;

  case 83: /* aninstruction: DATA String  */
#line 254 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) changedata,(Node *) ((yyvsp[0].y_sym)));}
#line 2109 "syn.tab.c"
    break;

  case 84: /* aninstruction: DATA Const  */
#line 255 "syn.y"
                                                                        {if (rtypes((yyvsp[0].y_sym)) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               (yyval.y_nod)=NULL;}
                             else
                               (yyval.y_nod)=mknod(FUNC,(Node *) readdata,(Node *) ((yyvsp[0].y_sym)));
                            }
#line 2120 "syn.tab.c"
    break;

  case 85: /* aninstruction: Term EQ term  */
#line 261 "syn.y"
                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod)));}
#line 2126 "syn.tab.c"
    break;

  case 86: /* aninstruction: Term EQ REWR term ':' alglist  */
#line 262 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) rewrite_ass_fn,mknod(PARAM,(Node *) (yyvsp[-5].y_sym),mknod(PARAM,(Node *) (yyvsp[-2].y_nod),(Node *) (yyvsp[0].y_nod))));}
#line 2132 "syn.tab.c"
    break;

  case 87: /* aninstruction: Const EQ term  */
#line 263 "syn.y"
                                                        { (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ((yyvsp[-2].y_sym)),(Node *) ((yyvsp[0].y_nod))));}
#line 2138 "syn.tab.c"
    break;

  case 88: /* aninstruction: Id EQ term  */
#line 264 "syn.y"
                                                        { Symbol * s = auto_symbol((yyvsp[-2].y_sym));	/* 2026: AUTOSYM */
							  if (! s) YYERROR;
							  (yyval.y_nod)=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) s,(Node *) ((yyvsp[0].y_nod))));}
#line 2146 "syn.tab.c"
    break;

  case 89: /* aninstruction: EXE func Id  */
#line 267 "syn.y"
                                                        {(yyval.y_nod) = NULL;
																exe_always((yyvsp[-1].y_nod))=TRUE;
																hasval((yyvsp[-1].y_nod)) = TRUE;
																value((yyvsp[-1].y_nod))  = (Node *) give_ufn(name((yyvsp[0].y_sym)));
 													}
#line 2156 "syn.tab.c"
    break;

  case 90: /* aninstruction: LIFT '(' termlist ')' TO '(' termlist ')'  */
#line 272 "syn.y"
                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) (yyvsp[-1].y_nod),(Node *) (yyvsp[-5].y_nod)));}
#line 2162 "syn.tab.c"
    break;

  case 91: /* aninstruction: DBG Const  */
#line 273 "syn.y"
                                                {(yyval.y_nod)=mknod(FUNC,(Node *) setdebug,(Node *) ((yyvsp[0].y_sym)));}
#line 2168 "syn.tab.c"
    break;

  case 92: /* aninstruction: MAXSTEPS Const  */
#line 274 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) maxsteps_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2174 "syn.tab.c"
    break;

  case 93: /* aninstruction: MAXSTEPS  */
#line 275 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) maxsteps_fn,NULL);}
#line 2180 "syn.tab.c"
    break;

  case 94: /* aninstruction: MAXDEPTH Const  */
#line 276 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) maxdepth_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2186 "syn.tab.c"
    break;

  case 95: /* aninstruction: MAXDEPTH  */
#line 277 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) maxdepth_fn,NULL);}
#line 2192 "syn.tab.c"
    break;

  case 96: /* aninstruction: AUTOSYM Sort  */
#line 278 "syn.y"
                                                        {autosym_fn((Node *) (yyvsp[0].y_sym)); (yyval.y_nod)=NULL;}
#line 2198 "syn.tab.c"
    break;

  case 97: /* aninstruction: AUTOSYM  */
#line 279 "syn.y"
                                                        {autosym_fn(NULL); (yyval.y_nod)=NULL;}
#line 2204 "syn.tab.c"
    break;

  case 98: /* aninstruction: PRETTY Const  */
#line 280 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) pretty_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2210 "syn.tab.c"
    break;

  case 99: /* aninstruction: PRETTY  */
#line 281 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) pretty_fn,NULL);}
#line 2216 "syn.tab.c"
    break;

  case 100: /* aninstruction: PLOT String  */
#line 282 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) plot_set_fn,(Node *) ((yyvsp[0].y_sym)));}
#line 2222 "syn.tab.c"
    break;

  case 101: /* aninstruction: PLOT  */
#line 283 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) plot_set_fn,NULL);}
#line 2228 "syn.tab.c"
    break;

  case 102: /* aninstruction: STEPS Alg String  */
#line 284 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) steps_fn,mknod(PARAM,(Node *) (yyvsp[-1].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2234 "syn.tab.c"
    break;

  case 103: /* aninstruction: SYMBOLIC String EQ String  */
#line 285 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fn,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2240 "syn.tab.c"
    break;

  case 104: /* aninstruction: SYMBOLIC  */
#line 286 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) role_fn,NULL);  /* delete roles */}
#line 2246 "syn.tab.c"
    break;

  case 105: /* aninstruction: ALIAS String EQ String  */
#line 287 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) alias_fn,mknod(PARAM,(Node *) (yyvsp[-2].y_sym),(Node *) (yyvsp[0].y_sym)));}
#line 2252 "syn.tab.c"
    break;

  case 106: /* aninstruction: ALIAS String EQ String SHOW  */
#line 288 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) alias_show_fn,mknod(PARAM,(Node *) (yyvsp[-3].y_sym),(Node *) (yyvsp[-1].y_sym)));}
#line 2258 "syn.tab.c"
    break;

  case 107: /* aninstruction: RETURN term  */
#line 289 "syn.y"
                                                                                                {(yyval.y_nod)=mknod(FUNC,(Node *) return_fn,(yyvsp[0].y_nod));}
#line 2264 "syn.tab.c"
    break;

  case 108: /* aninstruction: QUIT  */
#line 290 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) quit_fn,NULL);}
#line 2270 "syn.tab.c"
    break;

  case 109: /* aninstruction: OPT idlist  */
#line 291 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fn,(yyvsp[0].y_nod));}
#line 2276 "syn.tab.c"
    break;

  case 110: /* aninstruction: OPT  */
#line 292 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) opt_fn,NULL);   /* delete */}
#line 2282 "syn.tab.c"
    break;

  case 111: /* aninstruction: COMM funclist  */
#line 293 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fn,(yyvsp[0].y_nod));}
#line 2288 "syn.tab.c"
    break;

  case 112: /* aninstruction: COMM  */
#line 294 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) comm_fn,NULL);  /* delete */}
#line 2294 "syn.tab.c"
    break;

  case 113: /* aninstruction: DEFAULT  */
#line 295 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,NULL); /* delete */}
#line 2300 "syn.tab.c"
    break;

  case 114: /* aninstruction: DEFAULT func EQ term  */
#line 296 "syn.y"
                                                    {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),NULL),(yyvsp[0].y_nod)));}
#line 2307 "syn.tab.c"
    break;

  case 115: /* aninstruction: DEFAULT RIGHT func EQ term  */
#line 298 "syn.y"
                                                     {(yyval.y_nod)=mknod(FUNC,(Node *) default_fn,
			                                  mknod(PARAM,mknod(PARAM,(yyvsp[-2].y_nod),mknod(PARAM,NULL,NULL)),(yyvsp[0].y_nod)));}
#line 2314 "syn.tab.c"
    break;

  case 116: /* step: %empty  */
#line 301 "syn.y"
                        {(yyval.y_nod)=(Node *) NULL;}
#line 2320 "syn.tab.c"
    break;

  case 117: /* step: STEP term  */
#line 302 "syn.y"
                                        {(yyval.y_nod)=(yyvsp[0].y_nod);}
#line 2326 "syn.tab.c"
    break;

  case 118: /* prntexpr: term  */
#line 304 "syn.y"
                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printterm,(yyvsp[0].y_nod)); rtypes(lastterm)=get_type((yyvsp[0].y_nod));}
#line 2332 "syn.tab.c"
    break;

  case 119: /* prntexpr: String  */
#line 305 "syn.y"
                                                                                        {(yyval.y_nod)=mknod(FUNC,(Node *) printstring,(Node *) ((yyvsp[0].y_sym)));}
#line 2338 "syn.tab.c"
    break;

  case 120: /* prntlist: prntexpr  */
#line 307 "syn.y"
                                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[0].y_nod),NULL);}
#line 2344 "syn.tab.c"
    break;

  case 121: /* prntlist: prntexpr ',' prntlist  */
#line 308 "syn.y"
                                                {(yyval.y_nod)=mknod(PARAM,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2350 "syn.tab.c"
    break;

  case 122: /* alglist: Alg2  */
#line 310 "syn.y"
                                                                {(yyval.y_nod) = mknod(Algs,((yyvsp[0].y_nod)),NULL);}
#line 2356 "syn.tab.c"
    break;

  case 123: /* alglist: Alg2 ',' alglist  */
#line 311 "syn.y"
                                                        {(yyval.y_nod) = mknod(Algs,((yyvsp[-2].y_nod)),((yyvsp[0].y_nod)));}
#line 2362 "syn.tab.c"
    break;

  case 124: /* Alg2: Alg  */
#line 313 "syn.y"
                                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2368 "syn.tab.c"
    break;

  case 125: /* Alg2: '(' alglist ')'  */
#line 314 "syn.y"
                                                                {(yyval.y_nod) = mknod(Alg,((yyvsp[-1].y_nod)),NULL);}
#line 2374 "syn.tab.c"
    break;

  case 126: /* sortlist: Sort  */
#line 316 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2380 "syn.tab.c"
    break;

  case 127: /* sortlist: Sort ',' sortlist  */
#line 317 "syn.y"
                                                                {(yyval.y_nod) = mknod(Sorts,(Node *) ((yyvsp[-2].y_sym)),(yyvsp[0].y_nod));}
#line 2386 "syn.tab.c"
    break;

  case 128: /* vsortlist: sortlist  */
#line 319 "syn.y"
                                                        {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2392 "syn.tab.c"
    break;

  case 129: /* vsortlist: sortlist VARPAR  */
#line 320 "syn.y"
                                                                        {(yyval.y_nod) = mknod(VARPAR,(Node *) ((yyvsp[-1].y_nod)),NULL);}
#line 2398 "syn.tab.c"
    break;

  case 130: /* func: Func  */
#line 322 "syn.y"
                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2404 "syn.tab.c"
    break;

  case 131: /* func: La1  */
#line 323 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2410 "syn.tab.c"
    break;

  case 132: /* func: La2  */
#line 324 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2416 "syn.tab.c"
    break;

  case 133: /* func: La3  */
#line 325 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2422 "syn.tab.c"
    break;

  case 134: /* func: La4  */
#line 326 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2428 "syn.tab.c"
    break;

  case 135: /* func: La5  */
#line 327 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2434 "syn.tab.c"
    break;

  case 136: /* func: Ra  */
#line 328 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2440 "syn.tab.c"
    break;

  case 137: /* func: Ru  */
#line 329 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2446 "syn.tab.c"
    break;

  case 138: /* func: Bra  */
#line 330 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2452 "syn.tab.c"
    break;

  case 139: /* func: Bra1  */
#line 331 "syn.y"
                                                                {(yyval.y_nod) = (Node *) ((yyvsp[0].y_sym));}
#line 2458 "syn.tab.c"
    break;

  case 140: /* funclist: func  */
#line 333 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2464 "syn.tab.c"
    break;

  case 141: /* funclist: func ',' funclist  */
#line 334 "syn.y"
                                                        {(yyval.y_nod) = mknod(Functs,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2470 "syn.tab.c"
    break;

  case 142: /* term: Term  */
#line 336 "syn.y"
                                                                        {	(yyval.y_nod) = (Node *) (yyvsp[0].y_sym); /* tcopy(); does not remember dependencies and does not work in blocks */ 
														}
#line 2477 "syn.tab.c"
    break;

  case 143: /* term: LAST  */
#line 338 "syn.y"
                                                                                        {(yyval.y_nod) = (Node *) lastterm;}
#line 2483 "syn.tab.c"
    break;

  case 144: /* term: Const  */
#line 339 "syn.y"
                                                                                        {(yyval.y_nod) = mknod(Const,(Node *) ((yyvsp[0].y_sym)),NULL);}
#line 2489 "syn.tab.c"
    break;

  case 145: /* term: Const Bra1 termlist Bra2  */
#line 340 "syn.y"
                                                   {np_aux=mknod(Terms,mknod(Const,(Node *) ((yyvsp[-3].y_sym)),NULL),(yyvsp[-1].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),np_aux), np_aux);}
#line 2496 "syn.tab.c"
    break;

  case 146: /* term: Var  */
#line 342 "syn.y"
                                                                        {(yyval.y_nod) = (Node *) (yyvsp[0].y_sym);}
#line 2502 "syn.tab.c"
    break;

  case 147: /* term: Id  */
#line 343 "syn.y"
                                                        { Symbol * s = auto_symbol((yyvsp[0].y_sym));	/* 2026: AUTOSYM */
							  if (! s) YYERROR;
							  (yyval.y_nod) = mknod(Const,(Node *) s,NULL);}
#line 2510 "syn.tab.c"
    break;

  case 148: /* term: Id '(' termlist ')'  */
#line 346 "syn.y"
                                                        { unknown_function((yyvsp[-3].y_sym)); YYERROR; }
#line 2516 "syn.tab.c"
    break;

  case 149: /* term: '(' term ')'  */
#line 347 "syn.y"
                                                    {(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2522 "syn.tab.c"
    break;

  case 150: /* term: term Ru  */
#line 348 "syn.y"
                                                                      {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[0].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2528 "syn.tab.c"
    break;

  case 151: /* term: Func term  */
#line 349 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2534 "syn.tab.c"
    break;

  case 152: /* term: La1 term  */
#line 350 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2540 "syn.tab.c"
    break;

  case 153: /* term: La2 term  */
#line 351 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2546 "syn.tab.c"
    break;

  case 154: /* term: La3 term  */
#line 352 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2552 "syn.tab.c"
    break;

  case 155: /* term: La4 term  */
#line 353 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2558 "syn.tab.c"
    break;

  case 156: /* term: La5 term  */
#line 354 "syn.y"
                                                                    {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),((yyvsp[0].y_nod))), ((yyvsp[0].y_nod)) ); }
#line 2564 "syn.tab.c"
    break;

  case 157: /* term: Bra termlist Bra  */
#line 355 "syn.y"
                                                  {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2570 "syn.tab.c"
    break;

  case 158: /* term: Bra1 termlist Bra2  */
#line 356 "syn.y"
                                                {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-2].y_sym)),((yyvsp[-1].y_nod))), ((yyvsp[-1].y_nod)) ); }
#line 2576 "syn.tab.c"
    break;

  case 159: /* term: Func '(' termlist ')'  */
#line 357 "syn.y"
                                                        {(yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-3].y_sym)),((yyvsp[-1].y_nod))),((yyvsp[-1].y_nod)));}
#line 2582 "syn.tab.c"
    break;

  case 160: /* term: term La1 term  */
#line 358 "syn.y"
                                                    {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2589 "syn.tab.c"
    break;

  case 161: /* term: term La2 term  */
#line 360 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2596 "syn.tab.c"
    break;

  case 162: /* term: term La3 term  */
#line 362 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2603 "syn.tab.c"
    break;

  case 163: /* term: term La4 term  */
#line 364 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2610 "syn.tab.c"
    break;

  case 164: /* term: term La5 term  */
#line 366 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2617 "syn.tab.c"
    break;

  case 165: /* term: term Ra term  */
#line 368 "syn.y"
                                                                {np_aux=mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));
														 (yyval.y_nod) = mknod(Func,(Node *) getsymbol(((yyvsp[-1].y_sym)),np_aux),np_aux);}
#line 2624 "syn.tab.c"
    break;

  case 166: /* termlist: term  */
#line 371 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2630 "syn.tab.c"
    break;

  case 167: /* termlist: term ',' termlist  */
#line 372 "syn.y"
                                                        {(yyval.y_nod) = mknod(Terms,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2636 "syn.tab.c"
    break;

  case 168: /* formula: term EQ term  */
#line 374 "syn.y"
                                        {(yyval.y_nod) = mknod(Form,(yyvsp[-2].y_nod),(yyvsp[0].y_nod));}
#line 2642 "syn.tab.c"
    break;

  case 169: /* vinstr: %empty  */
#line 376 "syn.y"
                                                                {(yyval.y_nod) = NULL;}
#line 2648 "syn.tab.c"
    break;

  case 170: /* vinstr: DO instruction  */
#line 377 "syn.y"
                                                                {(yyval.y_nod) = (yyvsp[0].y_nod);}
#line 2654 "syn.tab.c"
    break;

  case 171: /* cformula: formula vinstr  */
#line 379 "syn.y"
                                                                        {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2661 "syn.tab.c"
    break;

  case 172: /* cformula: IF condition formula vinstr  */
#line 381 "syn.y"
                                               {(((yyvsp[-1].y_nod))->r)=mknod(PARAM,mknod(Cond2,(yyvsp[-2].y_nod),((yyvsp[-1].y_nod))->r),
																									 (yyvsp[0].y_nod));(yyval.y_nod) = (yyvsp[-1].y_nod);}
#line 2668 "syn.tab.c"
    break;

  case 173: /* formlist: cformula  */
#line 384 "syn.y"
                                                                {(yyval.y_nod) = mknod(Forms,(yyvsp[0].y_nod),NULL); /* NULL serves for hooking in further formulas !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. because of SPEC real : A+B=C;a=3 */
															}
#line 2676 "syn.tab.c"
    break;


#line 2680 "syn.tab.c"

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

#line 388 "syn.y"


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
