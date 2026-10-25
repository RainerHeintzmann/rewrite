/* node.c  :   memory management for nodes  ( for speed) */

#include <stdlib.h>
#include <string.h> /* memset */
#include "inout.h"
#include "strsave.h"
#include "sym.h"
#include "node.h"
#include "syn.h"
#include "numsort.h"	/* 2026: SUBSORT (symeq) */

#define ANZNODES 1024

extern Node * numbertype; /* run.c */

const char * numbername = "flt"; /* Unique identification of a number via this const. */

static int i;
static Node * nodestack = NULL;
static Symbol * symbolstack = NULL;

static char * prtnumstring = "%g ";


static Symbol stdsort={ /* Global standard real set */
{SYM_TYPE,
(Node *) NULL,
(Node *) NULL
},
"StdSort",
Sort,
(Node *) std_cmp_real,
(Node *) std_cpy_real,
TRUE,
(void *) std_show_real,
(Symbol *) NULL,
0,
(Symbol *) std_del_real,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
0
};

/* special numbers 0,1  , so that lifting always starts at the same symbol. */
static double Zero = 0.0;
static double One  = 1.0;

static Symbol Zero_Symbol={
{SYM_TYPE,
(Node *) NULL,
(Node *) NULL
},
"0",
Const,
(Node *) & stdsort,
(Node *) NULL,
TRUE,
(void *) & Zero,
NULL,
0,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
0
};

static Symbol One_Symbol={
{SYM_TYPE,
(Node *) NULL,
(Node *) NULL
},
"1",
Const,
(Node *) & stdsort,
(Node *) NULL,
TRUE,
(void *) & One,
NULL,
0,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
(Symbol *) NULL,
0
};

/* Functions for the standard handling of real numbers : */

/* void std_show_cont (double * * x)
{
	int anz;
	anz = (int) (* x++);
	printfOut("[ ");
	for (i=0;i< (anz-1);i++)
		{print(x++);
		printfOut(", ");
		}
	print(x);
	printfOut("] ");
}

int std_cmp_cont (double * x,double * y)
{
	int anz1,anz2;
	anz1 = (int) (* x++);
	anz2 = (int) (* y++);
	return (anz1 > anz2) ? 1 : ((anz1 == anz2) ? 0 : -1);
} */	


void std_show_real (double * x)
{
	printfOut(prtnumstring,* x);
}

double * std_cpy_real (double * x)
{
double * dp;
  DEBG((5,"hier std_cpy_real (%g) \n",*x));

	dp = malloc(sizeof(double));
	if (NULL==(void *) dp)
		fatal("(std_cpy_real) ERROR no Space for making double !\n");
	(* dp) = (* x);
return dp;
}

int std_cmp_real (double * x,double * y)
{
  DEBG((5,"hier std_cmp_real (%g,%g) \n",*x,*y));

	return ((* x) > (* y)) ? 1 : (((*x) == (*y)) ? 0 : -1);
}

void std_del_real (double * x)
{
free(x);
return;
}

void prt_num(Node * np)
{
	prtnumstring=name((Symbol *) np->r);
}

BOOLEAN symeq (Symbol * a,Symbol * b) /* Compares two symbols for equality */
{
BOOLEAN tmp;
	DEBG((6,"symeq("));
	DBFN(6,print(((Node *) a)));
	DEBG((6,", "));
	DBFN(6,print((Node *) b));
	DEBG((6,") \n"));

if (a==b) return TRUE;

if (!hasval(a) || ! hasval(b))
	return FALSE;

if ((lexval(a) != Const) || (lexval(b)!=Const))
	return FALSE;

/* Compare numeric values ? */

if (rtypes(a) != rtypes(b))  /* result types */
	{			/* 2026: numbers of different sorts of a SUBSORT chain */
	Node * sa = rtypes(a), * sb = rtypes(b), * to = NULL;
	void * w;
	BOOLEAN eq;
	if (sort_dist(sa, sb) > 0) to = sb;
	else if (sort_dist(sb, sa) > 0) to = sa;
	if (! to) return FALSE;
	if (to == sb)
		{
		w = sort_convert(value(a), sa, sb);
		if (! w) return FALSE;
		eq = (0==((int (*)(void *,void *)) cmp(sb))(w,value(b)));
		}
	else
		{
		w = sort_convert(value(b), sb, sa);
		if (! w) return FALSE;
		eq = (0==((int (*)(void *,void *)) cmp(sa))(value(a),w));
		}
	((void (*) (void *)) del(to)) (w);
	return eq;
	}

tmp=(0==((int (*)(void *,void *)) cmp(rtypes(a)))(value(a),value(b)));

#ifdef DEBUG
	DEBG((6,"symeq: cmp returned "));
	if (tmp)
		DEBG((6,"true \n"));
	else
		DEBG((6,"false \n"));
#endif
return tmp;
}


Node * mknod (int type, Node * l, Node * r)
{ Node * p;
  if (! nodestack) 
		{
		if (! (nodestack = (Node *) malloc(sizeof(Node)*ANZNODES)))
			fatal("mknod: no room");
		for (i=0;i<(ANZNODES-1);i++)
			{
			nodestack[i].type = 0;
			nodestack[i].l = &(nodestack[i+1]);
			nodestack[i].r = NULL;
			}
		nodestack[i].type = 0;
		nodestack[i].l = NULL;
		nodestack[i].r = NULL;
		}

	p = nodestack;
	nodestack = p->l;
	p -> type = type;
	p -> l = l;
	p -> r = r;
	return p;
	
}

