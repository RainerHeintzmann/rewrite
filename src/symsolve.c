/*
 *	symsolve.c (2026)
 *
 *	C helpers of the equation solver inc/solve, included by symfkt.c after
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

/* ---- cancel(u): u as N/D over a common denominator, the polynomial gcd
 * of N and D cancelled (symmat.c: mp_gcd) ---- */
static Node * s_cancel (Node * a[], int n, Symbol * f)
{
	Node * d, * nu = NULL;
	MPoly pn, pd;
	if (n != 1) return NULL;
	nu = eqnorm_den(a[0], NULL, & d);
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
	if (n != 2) return NULL;
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
	for (k = 0; k <= deg; k++)
		if (! is_num(c[k], & cv[k]) || ! is_exact(c[k]) || cv[k] != floor(cv[k]) || fabs(cv[k]) > 1e9)
			return 0;
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
	return 0;
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

/* isoeach(g, list(r1,..,rn), x) = union(iso(g,r1,x), union(iso(g,r2,x), ..)):
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

/* ---- linsys: a system of linear equations, solve(list(eqs), list(vars)) ----
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
