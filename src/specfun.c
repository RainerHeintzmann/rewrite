/*
 *	specfun.c (2026)
 *
 *	Special functions for real arguments, as C functions of rewrite (sort
 *	real). The definitions and parameter conventions are those of
 *	Mathematica (and Rubi), e.g. EllipticF[phi, m] with the parameter m, and
 *	FresnelS[x] = integral of sin(pi t^2/2). Outside the real domain the
 *	result is NaN.
 *
 *	Methods: series and asymptotic expansions, continued fractions (Lentz),
 *	Carlson's symmetric elliptic integrals (duplication), Euler-Maclaurin
 *	summation for the Hurwitz zeta function. The accuracy is about 1e-13
 *	relative in the main domains.
 */

#include <math.h>
#include <complex.h>
#include <float.h>
#include "real.h"
#include "specfun.h"

#define PI     3.14159265358979323846
#define EULER  0.57721566490153286061
#define TINY   1e-300
#define EPS    1e-16
#define MAXIT  100000

static double nan_val (void) { return NAN; }

/* ---------------- inverse trigonometric and hyperbolic functions ------- */

double sf_arcsec (double x)  { return acos(1.0 / x); }
double sf_arccsc (double x)  { return asin(1.0 / x); }
double sf_arcsech (double x) { return acosh(1.0 / x); }
double sf_arccsch (double x) { return asinh(1.0 / x); }

/* ---------------- error functions ---------------- */

double sf_erfi (double x)		/* -i erf(i x) */
{
	double ax = fabs(x), s, t, x2 = x * x;
	int n;
	if (ax < 6.0)		/* series: all terms positive */
		{
		t = x; s = x;
		for (n = 1; n < 500; n++)
			{
			t *= x2 / n;
			s += t / (2 * n + 1);
			if (fabs(t / (2 * n + 1)) < EPS * fabs(s)) break;
			}
		return 2.0 / sqrt(PI) * s;
		}
	/* asymptotic: e^(x^2)/(x sqrt(pi)) (1 + 1/(2x^2) + 3/(4x^4) + ...) */
	s = 1.0; t = 1.0;
	for (n = 1; n < 60; n++)
		{
		double nt = t * (2 * n - 1) / (2.0 * x2);
		if (nt > t) break;
		t = nt;
		s += t;
		if (t < EPS * s) break;
		}
	return exp(x2) / (x * sqrt(PI)) * s;
}

/* ---------------- Fresnel integrals (Numerical Recipes 'frenel') -------- */

static void fresnel (double x, double * s, double * c)
{
	double ax = fabs(x), t = PI * ax * ax / 2.0;
	int k, n, odd;
	if (ax < 1.8)		/* series */
		{
		double sum, sums = 0, sumc = 0, fact = PI / 2.0, sign = 1.0, term;
		sum = 0;
		if (ax < sqrt(DBL_MIN)) { * s = 0; * c = x; return; }
		sumc = ax; sums = 0; sum = 0;
		odd = 1;
		term = ax;
		n = 3;
		fact = 1.0;
		/* term_k = (pi/2)^k x^(2k+1) / (k! (2k+1)) with alternating signs per pair */
		{
		double p = ax;		/* x^(2k+1) (pi/2)^k / k! */
		int kk;
		sumc = ax; sums = 0;
		for (kk = 1; kk < 200; kk++)
			{
			p *= (PI / 2.0) * ax * ax / kk;
			term = p / (2 * kk + 1);
			/* k = 1: sin, +; k = 2: cos, -; k = 3: sin, -; k = 4: cos, + ... */
			switch (kk % 4)
				{
				case 1: sums += term; break;
				case 2: sumc -= term; break;
				case 3: sums -= term; break;
				case 0: sumc += term; break;
				}
			if (term < EPS * (fabs(sums) + fabs(sumc))) break;
			}
		}
		(void) sum; (void) odd; (void) n; (void) sign; (void) fact; (void) k;
		* s = sums; * c = sumc;
		}
	else			/* continued fraction (complex Lentz) */
		{
		double complex b, cc, d, h, del, cs;
		double a, pix2 = PI * ax * ax;
		b = 1.0 + I * (-pix2);
		cc = 1.0 / TINY;
		d = h = 1.0 / b;
		n = -1;
		for (k = 2; k <= MAXIT; k++)
			{
			n += 2;
			a = -n * (n + 1);
			b += 4.0;
			d = 1.0 / (a * d + b);
			cc = b + a / cc;
			del = cc * d;
			h *= del;
			if (fabs(creal(del) - 1.0) + fabs(cimag(del)) < EPS) break;
			}
		h *= ax + I * (-ax);
		cs = (0.5 + 0.5 * I) * (1.0 - (cos(t) + I * sin(t)) * h);
		* c = creal(cs);
		* s = cimag(cs);
		}
	if (x < 0) { * c = -(* c); * s = -(* s); }
}

