/* help.h (2026): HELP "name" "text" and ?name (help.c) */
#ifndef HELP_H
#define HELP_H
void help_def (Node * np);		/* HELP "name" "text": a line of help */
int  help_line (const char * line);	/* ?name: prints the help, TRUE */
#endif
