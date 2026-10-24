/*
 *	run.c V1.00
 * 
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *
 *	Variablen
 */

#include <string.h> /* fuer strcmp */
#include <stdio.h>
#include <stdlib.h>
#include "strsave.h"

#include "inout.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "stack.h"
#include "forms.h"
#include "userfkt.h"
#include "sync.h" /* fuer IS_follows,IS_search  */
#include "node.h"
#include "defs.h"
#include "nodes.h"
#include "symfkt.h"
#include "listmatch.h"
#include "numsort.h"	/* 2026: SUBSORT */

#define EQUAL  0	/* wichtig wegen strcmp */

extern char * numbername; /* zur Identifizierung einer Nummer fuer delete */

Node * numbertype = NULL;

static int mistake = FALSE;

static BOOLEAN didrewrite = FALSE; /* fuer Verkettung der Algebren : (real;diff);more -> nicht reentrent */

BOOLEAN truefunc _1p (Node *);
BOOLEAN in_tree2 _2p(Node * npl,Node * npr);
int tcmp _2p(Node * a, Node * b);      /* forward : Vergleicht Baeume  1 : a>b */


Node var_chain =
{CHAIN,
NULL,
NULL};

Node * chain_pos = & var_chain;

Node * condarg;
BOOLEAN (* condfunc) (Node *);

/* void tprint _2p(Node *,int); */

int i;    /* zum Zwischenspeichern */

Node * rewrite _2a ((term,Baum) , Node * term ,Node * Baum)
{
	DEBG((5,"rewrite : trying Term : "));
	DBFK(5,print(term));
	DEBG((5,", Tree : "));
	DBFK(5,print(Baum));
	DEBG((5,"\n"));

	if (Baum && Baum->type == RULELIST)	/* Regelliste (listmatch.c) */
		return match_list(term,Baum);
	return match(term,Baum);

}

/* 2026: Schrittbegrenzung, damit eine Regelschleife REWR nicht endlos laufen laesst */
long max_rewrite_steps = 100000;
static long rewrite_steps = 0;
static int  rewrite_depth = 0;
static BOOLEAN step_limit_hit = FALSE;

/* 2026: die zuletzt von Regellisten ersetzten Terme und ihre Ergebnisse. Ein
   Ergebnis, von dem die Kette der Ersetzungen wieder zum jetzigen Term fuehrt,
   schliesst einen Zyklus (A -> B -> A) und gilt als kein Fortschritt. */
#define NHIST 16
static Node * hist[NHIST], * hist_to[NHIST];
static int hist_rule[NHIST];
static int hist_pos = 0;

static void hist_clear (void)
{
	int i;
	for (i = 0; i < NHIST; i++)
		{
		delete(hist[i]);
		delete(hist_to[i]);
		hist[i] = hist_to[i] = NULL;
		}
	hist_pos = 0;
}

static void hist_add (Node * t, Node * to, int rule)
{
	delete(hist[hist_pos]);
	delete(hist_to[hist_pos]);
	hist[hist_pos] = term_copy(t);
	hist_to[hist_pos] = term_copy(to);
	hist_rule[hist_pos] = rule;
	hist_pos = (hist_pos + 1) % NHIST;
}

/* the same rule rewrote this term several times recently: a longer cycle */
static BOOLEAN hist_revisit (Node * t, int rule)
{
	int i, n = 0;
	for (i = 0; i < NHIST; i++)
		if (hist[i] && hist_rule[i] == rule && term_equal(hist[i], t)) n++;
	return n >= 3;
}

static BOOLEAN has_subterm (Node * t, Node * s)
{
	if (! t) return FALSE;
	if (term_equal(t, s)) return TRUE;
	if (t->type == SYM_TYPE || t->type == Const) return FALSE;
	return has_subterm(t->l, s) || has_subterm(t->r, s);
}

/* does old -> neu close a cycle? neu was replaced before, and the chain of
 * replacements from there (also of subterms, as in A -> subst(B), B -> A)
 * leads to old. A term that was replaced in another branch (Int(b,x) -> b*x
 * elsewhere) may come up again. */
static BOOLEAN hist_cycle (Node * neu, Node * old)
{
	Node * cur = neu;
	int steps, i;
	for (steps = 0; steps < NHIST; steps++)
		{
		for (i = 0; i < NHIST; i++)
			if (hist[i] && has_subterm(cur, hist[i])) break;
		if (i == NHIST) return FALSE;
		cur = hist_to[i];
		if (has_subterm(cur, old)) return TRUE;
		}
	return FALSE;
}