double sf_fresnels (double x) { double s, c; fresnel(x, & s, & c); return s; }
double sf_fresnelc (double x) { double s, c; fresnel(x, & s, & c); return c; }

/* ---------------- sine and cosine integrals (NR 'cisi') ---------------- */

static void cisi (double x, double * ci, double * si)
{
	double t = fabs(x);
	int k;
	if (t == 0) { * si = 0; * ci = -INFINITY; return; }
	if (t > 2.0)		/* continued fraction */
		{
		double complex b, c, d, h, del;
		double a;
		b = 1.0 + I * t;
		c = 1.0 / TINY;
		d = h = 1.0 / b;
		for (k = 2; k <= MAXIT; k++)
			{
			a = -(k - 1) * (k - 1);
			b += 2.0;
			d = 1.0 / (a * d + b);
			c = b + a / c;
			del = c * d;
			h *= del;
			if (fabs(creal(del) - 1.0) + fabs(cimag(del)) < EPS) break;
			}
		h = (cos(t) - I * sin(t)) * h;
		* ci = -creal(h);
		* si = PI / 2.0 + cimag(h);
		}
	else			/* series */
		{
		double sum = 0, sums = 0, sumc = 0, fact = 1, term, err, sign = 1;
		int odd = 1;
		for (k = 1; k <= MAXIT; k++)
			{
			fact *= t / k;
			term = fact / k;
			sum += sign * term;
			err = term / fabs(sum);
			if (odd) { sign = -sign; sums = sum; sum = sumc; }
			else { sumc = sum; sum = sums; }
			if (err < EPS) break;
			odd = ! odd;
			}
		* si = sums;
		* ci = sumc + log(t) + EULER;
		}
	if (x < 0) { * si = -(* si); * ci = NAN; }	/* Ci(x<0) is complex */
}

double sf_si (double x) { double c, s; cisi(x, & c, & s); return s; }
double sf_ci (double x) { double c, s; if (x <= 0) return nan_val(); cisi(x, & c, & s); return c; }

static void chishi (double x, double * chi, double * shi)
{
	double t = fabs(x), s1 = 0, s2 = 0, term = 1;
	int k;
	if (t == 0) { * shi = 0; * chi = -INFINITY; return; }
	if (t < 40.0)		/* series, all terms positive */
		{
		s1 = t; term = t;		/* shi: x^(2k+1)/((2k+1)(2k+1)!) */
		for (k = 1; k < 1000; k++)
			{
			term *= t / (2 * k);			/* t^(2k)/(2k)! */
			s2 += term / (2 * k);
			term *= t / (2 * k + 1);		/* t^(2k+1)/(2k+1)! */
			s1 += term / (2 * k + 1);
			if (term < EPS * s1) break;
			}
		* shi = s1;
		* chi = EULER + log(t) + s2;
		}
	else			/* asymptotic: e^t/(2t) sum k!/t^k */
		{
		double s = 1, tk = 1;
		for (k = 1; k < 40; k++)
			{
			double nt = tk * k / t;
			if (nt > tk) break;
			tk = nt;
			s += tk;
			if (tk < EPS * s) break;
			}
		* shi = * chi = exp(t) / (2 * t) * s;
		}
	if (x < 0) { * shi = -(* shi); * chi = NAN; }
}

