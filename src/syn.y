/*
 *	syn.y V1.00
 *	Copyright (c)  Rainer Heintzmann (1992)
 *	Grundgeruesst : Prof. Axel T. Schreiner
 *
 *	Variablen
 */

%{

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

static Node * sym_att (Node * id, int hold);	/* below */

%}

%union	{
	Symbol 	* y_sym;
	Node 	* y_nod;
	int	 	  y_int; 
	char 	* y_chr;
	}

%token			CST VAR SORT FUNC ALG SPEC ADDSPEC REWR PRT GRAPH PFEIL TERM NUM ATT IS EQ INFO
%token			LA1 LA2 LA3 LA4 LA5 LOCAL RU RA KOMMU LB IN NIN PARAM FOR TO STEP DO DBG LAST
%token			BRA OTHER DATA OUT INC EXE VARPAR SYS IF ELSE WHILE PRTNUM LIFT QUIT RETURN
%token			OPT COMM DEFAULT RIGHT SUBSORT INTNUM STEPS SYMBOLIC HOLD
%token	<y_sym>	Id String
%token	<y_sym>	Sort Alg Term
%token	<y_sym>	La1 La2 La3 La4 La5 Ru Ra Func Const Var Bra Bra1 Bra2
%token			Terms Form Sorts Functs Forms Algs Cond2 Cond
%type	<y_int>	VORRANG
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
															
