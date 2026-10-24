/*
 *	defs.c V1.00
 *	Copyright (c)  Rainer Heintzmann (1993)
 *
 */

#include <stdlib.h> /* free */
#include "inout.h"
#include "sym.h"
#include "node.h"
#include "defs.h"
#include "forms.h"
#include "syn.h"
#include "run.h"
#include "sync.h"
#include "nodes.h"
#include "expand.h"


static Symbol ReturnTerm =
{
{
SYM_TYPE,
NULL,
NULL},
"ReturnTerm",
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
0 /* global (wird geaendert) */
};

static Symbol * returnterm =  & ReturnTerm; /* speichert letzten term zwischen */
static int blockstufe=0;	/* wird von sync.c bei Fehlern auf Null gesetzt */
static int running   =0;	/* Wird gerade ein statement ausgefuert ? */
static int blockbase =0;	/* Blockstufe, auf der ein per INC gelesenes File "Top-Level" ist */

#define MAXBLOCKS 250

Node * local[MAXBLOCKS]; /* Kette lokaler Symbole */

static BOOLEAN dont_protect[MAXBLOCKS]; /* mit FALSE initialisiert */

static BOOLEAN never_protect; /* In Funktionsaufruf kein protect */

static BOOLEAN in_definition=0; /* In Funktionsaufruf kein protect */

static Node * globalArglist=NULL; /* fuer direktes Zuweisen von Parametern */

static Node * globalRtw = NULL; /* Return-Wert von Funktionen */

/* Funktionen zum Blockhandling :   */

static Symbol * save_local_run(Symbol * sp)  /* zur Laufzeit andere Reihenfolge ! */
{
	Symbol * ns;
	Node * vp;

	DEBG((15,"save_local_run\n"));

	if (! blockstufe) return sp;
	for (vp=local[blockstufe];vp != NULL;vp=vp->r) /* schon mal definiert ? */
		if (sp==(Symbol *) vp->l)	return oldvals(sp);

	ns=mksym(Id,name(sp));           /* jetzt frei fuer bel. Definitionen */
	defined_in_block(ns)=blockstufe;
	oldvals(ns)=oldvals(sp);
	oldvals(sp)=ns;
	local[blockstufe]=mknod(Id,(Node *) sp,local[blockstufe]);	
	DEBG((15,"save_local_run_end\n"));
	return ns;
}

static Symbol * save_local(Symbol * sp)
{
	Symbol * ns;
	Node * vp;

	DEBG((15,"save_local\n"));

	if (blockstufe <= blockbase) return sp; /* Top-Level (auch in INC-Files): global definieren */
	if (running) return save_local_run(sp); /* Zur Laufzeit anderes Verfahren ! */

	for (vp=local[blockstufe];vp != NULL;vp=vp->r)
		if (sp==(Symbol *) vp->l)	return sp;

	ns=clonesym(sp);
	oldvals(sp)=ns;
	lexval(sp)=Id; /* jetzt frei fuer bel. Definitionen */
	local[blockstufe]=mknod(Id,(Node *) sp,local[blockstufe]);	
	DEBG((15,"save_local_end\n"));
	return sp;
}

/* Laufzeit-Kopie eines lokalen Symbols (aus save_local_run) freigeben:
 * Name (strsave in mksym), Zahlenwert und gespeicherter Term gehoeren ihr. */
static void free_local_sym(Symbol * sp)
{
	if (lexval(sp) == Const && hasval(sp) && value(sp)
	    && rtypes(sp) && del((Symbol *) rtypes(sp)))
		DELNUM(sp,value(sp));
	else if (lexval(sp) == Term)
		delete(sp->node.l);
	free(name(sp));
	delsym(sp);
}

static void restore_locals_run(void) /* zur Laufzeit andere Reihenfolge ! */
{
	Node * vp,* op;
	Symbol * sp,* sp2;

	DEBG((20,"restore_locals_run\n"));

	for (vp=local[blockstufe];vp != NULL;)
		{
		DEBG((20,"restore_local_1\n"));
		sp=(Symbol *) vp->l;
		sp2=oldvals(sp);
		oldvals(sp)=oldvals(sp2);
		free_local_sym(sp2);
		op=vp;
		vp=vp->r;
		delnod(op);
		DEBG((20,"restore_locals_run_2\n"));
		}
	local[blockstufe]=NULL;
}

