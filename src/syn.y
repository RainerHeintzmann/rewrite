/*
 *	syn.y V1.00
 *	Copyright (c)  Rainer Heintzmann (1992)
 *	Basic framework : Prof. Axel T. Schreiner
 *
 *	Variables
 */

%{

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

%}

%union	{
	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	}

%token			CST VAR SORT FUNC ALG SPEC ADDSPEC REWR PRT GRAPH PFEIL TERM NUM ATT IS EQ INFO
%token			LA1 LA2 LA3 LA4 LA5 LOCAL RU RA COMMU LB IN NIN PARAM FOR TO STEP DO DBG LAST
%token			BRA OTHER DATA OUT INC EXE VARPAR SYS IF ELSE WHILE PRTNUM LIFT QUIT RETURN
%token			OPT COMM DEFAULT RIGHT SUBSORT INTNUM STEPS SYMBOLIC HOLD RULES SHOW
%token	<y_sym>	Id String
%token	<y_sym>	Sort Alg Term
%token	<y_sym>	La1 La2 La3 La4 La5 Ru Ra Func Const Var Bra Bra1 Bra2
%token			Terms Form Sorts Functs Forms Algs Cond2 Cond
%type	<y_int>	PRECEDENCE
%type	<y_nod>	vinstr definition instruction aninstruction instructions prntexpr  tinstructions oinstructions
%type	<y_nod> idlist l_thing l_list sortlist vsortlist funclist formlist termlist alglist Alg2 prntlist
%type	<y_nod>	term func step att namedId d_list
%type	<y_nod> formula cformula condition condfunc

%left	La1 
%left	La2 
%left	La3 
%left	La4 
%left	La5
%right	Ra 
%right	Ru 
%left	Func 
%%

prog		: line
				| prog line;

line		: instructions '\n' {Node * temp;
														if ($1) { temp = mknod(FUNC,(Node *) sequence,$1);
															is_running();
															CALLFUNCT(temp);
															is_not_running();
															delete(temp);}
														};
															