/* 2026: solution steps. STEPS Alg "file" shows every rule of the rule list
   of Alg that is applied, with a label from the file (lines
   "index<TAB>label<TAB>text", index = position of the rule in the list);
   STEPS Alg "" switches it off. */
static Symbol * steps_alg = NULL;
static char ** steps_label = NULL;
static int steps_n = 0, step_no = 0;

static void steps_clear (void)
{
	int i;
	for (i = 0; i < steps_n; i++) free(steps_label[i]);
	free(steps_label);
	steps_label = NULL;
	steps_n = 0;
}

void steps_fkt (Node * np)
{
	const char * file = name((Symbol *) np->r->r);
	FILE * f;
	char line[8192];
	steps_clear();
	steps_alg = NULL;
	if (! file || ! * file) return;			/* STEPS Alg "": off */
	if (! (f = fopen(file, "r")))
		{
		printfErr("STEPS : cannot read %s\n", file);
		return;
		}
	while (fgets(line, sizeof(line), f))
		{
		char * tab;
		long i = strtol(line, & tab, 10);
		if (tab == line || * tab != '\t' || i < 0 || i > 1000000) continue;
		if (i >= steps_n)
			{
			int n = (int) i + 1, k;
			steps_label = (char **) realloc(steps_label, n * sizeof(char *));
			if (! steps_label) fatal("STEPS : no room");
			for (k = steps_n; k < n; k++) steps_label[k] = NULL;
			steps_n = n;
			}
		line[strcspn(line, "\r\n")] = 0;
		free(steps_label[i]);
		steps_label[i] = strsave(tab + 1);
		}
	fclose(f);
	steps_alg = (Symbol *) np->r->l;
}

static void show_step (int rule, Node * old, Node * neu)
{
	const char * l = (rule >= 0 && rule < steps_n) ? steps_label[rule] : NULL;
	const char * t = l ? strchr(l, '\t') : NULL;
	printfOut("Step %d: ", ++step_no);
	if (l) printfOut("%.*s\n  %s\n  ", (int) (t ? t - l : (int) strlen(l)), l, t ? t + 1 : "");
	else printfOut("rule %d\n  ", rule);
	print(old);
	printfOut("\n    = ");
	print(neu);
	printfOut("\n");
}

void rewrite_begin (void)	/* vor REWR (verschachtelt: nur aussen zuruecksetzen) */
{
	if (rewrite_depth++ == 0)
		{
		step_no = 0;
		rewrite_steps = 0;
		step_limit_hit = FALSE;
		hist_clear();
		}
}

void rewrite_end (void)
{
	if (rewrite_depth > 0) rewrite_depth--;
	if (rewrite_depth == 0) hist_clear();
}

BOOLEAN suche_Stelle _2a ((p_term,Baum), Node * * p_term, Node * Baum)
{
	Node * lt, * rt,* ers ,* maintype;
	BOOLEAN rewritten;

	if (* p_term == NULL || step_limit_hit)
		return FALSE;

	DEBG((4,"\nsuche_Stelle : term : "));
	DBFK(4,print(* p_term));
	DEBG((4,"\n"));

    /* Zuerst lokale terme dann globale */

	do rewritten=(suche_Stelle (&((* p_term) -> l),Baum));
	while (rewritten);
	do rewritten=(suche_Stelle (&((* p_term) -> r),Baum));
	while (rewritten);

	lm_start = 0;
	while ((ers=rewrite(* p_term,Baum)) != (Node *) NULL)
			{
			Node * old = * p_term, * neu;
			int found = lm_last;

				lt = (* p_term) -> l;
				rt = (* p_term) -> r;
				if (RES_DO(ers)) {CALLFUNCT(RES_DO(ers));} /* Ausfueher von DO-Block */
				if (lt && lt->type == SYM_TYPE)
					maintype=rtypes((Symbol *) lt);
				else
					maintype=NULL;
				neu = tcopy(RES_RHS(ers)); /* Formel einsetzen (Es wird auch 'geliftet' !) */
				retype_term(neu);	/* 2026: Varianten zu den Sorten der Argumente (SUBSORT) */
				neu = tcalc(neu);  /* Formel numerisch auswerten */
				if (Baum && Baum->type == RULELIST)
					term_simplify_trivial(& neu);	/* x^0, 1*u, ... wie Mathematica */
				RESTORE;					/* Symboltabelle restaurieren (auch locks beseitigen)*/
				/* 2026: in einer Regelliste wird eine Regel ohne Fortschritt
				   (Ergebnis gleich dem Term) uebersprungen; die naechste wird versucht */
				if (Baum && Baum->type == RULELIST
				    && (term_equal(neu, old) || term_has_nan(neu) || hist_cycle(neu, old)
				        || hist_revisit(old, found)))
					{
					DEBG((2,"REWR: rule %d makes no progress or gives NaN, skipped\n", found));
					delete(neu);
					lm_start = found + 1;
					continue;
					}
				if (Baum && Baum->type == RULELIST)
					hist_add(old, neu, found);
				if (steps_alg && Baum && Baum == atypes(steps_alg))
					show_step(found, old, neu);
				DEBG((2,"REWR: "));
				DBFK(2,print(old));
				* p_term = neu;
				delete (lt);
				delete (rt);
				if (old->type != SYM_TYPE)
					delnod(old);  /* ersetzter Knoten (Kinder sind schon geloescht) */
				else
					delete(old);  /* gibt nur Zahlen frei */
				DEBG((2," -> "));
				DBFK(2,print(*p_term));
				DEBG((2,"\n"));
				didrewrite = TRUE; /* wurde umgeschrieben */
				if (++rewrite_steps > max_rewrite_steps && ! step_limit_hit)
					{
					step_limit_hit = TRUE;
					printfErr("REWR : step limit (%ld rewrites) reached, the result is not complete\n",
					          max_rewrite_steps);
					}
				return TRUE;
			}
	RESTORE;					/* Symboltabelle restaurieren */
	lm_start = 0;

	return FALSE;

}

