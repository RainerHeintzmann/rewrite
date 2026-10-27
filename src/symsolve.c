/*
 *	symsolve.c (2026)
 *
 *	C helpers of the equation solver inc/solve, included by symfn.c after
 *	symmat.c. The methods themselves are rules in the style of PRESS
 *	(Bundy and Welham 1981): isolation, polynomial methods, change of the
 *	unknown, attraction of logarithms, removal of square roots. The
 *	helpers analyse and transform the equation f = 0:
 *
 *	    occurs(f,x)      number of occurrences of x in f
 *	    eqnorm(f,x)      f over a common denominator, its numerator multiplied out
 *	    polyroots(p,x)   the roots of a polynomial (degree <= 2, rational
 *	                     roots, x^n = c, biquadratic), a list; or unevaluated
 *	    nroots(r,n)      the n roots of y^n = r (with im)
 *	    kernel(f,x)      ker(p, y, g): f = p(g(x)) with p a polynomial in y
 *	    unradical(f,x)   f = a + b*c^(1/2) -> a^2 - b^2*c
 *	    attract(f,x)     sum of c*ln(u) -> ln(prod u^c)
 *	    solcheck(l,f,x)  the solutions in l without those that make f
 *	                     undefined or (numerically) nonzero; no duplicates
 */

static int occurs (Node * u, Node * x)
{
	int i, n, c = 0;
	u = deref(u);
	if (! u) return 0;
	if (tequal(u, x)) return 1;
	if (u->type != Func) return 0;
	n = term_nargs(u);
	for (i = 0; i < n; i++) c += occurs(arg(u, i), x);
	return c;
}

static Node * s_occurs (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_int(occurs(a[0], a[1]));
}

/* ---- eqnorm: the numerator of f over a common denominator ---- */

/* the numerator of f over a common denominator of the negative powers of
 * terms with x (x = NULL: of any terms); *den (if wanted) the denominator */
static Node * eqnorm_den (Node * f, Node * x, Node ** den_out);

static Node * eqnorm (Node * f, Node * x)
{
	return eqnorm_den(f, x, NULL);
}

static Node * eqnorm_den (Node * f, Node * x, Node ** den_out)
{
	TList l = {0}, out = {0};
	Node * den[64], * r;
	double dex[64], e;
	int nd = 0, i, j, k;
	expand_to(f, & l);
	for (i = 0; i < l.n; i++)		/* the denominators with x: base^-e */
		{
		TList fl = {0};
		factors_to(l.t[i], & fl);
		for (j = 0; j < fl.n; j++)
			{
			Node * t = deref(fl.t[j]);
			if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e < 0 && e == floor(e)
			    && (x ? contains(arg(t, 0), x) : ! num_sym(arg(t, 0))))
				{
				for (k = 0; k < nd && ! tequal(den[k], arg(t, 0)); k++)
					;
				if (k == nd && nd < 64) { den[nd] = arg(t, 0); dex[nd++] = -e; }
				else if (k < nd && -e > dex[k]) dex[k] = -e;
				}
			}
		free(fl.t);
		}
	for (i = 0; i < l.n; i++)		/* each summand times the common denominator */
		{
		TList fl = {0};
		Node * t = NULL;
		double ek[64];
		for (k = 0; k < nd; k++) ek[k] = dex[k];
		factors_to(l.t[i], & fl);
		for (j = 0; j < fl.n; j++)	/* the exponents of the denominators added first */
			{
			Node * u = deref(fl.t[j]), * b = u;
			double eu = 1;
			if (is_head(u, "^", 2) && num_value(arg(u, 1), & e)) { b = arg(u, 0); eu = e; }
			for (k = 0; k < nd && ! tequal(den[k], b); k++)
				;
			if (k < nd) ek[k] += eu;
			else t = t ? mk_mul(t, tcpy(u)) : tcpy(u);
			}
		free(fl.t);
		for (k = 0; k < nd; k++)
			if (ek[k] != 0)
				{
				Node * p = mk_pow(tcpy(den[k]), mk_int(ek[k]));
				t = t ? mk_mul(t, p) : p;
				}
		if (! t) t = mk_int(1);
		expand_to(t, & out);
		delete(t);
		}
	if (den_out)
		{
		Node * d = NULL;
		for (k = 0; k < nd; k++)
			{
			Node * p = mk_pow(tcpy(den[k]), mk_int(dex[k]));
			d = d ? mk_mul(d, p) : p;
			}
		* den_out = d ? d : mk_int(1);
		}
	tl_free(& l);
	r = tl_collect(& out);
	return r;
}

/* the denominators b^-e of a product t as k^-e b'^-e (mp_canon), so that
 * denominators equal up to a constant factor become equal (takes t) */
static Node * canon_dens (Node * t)
{
	TList fl = {0};
	Node * r = NULL, * u, * b, * k;
	double e;
	int j;
	factors_to(t, & fl);
	for (j = 0; j < fl.n; j++)
		{
		u = deref(fl.t[j]);
		if (is_head(u, "^", 2) && num_value(arg(u, 1), & e) && e < 0 && e == floor(e)
		    && ! num_sym(arg(u, 0)) && (b = mp_canon(arg(u, 0), & k)) != NULL)
			u = mk_mul(mk_pow(k, mk_int(e)), mk_pow(b, mk_int(e)));
		else
			u = tcpy(u);
		r = r ? mk_mul(r, u) : u;
		}
	free(fl.t);
	delete(t);
	return r ? r : mk_int(1);
}

/* the number of summands of the common denominator of the summands l,
 * multiplied out (an upper bound) */
static double den_size (TList * l)
{
	Node * den[64];
	double size = 1, e;
	int nd = 0, i, j, k;
	for (i = 0; i < l->n; i++)
		{
		TList fl = {0};
		factors_to(l->t[i], & fl);
		for (j = 0; j < fl.n; j++)
			{
			Node * t = deref(fl.t[j]);
			if (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e < 0 && ! num_sym(arg(t, 0)))
				{
				for (k = 0; k < nd && ! tequal(den[k], arg(t, 0)); k++)
					;
				if (k == nd && nd < 64)
					{
					TList sl = {0};
					den[nd++] = arg(t, 0);
					expand_to(arg(t, 0), & sl);
					size *= pow(sl.n, -e);
					tl_free(& sl);
					}
				}
			}
		free(fl.t);
		}
	return size;
}

/* ---- cancel(u): u as N/D over a common denominator, the polynomial gcd
 * of N and D cancelled (symmat.c: mp_gcd); unevaluated if the common
 * denominator would be too large (nested roots, as in Int(1/(1+x^5),x)) ---- */
