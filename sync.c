/*
 *	sync.c V1.00
 *	Copyright (c)  Rainer Heintzmann (1992)
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>  /* fuer ReadInput */

#include "sym.h"
#include "syn.h"
#include "run.h"
#include "node.h"  /* fuer symeq */
#include "sync.h"
#include "inout.h"
#include "defs.h"
#include "nodes.h"

#define BLOCKAUF '{'
#define BLOCKZU  '}'

#define BUFFSIZE 65536	/* Programm-Stack muss gross genug sein ! (2026: lange Regeln aus Rubi) */

#ifdef NO_MAIN
#define main(argc,argv) start_input(argc,argv)
#endif

extern int yyparse(void); /* in syn.c */

void yyerror (const char *);

static const char * IncFileName = "stdin";
static const char * ActualLine = "";

int inc_level=0;

static Symbol LastTerm =
{
{
SYM_TYPE,
NULL,
NULL},
"%",
Term,
NULL, /* beliebiger Datentyp */
NULL,
FALSE,
NULL,
NULL,
0,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
0 /* global */
};

Symbol * lastterm =  & LastTerm; /* speichert letzten term zwischen */

void ErrorMsg(const char * s)
{
	printfErr("\n>> %s",ActualLine);
	printfErr("Error in %s : %s",IncFileName, s);
}


void sequence (Node * np)	/* fuert instructions hintereinander aus */
{
 	np = np->r;
	while (np)  /* ehemals -> type == PARAM */ 
		{
		if (np->l != NULL)
			{
#ifdef DEBUG
			if (np->l->type != FUNC)
				fatal("sequence: ERROR expected a function here !\n");
#endif
			CALLFUNCT(np->l);
			}
		np = np->r;
		}
}	 

BOOLEAN rm_term_in(Node * to_remove,Node ** p_in) /* ueberspringt 'to_remove' */
{
BOOLEAN changed = FALSE;
	if (!(* p_in)) return FALSE;
	if (to_remove == (* p_in))
		{(* p_in) =(* p_in)->l;
		 changed = TRUE;
		}
	else /* to_remove != % */
		if (((Node *) lastterm) == (* p_in)) /* Termabhaengigkeit von % nicht merken -> Term nicht loeschen */
			(* p_in) = tcopy((* p_in)->l); /* % wird kopiert, da es spaeter geloescht wird */

	if (!(* p_in)) return FALSE;

	if ((* p_in) -> l)
		{
		changed = changed | (rm_term_in(to_remove,&((* p_in) ->l)));
		}
	if ((* p_in) -> r)
		{
		changed = changed | (rm_term_in(to_remove,&((* p_in)->r)));
		}		
	return changed;
}

int cmp_blockstufe (Node * term,int maxstufe)
{
	if (! term) return TRUE;
	if (term->type != SYM_TYPE)
		{
		return (cmp_blockstufe (term->l,maxstufe) && cmp_blockstufe (term->r,maxstufe));
		}
	else
		if (lexval((Symbol *) term) == Term) return cmp_blockstufe (term->l,maxstufe); /* wird bei tcopy sowieso ersetzt */
		else
			if (defined_in_block((Symbol *) term) > maxstufe)
				if (! hasval((Symbol *) term))
					{
					ErrorMsg("");
					printfErr("Local Symbol '%s' should not be assigned to more global Term ! (not done)\n",name((Symbol *) term));
					return FALSE;
					}
				else
					if (IS_FUNCTION(lexval((Symbol *) term)))
						{
						ErrorMsg("");
						printfErr("Local Function '%s' should not be assigned to more global Term ! (not done)\n",name((Symbol *) term));
						return FALSE;
						}
					else return TRUE;
			else
				return TRUE;
return TRUE;
}

int termassign2 (Node * toass, Node * froass)
{
Node * merkold;

if (froass->type != SYM_TYPE)
	{if (rtypes((Symbol *) toass) != rtypes((Symbol *) (froass->l)))
		{
		ErrorMsg("");
		printfErr("Termsort equals not the used sort ! (Converted to %s )\n",name((Symbol *) rtypes((Symbol *) toass)));
		}
	}
else
	if (rtypes((Symbol *) toass) != rtypes((Symbol *) froass))
		{
		ErrorMsg("");
		printfErr("Termsort equals not the used sort ! (Converted to %s )\n",name((Symbol *) rtypes((Symbol *) toass)));
		}

if (!cmp_blockstufe(froass,defined_in_block((Symbol *) toass))) return FALSE;

merkold=toass->l;
toass->l = tcopy(froass);      /* direkt in der Symboltabelle ueberschreiben ! */
delete(merkold);   /* stoppt vor Term Symbolen */
return TRUE;
}

