#ifndef	_MAIN_H
#define	_MAIN_H

/*
 *	main.h -- 2.2 Apr 22 21:56:26 1991
 *	Copyright (c) 1986-1991 Axel T. Schreiner
 *
 *	main.h -- argument standards
 *	unix, cp/m-86 and ms-dos
 *	ANSI-ized
 */

#include "ansi.h"

#define	MAIN	int main _2a ((argc, argv),				\
			int argc,					\
			char ** argv)

#define	OPT	while (--argc > 0 && **++argv == '-')			\
		{	switch (*++*argv) {				\
			case 0:		--*argv;			\
					break;				\
			case '-':	if (! (*argv)[1])		\
					{	++argv, --argc;		\
						break;			\
					}				\
			default:	do				\
					{	switch (**argv) {	\
						case 0:

#define	ARG						continue;	\
						case

#define	OTHER						continue;	\
						}

#define	ENDOPT				} while (*++*argv);		\
					continue;			\
			}						\
			break;						\
		}

#define	IFANY	if (argc > 1) while (-- argc > 0)			\
		{	static char _any;				\
			if (**++argv == '-'				\
			    && ! _any) switch (*++*argv) {		\
			case 0:		--*argv;			\
					break;				\
			case '-':	if (! (*argv)[1])		\
					{	_any = 1;		\
						continue;		\
					}				\
			default:	do {				\
						switch (**argv)

#define	ANY				} while (*++*argv);		\
					continue;			\
				}

#define	PARM	if (*++*argv)						\
			;						\
		else if (--argc > 0)					\
			++argv;						\
		else							\
		{	--*argv, ++argc;				\
			break;						\
		}

#define	NEXTOPT	*argv += strlen(*argv) - 1;
#endif
