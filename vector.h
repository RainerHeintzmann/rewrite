#ifndef VECTOR_H
#define VECTOR_H

/*
 * vector.h V1.00
 * Copyright (c) : Rainer Heintzmann
 * 
 * Benutzerfunktionen fuer 'rewrite' (Resultattyp rvector)
 *
 */

typedef struct {
	int Dimension;
	double * Vector;
	} vector;

#define Dimension(vp)  ((vp)->Dimension)
#define Vector(vp)  ((vp)->Vector)
#define Vecsize(vp) (Dimension(vp)*sizeof(double))
#define VecElem(vp,Pos) (((Pos) >= Dimension(vp) || (Pos) < 0) ? (printfErr("Vector element error : Vector has lower dimension\n"),0.0) : \
                                                  (Vector(vp)[Pos]))
#define pVecElem(vp,Pos) ((void *) &(Vector(vp)[Pos]))
                               
vector * mkvec (int Dimension);

void     show_vec (vector * mp);
int      cmp_vec (vector * x,vector * y);
vector * cpy_vec (vector * mp) ;
void     del_vec (vector * mp);

double * elem_vec (void * arg[]);
vector * vec_part (void * arg[]);
vector * null_vec (double * arg[]);
vector * eins_vec (double * arg[]);
vector * ch_vec (void * arg[]);
vector * constr_vec (double * arg[]); /* Va - args */
vector * vec_add (void * arg[]);
vector * vec_min_vec (void * arg[]);
vector * vec_mul_real (void * arg[]);
vector * vec_div_real (void * arg[]);
vector * minus_vec (void * arg[]);
vector * real_mul_vec (void * arg[]);
vector * vec_x_vec (void * arg[]);
double * vec_mul (void * arg[]);    /* Scalarprodukt */
double * vec_sqr (void * arg[]);    /* Quadrat       */
double * vec_abs (void * arg[]);    /* Betrag        */
double * vec_middle (void * arg[]); /* Mittelwert    */
double * vec_ms (void * arg[]);     /* Varianz       */
double * vec_rms (void * arg[]);    /* Standartabweichung */
double * vec_write (void * arg[]);  /* Display vectors */

vector * sin_vec (void * arg[]);    /* Elementweise */
vector * sinh_vec (void * arg[]);    /* Elementweise */
vector * asin_vec (void * arg[]);    /* Elementweise */
vector * cos_vec (void * arg[]);    /* Elementweise */
vector * cosh_vec (void * arg[]);    /* Elementweise */
vector * acos_vec (void * arg[]);    /* Elementweise */
vector * tan_vec (void * arg[]);    /* Elementweise */
vector * tanh_vec (void * arg[]);    /* Elementweise */
vector * atan_vec (void * arg[]);    /* Elementweise */
vector * log_vec (void * arg[]);    /* Elementweise */
vector * exp_vec (void * arg[]);    /* Elementweise */
vector * fak_vec (void * arg[]);    /* Elementweise */
vector * sqr_vec (void * arg[]);    /* Elementweise */
vector * sqrt_vec (void * arg[]);    /* Elementweise */
vector * abs_vec (void * arg[]);    /* Elementweise */
vector * gen_vec (void * arg[]);    /* Elementweise */
vector * eplus1_vec (void * arg[]);    /* vec+real */
vector * eplus2_vec (void * arg[]);    /* real+vec */
vector * emin1_vec (void * arg[]);    /* vec-real */
vector * emin2_vec (void * arg[]);    /* real-vec */
vector * emul_vec (void * arg[]);    /* Elementweise */
vector * epow_vec (void * arg[]);    /* Elementweise */
vector * ediv_vec (void * arg[]);    /* Elementweise */

#endif