static void restore_locals(void)
{
	Node * vp,* op;
	Symbol * sp,* sp2;

	DEBG((20,"restore_local\n"));
	if (running) 
		{
		restore_locals_run(); /* Zur Laufzeit anderes Verfahren ! */
		return;
		}

	for (vp=local[blockstufe];vp != NULL;)
		{
		DEBG((20,"restore_local_1\n"));
		sp=(Symbol *) vp->l;
		sp2=oldvals(sp);
		{
		char * keep = name(sp); /* sp behaelt seinen eigenen Namen */
		cpysym(sp2,sp);
		name(sp) = keep;
		}
		free(name(sp2));        /* Kopie des Namens aus clonesym */
		delsym(sp2);
		op=vp;
		vp=vp->r;
		delnod(op);
		DEBG((20,"restore_local_2\n"));
		}
	local[blockstufe]=NULL;
}

/* weitere Functs */

void specials(Symbol * sp, int lexv)
{
	switch (lexv)
		{
		case Sort :			value(sp) = NULL;
										IS_Verbindung(sp) = NULL;
										IS_kette(sp) = NULL;
										show(sp)  = (void *) std_show_real; /* show-Fkt. */
										cmp(sp)  = (Node *) std_cmp_real;
										cpy(sp)  = (Node *) std_cpy_real;
										del(sp)  = (Symbol *) std_del_real;
										break;
		case Bra :
										klammer(sp) = sp; /* mit sich selbst */
										kette(sp) = NULL;
										break;			
		default : break;
		}

}

void protectAtall (void) /* fuer declare-argumente */
{
never_protect=FALSE;
}

void protect (void) /* fuer declare-argumente */
{
dont_protect[blockstufe]=FALSE;
}

void no_protectAtall (void)
{
never_protect=TRUE;
}

void no_protect (void)
{
dont_protect[blockstufe]=TRUE;
}

Symbol * declaresym(Symbol * sp,Node * rtps,Node * atps,int lexv,int hasv)
{
	sp=save_local(sp);
	if (lexval(sp) != Id)
		{if (lexval(sp) != lexv)
     	  printfErr("warning : %s was previosly defined to be a : %s !\n",name(sp),type(sp));
		 if ((lexv != Sort) && (rtypes(sp) != rtps))
     	  printfErr("warning : %s was previosly defined to be of type %s !\n",name(sp),name((Symbol *) rtypes(sp)));
		}
	lexval(sp) = (lexv);
	if (lexval(sp) != Sort) delete(atypes(sp));
	rtypes(sp) = (Node *)(rtps);
	atypes(sp) = (Node *)(atps);
	kette(sp)  = NULL;
  hasval(sp) = (hasv);
	specials(sp,lexv);
	if (in_definition)
		{
		Node * np=globalArglist;
		if (! globalArglist)
			{
			printfErr("error : no argument given for %s !\n",name(sp));
			return sp;
			}
		DEBG((15,"declare_sym : "));
		DBFK(15, print(np));
		DEBG((15,"\n"));
		np=ARGS_ITEM(np);  /* aktuelles Argument */
		switch (lexv)
			{
				case Const : numassign2(np,sp);
										globalArglist=ARGS_NEXT(globalArglist);
										break;
				case Term : termassign2((Node *) sp,np);
										globalArglist=ARGS_NEXT(globalArglist);
										break;
				case Func : /* Funktionen zu weisen */
				case Bra  :
				case Bra1 :
				case Ra   :
				case Ru   :
				case La1  :
				case La2  :
				case La3  :
				case La4  :
				case La5  : if (np->type != Func) printfErr("error : %s could not be assigned (no function) !\n",name(sp));
										else
											{
											Symbol * sp2=TERM_HEAD(np);
											hasval(sp)=hasval(sp2);
											value(sp)=value(sp2);
											exe_always(sp)=exe_always(sp2);
											globalArglist=ARGS_NEXT(globalArglist);
											}
										break;
				default : printfErr("error : %s has no assignable type !\n",name(sp));
									break;
			}
		}
	return sp;
}