definition	: FUNC namedId ':' vsortlist PFEIL Sort	PRECEDENCE att {	$$=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) $2,$7,(Node *) $6,$4,FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fn,mknod(PARAM,(Node *) $2,$8)),NULL)));}
			| OTHER func ':' vsortlist PFEIL Sort att { $$=mknod(FUNC,(Node *) other_fn,
                                              mknod(PARAM,(Node *) $2,
                                              mknod(PARAM,$4,
                                              mknod(PARAM,(Node *) $6,$7))));}
			| ATT Sort Id ',' Id ',' Id ',' Id { $$=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) $2,
                                              mknod(PARAM,(Node *) give_ufn(name($3)),
                                              mknod(PARAM,(Node *) give_ufn(name($5)),
                                              mknod(PARAM,(Node *) give_ufn(name($7)),
                                              (Node *) give_ufn(name($9)))))));	}
			| BRA Id Id	':'  vsortlist PFEIL Sort	att {Node * fnlist;  /* Brackets */
							            				if (($2)==($3))
							            					fnlist=mknod(PARAM,DECLARE((Node *) $2,Bra,(Node *) $7,$5,FALSE),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fn,mknod(PARAM,(Node *) $2,$8)),NULL));
											            else
								             				fnlist=mknod(PARAM,DECLARE((Node *) $2,Bra1,(Node *) $7,$5,FALSE),
                                       mknod(PARAM,DECLARE((Node *) $3,Bra2,(Node *) $7,$5,FALSE),
                                       mknod(PARAM, mknod(FUNC,(Node *) set_brackets,mknod(PARAM,(Node *) $2,(Node *) $3)),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fn,mknod(PARAM,(Node *) $2,$8)),NULL))));
																	$$=mknod(FUNC,(Node *) sequence,fnlist);
																	}
			| VAR idlist ':' Sort			 {$$=DECLARE($2,Var,(Node *) $4,NULL,FALSE);}
			| NUM Sort	 			  			 {$$=mknod(FUNC,(Node *) set_numbertype,(Node *) ($2)); /* sets numbertype for mknum */}
			| SUBSORT Sort ',' Sort ATT Id	 {$$=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort */
										      mknod(PARAM,(Node *) $2,mknod(PARAM,(Node *) $4,(Node *) give_ufn(name($6)))));}
			| SUBSORT Sort ',' Sort		 {$$=mknod(FUNC,(Node *) subsort_def,   /* 2026: subsort of a sort without values */
										      mknod(PARAM,(Node *) $2,mknod(PARAM,(Node *) $4,NULL)));}
			| SHOW func ATT Id		 {$$=mknod(FUNC,(Node *) show_def,      /* 2026: print function */
										      mknod(PARAM,(Node *) $2,(Node *) give_pfn(name($4))));}
			| SHOW func			 {$$=mknod(FUNC,(Node *) show_def,      /* 2026: the usual printing again */
										      mknod(PARAM,(Node *) $2,NULL));}
			| INTNUM Sort ATT Id		 {$$=mknod(FUNC,(Node *) intnum_def,    /* 2026: sort of integers */
										      mknod(PARAM,(Node *) $2,(Node *) give_ufn(name($4))));}
			| NUM idlist ':' Sort			 { /* Variables for numeric numbers */
									                $$=DECLARE($2,Var,(Node *) $4,NULL,TRUE);}
			| CST idlist ':' Sort			 {$$=DECLARE($2,Const,(Node *) $4,NULL,FALSE);}
			| SPEC Alg ':' alglist	   {$$ = mknod(FUNC,(Node *) spec,mknod(PARAM,(Node *) $2,(Node *) $4));}
			| SPEC Alg ':' formlist		 {$$ = mknod(FUNC,(Node *) spec_form,mknod(PARAM,(Node *) $2,$4));	}
			| ADDSPEC Alg ':' formlist {$$ = mknod(FUNC,(Node *) a_spec_form,mknod(PARAM,(Node *) $2,$4));}
			| SORT idlist					     {$$=DECLARE($2,Sort,NULL,NULL,FALSE);}

			| ALG idlist	             {$$=DECLARE($2,Alg,NULL,NULL,FALSE);}
			| TERM idlist ':' Sort	   {$$=DECLARE($2,Term,(Node *) $4,NULL,FALSE);};

idlist	: namedId						{$$ = $1;}
			| namedId ',' idlist		{$$ = mknod(Id,$1,$3);};

l_thing : Const					{$$=(Node *) $1;}
			| Term						{$$=(Node *) $1;};

l_list	: l_thing			     {$$ = mknod(PARAM,(Node *) $1,NULL);}
			| l_thing ',' l_list {$$ = mknod(PARAM,(Node *) $1,$3);};

att 		: /* NULL */		{ $$ = NULL;}
			  | ATT namedId		{ /* numeric C function (userfn.c), otherwise symbolic (symfn.c) */
			                  u_function * u = give_ufn_quiet(name((Symbol *) $2));
			                  s_function * s = u ? NULL : give_sfn(name((Symbol *) $2));
			                  if (u)
			                    $$ = mknod(ATT,(Node *) u,NULL);
			                  else if (s)
			                    $$ = mknod(ATT,(Node *) s,mknod(PARAM,NULL,NULL)); /* r: symbolic */
			                  else
			                    { printfErr(" --ERROR ATT : C-Function %s not Implemented \n",name((Symbol *) $2));
			                      $$ = mknod(ATT,NULL,NULL); }
			                }
			  | ATT SYMBOLIC namedId	{ /* 2026: symbolic C function (symfn.c): gets terms */
			                  $$ = sym_att($3, 0); }
			  | ATT RULES alglist	{ /* 2026: function defined by a rule list: f(..) is REWR f(..) : alglist */
			                  $$ = mknod(ATT,(Node *) rules_sfn(),mknod(PARAM,$3,NULL)); }
			  | ATT SYMBOLIC HOLD namedId	{ /* 2026: plus arguments unevaluated (matchq) */
			                  $$ = sym_att($4, 1); }
				| ATT '(' {block_begin();no_protect();}
								 d_list ')' instruction {protect();block_end();$$ =mknod(PARAM,$4,$6);};

