/*
 *	strsave.c -- 1.1 Apr 19 06:31:46 1991
 *	Copyright (c) 1991 Axel T. Schreiner
 *
 *	strsave -- String dynamisch speichern
 */

#include <string.h>

#include "fatal.h"
#include "strsave.h"

char * strsave _1a ((s), const char * s)
{	char * p;
	void * malloc _1p (unsigned);

	if (! (p = (char *) malloc(strlen(s) + 1)))
		fatal("strsave: no room");
	return strcpy(p, s);
}