double sf_shi (double x) { double c, s; chishi(x, & c, & s); return s; }
double sf_chi (double x) { double c, s; if (x <= 0) return nan_val(); chishi(x, & c, & s); return c; }

/* ---------------- exponential integrals ---------------- */

static double expint_n (int n, double x)	/* E_n(x), NR 'expint' */
{
	int i, ii, nm1 = n - 1;
	double a, b, c, d, del, fact, h, psi, ans;
	if (n < 0 || x < 0 || (x == 0 && (n == 0 || n == 1))) return nan_val();
	if (n == 0) return exp(-x) / x;
	if (x == 0) return 1.0 / nm1;
	if (x > 1.0)
		{
		b = x + n; c = 1.0 / TINY; d = 1.0 / b; h = d;
		for (i = 1; i <= MAXIT; i++)
			{
			a = -i * (nm1 + i);
			b += 2.0;
			d = 1.0 / (a * d + b);
			c = b + a / c;
			del = c * d;
			h *= del;
			if (fabs(del - 1.0) < EPS) break;
			}
		return h * exp(-x);
		}
	ans = (nm1 != 0 ? 1.0 / nm1 : -log(x) - EULER);
	fact = 1.0;
	for (i = 1; i <= MAXIT; i++)
		{
		fact *= -x / i;
		if (i != nm1) del = -fact / (i - nm1);
		else
			{
			psi = -EULER;
			for (ii = 1; ii <= nm1; ii++) psi += 1.0 / ii;
			del = fact * (-log(x) + psi);
			}
		ans += del;
		if (fabs(del) < fabs(ans) * EPS) break;
		}
	return ans;
}

double sf_ei (double x)
{
	double s, t;
	int k;
	if (x == 0) return -INFINITY;
	if (x < 0) return -expint_n(1, -x);
	if (x < 40.0)
		{
		s = 0; t = 1;
		for (k = 1; k < 1000; k++)
			{
			t *= x / k;
			s += t / k;
			if (t / k < EPS * s) break;
			}
		return EULER + log(x) + s;
		}
	s = 1; t = 1;
	for (k = 1; k < 40; k++)
		{
		double nt = t * k / x;
		if (nt > t) break;
		t = nt;
		s += t;
		if (t < EPS * s) break;
		}
	return exp(x) / x * s;
}

double sf_li (double x) { if (x < 0) return nan_val(); if (x == 0) return 0; return sf_ei(log(x)); }

/* ---------------- gamma functions ---------------- */

/* regularized incomplete gamma: lower P (series) and upper Q (cont. fraction) */
static double gser (double a, double x)
{
	double sum, del, ap = a;
	int n;
	del = sum = 1.0 / a;
	for (n = 1; n <= MAXIT; n++)
		{
		ap += 1;
		del *= x / ap;
		sum += del;
		if (fabs(del) < fabs(sum) * EPS) break;
		}
	return sum * exp(-x + a * log(x) - lgamma(a));
}

static double gcf (double a, double x)
{
	double an, b, c, d, del, h;
	int i;
	b = x + 1.0 - a; c = 1.0 / TINY; d = 1.0 / b; h = d;
	for (i = 1; i <= MAXIT; i++)
		{
		an = -i * (i - a);
		b += 2.0;
		d = an * d + b; if (fabs(d) < TINY) d = TINY;
		c = b + an / c; if (fabs(c) < TINY) c = TINY;
		d = 1.0 / d;
		del = d * c;
		h *= del;
		if (fabs(del - 1.0) < EPS) break;
		}
	return exp(-x + a * log(x) - lgamma(a)) * h;
}

static double upper_gamma (double a, double x)		/* Gamma(a, x), x > 0 */
{
	if (x < 0) return nan_val();
	if (a > 0)
		{
		if (x == 0) return tgamma(a);
		if (x < a + 1.0) return tgamma(a) * (1.0 - gser(a, x));
		return (a < 170 ? tgamma(a) : exp(lgamma(a))) * gcf(a, x);
		}
	if (x == 0) return nan_val();
	if (a == 0) return expint_n(1, x);
	/* a < 0: Gamma(a,x) = (Gamma(a+1,x) - x^a e^-x) / a */
	return (upper_gamma(a + 1.0, x) - pow(x, a) * exp(-x)) / a;
}