Node * solve _2a ((term,alglist), Node * term ,Node * alglist)
{
	int rewritten;
	Node  * Baum;
	Node  * algpt;
	BOOLEAN wasbefore;

	if(!alglist) return term; /* Leere Algebra (ohne SPEC) */

	if (alglist -> type == Alg)
		{
		wasbefore = didrewrite;
		do 
		{
		didrewrite = FALSE;
		term = solve(term,(alglist->l));
		if (didrewrite) wasbefore = TRUE;
		}
		while (didrewrite);
		didrewrite = wasbefore;
		return term;
		}

	if (alglist -> type == Algs)  /* Hier liegt eine Liste vor ! */
		{
		for (algpt=alglist; algpt != NULL; algpt = algpt -> r)
			{
			if (algpt->l->type == Alg) /* algpt -> l ist Alg2 ,hier : Verkettung */
				term = solve(term,(algpt->l));
			else
				term = solve(term,atypes((Symbol *)(algpt->l)));

			DEBG((1,"Alg: "));
			DBFK(1,print(algpt->l));
			DEBG((1,"Term: "));
			DBFK(1,print(term));
			DEBG((1,"\n"));
			}

		return term;
		}

	Baum=alglist;

	chain_pos = & var_chain;
	do rewritten=(suche_Stelle (&term,Baum));
	while (rewritten);


	return tcalc(term);  /* Formel numerisch auswerten und zurueckgeben */
}


void print _1a((np),Node * np)
{
	tprint(np,0);
}