definition	: FUNC namedId ':' vsortlist PFEIL Sort	VORRANG att {	$$=mknod(FUNC,(Node *) sequence,
                                                                 mknod(PARAM,DECLARE((Node *) $2,$7,(Node *) $6,$4,FALSE),
                                                                 mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) $2,$8)),NULL)));}
			| OTHER func ':' vsortlist PFEIL Sort att { $$=mknod(FUNC,(Node *) other_fkt,
                                              mknod(PARAM,(Node *) $2,
                                              mknod(PARAM,$4,
                                              mknod(PARAM,(Node *) $6,$7))));}
			| ATT Sort Id ',' Id ',' Id ',' Id { $$=mknod(FUNC,(Node *) att_sort,
                                              mknod(PARAM,(Node *) $2,
                                              mknod(PARAM,(Node *) give_ufkt(name($3)),
                                              mknod(PARAM,(Node *) give_ufkt(name($5)),
                                              mknod(PARAM,(Node *) give_ufkt(name($7)),
                                              (Node *) give_ufkt(name($9)))))));	}
			| BRA Id Id	':'  vsortlist PFEIL Sort	att {Node * fkts;  /* Klammern */
							            				if (($2)==($3))
							            					fkts=mknod(PARAM,DECLARE((Node *) $2,Bra,(Node *) $7,$5,FALSE),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) $2,$8)),NULL));
											            else
								             				fkts=mknod(PARAM,DECLARE((Node *) $2,Bra1,(Node *) $7,$5,FALSE),
                                       mknod(PARAM,DECLARE((Node *) $3,Bra2,(Node *) $7,$5,FALSE),
                                       mknod(PARAM, mknod(FUNC,(Node *) set_brackets,mknod(PARAM,(Node *) $2,(Node *) $3)),
																				mknod(PARAM,mknod(FUNC,(Node *) att_fkt,mknod(PARAM,(Node *) $2,$8)),NULL))));
																	$$=mknod(FUNC,(Node *) sequence,fkts);
																	}
			| VAR idlist ':' Sort			 {$$=DECLARE($2,Var,(Node *) $4,NULL,FALSE);}
			| NUM Sort	 			  			 {$$=mknod(FUNC,(Node *) set_numbertype,(Node *) ($2)); /* setzt numbertype fuer mknum */}
			| SUBSORT Sort ',' Sort ATT Id	 {$$=mknod(FUNC,(Node *) subsort_def,   /* 2026: Untersorte */
										      mknod(PARAM,(Node *) $2,mknod(PARAM,(Node *) $4,(Node *) give_ufkt(name($6)))));}
			| INTNUM Sort ATT Id		 {$$=mknod(FUNC,(Node *) intnum_def,    /* 2026: Sorte ganzer Zahlen */
										      mknod(PARAM,(Node *) $2,(Node *) give_ufkt(name($4))));}
			| NUM idlist ':' Sort			 { /* Variablen fuer Numerische Zahlen */
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
			  | ATT namedId		{ /* numerische C-Funktion (userfkt.c), sonst symbolische (symfkt.c) */
			                  u_function * u = give_ufkt_quiet(name((Symbol *) $2));
			                  s_function * s = u ? NULL : give_sfkt(name((Symbol *) $2));
			                  if (u)
			                    $$ = mknod(ATT,(Node *) u,NULL);
			                  else if (s)
			                    $$ = mknod(ATT,(Node *) s,mknod(PARAM,NULL,NULL)); /* r: symbolisch */
			                  else
			                    { printfErr(" --ERROR ATT : C-Function %s not Implemented \n",name((Symbol *) $2));
			                      $$ = mknod(ATT,NULL,NULL); }
			                }
			  | ATT SYMBOLIC namedId	{ /* 2026: symbolische C-Funktion (symfkt.c): bekommt Terme */
			                  $$ = sym_att($3, 0); }
			  | ATT SYMBOLIC HOLD namedId	{ /* 2026: dazu Argumente unausgewertet (matchq) */
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


VORRANG		: /* nothing */				{$$ = Func;}
			| LA1						{$$ = La1;	/* Linksassoziativ */}
			| LA2						{$$ = La2;	/* Linksassoziativ */}
			| LA3						{$$ = La3;	/* Linksassoziativ */}
			| LA4						{$$ = La4;	/* Linksassoziativ */}
			| LA5						{$$ = La5;	/* Linksassoziativ */}
			| RA						{$$ = Ra;  	/* Rechtsassoziativ */}
			| RU						{$$ = Ru;	  /* Rechts Unaer */};

condition : condfunc					{$$ = $1;}
			| condfunc ',' condition	{$$ = mknod(Cond,(Node *) and_cond,mknod(PARAM,$1,$3));}; /* alle muessen gelten */

condfunc : LB '(' termlist ')'{$$ = mknod(Cond,(Node *) lower_between,$3);}
			| IN '(' termlist ')' 	{$$ = mknod(Cond,(Node *) in_tree,$3);}
			| NIN '(' termlist ')'	{$$ = mknod(Cond,(Node *) not_in_tree,$3);}
			| '(' term ')'   				{$$ = mknod(Cond,(Node *) isnt_zero,$2);};

instructions  : instruction	{if ($1) $$ = mknod(PARAM,$1,NULL); else $$=NULL;}
							| instruction ';' instructions {if ($1) $$ = mknod(PARAM,$1,$3);else $$=$3;};

tinstructions : oinstructions	{if ($1) $$ = mknod(PARAM,$1,NULL); else $$=NULL;}
							| oinstructions '\n' tinstructions 			{if ($1) $$ = mknod(PARAM,$1,$3);else $$=$3;};

oinstructions : instructions			{if($1) $$=mknod(FUNC,(Node *) sequence,$1); else $$=$1;};

trenner : '\n' {/* oder ; , bringt aber shift-reduce conflicts wegen alglist: Alg;alglist */}
				| ';';

d_list : definition						 {$$ = mknod(PARAM,in_block_def($1),NULL);}
			 | definition ';' d_list {$$ = mknod(PARAM,in_block_def($1),$3);};

instruction : aninstruction     {$$ = in_block_instruct($1); /* Locale Variablen pruefen ! */ }
			| definition		    			{$$ = in_block_def($1);}
			| '{' 										{block_begin();no_protect();}
				tinstructions '}' 			{protect();block_end();
																$$=mknod(FUNC,(Node *) sequence,
																mknod(PARAM,mknod(FUNC,(Node *) do_block_begin,NULL),
																mknod(PARAM,mknod(FUNC,(Node *) sequence,$3),
																mknod(PARAM,mknod(FUNC,(Node *) do_block_end,NULL),NULL))));}
			| WHILE condition instruction	{Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) while_fkt,mknod(PARAM,$2,NULL /* wird dann $3 */)));
																		WHILE_BODY(merk) = $3;$$=rtw;}

			| IF condition instruction	{Node * merk,* rtw=in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,$2,mknod(PARAM,NULL,NULL))));
																		IF_THEN(merk) = $3;$$=rtw;}
			| IF condition instruction ELSE instruction	{Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) if_fkt,mknod(PARAM,$2,mknod(PARAM,NULL /* $3 */,NULL /* $5 */ ))));
																		IF_THEN(merk) = $3;IF_ELSE(merk) = $5;$$=rtw;}
			| FOR term EQ term TO term step DO instruction
														{Node * merk,* rtw = in_block_instruct(merk=mknod(FUNC,(Node *) forschleife,
																mknod(PARAM,
																	mknod(PARAM,$4,$6),
																	mknod(PARAM,
																		mknod(PARAM,$7,(Node *) ($2)),
																		NULL /* $9 */) )));	
														FOR_BODY(merk) = $9;$$=rtw;};


