#ifndef COMPLEX_H
#define COMPLEX_H
/*
 * complex.h V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type complex)
 *
 */

typedef struct {
  double Re;
  double Im;
  } complex;

#define Re(x) (((complex *) (x)) -> Re)
#define Im(x) (((complex *) (x)) -> Im)

complex * cpy_complex (complex * x);
void show_complex (complex * x);
int cmp_complex (complex * x,complex * y);
void del_complex (complex * x);

complex * real2cpx (double * arg[]);   /* 2026: SUBSORT real,complex */
complex * cpx2num (complex * arg[]);   /* 2026: SUBSORT complex,number */
complex * cpx (double * arg[]);
complex * c_plus (complex * arg[]);
complex * c_plus_r (complex * arg[]);
complex * r_plus_c (complex * arg[]);
complex * c_minus (complex * arg[]);
complex * c_minus_r (complex * arg[]);
complex * r_minus_c (complex * arg[]);
complex * c_mult (complex * arg[]);
complex * c_mult_r (complex * arg[]);
complex * r_mult_c (complex * arg[]);
complex * c_divide (complex * arg[]);
complex * c_divide_r (complex * arg[]);
complex * r_divide_c (complex * arg[]);
complex * c_power(complex * arg[]);
complex * c_power_r(complex * arg[]);
complex * r_power_c(complex * arg[]);
complex * c_ln (complex * arg[]);
complex * c_sqrt (complex * arg[]);
complex * c_sin (complex * arg[]);
complex * c_cos (complex * arg[]);
complex * c_tan (complex * arg[]);
complex * c_exp(complex * arg[]);
complex * c_ai(complex * arg[]);
complex * c_mi(complex * arg[]);
double  * c_real(complex * arg[]);
double  * c_imag(complex * arg[]);
double  * c_asqr(complex * arg[]);
double  * c_abs(complex * arg[]);
complex * c_factorial(complex * arg[]);
complex * c_asinus   (complex * arg[]);
complex * c_acosinus (complex * arg[]);
complex * c_atangens (complex * arg[]);

#endif
