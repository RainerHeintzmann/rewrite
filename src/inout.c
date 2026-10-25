/*
 *	inout.c  V1.00
 * 
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *
 *	EinAusgabe Funktionen
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "inout.h"

#ifdef NEXT
extern int display(const char * text);
#endif

#define MAXLINE 1024

char buf[MAXLINE];
char tmpline[MAXLINE];

FILE * fp= 0;    /* Fuer Ausgabe-Umlenkung */
FILE * datafp= 0; /* Zum Einlesen von Daten */

static int debug=0;

int printfOut(const char * format,...)
{
	int rt;
	va_list mylist;
	va_start(mylist,format);
	if (!fp) fp=stdout;
	if (fp==stdout)
	{
		vsprintf(buf,format,mylist);
#ifndef NEXT
		rt=printf("%s",buf);
#else
		rt=display(buf);
#endif
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

	vsprintf(buf,format,mylist);
#ifndef NEXT
	rt=fprintf(stderr,"%s",buf);
#else
	rt=display(buf);
#endif
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

	vsprintf(buf,format,mylist);
#ifndef NEXT
	rt=fprintf(stderr,"%s",buf);
	fflush(stderr);
#else
	rt=display(buf);
#endif
	va_end(mylist);
	return rt;
}