void delnod (Node * node)
{
	node -> l = nodestack;
	nodestack	= node;
	return;	
}


Symbol * mksym (int lexv,const char * name)  /* creates a symbol */
{
	Symbol * newsym;

  if (! symbolstack) 
	{
	if (! (symbolstack = (Symbol *) calloc(ANZNODES,sizeof(Symbol))))
     fatal("making symbol/number : no room");

	DEBG((3,"DB : mksym : allocated %d Bytes new symbol-space\n",(ANZNODES*sizeof(Symbol))));

	for (i=0;i<(ANZNODES-1);i++)
		{
		symbolstack[i].node.type = 0;
		symbolstack[i].node.l = (Node *) &(symbolstack[i+1]);
		symbolstack[i].node.r = NULL;
		}
	symbolstack[i].node.type = 0;
	symbolstack[i].node.l = NULL;
	symbolstack[i].node.r = NULL;
	}

	newsym = symbolstack;
	symbolstack = (Symbol *) newsym->node.l;
	memset(newsym, 0, sizeof(Symbol)); /* reused slot: no old atypes/value etc. */
	newsym->node.type = SYM_TYPE;
	newsym->node.l = NULL;
	newsym->node.r = NULL;
	defined_in_block(newsym) = 0;
	if (name) 
		name(newsym)=strsave(name);
	else
		name(newsym)="(not saved)";
	lexval(newsym) = lexv;

	DEBG((4,"DB : mksym : New Id : %s\n",name(newsym)));

	return newsym;
}

/* frees a numeric value with the delete function of its number type */
static void free_number_value (void * value)
{
	Symbol * srt = numbertype ? (Symbol *) numbertype : & stdsort;
	if (del(srt))
		((void (*) (void *)) del(srt)) (value);
}

/* mknum takes over the value 'value'. For 0 and 1 the shared
 * symbol is returned and 'value' is freed. */
Symbol * mknum (void * value,Node * rtype)
{
Symbol * sp;

  DEBG((4,"hier mknum\n"));
	if (! rtype) 
		{
		rtype=numbertype;
		}
	if (! numbertype)
		printfErr("You have to set numbertype first (NUM Sort) !\n"); 

	if (rtype == numbertype) /* is set via NUM Sort */
		{
		if (* (double *) value == 0.0)
			{
			if (numbertype) rtypes(& Zero_Symbol) = numbertype;
			else
				rtypes(& Zero_Symbol) = ( Node *) & stdsort;
			free_number_value(value); /* the shared symbol has its own value */
			return & Zero_Symbol;
			}
		if (* (double *) value == 1.0)
			{
			if (numbertype) rtypes(& One_Symbol) = numbertype;
			else
				rtypes(& One_Symbol) = ( Node *) & stdsort;
			free_number_value(value); /* the shared symbol has its own value */
			return & One_Symbol;
			}
		}

	sp=mksym(Const,NULL); /* NULL, so that strsave is not used */
	name(sp)   = numbername;

 	rtypes(sp) = rtype;

	if (! numbertype)
		{
		rtypes(sp) = (Node *) & stdsort;
		}

	hasval(sp) = TRUE;
	value(sp) = value;
	return sp;
}

void delsym (Symbol * sp)
{
	DEBG((4,"delsym Symbol:"));
	DBFN(4,print((Node *) sp));
	DEBG((4,"\n"));

	if (! sp) return;

	if ((sp == & One_Symbol) || (sp == & Zero_Symbol))
		return;

	sp->node.type = SYM_TYPE;
	sp->node.r = NULL;
	name(sp) = "not used";
	lexval(sp) = 0;

	sp -> node.l = (Node *) symbolstack;
	symbolstack	= sp;
	return;
}

void delnum (Symbol * number,BOOLEAN delvalue)
{	
	DEBG((4,"hier delnum Number :"));
	DBFN(4,print((Node *) number));
	DEBG((4,"\n"));

	if (! number) return;

	if ((number == & One_Symbol) || (number == & Zero_Symbol))
		return;
	if (! rtypes(number))
		fatal("FATAL ERROR node.c : delnum: Number has no rtype");

	if (delvalue) DELNUM(number,value(number)); /* managed by the user ! (delnum) see sym.h */

	delsym(number);
	return;
}

void cpysym(Symbol * s1,Symbol * s2)
{
	(* s2) = * s1; /* do not free name(s) */
}

Symbol * clonesym(Symbol * s) /* names duplicated ! */
{	Symbol * sp=mksym(lexval(s),name(s));
	char * cp = name(sp);
	cpysym(s,sp);
	name(sp)=cp;
	return sp;
}


/* TRUE for the shared numbers 0 and 1 (Zero_Symbol, One_Symbol).
 * Their value lives in static memory and must never be handed to a variable
 * and later freed with free(). */
BOOLEAN is_shared_num (Symbol * sp)
{
	return (sp == & Zero_Symbol) || (sp == & One_Symbol);
}
