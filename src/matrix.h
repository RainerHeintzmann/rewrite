#ifndef MATRIX_H
#define MATRIX_H

/*
 * matrix.h V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite' (result type matrix)
 *
 */

#include "vector.h"

typedef struct {
	int Zeilen;
	int Spalten;
	double * Matrix;
	} matrix;

#define Zeilen(mp)  ((mp)->Zeilen)
#define Spalten(mp) ((mp)->Spalten)
#define Matrix(mp)  ((mp)->Matrix)
#define Matsize(mp) (Zeilen(mp)*Spalten(mp)*sizeof(double))
#define Elem(dp,Ze,Sp,maxSp) (*(dp+(Ze*maxSp+Sp)))
#define MatElem(mp,Ze,Sp) (((Ze) >= Zeilen(mp) || (Ze) < 0) ? (printfErr("Matrix element error : Matrix has not enought rows\n"),0.0) : \
                          ((Sp) >= Spalten(mp) || (Sp) < 0) ? (printfErr("Matrix element error : Matrix has not enought columns\n"),0.0) : \
                                                  (*(Matrix(mp)+((Ze)*Spalten(mp)+(Sp)))) )
                               

void     show_mat (matrix * mp);
int      cmp_mat (matrix * x,matrix * y);
matrix * cpy_mat (matrix * mp) ;
void     del_mat (matrix * mp);

double * elem_mat (void * arg[]);
matrix * zero_mat (double * arg[]);
matrix * one_mat (double * arg[]);
matrix * ch_mat (void * arg[]);
matrix * mat_add (void * arg[]);
matrix * mat_mul_real (void * arg[]);
matrix * real_mul_mat (void * arg[]);
matrix * mat_mul (void * arg[]);
matrix * mat_trans (matrix * arg[]);
vector * mat_mul_vec (void * arg[]);

#endif
