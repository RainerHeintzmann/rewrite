#ifndef REAL_H
#define REAL_H

/*
 * real.h V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type real)
 *
 */

double myfak (double a);
double * cpy_real(double * x);
void show_real (double * x);
int cmp_real (double * x,double * y);
void del_real (double * x);
double * mkreal (double x);

double * plus (double * arg[]);
double * minus (double * arg[]);
double * mult (double * arg[]);
double * divide (double * arg[]);
double * power(double * arg[]);
double * r_ln (double * arg[]);
double * wurzel (double * arg[]);
double * r_sin (double * arg[]);
double * r_cos (double * arg[]);
double * r_tan (double * arg[]);
double * r_sinh (double * arg[]);
double * r_cosh (double * arg[]);
double * r_tanh (double * arg[]);
double * r_exp(double * arg[]);
double * ai(double * arg[]);
double * mi(double * arg[]);
double * factorial(double * arg[]);
double * r_abs   (double * arg[]);
double * r_sqr   (double * arg[]);
double * r_sqrt  (double * arg[]);
double * r_arcsin   (double * arg[]);
double * r_arccos (double * arg[]);
double * r_arctan (double * arg[]);
double * bessel  (double * arg[]);
double * signum   (double * arg[]);
double * integer  (double * arg[]);
double * plttest  (double * arg[]);

/* 2026 */
double * r_csc (double * arg[]);
double * r_sec (double * arg[]);
double * r_cot (double * arg[]);
double * r_arccot (double * arg[]);
double * r_coth (double * arg[]);
double * r_sech (double * arg[]);
double * r_csch (double * arg[]);
double * r_arcsinh (double * arg[]);
double * r_arccosh (double * arg[]);
double * r_arctanh (double * arg[]);
double * r_arccoth (double * arg[]);
double * r_polylog (double * arg[]);
double * r_productlog (double * arg[]);
double * r_arctan2 (double * arg[]);

#endif
