/*
 *	help.c (2026)
 *
 *	Help texts, as in Julia's REPL: the library declares them,
 *	    HELP "REWR" "REWR term : alg   rewrites term with the rule set alg"
 *	(each HELP adds a line to the text of the name), and a line that begins
 *	with ? asks for one:  ?REWR   ?Int   ? alone lists the names. Without a
 *	text, ?name shows what is known: the variants of a function (as TYPEOF),
 *	the kind and value of a name.
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inout.h"
#include "fatal.h"
#include "run.h"
#include "sym.h"
#include "syn.h"
#include "node.h"
#include "sync.h"
#include "help.h"
#include "defs.h"
#include "numsort.h"
#include "symfn.h"

typedef struct { char * name, * text; } HelpEntry;

static HelpEntry * tab = NULL;
static int ntab = 0, maxtab = 0;

static HelpEntry * find_help (const char * name)
{
	int i;
	for (i = 0; i < ntab; i++)
		if (! strcmp(tab[i].name, name)) return & tab[i];
	return NULL;
}

void help_def (Node * np)		/* FUNC(help_def, PARAM(name, text)) */
{
	const char * n = name((Symbol *) np->r->l), * t = name((Symbol *) np->r->r);
	HelpEntry * e = find_help(n);
	char * s;
	if (! e)
		{
		if (ntab == maxtab)
			{
			maxtab = maxtab ? 2 * maxtab : 64;
			tab = (HelpEntry *) realloc(tab, maxtab * sizeof(HelpEntry));
			if (! tab) fatal("help : no room");
			}
		e = & tab[ntab++];
		e->name = strdup(n);
		e->text = strdup("");
		}
	s = (char *) malloc(strlen(e->text) + strlen(t) + 2);	/* a further line */
	if (! s) fatal("help : no room");
	strcpy(s, e->text);
	if (* e->text) strcat(s, "\n");
	strcat(s, t);
	free(e->text);
	e->text = s;
}

static int cmp_entry (const void * a, const void * b)
{
	return strcmp(((const HelpEntry *) a)->name, ((const HelpEntry *) b)->name);
}

static void overview (void)
{
	HelpEntry * e = find_help("?");
	int i, col = 0;
	if (e) printfOut("%s\n\n", e->text);
	qsort(tab, ntab, sizeof(HelpEntry), cmp_entry);
	printfOut("Help on:");
	for (i = 0; i < ntab; i++)
		{
		int w = (int) strlen(tab[i].name) + 1;
		if (! strcmp(tab[i].name, "?")) continue;
		if (col + w > 72) { printfOut("\n       "); col = 0; }
		printfOut(" %s", tab[i].name);
		col += w;
		}
	printfOut("\n");
}

static int is_function (Symbol * s)
{
	switch (lexval(s))
		{
		case Func: case La1: case La2: case La3: case La4: case La5:
		case Ru: case Ra: case Bra: case Bra1:
			return 1;
		}
	return 0;
}

/* ---- TYPEOF of a rule set (ALG) and of a sort ---- */

#define MAXLISTED 12		/* names listed, then "... (n)" */

/* the names, without the internal ones of the library (beginning with _),
 * which are only counted */
static void print_names (const char * what, Symbol * s[], int n)
{
	int i, shown = 0, internal = 0;
	for (i = 0; i < n; i++)
		if (name(s[i])[0] == '_') internal++;
	if (n == 0) return;
	printfOut("  %s: ", what);
	for (i = 0; i < n && shown < MAXLISTED; i++)
		if (name(s[i])[0] != '_') printfOut("%s%s", shown++ ? ", " : "", name(s[i]));
	if (n - internal > MAXLISTED) printfOut(", ... (%d)", n - internal);
	if (internal) printfOut("%s%d internal (_name)", shown ? "; " : "", internal);
	printfOut("\n");
}

/* a list of rule sets (SPEC All : a, (b, c)): Algs(element, next), an
 * element is a rule set or a group Alg(list) */
int alglist_has (Node * l, Symbol * alg)
{
	for ( ; l && l->type == Algs; l = l->r)
		if (l->l->type == Alg ? alglist_has(l->l->l, alg) : (Symbol *) l->l == alg) return 1;
	return 0;
}

static void print_alglist (Node * l)
{
	for ( ; l && l->type == Algs; l = l->r)
		{
		if (l->l->type == Alg) { printfOut("("); print_alglist(l->l->l); printfOut(")"); }
		else printfOut("%s", name((Symbol *) l->l));
		if (l->r) printfOut(", ");
		}
}

#define MAXFOUND 512
static Symbol * found[MAXFOUND];
static int nfound;
static Symbol * target;

static void find_lists_with (Symbol * s)	/* rule lists that contain target */
{
	if (nfound < MAXFOUND && lexval(s) == Alg && atypes(s) && atypes(s)->type == Algs
	    && alglist_has(atypes(s), target))
		found[nfound++] = s;
}

