/*
 * real.c V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type real)
 *
 */

#include <stdlib.h>
#include <math.h>
#include "inout.h"
#include "fatal.h"
#include "real.h"

#define MAXPOWER 30
#define MAXREAL 9.0E+259;

double mypow (double a,double b)
{
if (b>=0) return pow(a,b);
else return (1.0/pow(a,fabs(b)));

printfErr("Tried to compute a non-integer negative power (Domain Error) !\n");
return 0.0;
}

double myfactorial (double a)
{
double result=1;
int i = (int) a;
if (i != a)
	printfErr("Tried to compute a non-integer factorial (Domain Error) !\n");

if (i>148) return MAXREAL
	else 
	while (i>0) result=result*(i--); 
return result;
}

double * mkreal (double x)
{
double * dp;
	dp = malloc(sizeof(double));
	if (NULL==(void *) dp)
		fatal("userfn : (mkreal) ERROR no Space for making double !\n");
	(* dp) = x;
	return dp;
}
	
double * cpy_real(double * x)
{
return mkreal(* x);
}

void std_show_real (double * x);	/* node.c: with the PRTNUM format */

void show_real (double * x)		/* 2026: also with the PRTNUM format */
{
	std_show_real(x);
}

int cmp_real (double * x,double * y)
{
#ifdef DEBUG
		{
		int tmp;
		tmp= ((* x) > (* y)) ? 1 : (((*x) == (*y)) ? 0 : -1);
		DEBG((6,"cmp_real(%g,%g): returned %d",*x,*y,tmp));
		}
#endif

	return ((* x) > (* y)) ? 1 : (((*x) == (*y)) ? 0 : -1);

}

void del_real (double * x)
{
free(x);
return;
}


double * plus (double * arg[]) 			{return mkreal((* arg[0]) + (* arg[1]));}
double * minus (double * arg[])			{return mkreal((* arg[0]) - (* arg[1]));}
double * mult (double * arg[])			{return mkreal((* arg[0]) * (* arg[1]));}
double * divide (double * arg[])		{return mkreal((* arg[0]) / (* arg[1]));}
double * power(double * arg[])			{return mkreal(mypow((* arg[0]),(* arg[1])));}
double * r_ln (double * arg[])	{return mkreal(log((* arg[0])));}
double * sqrt_plain (double * arg[])		{return mkreal(sqrt((* arg[0])));}
double * r_sin (double * arg[])			{return mkreal(sin((* arg[0])));}
double * r_cos (double * arg[])		{return mkreal(cos((* arg[0])));}
double * r_tan (double * arg[])		{return mkreal(tan((* arg[0])));}
double * r_sinh (double * arg[])      {return mkreal(sinh((* arg[0])));}
double * r_cosh (double * arg[])      {return mkreal(cosh((* arg[0])));}
double * r_tanh (double * arg[])      {return mkreal(tanh((* arg[0])));}
double * r_exp(double * arg[])			{return mkreal(exp((* arg[0])));}
double * ai(double * arg[])			{return mkreal(-(* arg[0]));}
double * mi(double * arg[])			{return mkreal(((double) 1)/(* arg[0]));}
double * factorial(double * arg[])			{return mkreal(myfactorial(* arg[0]));}
double * r_arcsin   (double * arg[])		{return mkreal(asin((* arg[0])));}
double * r_arccos (double * arg[])		{return mkreal(acos((* arg[0])));}
double * r_arctan (double * arg[])		{return mkreal(atan((* arg[0])));}
double * r_abs      (double * arg[])		{return mkreal(fabs((* arg[0])));}
double * r_sqr      (double * arg[])		{return mkreal((* arg[0])*(* arg[0]));}
double * r_sqrt     (double * arg[])		{return mkreal(sqrt((* arg[0])));}

double * signum   (double * arg[])		{return mkreal((double) ((* arg[0]) > (double) 0 ? 1 : ((* arg[0]) == (double) 0 ? 0 : -1)));}
double * integer  (double * arg[])		{return mkreal((double) (int) (* arg[0]));}

