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
/* printfOut("size %d %d ",Nrow,Ncol); */

dp=Matrix(mp);

printfOut("\n");
for(i=0;i<Rows(mp);i++)
	{
	for(j=0;j<Cols(mp);j++)
		{
		printfOut(" %g",* (dp++));
		if (j < Cols(mp)-1) printfOut(",");
		}
	printfOut("\n");
	}
/* printfOut(") "); */
}

int cmp_mat (matrix * x,matrix * y)
{
	return ( Rows(x) > Rows(y));
}

matrix * mkmat (int Rows,int Cols) 
{
matrix * mp;
	if (!(mp = malloc(sizeof(matrix))))
		fatal("userfn : (mkmatrix) ERROR no Space for making matrix !\n");
	mp->Rows = Rows;
	mp->Cols= Cols;
  if (!(mp->Matrix = malloc(Matsize(mp))))
		fatal("userfn : (mkmatrix) ERROR no Space for making matrix !\n");
/*  printfOut("mkmat : size %d %d ",Rows,Cols); */
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
rp = mkmat(Rows(mp),Cols(mp));

memcpy(Matrix(rp),Matrix(mp),Matsize(rp));
return rp;
}
	
matrix * zero_mat (double * arg[]) 
{
matrix * mp;
double * dp;
int i,j;

	mp=mkmat((int) * arg[0],(int) * arg[1]);

	dp=Matrix(mp); /* next structure ! */

	for(i=0;i<Rows(mp);i++)
		for(j=0;j<Cols(mp);j++)
			(* (dp++)) = (double) 0.0; /* set to zero */
	return mp;
}

matrix * one_mat (double * arg[]) /* identity matrix with the minimum diagonal */
{
matrix * rt = zero_mat(arg);
double * dp = Matrix(rt);
int i,min,dia=Cols(rt)+1;
min= (Rows(rt) < Cols(rt)) ? Rows(rt) : Cols(rt);
for (i=0;i<min;i++)
	{
	*(dp) = 1.0;
	dp += dia;
	}
return rt;
}


matrix * ch_mat (void * arg[]) /* Matrix,PosRow,PosCol,Value */
{
int	Rows=Rows((matrix *) arg[0]); 
int	Cols=Cols((matrix *) arg[0]); 
int   PosRow=(int) * (double *)(arg[1]);
int   PosCol=(int) * (double *)(arg[2]);
matrix * mp = ((matrix *) (arg[0])),
       * rp;
double * dp = Matrix(mp);

if (PosRow < 0 || PosRow >= Rows || PosCol < 0 || PosCol >= Cols)
	{
	printfErr("ERROR : chmat Matrix is not as big !!\n");
	return NULL;
	}
rp=cpy_mat(mp);
dp=Matrix(rp);

dp += (Cols*PosRow+PosCol);
(* dp) = * (double *)(arg[3]);
return rp;
}

double * elem_mat (void * arg[])
{
	return mkreal(MatElem((matrix *) arg[0],(int) * (double *) arg[1],(int) * (double *) arg[2]));
}

void addMat(double * m1,double * m2,double * m3,int Nrow,int Ncol)
{
int i;
for (i=0;i<Nrow*Ncol;i++)
	*(m3++) = *(m1++) + *(m2++);
}

void mulMat(double * m1,double * m2,double * m3,int Nrow,int Ncol,int Ncol2)
{
int i,j,k;
double * l1=m1, * l2=m2,sum;

	for (i=0;i<Nrow;i++)
	{
	for (k=0;k<Ncol2;k++) /* columns of the 2nd matrix */
		{
		l1 = m1;
		l2 = m2+k;
		sum=0.0;
		for (j=0;j<Ncol;j++)
			{
			/* printfOut("l1 : %g l2 : %g ",* l1,* l2); */
			sum += *(l1++) * *(l2);
			l2 += Ncol2; /* == columns(m2) */
			}
		* (m3++) = sum;
		}
	m1 += Ncol;
	}
}

matrix * mat_add (void * arg[])
{
matrix * m1= (matrix *) arg[0];
matrix * m2= (matrix *) arg[1];
matrix * rt;

if (Rows(m1) != Rows(m2) || Cols(m1) != Cols(m2))
	{
	printfErr("ERROR : matadd Matrix are not of same type !!\n");
	return NULL;
	}

rt = mkmat(Rows(m1),Cols(m1));

addMat(Matrix(m1),Matrix(m2),Matrix(rt),Rows(m1),Cols(m1));
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

MatRealMul (* (double *) arg[0],Matrix(rt),Rows(rt)*Cols(rt));

return rt;
}

matrix * mat_mul_real (void * arg[])
{
matrix * rt = cpy_mat((matrix *) arg[0]);

MatRealMul (* (double *) arg[1],Matrix(rt),Rows(rt)*Cols(rt));

return rt;
}


matrix * mat_mul (void * arg[])
{
matrix * m1= (matrix *) arg[0];
matrix * m2= (matrix *) arg[1];
matrix * rt;

if (Cols(m1) != Rows(m2))
	{
	printfErr("ERROR : matmul Matrix are not of same type !!\n");
	return NULL;
	}

rt = mkmat(Rows(m1),Rows(m1));

mulMat(Matrix(m1),Matrix(m2),Matrix(rt),Rows(m1),Cols(m1),Cols(m2));
return rt;
}

void transMat(double * old,double * new,int Nrow,int Ncol)
{
int i,j;
double * lnew=new;
for (i=0;i<Nrow;i++)
	{
	lnew = new ++;
	for (j=0;j<Ncol;j++)
		{
		* lnew = * (old ++);
		lnew += Ncol;
		}
	}
}

matrix * mat_trans (matrix * arg[]) /* matrix */
{
matrix * rt = mkmat(Cols(arg[0]),Rows(arg[0]));

transMat(Matrix(arg[0]),Matrix(rt),Rows(arg[0]),Cols(arg[0]));
return rt;
}

vector * mat_mul_vec (void * arg[]) /* matrix,vector */
{
matrix * mp= (matrix *) arg[0];
vector * vp= (vector *) arg[1],* rt;

if (Cols(mp) != Dimension(vp))
	{
	printfErr("ERROR : matmulvec matrix & vector are not of same dimension !!\n");
	return NULL;
	}
rt = mkvec(Rows(mp));

mulMat(Matrix(mp),Vector(vp),Vector(rt),Rows(mp),Cols(mp),1);
return rt;
}
