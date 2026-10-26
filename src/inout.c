/*
 *	inout.c  V1.00
 *
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *
 *	Input/output functions
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "inout.h"
#include "fatal.h"

#ifdef NEXT
extern int display(const char * text);
#endif

#define MAXLINE 1024

char buf[MAXLINE];
char tmpline[MAXLINE];

FILE * fp= 0;    /* for output redirection */
FILE * datafp= 0; /* for reading data */

static int debug=0;

/* 2026: the output can be captured into a string (stack of buffers), e.g.
 * to measure the entries of a matrix before printing it as a grid */
#define MAXCAP 8
static char * cap_buf[MAXCAP];
static size_t cap_len[MAXCAP], cap_size[MAXCAP];
static int cap_depth = 0;

void out_capture_begin (void)
{
	if (cap_depth == MAXCAP) fatal("inout : output captured too deeply");
	cap_buf[cap_depth] = NULL;
	cap_len[cap_depth] = cap_size[cap_depth] = 0;
	cap_depth++;
}

char * out_capture_end (void)		/* the captured text (malloc), "" if none */
{
	char * s;
	if (cap_depth == 0) return NULL;
	cap_depth--;
	s = cap_buf[cap_depth];
	if (! s) { s = (char *) malloc(1); if (s) * s = 0; }
	return s;
}

/* 2026: the formatted text in buf, or in a larger buffer for a longer one
   (formerly vsprintf into buf: a text over 1024 bytes overwrote tmpline,
   fp and datafp behind it). The caller frees the result if it is not buf. */
static char * format_text (const char * format, va_list ap)
{
	va_list cp;
	char * big;
	int n;
	va_copy(cp, ap);
	n = vsnprintf(buf, sizeof buf, format, cp);
	va_end(cp);
	if (n < (int) sizeof buf) return buf;
	big = (char *) malloc(n + 1);
	if (! big) fatal("inout : no room");
	vsnprintf(big, n + 1, format, ap);
	return big;
}

int printfOut(const char * format,...)
{
	int rt;
	va_list mylist;
	va_start(mylist,format);
	if (cap_depth > 0)
		{
		int d = cap_depth - 1;
		va_list cp;
		va_copy(cp, mylist);
		rt = vsnprintf(NULL, 0, format, cp);
		va_end(cp);
		if (rt > 0)
			{
			if (cap_len[d] + rt + 1 > cap_size[d])
				{
				cap_size[d] = 2 * (cap_len[d] + rt + 1);
				cap_buf[d] = (char *) realloc(cap_buf[d], cap_size[d]);
				if (! cap_buf[d]) fatal("inout : no room");
				}
			vsnprintf(cap_buf[d] + cap_len[d], rt + 1, format, mylist);
			cap_len[d] += rt;
			}
		va_end(mylist);
		return rt;
		}
	if (!fp) fp=stdout;
	if (fp==stdout)
	{
		char * text = format_text(format, mylist);
#ifndef NEXT
		rt=printf("%s",text);
#else
		rt=display(text);
#endif
		if (text != buf) free(text);
	}
	else
	{
		rt=vfprintf(fp,format,mylist);
	}
	va_end(mylist);
	fflush(fp);
	return rt;
}
	

int printfErr(const char * format,...)
{
	int rt;
	va_list mylist;
	va_start(mylist,format);
	{
	char * text = format_text(format, mylist);
#ifndef NEXT
	rt=fprintf(stderr,"%s",text);
#else
	rt=display(text);
#endif
	if (text != buf) free(text);
	}
	va_end(mylist);
	return rt;
}

int changeOut(const char * filename)
{
	FILE * try;

	if (!fp) fp=stdout;
	if (0 == strcmp(filename,"stdout"))
	{
		if ((fp != stdout) && (fp != stderr))
			fclose(fp);
		fp = stdout;
		return 1;
	}

	if (!(try = fopen (filename,"w"))) 
		{
		printfErr(" -- Unable to open output to %s\n",filename);
		return 0;
		}

	if ((fp != stdout) && (fp != stderr))
		fclose(fp);
	fp=try;
	return 1;
}

double readData (void)
{
	double x;
	if (! datafp) datafp=stdin;
	while (fscanf(datafp,"%lf",&x) <= 0)
		{
		fgets(tmpline,MAXLINE-1,datafp);
		printfErr("%s",tmpline);
		if (feof(datafp))
			{
			printfErr("%s","ERROR in readData : reached EOF \n");
			x=0.0;
			break;
			}
		}
	return x;
}

int changeData(const char * filename)
{
	FILE * try;

	if (! datafp) datafp=stdin;
	if (0 == strcmp(filename,"stdin"))
	{
		if (datafp != stdin)
			fclose(datafp);
		datafp = stdin;
		return 1;
	}

 if (!(try = fopen (filename,"r"))) 
		{
		printfErr(" -- Unable to open datafile %s\n",filename);
		return 0;
		}

 if (datafp != stdin)
		fclose(datafp);
 datafp=try;
 return 1;
}

int mustDebug(int pri)
{
	return (debug>pri);
}

void setDebug(int pri)
{
	debug=pri;
	return;
}

int printfDebug(int pri,const char * format,...)
{
	int rt=0;
	va_list mylist;
	if (debug<=pri) return rt;

	va_start(mylist,format);
	{
	char * text = format_text(format, mylist);
#ifndef NEXT
	rt=fprintf(stderr,"%s",text);
	fflush(stderr);
#else
	rt=display(text);
#endif
	if (text != buf) free(text);
	}
	va_end(mylist);
	return rt;
}
