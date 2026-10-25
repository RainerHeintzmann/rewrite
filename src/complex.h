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

complex * cpx (double * arg[]);
complex * c_plus (complex * arg[]);
complex * c_plus_r (complex * arg[]);
complex * r_plus_c (complex * arg[]);
complex * c_minus (complex * arg[]);
complex * c_minus_r (complex * arg[]);
complex * r_minus_c (complex * arg[]);
complex * c_mal (complex * arg[]);
complex * c_mal_r (complex * arg[]);
complex * r_mal_c (complex * arg[]);
complex * c_geteilt (complex * arg[]);
complex * c_geteilt_r (complex * arg[]);
complex * r_geteilt_c (complex * arg[]);
complex * c_hoch(complex * arg[]);
complex * c_hoch_r(complex * arg[]);
complex * r_hoch_c(complex * arg[]);
complex * c_logarithmus (complex * arg[]);
complex * c_wurzel (complex * arg[]);
complex * c_sinus (complex * arg[]);
complex * c_cosinus (complex * arg[]);
complex * c_tangens (complex * arg[]);
complex * c_ehoch(complex * arg[]);
complex * c_ai(complex * arg[]);
complex * c_mi(complex * arg[]);
double  * c_real(complex * arg[]);
double  * c_imag(complex * arg[]);
double  * c_asqr(complex * arg[]);
double  * c_abs(complex * arg[]);
complex * c_fak(complex * arg[]);
complex * c_asinus   (complex * arg[]);
complex * c_acosinus (complex * arg[]);
complex * c_atangens (complex * arg[]);

#endif