double sf_gamma (double a) { return tgamma(a); }
double sf_gamma2 (double a, double x) { return upper_gamma(a, x); }
double sf_loggamma (double x) { if (x <= 0) return nan_val(); return lgamma(x); }

double sf_expinte (double n, double x)	/* E_n(x) for real n */
{
	if (n == floor(n) && n >= 0) return expint_n((int) n, x);
	if (x <= 0) return nan_val();
	return pow(x, n - 1.0) * upper_gamma(1.0 - n, x);
}

/* ---------------- Hurwitz zeta and polygamma ---------------- */

static const double B2[] = {	/* Bernoulli numbers B_2, B_4, ..., B_24 */
	1.0/6, -1.0/30, 1.0/42, -1.0/30, 5.0/66, -691.0/2730, 7.0/6,
	-3617.0/510, 43867.0/798, -174611.0/330, 854513.0/138, -236364091.0/2730 };

double sf_hurwitz (double s, double a)		/* zeta(s, a), a > 0, s != 1 */
{
	int N = 20, k, j;
	double sum = 0, an, fac, term, sp;
	if (s == 1 || a <= 0) return nan_val();
	for (k = 0; k < N; k++) sum += pow(a + k, -s);
	an = a + N;
	sum += pow(an, 1.0 - s) / (s - 1.0) + 0.5 * pow(an, -s);
	fac = s / 2.0;				/* s (s+1) ... (s+2j-2) / (2j)! */
	sp = pow(an, -s - 1.0);
	for (j = 1; j <= 12; j++)
		{
		term = B2[j - 1] * fac * sp;
		sum += term;
		if (fabs(term) < EPS * fabs(sum)) break;
		fac *= (s + 2 * j - 1) * (s + 2 * j) / ((2.0 * j + 1) * (2.0 * j + 2));
		sp /= an * an;
		}
	return sum;
}

double sf_zeta (double s) { return sf_hurwitz(s, 1.0); }
double sf_zeta2 (double s, double a) { return sf_hurwitz(s, a); }

static double digamma (double x)
{
	double r = 0, f, x2;
	if (x <= 0 && x == floor(x)) return nan_val();
	if (x < 0) return digamma(1.0 - x) - PI / tan(PI * x);
	while (x < 10) { r -= 1.0 / x; x += 1; }
	f = 1.0 / (x * x);
	x2 = f;
	r += log(x) - 0.5 / x
	     - x2 * (1.0/12 - x2 * (1.0/120 - x2 * (1.0/252 - x2 * (1.0/240 - x2 * (1.0/132)))));
	return r;
}

double sf_polygamma (double n, double x)
{
	double f = 1;
	int k;
	if (n == 0) return digamma(x);
	if (n < 0 || n != floor(n) || x <= 0) return nan_val();
	for (k = 2; k <= (int) n; k++) f *= k;		/* n! */
	return ((int) n % 2 ? 1 : -1) * f * sf_hurwitz(n + 1, x);
}

/* ---------------- elliptic integrals (Carlson) ---------------- */

static double rf (double x, double y, double z)
{
	double alamb, ave, delx, dely, delz, e2, e3, sqrtx, sqrty, sqrtz, xt, yt, zt;
	if (x < 0 || y < 0 || z < 0 || x + y < TINY || x + z < TINY || y + z < TINY) return nan_val();
	xt = x; yt = y; zt = z;
	do	{
		sqrtx = sqrt(xt); sqrty = sqrt(yt); sqrtz = sqrt(zt);
		alamb = sqrtx * (sqrty + sqrtz) + sqrty * sqrtz;
		xt = 0.25 * (xt + alamb); yt = 0.25 * (yt + alamb); zt = 0.25 * (zt + alamb);
		ave = (xt + yt + zt) / 3.0;
		delx = (ave - xt) / ave; dely = (ave - yt) / ave; delz = (ave - zt) / ave;
		} while (fmax(fmax(fabs(delx), fabs(dely)), fabs(delz)) > 0.0008);
	e2 = delx * dely - delz * delz;
	e3 = delx * dely * delz;
	return (1.0 + (e2 / 24.0 - 0.1 - 3.0 * e3 / 44.0) * e2 + e3 / 14.0) / sqrt(ave);
}