static Node * s_cancel (Node * a[], int n, Symbol * f)
{
	Node * d, * nu = NULL, * u = NULL;
	TList l = {0};
	MPoly pn, pd;
	int i;
	if (n != 1) return NULL;
	u = s_normform(a, 1, NULL);		/* D leaves 0*u, 1*u, mi(u) */
	expand_to(u, & l);
	delete(u);
	u = NULL;
	for (i = 0; i < l.n; i++) l.t[i] = canon_dens(l.t[i]);
	if (den_size(& l) > 20000) { tl_free(& l); return NULL; }
	for (i = 0; i < l.n; i++) u = mk_add(u, tcpy(l.t[i]));
	tl_free(& l);
	nu = eqnorm_den(u ? u : a[0], NULL, & d);
	delete(u);
	pn = mp_from(nu);
	pd = mp_from(d);
	delete(nu);
	delete(d);
	return mp_quotient_free(& pn, & pd);
}

/* polygcd(a, b): the greatest common divisor of two polynomials */
static Node * s_polygcd (Node * a[], int n, Symbol * f)
{
	MPoly pa, pb, g;
	Node * r;
	if (n != 2 && n != 3) return NULL;		/* polygcd(p, q) or Rubi's PolyGCD[p, q, x] */
	pa = mp_from(a[0]);
	pb = mp_from(a[1]);
	g = mp_gcd(& pa, & pb);
	r = nice(mp_term(& g));
	mp_free(& pa);
	mp_free(& pb);
	mp_free(& g);
	return r;
}

static Node * s_eqnorm (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return eqnorm(a[0], a[1]);
}

/* ---- roots ---- */

static Node * unit_root (long p, long q, Node * im)	/* cos(p pi/q) + im sin(p pi/q) */
{
	Node * c = cos_pi(p, q), * s = cos_pi(q - 2 * p, 2 * q);	/* sin t = cos(pi/2 - t) */
	return collected(mk_add(c, mk_mul(tcpy(im), s)));
}

/* the n roots of y^n = r: r^(1/n) times the n-th roots of unity; for a
 * negative number r: |r|^(1/n) times the roots of -1 */
static Node * nroots (Node * r, int n)
{
	Node * e[64], * im = im_node(), * base;
	double v;
	int k, neg;
	if (n < 1 || n > 64) return NULL;
	neg = is_num(r, & v) && v < 0;
	base = mk_pow(neg ? mk_neg(tcpy(r)) : tcpy(r), mk_pow(mk_int(n), mk_int(-1)));
	if (n == 1) { delete(im); return mk_list(& base, 1); }
	if (! im)
		{
		delete(base);
		return NULL;
		}
	for (k = 0; k < n; k++)
		{
		Node * u = unit_root(neg ? 2 * k + 1 : 2 * k, n, im);
		e[k] = nice(collected(mk_mul(tcpy(base), u)));
		}
	delete(base);
	delete(im);
	return mk_list(e, n);
}

static Node * s_nroots (Node * a[], int n, Symbol * f)
{
	double v;
	if (n != 2 || ! is_num(a[1], & v) || v != floor(v)) return NULL;
	return nroots(a[0], (int) v);
}

/* the square root of d; im*(-d)^(1/2) for a negative number */
static Node * sqrt_im (Node * d)
{
	double v;
	Node * im;
	if (is_num(d, & v) && v < 0 && (im = im_node()))
		return mk_mul(im, mk_pow(mk_neg(d), mk_num_ex(0.5, 1)));
	return mk_pow(d, mk_num_ex(0.5, 1));
}

static void add_root (Node * e[], int * n, Node * r)	/* without duplicates (takes r) */
{
	int i;
	for (i = 0; i < * n; i++)
		if (eq_terms(e[i], r)) { delete(r); return; }
	if (* n < 64) e[(* n)++] = r;
	else delete(r);
}

/* the roots of c[0] + c[1] x + ... + c[deg] x^deg into e; 0 if not all found */
static int cardano (Node * cf[], Node * e[], int * ne);
static int ferrari (Node * cf[], Node * e[], int * ne);

static int poly_solve (Node * cin[], int deg, Node * e[], int * ne)
{
	Node * c[MAXDEG];		/* borrowed: the caller owns the coefficients */
	double v;
	int k, nz = 0;
	for (k = 0; k <= deg; k++) c[k] = cin[k];
	while (deg > 0 && is_num(c[deg], & v) && v == 0) deg--;
	while (nz < deg && is_num(c[nz], & v) && v == 0) nz++;	/* x^nz factor: root 0 */
	if (nz > 0)
		{
		add_root(e, ne, mk_int(0));
		for (k = 0; k + nz <= deg; k++) c[k] = c[k + nz];
		deg -= nz;
		}
	if (deg <= 0) return deg == 0;
	if (deg == 1)
		{
		add_root(e, ne, nice(collected(mk_neg(mk_mul(tcpy(c[0]), mk_pow(tcpy(c[1]), mk_int(-1)))))));
		return 1;
		}
	if (deg == 2)		/* (-b +- (b^2 - 4ac)^(1/2)) / (2a) */
		{
		Node * d = collected(mk_add(mk_pow(tcpy(c[1]), mk_int(2)), mk_mul(mk_int(-4), mk_mul(tcpy(c[2]), tcpy(c[0])))));
		Node * s = sqrt_im(d), * a2 = mk_pow(mk_mul(mk_int(2), tcpy(c[2])), mk_int(-1));
		add_root(e, ne, nice(collected(mk_mul(tcpy(a2), mk_add(mk_neg(tcpy(c[1])), tcpy(s))))));
		add_root(e, ne, nice(collected(mk_mul(a2, mk_add(mk_neg(tcpy(c[1])), mk_neg(s))))));
		return 1;
		}
	/* x^n = r: a binomial */
	for (k = 1; k < deg && is_num(c[k], & v) && v == 0; k++)
		;
	if (k == deg)
		{
		Node * r0 = collected(mk_neg(mk_mul(tcpy(c[0]), mk_pow(tcpy(c[deg]), mk_int(-1))))), * l = nroots(r0, deg);
		int i;
		delete(r0);
		if (! l) return 0;
		for (i = 0; i < list_len(l); i++) add_root(e, ne, tcpy(arg(l, i)));
		delete(l);
		return 1;
		}
	/* only even powers: a polynomial in x^2 */
	for (k = 1; k <= deg && (k % 2 == 0 || (is_num(c[k], & v) && v == 0)); k++)
		;
	if (k > deg && deg % 2 == 0)
		{
		Node * h[MAXDEG], * y[64];
		int ny = 0, i, ok;
		for (k = 0; k <= deg / 2; k++) h[k] = c[2 * k];
		ok = poly_solve(h, deg / 2, y, & ny);
		for (i = 0; i < ny; i++)
			{
			Node * s = sqrt_im(tcpy(y[i]));
			add_root(e, ne, nice(collected(tcpy(s))));
			add_root(e, ne, nice(collected(mk_neg(s))));
			delete(y[i]);
			}
		return ok;
		}
	/* rational roots of a polynomial with integer coefficients: divide them out */
	{
	double cv[MAXDEG];
	int integral = 1;
	for (k = 0; k <= deg; k++)
		if (! is_num(c[k], & cv[k]) || ! is_exact(c[k]) || cv[k] != floor(cv[k]) || fabs(cv[k]) > 1e9)
			integral = 0;
	if (integral)
	{
	double a0 = fabs(cv[0]), an = fabs(cv[deg]), p, q;
	for (p = 1; p <= a0 && p <= 1000; p++)
		{
		if (fmod(a0, p) != 0) continue;
		for (q = 1; q <= an && q <= 1000; q++)
			{
			int sgn;
			if (fmod(an, q) != 0) continue;
			for (sgn = -1; sgn <= 1; sgn += 2)
				{
				double x0 = sgn * p / q, val = 0, b[MAXDEG];
				for (k = deg; k >= 0; k--) val = val * x0 + cv[k];
				if (fabs(val) > 1e-9 * (1 + fabs(cv[0]))) continue;
				/* found: divide by (x - x0) (Horner), solve the rest */
				b[deg - 1] = cv[deg];
				for (k = deg - 1; k >= 1; k--) b[k - 1] = cv[k] + x0 * b[k];
				add_root(e, ne, mk_num_ex(x0, 1));
				{
				Node * nc[MAXDEG];
				int r, j;
				for (j = 0; j < deg; j++) nc[j] = mk_num_ex(b[j], 1);
				r = poly_solve(nc, deg - 1, e, ne);
				for (j = 0; j < deg; j++) delete(nc[j]);
				return r;
				}
				}
			}
		}
	}
	}
	if (deg == 3) return cardano(c, e, ne);
	if (deg == 4) return ferrari(c, e, ne);
	return 0;
}