void tprint _2a((np,last_func_type),Node * np,int last_func_type)
{
int	this_type;					/* Da La1 .. La5 als Func im Baum eingtragen ! */

	if (! np)	return;
	this_type = (np -> type);

	switch(this_type)
	{
	case Cond2 :
		printfOut("Cond2 ");
		if (COND_ARG(COND2_COND(np)) != (Node *) NULL)
			{printfOut("( ");
			tprint(COND_ARG(COND2_COND(np)),0);
  		printfOut(") ");
			}
		printfOut(", ");
		tprint(np ->r,0);
		break;

	case OR_TYPE :
		printfOut("( ");
		tprint(np ->l,0);
		printfOut(") OR (");
		tprint(np ->r,0);
		printfOut(") ");
		break;

	case ERSETZ_TYPE :
		printfOut("( ");
		tprint(np ->l,0);
		printfOut(") = (");
		tprint(np ->r,0);
		printfOut(") ");
		break;

	case SYM_TYPE :
		if (lexval((Symbol *) np) == Term)
			tprint(np->l,last_func_type); /* letzter Typ */
		else
			if ((lexval((Symbol *) np) == Const)
				&& (hasval(np) == TRUE)) 
				{
				if (rtypes((Symbol *) np) == NULL)
					fatal("run.c : tprint no rtypes given for Symbol");

				if (NULL==(void *) show(rtypes((Symbol *) np)))
         		printfOut("%g ",* ((double *) value(np)));
				else
          SHOWNUM(np,value(np));            /* Wert ausgeben */
				}
			else    /* sonst Namen */
      	    printfOut("%s ",name((Symbol *) np) );
      break;
	case Var :
		printfOut("-Fehler : Hier tritt 'Var' auf ! -");
		break;
	case Const :
		tprint(np -> l,0);			/* Symboltabelleneintrag */
		break;
	case Func :
		if (lexval((Symbol *) (np -> l)) == Func)
			{
			tprint(np -> l,0);		/* Name der Funktion ausgeben */
			printfOut("(");
			tprint(np -> r,0);
			printfOut(")");
			return;
			}
		else 
			this_type = lexval((Symbol *) (np->l));
	case Ru:											/* Im Baum als Func eingetragen ! */
		if (lexval((Symbol *) (np -> l)) == Ru)
			{
			if (last_func_type > this_type)
				printfOut("(");
			tprint(np -> r,this_type);
			if (last_func_type > this_type)
				printfOut(")");
			tprint(np -> l,0);		/* Name der Funktion ausgeben */
			return;
			}
		/* else			; */

	case Bra:
	case Bra1:
		if ((lexval((Symbol *) (np -> l)) == Bra)
		 || (lexval((Symbol *) (np -> l)) == Bra1))
			{
			tprint(np -> l,0);		/* Name der Funktion (Klammer auf) ausgeben */
			tprint(np -> r,0);              /* Inhalt dazwischen ausgeben */
			tprint((Node *) (((Symbol *)(np -> l))->klammer),0); /* andere Klammer */
			return;
			}
		/* else			; */
	case Ra:							/* Im Baum als Func eingetragen ! */
	case La1:
	case La2:
	case La3:
	case La4:
	case La5:						/* Gleich od. Staerker -> Keine Klammern */

		DEBG((9,"-Vorrang : %d -",this_type));
		if (last_func_type > this_type)
			printfOut("(");

			/* Bei einem Argument : Linksunaer sonst wie Linksassoziativ */
			if (term_nargs(np) == 1) /* -> Ein Argument -> Links-unaer */
				{
				tprint((Node *) TERM_HEAD(np),0);		/* Name der Funktion ausgeben */
				tprint(term_arg(np,0),this_type+1); /* Bei gleichem Vorrang Argument-Term klammern z.B. -(1-2) */
				}
			else /* links Op. rechts */
				{
				if (lexval(TERM_HEAD(np)) == Ra) /* Rechts-assoziativ */
					{
					tprint(term_arg(np,0),this_type+1);  	/* Linker Teilbaum muss bei gleichem Vorrang geklammert werden : a-(b+c) */
					tprint((Node *) TERM_HEAD(np),0);			/* Name der Funktion ausgeben */
					tprint(term_arg(np,1),this_type);
					}
				else 																	/* Links-assoziativ */
					{
					tprint(term_arg(np,0),this_type);
					tprint((Node *) TERM_HEAD(np),0);			/* Name der Funktion ausgeben */
					tprint(term_arg(np,1),this_type + 1); /* Rechter Teilbaum muss bei gleichem Vorrang geklammert werden : a-(b+c) */
					}
				}

		if (last_func_type > this_type)
			printfOut(")");
		break;
	case Terms:
	case Forms:
		tprint(np -> l,0);
		if (np -> r)
			{
			printfOut(",");
			tprint(np -> r,0);
			}
		break;
	case Form:
		tprint(np ->l,0);
		printfOut(" = ");
		tprint(np ->r,0);
		break;
	case FUNC:
		printfOut("INSTR. (");
		tprint(np ->r,0);
		printfOut(")");
		break;
	case Cond:
		printfOut("Condition (");
		tprint(np ->r,0);
		printfOut(")");
		break;
	default :
		tprint(np->l,0);
		tprint(np->r,0);
		break;
	}
	return;
}

/* Liste aus rec_build_list (defs.c) freigeben. Ihre SYM_TYPE-Knoten sind
 * keine Symbole, sondern Knoten mit (Adresse, Symbol) und duerfen nicht
 * wie Symbole behandelt werden. */
static void delete_locals_list (Node * p)
{
	if (! p) return;
	if (p->type == PARAM)
		{
		delete_locals_list(p->l);
		delete_locals_list(p->r);
		}
	delnod(p);
}

