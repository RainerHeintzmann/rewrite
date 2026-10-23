/* A Bison parser, made from syn.y, by GNU bison 1.75.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef BISON_SYN_TAB_H
# define BISON_SYN_TAB_H

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
#define CST 258
#define VAR 259
#define SORT 260
#define FUNC 261
#define ALG 262
#define SPEC 263
#define ADDSPEC 264
#define REWR 265
#define PRT 266
#define GRAPH 267
#define PFEIL 268
#define TERM 269
#define NUM 270
#define ATT 271
#define IS 272
#define EQ 273
#define INFO 274
#define LA1 275
#define LA2 276
#define LA3 277
#define LA4 278
#define LA5 279
#define LOCAL 280
#define RU 281
#define RA 282
#define KOMMU 283
#define LB 284
#define IN 285
#define NIN 286
#define PARAM 287
#define FOR 288
#define TO 289
#define STEP 290
#define DO 291
#define DBG 292
#define LAST 293
#define BRA 294
#define OTHER 295
#define DATA 296
#define OUT 297
#define INC 298
#define EXE 299
#define VARPAR 300
#define SYS 301
#define IF 302
#define ELSE 303
#define WHILE 304
#define PRTNUM 305
#define LIFT 306
#define QUIT 307
#define RETURN 308
#define Id 309
#define String 310
#define Sort 311
#define Alg 312
#define Term 313
#define La1 314
#define La2 315
#define La3 316
#define La4 317
#define La5 318
#define Ru 319
#define Ra 320
#define Func 321
#define Const 322
#define Var 323
#define Bra 324
#define Bra1 325
#define Bra2 326
#define Terms 327
#define Form 328
#define Sorts 329
#define Functs 330
#define Forms 331
#define Algs 332
#define Cond2 333
#define Cond 334




#ifndef YYSTYPE
#line 42 "syn.y"
typedef union {
	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	} yystype;
/* Line 1281 of /usr/share/bison/yacc.c.  */
#line 205 "syn.tab.h"
# define YYSTYPE yystype
#endif

extern YYSTYPE yylval;


#endif /* not BISON_SYN_TAB_H */

