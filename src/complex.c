/*
 * complex.c V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type complex)
 *
 */

#include <stdlib.h>
#include <math.h>
#include "inout.h"
#include "fatal.h"
#include "real.h"
#include "complex.h"

#define Db(x) (*((double *) (x)))

complex * mkcomplex (double x, double y)
{
complex * cp;
	cp = malloc(sizeof(complex));
	if (NULL==(void *) cp)
		fatal("complex : (mkcomplex) ERROR no Space for making complex !\n");
	Re(cp) = x;
	Im(cp) = y;
	return cp;
}
	
complex * cpy_complex (complex * x)
{
	DEBG((6,"cpy_complex(%g,%g)\n",Re(x),Im(x)));
	return mkcomplex(Re(x),Im(x));
}

void show_complex (complex * x)
{
	printfOut("(%g,%g) ",Re(x),Im(x));
}

int cmp_complex (complex * x,complex * y)
{
#ifdef DEBUG
		int tmp;
	  tmp= ((Re(x)*Re(x)+Im(x)*Im(x)) > (Re(y)*Re(y)+Im(y)*Im(y))) ? 1 : ((Re(x) == Re(y) && Im(x) == Im(y)) ? 0 : -1);
		DEBG((6,"cmp_complex((%g,%g),(%g,%g)): returned %d",Re(x),Im(x),Re(y),Im(y),tmp));
#endif

	return ((Re(x)*Re(x)+Im(x)*Im(x)) > (Re(y)*Re(y)+Im(y)*Im(y))) ? 1 : ((Re(x) == Re(y) && Im(x) == Im(y)) ? 0 : -1);
}

void del_complex (complex * x)
{
free(x);
return;
}

/* 2026: SUBSORT real,complex: a real number as a complex one */
complex * real2cpx (double * arg[])		{return mkcomplex((* arg[0]),0.0);}
complex * cpx2num (complex * arg[])		{return mkcomplex(Re(arg[0]),Im(arg[0]));}	/* SUBSORT complex,number */
complex * cpx (double * arg[]) 					{return mkcomplex((* arg[0]),(* arg[1]));}
complex * c_plus (complex * arg[]) 			{return mkcomplex(Re(arg[0]) + Re(arg[1]),Im(arg[0]) + Im(arg[1]));}
complex * c_plus_r (complex * arg[]) 		{return mkcomplex(Re(arg[0]) + Db(arg[1]),Im(arg[0]));}
complex * r_plus_c (complex * arg[]) 		{return mkcomplex(Db(arg[0]) + Re(arg[1]),Im(arg[1]));}

complex * c_minus (complex * arg[]) 		{return mkcomplex(Re(arg[0]) - Re(arg[1]),Im(arg[0]) - Im(arg[1]));}
complex * c_minus_r (complex * arg[]) 	{return mkcomplex(Re(arg[0]) - Db(arg[1]),Im(arg[0]));}
complex * r_minus_c (complex * arg[]) 	{return mkcomplex(Db(arg[0]) - Re(arg[1]),- Im(arg[1]));}

complex * c_mult (complex * arg[])				{return mkcomplex(Re(arg[0]) * Re(arg[1]) - Im(arg[0])*Im(arg[1]),Re(arg[0])*Im(arg[1])+Im(arg[0])*Re(arg[1]));}
complex * c_mult_r (complex * arg[])			{return mkcomplex(Re(arg[0]) * Db(arg[1]),Im(arg[0])*Db(arg[1]));}
complex * r_mult_c (complex * arg[])			{return mkcomplex(Db(arg[0]) * Re(arg[1]) ,Db(arg[0])*Im(arg[1]));}

complex * c_divide (complex * arg[])		{double tmp=Re(arg[1])*Re(arg[1])+Im(arg[1])*Im(arg[1]);
  return mkcomplex((Re(arg[0])*Re(arg[1])+Im(arg[0])*Im(arg[1]))/tmp,(Im(arg[0])*Re(arg[1])-Re(arg[0])*Im(arg[1]))/tmp);}
