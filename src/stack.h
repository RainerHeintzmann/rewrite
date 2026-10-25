/* stack.h (c) Rainer Heintzmann Juni 1991 */

typedef struct Stackelem STACKELEM;

struct Stackelem {
		STACKELEM * next;
		void * elem;
		};

typedef STACKELEM * STACK;

void push (STACK *,void *);
void * pop (STACK *);