static double rd (double x, double y, double z)
{
	double alamb, ave, delx, dely, delz, ea, eb, ec, ed, ee, fac, sqrtx, sqrty, sqrtz, sum, xt, yt, zt;
	if (x < 0 || y < 0 || x + y < TINY || z < TINY) return nan_val();
	xt = x; yt = y; zt = z; sum = 0; fac = 1;
	do	{
		sqrtx = sqrt(xt); sqrty = sqrt(yt); sqrtz = sqrt(zt);
		alamb = sqrtx * (sqrty + sqrtz) + sqrty * sqrtz;
		sum += fac / (sqrtz * (zt + alamb));
		fac *= 0.25;
		xt = 0.25 * (xt + alamb); yt = 0.25 * (yt + alamb); zt = 0.25 * (zt + alamb);
		ave = 0.2 * (xt + yt + 3.0 * zt);
		delx = (ave - xt) / ave; dely = (ave - yt) / ave; delz = (ave - zt) / ave;
		} while (fmax(fmax(fabs(delx), fabs(dely)), fabs(delz)) > 0.0005);
	ea = delx * dely; eb = delz * delz; ec = ea - eb; ed = ea - 6.0 * eb; ee = ed + ec + ec;
	return 3.0 * sum + fac * (1.0 + ed * (-3.0/14 + 9.0/88 * ed - 4.5/26 * delz * ee)
	       + delz * (ee / 6.0 + delz * (-9.0/22 * ec + delz * 3.0/26 * ea))) / (ave * sqrt(ave));
}

static double rc (double x, double y)
{
	double alamb, ave, s, w, xt, yt;
	if (x < 0 || y == 0) return nan_val();
	if (y > 0) { xt = x; yt = y; w = 1.0; }
	else { xt = x - y; yt = -y; w = sqrt(x) / sqrt(xt); }
	do	{
		alamb = 2.0 * sqrt(xt) * sqrt(yt) + yt;
		xt = 0.25 * (xt + alamb); yt = 0.25 * (yt + alamb);
		ave = (xt + yt + yt) / 3.0;
		s = (yt - ave) / ave;
		} while (fabs(s) > 0.0008);
	return w * (1.0 + s * s * (0.3 + s * (1.0/7 + s * (0.375 + s * 9.0/22)))) / sqrt(ave);
}

static double rj (double x, double y, double z, double p)
{
	double a = 0, alamb, alpha, ans, ave, b = 0, beta, delp, delx, dely, delz, ea, eb, ec, ed, ee,
	       fac, pt, rcx = 0, rho, sqrtx, sqrty, sqrtz, sum, tau, xt, yt, zt;
	if (x < 0 || y < 0 || z < 0 || x + y < TINY || x + z < TINY || y + z < TINY || fabs(p) < TINY)
		return nan_val();
	sum = 0; fac = 1;
	if (p > 0) { xt = x; yt = y; zt = z; pt = p; }
	else	/* Cauchy principal value */
		{
		xt = fmin(fmin(x, y), z);
		zt = fmax(fmax(x, y), z);
		yt = x + y + z - xt - zt;
		a = 1.0 / (yt - p);
		b = a * (zt - yt) * (yt - xt);
		pt = yt + b;
		rho = xt * zt / yt;
		tau = p * pt / yt;
		rcx = rc(rho, tau);
		}
	do	{
		sqrtx = sqrt(xt); sqrty = sqrt(yt); sqrtz = sqrt(zt);
		alamb = sqrtx * (sqrty + sqrtz) + sqrty * sqrtz;
		alpha = pt * (sqrtx + sqrty + sqrtz) + sqrtx * sqrty * sqrtz;
		alpha = alpha * alpha;
		beta = pt * (pt + alamb) * (pt + alamb);
		sum += fac * rc(alpha, beta);
		fac *= 0.25;
		xt = 0.25 * (xt + alamb); yt = 0.25 * (yt + alamb); zt = 0.25 * (zt + alamb); pt = 0.25 * (pt + alamb);
		ave = 0.2 * (xt + yt + zt + pt + pt);
		delx = (ave - xt) / ave; dely = (ave - yt) / ave; delz = (ave - zt) / ave; delp = (ave - pt) / ave;
		} while (fmax(fmax(fabs(delx), fabs(dely)), fmax(fabs(delz), fabs(delp))) > 0.0005);
	ea = delx * (dely + delz) + dely * delz;
	eb = delx * dely * delz;
	ec = delp * delp;
	ed = ea - 3.0 * ec;
	ee = eb + 2.0 * delp * (ea - ec);
	ans = 3.0 * sum + fac * (1.0 + ed * (-3.0/14 + 9.0/88 * ed - 4.5/26 * ee)
	      + eb * (1.0/6 + delp * (-3.0/11 + delp * 3.0/26)) + delp * ea * (1.0/3 - delp * 3.0/22)
	      - delp * ec / 3.0) / (ave * sqrt(ave));
	if (p <= 0) ans = a * (b * ans + 3.0 * (rcx - rf(xt, yt, zt)));
	return ans;
}