void delete _1a ((p), Node * p)
{
	void set_locals_seq (Node * np);
	void declare (Node * np);
	if (p)
		{
		if (((p -> type) == FUNC) && ((p->l) == (Node *) declare) && p->r)
			{ /* FUNC declare ( lexv ( Idlist, hasv ( rtypes, atypes ) ) )
			   * Der hasv-Knoten hat als Typ TRUE/FALSE (FALSE == SYM_TYPE !).
			   * rtypes/atypes gehoeren jetzt den deklarierten Symbolen. */
			if (DECL_HASVNODE(p))
				delnod(DECL_HASVNODE(p));
			delete(DECL_IDLIST(p));
			delnod(DECL_LEXNODE(p));
			delnod(p);
			return;
			}
		if (((p -> type) == FUNC) && ((p->l) == (Node *) set_locals_seq))
			{ /* FUNC set_locals_seq ( PARAM ( Liste, Anweisung ) ) */
			delete_locals_list(LOCALS_LIST(p));
			delete(LOCALS_INSTR(p));
			delnod(p->r);
			delnod(p);
			return;
			}
		if ( ((p -> type) == Cond)
		  || ((p -> type) == FUNC))
			{
			/* Frueher wurden die Terme von printterm und termassign hier nicht
			 * geloescht. % und Term-Variablen speichern aber Kopien (tcopy in
			 * termassign2), daher koennen die Terme geloescht werden. */
			delete(p->r); /* nicht die Funktion zestoeren ! */

			delnod(p);
			p = NULL;
			}
		else if ((p -> type) != SYM_TYPE)
				{
				delete(p -> l), delete(p -> r);
				delnod(p);
				p = NULL;
				}
		  else
				{
				if (name((Symbol *) p) == numbername) /* -> ist Number */
					delnum((Symbol *) p,TRUE); /* value auch loeschen */
				}
		}
	return;
}


/* Condition-Funktionen */

BOOLEAN truefunc _1a((np),Node * np)
{
	return TRUE;
}



BOOLEAN in_tree _1a((np),Node * np)
{
	return in_tree2 (np->l,np->r);
}


BOOLEAN in_tree2 _2a((npl,npr),Node * npl,Node * npr)
{
Node * npre = npr;

	if (npr == NULL) return FALSE;

	DEBG((4,"func in_tree2 ( "));
	DBFK(4,print(npl));
	DEBG((4,", "));
	DBFK(4,print(npr));
	DEBG((4," )\n"));

	if (npr->type != Terms)
		{
		if (testrewrite(npre,npl) == TRUE)
			{
			return TRUE;
			}
		/* nicht Symboltabelle restaurieren !! Variablen werden speater ersetzt ,und dort wird restauriert ! */
		}

		DEBG((4," end in_tree2 \n"));

	return (in_tree2(npl,npr->l) || in_tree2(npl,npr->r));

}

BOOLEAN not_in_tree _1a ((np),Node * np)
{
	DEBG((4,"func not in_tree2 , "));
	return ! in_tree(np);
}

BOOLEAN isnt_zero (Node * np)
{ Node * erg1;
	double val;
  BOOLEAN iszero=FALSE;
	erg1=calkulate (np);
	if (! erg1)
		return FALSE;	/* nicht berechenbar (z.B. symbolisch): Bedingung gilt nicht */
	/* if (rtypes((Symbol *) erg1) != numbertype)
		fprintf(stderr,"ERROR -- Condition with non calculatable type !\n");
	else */

		{
		if (! num_to_double((Symbol *) erg1, & val))	/* 2026: auch integer, rational */
			val=(* ((double *) value((Symbol *) erg1)));
		iszero=(val==0.0);
		}
	delete (erg1);
	return (! iszero);
}

BOOLEAN lower_between _1a((np),Node * np)
{
	int rtw;
	DEBG((4,"func lower_between ( "));
	DBFK(4,print(np));
	DEBG((4," )\n"));

	rtw= (tcmp(np->l,np->r) > 0) ? TRUE : FALSE;

	DEBG((4,"lower_between rt: %d\n",rtw));
	return rtw;
}

