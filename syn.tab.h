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
    CST = 258,                     /* CST  */
    VAR = 259,                     /* VAR  */
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
    NUM = 270,                     /* NUM  */
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
    KOMMU = 283,                   /* KOMMU  */
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
    Id = 316,                      /* Id  */
    String = 317,                  /* String  */
    Sort = 318,                    /* Sort  */
    Alg = 319,                     /* Alg  */
    Term = 320,                    /* Term  */
    La1 = 321,                     /* La1  */
    La2 = 322,                     /* La2  */
    La3 = 323,                     /* La3  */
    La4 = 324,                     /* La4  */
    La5 = 325,                     /* La5  */
    Ru = 326,                      /* Ru  */
    Ra = 327,                      /* Ra  */
    Func = 328,                    /* Func  */
    Const = 329,                   /* Const  */
    Var = 330,                     /* Var  */
    Bra = 331,                     /* Bra  */
    Bra1 = 332,                    /* Bra1  */
    Bra2 = 333,                    /* Bra2  */
    Terms = 334,                   /* Terms  */
    Form = 335,                    /* Form  */
    Sorts = 336,                   /* Sorts  */
    Functs = 337,                  /* Functs  */
    Forms = 338,                   /* Forms  */
    Algs = 339,                    /* Algs  */
    Cond2 = 340,                   /* Cond2  */
    Cond = 341                     /* Cond  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 52 "syn.y"

	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	

#line 158 "syn.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SYN_TAB_H_INCLUDED  */
