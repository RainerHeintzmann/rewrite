/* forms.c */
/* Baum fuer Formeln der Algebren */

#include "inout.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "forms.h"
#include "node.h" /* auch symeq */
#include "sync.h"  /* Fuer IS_follows, lock_rtypes */
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
	return mknod(ERSETZ_TYPE,form,Ersetz);  /* tcopy benutzen ?? (Aber geht nicht wegen Cond) */
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
			return FALSE; /* Metavariablen duerfen nie passen, da es sonst spaeter Entscheidungsprobleme fuer das restaurieren der Variablen gibt : */

	if (form == Baum)
		return TRUE;   /* Teilbaeume sind identisch (Symbole oder NULL) */

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
		/*	tmp = merge2(form,Baum->l);  /* Tiefe mitzaehlen, besseren Baum nehmen */
	  /* 	} */
		/* else */
		/* 	{ */
		/* 	merk_p_baum = &(Baum->r); */
		/* 	tmp = merge2(form,Baum->r);  /* Tiefe mitzaehlen, besseren Baum nehmen */
		/* 	} */

		depthcount += merk_depth;
		merk_p_baum = &(Baum->r); 
    matched_ers = FALSE;
		tmp = merge2(form,Baum->r);  /* Besser Tiefe mitzaehlen, besseren Baum nehmen */
		if (! tmp)  /* siehe auch unten */
			if (wo_ers == (Node * *) NULL)
				{
				wo_ers = &(Baum->r);
				neu_ers = form;
				wo_ers_weg = alt_ers_weg;
				alt_ers = in_ers;
				}
		return tmp;
		}


	if (  (form -> type == SYM_TYPE)   /* evt. gleicher Wert ? */
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
		if (form->type==Baum->type)   /* Term oder Func ,.. */
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
				if ((!m1)       /* && (!m2) aber Probleme bei Func-dann OR-Knoten ! */
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
						matched_ers = FALSE; /* Zuruecksetzen, neachste moegliche Ersetzung findet statt */
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
					alt_ers=NULL; /* Oberer ER-Knoten wird ganz ersetzt */
				else
          Baum = Baum->l; /* Da ER-Knoten in den Teilbaum gezogen wird ! */
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

			/* passende Formel gefunden , nun Condition pruefen */
			if (COND_CALL(RES_COND(Baum->r)))	/* Condition fuer Gleichung */
				{
				ersetz = Baum->r; /* Condition passt auch ! */
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

			switch (term->type)	/* Sucht zu term gehoeredes Symbol */
				{
				case Const: 
				case Func:  tsym=(Symbol *) term->l;
										break;
				case SYM_TYPE:
										tsym=(Symbol *) term;
										break;
				default:
										RESTORE
										return FALSE; /* Passiert schon mal im Baum ! */
										/* printfErr("match2: Internal ERROR : term : ");
										   print(term);
										   printfErr("Baum : ");
										   print(Baum);
										   printfErr("(unexpected term-type) Nr.:%d !\n",term->type); */
				}

		if  (lexval((Symbol *) Baum) == Var) /* Variable ersetzen */
			{
			if ((term->type != Const) 
					&& (term->type != Func)) /* Gewuenscht : Const,Func */
				{
				printfErr("match2: ERROR : unexpected term-type : ");
				print(term);
				printfErr("  Typenr. : %d (matching Var) \n",term->type);
				RESTORE
				return FALSE;
				}

			/* Verschiedene Sorts werden auch zugeordnet, ehemals: if (! eq_sorts(rtypes((Symbol *) Baum),rtypes(tsym))) return FALSE;*/

                       /* Typen (auch Fkt.resultate) stimmen nun */

			if (hasval(Baum))                 /* Numerische Variable ? */
       if (!(lexval(tsym) == Const)
  				|| ! hasval(tsym))            /* nur Numerische Const / Func ersetzen */
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
			chain_pos->r = (Node *) Baum; /* Neue Pos. belegen */
			DEBG((4,"Variable ersetzt : "));
			DBFK(4,print(Baum));

				Baum->type = term->type;  /* Const oder Func */
				Baum->l = term->l;
				Baum->r = term->r;

	/* (* Baum) = (* term);	einzig moegl. Ersetzung direkt in der Symboltabelle ! */
		   												/* Node-Struktur wird kopiert (und so ueberschrieben !) */

				DEBG((4,"-> "));
				DBFK(4,print(Baum));
				DEBG((4,"\n"));

			return TRUE;
			}
		else			/* Constanten oder Funktionen vergleichen */
			{
			if (lexval((Symbol *) Baum) == Term)
				{
				return match2(term,Baum->l); /* Symbol-Platz ueberspringen */
				}
			return symeq((Symbol *) term,(Symbol *) Baum);
			}
	}

	if ((term -> type) == (Baum -> type))
				{

				if (term->type == Func)
					{	
					Node * tmpchain = NULL;
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
								{ /* locks loeschen */
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
	else			/* Hier unterscheiden sich term, Baum ! */
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

ersetz = &dummi; /* damit fuer in_tree nicht NULL zurueck kommt ! */

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

	if (term == formterm) /* Symbole / Zeiger vergleichen (auch NULL !!) */
		return TRUE;

	if (((formterm -> type) == SYM_TYPE))
		{
		if  (lexval((Symbol *) formterm) == Var) /* Variable ersetzen */
			{
			/* ehemals : if (!eq_sorts(rtypes((Symbol *) formterm),rtypes((Symbol *) term->l))) /* term -> l geht in die Symboltabelle */
      /*  return FALSE; */
                                            /* Typen (auch Fkt.resultate) stimmen nun */
			if (hasval(formterm))
        if ((term->type != Const) /****/
					|| ! hasval(term->l))    /* nur Numerische Const ersetzen */
				return FALSE;

			chain_pos = chain_pos -> l = mknod(CHAIN,NULL,NULL);
			chain_pos->r = (Node *) formterm;
			DEBG((4,"Variable ersetzt : "));
			DBFK(4,print(formterm));

			(* formterm) = (* term);	/* einzig moegl. Ersetzung direkt in der Symboltabelle !*/
												/* formterm->l wird ueberschrieben !! */
			DEBG((4,"-> "));
			DBFK(4,print(formterm));
			DEBG((4,"\n"));

			return TRUE;
			}
		else			/* Constanten oder Funktionen vergleichen */
			{
			if (lexval((Symbol *) formterm) == Term)
				{
				return testrewrite(term,formterm->l); /* Symbol-Platz ueberspringen */
				}

			   /* Numerische Werte vergleichen ? */

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
						/* erst Namen vergleichen, dann Terms vergleichen */
			default:
				if ((testrewrite(term->l,formterm->l)) && (testrewrite (term->r,formterm->r)))
					return TRUE;
				else
					return FALSE;
				break;
			}
	else			/* Hier unterscheiden sich term, form ! */
		{
		DEBG((4,"Terms don't match : returned False !\n"));
		return FALSE;
		}
}