int tcmp _2a((a,b), Node * a, Node * b) /* Vergleicht Baeume  1 : a>b */
{													 /* 0  : a == b */
int rtn;									 /* -1 : a < b */

if (a == b)						 		 /* auch NULL !! */	
	return 0;
if (a == NULL)
	return -1;
if (b == NULL)
	return  1;

DEBG((4,"tcmp ( "));
DBFK(4,print(a));
DEBG((4," und "));
DBFK(4,print(b));
DEBG((4," )\n"));

if (a->type == SYM_TYPE)
	if (b->type == SYM_TYPE)
		{
		DEBG((4,".. both Symbols\n"));
		if (hasval((Symbol *) a))
			if (hasval((Symbol *) b))
				if (rtypes((Symbol *) a) == rtypes((Symbol *) b))
					if (IS_FUNCTION(lexval((Symbol *) a)))
					 if (IS_FUNCTION(lexval((Symbol *) b)))
					  return strcmp(name((Symbol *) a),name((Symbol *) b));	
					 else return 1;
					else if (IS_FUNCTION(lexval((Symbol *) b)))
					   return -1;
				   	else
			 		return CMPNUM(a,value(a),value(b));
				else
					return strcmp(name((Symbol *) rtypes((Symbol *) a)) ,name((Symbol *) rtypes((Symbol *) b)));
	  		else
	    		return -1; /* a Num ,b nicht */
		else
			if (hasval((Symbol *) b))
	    		return 1; /* b Num ,a nicht */
			else
				{
				rtn=strcmp(name((Symbol *) a),name((Symbol *) b)); /* Namen vergl. */
				DEBG((4,".. comparing Names : %s , %s : %d\n",name((Symbol *) a),name((Symbol *) b),rtn));
				return rtn;
				}
		}
	else
		return -1;
else
	if (b->type == SYM_TYPE)
		return 1;
	else
		{
		if ((rtn=tcmp(a->l,b->l)) == 0) /* erst Fkt.Namen dann Argumente */
			return tcmp(a->r,b->r);
		else
			{
			DEBG((4,".. left tree was %d\n",rtn));
			return rtn;
			}
		}

}

void set_numbertype (Node * np)
{	Node * nt=np->r;
		numbertype = nt;
}

Node * get_numbertype (void)
{
return numbertype; 
}


/* 2026: deklarierte Sorte des i-ten Arguments einer Funktion (NULL: unbekannt) */
static Node * param_sort (Symbol * f, int i)
{
	Node * a = atypes(f);
	int k;
	if (! a) return NULL;
	if (a->type == VARPAR)
		{
		a = a->l;
		for (k = 0; k < i && a->r != NULL; k++) a = a->r;
		return (a->r != NULL) ? a->l : a;
		}
	for (k = 0; k < i; k++)
		{
		if (a->r == NULL) return NULL;
		a = a->r;
		}
	return (a->r != NULL) ? a->l : a;
}

static Symbol * lastsym = NULL;	/* Symbol mit der Sorte des letzten Werts von realcalk */

