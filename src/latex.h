/* latex.h (2026): LaTeX-like names of Unicode characters (\\alpha -> α) */
#ifndef LATEX_H
#define LATEX_H
const char * latex_symbol (const char * s, int * len);	/* after the backslash */
char * latex_convert (const char * line);		/* NULL: no name in it */
#endif