void declare (Node * np) /* Idlist,lexv,rtps,atps,hasv */
{
	Node * Idlist= DECL_IDLIST(np),
       * rtps  = DECL_RTYPES(np),
       * atps  = DECL_ATYPES(np),
       * mynp;
	Symbol * sp;
  int  lexv  = DECL_LEXV(np),
       hasv  = DECL_HASV(np);

	DEBG((4,"def.c : declare \n"));

	for (mynp=Idlist;mynp->type == Id;mynp=mynp->r)
		{	sp = (Symbol *) mynp->l;
			sp = declaresym(sp,rtps,atps,lexv,hasv);
		}
	sp = (Symbol *) mynp;
	sp = declaresym(sp,rtps,atps,lexv,hasv);

	/* Nur auf Top-Level neutralisieren: dort wird die Zeile nach dem Ausfuehren geloescht.
	 * In Bloecken (Schleifen, Funktionen, INC in Bloecken) muss die Definition
	 * bei jedem Durchlauf erneut ausgefuehrt werden koennen. */
	if (blockstufe <= blockbase)
		{
		DECL_LEXV(np)=PARAM;   /* vorher lexval */
		DECL_HASV(np)=PARAM;   /* vorher hasval */
		DECL_ATYPES(np)= NULL; /* atypes nicht loeschen ! */
		DECL_RTYPES(np)= NULL;
		}

	if (lexv != Sort)
		DEBG((4,"def.c : declare rtypes(sp) = %s\n","Error")); // name((Symbol *) rtypes(sp))));
	else
		DEBG((4,"def.c : declared Sort\n"));
}

void set_brackets (Node * np)
{
klammer((Symbol *) BRK_OPEN(np)) = ((Symbol *) BRK_CLOSE(np));
klammer((Symbol *) BRK_CLOSE(np)) = NULL;
}

void other_fkt (Node * np)
{
	Symbol * sp   = (Symbol *) OTHER_SYM(np),* newsym, * hilf;
  Node * vsortl = OTHER_SORTS(np),
       * sort   = OTHER_RTYPE(np),
       * att    = OTHER_ATT(np);

  newsym=mksym(lexval(sp),name(sp));
	atypes(newsym)=vsortl;
	rtypes(newsym)=sort;
	kette(newsym)=sp; /* Im Kreis verkettet */
	for (hilf=sp;(kette(hilf)!= (Symbol *) NULL) && (kette(hilf) != sp);hilf=kette(hilf))
				; /* Kein Schleifenkoerper */
	kette(hilf)=newsym;  /* Verketten der Funktionen */
	urs_fkt(newsym)=sp;
	if (att)
		if (att->type==ATT)
			{
			hasval(newsym) = TRUE;
			value(newsym)  = ATT_CFUNC(att);
			builtin(newsym) = (att->r != NULL);	/* symbolische C-Funktion */
			}
		else /* PARAM */
			{
			value(newsym) = att;
			exe_always(newsym) =TRUE;
			hasval(newsym) = TRUE;
			}
	OTHER_ATT(np)   = NULL;
	OTHER_RTYPE(np) = NULL; /* atypes nicht loeschen */
	OTHER_SORTS(np) = NULL;
}


void att_fkt (Node * np)
{
	Symbol * sp  = (Symbol *) ATTF_SYM(np);
  Node   * ufk = ATTF_ATT(np);

	kette(sp) = NULL;
	urs_fkt(sp)= sp;
	if (ufk)
		if (ufk->type == ATT) /* USERfkt. */
			{value(sp)  = ATT_CFUNC(ufk);
			hasval(sp) = TRUE;
			builtin(sp) = (ufk->r != NULL);}	/* symbolische C-Funktion */
		else /* PARAM */
			{
			value(sp) =ufk;
			exe_always(sp) =TRUE;
			hasval(sp) = TRUE;}
	ATTF_ATT(np) = NULL;
}

