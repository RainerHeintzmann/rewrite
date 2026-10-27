/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SYN_TAB_H_INCLUDED
# define YY_YY_SYN_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SYM = 258,                     /* SYM  */
    PAT = 259,                     /* PAT  */
    SORT = 260,                    /* SORT  */
    FUNC = 261,                    /* FUNC  */
    ALG = 262,                     /* ALG  */
    SPEC = 263,                    /* SPEC  */
    ADDSPEC = 264,                 /* ADDSPEC  */
    REWR = 265,                    /* REWR  */
    PRT = 266,                     /* PRT  */
    GRAPH = 267,                   /* GRAPH  */
    PFEIL = 268,                   /* PFEIL  */
    TERM = 269,                    /* TERM  */
    NUMPAT = 270,                  /* NUMPAT  */
    ATT = 271,                     /* ATT  */
    IS = 272,                      /* IS  */
    EQ = 273,                      /* EQ  */
    INFO = 274,                    /* INFO  */
    LA1 = 275,                     /* LA1  */
    LA2 = 276,                     /* LA2  */
    LA3 = 277,                     /* LA3  */
    LA4 = 278,                     /* LA4  */
    LA5 = 279,                     /* LA5  */
    LOCAL = 280,                   /* LOCAL  */
    RU = 281,                      /* RU  */
    RA = 282,                      /* RA  */
    COMMU = 283,                   /* COMMU  */
    LB = 284,                      /* LB  */
    IN = 285,                      /* IN  */
    NIN = 286,                     /* NIN  */
    PARAM = 287,                   /* PARAM  */
    FOR = 288,                     /* FOR  */
    TO = 289,                      /* TO  */
    STEP = 290,                    /* STEP  */
    DO = 291,                      /* DO  */
    DBG = 292,                     /* DBG  */
    LAST = 293,                    /* LAST  */
    BRA = 294,                     /* BRA  */
    OTHER = 295,                   /* OTHER  */
    DATA = 296,                    /* DATA  */
    OUT = 297,                     /* OUT  */
    INC = 298,                     /* INC  */
    EXE = 299,                     /* EXE  */
    VARPAR = 300,                  /* VARPAR  */
    SYS = 301,                     /* SYS  */
    IF = 302,                      /* IF  */
    ELSE = 303,                    /* ELSE  */
    WHILE = 304,                   /* WHILE  */
    PRTNUM = 305,                  /* PRTNUM  */
    LIFT = 306,                    /* LIFT  */
    QUIT = 307,                    /* QUIT  */
    RETURN = 308,                  /* RETURN  */
    OPT = 309,                     /* OPT  */
    COMM = 310,                    /* COMM  */
    DEFAULT = 311,                 /* DEFAULT  */
    RIGHT = 312,                   /* RIGHT  */
    SUBSORT = 313,                 /* SUBSORT  */
    INTNUM = 314,                  /* INTNUM  */
    STEPS = 315,                   /* STEPS  */
    MAXSTEPS = 316,                /* MAXSTEPS  */
    MAXDEPTH = 317,                /* MAXDEPTH  */
    SYMBOLIC = 318,                /* SYMBOLIC  */
    HOLD = 319,                    /* HOLD  */
    RULES = 320,                   /* RULES  */
    SHOW = 321,                    /* SHOW  */
    REALNUM = 322,                 /* REALNUM  */
    TYPEOF = 323,                  /* TYPEOF  */
    HELP = 324,                    /* HELP  */
    ALIAS = 325,                   /* ALIAS  */
    AUTOSYM = 326,                 /* AUTOSYM  */
    Id = 327,                      /* Id  */
    String = 328,                  /* String  */
    Sort = 329,                    /* Sort  */
    Alg = 330,                     /* Alg  */
    Term = 331,                    /* Term  */
    La1 = 332,                     /* La1  */
    La2 = 333,                     /* La2  */
    La3 = 334,                     /* La3  */
    La4 = 335,                     /* La4  */
    La5 = 336,                     /* La5  */
    Ru = 337,                      /* Ru  */
    Ra = 338,                      /* Ra  */
    Func = 339,                    /* Func  */
    Const = 340,                   /* Const  */
    Var = 341,                     /* Var  */
    Bra = 342,                     /* Bra  */
    Bra1 = 343,                    /* Bra1  */
    Bra2 = 344,                    /* Bra2  */
    Terms = 345,                   /* Terms  */
    Form = 346,                    /* Form  */
    Sorts = 347,                   /* Sorts  */
    Functs = 348,                  /* Functs  */
    Forms = 349,                   /* Forms  */
    Algs = 350,                    /* Algs  */
    Cond2 = 351,                   /* Cond2  */
    Cond = 352                     /* Cond  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 55 "syn.y"

	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	

#line 169 "syn.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SYN_TAB_H_INCLUDED  */
