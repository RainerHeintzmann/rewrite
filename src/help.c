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

static void show_help (const char * nm)
{
	HelpEntry * e = find_help(nm);
	Symbol * s = find_symbol(nm);
	if (e) printfOut("%s\n", e->text);
	if (s && is_function(s))
		{
		if (e) printfOut("\n");
		print_variants(s);
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
	if (s && lexval(s) == Sort)
		{
		printfOut("%s is a sort\n", nm);
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