Node * get_type(Node * np)
{
if (np->type != SYM_TYPE)
	return rtypes((Symbol *)(np->l));     /* setzen des variablen Term-types */
else
	return rtypes((Symbol *) np);         /* z.B. Term */
}


void termassign (Node * np)
{
termassign2(ASSIGN_TARGET(np),ASSIGN_TERM(np));
}

void termlist_is_termlist(Node * np)   /* LIFT Befehl */
{
Node * jog1, * jog2;
Symbol * oldsym=(Symbol *) 0;

/* Pruefen, ob Symbole schon belegt sind  */
for (jog1= LIFT_TO(np);jog1->type==Terms; jog1=jog1->r)
	if (IS_kette(TERM_HEAD(jog1->l)) != (Symbol *) NULL)
		{
		ErrorMsg("");
		printfErr("Symbol '");
		print((Node *) TERM_HEAD(jog1->l));
		printfErr("' is already lifted \n");
		return;
		}
if (IS_kette(TERM_HEAD(jog1)) != (Symbol *) NULL)
	{
	ErrorMsg("");
	printfErr("Symbol '");
	print((Node *) TERM_HEAD(jog1));
	printfErr("' is already lifted \n");
	return;
	}


for (jog1= LIFT_TO(np),jog2= LIFT_FROM(np);jog1->type==Terms; jog1=jog1->r,jog2=jog2->r)
	{
		if (jog2->type != Terms)
			break;
		IS_kette(TERM_HEAD(jog1->l)) = oldsym;
		oldsym = TERM_HEAD(jog1->l);
		IS_Verbindung(oldsym) = TERM_HEAD(jog2->l);
          /* Symbol2 ^^                                 Symbol1 ^^ */
	}

if (jog2->type == Terms) /* jog1 ist kuerzer */
	{
	ErrorMsg("");
	printfErr("Assigned list is too long\n");
	IS_kette(TERM_HEAD(jog1)) = oldsym;
	oldsym = TERM_HEAD(jog1);
	IS_Verbindung(oldsym) = TERM_HEAD(jog2->l);
	}
if (jog1->type == Terms) /* jog1 ist laenger */
	{
	ErrorMsg("");
	printfErr("Assigned list is too short\n");
	IS_kette(TERM_HEAD(jog1->l)) = oldsym;
	oldsym = TERM_HEAD(jog1->l);
	IS_Verbindung(oldsym) = TERM_HEAD(jog2);
	}
if (jog1->type != Terms && jog2->type != Terms) /* jog1,jog2 sind gleichlang */
	{
	IS_kette(TERM_HEAD(jog1)) = oldsym;
	oldsym = TERM_HEAD(jog1);
	IS_Verbindung(oldsym) = TERM_HEAD(jog2);
	}

if (LIFT_TO(np)->type != Terms)                          /* Im Kreis verketten */
	IS_kette(TERM_HEAD(LIFT_TO(np))) = oldsym;
else
	IS_kette(TERM_HEAD(LIFT_TO(np)->l)) = oldsym;

return;
}

void history_store (Node * np)
{
if (!(np->l))
	return;    /* Nur Terme speichern,die nicht NULL sind */

rtypes(lastterm)=get_type(np);

termassign2((Node *) lastterm,np);         /* hier tcopy sonst Verwirrung bei der Benutzung */
}

void printterm (Node * np)
{
Node * erg;
if (erg=calkulate (np ->r)) 
	{
	print(erg);
	delnum((Symbol *) erg,TRUE); /* auch value */
	}
else print(np -> r);

/* printfOut("\t"); */ /* Tab ausgeben */

history_store(np->r);

}

void printstring (Node * np)
{char * cp;
cp= name(((Symbol *) (np -> r)));
/* if ((cp[0] == '\\') &&( cp[1] == 'n'))	{cp+=2;	printfOut("\n");	} */
printfOut("%s",cp);
}

