/*
 * vector.c V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type vector)
 *
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "inout.h"
#include "fatal.h"
#include "vector.h"
#include "real.h"
#include "sym.h"

/* 2026: printed like the lists of inc/list. A value that is the whole
   printed term (print_root, run.c) is a column (vector) or a grid (matrix),
   otherwise inline. */
extern Node * print_root;

int value_is_root (void * value)
{
	Node * r = print_root;
	return r && r->type == SYM_TYPE && hasval((Symbol *) r) && value((Symbol *) r) == value;
}

void show_vec (vector * vp)
{
int i;
double * dp; /* otherwise Lattice does not get it */

/* printfOut("vec( "); */

dp=Vector(vp);

if (value_is_root(vp) && Dimension(vp) > 1 && Dimension(vp) <= 10)	/* [1,\n 2,\n 3] */
	{
	for(i=0;i<Dimension(vp);i++)
		printfOut("%s%g%s", i ? " " : "[", dp[i], i < Dimension(vp)-1 ? ",\n" : "] ");
	return;
	}
printfOut("[");
for(i=0;i<Dimension(vp);i++)
	{
		printfOut("%g",* (dp++));
		if (i<Dimension(vp)-1) printfOut(", ");
	}
printfOut("] ");
}

int cmp_vec (vector * x,vector * y)
{
	return ( Dimension(x) > Dimension(y));
}

vector * mkvec (int Dimension)
{
vector * vp;
double * dp;
	if (!(vp = malloc(sizeof(vector))))
		fatal("userfn : (mkvector) ERROR no Space for making vector !\n");
	vp->Dimension = Dimension;
  if (!(dp = malloc(Vecsize(vp))))
		fatal("userfn : (mkvector) ERROR no Space for making vector !\n");
	Vector(vp) = dp;
	/* printfOut("mkvec : size %d ptr : %p, %p\n",Dimension,vp,Vector(vp)); */
	return vp;
}

void del_vec (vector * vp) 
{
	/* printfOut("del_vec : size %d ptr : %p, %p ",vp->Dimension,vp,Vector(vp));*/
	free(Vector(vp));
	free(vp);
	/* printfOut(".. freed\n"); */
}

vector * cpy_vec (vector * vp) 
{
vector * rp;
rp = mkvec(Dimension(vp));

memcpy(Vector(rp),Vector(vp),Vecsize(rp));
return rp;
}

void cpvecto (vector * from,int begin,vector * to)
{
void * fro;
fro = pVecElem(from,begin);

memcpy(Vector(to),fro,Vecsize(to));
return;
}

	
vector * zero_vec (double * arg[]) 
{
vector * vp;
double * dp;
int i;

	vp=mkvec((int) *arg[0]);

	dp=Vector(vp);

	for(i=0;i<Dimension(vp);i++)
			(* dp++) = (double) 0; /* set to zero */
	return vp;
}

vector * one_vec (double * arg[]) /* unit vector with a one at arg[1] */
{
vector * rt = zero_vec(arg);
int pos = (int) * arg[1]; 

if (pos >= Dimension(rt) || pos < 0) printfErr("Vector element error : Vector has lower dimension\n");
else Vector(rt)[pos] = 1.0;

return rt;
}


vector * ch_vec (void * arg[]) /* vector,Pos,Value */
{
int	Dimension=Dimension((vector *) arg[0]); 
int   Pos=(int) * (double *)(arg[1]);
vector * vp = ((vector *) (arg[0])),
       * rp;
double * dp = Vector(vp);

if (Pos < 0 || Pos > Dimension)
	{
	printfErr("ERROR : chvec vector is not as big !!\n");
	return NULL;
	}
rp=cpy_vec(vp);
dp=Vector(rp);

dp += Pos;
(* dp) = * (double *)(arg[2]);
return rp;
}

vector * constr_vec (double * arg[]) /* variable number of args ! */
{
int args;
double * dp;
vector * rt;

for (args=0;arg[args];args++)
	;

rt = mkvec(args);

dp = Vector(rt);
for (;* arg;)
    * (dp++) = * * (arg ++);

return rt;
}

