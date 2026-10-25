#ifndef	USERFN_H
#define	USERFN_H

/*
 *	userfn.h  V1.00
 *
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *
 *	Interface for user-defined numeric functions
 */

typedef void * u_function (void * []);

extern u_function * give_ufn (char * name);
extern u_function * give_ufn_quiet (char * name);  /* 2026: without an error message */

#define MAXARGS 32  /* maximum number of function arguments (recompile run.c after changing it !!) */

/* extern Node * calculate(Node *); /* prototype for the function from run.c */

#endif
