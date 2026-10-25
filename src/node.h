#ifndef NODE_H
#define NODE_H

/*
 *	node.h V1.00
 *	Copyright (c) Rainer Heintzmann 1992
 *
 *	Include for node.c (memory management for nodes)
 */

void std_show_real(double * x);

double * std_cpy_real(double * x);

int std_cmp_real(double * x,double * y);

void std_show_cont(double * x);

int std_cmp_cont(double * x,double * y);

void std_del_real(double * x);


Node * mknod (int type, Node * l, Node * r);

void delnod (Node * node);

Symbol * mksym (int lexv,const char * name);

Symbol * mknum (void * value,Node * rtype);

void delsym (Symbol * sp);

void delnum (Symbol * number,int delvalue); /* Flag delvalue */

BOOLEAN symeq (Symbol * a,Symbol * b); /* Compares two symbols for equality */

Symbol * clonesym(Symbol * s);

BOOLEAN is_shared_num (Symbol * sp); /* 0 and 1: static value, do not free */

void cpysym(Symbol * s1,Symbol * s2);

#endif