/* ---- the cubic and the quartic formulas ---- */

static Node * q_(double p, double q) { return mk_num_ex(p / q, 1); }	/* the fraction p/q */

static Node * cbrt_any (Node * u)	/* some cube root of u: real for a negative number */
{
	double v;
	if (is_num(u, & v) && v < 0)
		return mk_neg(mk_pow(mk_neg(u), q_(1, 3)));
	return mk_pow(u, q_(1, 3));
}

static int is_zero_node (Node * u)
{
	double v;
	Node * c = collected(tcpy(u));
	int z = is_num(c, & v) && v == 0;
	delete(c);
	return z;
}

/* a x^3 + b x^2 + c x + d = 0 (Cardano): x = t - b/(3a), t^3 + p t + q = 0,
 * t = w C - p/(3 w C) with C^3 = -q/2 + (q^2/4 + p^3/27)^(1/2), w^3 = 1 */
static int cardano (Node * cf[], Node * e[], int * ne)
{
	Node * a = cf[3], * b = cf[2], * c = cf[1], * d = cf[0], * im = im_node(), * p, * q, * shift, * D, * C;
	int k;
	if (! im) return 0;
	/* p = (3ac - b^2)/(3a^2), q = (2b^3 - 9abc + 27a^2 d)/(27a^3) */
	p = collected(mk_mul(mk_add(mk_mul(mk_int(3), mk_mul(tcpy(a), tcpy(c))), mk_neg(mk_pow(tcpy(b), mk_int(2)))),
	                     mk_pow(mk_mul(mk_int(3), mk_pow(tcpy(a), mk_int(2))), mk_int(-1))));
	q = collected(mk_mul(mk_add(mk_add(mk_mul(mk_int(2), mk_pow(tcpy(b), mk_int(3))),
	                                   mk_mul(mk_int(-9), mk_mul(tcpy(a), mk_mul(tcpy(b), tcpy(c))))),
	                            mk_mul(mk_int(27), mk_mul(mk_pow(tcpy(a), mk_int(2)), tcpy(d)))),
	                     mk_pow(mk_mul(mk_int(27), mk_pow(tcpy(a), mk_int(3))), mk_int(-1))));
	shift = collected(mk_neg(mk_mul(tcpy(b), mk_pow(mk_mul(mk_int(3), tcpy(a)), mk_int(-1)))));
	if (is_zero_node(p))				/* t^3 = -q */
		{
		Node * l = nroots(collected(mk_neg(tcpy(q))), 3);
		int i;
		if (l)
			{
			for (i = 0; i < list_len(l); i++)
				add_root(e, ne, nice(collected(mk_add(tcpy(arg(l, i)), tcpy(shift)))));
			delete(l);
			}
		delete(p); delete(q); delete(shift); delete(im);
		return l != NULL;
		}
	D = collected(mk_add(mk_mul(q_(1, 4), mk_pow(tcpy(q), mk_int(2))), mk_mul(q_(1, 27), mk_pow(tcpy(p), mk_int(3)))));
	{
	Node * s = sqrt_im(D), * h = collected(mk_add(mk_mul(q_(-1, 2), tcpy(q)), tcpy(s)));
	if (is_zero_node(h))				/* take the other sign */
		{
		delete(h);
		h = collected(mk_add(mk_mul(q_(-1, 2), tcpy(q)), mk_neg(tcpy(s))));
		}
	delete(s);
	C = cbrt_any(h);
	}
	for (k = 0; k < 3; k++)
		{
		Node * w = unit_root(2 * k, 3, im), * wc = mk_mul(w, tcpy(C));
		Node * t = mk_add(tcpy(wc), mk_neg(mk_mul(tcpy(p), mk_pow(mk_mul(mk_int(3), wc), mk_int(-1)))));
		add_root(e, ne, nice(mk_add(t, tcpy(shift))));
		}
	delete(p); delete(q); delete(shift); delete(C); delete(im);
	return 1;
}

/* a x^4 + b x^3 + c x^2 + d x + f = 0 (Ferrari): x = y - b/(4a),
 * y^4 + p y^2 + q y + r = 0; with a root m != 0 of the resolvent cubic
 * 8 m^3 + 8 p m^2 + (2 p^2 - 8 r) m - q^2 = 0 and s = (2m)^(1/2):
 * y = (+-1 s +-2 (-(2p + 2m +-1 2q/s))^(1/2)) / 2 */
