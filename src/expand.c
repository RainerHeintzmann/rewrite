/*
 *	expand.c (2026)
 *
 *	Settings for optional pattern parts and commutative operators, and
 *	condition lists, see expand.h.
 *
 *	Rules that are defined while OPT, DEFAULT or COMM are active go into a
 *	rule list (listmatch.c) together with a copy of the settings; the
 *	backtracking matcher there handles the missing operands and the
 *	operand orders. All other rules go into the rule tree of forms.c as
 *	before.
 *
 *	Example: with  OPT Ka,Kb   DEFAULT + = 0   DEFAULT * = 1   COMM +,*
 *	the pattern  Ka+Kb*Xv  also matches  Xv*Kb+Ka, Kb*Xv (Ka = 0),
 *	Ka+Xv (Kb = 1) and Xv (Ka = 0, Kb = 1).
 */

#include <string.h>
#include <stdlib.h>

#include "inout.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "node.h"
#include "forms.h"
#include "nodes.h"
#include "listmatch.h"
#include "expand.h"

#define MAXTAB 128

static Symbol * opt_vars[MAXTAB];		/* optional meta variables */
static int n_opt = 0;

static Symbol * comm_funcs[MAXTAB];		/* commutative functions */
static int n_comm = 0;

static struct {
	Symbol * f;			/* function */
	Node * value;			/* default value (term) */
	BOOLEAN right_only;	/* only the right operand may be missing */
} defaults[MAXTAB];
static int n_def = 0;

/* ---------------- statements ---------------- */

static void mark_optional (Symbol * sp)
{
	int i;
	if (lexval(sp) != Var)
		{
		printfErr("error : OPT %s : only pattern variables (PAT, NUMPAT) can be optional !\n",name(sp));
		return;
		}
	for (i = 0; i < n_opt; i++)
		if (opt_vars[i] == sp) return;
	if (n_opt >= MAXTAB) fatal("OPT : too many optional variables");
	opt_vars[n_opt++] = sp;
}

void opt_fn (Node * np)		/* FUNC(opt_fn, idlist); without list: clear */
{
	Node * l;
	if (! INSTR_PAR(np)) { n_opt = 0; return; }
	for (l = INSTR_PAR(np); l->type == Id; l = l->r)
		mark_optional((Symbol *) l->l);
	mark_optional((Symbol *) l);
}

static void mark_comm (Symbol * sp)
{
	int i;
	for (i = 0; i < n_comm; i++)
		if (strcmp(name(comm_funcs[i]),name(sp)) == 0) return;
	if (n_comm >= MAXTAB) fatal("COMM : too many functions");
	comm_funcs[n_comm++] = sp;
}

void comm_fn (Node * np)		/* FUNC(comm_fn, funclist); without list: clear */
{
	Node * l;
	if (! INSTR_PAR(np)) { n_comm = 0; return; }
	for (l = INSTR_PAR(np); l->type == Functs; l = l->r)
		mark_comm((Symbol *) l->l);
	mark_comm((Symbol *) l);
}

void default_fn (Node * np)	/* FUNC(default_fn, PARAM(PARAM(f, right_only), value)) */
{
	Symbol * f;
	BOOLEAN right;
	int i;
	if (! INSTR_PAR(np))		/* DEFAULT without arguments: clear */
		{
		for (i = 0; i < n_def; i++)
			delete(defaults[i].value);
		n_def = 0;
		return;
		}
	f     = (Symbol *) np->r->l->l;
	right = (np->r->l->r != NULL);
	for (i = 0; i < n_def; i++)
		if (strcmp(name(defaults[i].f),name(f)) == 0) break;
	if (i == n_def)
		{
		if (n_def >= MAXTAB) fatal("DEFAULT : too many functions");
		n_def++;
		}
	else
		delete(defaults[i].value);
	defaults[i].f          = f;
	defaults[i].value      = np->r->r;
	defaults[i].right_only = right;
	np->r->r = NULL;	/* value is kept in the table */
}

BOOLEAN and_cond (Node * np)	/* PARAM(Cond, Cond) */
{
	return COND_CALL(np->l) && COND_CALL(np->r);
}

/* ---------------- rules ---------------- */

static BOOLEAN settings_active (void)
{
	return n_opt > 0 || n_comm > 0 || n_def > 0;
}

/* copy of the settings for a rule list:
 *	PARAM(optvars, PARAM(commfuncs, defaults)), lists of PARAM nodes;
 *	a default is PARAM(PARAM(fsym, value), rightflag) */
static Node * settings_snapshot (void)
{
	Node * opts = NULL, * comms = NULL, * defs = NULL;
	int i;
	for (i = n_opt - 1; i >= 0; i--)
		opts = mknod(PARAM, (Node *) opt_vars[i], opts);
	for (i = n_comm - 1; i >= 0; i--)
		comms = mknod(PARAM, (Node *) comm_funcs[i], comms);
	for (i = n_def - 1; i >= 0; i--)
		defs = mknod(PARAM,
		         mknod(PARAM, mknod(PARAM, (Node *) defaults[i].f, tcopy(defaults[i].value)),
		               defaults[i].right_only ? mknod(PARAM, NULL, NULL) : NULL),
		         defs);
	return mknod(PARAM, opts, mknod(PARAM, comms, defs));
}

Node * add_rule (Node * lhs, Node * res, Node * tree)
{
	if (tree && tree->type == RULELIST)
		return rulelist_add(tree, lhs, res, settings_active() ? settings_snapshot() : NULL);
	if (settings_active())
		{
		if (! tree)
			return rulelist_add(NULL, lhs, res, settings_snapshot());
		printfErr("warning : rule added without OPT/COMM/DEFAULT, because the algebra already has ordinary rules !\n");
		}
	return merge(lhs, res, tree);
}
