/*
 *	fatal.c -- 1.3 Jun 21 07:09:35 1987
 *	Copyright (c) 1987 Axel T. Schreiner
 *
 *	fatal() -- error termination
 *
 *	AMIGA Version -- Jul 16 13:46:49 1990
 *	Hartmut Ufer 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "unix.h"

void fatal(char* fmt, ...)
{	va_list ap;

	fflush(stdout);
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	putc('\n', stderr);
	va_end(ap);
	exit(1);
}