void * realcalk(Node * term,int * perr)
{
	Node * lterm;
	void * erg; /* Ergebnisse der Teilbaeume */

	DEBG((5,"realcalk : "));
	DBFK(5,print(term));
	DEBG((5,"\n"));

  if (term->type == SYM_TYPE)
		{
		if ((hasval(term)) && lexval((Symbol *) term)==Const)
			{
			lastsym = (Symbol *) term;
			return CPYNUM(term,value(term));
			}
		if (lexval((Symbol *) term) == Term) /* ersetzter Term ? */
			if (term->l) 
				return realcalk(term->l,perr);
		
		* perr = TRUE; /* Z.B. VAR */
		return NULL;
		}

	if (term->type == Func && builtin(term->l))	/* symbolische C-Funktion (symfkt.c) */
		{
		Node * res = call_builtin(term);
		void * v = NULL;
		if (res)
			{
			v = realcalk(res, perr);
			/* 2026: der Wert hat die Sorte des Ergebnisses (z.B. rational); fuer
			   den Aufrufer muss er die deklarierte Sorte der Funktion haben */
			if (! * perr && v && rtypes(lastsym) != rtypes(TERM_HEAD(term)))
				{
				Node * from = rtypes(lastsym), * to = rtypes(TERM_HEAD(term));
				void * w = (sort_dist(from, to) > 0) ? sort_convert(v, from, to) : NULL;
				((void (*) (void *)) del(from)) (v);
				v = w;
				if (! v) * perr = TRUE;
				}
			delete(res);
			}
		else
			* perr = TRUE;
		lastsym = TERM_HEAD(term);	/* fuer DELNUM: Sorte des Ergebnisses */
		return * perr ? NULL : v;
		}

  if (!hasval(term->l) || exe_always(term->l))  /* Symbol der Funktion */
		{
		if (exe_always(term->l) && (term->type == Func)) /* benutzerdef. Fkt. */
			{ Node * lterm;
			if ((lterm=exe_function(term)) != NULL)
				return realcalk(lterm,perr);
			}

		* perr = TRUE;       /* Funktion nicht berechenbar oder Konstante ohne Wert */
		DEBG((5,"realcalk: found not calkulable symbol : "));
		DBFK(5,print(term));
		DEBG((5,"\n"));
		return NULL;
		}

	if (term->type == Const) /***/
		{
		lastsym = (Symbol *) term->l;
		return CPYNUM(term->l,value(term->l));
		}

	/* --------------------------- Bis hier auf beliebiger Num Const */

	/* if (term -> type == SYM_TYPE)	lastsym=term,return value(term); */

	/* Ab jetzt ist es eine Numerische Fkt. */

	if (term->type != Func) 
		{
		printf("--- Internal Error run.c expected Funct got : ");
		print(term);
		fatal("\n");
		}


	if (* perr) 
		return (void *) NULL;

	lterm=TERM_ARGS(term);

	{
	void * feld[MAXARGS];
	Symbol * syms[MAXARGS];
	Node * conv[MAXARGS];		/* 2026: Sorte nach Erweiterung (SUBSORT), sonst NULL */
	int i=0,j;

	for ( ; lterm; lterm = ARGS_NEXT(lterm))
		{
		Node * want;
		feld[i]=realcalk(ARGS_ITEM(lterm),perr);/* Const oder Funct */
		syms[i]=lastsym;
		conv[i]=NULL;
		/* 2026: Wert einer Untersorte in die deklarierte Sorte umwandeln */
		if (! * perr && feld[i] && (want = param_sort(TERM_HEAD(term), i)) != NULL
		    && want != rtypes(syms[i]) && sort_dist(rtypes(syms[i]), want) > 0)
			{
			void * w = sort_convert(feld[i], rtypes(syms[i]), want);
			if (w)
				{
				DELNUM(syms[i],feld[i]);
				feld[i] = w;
				conv[i] = want;
				}
			}
		i++;
		if (i > MAXARGS-2) fatal("Fatal Error run.c : Too max Arguments for Function !");
		if (* perr)
			break;
		}
	if (!(* perr))
		{
		feld[i] = NULL; /* Ende (bei variabel Argumenten) kennzeichnen */
		lastsym = TERM_HEAD(term);
		erg= ((void * (*) (void * [])) value(TERM_HEAD(term)))(feld); /* Aufruf der Benutzerfunktion */
		if (erg == NULL)	/* 2026: kein Ergebnis (z.B. exakte Division durch 0) */
			* perr = TRUE;
		}

	for (j=0;j<i;j++)
		{
		if (((Node *) syms[j])->type != SYM_TYPE)
			 fatal("run.c : Not a Symbol to delete !! j: %d, type: %d\n",j,((Node *) syms[j])->type);
		if (feld[j] && conv[j])	/* umgewandelter Wert */
			((void (*) (void *)) del(conv[j])) (feld[j]);
		else if (feld[j])  /* bei Fehler (perr) ist der Wert NULL: nichts freizugeben */
			DELNUM(syms[j],feld[j]);
		}
	}

	if (!(* perr))
		return erg;
	else
		return (void *) NULL;
}

void functions_execute(Node * np) /* Achtung es wird im Baum geaendert ! Voellig FALSCH (for-schleife ..) !!!!! */
{
if (! np) return;

if (np ->type != Func)
	{functions_execute(np->l);functions_execute(np->r);}
else
	if (exe_always(np->l))
		{ Node * lterm;
		if (! (lterm=exe_function(np)))
			return;
		else
			{ /* In dem aktuellem Baum Ergebnis eintragen */
			delete(np->r);
			delete(np->l);
			if (TERM_CONTENT(lterm)->type == SYM_TYPE) fatal ("run.h fatal internal TYPE ERROR ! ");

			np->type=TERM_CONTENT(lterm)->type;  /* Ueberschreiben des Func-Knoten -> Transparent nach aussen */
			np->r = tcopy(TERM_CONTENT(lterm)->r);
			np->l = tcopy(TERM_CONTENT(lterm)->l);

			functions_execute(np); /* Im Return-Wert suchen */
			return;
			}
		}
	else
		functions_execute(np->r); /* In Argumenten suchen */
return;
}