static int ferrari (Node * cf[], Node * e[], int * ne)
{
	Node * a = cf[4], * b = cf[3], * c = cf[2], * d = cf[1], * f = cf[0], * p, * q, * r, * shift, * rc[4], * m[64], * s;
	int nm = 0, k, s1, s2;
	Node * ia = mk_pow(tcpy(a), mk_int(-1));
	/* p = c/a - 3b^2/(8a^2), q = b^3/(8a^3) - bc/(2a^2) + d/a,
	 * r = -3b^4/(256a^4) + b^2 c/(16a^3) - bd/(4a^2) + f/a */
	p = collected(mk_add(mk_mul(tcpy(c), tcpy(ia)), mk_mul(q_(-3, 8), mk_mul(mk_pow(tcpy(b), mk_int(2)), mk_pow(tcpy(ia), mk_int(2))))));
	q = collected(mk_add(mk_add(mk_mul(q_(1, 8), mk_mul(mk_pow(tcpy(b), mk_int(3)), mk_pow(tcpy(ia), mk_int(3)))),
	                            mk_mul(q_(-1, 2), mk_mul(mk_mul(tcpy(b), tcpy(c)), mk_pow(tcpy(ia), mk_int(2))))),
	                     mk_mul(tcpy(d), tcpy(ia))));
	r = collected(mk_add(mk_add(mk_mul(q_(-3, 256), mk_mul(mk_pow(tcpy(b), mk_int(4)), mk_pow(tcpy(ia), mk_int(4)))),
	                            mk_mul(q_(1, 16), mk_mul(mk_mul(mk_pow(tcpy(b), mk_int(2)), tcpy(c)), mk_pow(tcpy(ia), mk_int(3))))),
	                     mk_add(mk_mul(q_(-1, 4), mk_mul(mk_mul(tcpy(b), tcpy(d)), mk_pow(tcpy(ia), mk_int(2)))),
	                            mk_mul(tcpy(f), tcpy(ia)))));
	shift = collected(mk_mul(q_(-1, 4), mk_mul(tcpy(b), tcpy(ia))));
	delete(ia);
	if (is_zero_node(q))				/* biquadratic: y^2 = z, z^2 + p z + r = 0 */
		{
		Node * h[3] = { r, p, NULL }, * z[64];
		int nz = 0, i, ok;
		h[2] = mk_int(1);
		ok = poly_solve(h, 2, z, & nz);
		delete(h[2]);
		for (i = 0; i < nz; i++)
			{
			Node * sq = sqrt_im(tcpy(z[i]));
			add_root(e, ne, nice(mk_add(tcpy(sq), tcpy(shift))));
			add_root(e, ne, nice(mk_add(mk_neg(sq), tcpy(shift))));
			delete(z[i]);
			}
		delete(p); delete(q); delete(r); delete(shift);
		return ok;
		}
	rc[3] = mk_int(8);				/* the resolvent cubic */
	rc[2] = collected(mk_mul(mk_int(8), tcpy(p)));
	rc[1] = collected(mk_add(mk_mul(mk_int(2), mk_pow(tcpy(p), mk_int(2))), mk_mul(mk_int(-8), tcpy(r))));
	rc[0] = collected(mk_neg(mk_pow(tcpy(q), mk_int(2))));
	k = poly_solve(rc, 3, m, & nm);
	for (k = 0; k < 4; k++) delete(rc[k]);
	for (k = 0; k < nm && is_zero_node(m[k]); k++)
		;
	if (k == nm)
		{
		for (k = 0; k < nm; k++) delete(m[k]);
		delete(p); delete(q); delete(r); delete(shift);
		return 0;
		}
	s = sqrt_im(mk_mul(mk_int(2), tcpy(m[k])));
	for (s1 = -1; s1 <= 1; s1 += 2)
		{
		Node * inner = collected(mk_neg(mk_add(mk_add(mk_mul(mk_int(2), tcpy(p)), mk_mul(mk_int(2), tcpy(m[k]))),
		                                       mk_mul(mk_int(2 * s1), mk_mul(tcpy(q), mk_pow(tcpy(s), mk_int(-1)))))));
		Node * t = sqrt_im(inner);
		for (s2 = -1; s2 <= 1; s2 += 2)
			{
			Node * y = mk_mul(q_(1, 2), mk_add(mk_mul(mk_int(s1), tcpy(s)), mk_mul(mk_int(s2), tcpy(t))));
			add_root(e, ne, nice(mk_add(y, tcpy(shift))));
			}
		delete(t);
		}
	for (k = 0; k < nm; k++) delete(m[k]);
	delete(s); delete(p); delete(q); delete(r); delete(shift);
	return 1;
}

static Node * s_polyroots (Node * a[], int n, Symbol * f)
{
	Node * c[MAXDEG], * e[64];
	int deg, ne = 0, k, ok;
	if (n != 2 || ! poly_coeffs(a[0], a[1], c, & deg) || deg < 1) return NULL;
	for (k = 0; k <= deg; k++)
		{
		Node * t = collected(c[k]);
		c[k] = t;
		}
	ok = poly_solve(c, deg, e, & ne);
	for (k = 0; k <= deg; k++) delete(c[k]);
	if (! ok)
		{
		for (k = 0; k < ne; k++) delete(e[k]);
		return NULL;
		}
	return mk_list(e, ne);
}

/* sqrt(u) as u^(1/2), so that the methods see one form */
static Node * sqrt_to_pow (Node * t)
{
	Node * args = NULL, ** tail = & args, * r;
	int i, n;
	t = deref(t);
	if (! t || t->type != Func) return tcpy(t);
	n = term_nargs(t);
	for (i = 0; i < n; i++)
		{
		Node * c = sqrt_to_pow(arg(t, i));
		if (i < n - 1) { * tail = mknod(Terms, c, NULL); tail = & (* tail)->r; }
		else * tail = c;
		}
	r = mknod(Func, t->l, args);
	if (is_head(r, "sqrt", 1))
		{
		Node * u = tcpy(arg(r, 0));
		delete(r);
		r = mk_pow(u, mk_num_ex(0.5, 1));
		}
	return r;
}

/* ---- kernel: f as a polynomial in g(x) ---- */

static Node * solve_var (void)		/* the new unknown y (CONST yker of inc/solve) */
{
	Symbol * s = role_find("yker");
	return s ? mknod(Const, (Node *) s, NULL) : NULL;
}

/* exponentials F^u with u = a x + b; the gcd of the a as a rational multiple */
typedef struct { Node * x, * base, * d; int ok, n; } ExpK;

static int exp_parts (Node * t, Node ** base, Node ** u)	/* t = base^u or exp(u) */
{
	t = deref(t);
	if (is_head(t, "exp", 1)) { * base = NULL; * u = arg(t, 0); return 1; }
	if (is_head(t, "^", 2)) { * base = arg(t, 0); * u = arg(t, 1); return 1; }
	return 0;
}

static void exp_scan (Node * t, ExpK * s)
{
	Node * b, * u, * c0, * c1;
	int i, n;
	t = deref(t);
	if (! t || t->type != Func || ! contains(t, s->x)) return;
	if (exp_parts(t, & b, & u) && (! b || ! contains(b, s->x)) && contains(u, s->x))
		{
		if (! linear_parts(u, s->x, & c0, & c1)) { s->ok = 0; return; }
		delete(c0);
		if (s->n == 0)
			{
			s->base = b; s->d = c1;
			}
		else
			{
			double q, p, r;
			Node * ratio = collected(mk_mul(tcpy(c1), mk_pow(tcpy(s->d), mk_int(-1))));
			if ((b && (! s->base || ! tequal(b, s->base))) || (! b && s->base)
			    || ! is_num(ratio, & r) || ! rat_approx(r, & p, & q))
				s->ok = 0;
			else if (q != 1)		/* c1 = d*p/q: the common unit becomes d/q */
				s->d = collected(mk_mul(s->d, mk_num_ex(1.0 / q, 1)));
			delete(ratio);
			delete(c1);
			}
		s->n++;
		return;
		}
	n = term_nargs(t);
	for (i = 0; i < n; i++) exp_scan(arg(t, i), s);
}

