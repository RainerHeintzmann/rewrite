/* forms.c */
/* Tree for the formulas of the algebras */

#include "inout.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "forms.h"
#include "node.h" /* also symeq */
#include "sync.h"
#include "numsort.h"	/* 2026: var_sort_ok */  /* For IS_follows, lock_rtypes */
#include "nodes.h"
#include "symfn.h"	/* 2026: symbolic_constant */

extern Node * chain_pos;
extern Node var_chain;

static Node * old_repl,
            * in_repl,
            * new_repl,
            * repl_arg,
          * * where_repl,
          * * where_repl_path,
          * * old_repl_path,
          * * saved_p_tree;

static BOOLEAN matched_repl;
static int depthcount;
static Node * repl_node;

Node * attach_repl (Node * form,Node * Repl)
{
	return mknod(REPL_TYPE,form,Repl);  /* use tcopy ?? (But does not work because of Cond) */
}

Node * mkor(Node * l,Node * r)
{
	DEBG((4,"Mache ODER-Knoten im Formel-rtree :"));
	DBFN(4,print(r->l));
	DEBG((4,"\n"));
	return mknod(OR_TYPE,l,r);
}

Node * instree(Node * rtree,Node * form,Node * Repl)
{
		DEBG((5,"instree: rtree: "));
		DBFN(5,print(rtree));
		DEBG((5,",form: "));
		DBFN(5,print(form));
		DEBG((5,"\n"));

if (old_repl == (Node *) NULL)
	{
	return mkor(rtree,attach_repl(form,Repl));
	}
else
	{
	old_repl->l = rtree;
	return mkor(old_repl,attach_repl(form,Repl));
	}
}

BOOLEAN merge2(Node * form,Node * rtree)
{
	DEBG((5,"Merge2 form: "));
	DBFN(5,print(form));
	DEBG((5,",tree: "));
	DBFN(5,print(rtree));
	DEBG((5,"\n"));

	depthcount++;
	if ((form != NULL) && (rtree != NULL) 
		&& (form->type == SYM_TYPE) && (rtree->type == SYM_TYPE)
		&& (lexval((Symbol *) form) == Var) && (lexval((Symbol *) rtree) == Var))
			return FALSE; /* Metavariables must never match, otherwise there are decision problems later when restoring the variables : */

	if (form == rtree)
		return TRUE;   /* Subtrees are identical (symbols or NULL) */

	if ((rtree == (Node *) NULL) || (form == (Node *) NULL))
		{
		return FALSE;
		}
		
	if (rtree->type==REPL_TYPE)
		{
		BOOLEAN tmp;
    in_repl = rtree;
		old_repl_path = saved_p_tree;
#ifdef DEBUG
			if (old_repl_path == (Node **)NULL)
				DEBG((5," saved_p_tree is NULL !\n"));
#endif			
		saved_p_tree = &(rtree->l);
		if (tmp=merge2(form,rtree->l))
			{
			DEBG((6," matched repl. !\n"));
	    matched_repl = TRUE;
			}
    in_repl = NULL;
		old_repl_path = (Node **) NULL;
		return tmp;		
		}

	if (rtree->type==OR_TYPE)
		{
		BOOLEAN tmp;
		if (in_repl != (Node *) NULL)
			fatal("internal-error: merge2 did not expect a replacement before OR");
		saved_p_tree = &(rtree->r); 
    matched_repl = FALSE;
		tmp = merge2(form,rtree->r);  /* Better: count depth, take the better tree */
		if (! tmp)  /* see also below */
			if (where_repl == (Node * *) NULL)
				{
				where_repl = &(rtree->r);
				new_repl = form;
				where_repl_path = old_repl_path;
				old_repl = in_repl;
				}
		return tmp;
		}


	if (  (form -> type == SYM_TYPE)   /* possibly the same value ? */
		 && (rtree -> type == SYM_TYPE))
		{
		BOOLEAN tmp=symeq((Symbol *) form,(Symbol *) rtree);
#ifdef DEBUG
			DEBG((6,"symeq returned "));
			if (tmp)
				DEBG((6,"true \n"));
			else
				DEBG((6,"false \n"));
#endif
		return tmp;
		}
	else
		if (form->type==rtree->type)   /* Term or Func ,.. */
			{
				BOOLEAN m1,m2,saved_repl;

				saved_p_tree = &(rtree->l);
				m1= merge2(form->l,rtree->l);
				saved_repl = matched_repl;
				saved_p_tree = &(rtree->r);
				m2= merge2(form->r,rtree->r);
				if (! matched_repl)
					matched_repl = saved_repl;

				if (m1 && m2)
					{
					DEBG((6,"merge2: matched two eqal terms:"));
					DBFN(6,print(rtree->l));
					DEBG((6,", "));
					DBFN(6,print(rtree->r));
					DEBG((6,", ret. true.\n"));
					return TRUE;
					}
				if (! m1)
					if (where_repl == (Node * *) NULL)
						{
						where_repl = &(rtree->l);
						new_repl = form->l;
						where_repl_path = old_repl_path;
						old_repl = in_repl;
						}
				if (! m2)
					if (where_repl == (Node * *) NULL)
						{
						where_repl = &(rtree->r);
						new_repl = form->r;
						where_repl_path = old_repl_path;
						old_repl = in_repl;
						}
				if ((!m1)       /* && (!m2) but problems with Func followed by OR node ! */
				  || ( matched_repl))
						{
						if (! matched_repl)
							{
							DEBG((6,"merge2: Got two wrong Terms, where_repl := NULL : "));
							DBFN(6,print(rtree->l));
							DEBG((6,", "));
							DBFN(6,print(form->l));
							DEBG((6,"und "));
							DBFN(6,print(rtree->r));
							DEBG((6,", "));
							DBFN(6,print(form->r));
							DEBG((6,"\n"));
							}

						where_repl = (Node * *) NULL;
						old_repl = in_repl;
						matched_repl = FALSE; /* Reset, the next possible replacement takes place */
						}
				else
						depthcount--;
				return FALSE;
			}

	return FALSE;
}

