/*
 * matrix.c V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type matrix)
 *
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "inout.h"
#include "fatal.h"
#include "vector.h"
#include "real.h"
#include "matrix.h"

void show_mat (matrix * mp)
{
int i,j;
double * dp; /* otherwise Lattice does not get it */

/* printfOut("mat( "); */
/* printfOut("size %d %d ",Ze,Sp); */

dp=Matrix(mp);

printfOut("\n");
for(i=0;i<Zeilen(mp);i++)
	{
	for(j=0;j<Spalten(mp);j++)
		{
		printfOut(" %g",* (dp++));
		if (j < Spalten(mp)-1) printfOut(",");
		}
	printfOut("\n");
	}
/* printfOut(") "); */
}

int cmp_mat (matrix * x,matrix * y)
{
	return ( Zeilen(x) > Zeilen(y));
}

matrix * mkmat (int Zeilen,int Spalten) 
{
matrix * mp;
	if (!(mp = malloc(sizeof(matrix))))
		fatal("userfkt : (mkmatrix) ERROR no Space for making matrix !\n");
	mp->Zeilen = Zeilen;
	mp->Spalten= Spalten;
  if (!(mp->Matrix = malloc(Matsize(mp))))
		fatal("userfkt : (mkmatrix) ERROR no Space for making matrix !\n");
/*  printfOut("mkmat : size %d %d ",Zeilen,Spalten); */
	return mp;
}

void del_mat (matrix * mp) 
{
/*	printfOut("del_mat\n"); */
	free(Matrix(mp)); 
	free(mp); 
}

matrix * cpy_mat (matrix * mp) 
{
matrix * rp;
rp = mkmat(Zeilen(mp),Spalten(mp));

memcpy(Matrix(rp),Matrix(mp),Matsize(rp));
return rp;
}
	
matrix * null_mat (double * arg[]) 
{
matrix * mp;
double * dp;
int i,j;

	mp=mkmat((int) * arg[0],(int) * arg[1]);

	dp=Matrix(mp); /* next structure ! */

	for(i=0;i<Zeilen(mp);i++)
		for(j=0;j<Spalten(mp);j++)
			(* (dp++)) = (double) 0.0; /* set to zero */
	return mp;
}

matrix * eins_mat (double * arg[]) /* identity matrix with the minimum diagonal */
{
matrix * rt = null_mat(arg);
double * dp = Matrix(rt);
int i,min,dia=Spalten(rt)+1;
min= (Zeilen(rt) < Spalten(rt)) ? Zeilen(rt) : Spalten(rt);
for (i=0;i<min;i++)
	{
	*(dp) = 1.0;
	dp += dia;
	}
return rt;
}


matrix * ch_mat (void * arg[]) /* Matrix,PosZ,PosS,Value */
{
int	Zeilen=Zeilen((matrix *) arg[0]); 
int	Spalten=Spalten((matrix *) arg[0]); 
int   PosZ=(int) * (double *)(arg[1]);
int   PosS=(int) * (double *)(arg[2]);
matrix * mp = ((matrix *) (arg[0])),
       * rp;
double * dp = Matrix(mp);

if (PosZ < 0 || PosZ >= Zeilen || PosS < 0 || PosS >= Spalten)
	{
	printfErr("ERROR : chmat Matrix is not as big !!\n");
	return NULL;
	}
rp=cpy_mat(mp);
dp=Matrix(rp);

dp += (Spalten*PosZ+PosS);
(* dp) = * (double *)(arg[3]);
return rp;
}

double * elem_mat (void * arg[])
{
	return mkreal(MatElem((matrix *) arg[0],(int) * (double *) arg[1],(int) * (double *) arg[2]));
}

void addMat(double * m1,double * m2,double * m3,int Ze,int Sp)
{
int i;
for (i=0;i<Ze*Sp;i++)
	*(m3++) = *(m1++) + *(m2++);
}

void mulMat(double * m1,double * m2,double * m3,int Ze,int Sp,int Sp2)
{
int i,j,k;
double * l1=m1, * l2=m2,sum;

	for (i=0;i<Ze;i++)
	{
	for (k=0;k<Sp2;k++) /* columns of the 2nd matrix */
		{
		l1 = m1;
		l2 = m2+k;
		sum=0.0;
		for (j=0;j<Sp;j++)
			{
			/* printfOut("l1 : %g l2 : %g ",* l1,* l2); */
			sum += *(l1++) * *(l2);
			l2 += Sp2; /* == columns(m2) */
			}
		* (m3++) = sum;
		}
	m1 += Sp;
	}
}

matrix * mat_add (void * arg[])
{
matrix * m1= (matrix *) arg[0];
matrix * m2= (matrix *) arg[1];
matrix * rt;

if (Zeilen(m1) != Zeilen(m2) || Spalten(m1) != Spalten(m2))
	{
	printfErr("ERROR : matadd Matrix are not of same type !!\n");
	return NULL;
	}

rt = mkmat(Zeilen(m1),Spalten(m1));

addMat(Matrix(m1),Matrix(m2),Matrix(rt),Zeilen(m1),Spalten(m1));
return rt;
}

void MatRealMul (double value,double * matrix,int size)
{
int i;
for (i=0;i<size;i++)
	* (matrix++) *= value;
}

matrix * real_mul_mat (void * arg[])
{
matrix * rt = cpy_mat((matrix *) arg[1]);

MatRealMul (* (double *) arg[0],Matrix(rt),Zeilen(rt)*Spalten(rt));

return rt;
}

matrix * mat_mul_real (void * arg[])
{
matrix * rt = cpy_mat((matrix *) arg[0]);

MatRealMul (* (double *) arg[1],Matrix(rt),Zeilen(rt)*Spalten(rt));

return rt;
}


matrix * mat_mul (void * arg[])
{
matrix * m1= (matrix *) arg[0];
matrix * m2= (matrix *) arg[1];
matrix * rt;

if (Spalten(m1) != Zeilen(m2))
	{
	printfErr("ERROR : matmul Matrix are not of same type !!\n");
	return NULL;
	}

rt = mkmat(Zeilen(m1),Zeilen(m1));

mulMat(Matrix(m1),Matrix(m2),Matrix(rt),Zeilen(m1),Spalten(m1),Spalten(m2));
return rt;
}

void transMat(double * old,double * new,int Ze,int Sp)
{
int i,j;
double * lnew=new;
for (i=0;i<Ze;i++)
	{
	lnew = new ++;
	for (j=0;j<Sp;j++)
		{
		* lnew = * (old ++);
		lnew += Sp;
		}
	}
}

matrix * mat_trans (matrix * arg[]) /* matrix */
{
matrix * rt = mkmat(Spalten(arg[0]),Zeilen(arg[0]));

transMat(Matrix(arg[0]),Matrix(rt),Zeilen(arg[0]),Spalten(arg[0]));
return rt;
}

vector * mat_mul_vec (void * arg[]) /* matrix,vector */
{
matrix * mp= (matrix *) arg[0];
vector * vp= (vector *) arg[1],* rt;

if (Spalten(mp) != Dimension(vp))
	{
	printfErr("ERROR : matmulvec matrix & vector are not of same dimension !!\n");
	return NULL;
	}
rt = mkvec(Zeilen(mp));

mulMat(Matrix(mp),Vector(vp),Vector(rt),Zeilen(mp),Spalten(mp),1);
return rt;
}
