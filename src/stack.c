/* stack.c : (c) Rainer Heintzmann Juni 1992 */

#include <stdlib.h>
#include "fatal.h"
#include "stack.h"

void push (STACK * p_stack,void * elem)
{
STACK	top;
	if (((void *) 0) == (top = (STACK) calloc(1,sizeof(STACKELEM))))
		fatal("stack : No Room \n");
	(* top).next = (* p_stack);							/* Verketten */
	(* top).elem = elem;
	(* p_stack) = top;
	return;
}
	
void * pop (STACK * p_stack)
{
STACK top;
void * topelem;	/* Users element */
	topelem = (* * p_stack).elem;
	top = (* * p_stack).next;
	if (top != 0)
		{
		free(* p_stack);
			/* if .. fatal("stack : free failed ?? \n"); ?? */
		(* p_stack) = top;
		}
	return topelem;
}

void s_delete (STACK stack)
{
for (;stack != 0;pop(& stack))
	;
return;
}