/* reduce phi to [-pi/2, pi/2]: phi = phi0 + k pi */
static double reduce_phi (double phi, int * k)
{
	double kk = floor(phi / PI + 0.5);
	* k = (int) kk;
	return phi - kk * PI;
}

static double ell_f (double phi0, double m)		/* |phi0| <= pi/2 */
{
	double s = sin(phi0), c = cos(phi0);
	return s * rf(c * c, 1.0 - m * s * s, 1.0);
}

static double ell_e (double phi0, double m)
{
	double s = sin(phi0), c = cos(phi0), q = 1.0 - m * s * s;
	return s * rf(c * c, q, 1.0) - m * s * s * s * rd(c * c, q, 1.0) / 3.0;
}

static double ell_pi (double n, double phi0, double m)
{
	double s = sin(phi0), c = cos(phi0), q = 1.0 - m * s * s;
	return s * rf(c * c, q, 1.0) + n * s * s * s * rj(c * c, q, 1.0, 1.0 - n * s * s) / 3.0;
}

double sf_elliptick (double m) { if (m >= 1) return nan_val(); return rf(0, 1.0 - m, 1.0); }

double sf_ellipticf (double phi, double m)
{
	int k;
	double p0 = reduce_phi(phi, & k);
	return ell_f(p0, m) + (k ? 2.0 * k * sf_elliptick(m) : 0.0);
}

double sf_elliptice1 (double m)
{
	if (m > 1) return nan_val();
	if (m == 1) return 1.0;
	return rf(0, 1.0 - m, 1.0) - m * rd(0, 1.0 - m, 1.0) / 3.0;
}

double sf_elliptice2 (double phi, double m)
{
	int k;
	double p0 = reduce_phi(phi, & k);
	return ell_e(p0, m) + (k ? 2.0 * k * sf_elliptice1(m) : 0.0);
}

double sf_ellipticpi2 (double n, double m)
{
	if (m >= 1 || n == 1) return nan_val();
	return rf(0, 1.0 - m, 1.0) + n * rj(0, 1.0 - m, 1.0, 1.0 - n) / 3.0;
}

double sf_ellipticpi3 (double n, double phi, double m)
{
	int k;
	double p0 = reduce_phi(phi, & k);
	return ell_pi(n, p0, m) + (k ? 2.0 * k * sf_ellipticpi2(n, m) : 0.0);
}

/* ---------------- hypergeometric functions ---------------- */

static double hyp2f1_series (double a, double b, double c, double z)
{
	double sum = 1, term = 1;
	int n;
	for (n = 0; n < 200000; n++)
		{
		term *= (a + n) * (b + n) / ((c + n) * (n + 1.0)) * z;
		sum += term;
		if (term == 0 || fabs(term) < EPS * fabs(sum)) return sum;
		}
	return nan_val();
}