/* f with every F^(a x + b) replaced by F^b * y^(a/d) */
static Node * exp_replace (Node * t, ExpK * s, Node * y)
{
	Node * b, * u, * c0, * c1, * args = NULL, ** tail = & args, * r;
	int i, n;
	t = deref(t);
	if (! t || t->type != Func || ! contains(t, s->x)) return tcpy(t);
	if (exp_parts(t, & b, & u) && (! b || ! contains(b, s->x)) && contains(u, s->x)
	    && linear_parts(u, s->x, & c0, & c1))
		{
		Node * k = collected(mk_mul(c1, mk_pow(tcpy(s->d), mk_int(-1))));
		Node * fb = b ? mk_pow(tcpy(b), c0) : mk_f1("exp", c0);
		return mk_mul(fb, mk_pow(tcpy(y), k));
		}
	n = term_nargs(t);
	for (i = 0; i < n; i++)
		{
		Node * c = exp_replace(arg(t, i), s, y);
		if (i < n - 1) { * tail = mknod(Terms, c, NULL); tail = & (* tail)->r; }
		else * tail = c;
		}
	r = mknod(Func, t->l, args);
	return r;
}

/* the subterms g(x) that are no sums, products or natural powers: the atoms of f */
static void x_atoms (Node * t, Node * x, Node * at[], int * na)
{
	double e;
	int i, n;
	t = deref(t);
	if (! t || ! contains(t, x)) return;
	if (is_head(t, "+", 2) || is_head(t, "-", 2) || is_head(t, "*", 2) || is_head(t, "-", 1)
	    || (is_head(t, "^", 2) && num_value(arg(t, 1), & e) && e == floor(e)))
		{
		n = term_nargs(t);
		for (i = 0; i < n; i++) x_atoms(arg(t, i), x, at, na);
		return;
		}
	for (i = 0; i < * na; i++)
		if (tequal(at[i], t)) return;
	if (* na < 16) at[(* na)++] = t;
}

static Node * kernel_pow (Node * f, Node * x);

static Node * kernel (Node * f, Node * x)
{
	Node * f2 = sqrt_to_pow(f), * r = kernel_pow(f2, x);
	delete(f2);
	return r;
}

static Node * kernel_pow (Node * f, Node * x)
{
	Node * y = solve_var(), * p = NULL, * g = NULL, * at[16], * ker;
	int na = 0, i;
	double e, p1, q1;
	if (! y) return NULL;
	x_atoms(f, x, at, & na);
	if (na == 1 && ! tequal(at[0], x))		/* a single atom: sin(x), ln(x), x^(1/2) */
		{
		g = tcpy(at[0]);
		p = replace(f, g, y);
		}
	if (! p)					/* x^(p/q) and x: y = x^(1/L) */
		{
		long L = 1;
		int ok = na > 0;
		for (i = 0; i < na && ok; i++)
			if (tequal(at[i], x)) ;
			else if (is_head(at[i], "^", 2) && tequal(arg(at[i], 0), x) && num_value(arg(at[i], 1), & e)
			         && rat_approx(e, & p1, & q1) && q1 < 100)
				{
				long a = L, b = (long) q1;
				while (b) { long t = a % b; a = b; b = t; }
				L = L / a * (long) q1;
				}
			else
				ok = 0;
		if (ok && L > 1)
			{
			Node * t = replace(f, x, mk_pow(tcpy(y), mk_int(L)));	/* x = y^L */
			p = collected(t);
			g = mk_pow(tcpy(x), mk_num_ex(1.0 / L, 1));
			}
		}
	if (! p)					/* exponentials: y = F^(d x) */
		{
		ExpK s = { x, NULL, NULL, 1, 0 };
		exp_scan(f, & s);
		if (s.ok && s.n > 0)
			{
			p = exp_replace(f, & s, y);
			g = s.base ? mk_pow(tcpy(s.base), mk_mul(tcpy(s.d), tcpy(x)))
			           : mk_f1("exp", mk_mul(tcpy(s.d), tcpy(x)));
			}
		if (s.d) delete(s.d);
		}
	if (! p || contains(p, x))
		{
		delete(p); delete(g); delete(y);
		return NULL;
		}
	{
	Node * q = eqnorm(p, y), * c[MAXDEG];
	int deg, k;
	delete(p);
	if (! poly_coeffs(q, y, c, & deg) || deg < 1)
		{
		delete(q); delete(g); delete(y);
		return NULL;
		}
	for (k = 0; k <= deg; k++) delete(c[k]);
	ker = mknod(Terms, q, mknod(Terms, y, g));
	return mknod(Func, (Node *) getsymbol(fsym("ker"), ker), ker);
	}
}

static Node * s_kernel (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return kernel(a[0], a[1]);
}

/* ---- unradical: f = a + b*c^(1/2) = 0 -> a^2 - b^2*c = 0 ---- */

static Node * find_sqrt (Node * t, Node * x)	/* a subterm c^(k/2) with x, odd k */
{
	double e;
	int i, n;
	t = deref(t);
	if (! t || t->type != Func || ! contains(t, x)) return NULL;
	if (is_head(t, "^", 2) && contains(arg(t, 0), x) && num_value(arg(t, 1), & e)
	    && e * 2 == floor(e * 2) && e != floor(e))
		return arg(t, 0);
	if (is_head(t, "sqrt", 1) && contains(arg(t, 0), x)) return arg(t, 0);
	n = term_nargs(t);
	for (i = 0; i < n; i++)
		{
		Node * r = find_sqrt(arg(t, i), x);
		if (r) return r;
		}
	return NULL;
}

static Node * unradical_pow (Node * f, Node * x);

static Node * unradical (Node * f, Node * x)
{
	Node * f2 = sqrt_to_pow(f), * r = unradical_pow(f2, x);
	delete(f2);
	return r;
}

static Node * unradical_pow (Node * f, Node * x)
{
	Node * c = find_sqrt(f, x), * y = solve_var(), * p, * q, * cf[MAXDEG], * a = NULL, * b = NULL, * r;
	int deg, k;
	if (! c || ! y) { delete(y); return NULL; }
	c = tcpy(c);
	{
	Node * t = replace(f, mk_pow(tcpy(c), mk_num_ex(0.5, 1)), y);	/* c^(1/2) = y */
	p = replace(t, mk_pow(tcpy(c), mk_num_ex(-0.5, 1)), mk_pow(tcpy(y), mk_int(-1)));
	delete(t);
	}
	q = eqnorm(p, y);
	delete(p);
	if (! poly_coeffs(q, y, cf, & deg) || deg < 1)
		{
		delete(q); delete(c); delete(y);
		return NULL;
		}
	for (k = 0; k <= deg; k++)	/* y^k = c^(k/2): even k into a, odd k into b */
		{
		Node * t = mk_mul(cf[k], mk_pow(tcpy(c), mk_int(k / 2)));
		if (k % 2 == 0) a = a ? mk_add(a, t) : t;
		else b = b ? mk_add(b, t) : t;
		}
	if (! a) a = mk_int(0);
	if (! b) b = mk_int(0);
	r = eqnorm(mk_add(mk_pow(a, mk_int(2)), mk_neg(mk_mul(mk_pow(b, mk_int(2)), c))), x);
	delete(q);
	delete(y);
	return r;
}