Node * merge(Node * form,Node * Repl,Node * rtree)
{
	DEBG((5,"Merge form: "));
	DBFN(5,print(form));
	DEBG((5,"in tree: "));
	DBFN(5,print(rtree));
	DEBG((5,"\n"));

	if (rtree == (Node *) NULL)
		return attach_repl(form,Repl);
  else
    {
		in_repl  = (Node *) NULL;
		old_repl = (Node *) NULL;
		where_repl  = (Node * *) NULL;
		new_repl = (Node *) NULL;
		repl_arg = (Node *) NULL;
		where_repl_path = (Node * *) NULL;
		saved_p_tree = (Node * *) NULL;
		old_repl_path = (Node * *) NULL;
		matched_repl = FALSE;

		if (! merge2(form,rtree))
			{
			if (old_repl==rtree)
				if (where_repl == (Node **) NULL)
					old_repl=NULL; /* Upper ER node is replaced entirely */
				else
          rtree = rtree->l; /* Because the ER node is pulled into the subtree ! */
			else
					if (old_repl != (Node *) NULL)
						(* where_repl_path) = old_repl->l;

			if (where_repl == (Node * *) NULL)
				{
				DEBG((6,"where_repl == NULL \n"));
				return instree(rtree,form,Repl);
				}

			(* where_repl) = instree(* where_repl,new_repl,Repl);
			return rtree;
			}
		return rtree;
		}
}