void printnl (Node * np)
{
CALLFUNCT(PRINTNL_SEQ(np));
printfOut("\n");
}


void setdebug (Node * np)
{
	setDebug((int) (* (double *) value(np ->r)));
}

void numassign2 (Node * froass, Symbol * toass)   /* Setzt bzw Loescht Nummer */
{
Node * erg;
while (((froass)->type != Const) && (froass->type != Func))
	{
	if (!(froass->l))	
		{ErrorMsg("Wrong const-assignment : no Valid Term\n");
		return;}
	froass=froass->l;
	}
if (rtypes(toass) != rtypes((Symbol *)froass->l))
 	{ErrorMsg("Wrong const-assignment : different types\n");
 	return;}

erg = calkulate(froass);

if (hasval(toass)) DELNUM(toass,value(toass));

if (erg)
	{
	if (is_shared_num((Symbol *) erg))  /* 0,1: statischen Wert kopieren, sonst spaeter free() auf statischen Speicher */
		value(toass) = CPYNUM(erg,value(erg));
	else
		value(toass)  = value(erg);
	hasval(toass) = TRUE;
	delnum((Symbol *) erg,FALSE); /* Do not delete value */
	}
else 
	hasval(toass) = FALSE;
}

void numassign (Node * np)   /* Setzt bzw Loescht Nummer */
{
numassign2(ASSIGN_TERM(np),(Symbol *) ASSIGN_TARGET(np));
}

void while_fkt (Node * np)
{
	while (COND_CALL(WHILE_COND(np)))
		CALLFUNCT(WHILE_BODY(np));
}

void if_fkt (Node * np)
{
	DEBG((5,"-- If_fkt ( "));
	DBFK(5, print(COND_ARG(IF_COND(np))));
	DEBG((5,") \n"));
	if (COND_CALL(IF_COND(np)))
		CALLFUNCT(IF_THEN(np));
	else
		if (IF_ELSE(np)) CALLFUNCT(IF_ELSE(np));
}

void forschleife (Node * np)
{
Node * p_anf,
		 * p_ende,
		 * p_step = FOR_STEP(np),
		 * p_symbol;

double anf,ende,step;
long schritte,i;
double counter;    /* lokal */
double * merkval;
int merkhasval;

if (	!( p_anf = calkulate(FOR_FROM(np)))
	||	!(p_ende = calkulate(FOR_TO(np)))
	||	((p_step) && !(p_step = calkulate(FOR_STEP(np)))))
	{
	ErrorMsg("Wrong FOR-loop: all values must be calculable !\n");
	if (p_anf)  delnum((Symbol *) p_anf,TRUE); /* auch value */
	if (p_ende) delnum((Symbol *) p_ende,TRUE); /* auch value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* auch value */
	return;
	}
anf = * (double *) value(p_anf);
ende = * (double *) value(p_ende);

if (p_step)
	step = * (double *) value(p_step);
else
	step = (double) 1.0;

	DEBG((5,"-- Forschleife (%g,%g,%g) \n",anf,ende,step));

if (step == 0) 
	{ErrorMsg("Step must not be zero !\n");
	return;
	}

schritte = ((long) 1) + (long) ((ende-anf)/step);
if  (schritte < 0)
	{ErrorMsg("Step must point in the other direction ! \n");
	delnum((Symbol *) p_anf,TRUE); /* auch value */
	delnum((Symbol *) p_ende,TRUE); /* auch value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* auch value */
	return;
	}

if (FOR_VAR(np) -> type != Const)
	{ErrorMsg("Assigned Term should be a CONST - Value \n");
	delnum((Symbol *) p_anf,TRUE); /* auch value */
	delnum((Symbol *) p_ende,TRUE); /* auch value */
	if (p_step) delnum((Symbol *) p_step,TRUE); /* auch value */
	return;
	}

p_symbol = (Node *) TERM_HEAD(FOR_VAR(np));

DEBG((5, "-- Symbol to count : "));
DBFK(5, print(p_symbol));
DEBG((5,"\n"));

merkhasval = hasval(p_symbol);
merkval = (double *) value(p_symbol);

hasval(p_symbol) = TRUE;

value(p_symbol)= & counter;

for (i=0;i<schritte;i++)
	{
	counter = ((double) i)*step+anf;
	if (FOR_BODY(np))				/* Sonst sozusagen NOP (instruction ist NULL) */
		CALLFUNCT(FOR_BODY(np));
	}

hasval(p_symbol) = merkhasval;
value(p_symbol) = (void *) merkval;

delnum((Symbol *) p_anf,TRUE); /* auch value */
delnum((Symbol *) p_ende,TRUE); /* auch value */
if (p_step) delnum((Symbol *) p_step,TRUE); /* auch value */

return;
}

