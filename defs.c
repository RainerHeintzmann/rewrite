/*
 *	defs.c V1.00
 *	Copyright (c)  Rainer Heintzmann (1993)
 *
 */

#include "inout.h"
#include "sym.h"
#include "node.h"
#include "defs.h"
#include "forms.h"
#include "syn.h"
#include "run.h"
#include "sync.h"


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

	if (! blockstufe) return sp;
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
		delsym(sp2);
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
		cpysym(sp2,sp);
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
		if (np->type == Terms)
			np=np->l;
		switch (lexv)
			{
				case Const : numassign2(np,sp);
										globalArglist=globalArglist->r;
										break;
				case Term : termassign2((Node *) sp,np);
										globalArglist=globalArglist->r;
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
											Symbol * sp2=(Symbol *) np->l;
											hasval(sp)=hasval(sp2);
											value(sp)=value(sp2);
											exe_always(sp)=exe_always(sp2);
											globalArglist=globalArglist->r;
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
	Node * Idlist= np->r->l,
       * rtps  = np->r->r->l,
       * atps  = np->r->r->r,
       * mynp;
	Symbol * sp;
  int  lexv  = np->r->type,
       hasv  = np->r->r->type;

	DEBG((4,"def.c : declare \n"));

	for (mynp=Idlist;mynp->type == Id;mynp=mynp->r)
		{	sp = (Symbol *) mynp->l;
			sp = declaresym(sp,rtps,atps,lexv,hasv);
		}
	sp = (Symbol *) mynp;
	sp = declaresym(sp,rtps,atps,lexv,hasv);

	if ((! dont_protect[blockstufe]) && (! never_protect))
		{
		np->r->type=PARAM;    /* vorher lexval */
		np->r->r->type=PARAM; /* vorher hasval */
		np->r->r->r= NULL;    /* atypes nicht loeschen ! */
		np->r->r->l= NULL;
		}

	if (lexv != Sort)
		DEBG((4,"def.c : declare rtypes(sp) = %s\n","Error")); // name((Symbol *) rtypes(sp))));
	else
		DEBG((4,"def.c : declared Sort\n"));
}

void set_brackets (Node * np)
{
klammer((Symbol *) np->r->l) = ((Symbol *) np->r->r);
klammer((Symbol *) np->r->r) = NULL;
}

void other_fkt (Node * np)
{
	Symbol * sp   = (Symbol *) np->r->l,* newsym, * hilf;
  Node * vsortl = np->r->r->l,
       * sort   = np->r->r->r->l,
       * att    = np->r->r->r->r;

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
			value(newsym)  = att->l;
			}
		else /* PARAM */
			{
			value(newsym) = att;
			exe_always(newsym) =TRUE;
			hasval(newsym) = TRUE;
			}
	np->r->r->r->r = NULL;
	np->r->r->r->l = NULL; /* atypes nicht loeschen */
	np->r->r->l    = NULL; 
}


void att_fkt (Node * np)
{
	Symbol * sp  = (Symbol *) np->r->l;
  Node   * ufk = np->r->r;
	
	kette(sp) = NULL;
	urs_fkt(sp)= sp;
	if (ufk)
		if (ufk->type == ATT) /* USERfkt. */
			{value(sp)  = ufk->l;
			hasval(sp) = TRUE;}
		else /* PARAM */
			{
			value(sp) =ufk;
			exe_always(sp) =TRUE;
			hasval(sp) = TRUE;}
	np->r->r = NULL;
}

void att_sort (Node * np)
{
	Symbol * sp  = (Symbol *) np->r->l;
  Node * ufk1  = np->r->r->l,
       * ufk2  = np->r->r->r->l,
       * ufk3  = np->r->r->r->r->l,
       * ufk4  = np->r->r->r->r->r;
DEBG((4,"def.c : att_sort \n"));
hasval(sp) = TRUE;
show(sp) = (void *) ufk1 ; /* show-Fkt. */
cmp(sp)  = (Node *) ufk2;
cpy(sp)  = (Node *) ufk3;
del(sp)  = (Symbol *) ufk4;

np->r->r->l = NULL;
np->r->r->r->l = NULL;
np->r->r->r->r->l = NULL;
np->r->r->r->r->r = NULL;
DEBG((4,"def.c : att_sort ende\n"));
}

void spec (Node * np)
{
Symbol * sp = (Symbol *) np->r->l;
Node * alist = np->r->r;
	delete(atypes(sp));
	atypes(sp) = alist;
np->r->r = NULL;
}

void a_spec_form (Node * np)
{
Symbol * sp = (Symbol *) np->r->l;
Node * flist = np->r->r;
Node * ap,* form,* toform;
	for (ap=(flist);ap != NULL;ap=ap->r)
		{
		form=ap->l->l;
		toform=ap->l->r;
		atypes(sp)=merge(form,toform,atypes(sp)); /* In Formelbaum einfuegen */
		}
np->r->r = NULL;
}

void spec_form (Node * np)
{
	delete(atypes((Symbol *) np->r->l));
	atypes((Symbol *) np->r->l)=NULL;
	a_spec_form(np);
}

void clearBlockstufe (void)
{
for(;blockstufe;blockstufe--) restore_locals();
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
	while (blockstufe>0)
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
if (blockstufe)
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
	Symbol * sp = (Symbol *) np->l;
	DEBG((7,"exe_function\n"));

	returnterm= &ReturnTerm;
	rtypes(returnterm)=rtypes(sp);
	defined_in_block(returnterm)=blockstufe;

	block_begin();
	no_protect();
	
	globalArglist=np->r;
	in_definition=TRUE;

	for(jog=((Node *) value(sp))->l;jog;jog=jog->r) /* Argument-definitionen */
		CALLFUNCT(jog->l);

	in_definition=FALSE;

	DEBG((7,"exe_function alles definiert\n"));

	globalArglist=NULL;
	globalRtw=NULL;

	no_protectAtall();
	CALLFUNCT(((Node *) value(sp))->r);
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
np = np->r;
set_locals(np->l,give_actual);
DEBG((4,"set_locals_seq will call\n"));
if (np->r->type != FUNC) fatal("fatal locals_seq ERROR: No Funct in instruction !");
DEBG((4,"args: "));
DBFK(4, print(np->r->r));
DEBG((4,"\n"));
CALLFUNCT(np->r);
set_locals(np->l,give_old); /* Wieder fuer naechsten Aufruf zuruecksetzen */
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