static Node * s_unradical (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return unradical(a[0], a[1]);
}

/* ---- attract: c1*ln(u1) + c2*ln(u2) + ... = ln(u1^c1 * u2^c2) ---- */

static Node * attract (Node * f, Node * x)
{
	TList l = {0};
	Node * prod = NULL, * rest = NULL;
	int i, nl = 0;
	summands_to(f, & l, 0);
	for (i = 0; i < l.n; i++)
		{
		TList fl = {0};
		Node * lnf = NULL, * c = NULL;
		int j, ok = 1;
		factors_to(l.t[i], & fl);
		for (j = 0; j < fl.n; j++)
			{
			Node * t = deref(fl.t[j]);
			if (! lnf && is_head(t, "ln", 1) && contains(t, x)) lnf = arg(t, 0);
			else if (! contains(t, x)) c = c ? mk_mul(c, tcpy(t)) : tcpy(t);
			else ok = 0;
			}
		free(fl.t);
		if (ok && lnf)
			{
			Node * pw = c ? mk_pow(tcpy(lnf), c) : tcpy(lnf);
			prod = prod ? mk_mul(prod, pw) : pw;
			nl++;
			}
		else
			{
			delete(c);
			rest = rest ? mk_add(rest, tcpy(l.t[i])) : tcpy(l.t[i]);
			}
		}
	tl_free(& l);
	if (nl < 2) { delete(prod); delete(rest); return NULL; }
	prod = mk_f1("ln", prod);
	return rest ? mk_add(prod, rest) : prod;
}

static Node * s_attract (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return attract(a[0], a[1]);
}

/* ---- solcheck: drop solutions that make f undefined or nonzero ---- */

static Node * s_solfilter (Node * a[], int n, Symbol * f)
{
	Node * e[64];
	int ne = 0, i, len;
	if (n != 3) return NULL;
	if (is_nil(a[0])) return tcpy(a[0]);		/* no solution */
	if (! is_head(a[0], "list", -1)) return NULL;
	len = list_len(a[0]);
	for (i = 0; i < len && i < 64; i++)
		{
		Node * s = arg(deref(a[0]), i), * v;
		double val;
		int keep = 1;
		v = replace(a[1], a[2], s);
		if (num_value_r(v, & val))
			keep = isfinite(val) && fabs(val) < 1e-7;
		else
			{
			Node * c = collected(tcpy(v));
			double z;
			if (is_num(c, & z)) keep = isfinite(z) && fabs(z) < 1e-9;
			delete(c);
			}
		delete(v);
		if (keep) add_root(e, & ne, tcpy(s));
		}
	return mk_list(e, ne);
}

/* ---- predicates for the rule conditions ---- */

static Node * s_attractq (Node * a[], int n, Symbol * f)
{
	Node * r;
	if (n != 2) return NULL;
	r = attract(a[0], a[1]);
	delete(r);
	return mk_bool(r != NULL, f);
}

static Node * s_kernelq (Node * a[], int n, Symbol * f)
{
	Node * r;
	if (n != 2) return NULL;
	r = kernel(a[0], a[1]);
	delete(r);
	return mk_bool(r != NULL, f);
}

static Node * s_radicalq (Node * a[], int n, Symbol * f)
{
	if (n != 2) return NULL;
	return mk_bool(find_sqrt(a[0], a[1]) != NULL, f);
}

/* isoeach(g, [r1,..,rn], x) = union(iso(g,r1,x), union(iso(g,r2,x), ..)):
 * the isolation for each solution of the new unknown */
static Node * s_isoeach (Node * a[], int n, Symbol * f)
{
	Node * r = NULL;
	int k, len;
	if (n != 3) return NULL;
	if (is_nil(a[1])) return tcpy(a[1]);
	if (! is_head(a[1], "list", -1)) return NULL;
	len = list_len(a[1]);
	for (k = len - 1; k >= 0; k--)
		{
		Node * args = mknod(Terms, tcpy(a[0]), mknod(Terms, tcpy(arg(deref(a[1]), k)), tcpy(a[2])));
		Node * t = mknod(Func, (Node *) getsymbol(fsym("iso"), args), args);
		r = r ? mk_f2("union", t, r) : t;
		}
	return r;
}

/* ---- linsys: a system of linear equations, solve([eqs], [vars]) ----
 * The coefficients of the unknowns are collected into a matrix and the
 * system is solved with Bareiss' elimination (symmat.c). The values come
 * in the order of the unknowns; nonlinear systems stay unevaluated. */

static Node * s_linsys (Node * a[], int n, Symbol * f)
{
	Node * A[MAXDIM * MAXDIM], * b[MAXDIM], * rows[MAXDIM], * m, * bv, * r;
	int ne, nv, i, j, k, ok = 1;
	if (n != 2 || ! is_head(a[0], "list", -1) || ! is_head(a[1], "list", -1)) return NULL;
	ne = list_len(a[0]);
	nv = list_len(a[1]);
	if (ne != nv || ne < 1 || ne > MAXDIM) return NULL;
	for (i = 0; i < ne * nv; i++) A[i] = NULL;
	for (i = 0; i < ne; i++) b[i] = NULL;
	for (i = 0; i < ne && ok; i++)
		{
		Node * eq = deref(arg(deref(a[0]), i)), * fi;
		TList l = {0};
		if (! is_head(eq, "==", 2)) { ok = 0; break; }
		fi = mk_add(tcpy(arg(eq, 0)), mk_neg(tcpy(arg(eq, 1))));
		expand_to(fi, & l);
		delete(fi);
		for (k = 0; k < l.n && ok; k++)
			{
			Node * c;
			double deg;
			int jv = -1;
			for (j = 0; j < nv; j++)
				if (contains(l.t[k], arg(deref(a[1]), j)))
					{
					if (jv >= 0) { ok = 0; break; }	/* x*y: not linear */
					jv = j;
					}
			if (! ok) break;
			if (jv < 0)				/* a constant: to the right side */
				{
				Node * t = mk_neg(tcpy(l.t[k]));
				b[i] = b[i] ? mk_add(b[i], t) : t;
				continue;
				}
			if (! monomial(l.t[k], arg(deref(a[1]), jv), & c, & deg) || deg != 1) { ok = 0; break; }
			A[i * nv + jv] = A[i * nv + jv] ? mk_add(A[i * nv + jv], c) : c;
			}
		tl_free(& l);
		}
	if (! ok)
		{
		for (i = 0; i < ne * nv; i++) delete(A[i]);
		for (i = 0; i < ne; i++) delete(b[i]);
		return NULL;
		}
	for (i = 0; i < ne; i++)
		{
		for (j = 0; j < nv; j++)
			if (! A[i * nv + j]) A[i * nv + j] = mk_int(0);
		rows[i] = mk_list(A + i * nv, nv);
		if (! b[i]) b[i] = mk_int(0);
		}
	m = mk_list(rows, ne);
	bv = mk_list(b, ne);
	r = mat_solve(m, bv, 1);
	delete(m);
	delete(bv);
	return r;
}