void att_sort (Node * np)
{
	Symbol * sp  = (Symbol *) ATTS_SORT(np);
  Node * ufk1  = ATTS_SHOW(np),
       * ufk2  = ATTS_CMP(np),
       * ufk3  = ATTS_CPY(np),
       * ufk4  = ATTS_DEL(np);
DEBG((4,"def.c : att_sort \n"));
hasval(sp) = TRUE;
show(sp) = (void *) ufk1 ; /* show-Fkt. */
cmp(sp)  = (Node *) ufk2;
cpy(sp)  = (Node *) ufk3;
del(sp)  = (Symbol *) ufk4;

ATTS_SHOW(np) = NULL;
ATTS_CMP(np)  = NULL;
ATTS_CPY(np)  = NULL;
ATTS_DEL(np)  = NULL;
DEBG((4,"def.c : att_sort ende\n"));
}

void spec (Node * np)
{
Symbol * sp = (Symbol *) SPEC_ALG(np);
Node * alist = SPEC_LIST(np);
	delete(atypes(sp));
	atypes(sp) = alist;
SPEC_LIST(np) = NULL;
}

void a_spec_form (Node * np)
{
Symbol * sp = (Symbol *) SPEC_ALG(np);
Node * flist = SPEC_LIST(np);
Node * ap,* form,* toform;
	for (ap=(flist);ap != NULL;ap=ap->r)
		{
		form=FORM_LHS(ap->l);
		toform=FORM_RES(ap->l);
		atypes(sp)=add_rule_variants(form,toform,atypes(sp)); /* In Formelbaum einfuegen (mit Varianten, expand.c) */
		}
SPEC_LIST(np) = NULL;
}

void spec_form (Node * np)
{
	delete(atypes((Symbol *) SPEC_ALG(np)));
	atypes((Symbol *) SPEC_ALG(np))=NULL;
	a_spec_form(np);
}

void clearBlockstufe (void)
{
for(;blockstufe>blockbase;blockstufe--) restore_locals();
}

void block_begin(void)
{
	blockstufe++;
	if (blockstufe>=MAXBLOCKS) fatal("Maxblocks reached !");
	local[blockstufe]=NULL;
}

void block_end(void)
{
	restore_locals();
	blockstufe--;
}

void end_all_blocks(void)
{
	while (blockstufe>blockbase)
		{
		protect();
		block_end();
		}
}

void do_block_begin(Node * np)
{
	block_begin();
}

void do_block_end(Node * np)
{
	block_end();
}


Node * in_block_def(Node * np)
{
if (blockstufe > blockbase)
	{
	((void (*) (Node *)) (np->l)) (np); /* zeitweise definieren, werden durch block-end geloescht */
	return np;
	}
else return np;
}

Node * mksortlist(Node * np) /* Convert definitions into Sortlist */
{
	if (np->r)
		return mknod(Sorts,np->l,mksortlist(np->r));
	else
		return np->l;
}
		
Node * exe_function (Node * np)
{
	Node * jog;
	Symbol * sp = TERM_HEAD(np);
	DEBG((7,"exe_function\n"));

	returnterm= &ReturnTerm;
	rtypes(returnterm)=rtypes(sp);
	defined_in_block(returnterm)=blockstufe;

	block_begin();
	no_protect();
	
	globalArglist=TERM_ARGS(np);
	in_definition=TRUE;

	for(jog=UFUNC_ARGDEFS((Node *) value(sp));jog;jog=jog->r) /* Argument-definitionen */
		CALLFUNCT(jog->l);

	in_definition=FALSE;

	DEBG((7,"exe_function alles definiert\n"));

	globalArglist=NULL;
	globalRtw=NULL;

	no_protectAtall();
	CALLFUNCT(UFUNC_BODY((Node *) value(sp)));
	protectAtall();
				
	protect();
	block_end();

	DEBG((7,"exe_function ende\n"));
	return (Node *) returnterm;
}

void return_fkt (Node * np)
{
returnterm= &ReturnTerm;
if (! termassign2((Node *) returnterm,np->r)) returnterm=NULL; /* damit wird Ergebnis ignoriert */
DEBG((4,"RETURNed : "));
DBFK(4, print((Node *) returnterm));
DEBG((4,"\n"));
}

