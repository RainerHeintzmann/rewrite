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

extern Node * chain_pos;
extern Node var_chain;

static Node * alt_ers,
            * in_ers,
            * neu_ers,
            * ers_arg,
          * * wo_ers,
          * * wo_ers_weg,
          * * alt_ers_weg,
          * * merk_p_baum;

static BOOLEAN matched_ers;
static int depthcount;
static Node * ersetz;

Node * einhaengen (Node * form,Node * Ersetz)
{
	return mknod(ERSETZ_TYPE,form,Ersetz);  /* use tcopy ?? (But does not work because of Cond) */
}

Node * mkor(Node * l,Node * r)
{
	DEBG((4,"Mache ODER-Knoten im Formel-Baum :"));
	DBFK(4,print(r->l));
	DEBG((4,"\n"));
	return mknod(OR_TYPE,l,r);
}

Node * instree(Node * Baum,Node * form,Node * Ersetz)
{
		DEBG((5,"instree: Baum: "));
		DBFK(5,print(Baum));
		DEBG((5,",form: "));
		DBFK(5,print(form));
		DEBG((5,"\n"));

if (alt_ers == (Node *) NULL)
	{
	return mkor(Baum,einhaengen(form,Ersetz));
	}
else
	{
	alt_ers->l = Baum;
	return mkor(alt_ers,einhaengen(form,Ersetz));
	}
}

