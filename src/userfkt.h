#ifndef	USERFKT_H
#define	USERFKT_H

/*
 *	userfkt.h  V1.00
 * 
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *
 *	Schnittstelle fuer benutzerdefinierte numerische Funktionen
 */

typedef void * u_function (void * []);

extern u_function * give_ufkt (char * name);
extern u_function * give_ufkt_quiet (char * name);  /* 2026: ohne Fehlermeldung */

#define MAXARGS 32  /* Maximalzahl an Funktionsargumenten (bei Aenderung run.c neu uebersetzen !!) */

/* extern Node * calkulate(Node *); /* Prototyp fuer Fkt. aus run.c */

#endif
