/*
 * bool.c V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type bool)
 *
 */

#include <stdlib.h>
#include <math.h>
#include "inout.h"
#include "real.h"
#include "fatal.h"
#include "bool.h"

void show_bool (double * x)
{
	if (*x == 0.0) printfOut("false ");
	else printfOut("true ");
}

int cmp_bool (double * x,double * y)
{
#ifdef DEBUG
		{
		int tmp;
		tmp= ((* x) > (* y)) ? 1 : (((*x) == (*y)) ? 0 : -1);
		DEBG((6,"cmp_real(%g,%g): returned %d",*x,*y,tmp));
		}
#endif

	return (((*x) == 0.0 && (*y) == 0.0) || ((*x) != 0.0 && (*y) != 0.0) ? 0 : 1);

}

double * greater_than (double * arg[]) 	{return mkreal((double) ((* arg[0]) > (* arg[1])));}
double * greater_equal (double * arg[]) {return mkreal((double) ((* arg[0]) >= (* arg[1])));}
double * lower_than (double * arg[]) 		{return mkreal((double) ((* arg[0]) < (* arg[1])));}
double * lower_equal (double * arg[]) 	{return mkreal((double) ((* arg[0]) <= (* arg[1])));}
double * equal (double * arg[]) 				{return mkreal((double) ((* arg[0]) == (* arg[1])));}
double * not_equal (double * arg[]) 		{return mkreal((double) ((* arg[0]) != (* arg[1])));}
double * and (double * arg[]) 					{return mkreal((double) (((int) (* arg[0])) && ((int) (* arg[1]))));}
double * or (double * arg[]) 						{return mkreal((double) (((int) (* arg[0])) || ((int) (* arg[1]))));}
double * not (double * arg[]) 					{return mkreal((double) ! ((int) (* arg[0])));}
double * is_int (double * arg[]) 			  {return mkreal((double) (((double) (* arg[0])) == (int) (* arg[0])));}