double * elem_vec (void * arg[]) /* vector,pos */
{
	return mkreal(VecElem((vector *) arg[0],(int) * (double *) arg[1]));
}

vector * vec_part (void * arg[]) /* vector,begin,end */
{
vector * v= (vector *) arg[0];
vector * rt;
double begin= * (double *) arg[1],
				end = * (double *) arg[2];


	if (end>=Dimension(v) || begin < 0.0)
		{
		printfErr("ERROR : vec_part Begin or End is not in vector !!\n");
		return NULL;
		}

	if (end<begin)
		{
		printfErr("ERROR : vec_part begin is bigger than end !!\n");
		return NULL;
		}

	rt=mkvec((int) ((end+1)-begin));
	cpvecto(v,begin,rt);
	return rt;

}

void addvec(double * v1,double * v2,double * m3,int Di)
{
int i;
for (i=0;i<Di;i++)
	*(m3++) = *(v1++) + *(v2++);
}

void vecminvec(double * v1,double * v2,double * m3,int Di)
{
int i;
for (i=0;i<Di;i++)
	*(m3++) = *(v1++) - *(v2++);
}

void mulvec(double * v1,double * v2,double * r3,int Di)
{
int i;
double sum=0.0;

	for (i=0;i<Di;i++)
		{
		sum += *(v1++) * *(v2++);
		}
	* r3 = sum;
}

vector * vec_add (void * arg[])
{
vector * v1= (vector *) arg[0];
vector * v2= (vector *) arg[1];
vector * rt;

if (Dimension(v1) != Dimension(v2))
	{
	printfErr("ERROR : vecadd vector are not of same type !!\n");
	return NULL;
	}

rt = mkvec(Dimension(v1));

addvec(Vector(v1),Vector(v2),Vector(rt),Dimension(v1));
return rt;
}

vector * vec_min_vec (void * arg[])
{
vector * v1= (vector *) arg[0];
vector * v2= (vector *) arg[1];
vector * rt;

if (Dimension(v1) != Dimension(v2))
	{
	printfErr("ERROR : vec_min_vec vector are not of same type !!\n");
	return NULL;
	}

rt = mkvec(Dimension(v1));

vecminvec(Vector(v1),Vector(v2),Vector(rt),Dimension(v1));
return rt;
}

void vecRealMul (double value,double * vector,int size)
{
int i;
for (i=0;i<size;i++)
	* (vector++) *= value;
}

vector * real_mul_vec (void * arg[])
{
vector * rt = cpy_vec((vector *) arg[1]);

vecRealMul (* (double *) arg[0],Vector(rt),Dimension(rt));

return rt;
}

vector * vec_mul_real (void * arg[])
{
vector * rt = cpy_vec((vector *) arg[0]);

vecRealMul (* (double *) arg[1],Vector(rt),Dimension(rt));

return rt;
}

vector * vec_div_real (void * arg[])
{
vector * rt = cpy_vec((vector *) arg[0]);

vecRealMul (1.0/(* (double *) arg[1]),Vector(rt),Dimension(rt));

return rt;
}

vector * minus_vec (void * arg[])
{
vector * rt = cpy_vec((vector *) arg[0]);

vecRealMul (-1.0,Vector(rt),Dimension(rt));

return rt;
}

double * vec_mul (void * arg[])
{
vector * v1= (vector *) arg[0];
vector * v2= (vector *) arg[1];
double * rt;

if (Dimension(v1) != Dimension(v2))
	{
	printfErr("ERROR : vecmul vectors are not of same type !!\n");
	return NULL;
	}

rt = mkreal(0.0);

mulvec(Vector(v1),Vector(v2),rt,Dimension(v1));
return rt;
}

double * vec_sqr (void * arg[])
{
vector * v1= (vector *) arg[0];
double * rt;

rt = mkreal(0.0);

mulvec(Vector(v1),Vector(v1),rt,Dimension(v1));
return rt;
}