Node * calkulate (Node * term) /* bekommt Zeiger auf kalkulierbare Fkt */
{
	Symbol * sp;
	int error = FALSE;
	void * erg;

	DEBG((4,"calkulate : "));
	DBFK(4,print(term));
	DEBG((4,"\n"));

	/* functions_execute(term);  aendert im Baum ! */

	erg=realcalk(term,&error);

#ifdef DEBUG
	DEBG((4,"calkulate : realcalk : "));
	if (error== TRUE)
		DEBG((4,"Term not calkulable \n"));
	else
		DEBG((4,"calkulated Term \n"));
#endif

	if (error==TRUE) return NULL;
	else
		{

			if ((term->type == Const)
				|| (term->type == Func))
				{
				sp=mknum(erg,rtypes((Symbol *) (term->l)));

				rtypes(sp)=rtypes((Symbol *)(term->l)); /* Resultattyp der Fkt. */
				}
			else
				{
				sp=mknum(erg,rtypes((Symbol *) term));

				if ((term->type == SYM_TYPE) && (lexval((Symbol *)term) == Term))
					{
					/* 2026: ein Wert einer Untersorte (z.B. integer in einem
					   real-Term) behaelt seine Sorte */
					if (lastsym && rtypes(lastsym) != rtypes((Symbol *) term)
					    && sort_dist(rtypes(lastsym), rtypes((Symbol *) term)) > 0)
						rtypes(sp)=rtypes(lastsym);
					else
						rtypes(sp)=rtypes((Symbol *) term);
					}
				else
					{
					printfOut("calkulate : Internal ERROR : unexpected term-type : ");
					print(term);
					printfOut("  Typenr. : %d\n",term->type);
					delnum(sp,TRUE); /* Wert gehoert der Zahl */
					return NULL;
					}
				}
		DEBG((4,"calculate returned : "));
		DBFK(4,print((Node *) sp));
		DEBG((4,"\n"));
		return (Node *) sp;
		}
}


Node * tcalc (Node * term)   /* Traversiert Baum und berechnet */
{
if (! term)
	return NULL;
term->l = tcalc(term->l);
term->r = tcalc(term->r);

if ((term -> type) == Func && ! builtin(term->l))
	retype_node(term);	/* 2026: Argumente koennen jetzt exakte Zahlen sein (SUBSORT) */

if ((term -> type) == Func && builtin(term->l))  /* symbolische C-Funktion (symfkt.c) */
	{
	Node * res = call_builtin(term);
	if (res)
		{
		delete(term);
		return tcalc(res);
		}
	return term;	/* nicht anwendbar */
	}

if  ((term -> type) == Func) /* Rest wird darauf abgebildet */
	{
	Symbol * sp = (Symbol *) calkulate(term);

	if (sp==(Symbol *) NULL) 
		return term;
	else
		{
		DEBG((4,"- tcalc did numerics : funct : "));
		DBFK(4,print(term));
		DEBG((4," => "));
		DBFK(4,print((Node *) sp));
		DEBG((4," \n"));

		delete(term);
		return mknod(Const,(Node *) sp,NULL);
		}
	}
return term;
}

/* ---- Argumente von Func-Knoten (siehe nodes.h) ---- */

int term_nargs (Node * t)
{
	int n = 0;
	Node * a;
	if (! t) return 0;
	for (a = TERM_ARGS(t); a; a = ARGS_NEXT(a))
		n++;
	return n;
}

Node ** term_argp (Node * t, int i)
{
	Node ** pp;
	if (! t || ! TERM_ARGS(t) || i < 0) return NULL;
	pp = & TERM_ARGS(t);
	while ((* pp)->type == Terms)
		{
		if (i == 0) return & (* pp)->l;
		i--;
		pp = & (* pp)->r;
		}
	return (i == 0) ? pp : NULL;  /* letztes Argument steht direkt im r */
}

Node * term_arg (Node * t, int i)
{
	Node ** pp = term_argp(t, i);
	return pp ? * pp : NULL;
}

Node * tcopy _1a ((term), Node * term)
{
Symbol * sp;

if (term==NULL)
	return NULL;

if (term->type == SYM_TYPE)
	{
	if (lexval((Symbol *) term) == Term) /* Term ersetzen */
		return tcopy(term->l);

	if ((hasval((Symbol *) term)) && lexval((Symbol *) term)==Const)
		{
		return (Node *) mknum(CPYNUM(term,value(term)),rtypes((Symbol *) term));
		}

	if (IS_FUNCTION(lexval((Symbol *) term))
			|| (lexval((Symbol *) term) == Const))  /*  'liften' */
		{Symbol * sp2=(Symbol *) term,* spnew, * spold=NULL;
		while((sp=IS_Verbindung(rtypes(sp2))) != NULL)  /* IS_VERB. wird beim analysieren des linken Teils der Formel gesetzt */
			{
			if (sp == spold) break; /* laeuft im Kreis */
			spold=sp;

			DEBG((4,"lift : "));
			DBFK(4,print((Node *) sp));
			DEBG((4,", "));
			DBFK(4,print((Node *) rtypes(sp)));
			DEBG((4,"\n"));
			if ((spnew=IS_search(sp,sp2)) == NULL) break;
			sp2=spnew;
			}
		return (Node *) sp2;
		}

	return term; /* Zeiger auf Symbol */
	}

return mknod(term->type,tcopy(term->l),tcopy(term->r));
}