aninstruction	: /* Nichts */ 	{$$=NULL;}
			| SYS String					{$$=mknod(FUNC,(Node *) system_fkt,(Node *) ($2));}
			| INC String					{/* include(name($2));$$=NULL;*/ $$=mknod(FUNC,(Node *) include_fkt,(Node *) ($2)); }
			| INFO namedId				{$$=mknod(FUNC,(Node *) info_fkt,(Node *) ($2)); }
			| REWR term ':' alglist	{$$=mknod(FUNC,(Node *) rewrite_fkt,mknod(PARAM,(Node *) ($2),(Node *) ($4)));
														 rtypes(lastterm)=get_type($2);}
			| prntlist						{$$=mknod(FUNC,(Node *) printnl,mknod(FUNC,(Node *) sequence,$1));}
			| PRTNUM String				{$$=mknod(FUNC,(Node *) prt_num,(Node *) ($2));}
			| PRT prntlist				{$$=mknod(FUNC,(Node *) sequence,$2); /* ohne \n */ }
			| OUT String					{$$=mknod(FUNC,(Node *) changeout,(Node *) ($2));}
			| DATA String					{$$=mknod(FUNC,(Node *) changedata,(Node *) ($2));} /* Besser : String !! */
			| DATA Const					{if (rtypes($2) != get_numbertype())
                               {printfErr("error : DATA-Const must be of real-type !\n");
                               $$=NULL;}
                             else
                               $$=mknod(FUNC,(Node *) readdata,(Node *) ($2));
                            }
			| Term EQ term				{$$=mknod(FUNC,(Node *) termassign,mknod(PARAM,(Node *) ($1),$3));}
			| Term EQ REWR term ':' alglist	{$$=mknod(FUNC,(Node *) rewrite_ass_fkt,mknod(PARAM,(Node *) $1,mknod(PARAM,(Node *) $4,(Node *) $6)));}
			| Const EQ term			{ $$=mknod(FUNC,(Node *) numassign,mknod(PARAM,(Node *) ($1),(Node *) ($3)));}
			| EXE func Id 			{$$ = NULL;
																exe_always($2)=TRUE;
																hasval($2) = TRUE;
																value($2)  = (Node *) give_ufkt(name($3));
 													}
			| LIFT '(' termlist ')' TO '(' termlist ')'	{$$=mknod(FUNC,(Node *) termlist_is_termlist,mknod(PARAM,(Node *) $7,(Node *) $3));}
			| DBG Const 	      	{$$=mknod(FUNC,(Node *) setdebug,(Node *) ($2));}
			| STEPS Alg String		{$$=mknod(FUNC,(Node *) steps_fkt,mknod(PARAM,(Node *) $2,(Node *) $3));} /* 2026 */
			| SYMBOLIC String EQ String	{$$=mknod(FUNC,(Node *) role_fkt,mknod(PARAM,(Node *) $2,(Node *) $4));} /* 2026: Rolle */
			| SYMBOLIC			{$$=mknod(FUNC,(Node *) role_fkt,NULL);  /* Rollen loeschen */}
			| RETURN term								{$$=mknod(FUNC,(Node *) return_fkt,$2);}
			| QUIT                      {$$=mknod(FUNC,(Node *) quit_fkt,NULL);}
			| OPT idlist                {$$=mknod(FUNC,(Node *) opt_fkt,$2);}
			| OPT                       {$$=mknod(FUNC,(Node *) opt_fkt,NULL);   /* loeschen */}
			| COMM funclist             {$$=mknod(FUNC,(Node *) comm_fkt,$2);}
			| COMM                      {$$=mknod(FUNC,(Node *) comm_fkt,NULL);  /* loeschen */}
			| DEFAULT                   {$$=mknod(FUNC,(Node *) default_fkt,NULL); /* loeschen */}
			| DEFAULT func EQ term      {$$=mknod(FUNC,(Node *) default_fkt,
			                                  mknod(PARAM,mknod(PARAM,$2,NULL),$4));}
			| DEFAULT RIGHT func EQ term {$$=mknod(FUNC,(Node *) default_fkt,
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
			| '(' alglist ')'			{$$ = mknod(Alg,($2),NULL);} /* Standart muss alle alg passieren (Verkettung) */;

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

term		: Term							{	$$ = (Node *) $1; /* tcopy(); merkt sich keine Abhaengigkeiten und funktioniert nicht in Bloecken */ 
														}
			| LAST								{$$ = (Node *) lastterm;}
			| Const								{$$ = mknod(Const,(Node *) ($1),NULL);} /* Wichtig fuer spaeteres Ersetzen von Variablen */
			| Const	Bra1 termlist Bra2 {nphilf=mknod(Terms,mknod(Const,(Node *) ($1),NULL),$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),nphilf), nphilf);} 
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
			| term La1 term		    {nphilf=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),nphilf),nphilf);}
			| term La2 term				{nphilf=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),nphilf),nphilf);}
			| term La3 term				{nphilf=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),nphilf),nphilf);}
			| term La4 term				{nphilf=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),nphilf),nphilf);}
			| term La5 term				{nphilf=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),nphilf),nphilf);}
			| term Ra  term				{nphilf=mknod(Terms,$1,$3);
														 $$ = mknod(Func,(Node *) getsymbol(($2),nphilf),nphilf);};

termlist	: term						{$$ = $1;}
			| term ',' termlist		{$$ = mknod(Terms,$1,$3);};

formula		: term EQ term		{$$ = mknod(Form,$1,$3);};

vinstr : /* */							{$$ = NULL;}
			| DO instruction			{$$ = $2;};

cformula	: formula	vinstr					{(($1)->r)=mknod(PARAM,mknod(Cond2,mknod(Cond,(Node *) truefunc,NULL),($1)->r),
																									 $2);$$ = $1;}
          | IF condition formula	vinstr {(($3)->r)=mknod(PARAM,mknod(Cond2,$2,($3)->r),
																									 $4);$$ = $3;};

formlist	: cformula					{$$ = mknod(Forms,$1,NULL); /* NULL dient zum Einhaengen weiterer Formeln !! */
			/* | cformula ';' formlist {$$ = mknod(Forms,$1,$3);}  shift-red. wegen SPEC real : A+B=C;a=3 */
															};

%%

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