BOOLEAN match2 (Node * term,Node * rtree)
{
	DEBG((5,"match2: term:"));
	DBFN(5,print(term));
	DEBG((5,",tree: "));
	DBFN(5,print(rtree));
	DEBG((5,"\n"));

	if (term == rtree)
		{
		DEBG((6,"match2: pointers are eqal: "));
		DBFN(6,print(term));
		DEBG((6,"\n"));
		return TRUE;
		}

	if ((rtree == (Node *) NULL) || (term == (Node *) NULL))
		{
		RESTORE
		return FALSE;
		}

	if (rtree->type==REPL_TYPE)
		{
		DEBG((6,"match2: found ER-Type := "));
		DBFN(6,print(rtree->l));
		DEBG((6," ; "));
		DBFN(6,print(rtree->r));
		DEBG((6,"\n"));

		if (match2(term,rtree->l) == TRUE)
			{
			DEBG((6,"match2: repl_node := "));
			DBFN(6,print(rtree->r));
			DEBG((6,"\n"));

			/* matching formula found, now check the condition */
			if (COND_CALL(RES_COND(rtree->r)))	/* Condition for the equation */
				{
				repl_node = rtree->r; /* Condition matches too ! */
				return TRUE;
				}
			else
				{
				RESTORE
				return FALSE;
				}
			}
		else
			{
			RESTORE
			return FALSE;
			}
		}

	if (rtree->type==OR_TYPE)
		{
		if (match2(term,rtree->l))
			return TRUE;
		if (match2(term,rtree->r))
			return TRUE;
		RESTORE
		return FALSE;
		}

	if (((rtree -> type) == SYM_TYPE))
		{
			Symbol * tsym;

			switch (term->type)	/* Finds the symbol belonging to term */
				{
				case Const: 
				case Func:  tsym=(Symbol *) term->l;
										break;
				case SYM_TYPE:
										tsym=(Symbol *) term;
										break;
				default:
										RESTORE
										return FALSE; /* Does happen in the tree ! */
				}

		if  (lexval((Symbol *) rtree) == Var) /* Replace variable */
			{
			if (term->type == SYM_TYPE)	/* 2026: the symbol inside a Const node, reached
							   by the traversal: a variable matches the Const */
				{
				RESTORE
				return FALSE;
				}
			if ((term->type != Const)
					&& (term->type != Func)) /* Wanted : Const,Func */
				{
				printfErr("match2: ERROR : unexpected term-type : ");
				print(term);
				printfErr("  Typenr. : %d (matching Var) \n",term->type);
				RESTORE
				return FALSE;
				}

			/* Different sorts are assigned too, formerly: if (! eq_sorts(rtypes((Symbol *) rtree),rtypes(tsym))) return FALSE;*/
			/* 2026: except for subsorts (PAT X : nonneg only matches nonneg) */
			if (! var_sort_ok(rtypes((Symbol *) rtree), term))
				{
				RESTORE
				return FALSE;
				}

                       /* Types (also function results) match now */

			if (hasval(rtree))                 /* Numeric variable ? */
       if (!(lexval(tsym) == Const)
  				|| ! hasval(tsym)            /* only replace numeric Const / Func */
				|| symbolic_constant(tsym))	/* 2026: pi in exact mode: no number */
        {

					RESTORE
					return FALSE;
				}

			chain_pos = chain_pos -> l = mknod(CHAIN,NULL,NULL);
			chain_pos->r = (Node *) rtree; /* Occupy new position */
			DEBG((4,"Variable ersetzt : "));
			DBFN(4,print(rtree));

				rtree->type = term->type;  /* Const or Func */
				rtree->l = term->l;
				rtree->r = term->r;

	/* (* rtree) = (* term);	only possible replacement directly in the symbol table ! */
		   												/* Node structure is copied (and thus overwritten !) */

				DEBG((4,"-> "));
				DBFN(4,print(rtree));
				DEBG((4,"\n"));

			return TRUE;
			}
		else			/* Compare constants or functions */
			{
			if (lexval((Symbol *) rtree) == Term)
				{
				return match2(term,rtree->l); /* Skip the symbol slot */
				}
			return symeq((Symbol *) term,(Symbol *) rtree);
			}
	}

	if ((term -> type) == (rtree -> type))
				{

				if (term->type == Func)
					{	
					Node * tmpchain = NULL;
					if (term->l != rtree->l && variant_fits((Symbol *) term->l,(Symbol *) rtree->l)
					    && ! IS_follows((Symbol *) term->l,(Symbol *) rtree->l))
						return match2(term->r,rtree->r);	/* 2026: + : real,real for + : number,number */
					if (IS_follows((Symbol *) term->l,(Symbol *) rtree->l))
						if (lock_rtypes((Symbol *) rtree->l,(Symbol *) term->l,& tmpchain))
							if (match2(term->r,rtree->r))
								{
								chain_pos -> l = tmpchain;
								while (chain_pos -> l)
									chain_pos=chain_pos->l;
								return TRUE;
								}
							else
								{ /* delete locks */
								Node * oldc;
								while (tmpchain)
									{
									oldc=tmpchain;
									IS_link((Symbol *) (tmpchain->r))=(Symbol *) NULL;
									DEBG((4,"restoring Sort: %s\n",((Symbol *) tmpchain->r)->name));
									tmpchain=tmpchain->l;
									delnod(oldc);
									}
								}								
					}			
				else
					if (term->type == Const)
						{
						Node * tmpchain = NULL;
						if (IS_follows((Symbol *) term->l,(Symbol *) rtree->l))
							if (lock_rtypes((Symbol *) rtree->l,(Symbol *) term->l,& tmpchain))
								{
								chain_pos -> l = tmpchain;
								while (chain_pos -> l)
									chain_pos=chain_pos->l;
								return TRUE;
								}
						}
					else if ((match2(term->l,rtree->l)) && (match2(term->r,rtree->r)))
								return TRUE;
				
				RESTORE
				return FALSE;
				}
	else			/* Here term and rtree differ ! */
		{

		DEBG((5,"Terms don't match : returned False !\n"));

		RESTORE
  	return FALSE;
		}
}