double * plttest  (double * arg[])		{printfOut("x:%g y:%g \n",* arg[0],* arg[1]);
																			return mkreal(0.0);}
double * bessel   (double * arg[])		
	{
	int v,n;
	double dn,x,result=0.0,summand,x_2;
	dn=(* arg[0]);
	n=(int) dn;

	if (n != dn) 
		{printfErr("Error cant compute Besselfkt with not integer index !\n");
		return mkreal(0);
		}
	x=(* arg[1]);

	x_2 = (x/2.0)*(x/2.0);

	v=0;
	if (v < -n) v= -n;  /* -> v > 0 */
	summand = mypow(-1.0,(double) v)/(myfactorial((double)v)*myfactorial((double)(n+v)));
	if (n != 0) summand *= mypow(x/2.0,(double)( n+2*v));
	result=summand;

	for (v++;v<MAXPOWER;v++)
		{
/* printf(" summ: %d, %g %g\n",v,summand,result);  */
		summand *= (-1.0)*x_2/((double)(v*(n+v+1)));
		result += summand;
		}
	return mkreal(result);
	}


/* ---- 2026: more elementary functions (for the Rubi rules) ---- */
double * r_csc     (double * arg[])	{return mkreal(1.0/sin(* arg[0]));}
double * r_sec     (double * arg[])	{return mkreal(1.0/cos(* arg[0]));}
double * r_cot     (double * arg[])	{return mkreal(1.0/tan(* arg[0]));}
double * r_arccot  (double * arg[])	{return mkreal(atan(1.0/(* arg[0])));}
double * r_coth    (double * arg[])	{return mkreal(1.0/tanh(* arg[0]));}
double * r_sech    (double * arg[])	{return mkreal(1.0/cosh(* arg[0]));}
double * r_csch    (double * arg[])	{return mkreal(1.0/sinh(* arg[0]));}
double * r_arcsinh (double * arg[])	{return mkreal(asinh(* arg[0]));}
double * r_arccosh (double * arg[])	{return mkreal(acosh(* arg[0]));}
double * r_arctanh (double * arg[])	{return mkreal(atanh(* arg[0]));}
double * r_arccoth (double * arg[])	{return mkreal(atanh(1.0/(* arg[0])));}

/* polylog(n,x) = sum x^k/k^n for integer n and |x| <= 1 (series) */
double * r_polylog (double * arg[])
{
	double n = * arg[0], x = * arg[1], sum = 0.0, term, xk = 1.0;
	int k;
	if (fabs(x) > 1.0 || n != floor(n))
		return mkreal(NAN);
	if (n <= 0 && fabs(x) < 1.0)
		{	/* closed forms: Li_0 = x/(1-x), Li_-1 = x/(1-x)^2 */
		if (n == 0)  return mkreal(x/(1.0-x));
		if (n == -1) return mkreal(x/((1.0-x)*(1.0-x)));
		}
	for (k = 1; k < 1000000; k++)
		{
		xk *= x;
		term = xk/pow((double) k, n);
		sum += term;
		if (fabs(term) < 1e-17*fabs(sum)) break;
		}
	return mkreal(sum);
}

/* productlog(x) = Lambert W function (principal branch), w*exp(w) = x */
double * r_productlog (double * arg[])
{
	double x = * arg[0], w;
	int i;
	if (x < -exp(-1.0)) return mkreal(NAN);
	w = (x < 1.0) ? 0.0 : log(x);
	for (i = 0; i < 100; i++)
		{
		double ew = exp(w), f = w*ew - x, wn = w - f/(ew*(w+1.0));
		if (fabs(wn - w) < 1e-15*(1.0+fabs(wn))) { w = wn; break; }
		w = wn;
		}
	return mkreal(w);
}

/* ArcTan[x,y] in Mathematica: angle of (x,y) */
double * r_arctan2 (double * arg[])	{return mkreal(atan2(* arg[1], * arg[0]));}
