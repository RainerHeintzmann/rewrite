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
#include "symfn.h"	/* ATT RULES */
#include "expand.h"


static Symbol ReturnTerm =
{
{
SYM_TYPE,
NULL,
NULL},
"ReturnTerm",
Term,
NULL, /* any data type */
NULL,
FALSE,
NULL,
NULL,
0,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
0 /* global (is changed) */
};

static Symbol * returnterm =  & ReturnTerm; /* temporarily stores the last term */
static int block_level=0;	/* set to zero by sync.c on errors */
static int running   =0;	/* Is a statement being executed right now ? */
static int blockbase =0;	/* Block level at which a file read via INC is "top level" */

#define MAXBLOCKS 250

Node * local[MAXBLOCKS]; /* Chain of local symbols */

static BOOLEAN dont_protect[MAXBLOCKS]; /* initialized with FALSE */

static BOOLEAN never_protect; /* No protect inside a function call */

static BOOLEAN in_definition=0; /* No protect inside a function call */

static Node * globalArglist=NULL; /* for direct assignment of parameters */

static Node * globalRtw = NULL; /* Return value of functions */

/* Functions for block handling :   */

static Symbol * save_local_run(Symbol * sp)  /* different order at run time ! */
{
	Symbol * ns;
	Node * vp;

	DEBG((15,"save_local_run\n"));

	if (! block_level) return sp;
	for (vp=local[block_level];vp != NULL;vp=vp->r) /* already defined ? */
		if (sp==(Symbol *) vp->l)	return oldvals(sp);

	ns=mksym(Id,name(sp));           /* now free for arbitrary definitions */
	defined_in_block(ns)=block_level;
	oldvals(ns)=oldvals(sp);
	oldvals(sp)=ns;
	local[block_level]=mknod(Id,(Node *) sp,local[block_level]);	
	DEBG((15,"save_local_run_end\n"));
	return ns;
}

static Symbol * save_local(Symbol * sp)
{
	Symbol * ns;
	Node * vp;

	DEBG((15,"save_local\n"));

	if (block_level <= blockbase) return sp; /* Top level (also in INC files): define globally */
	if (running) return save_local_run(sp); /* Different procedure at run time ! */

	for (vp=local[block_level];vp != NULL;vp=vp->r)
		if (sp==(Symbol *) vp->l)	return sp;

	ns=clonesym(sp);
	oldvals(sp)=ns;
	lexval(sp)=Id; /* now free for arbitrary definitions */
	local[block_level]=mknod(Id,(Node *) sp,local[block_level]);	
	DEBG((15,"save_local_end\n"));
	return sp;
}

/* Free the run-time copy of a local symbol (from save_local_run):
 * the name (strsave in mksym), numeric value and stored term belong to it. */
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

static void restore_locals_run(void) /* different order at run time ! */
{
	Node * vp,* op;
	Symbol * sp,* sp2;

	DEBG((20,"restore_locals_run\n"));

	for (vp=local[block_level];vp != NULL;)
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
	local[block_level]=NULL;
}

static void restore_locals(void)
{
	Node * vp,* op;
	Symbol * sp,* sp2;

	DEBG((20,"restore_local\n"));
	if (running) 
		{
		restore_locals_run(); /* Different procedure at run time ! */
		return;
		}

	for (vp=local[block_level];vp != NULL;)
		{
		DEBG((20,"restore_local_1\n"));
		sp=(Symbol *) vp->l;
		sp2=oldvals(sp);
		{
		char * keep = name(sp); /* sp keeps its own name */
		cpysym(sp2,sp);
		name(sp) = keep;
		}
		free(name(sp2));        /* Copy of the name from clonesym */
		delsym(sp2);
		op=vp;
		vp=vp->r;
		delnod(op);
		DEBG((20,"restore_local_2\n"));
		}
	local[block_level]=NULL;
}

/* further Functs */

void specials(Symbol * sp, int lexv)
{
	switch (lexv)
		{
		case Sort :			value(sp) = NULL;
										IS_link(sp) = NULL;
										IS_chain(sp) = NULL;
										show(sp)  = (void *) std_show_real; /* show function */
										cmp(sp)  = (Node *) std_cmp_real;
										cpy(sp)  = (Node *) std_cpy_real;
										del(sp)  = (Symbol *) std_del_real;
										break;
		case Bra :
										bracket(sp) = sp; /* with itself */
										variants(sp) = NULL;
										break;			
		default : break;
		}

}