namedId : Id           { $$ = (Node *) $1;}
        | Const        { $$ = (Node *) $1;}
        | Var	         { $$ = (Node *) $1;}
        | func         { $$ = (Node *) $1;}
        | Sort         { $$ = (Node *) $1;}
        | Alg          { $$ = (Node *) $1;}
        | Term         { $$ = (Node *) $1;};


PRECEDENCE		: /* nothing */				{$$ = Func;}
			| LA1						{$$ = La1;	/* Left-associative */}
			| LA2						{$$ = La2;	/* Left-associative */}
			| LA3						{$$ = La3;	/* Left-associative */}
			| LA4						{$$ = La4;	/* Left-associative */}
			| LA5						{$$ = La5;	/* Left-associative */}
			| RA						{$$ = Ra;  	/* Right-associative */}
			| RU						{$$ = Ru;	  /* Right unary */};

condition : condfunc					{$$ = $1;}
			| condfunc ',' condition	{$$ = mknod(Cond,(Node *) and_cond,mknod(PARAM,$1,$3));}; /* all must hold */

condfunc : LB '(' termlist ')'{$$ = mknod(Cond,(Node *) lower_between,$3);}
			| IN '(' termlist ')' 	{$$ = mknod(Cond,(Node *) in_tree,$3);}
			| NIN '(' termlist ')'	{$$ = mknod(Cond,(Node *) not_in_tree,$3);}
			| '(' term ')'   				{$$ = mknod(Cond,(Node *) isnt_zero,$2);};

instructions  : instruction	{if ($1) $$ = mknod(PARAM,$1,NULL); else $$=NULL;}
							| instruction ';' instructions {if ($1) $$ = mknod(PARAM,$1,$3);else $$=$3;};

tinstructions : oinstructions	{if ($1) $$ = mknod(PARAM,$1,NULL); else $$=NULL;}
							| oinstructions '\n' tinstructions 			{if ($1) $$ = mknod(PARAM,$1,$3);else $$=$3;};

oinstructions : instructions			{if($1) $$=mknod(FUNC,(Node *) sequence,$1); else $$=$1;};

separator : '\n' {/* or ; , but gives shift-reduce conflicts because of alglist: Alg;alglist */}
				| ';';

d_list : definition						 {$$ = mknod(PARAM,in_block_def($1),NULL);}
			 | definition ';' d_list {$$ = mknod(PARAM,in_block_def($1),$3);};