Node * match (Node * term,Node * rtree)
{
static Node dummy = {
CHAIN,
NULL,
NULL
};

repl_node = &dummy; /* so that in_tree does not return NULL ! */

if(match2(term,rtree))
	return repl_node;
else
	return (Node *) NULL;
}

BOOLEAN testrewrite _2a ((term,formterm) , Node * term ,Node * formterm)
{
		DEBG((4,"testrewrite : trying Term : "));
		DBFN(4,print(term));
		DEBG((4,"  , Form : "));
		DBFN(4,print(formterm));
		DEBG((4,"\n"));

	if (term == formterm) /* Compare symbols / pointers (also NULL !!) */
		return TRUE;

	if (((formterm -> type) == SYM_TYPE))
		{
		if  (lexval((Symbol *) formterm) == Var) /* Replace variable */
			{
			/* formerly : if (!eq_sorts(rtypes((Symbol *) formterm),rtypes((Symbol *) term->l))) /* term -> l goes into the symbol table */
      /*  return FALSE; */
                                            /* Types (also function results) match now */
			if (hasval(formterm))
        if ((term->type != Const) /****/
					|| ! hasval(term->l))    /* only replace numeric Const */
				return FALSE;

			chain_pos = chain_pos -> l = mknod(CHAIN,NULL,NULL);
			chain_pos->r = (Node *) formterm;
			DEBG((4,"Variable ersetzt : "));
			DBFN(4,print(formterm));

			(* formterm) = (* term);	/* only possible replacement directly in the symbol table !*/
												/* formterm->l is overwritten !! */
			DEBG((4,"-> "));
			DBFN(4,print(formterm));
			DEBG((4,"\n"));

			return TRUE;
			}
		else			/* Compare constants or functions */
			{
			if (lexval((Symbol *) formterm) == Term)
				{
				return testrewrite(term,formterm->l); /* Skip the symbol slot */
				}

			   /* Compare numeric values ? */

         if ((lexval((Symbol *) term)==Const) &&
				 (lexval((Symbol *) formterm)==Const) && 
				 hasval(term) && hasval(formterm))
				if (rtypes((Symbol *) term) == rtypes((Symbol *) formterm))
					return (0==((int (*)(void *,void *)) cmp(rtypes((Symbol *) term)))(value(term),value(formterm)));
				else
					return FALSE;
			DEBG((4,"found different Symbols : returned False !\n"));
			return FALSE;
			}
	}

	if ((term -> type) == (formterm -> type))
			switch (formterm->type)
			{
			case Func:
			case Ru:
			case Ra:
			case La1:
			case La2:
			case La3:
			case La4:
			case La5:
						/* first compare names, then compare terms */
			default:
				if ((testrewrite(term->l,formterm->l)) && (testrewrite (term->r,formterm->r)))
					return TRUE;
				else
					return FALSE;
				break;
			}
	else			/* Here term and form differ ! */
		{
		DEBG((4,"Terms don't match : returned False !\n"));
		return FALSE;
		}
}