void changeout (Node * np)
{	
	changeOut(name((Symbol *) np->r));
	return;
}

void readdata (Node * np)
{ double * zahlp;
	zahlp = (double *) malloc(sizeof(double));
  if (! zahlp)
				fatal("readdata: no room for making real-number !\n");
	(* zahlp) = readData();
	if (hasval(np->r) && value(np->r))
		DELNUM(np->r,value(np->r)); /* alten Wert freigeben */
	value(np->r)=zahlp;
	hasval(np->r)=TRUE;
	return;
}

void changedata (Node * np)
{
	changeData(name((Symbol *) np->r));
	return;
}

void system_fkt (Node * np)
{
	system(name((Symbol *) np->r));
}

void include_fkt (Node * np)
{
	include(name((Symbol *) np -> r));
}

void info_fkt (Node * np)
{
printfOut("Object        : %s\n",name((Symbol *) np->r ));
printfOut("is a          : %s\n",type((Symbol *) np->r ));
if ((lexval((Symbol *) np->r) == Id) ||
		(lexval((Symbol *) np->r) == Sort)) return;

printfOut("result-type   : ");
if (rtypes((Symbol *) np->r )) tprint(rtypes((Symbol *) np->r ),0);
else printfOut("none");
printfOut("\n");
printfOut("argument-type : ");
if (atypes((Symbol *) np->r )) tprint(atypes((Symbol *) np->r ),0);
else printfOut("none");
printfOut("\n");
if	(((lexval((Symbol *) np->r) == Const) ||
		 ((lexval((Symbol *) np->r) == Var))) &&
		 (hasval((Symbol *) np->r))) {
		 printfOut("Value         : ");
		 tprint(np->r,0);
     printfOut("\n"); }
else
	if (hasval((Symbol *) np->r)) printfOut("is attached to a C-function \n");
}

void rewrite_ass_fkt (Node * np)
{
Node * to_rewr = tcopy(REWRASS_TERM(np)); /* in Termen (TERM t) darf nicht ersetzt werden ; tcopy ueberspringt die Symbole 'TERM' */
rewrite_begin();
to_rewr = solve(to_rewr,REWRASS_ALGS(np));
rewrite_end();
termassign2(REWRASS_TARGET(np),to_rewr); /* speichert eine Kopie */
delete(to_rewr);
}

void rewrite_fkt (Node * np)
{
Node * to_rewr = tcopy(REWR_TERM(np)); /* in Termen (TERM t) darf nicht ersetzt werden ; tcopy ueberspringt die Symbole 'TERM' */
rewrite_begin();
to_rewr = solve(to_rewr,REWR_ALGS(np));
rewrite_end();
print(to_rewr);
printfOut("\n");
history_store(to_rewr); /* speichert eine Kopie in % */
delete(to_rewr);
}

void quit_fkt (Node * np)
{
	exit(0);
}

BOOLEAN IS_follows(Symbol * from,Symbol * to) /* to befindet sich in IS_Verbindung */
{
	Symbol * jog;
	DEBG((4,"DB : IS_follows : from :"));
	DBFK(4,print((Node *) from));
	DEBG((4,"to :"));
	DBFK(4,print((Node *) to));

	for (jog=from;jog != (Symbol *) NULL ;jog=IS_Verbindung(jog))
		{
		if (symeq(jog,to)) /* Symbole bzw. Werte gleich */
			{
			DEBG((4," .. returned TRUE\n"));
			return TRUE;
			}
		if (IS_Verbindung(jog) == from) /* Einmal im Kreis */
			{
			DEBG((4," .. returned FALSE\n"));
			return FALSE;
			}
		}
	DEBG((4," .. returned FALSE\n"));
	return FALSE;
}