static Node * s_linsysq (Node * a[], int n, Symbol * f)	/* a linear system linsys can solve */
{
	Node * r = s_linsys(a, n, f);
	delete(r);
	return mk_bool(r != NULL, f);
}

/* ---- nonlinear systems ----
 * solve([eqs], [vars]) for a nonlinear system (inc/solve):
 *   syssol(F, V)     the solutions of the equations F = 0 (f = lhs - rhs) in V,
 *                    a list of tuples (lists in the order of V)
 *   sysstep(F, V)    the next step: one equation in one unknown; an unknown
 *                    that occurs linearly with a constant coefficient is
 *                    eliminated by substitution (sysback); two polynomial
 *                    equations by the resultant (sysext); NULL if none fits
 *   sysback, sysext  the solutions of the smaller system completed
 *   syscheck         tuples that make an equation false (numerically) removed */

static Node * sys_vars_except (Node * V, int j)
{
	Node * e[MAXDIM];
	int k, n = list_len(V), m = 0;
	for (k = 0; k < n; k++)
		if (k != j) e[m++] = tcpy(arg(deref(V), k));
	return mk_list(e, m);
}

static int free_of_vars (Node * u, Node * V)
{
	int k;
	for (k = 0; k < list_len(V); k++)
		if (contains(u, arg(deref(V), k))) return 0;
	return 1;
}

/* the resultant of f and g in y: the determinant of the Sylvester matrix */
static Node * resultant (Node * f, Node * g, Node * y)
{
	Node * cf[MAXDEG], * cg[MAXDEG], * rows[MAXDIM], * m, * r, * a[1];
	int df, dg, n, i, j;
	if (! poly_coeffs(f, y, cf, & df)) return NULL;
	if (! poly_coeffs(g, y, cg, & dg)) { for (i = 0; i <= df; i++) delete(cf[i]); return NULL; }
	n = df + dg;
	if (df < 1 || dg < 1 || n > MAXDIM)
		{
		for (i = 0; i <= df; i++) delete(cf[i]);
		for (i = 0; i <= dg; i++) delete(cg[i]);
		return NULL;
		}
	for (i = 0; i < n; i++)
		{
		Node * e[MAXDIM];
		for (j = 0; j < n; j++)
			{
			int k;
			if (i < dg) { k = df - (j - i); e[j] = (k >= 0 && k <= df) ? tcpy(cf[k]) : mk_int(0); }
			else { k = dg - (j - (i - dg)); e[j] = (k >= 0 && k <= dg) ? tcpy(cg[k]) : mk_int(0); }
			}
		rows[i] = mk_list(e, n);
		}
	for (i = 0; i <= df; i++) delete(cf[i]);
	for (i = 0; i <= dg; i++) delete(cg[i]);
	m = mk_list(rows, n);
	a[0] = m;
	r = det_impl(a, 1, NULL);
	delete(m);
	return r;
}

static Node * s_resultant (Node * a[], int n, Symbol * f)
{
	Node * p, * q, * r;
	if (n != 3) return NULL;
	p = eqnorm(a[0], a[2]);
	q = eqnorm(a[1], a[2]);
	r = resultant(p, q, a[2]);
	delete(p);
	delete(q);
	return r;
}

static Node * mk_fn (const char * f, Node * args[], int n)	/* f(args) (takes them) */
{
	Node * t = args[n - 1];
	int i;
	for (i = n - 2; i >= 0; i--) t = mknod(Terms, args[i], t);
	return mknod(Func, (Node *) getsymbol(fsym(f), t), t);
}

static Node * sysstep (Node * F, Node * V)
{
	int nf = list_len(F), nv = list_len(V), i, j, k;
	if (nf < 1 || nv < 1 || nf > MAXDIM || nv > MAXDIM) return NULL;
	if (nf == 1 && nv == 1)			/* one equation: the solver, then tuples */
		{
		Node * s[2], * t[1];
		s[0] = tcpy(arg(deref(F), 0));
		s[1] = tcpy(arg(deref(V), 0));
		t[0] = mk_fn("sol", s, 2);
		return mk_fn("systuple", t, 1);
		}
	for (i = 0; i < nf; i++)			/* linear in an unknown: substitution */
		for (j = 0; j < nv; j++)
			{
			Node * v = arg(deref(V), j), * fi = eqnorm(arg(deref(F), i), v), * c[MAXDEG];
			int deg;
			if (poly_coeffs(fi, v, c, & deg))
				{
				if (deg == 1 && free_of_vars(c[1], V) && ! is_zero_node(c[1]))
					{
					Node * expr = nice(collected(mk_neg(mk_mul(tcpy(c[0]), mk_pow(tcpy(c[1]), mk_int(-1))))));
					Node * fe[MAXDIM], * args[5], * inner[2];
					int m = 0;
					for (k = 0; k <= deg; k++) delete(c[k]);
					delete(fi);
					for (k = 0; k < nf; k++)
						if (k != i) fe[m++] = replace(arg(deref(F), k), v, expr);
					if (m == 0)			/* the other unknowns are free */
						{
						delete(expr);
						return NULL;
						}
					inner[0] = mk_list(fe, m);
					inner[1] = sys_vars_except(V, j);
					args[0] = mk_fn("syssol", inner, 2);
					args[1] = sys_vars_except(V, j);
					args[2] = tcpy(V);
					args[3] = mk_int(j);
					args[4] = expr;
					return mk_fn("sysback", args, 5);
					}
				for (k = 0; k <= deg; k++) delete(c[k]);
				}
			delete(fi);
			}
	if (nf == 2 && nv == 2)			/* two polynomial equations: the resultant in the last unknown */
		{
		Node * y = arg(deref(V), 1), * f1 = eqnorm(arg(deref(F), 0), y), * f2 = eqnorm(arg(deref(F), 1), y);
		Node * r = resultant(f1, f2, y), * args[5], * inner[2], * one[1];
		if (! r || occurs(r, arg(deref(V), 0)) == 0)
			{
			delete(r); delete(f1); delete(f2);
			return NULL;
			}
		one[0] = r;
		inner[0] = mk_list(one, 1);
		inner[1] = sys_vars_except(V, 1);
		args[0] = mk_fn("syssol", inner, 2);
		args[1] = sys_vars_except(V, 1);
		args[2] = tcpy(y);
		args[3] = f1;
		args[4] = f2;
		return mk_fn("sysext", args, 5);
		}
	return NULL;
}

