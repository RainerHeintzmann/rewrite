/*
 * real.c V1.00
 * Copyright (c) : Rainer Heintzmann
 * 
 * Benutzerfunktionen fuer 'rewrite' (Resultattyp real)
 *
 */

#include <stdlib.h>
#include <math.h>
#include "inout.h"
#include "fatal.h"
#include "real.h"

#define MAXPOTENZ 30
#define MAXREAL 9.0E+259;

double mypow (double a,double b)
{
if (b>=0) return pow(a,b);
else return (1.0/pow(a,fabs(b)));

printfErr("Tried to compute a non-integer negative power (Domain Error) !\n");
return 0.0;
}

double myfak (double a)
{
double result=1;
int i = (int) a;
if (i != a)
	printfErr("Tried to compute a non-integer fak (Domain Error) !\n");

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
		fatal("userfkt : (mkreal) ERROR no Space for making double !\n");
	(* dp) = x;
	return dp;
}
	
double * cpy_real(double * x)
{
return mkreal(* x);
}

void show_real (double * x)
{
	printfOut("%g ",* x);
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
double * mal (double * arg[])			{return mkreal((* arg[0]) * (* arg[1]));}
double * geteilt (double * arg[])		{return mkreal((* arg[0]) / (* arg[1]));}
double * hoch(double * arg[])			{return mkreal(mypow((* arg[0]),(* arg[1])));}
double * logarithmus (double * arg[])	{return mkreal(log((* arg[0])));}
double * wurzel (double * arg[])		{return mkreal(sqrt((* arg[0])));}
double * sinus (double * arg[])			{return mkreal(sin((* arg[0])));}
double * cosinus (double * arg[])		{return mkreal(cos((* arg[0])));}
double * tangens (double * arg[])		{return mkreal(tan((* arg[0])));}
double * sinush (double * arg[])      {return mkreal(sinh((* arg[0])));}
double * cosinush (double * arg[])      {return mkreal(cosh((* arg[0])));}
double * tangensh (double * arg[])      {return mkreal(tanh((* arg[0])));}
double * ehoch(double * arg[])			{return mkreal(exp((* arg[0])));}
double * ai(double * arg[])			{return mkreal(-(* arg[0]));}
double * mi(double * arg[])			{return mkreal(((double) 1)/(* arg[0]));}
double * fak(double * arg[])			{return mkreal(myfak(* arg[0]));}
double * asinus   (double * arg[])		{return mkreal(asin((* arg[0])));}
double * acosinus (double * arg[])		{return mkreal(acos((* arg[0])));}
double * atangens (double * arg[])		{return mkreal(atan((* arg[0])));}
double * r_abs      (double * arg[])		{return mkreal(abs((* arg[0])));}
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
	summand = mypow(-1.0,(double) v)/(myfak((double)v)*myfak((double)(n+v)));
	if (n != 0) summand *= mypow(x/2.0,(double)( n+2*v));
	result=summand;

	for (v++;v<MAXPOTENZ;v++)
		{
/* printf(" summ: %d, %g %g\n",v,summand,result);  */
		summand *= (-1.0)*x_2/((double)(v*(n+v+1)));
		result += summand;
		}
	return mkreal(result);
	}