instruction : aninstruction     {$$ = in_block_instruct($1); /* Check local variables ! */ }
			| definition		    			{$$ = in_block_def($1);}
			| '{' 										{block_begin();no_protect();}
				tinstructions '}' 			{protect();block_end();
																$$=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,$3),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
			| WHILE condition instruction	{Node * memo,* rtw=in_block_instruct(memo=mknod(FUNC,(Node *) while_fn,mknod(PARAM,$2,NULL /* then becomes $3 */)));
																		WHILE_BODY(memo) = $3;$$=rtw;}

			| IF condition instruction	{Node * memo,* rtw=in_block_instruct(memo=mknod(FUNC,(Node *) if_fn,mknod(PARAM,$2,mknod(PARAM,NULL,NULL))));
																		IF_THEN(memo) = $3;$$=rtw;}
			| IF condition instruction ELSE instruction	{Node * memo,* rtw = in_block_instruct(memo=mknod(FUNC,(Node *) if_fn,mknod(PARAM,$2,mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(memo) = $3;IF_ELSE(memo) = $5;$$=rtw;}
			| FOR term EQ term TO term step DO instruction
														{Node * memo,* rtw = in_block_instruct(memo=mknod(FUNC,(Node *) for_loop,
																mknod(PARAM,
																	mknod(PARAM,$4,$6),
																	mknod(PARAM,
																		mknod(PARAM,$7,(Node *) ($2)),
																		NULL /* $9 */) )));	
														FOR_BODY(memo) = $9;$$=rtw;};


aninstruction	: /* Nothing */ 	{$$=NULL;}
			| SYS String					{$$=mknod(FUNC,(Node *) system_fn,(Node *) ($2));}
			| INC String					{/* include(name($2));$$=NULL;*/ $$=mknod(FUNC,(Node *) include_fn,(Node *) ($2)); }
			| INFO namedId				{$$=mknod(FUNC,(Node *) info_fn,(Node *) ($2)); }
			| REWR term ':' alglist	{$$=mknod(FUNC,(Node *) rewrite_fn,mknod(PARAM,(Node *) ($2),(Node *) ($4)));
														 rtypes(lastterm)=get_type($2);}
			| prntlist						{$$=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,$1));}
			| PRTNUM String				{$$=mknod(FUNC,(Node *) prt_num,(Node *) ($2));}
			| PRT prntlist				{$$=mknod(FUNC,(Node *) sequence,$2); /* without \n */ }
			| OUT String					{$$=mknod(FUNC,(Node *) changeout,(Node *) ($2));}
			| DATA String					{$$=mknod(FUNC,(Node *) changedata,(Node *) ($2));} /* Better : String !! */
			| DATA Const					{if (rtypes($2) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               $$=NULL;}
                             else
                               $$=mknod(FUNC,(Node *) readdata,(Node *) ($2));
                            }
			| Term EQ term				{$$=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ($1),$3));}
			| Term EQ REWR term ':' alglist	{$$=mknod(FUNC,(Node *) rewrite_ass_fn,mknod(PARAM,(Node *) $1,mknod(PARAM,(Node *) $4,(Node *) $6)));}
			| Const EQ term			{ $$=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ($1),(Node *) ($3)));}
			| EXE func Id 			{$$ = NULL;
																exe_always($2)=TRUE;
																hasval($2) = TRUE;
																value($2)  = (Node *) give_ufn(name($3));
 													}
			| LIFT '(' termlist ')' TO '(' termlist ')'	{$$=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) $7,(Node *) $3));}
			| DBG Const 	      	{$$=mknod(FUNC,(Node *) setdebug,(Node *) ($2));}
			| STEPS Alg String		{$$=mknod(FUNC,(Node *) steps_fn,mknod(PARAM,(Node *) $2,(Node *) $3));} /* 2026 */
			| SYMBOLIC String EQ String	{$$=mknod(FUNC,(Node *) role_fn,mknod(PARAM,(Node *) $2,(Node *) $4));} /* 2026: role */
			| SYMBOLIC			{$$=mknod(FUNC,(Node *) role_fn,NULL);  /* delete roles */}
			| RETURN term								{$$=mknod(FUNC,(Node *) return_fn,$2);}
			| QUIT                      {$$=mknod(FUNC,(Node *) quit_fn,NULL);}
			| OPT idlist                {$$=mknod(FUNC,(Node *) opt_fn,$2);}
			| OPT                       {$$=mknod(FUNC,(Node *) opt_fn,NULL);   /* delete */}
			| COMM funclist             {$$=mknod(FUNC,(Node *) comm_fn,$2);}
			| COMM                      {$$=mknod(FUNC,(Node *) comm_fn,NULL);  /* delete */}
			| DEFAULT                   {$$=mknod(FUNC,(Node *) default_fn,NULL); /* delete */}
			| DEFAULT func EQ term      {$$=mknod(FUNC,(Node *) default_fn,
			                                  mknod(PARAM,mknod(PARAM,$2,NULL),$4));}
			| DEFAULT RIGHT func EQ term {$$=mknod(FUNC,(Node *) default_fn,
			                                  mknod(PARAM,mknod(PARAM,$3,mknod(PARAM,NULL,NULL)),$5));};

step  : /* NULL */	{$$=(Node *) NULL;}
			| STEP term	{$$=$2;};

prntexpr : term						{$$=mknod(FUNC,(Node *) printterm,$1); rtypes(lastterm)=get_type($1);}
			| String							{$$=mknod(FUNC,(Node *) printstring,(Node *) ($1));};

prntlist : prntexpr						{$$=mknod(PARAM,$1,NULL);}
			| prntexpr ',' prntlist	{$$=mknod(PARAM,$1,$3);};

alglist		: Alg2						{$$ = mknod(Algs,($1),NULL);}
			| Alg2 ',' alglist		{$$ = mknod(Algs,($1),($3));};