complex * c_divide_r (complex * arg[])	{return mkcomplex(Re(arg[0])/Db(arg[1]),Im(arg[0])/Db(arg[1]));}
complex * r_divide_c (complex * arg[])	{double tmp=Re(arg[1])*Re(arg[1])+Im(arg[1])*Im(arg[1]);
  return mkcomplex((Re(arg[0])*Re(arg[1]))/tmp,(- Re(arg[0])*Im(arg[1]))/tmp);}

complex * c_ai(complex * arg[])					{return mkcomplex(- Re(arg[0]),- Im(arg[0]));}
complex * c_mi(complex * arg[])					{double tmp=Re(arg[0])*Re(arg[0])+Im(arg[0])*Im(arg[0]);
  return mkcomplex(Re(arg[0])/tmp,- Im(arg[0])/tmp);}

complex * c_exp(complex * arg[])				{double tmp=exp(Re(arg[0]));
	return mkcomplex(tmp*cos(Im(arg[0])),tmp*sin(Im(arg[0])));}

complex * c_power(complex * arg[])				{complex x=* arg[0],y=* arg[1],z,w,* pw;
	z.Re=.5*log(x.Re*x.Re+x.Im*x.Im);
	z.Im=atan(x.Im/x.Re);        /* z = ln x */
	w.Re=z.Re * y.Re - z.Im*y.Im; 
	w.Im=z.Re*y.Im+z.Im*y.Re;            /* w= z*y */
	pw= &w;
	return c_exp(& pw);}

complex * c_power_r(complex * arg[])				{complex w,* pw[2];
w.Re=*((double *)arg[1]);
w.Im=0.0;
pw[0]=arg[0];
pw[1]=&w;
return c_power(pw);
}

complex * r_power_c(complex * arg[])				{complex w,* pw[2];
w.Re=*((double *)arg[0]);
w.Im=0.0;
pw[0]=&w;
pw[1]=arg[1];
return c_power(pw);
}

complex * c_ln (complex * arg[])	{return mkcomplex(.5*log(Re(arg[0])*Re(arg[0])+Im(arg[0])*Im(arg[0])),atan(Im(arg[0])/Re(arg[0])));}
complex * c_sin (complex * arg[])				{return mkcomplex(sin(Re(arg[0]))*cosh(Im(arg[0])),cos(Re(arg[0]))*sinh(Im(arg[0])));}
complex * c_cos (complex * arg[])			{return mkcomplex(cos(Re(arg[0]))*cosh(Im(arg[0])),- sin(Re(arg[0]))*sinh(Im(arg[0])));}
complex * c_tan (complex * arg[])			{double tmpx=2.0*Re(arg[0]),tmpy=2.0*Im(arg[0]),tmpz;
	tmpz=(cos(tmpx)+cosh(tmpy));
	return mkcomplex(sin(tmpx)/tmpz,sinh(tmpy)/tmpz);}

double * c_real (complex * arg[])	{return mkreal(Re(arg[0]));}
double * c_imag (complex * arg[])	{return mkreal(Im(arg[0]));}
double * c_asqr (complex * arg[])	{return mkreal(Re(arg[0])*Re(arg[0])+Im(arg[0])*Im(arg[0]));}
double * c_abs (complex * arg[])	{return mkreal(sqrt(Re(arg[0])*Re(arg[0])+Im(arg[0])*Im(arg[0])));}

/* complex * c_power(complex * arg[])				{return mkcomplex(pow((* arg[0]),(* arg[1])));}
complex * c_sqrt (complex * arg[])			{return mkcomplex(sqrt((* arg[0])));}

complex * c_asinus   (complex * arg[])		{return mkcomplex(asin((* arg[0])));}
complex * c_acosinus (complex * arg[])		{return mkcomplex(acos((* arg[0])));}
complex * c_atangens (complex * arg[])		{return mkcomplex(atan((* arg[0])));}

complex * c_signum   (complex * arg[])		{return mkcomplex((complex) ((* arg[0]) > (complex) 0 ? 1 : ((* arg[0]) == (complex) 0 ? 0 : -1)));}
*/
