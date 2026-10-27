/* help.h (2026): HELP "name" "text" and ?name (help.c) */
#ifndef HELP_H
#define HELP_H
void help_def (Node * np);		/* HELP "name" "text": a line of help */
int  help_line (const char * line);	/* ?name: prints the help, TRUE */
int  alglist_has (Node * l, Symbol * alg);	/* the list of rule sets l contains alg */
void typeof_alg (Symbol * a);		/* TYPEOF alg: kind, rules, where it is used */
void typeof_sort (Symbol * s);		/* TYPEOF sort: values, subsorts, names of the sort */
#endif
