#ifndef FORMS_H
#define FORMS_H

/*
 *	forms.h V1.00
 *	Copyright (c) Rainer Heintzmann 1992
 *
 *	Function prototypes for inserting and 'matching' in the formula tree
 */

Node * merge(Node * ,Node * ,Node * );  /* formula,'=' replacement,tree */

Node * match (Node * ,Node * );         /* formula,tree */
BOOLEAN testrewrite (Node * ,Node * );  /* Old linear version needs no RESTORE ! */
#endif