Symbol * IS_search (Symbol * from,Symbol * to)
{
	Symbol * jog;

	DEBG((4,"DB : IS_search : from :"));
	DBFK(4,print((Node *) from));
	DEBG((4,"to :"));
	DBFK(4,print((Node *) to));

	if (IS_follows(from,to))
		return from;
	if (! IS_kette(from))
		return (Symbol *) NULL; /* Variable ist in keine Kette eingetragen ! */

	for (jog=IS_kette(from);jog != from;jog=IS_kette(jog))
		{
		if (! jog)
			{
			fatal("Internal Error: Broken IS_kette ! ");
			}
		if (IS_follows(jog,to))
			return jog;
		}
	return (Symbol *) NULL;
}

BOOLEAN lock_rtypes (Symbol * which,Symbol * from,Node * * chain)
{
	Symbol * lock,* jog,* jog2,* from2;
	BOOLEAN detected=FALSE;

	DEBG((4,"DB : lock_rtypes : which :"));
	DBFK(4,print((Node *) which));
	DEBG((4,"from :"));
	DBFK(4,print((Node *) from));

if (symeq(which,from))
	return TRUE;

/* Einmal die IS_Verbindungskette ablaufen und moeglichen Widerspruch feststellen : */
for (from2=from,jog2=IS_Verbindung(from);!symeq(from2,which);from2=jog2,jog2=IS_Verbindung(jog2))
	{
	if (jog2 == NULL)
		fatal("ERROR sync.c: lock_rtypes : 'which' does'nt follow from 'from'\n") ; /* Ende der Kette erreicht ohne which zu finden */
	if ((lock=IS_Verbindung(rtypes(jog2))) != NULL)
			{
			if (lock != from2)
				{	detected=FALSE;
				for (jog=IS_kette(lock);jog!=lock;jog=IS_kette(jog))
					{
					DEBG((4,"DB : lock_rtype : jog :"));
					DBFK(4,print((Node *) jog));
					DEBG((4,"\n"));

					if (jog == from2)
						{
						DEBG((4," .. detected old\n"));
						detected=TRUE;
						}
					if (jog == (Symbol *) NULL)
						fatal("INTERNAL ERROR: sync.c:  lock_rtype got NULL");
					}
				}
			else
				detected=TRUE;
			if (! detected)
				{
				DEBG((4," did not detect one, returned FALSE\n"));
				return FALSE; /* anders gelockt */
				}
			}
	}

/* keine Falsch gelockte Menge vorhanden -> restliche locken */

for (from2=from,jog2=IS_Verbindung(from);!symeq(from2,which);from2=jog2,jog2=IS_Verbindung(jog2))
	{
	if ((lock=IS_Verbindung(rtypes(jog2))) == NULL)
			{
			IS_Verbindung(rtypes(jog2)) = from2;
			* chain = mknod(CHAIN,* chain,rtypes(jog2)); /* Aufspiessen um wieder zu loeschen */
			
			DEBG((4," .. established new\n"));
			}
	}


	DEBG((4,"lock_rtypes returned TRUE\n"));
			
return TRUE;
			
}

BOOLEAN eq_rtypes(Node * a,Node * typ)
{
	switch(a->type)
	{
	case Terms:
		DEBG((4,"DB : eq_rtypes : a->type is 'Terms' \n"));
		return FALSE;

	case SYM_TYPE: /* VAR (ersetzte VAR's sind mit Const oder Func ueberschrieben)*/
		DEBG((4,"DB : eq_rtypes Termsort : %s  required sort : %s \n",name((Symbol *) (rtypes((Symbol *)(a)))),name((Symbol *) (typ))));
		if (typ!=rtypes((Symbol *) (a))) /* ! eq_sorts(typ,rtypes..) bewirkt sofortige Reduktion */
			 return FALSE;
	break;

	default:                          /* Funct ,Const */
		DEBG((4,"DB : eq_rtypes Termsort : %s  required sort : %s \n",name((Symbol *) (rtypes((Symbol *)(a->l)))),name((Symbol *) (typ))));
		if (typ!=rtypes((Symbol *) (a->l))) /* ! eq_sorts(typ,rtypes..) bewirkt sofortige Reduktion */
			return FALSE;
	break;
	}

return TRUE;		
}


