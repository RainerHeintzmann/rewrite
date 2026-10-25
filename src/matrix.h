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
	int Rows;
	int Cols;
	double * Matrix;
	} matrix;

#define Rows(mp)  ((mp)->Rows)
#define Cols(mp) ((mp)->Cols)
#define Matrix(mp)  ((mp)->Matrix)
#define Matsize(mp) (Rows(mp)*Cols(mp)*sizeof(double))
#define Elem(dp,Nrow,Ncol,maxNcol) (*(dp+(Nrow*maxNcol+Ncol)))
#define MatElem(mp,Nrow,Ncol) (((Nrow) >= Rows(mp) || (Nrow) < 0) ? (printfErr("Matrix element error : Matrix has not enought rows\n"),0.0) : \
                          ((Ncol) >= Cols(mp) || (Ncol) < 0) ? (printfErr("Matrix element error : Matrix has not enought columns\n"),0.0) : \
                                                  (*(Matrix(mp)+((Nrow)*Cols(mp)+(Ncol)))) )
                               

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