BOOLEAN merge2(Node * form,Node * Baum)
{
	DEBG((5,"Merge2 form: "));
	DBFK(5,print(form));
	DEBG((5,",tree: "));
	DBFK(5,print(Baum));
	DEBG((5,"\n"));

	depthcount++;
	if ((form != NULL) && (Baum != NULL) 
		&& (form->type == SYM_TYPE) && (Baum->type == SYM_TYPE)
		&& (lexval((Symbol *) form) == Var) && (lexval((Symbol *) Baum) == Var))
			return FALSE; /* Metavariables must never match, otherwise there are decision problems later when restoring the variables : */

	if (form == Baum)
		return TRUE;   /* Subtrees are identical (symbols or NULL) */

	if ((Baum == (Node *) NULL) || (form == (Node *) NULL))
		{
		return FALSE;
		}
		
	if (Baum->type==ERSETZ_TYPE)
		{
		BOOLEAN tmp;
    in_ers = Baum;
		alt_ers_weg = merk_p_baum;
#ifdef DEBUG
			if (alt_ers_weg == (Node **)NULL)
				DEBG((5," merk_p_baum is NULL !\n"));
#endif			
		merk_p_baum = &(Baum->l);
		if (tmp=merge2(form,Baum->l))
			{
			DEBG((6," matched ers. !\n"));
	    matched_ers = TRUE;
			}
    in_ers = NULL;
		alt_ers_weg = (Node **) NULL;
		return tmp;		
		}

	if (Baum->type==OR_TYPE)
		{
		BOOLEAN tmp;
		int depth1,depth2,merk_depth;
		depth1 = 0;
		depth2 = 0;
		merk_depth=depthcount;
		depthcount = 0;
		if (in_ers != (Node *) NULL)
			fatal("internal-error: merge2 did not expect ERSETZ before OR");

		/* merk_p_baum = &(Baum->l);
    matched_ers = FALSE;
		if (merge2(form,Baum->l))
			{
			depthcount += merk_depth;
			return TRUE;
			}
		depth1=depthcount; */

		/* depthcount =0;
		merk_p_baum = &(Baum->r);
    matched_ers = FALSE;
		if (merge2(form,Baum->r))
			{
			depthcount += merk_depth;
			return TRUE;
			}
		depth2=depthcount;
		
		depthcount =0;
    matched_ers = FALSE; */
		/* if (depth1 >= depth2) */
		/* 	{  */
		/* 	merk_p_baum = &(Baum->l); */
		/*	tmp = merge2(form,Baum->l);  /* count depth, take the better tree */
	  /* 	} */
		/* else */
		/* 	{ */
		/* 	merk_p_baum = &(Baum->r); */
		/* 	tmp = merge2(form,Baum->r);  /* count depth, take the better tree */
		/* 	} */

		depthcount += merk_depth;
		merk_p_baum = &(Baum->r); 
    matched_ers = FALSE;
		tmp = merge2(form,Baum->r);  /* Better: count depth, take the better tree */
		if (! tmp)  /* see also below */
			if (wo_ers == (Node * *) NULL)
				{
				wo_ers = &(Baum->r);
				neu_ers = form;
				wo_ers_weg = alt_ers_weg;
				alt_ers = in_ers;
				}
		return tmp;
		}


	if (  (form -> type == SYM_TYPE)   /* possibly the same value ? */
		 && (Baum -> type == SYM_TYPE))
		{
		BOOLEAN tmp=symeq((Symbol *) form,(Symbol *) Baum);
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
		if (form->type==Baum->type)   /* Term or Func ,.. */
			{
				BOOLEAN m1,m2,merk_ers;

				merk_p_baum = &(Baum->l);
				m1= merge2(form->l,Baum->l);
				merk_ers = matched_ers;
				merk_p_baum = &(Baum->r);
				m2= merge2(form->r,Baum->r);
				if (! matched_ers)
					matched_ers = merk_ers;

				if (m1 && m2)
					{
					DEBG((6,"merge2: matched two eqal terms:"));
					DBFK(6,print(Baum->l));
					DEBG((6,", "));
					DBFK(6,print(Baum->r));
					DEBG((6,", ret. true.\n"));
					return TRUE;
					}
				if (! m1)
					if (wo_ers == (Node * *) NULL)
						{
						wo_ers = &(Baum->l);
						neu_ers = form->l;
						wo_ers_weg = alt_ers_weg;
						alt_ers = in_ers;
						}
				if (! m2)
					if (wo_ers == (Node * *) NULL)
						{
						wo_ers = &(Baum->r);
						neu_ers = form->r;
						wo_ers_weg = alt_ers_weg;
						alt_ers = in_ers;
						}
				if ((!m1)       /* && (!m2) but problems with Func followed by OR node ! */
				  || ( matched_ers))
						{
						if (! matched_ers)
							{
							DEBG((6,"merge2: Got two wrong Terms, wo_ers := NULL : "));
							DBFK(6,print(Baum->l));
							DEBG((6,", "));
							DBFK(6,print(form->l));
							DEBG((6,"und "));
							DBFK(6,print(Baum->r));
							DEBG((6,", "));
							DBFK(6,print(form->r));
							DEBG((6,"\n"));
							}

						wo_ers = (Node * *) NULL;
						alt_ers = in_ers;
						matched_ers = FALSE; /* Reset, the next possible replacement takes place */
						}
				else
						depthcount--;
				return FALSE;
			}

	return FALSE;
}

Node * merge(Node * form,Node * Ersetz,Node * Baum)
{
	DEBG((5,"Merge form: "));
	DBFK(5,print(form));
	DEBG((5,"in tree: "));
	DBFK(5,print(Baum));
	DEBG((5,"\n"));

	if (Baum == (Node *) NULL)
		return einhaengen(form,Ersetz);
  else
    {
		in_ers  = (Node *) NULL;
		alt_ers = (Node *) NULL;
		wo_ers  = (Node * *) NULL;
		neu_ers = (Node *) NULL;
		ers_arg = (Node *) NULL;
		wo_ers_weg = (Node * *) NULL;
		merk_p_baum = (Node * *) NULL;
		alt_ers_weg = (Node * *) NULL;
		matched_ers = FALSE;

		if (! merge2(form,Baum))
			{
			if (alt_ers==Baum)
				if (wo_ers == (Node **) NULL)
					alt_ers=NULL; /* Upper ER node is replaced entirely */
				else
          Baum = Baum->l; /* Because the ER node is pulled into the subtree ! */
			else
					if (alt_ers != (Node *) NULL)
						(* wo_ers_weg) = alt_ers->l;

			if (wo_ers == (Node * *) NULL)
				{
				DEBG((6,"wo_ers == NULL \n"));
				return instree(Baum,form,Ersetz);
				}

			(* wo_ers) = instree(* wo_ers,neu_ers,Ersetz);
			return Baum;
			}
		return Baum;
		}
}


BOOLEAN match2 (Node * term,Node * Baum)
{
	DEBG((5,"match2: term:"));
	DBFK(5,print(term));
	DEBG((5,",tree: "));
	DBFK(5,print(Baum));
	DEBG((5,"\n"));

	if (term == Baum)
		{
		DEBG((6,"match2: pointers are eqal: "));
		DBFK(6,print(term));
		DEBG((6,"\n"));
		return TRUE;
		}

	if ((Baum == (Node *) NULL) || (term == (Node *) NULL))
		{
		RESTORE
		return FALSE;
		}

	if (Baum->type==ERSETZ_TYPE)
		{
		DEBG((6,"match2: found ER-Type := "));
		DBFK(6,print(Baum->l));
		DEBG((6," ; "));
		DBFK(6,print(Baum->r));
		DEBG((6,"\n"));

		if (match2(term,Baum->l) == TRUE)
			{
			DEBG((6,"match2: ersetz := "));
			DBFK(6,print(Baum->r));
			DEBG((6,"\n"));

			/* matching formula found, now check the condition */
			if (COND_CALL(RES_COND(Baum->r)))	/* Condition for the equation */
				{
				ersetz = Baum->r; /* Condition matches too ! */
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

	if (Baum->type==OR_TYPE)
		{
		if (match2(term,Baum->l))
			return TRUE;
		if (match2(term,Baum->r))
			return TRUE;
		RESTORE
		return FALSE;
		}

	if (((Baum -> type) == SYM_TYPE))
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
										/* printfErr("match2: Internal ERROR : term : ");
										   print(term);
										   printfErr("Baum : ");
										   print(Baum);
										   printfErr("(unexpected term-type) Nr.:%d !\n",term->type); */
				}

		if  (lexval((Symbol *) Baum) == Var) /* Replace variable */
			{
			if ((term->type != Const) 
					&& (term->type != Func)) /* Wanted : Const,Func */
				{
				printfErr("match2: ERROR : unexpected term-type : ");
				print(term);
				printfErr("  Typenr. : %d (matching Var) \n",term->type);
				RESTORE
				return FALSE;
				}

			/* Different sorts are assigned too, formerly: if (! eq_sorts(rtypes((Symbol *) Baum),rtypes(tsym))) return FALSE;*/
			/* 2026: except for subsorts (VAR X : nonneg only matches nonneg) */
			if (! var_sort_ok(rtypes((Symbol *) Baum), term))
				{
				RESTORE
				return FALSE;
				}

                       /* Types (also function results) match now */

			if (hasval(Baum))                 /* Numeric variable ? */
       if (!(lexval(tsym) == Const)
  				|| ! hasval(tsym))            /* only replace numeric Const / Func */
        {
			/*	 Node * erg1=calkulate (term);
					if (!erg1 || rtypes((Symbol *) erg1) != numbertype)
					{
					RESTORE
					return FALSE;
					}
				 else
					delete(erg1); */

					RESTORE
					return FALSE;
				}

			chain_pos = chain_pos -> l = mknod(CHAIN,NULL,NULL);
			chain_pos->r = (Node *) Baum; /* Occupy new position */
			DEBG((4,"Variable ersetzt : "));
			DBFK(4,print(Baum));

				Baum->type = term->type;  /* Const or Func */
				Baum->l = term->l;
				Baum->r = term->r;

	/* (* Baum) = (* term);	only possible replacement directly in the symbol table ! */
		   												/* Node structure is copied (and thus overwritten !) */

				DEBG((4,"-> "));
				DBFK(4,print(Baum));
				DEBG((4,"\n"));

			return TRUE;
			}
		else			/* Compare constants or functions */
			{
			if (lexval((Symbol *) Baum) == Term)
				{
				return match2(term,Baum->l); /* Skip the symbol slot */
				}
			return symeq((Symbol *) term,(Symbol *) Baum);
			}
	}

	if ((term -> type) == (Baum -> type))
				{

				if (term->type == Func)
					{	
					Node * tmpchain = NULL;
					if (term->l != Baum->l && variant_fits((Symbol *) term->l,(Symbol *) Baum->l)
					    && ! IS_follows((Symbol *) term->l,(Symbol *) Baum->l))
						return match2(term->r,Baum->r);	/* 2026: + : real,real for + : number,number */
					if (IS_follows((Symbol *) term->l,(Symbol *) Baum->l))
						if (lock_rtypes((Symbol *) Baum->l,(Symbol *) term->l,& tmpchain))
							if (match2(term->r,Baum->r))
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
									IS_Verbindung((Symbol *) (tmpchain->r))=(Symbol *) NULL;
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
						if (IS_follows((Symbol *) term->l,(Symbol *) Baum->l))
							if (lock_rtypes((Symbol *) Baum->l,(Symbol *) term->l,& tmpchain))
								{
								chain_pos -> l = tmpchain;
								while (chain_pos -> l)
									chain_pos=chain_pos->l;
								return TRUE;
								}
						}
					else if ((match2(term->l,Baum->l)) && (match2(term->r,Baum->r)))
								return TRUE;
				
				RESTORE
				return FALSE;
				}
	else			/* Here term and Baum differ ! */
		{

		DEBG((5,"Terms don't match : returned False !\n"));

		RESTORE
  	return FALSE;
		}
}

Node * match (Node * term,Node * Baum)
{
static Node dummi = {
CHAIN,
NULL,
NULL
};

ersetz = &dummi; /* so that in_tree does not return NULL ! */

if(match2(term,Baum))
	return ersetz;
else
	return (Node *) NULL;
}

BOOLEAN testrewrite _2a ((term,formterm) , Node * term ,Node * formterm)
{
		DEBG((4,"testrewrite : trying Term : "));
		DBFK(4,print(term));
		DEBG((4,"  , Form : "));
		DBFK(4,print(formterm));
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
			DBFK(4,print(formterm));

			(* formterm) = (* term);	/* only possible replacement directly in the symbol table !*/
												/* formterm->l is overwritten !! */
			DEBG((4,"-> "));
			DBFK(4,print(formterm));
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