void typeof_alg (Symbol * a)
{
	Node * r = atypes(a);
	Symbol * fn[64];
	int n;
	printfOut("ALG %s : ", name(a));
	if (! r)
		printfOut("no rules yet\n");
	else if (r->type == Algs)
		{
		printfOut("a list of rule sets, applied one after the other, (..) repeated\n"
		          "  until nothing changes: ");
		print_alglist(r);
		printfOut("\n");
		}
	else if (r->type == RULELIST)
		{
		Node * p;
		for (n = 0, p = r->l; p; p = p->r) n++;
		printfOut("%d rules in order (OPT, COMM, DEFAULT): tried one after the other,\n"
		          "  with backtracking; a rule whose condition fails passes to the next\n", n);
		}
	else
		{
		n = alg_rule_count(a);
		if (n >= 0) printfOut("%d rules, ", n);
		printfOut("matched together (one tree of their left sides)\n");
		}
	nfound = 0;
	target = a;
	for_all_symbols(find_lists_with);
	print_names("in the rule lists", found, nfound);
	n = rules_fn_users(a, fn, 64);
	print_names("defines the functions (ATT RULES)", fn, n);
}

static int is_function (Symbol * s);

static void find_of_sort (Symbol * s)	/* names with the sort target, by kind */
{
	Symbol * v;
	if (nfound >= MAXFOUND) return;
	switch (lexval(s))
		{
		case Const: case Term: case Var:
			if ((Symbol *) rtypes(s) == target && strcmp(name(s), "not used")) found[nfound++] = s;
			break;
		default:
			if (! is_function(s)) break;
			v = s;
			do	{		/* a variant with this result sort */
				if ((Symbol *) rtypes(v) == target) { found[nfound++] = s; break; }
				v = variants(v);
				} while (v && v != s);
		}
}

void typeof_sort (Symbol * s)
{
	Node * nb[32];
	Symbol * sy[MAXFOUND];
	int n, i, k, kinds[] = { Const, Term, Var, 0 };
	const char * what[] = { "symbols (SYM)", "terms (TERM)", "pattern variables (PAT)", "functions with this result" };
	printfOut("SORT %s : %s\n", name(s), sort_valued((Node *) s) ? "with values (computed in C)"
	                                                             : "no values of its own (symbolic terms only)");
	if ((Node *) s == get_numbertype()) printfOut("  number literals like 1.5 have this sort (REALNUM)\n");
	if ((Node *) s == int_literal_sort()) printfOut("  whole number literals like 3 have this sort (INTNUM)\n");
	n = sort_neighbours((Node *) s, 1, nb, 32);
	for (i = 0; i < n; i++) sy[i] = (Symbol *) nb[i];
	print_names("wider sorts (SUBSORT)", sy, n);
	n = sort_neighbours((Node *) s, 0, nb, 32);
	for (i = 0; i < n; i++) sy[i] = (Symbol *) nb[i];
	print_names("narrower sorts", sy, n);
	nfound = 0;
	target = s;
	for_all_symbols(find_of_sort);
	for (k = 0; k < 4; k++)		/* by kind; kinds[3] = 0: the functions */
		{
		for (n = 0, i = 0; i < nfound; i++)
			if (kinds[k] ? lexval(found[i]) == kinds[k] : is_function(found[i])) sy[n++] = found[i];
		print_names(what[k], sy, n);
		}
}

static void show_help (const char * nm)
{
	HelpEntry * e = find_help(nm);
	Symbol * s = find_symbol(nm);
	if (e) printfOut("%s\n", e->text);
	if (s && (is_function(s) || lexval(s) == Alg || lexval(s) == Sort))
		{
		if (e) printfOut("\n");
		if (lexval(s) == Alg) typeof_alg(s);
		else if (lexval(s) == Sort) typeof_sort(s);
		else print_variants(s);
		return;
		}
	if (e) return;
	if (s && (lexval(s) == Const || lexval(s) == Term || lexval(s) == Var))
		{
		Node t, * c = lexval(s) == Const ? mknod(Const, (Node *) s, NULL) : (Node *) s;
		t.r = c;
		typeof_fn(& t);
		if (c != (Node *) s) delete(c);
		return;
		}
	printfOut("no help on %s (? alone lists the names)\n", nm);
}

/* a line that begins with ?: the help, and TRUE */
int help_line (const char * line)
{
	char nm[256];
	int n = 0;
	while (* line == ' ' || * line == '\t') line++;
	if (* line != '?') return 0;
	line++;
	while (* line == ' ' || * line == '\t') line++;
	while (* line && ! isspace((unsigned char) * line) && n < 255) nm[n++] = * line++;
	nm[n] = 0;
	if (n) show_help(nm);
	else overview();
	return 1;
}