double sf_hyp2f1 (double a, double b, double c, double z)
{
	if (c <= 0 && c == floor(c)) return nan_val();
	if (a <= 0 && a == floor(a)) return hyp2f1_series(a, b, c, z);	/* polynomial */
	if (b <= 0 && b == floor(b)) return hyp2f1_series(a, b, c, z);
	if (z < 1 && z >= -0.5)
		return hyp2f1_series(a, b, c, z);
	if (z < -0.5)		/* Pfaff: (1-z)^-a 2F1(a, c-b; c; z/(z-1)) */
		return pow(1.0 - z, -a) * hyp2f1_series(a, c - b, c, z / (z - 1.0));
	if (z == 1 && c - a - b > 0)		/* Gauss */
		return tgamma(c) * tgamma(c - a - b) / (tgamma(c - a) * tgamma(c - b));
	return nan_val();			/* z > 1: complex */
}

double sf_appellf1 (double a, double b1, double b2, double c, double x, double y)
{
	double sum = 0, t = 1, term;
	int m;
	if (fabs(x) >= 1 || fabs(y) >= 1) return nan_val();
	for (m = 0; m < 100000; m++)
		{
		term = t * sf_hyp2f1(a + m, b2, c + m, y);
		sum += term;
		if (fabs(term) < EPS * fabs(sum) && m > 2) break;
		t *= (a + m) * (b1 + m) / ((c + m) * (m + 1.0)) * x;
		if (t == 0) break;
		}
	return sum;
}

/* ---------------- Bessel function ---------------- */

double sf_besselj (double nu, double x)
{
	double sum = 0, term;
	int k;
	if (nu == floor(nu) && fabs(nu) < 1000) return jn((int) nu, x);
	if (x < 0) return nan_val();
	term = pow(x / 2.0, nu) / tgamma(nu + 1.0);
	for (k = 0; k < 500; k++)
		{
		sum += term;
		term *= -(x * x / 4.0) / ((k + 1.0) * (k + 1.0 + nu));
		if (fabs(term) < EPS * fabs(sum)) break;
		}
	return sum;
}

/* ---------------- C functions of rewrite (argument arrays) ---------------- */

#define A(k) (* (double *) arg[k])
#define F1(name, f) double * name (double * arg[]) { return mkreal(f(* arg[0])); }
#define F2(name, f) double * name (double * arg[]) { return mkreal(f(* arg[0], * arg[1])); }
#define F3(name, f) double * name (double * arg[]) { return mkreal(f(* arg[0], * arg[1], * arg[2])); }

F1(r_arcsec, sf_arcsec)
F1(r_arccsc, sf_arccsc)
F1(r_arcsech, sf_arcsech)
F1(r_arccsch, sf_arccsch)
F1(r_erf, erf)
F1(r_erfc, erfc)
F1(r_erfi, sf_erfi)
F1(r_fresnels, sf_fresnels)
F1(r_fresnelc, sf_fresnelc)
F1(r_si, sf_si)
F1(r_ci, sf_ci)
F1(r_shi, sf_shi)
F1(r_chi, sf_chi)
F1(r_ei, sf_ei)
F1(r_li, sf_li)
F2(r_expinte, sf_expinte)
F1(r_gamma, sf_gamma)
F2(r_gamma2, sf_gamma2)
F1(r_loggamma, sf_loggamma)
F2(r_polygamma, sf_polygamma)
F1(r_zeta, sf_zeta)
F2(r_zeta2, sf_zeta2)
F1(r_elliptick, sf_elliptick)
F2(r_ellipticf, sf_ellipticf)
F1(r_elliptice1, sf_elliptice1)
F2(r_elliptice2, sf_elliptice2)
F2(r_ellipticpi2, sf_ellipticpi2)
F3(r_ellipticpi3, sf_ellipticpi3)
double * r_hyp2f1 (double * arg[]) { return mkreal(sf_hyp2f1(* arg[0], * arg[1], * arg[2], * arg[3])); }
double * r_appellf1 (double * arg[])
{
	return mkreal(sf_appellf1(* arg[0], * arg[1], * arg[2], * arg[3], * arg[4], * arg[5]));
}
F2(r_besselj, sf_besselj)