void protectAtall (void) /* for declare arguments */
{
never_protect=FALSE;
}

void protect (void) /* for declare arguments */
{
dont_protect[block_level]=FALSE;
}

void no_protectAtall (void)
{
never_protect=TRUE;
}

void no_protect (void)
{
dont_protect[block_level]=TRUE;
}

Symbol * declaresym(Symbol * sp,Node * rtps,Node * atps,int lexv,int hasv)
{
	sp=save_local(sp);
	if (lexval(sp) == Sort && lexv != Sort)	/* 2026: the sorts of other symbols point to it */
		{
		printfErr("error : %s is a sort and cannot be declared again as something else !\n",name(sp));
		return sp;
		}
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
	variants(sp)  = NULL;
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
		DBFN(15, print(np));
		DEBG((15,"\n"));
		np=ARGS_ITEM(np);  /* current argument */
		switch (lexv)
			{
				case Const : numassign2(np,sp);
										globalArglist=ARGS_NEXT(globalArglist);
										break;
				case Term : termassign2((Node *) sp,np);
										globalArglist=ARGS_NEXT(globalArglist);
										break;
				case Func : /* assign functions */
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

	/* Neutralize only at top level: there the line is deleted after execution.
	 * In blocks (loops, functions, INC inside blocks) the definition must be
	 * executable again on every pass. */
	if (block_level <= blockbase)
		{
		DECL_LEXV(np)=PARAM;   /* formerly lexval */
		DECL_HASV(np)=PARAM;   /* formerly hasval */
		DECL_ATYPES(np)= NULL; /* do not delete atypes ! */
		DECL_RTYPES(np)= NULL;
		}

	if (lexv != Sort)
		DEBG((4,"def.c : declare rtypes(sp) = %s\n","Error")); // name((Symbol *) rtypes(sp))));
	else
		DEBG((4,"def.c : declared Sort\n"));
}

void set_brackets (Node * np)
{
bracket((Symbol *) BRK_OPEN(np)) = ((Symbol *) BRK_CLOSE(np));
bracket((Symbol *) BRK_CLOSE(np)) = NULL;
}

void other_fn (Node * np)
{
	Symbol * sp   = (Symbol *) OTHER_SYM(np),* newsym, * aux;
  Node * vsortl = OTHER_SORTS(np),
       * sort   = OTHER_RTYPE(np),
       * att    = OTHER_ATT(np);

  newsym=mksym(lexval(sp),name(sp));
	atypes(newsym)=vsortl;
	rtypes(newsym)=sort;
	variants(newsym)=sp; /* Linked in a circle */
	for (aux=sp;(variants(aux)!= (Symbol *) NULL) && (variants(aux) != sp);aux=variants(aux))
				; /* No loop body */
	variants(aux)=newsym;  /* Chaining of the functions */
	orig_func(newsym)=sp;
	if (att)
		if (att->type==ATT)
			{
			hasval(newsym) = TRUE;
			value(newsym)  = ATT_CFUNC(att);
			builtin(newsym) = att->r ? (att->r->r ? 2 : 1) : 0;	/* symbolic C function, 2: HOLD */
			if (att->r && att->r->l) rules_fn_register(newsym, att->r->l);	/* ATT RULES alglist */
			}
		else /* PARAM */
			{
			value(newsym) = att;
			exe_always(newsym) =TRUE;
			hasval(newsym) = TRUE;
			}
	OTHER_ATT(np)   = NULL;
	OTHER_RTYPE(np) = NULL; /* do not delete atypes */
	OTHER_SORTS(np) = NULL;
}


void att_fn (Node * np)
{
	Symbol * sp  = (Symbol *) ATTF_SYM(np);
  Node   * ufn = ATTF_ATT(np);

	variants(sp) = NULL;
	orig_func(sp)= sp;
	if (ufn)
		if (ufn->type == ATT) /* user function */
			{value(sp)  = ATT_CFUNC(ufn);
			hasval(sp) = TRUE;
			builtin(sp) = ufn->r ? (ufn->r->r ? 2 : 1) : 0;	/* symbolic C function, 2: HOLD */
			if (ufn->r && ufn->r->l) rules_fn_register(sp, ufn->r->l);}	/* ATT RULES alglist */
		else /* PARAM */
			{
			value(sp) =ufn;
			exe_always(sp) =TRUE;
			hasval(sp) = TRUE;}
	ATTF_ATT(np) = NULL;
}

void att_sort (Node * np)
{
	Symbol * sp  = (Symbol *) ATTS_SORT(np);
  Node * ufn1  = ATTS_SHOW(np),
       * ufn2  = ATTS_CMP(np),
       * ufn3  = ATTS_CPY(np),
       * ufn4  = ATTS_DEL(np);
DEBG((4,"def.c : att_sort \n"));
hasval(sp) = TRUE;
show(sp) = (void *) ufn1 ; /* show function */
cmp(sp)  = (Node *) ufn2;
cpy(sp)  = (Node *) ufn3;
del(sp)  = (Symbol *) ufn4;

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
		atypes(sp)=add_rule(form,toform,atypes(sp)); /* in formula tree or rule list (expand.c) */
		}
SPEC_LIST(np) = NULL;
}

