#ifndef FORMS_H
#define FORMS_H

/*
 *	forms.h V1.00
 *	Copyright (c) Rainer Heintzmann 1992
 *
 *	Funktionsprototypen fuer einfuegen, und 'matchen' im Formelbaum
 */

Node * merge(Node * ,Node * ,Node * );  /* Formel,'=' Ersetz,Baum */

Node * match (Node * ,Node * );         /* Formel,Baum */
BOOLEAN testrewrite (Node * ,Node * );  /* Alte lineare Version braucht kein RESTORE ! */
#endif