Alg2 : Alg									{$$ = (Node *) ($1);}
			| '(' alglist ')'			{$$ = mknod(Alg,($2),NULL);} /* Standard must pass all algs (chaining) */;

sortlist	: Sort							{$$ = (Node *) ($1);}
			| Sort ',' sortlist			{$$ = mknod(Sorts,(Node *) ($1),$3);};

vsortlist : sortlist					{$$ = $1;}
			| sortlist VARPAR				{$$ = mknod(VARPAR,(Node *) ($1),NULL);};

func		: Func				{$$ = (Node *) ($1);}
			| La1						{$$ = (Node *) ($1);}
			| La2						{$$ = (Node *) ($1);}
			| La3						{$$ = (Node *) ($1);}
			| La4						{$$ = (Node *) ($1);}
			| La5						{$$ = (Node *) ($1);}
			| Ra						{$$ = (Node *) ($1);}
			| Ru						{$$ = (Node *) ($1);}
			| Bra						{$$ = (Node *) ($1);}
			| Bra1					{$$ = (Node *) ($1);};

funclist	: func						{$$ = $1;}
			| func ',' funclist		{$$ = mknod(Functs,$1,$3);};

term		: Term							{	$$ = (Node *) $1; /* tcopy(); does not remember dependencies and does not work in blocks */ 
														}
			| LAST								{$$ = (Node *) lastterm;}
			| Const								{$$ = mknod(Const,(Node *) ($1),NULL);} /* Important for later replacement of variables */
			| Const	Bra1 termlist Bra2 {np_aux=mknod(Terms,mknod(Const,(Node *) ($1),NULL),$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),np_aux), np_aux);} 
			| Var				      		{$$ = (Node *) $1;}
			| '(' term ')'		    {$$ = $2;}
			| term Ru				      {$$ = mknod(Func,(Node *) getsymbol(($2),($1)), ($1) ); }
			| Func term				    {$$ = mknod(Func,(Node *) getsymbol(($1),($2)), ($2) ); }
			| La1 term				    {$$ = mknod(Func,(Node *) getsymbol(($1),($2)), ($2) ); }
			| La2 term				    {$$ = mknod(Func,(Node *) getsymbol(($1),($2)), ($2) ); }
			| La3 term				    {$$ = mknod(Func,(Node *) getsymbol(($1),($2)), ($2) ); }
			| La4 term				    {$$ = mknod(Func,(Node *) getsymbol(($1),($2)), ($2) ); }
			| La5 term				    {$$ = mknod(Func,(Node *) getsymbol(($1),($2)), ($2) ); }
			| Bra termlist Bra	  {$$ = mknod(Func,(Node *) getsymbol(($1),($2)), ($2) ); }
			| Bra1 termlist Bra2	{$$ = mknod(Func,(Node *) getsymbol(($1),($2)), ($2) ); }
			| Func '(' termlist ')'		{$$ = mknod(Func,(Node *) getsymbol(($1),($3)),($3));}
			| term La1 term		    {np_aux=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),np_aux),np_aux);}
			| term La2 term				{np_aux=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),np_aux),np_aux);}
			| term La3 term				{np_aux=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),np_aux),np_aux);}
			| term La4 term				{np_aux=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),np_aux),np_aux);}
			| term La5 term				{np_aux=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),np_aux),np_aux);}
			| term Ra  term				{np_aux=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),np_aux),np_aux);};

termlist	: term						{$$ = $1;}
			| term ',' termlist		{$$ = mknod(Terms,$1,$3);};

formula		: term EQ term		{$$ = mknod(Form,$1,$3);};

vinstr : /* */							{$$ = NULL;}
			| DO instruction			{$$ = $2;};

cformula	: formula	vinstr					{(($1)->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),($1)->r),
																									 $2);$$ = $1;}
          | IF condition formula	vinstr {(($3)->r)=mknod(PARAM,mknod(Cond2,$2,($3)->r),
																									 $4);$$ = $3;};

formlist	: cformula					{$$ = mknod(Forms,$1,NULL); /* NULL serves for hooking in further formulas !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. because of SPEC real : A+B=C;a=3 */
															};

%%

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
