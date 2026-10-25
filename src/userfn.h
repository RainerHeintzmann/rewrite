#ifndef	USERFKT_H
#define	USERFKT_H

/*
 *	userfkt.h  V1.00
 *
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *
 *	Interface for user-defined numeric functions
 */

typedef void * u_function (void * []);

extern u_function * give_ufkt (char * name);
extern u_function * give_ufkt_quiet (char * name);  /* 2026: without an error message */

#define MAXARGS 32  /* maximum number of function arguments (recompile run.c after changing it !!) */

/* extern Node * calkulate(Node *); /* prototype for the function from run.c */

#endif
