#ifndef BOOL_H
#define BOOL_H

/*
 * bool.h V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type bool)
 *
 */

void show_bool (double * x);
int cmp_bool (double * x,double * y);

double * greater_than (double * arg[]);
double * greater_equal (double * arg[]);
double * lower_than (double * arg[]);
double * lower_equal (double * arg[]);
double * equal (double * arg[]);
double * not_equal (double * arg[]);
double * and (double * arg[]);
double * or  (double * arg[]);
double * not  (double * arg[]);
double * is_int (double * arg[]);

#endif