void spec_form (Node * np)
{
	delete(atypes((Symbol *) SPEC_ALG(np)));
	atypes((Symbol *) SPEC_ALG(np))=NULL;
	a_spec_form(np);
}

void clearBlockLevel (void)
{
for(;block_level>blockbase;block_level--) restore_locals();
}

void block_begin(void)
{
	block_level++;
	if (block_level>=MAXBLOCKS) fatal("Maxblocks reached !");
	local[block_level]=NULL;
}

void block_end(void)
{
	restore_locals();
	block_level--;
}

void end_all_blocks(void)
{
	while (block_level>blockbase)
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
if (block_level > blockbase)
	{
	((void (*) (Node *)) (np->l)) (np); /* define temporarily, they are deleted by block end */
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
	defined_in_block(returnterm)=block_level;

	block_begin();
	no_protect();
	
	globalArglist=TERM_ARGS(np);
	in_definition=TRUE;

	for(jog=UFUNC_ARGDEFS((Node *) value(sp));jog;jog=jog->r) /* Argument definitions */
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

	DEBG((7,"exe_function end\n"));
	return (Node *) returnterm;
}

void return_fn (Node * np)
{
returnterm= &ReturnTerm;
if (! termassign2((Node *) returnterm,np->r)) returnterm=NULL; /* this way the result is ignored */
DEBG((4,"RETURNed : "));
DBFN(4, print((Node *) returnterm));
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
		DBFN(4, print(* np));
		DEBG((4,"\n"));
		return mknod(SYM_TYPE,(Node *) np,(Node *) (* np)); /* Address at which the change is to be made, and base symbol */
		}
	else
		return NULL;
	}
return NULL; /* for dumb compilers */
}

void set_locals (Node * np,Symbol * (* give_fn) (Symbol *))
{
DEBG((7,"def.c : set_locals \n"));
if (! np) return;
if (np -> type == PARAM)
	{set_locals(np->l,give_fn);set_locals(np->r,give_fn);return;}
if (np -> type == SYM_TYPE)
	{
	Symbol ** spp= (Symbol **) (np->l);
	DEBG((4,"def.c : set_locals Symbol : %s changed\n",name(* spp)));
	(* spp) = give_fn((Symbol *) np->r); /* Change the pointer */
	DEBG((4,"done\n",name(* spp)));
	}
else
	fatal("ERROR : set_locals : wrong type");
}

Symbol * give_actual (Symbol * sp) /* look up the newest symbol (run time) */
{
  DEBG((5,"def.c : giveactual returned : %s \n",name(oldvals(sp))));
  return oldvals(sp);
}

Symbol * give_old (Symbol * sp) /* look up the old symbol (run time) */
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
DBFN(4, print(INSTR_PAR(instr)));
DEBG((4,"\n"));
CALLFUNCT(instr);
set_locals(list,give_old); /* Reset again for the next call */
return;
}

Node * in_block_instruct (Node * np)
{
/* return np; */
DEBG((7,"def.c : in_block_instruct : block_level : %d\n",block_level));
if (! np) return NULL;
if (np->type != FUNC) fatal("fatal ERROR: No Funct in instruction !");
if (block_level)
	{
	Node * variants;
	if (variants=rec_build_list(& (np->r)))
		{
		return mknod(FUNC,(Node *) set_locals_seq,mknod(PARAM,variants,np));
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


/* INC inside a running block: the file read is treated like an
 * input at top level (definitions immediately and globally, not
 * twice at parse time and run time). The outer blocks are kept. */
int include_begin(void)
{
	int old = blockbase;
	blockbase = block_level;
	return old;
}

void include_end(int oldbase)
{
	while (block_level > blockbase) /* unclosed blocks in the file */
		{
		protect();
		block_end();
		}
	blockbase = oldbase;
}