static Node * s_sysstep (Node * a[], int n, Symbol * f)
{
	if (n != 2 || ! is_head(a[0], "list", -1) || ! is_head(a[1], "list", -1)) return NULL;
	return sysstep(a[0], a[1]);
}

static Node * s_sysstepq (Node * a[], int n, Symbol * f)
{
	Node * r = (n == 2 && is_head(a[0], "list", -1) && is_head(a[1], "list", -1)) ? sysstep(a[0], a[1]) : NULL;
	delete(r);
	return mk_bool(r != NULL, f);
}

static Node * s_systuple (Node * a[], int n, Symbol * f)	/* [r1, r2] -> [[r1], [r2]] */
{
	Node * e[64];
	int k, len;
	if (n != 1) return NULL;
	if (is_nil(a[0])) return tcpy(a[0]);
	if (! is_head(a[0], "list", -1)) return NULL;
	len = list_len(a[0]);
	if (len > 64) len = 64;
	for (k = 0; k < len; k++)
		{
		Node * v = tcpy(arg(deref(a[0]), k));
		e[k] = mk_list(& v, 1);
		}
	return mk_list(e, len);
}

static Node * subst_tuple (Node * u, Node * vars, Node * tuple)	/* u with vars -> values */
{
	Node * r = tcpy(u);
	int k;
	for (k = 0; k < list_len(vars); k++)
		{
		Node * t = replace(r, arg(deref(vars), k), arg(deref(tuple), k));
		delete(r);
		r = t;
		}
	return r;
}

/* sysback(tuples of Vrest, Vrest, V, j, expr): the value of the j-th unknown
 * inserted into each tuple */
static Node * s_sysback (Node * a[], int n, Symbol * f)
{
	Node * e[64];
	double jv;
	int k, len, j, i, nv;
	if (n != 5 || ! is_num(a[3], & jv)) return NULL;
	if (is_nil(a[0])) return tcpy(a[0]);
	if (! is_head(a[0], "list", -1)) return NULL;
	j = (int) jv;
	nv = list_len(a[2]);
	len = list_len(a[0]);
	if (len > 64) len = 64;
	for (k = 0; k < len; k++)
		if (! is_head(arg(deref(a[0]), k), "list", -1)) return NULL;
	for (k = 0; k < len; k++)
		{
		Node * t = arg(deref(a[0]), k), * vals[MAXDIM];
		int m = 0;
		for (i = 0; i < nv; i++)
			vals[i] = (i == j) ? nice(subst_tuple(a[4], a[1], t)) : tcpy(arg(deref(t), m++));
		e[k] = mk_list(vals, nv);
		}
	return mk_list(e, len);
}

/* sysext(tuples of x, [x], y, f1, f2): for each tuple the solutions y
 * of f1 = 0 (the solver) that also make f2 zero: sysy terms joined by union */
static Node * s_sysext (Node * a[], int n, Symbol * f)
{
	Node * r = NULL;
	int k, len;
	if (n != 5) return NULL;
	if (is_nil(a[0])) return tcpy(a[0]);
	if (! is_head(a[0], "list", -1)) return NULL;
	len = list_len(a[0]);
	for (k = len - 1; k >= 0; k--)
		{
		Node * t = arg(deref(a[0]), k), * s[2], * args[4], * term;
		s[0] = subst_tuple(a[3], a[1], t);
		s[1] = tcpy(a[2]);
		args[0] = tcpy(t);
		args[1] = mk_fn("sol", s, 2);
		args[2] = subst_tuple(a[4], a[1], t);
		args[3] = tcpy(a[2]);
		term = mk_fn("sysy", args, 4);
		r = r ? mk_f2("union", term, r) : term;
		}
	return r;
}

static int zero_value (Node * u)	/* 1: zero, 0: not zero, -1: unknown */
{
	double v;
	Node * c;
	if (num_value_r(u, & v)) return isfinite(v) && fabs(v) < 1e-7;
	c = collected(tcpy(u));
	if (is_num(c, & v)) { delete(c); return fabs(v) < 1e-9; }
	delete(c);
	return -1;
}

/* sysy(tuple, [y1, ..], f2, y): tuple ++ y_k for the y_k with f2 = 0 */
static Node * s_sysy (Node * a[], int n, Symbol * f)
{
	Node * e[64];
	int k, len, ne = 0, i;
	if (n != 4) return NULL;
	if (is_nil(a[1])) return tcpy(a[1]);
	if (! is_head(a[1], "list", -1) || ! is_head(a[0], "list", -1)) return NULL;
	len = list_len(a[1]);
	for (k = 0; k < len && ne < 64; k++)
		{
		Node * yk = arg(deref(a[1]), k), * v = replace(a[2], a[3], yk), * vals[MAXDIM];
		int z = zero_value(v), m = list_len(a[0]);
		delete(v);
		if (z == 0) continue;
		for (i = 0; i < m; i++) vals[i] = tcpy(arg(deref(a[0]), i));
		vals[m] = tcpy(yk);
		e[ne++] = mk_list(vals, m + 1);
		}
	return mk_list(e, ne);
}

/* syscheck(tuples, F, V): tuples that make an equation false removed, no duplicates */
static Node * s_syscheck (Node * a[], int n, Symbol * f)
{
	Node * e[64];
	int k, len, ne = 0, i, j;
	if (n != 3) return NULL;
	if (is_nil(a[0])) return tcpy(a[0]);
	if (! is_head(a[0], "list", -1)) return NULL;
	len = list_len(a[0]);
	for (k = 0; k < len && ne < 64; k++)
		{
		Node * t = arg(deref(a[0]), k);
		int keep = is_head(t, "list", -1);
		for (i = 0; i < list_len(a[1]) && keep; i++)
			{
			Node * v = subst_tuple(arg(deref(a[1]), i), a[2], t);
			if (zero_value(v) == 0) keep = 0;
			delete(v);
			}
		for (j = 0; j < ne && keep; j++)
			if (eq_terms(e[j], t)) keep = 0;
		if (keep) e[ne++] = tcpy(t);
		}
	return mk_list(e, ne);
}

/* sysnorm([lhs1 == rhs1, ..]): [lhs1 - rhs1, ..] */
static Node * s_sysnorm (Node * a[], int n, Symbol * f)
{
	Node * e[MAXDIM];
	int k, len;
	if (n != 1 || ! is_head(a[0], "list", -1)) return NULL;
	len = list_len(a[0]);
	if (len > MAXDIM) return NULL;
	for (k = 0; k < len; k++)
		{
		Node * eq = deref(arg(deref(a[0]), k));
		if (! is_head(eq, "==", 2)) { while (--k >= 0) delete(e[k]); return NULL; }
		e[k] = mk_add(tcpy(arg(eq, 0)), mk_neg(tcpy(arg(eq, 1))));
		}
	return mk_list(e, len);
}