Symbol * getsymbol (Symbol * symbol,Node * termlist) /* sucht aus gleinamigen Symbolen das, mit den richtigen Argumenten heraus */
{                                                    /* termlist ist Liste der Argumente,die tatsaechlich vorliegen */
	Node * at1,* at2,* asym;
	Symbol * sym=symbol;           /* Symbole sind im Kreis verkettet */
	int			varcount=-1,atype;
	BOOLEAN iseq;

	if (! termlist) fatal("Internal ERROR : No termlist in getsymbol\n ");	

	do	{       /* durchlaeuft die einzelnen Funktionen */
		iseq=TRUE;	
		varcount = -1;

		asym = atypes(sym); /* sym kann nicht NULL sein ! */
		atype= asym->type;

		if (atype == VARPAR)
			{
			asym=asym->l;
			}

		for (at1=termlist,at2=asym;(at2->r!=NULL);at1=at1->r,at2=at2->r)
			{
			if ((at1->r==NULL) || (at1->type!=Terms) )
				{iseq=FALSE;break;}
			if (! eq_rtypes(at1->l,at2->l))
				{iseq=FALSE;break;}
			}

		if (iseq)
			if (atype == VARPAR)
				{
				for (varcount=0;(at1->r!=NULL) && (at1->type==Terms);at1=at1->r,varcount++)
					if (! eq_rtypes(at1->l,at2))
						{iseq=FALSE;break;}
				}

		if (iseq)
			if (! eq_rtypes(at1,at2))
				{iseq=FALSE;}

	DEBG((4,"DB : -getsymbol  reached last parameter \n"));

		if (iseq) break;

	sym=kette(sym); /* naechstes Symbol */
	}  while	((sym != (Symbol *) NULL) && (sym != symbol));  /* NULL fuer den Fall nur eines Symbols */

	if (iseq==FALSE)
		{
		ErrorMsg("");
		printfErr("Used wrong argumenttype or -number for Funktion '%s' !\n",name(symbol));
		sym=symbol; /* erste Definition benutzen */
		}
	else
		if (varcount != -1)
			{
			DEBG((4,"DB : -getsymbol  varcount is %d \n",varcount));
			}

	return sym;
}


int read_input _1a ((fp), FILE * fp)
{	
	char buf[BUFFSIZE], * bp;
	char * const ep = buf + sizeof buf;
	int klammerbalance=0;
	void lexi_buf _1p (const char *);


	do
	{	for (bp = buf; bp < ep && fgets(bp, ep - bp, fp); ) /* Zeilenweises Aufrufen des Yacc */
		{	
			if (fp != stdin)
				DEBG((1,bp));  /* Text aus Datei auf den Bildschirm */

			for (;*bp != '\0';bp++)
				{
				if (*bp == BLOCKAUF) klammerbalance++;
				if (*bp == BLOCKZU) klammerbalance--;
				}
			DEBG((10,"klammerbal.: %d\n",klammerbalance));
			if (bp > buf + 1 && bp[-2] == '\\' && bp[-1] == '\n')
				{(-- bp)[-1] = ' '; 
				continue;
				}
			if (klammerbalance > 0)
				{if (fp == stdin)
					printfOut("--> ");
				 continue;
				}
			if (klammerbalance < 0) klammerbalance=0;

			break;
		}

		if (bp > buf)
			{
			ActualLine=buf;
			lexi_buf(buf);
			yyparse();
			}

	} while (! feof(fp));
	return 0;
}

int parse_it(char * text)
{
void lexi_buf(const char *); /* Prototyp */

lexi_buf(text);
yyparse();
return 0;
}


int main(int argc, char * argv []) /* Kein Leerzeichen zw. main und '(' ! */
{
	inc_level=0;
	read_input(stdin);
	return 0;
}

void include _1a ((cp), const char * cp)
{
	FILE * fp;
	const char * old;

	if (fp = fopen (cp,"r"))
		{
		old=IncFileName;
		IncFileName=cp;
		int oldbase;
		is_not_running();
		inc_level++;
		oldbase = include_begin(); /* File wie Top-Level-Eingabe behandeln */
		read_input(fp);
		include_end(oldbase);
		inc_level--;
		fclose (fp);
		is_running();
		IncFileName=old;
		}
	else
		{
		ErrorMsg("");
		printfErr("Unabel to open includefile \"%s\" \n",cp);
		}
}

void yyerror (const char * s)
{
	end_all_blocks();
	is_not_running();
	ErrorMsg(s);
	printfErr("\n");
}
int yywrap(void) /* von flex aufgerufen: 1 = Eingabe zu Ende */
{
return 1;
}