double * vec_abs (void * arg[])
{
vector * v1= (vector *) arg[0];
double * rt;

rt = mkreal(0.0);

mulvec(Vector(v1),Vector(v1),rt,Dimension(v1));
(* rt) = sqrt(* rt);

return rt;
}

void xvec(double * v1,double * v2,double * m3,int Di)
{
m3[0] = v1[1]*v2[2]-v1[2]*v2[1];
m3[1] = v1[2]*v2[0]-v1[0]*v2[2];
m3[2] = v1[0]*v2[1]-v1[1]*v2[0];
}

vector * vec_x_vec (void * arg[]) /* cross product */
{
vector * v1= (vector *) arg[0];
vector * v2= (vector *) arg[1];
vector * rt;

if ((Dimension(v1) != 3) || (Dimension(v2) != 3))
	{
	printfErr("ERROR : vec_x_vec vectors are not of dimension 3 !!\n");
	return NULL;
	}

rt = mkvec(Dimension(v1));

xvec(Vector(v1),Vector(v2),Vector(rt),Dimension(v1));
return rt;
}

double * vec_middle (void * arg[]) /* mean of a vector */
{
vector * vp= (vector *) arg[0];
double * dp= Vector(vp),sum=0.0;
int i;

for (i=0;i<Dimension(vp);i++) sum += * (dp++);

return mkreal(sum/Dimension(vp));
}

double * vec_ms (void * arg[]) /* mean square */
{
vector * vp= (vector *) arg[0];
double * dp= Vector(vp),sum=0.0,sqsum=0.0;
int i;

for (i=0;i<Dimension(vp);i++) {sum += * dp;sqsum += (* dp)*(* dp);dp++;}

return mkreal((sum*sum-sqsum)/Dimension(vp));
}

double * vec_rms (void * arg[]) /* root mean square */
{
vector * vp= (vector *) arg[0];
double * dp= Vector(vp),sum=0.0,sqsum=0.0;
int i;

for (i=0;i<Dimension(vp);i++) {sum += * dp;sqsum += (* dp)*(* dp);dp++;}

return mkreal(sqrt((sum*sum-sqsum)/Dimension(vp))/sqrt(Dimension(vp)-1.0));
}

double * vec_write (void * arg[]) /* display vectors */
{
int vecnr=0;
int pos=0;
int maxpos= Dimension((vector *) arg[0]);

for(pos=0;pos < maxpos;pos++)
	{
	for (vecnr=0;arg[vecnr];vecnr++)
		{
			printfOut("%g\t",(Vector((vector *) arg[vecnr]))[pos]);
		}
	printfOut("\n");
	}
return mkreal((double) maxpos);
}

/**************** elementwise functions *************************/

vector * sin_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = sin(* (dp ++));

return rt;
}

vector * asin_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = asin(* (dp ++));

return rt;
}

vector * sinh_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = sinh(* (dp ++));

return rt;
}

vector * cos_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = cos(* (dp ++));

return rt;
}

vector * acos_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = acos(* (dp ++));

return rt;
}

vector * cosh_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = cosh(* (dp ++));

return rt;
}

vector * tan_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = tan(* (dp ++));

return rt;
}

vector * atan_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = atan(* (dp ++));

return rt;
}

vector * tanh_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = tanh(* (dp ++));

return rt;
}

vector * log_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = log(* (dp ++));

return rt;
}

vector * exp_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = exp(* (dp ++));

return rt;
}

vector * factorial_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = myfactorial(* (dp ++));

return rt;
}

vector * abs_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = fabs(* (dp ++));

return rt;
}

vector * sqr_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++,dp++)
	* (drt ++) = (* (dp ))*(* (dp));

return rt;
}

vector * sqrt_vec (void * arg[])
{
int	i;
vector * vp= (vector *) arg[0];
double * dp= Vector(vp);
vector * rt = mkvec(Dimension(vp));
double * drt= Vector(rt);

for(i=0;i<Dimension(vp);i++)
	* (drt ++) = sqrt(* (dp ++));

return rt;
}

