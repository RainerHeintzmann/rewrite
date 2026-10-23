/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_SYN_TAB_H_INCLUDED
# define YY_YY_SYN_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CST = 258,
    VAR = 259,
    SORT = 260,
    FUNC = 261,
    ALG = 262,
    SPEC = 263,
    ADDSPEC = 264,
    REWR = 265,
    PRT = 266,
    GRAPH = 267,
    PFEIL = 268,
    TERM = 269,
    NUM = 270,
    ATT = 271,
    IS = 272,
    EQ = 273,
    INFO = 274,
    LA1 = 275,
    LA2 = 276,
    LA3 = 277,
    LA4 = 278,
    LA5 = 279,
    LOCAL = 280,
    RU = 281,
    RA = 282,
    KOMMU = 283,
    LB = 284,
    IN = 285,
    NIN = 286,
    PARAM = 287,
    FOR = 288,
    TO = 289,
    STEP = 290,
    DO = 291,
    DBG = 292,
    LAST = 293,
    BRA = 294,
    OTHER = 295,
    DATA = 296,
    OUT = 297,
    INC = 298,
    EXE = 299,
    VARPAR = 300,
    SYS = 301,
    IF = 302,
    ELSE = 303,
    WHILE = 304,
    PRTNUM = 305,
    LIFT = 306,
    QUIT = 307,
    RETURN = 308,
    Id = 309,
    String = 310,
    Sort = 311,
    Alg = 312,
    Term = 313,
    La1 = 314,
    La2 = 315,
    La3 = 316,
    La4 = 317,
    La5 = 318,
    Ru = 319,
    Ra = 320,
    Func = 321,
    Const = 322,
    Var = 323,
    Bra = 324,
    Bra1 = 325,
    Bra2 = 326,
    Terms = 327,
    Form = 328,
    Sorts = 329,
    Functs = 330,
    Forms = 331,
    Algs = 332,
    Cond2 = 333,
    Cond = 334
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 48 "syn.y" /* yacc.c:1909  */

	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	

#line 142 "syn.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYN_TAB_H_INCLUDED  */