Node * rec_build_list (Node * * np)
{
Node * l,* r;
DEBG((8,"def.c : rec_build_list \n"));
if (! (* np)) return NULL;
if ((* np) -> type != SYM_TYPE)
	{
	if (((* np) -> type == FUNC)
	|| ((* np) -> type == Cond))
		return rec_build_list(&((* np)->r));

	l = rec_build_list(&((* np)->l)); r= rec_build_list(&((* np)->r));
	if (l && r) return mknod(PARAM,l,r);
	if (l) return l;
	else return r;
	}
else /* type == SYM_TYPE */
	{
	if (oldvals((Symbol *) (* np)))
		{
		DEBG((4,"def.c : rec_build_list entered Symbol : "));
		DBFK(4, print(* np));
		DEBG((4,"\n"));
		return mknod(SYM_TYPE,(Node *) np,(Node *) (* np)); /* Adresse, an der Aenderung vorzunehmen ist und Grund-Symbol */
		}
	else
		return NULL;
	}
return NULL; /* fuer dumme Compiler */
}

void set_locals (Node * np,Symbol * (* give_fkt) (Symbol *))
{
DEBG((7,"def.c : set_locals \n"));
if (! np) return;
if (np -> type == PARAM)
	{set_locals(np->l,give_fkt);set_locals(np->r,give_fkt);return;}
if (np -> type == SYM_TYPE)
	{
	Symbol ** spp= (Symbol **) (np->l);
	DEBG((4,"def.c : set_locals Symbol : %s changed\n",name(* spp)));
	(* spp) = give_fkt((Symbol *) np->r); /* Aendern des Zeigers */
	DEBG((4,"done\n",name(* spp)));
	}
else
	fatal("ERROR : set_locals : wrong type");
}

Symbol * give_actual (Symbol * sp) /* neustes Symbol raussuchen (run-time) */
{
  DEBG((5,"def.c : giveactual returned : %s \n",name(oldvals(sp))));
  return oldvals(sp);
}

Symbol * give_old (Symbol * sp) /* altes Symbol raussuchen (run-time) */
{
  DEBG((5,"def.c : giveold returned : %s \n",name(sp)));
  return sp;
}

void set_locals_seq (Node * np)
{
Node * list  = LOCALS_LIST(np),
     * instr = LOCALS_INSTR(np);
set_locals(list,give_actual);
DEBG((4,"set_locals_seq will call\n"));
if (instr->type != FUNC) fatal("fatal locals_seq ERROR: No Funct in instruction !");
DEBG((4,"args: "));
DBFK(4, print(INSTR_PAR(instr)));
DEBG((4,"\n"));
CALLFUNCT(instr);
set_locals(list,give_old); /* Wieder fuer naechsten Aufruf zuruecksetzen */
return;
}

Node * in_block_instruct (Node * np)
{
/* return np; */
DEBG((7,"def.c : in_block_instruct : blockstufe : %d\n",blockstufe));
if (! np) return NULL;
if (np->type != FUNC) fatal("fatal ERROR: No Funct in instruction !");
if (blockstufe)
	{
	Node * kette;
	if (kette=rec_build_list(& (np->r)))
		{
		return mknod(FUNC,(Node *) set_locals_seq,mknod(PARAM,kette,np));
		}
	else
		return np;
	}
else
	return np;
}

void is_not_running(void)
{
	running = FALSE;
}

void is_running(void)
{
	running = TRUE;
}


/* INC innerhalb eines laufenden Blocks: das eingelesene File wird wie eine
 * Eingabe auf Top-Level behandelt (Definitionen sofort und global, nicht
 * doppelt zur Parse- und Laufzeit). Die aeusseren Bloecke bleiben erhalten. */
int include_begin(void)
{
	int old = blockbase;
	blockbase = blockstufe;
	return old;
}

void include_end(int oldbase)
{
	while (blockstufe > blockbase) /* nicht geschlossene Bloecke im File */
		{
		protect();
		block_end();
		}
	blockbase = oldbase;
}