vector * gen_vec (void * arg[])  /* arg : double : from,to,Steps */
{
int	i;
double * dp1 = (double *) arg[0];
double * dp2 = (double *) arg[1];
double * dp3 = (double *) arg[2];
int Steps=(int) (* dp3);

vector * rt = mkvec(Steps);
double * drt= Vector(rt);

for(i=0;i<Steps;i++)
	* (drt ++) = (((double) i)*(* dp2)+((Steps-1.0)-i)*(* dp1))/(Steps-1.0);

return rt;
}

vector * eplus1_vec (void * arg[]) /* vector + real */
{
int	i;
vector * vp1= (vector *) arg[0];
double * dp1= Vector(vp1);
double * dp2= (double *) arg[1];
vector * rt;
double * drt;

rt = mkvec(Dimension(vp1));
drt= Vector(rt);

for(i=0;i<Dimension(vp1);i++)
	* (drt ++) = (* (dp1 ++))+(* dp2);

return rt;
}

vector * eplus2_vec (void * arg[]) /* real+vector */
{
int	i;
vector * vp1= (vector *) arg[1];
double * dp1= Vector(vp1);
double * dp2= (double *) arg[0];
vector * rt;
double * drt;

rt = mkvec(Dimension(vp1));
drt= Vector(rt);

for(i=0;i<Dimension(vp1);i++)
	* (drt ++) = (* (dp1 ++))+(* dp2);

return rt;
}

vector * emin1_vec (void * arg[]) /* vector - real */
{
int	i;
vector * vp1= (vector *) arg[0];
double * dp1= Vector(vp1);
double * dp2= (double *) arg[1];
vector * rt;
double * drt;

rt = mkvec(Dimension(vp1));
drt= Vector(rt);

for(i=0;i<Dimension(vp1);i++)
	* (drt ++) = (* (dp1 ++))-(* dp2);

return rt;
}

vector * epow_vec (void * arg[]) /* vector ^ real */
{
int	i;
vector * vp1= (vector *) arg[0];
double * dp1= Vector(vp1);
double * dp2= (double *) arg[1];
vector * rt;
double * drt;

rt = mkvec(Dimension(vp1));
drt= Vector(rt);

for(i=0;i<Dimension(vp1);i++)
	* (drt ++) = pow((* (dp1 ++)),(* dp2));

return rt;
}

vector * emin2_vec (void * arg[]) /* real-vector */
{
int	i;
vector * vp1= (vector *) arg[1];
double * dp1= Vector(vp1);
double * dp2= (double *) arg[0];
vector * rt;
double * drt;

rt = mkvec(Dimension(vp1));
drt= Vector(rt);

for(i=0;i<Dimension(vp1);i++)
	* (drt ++) = (* dp2)-(* (dp1 ++));

return rt;
}

vector * emul_vec (void * arg[])
{
int	i,min;
vector * vp1= (vector *) arg[0];
double * dp1= Vector(vp1);
vector * vp2= (vector *) arg[1];
double * dp2= Vector(vp2);
vector * rt;
double * drt;

min=Dimension(vp1);
if (min>Dimension(vp2)) min=Dimension(vp2);

rt = mkvec(min);
drt= Vector(rt);

for(i=0;i<min;i++)
	* (drt ++) = (* (dp1 ++))*(* (dp2 ++));

return rt;
}

vector * ediv_vec (void * arg[])
{
int	i,min;
vector * vp1= (vector *) arg[0];
double * dp1= Vector(vp1);
vector * vp2= (vector *) arg[1];
double * dp2= Vector(vp2);
vector * rt;
double * drt;

min=Dimension(vp1);
if (min>Dimension(vp2)) min=Dimension(vp2);

rt = mkvec(min);
drt= Vector(rt);

for(i=0;i<min;i++)
	* (drt ++) = (* (dp1 ++))/(* (dp2 ++));

return rt;
}

