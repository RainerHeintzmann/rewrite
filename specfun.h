#ifndef SPECFUN_H
#define SPECFUN_H

/*
 *	specfun.h (2026)
 *
 *	Special functions (Mathematica conventions), see specfun.c.
 *	sf_*: plain C functions; r_*: C functions of rewrite (argument arrays).
 */

double sf_arcsec (double x);
double sf_arccsc (double x);
double sf_arcsech (double x);
double sf_arccsch (double x);
double sf_erfi (double x);
double sf_fresnels (double x);
double sf_fresnelc (double x);
double sf_si (double x);
double sf_ci (double x);
double sf_shi (double x);
double sf_chi (double x);
double sf_ei (double x);
double sf_li (double x);
double sf_expinte (double n, double x);
double sf_gamma (double a);
double sf_gamma2 (double a, double x);
double sf_loggamma (double x);
double sf_polygamma (double n, double x);
double sf_hurwitz (double s, double a);
double sf_zeta (double s);
double sf_zeta2 (double s, double a);
double sf_elliptick (double m);
double sf_ellipticf (double phi, double m);
double sf_elliptice1 (double m);
double sf_elliptice2 (double phi, double m);
double sf_ellipticpi2 (double n, double m);
double sf_ellipticpi3 (double n, double phi, double m);
double sf_hyp2f1 (double a, double b, double c, double z);
double sf_appellf1 (double a, double b1, double b2, double c, double x, double y);
double sf_besselj (double nu, double x);

#define SPECFUN_LIST \
	X(r_arcsec) X(r_arccsc) X(r_arcsech) X(r_arccsch) X(r_erf) X(r_erfc) X(r_erfi) \
	X(r_fresnels) X(r_fresnelc) X(r_si) X(r_ci) X(r_shi) X(r_chi) X(r_ei) X(r_li) \
	X(r_expinte) X(r_gamma) X(r_gamma2) X(r_loggamma) X(r_polygamma) X(r_zeta) X(r_zeta2) \
	X(r_elliptick) X(r_ellipticf) X(r_elliptice1) X(r_elliptice2) X(r_ellipticpi2) \
	X(r_ellipticpi3) X(r_hyp2f1) X(r_appellf1) X(r_besselj)

#define X(n) double * n (double * arg[]);
SPECFUN_LIST
#undef X

#endif
