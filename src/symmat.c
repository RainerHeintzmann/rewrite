/*
 *	symmat.c (2026)
 *
 *	Symbolic matrices on lists, included by symfkt.c (it uses its static
 *	helpers). A matrix is a list of rows, list(list(a,b),list(c,d)), a
 *	vector a list (inc/list, inc/linalg):
 *
 *	    transpose(m), dot(a,b), identity(n), det(m), linsolve(m,b), inverse(m)
 *
 *	det, linsolve and inverse use Bareiss' fraction-free elimination on
 *	sparse polynomials in the atoms of the entries (MPoly): every division
 *	in it is exact, so no fractions of polynomials occur until the end.
 *	An atom is any factor that is no number and no natural power, so
 *	sin(x), a^(-1) and 2^(1/2) are atoms too; the identities of the
 *	elimination hold for independent atoms and thus for these as well.
 */

/* ---- sparse polynomials: sums of monomials c * b1^e1 * ... (Mono) ----
 * The monomials own their bases (copies). Natural exponents only. */

typedef struct { Mono * m; int n, cap; } MPoly;

static void mono_free (Mono * m)
{
	int i;
	for (i = 0; i < m->nf; i++) delete(m->f[i].base);
	free(m->f);
	m->f = NULL;
	m->nf = m->cap = 0;
}

static void mp_free (MPoly * p)
{
	int i;
	for (i = 0; i < p->n; i++) mono_free(& p->m[i]);
	free(p->m);
	p->m = NULL;
	p->n = p->cap = 0;
}

static void mono_sort (Mono * m)	/* bases in the order of tcmp, no x^0 */
{
	int i, j, k = 0;
	mono_imag(m);			/* im^2 = -1 */
	for (i = 0; i < m->nf; i++)
		if (m->f[i].e != 0) m->f[k++] = m->f[i];
		else delete(m->f[i].base);
	m->nf = k;
	for (i = 1; i < m->nf; i++)
		for (j = i; j > 0 && tcmp(m->f[j-1].base, m->f[j].base) > 0; j--)
			{ Fac h = m->f[j]; m->f[j] = m->f[j-1]; m->f[j-1] = h; }
}

static void mono_put (Mono * m, Node * base, double e)	/* takes base */
{
	int i;
	for (i = 0; i < m->nf; i++)
		if (tequal(m->f[i].base, base)) { m->f[i].e += e; delete(base); return; }
	mono_addfac(m, base, e, 1);
}

static Mono mono_mul (Mono * a, Mono * b)
{
	Mono r = { a->c * b->c, NULL, 0, 0, a->exact && b->exact };
	int i;
	for (i = 0; i < a->nf; i++) mono_put(& r, tcpy(a->f[i].base), a->f[i].e);
	for (i = 0; i < b->nf; i++) mono_put(& r, tcpy(b->f[i].base), b->f[i].e);
	mono_sort(& r);
	return r;
}

/* lexicographic order of the exponents, the bases ordered by tcmp */
static int mono_cmp (Mono * a, Mono * b)
{
	int i = 0, j = 0, c;
	while (i < a->nf || j < b->nf)
		{
		if (j >= b->nf) return 1;
		if (i >= a->nf) return -1;
		c = tequal(a->f[i].base, b->f[j].base) ? 0 : tcmp(a->f[i].base, b->f[j].base);
		if (c == 0)
			{
			if (a->f[i].e != b->f[j].e) return a->f[i].e > b->f[j].e ? 1 : -1;
			i++; j++;
			}
		else
			return c < 0 ? 1 : -1;	/* a has the earlier base */
		}
	return 0;
}

/* p += m (takes m); like monomials are added, cancelled ones dropped */
static void mp_add_mono (MPoly * p, Mono m)
{
	int i;
	for (i = 0; i < p->n; i++)
		if (mono_like(& p->m[i], & m))
			{
			double c = p->m[i].c + m.c, mag = fabs(p->m[i].c) > fabs(m.c) ? fabs(p->m[i].c) : fabs(m.c);
			int exact = p->m[i].exact && m.exact;
			mono_free(& m);
			if (fabs(c) <= (exact ? 0 : 1e-12) * mag)
				{
				mono_free(& p->m[i]);
				p->m[i] = p->m[--p->n];
				}
			else
				{
				p->m[i].c = c;
				p->m[i].exact = exact;
				}
			return;
			}
	if (m.c == 0) { mono_free(& m); return; }
	if (p->n == p->cap)
		{
		p->cap = p->cap ? 2 * p->cap : 8;
		p->m = (Mono *) realloc(p->m, p->cap * sizeof(Mono));
		if (! p->m) fatal("symmat : no room");
		}
	p->m[p->n++] = m;
}

static Mono mono_dup (Mono * a)
{
	Mono one = { 1.0, NULL, 0, 0, 1 };
	return mono_mul(a, & one);
}

static MPoly mp_const (double c)
{
	MPoly p = { NULL, 0, 0 };
	Mono m = { c, NULL, 0, 0, 1 };
	mp_add_mono(& p, m);
	return p;
}

static MPoly mp_dup (MPoly * a)
{
	MPoly p = { NULL, 0, 0 };
	int i;
	for (i = 0; i < a->n; i++) mp_add_mono(& p, mono_dup(& a->m[i]));
	return p;
}

static void mp_addmul (MPoly * s, MPoly * a, MPoly * b, double sign)	/* s += sign*a*b */
{
	int i, j;
	for (i = 0; i < a->n; i++)
		for (j = 0; j < b->n; j++)
			{
			Mono m = mono_mul(& a->m[i], & b->m[j]);
			m.c *= sign;
			mp_add_mono(s, m);
			}
}

/* a*b - c*d */
static MPoly mp_cross (MPoly * a, MPoly * b, MPoly * c, MPoly * d)
{
	MPoly p = { NULL, 0, 0 };
	mp_addmul(& p, a, b, 1);
	mp_addmul(& p, c, d, -1);
	return p;
}

static int mp_lead (MPoly * p)		/* index of the leading monomial */
{
	int i, k = 0;
	for (i = 1; i < p->n; i++)
		if (mono_cmp(& p->m[i], & p->m[k]) > 0) k = i;
	return k;
}

/* q = p / d if the division is exact; 0 if it is not */
static int mp_div (MPoly * p, MPoly * d, MPoly * q)
{
	MPoly r = mp_dup(p);
	Mono * ld;
	int steps = 0, i, j;
	q->m = NULL; q->n = q->cap = 0;
	if (d->n == 0) { mp_free(& r); return 0; }
	ld = & d->m[mp_lead(d)];
	while (r.n > 0)
		{
		Mono * lr = & r.m[mp_lead(& r)];
		Mono t = { lr->c / ld->c, NULL, 0, 0, lr->exact && ld->exact };
		for (i = 0; i < lr->nf; i++) mono_put(& t, tcpy(lr->f[i].base), lr->f[i].e);
		for (j = 0; j < ld->nf; j++) mono_put(& t, tcpy(ld->f[j].base), - ld->f[j].e);
		mono_sort(& t);
		for (i = 0; i < t.nf; i++)
			if (t.f[i].e < 0) break;
		if (i < t.nf || ++steps > 100000)	/* the leading term does not divide */
			{
			mono_free(& t);
			mp_free(& r);
			mp_free(q);
			return 0;
			}
		for (j = 0; j < d->n; j++)		/* r -= t*d */
			{
			Mono m = mono_mul(& t, & d->m[j]);
			m.c = -m.c;
			mp_add_mono(& r, m);
			}
		mp_add_mono(q, t);
		}
	mp_free(& r);
	return 1;
}

/* the polynomial of a term; natural powers of a base are kept as powers,
 * everything else is an atom */
static MPoly mp_from (Node * t)
{
	MPoly p = { NULL, 0, 0 };
	TList l = {0};
	int i, k;
	expand_to(t, & l);
	for (i = 0; i < l.n; i++)
		{
		Mono m = { 1.0, NULL, 0, 0, 1 }, o = { 1.0, NULL, 0, 0, 1 };
		mono_flatten(l.t[i], & m);
		mono_normalize(& m);
		o.c = m.c;
		o.exact = m.exact;
		for (k = 0; k < m.nf; k++)
			{
			double e = m.f[k].e;
			if (e > 0 && e == floor(e))
				mono_put(& o, tcpy(m.f[k].base), e);
			else				/* a^(-1), 2^(1/2): an atom */
				mono_put(& o, mk_pow(tcpy(m.f[k].base), mk_num_ex(e, m.f[k].exact)), 1);
			}
		free(m.f);			/* the bases belong to the summands */
		mono_sort(& o);
		mp_add_mono(& p, o);
		}
	tl_free(& l);
	return p;
}

static Node * mp_term (MPoly * p)
{
	TList l = {0};
	int i;
	for (i = 0; i < p->n; i++) tl_add(& l, mono_build(& p->m[i]));
	return tl_collect(& l);
}

static Node * nice (Node * t)		/* a result entry in normal form (takes t) */
{
	Node * r = s_normform(& t, 1, NULL);
	delete(t);
	return r;
}

/* ---- matrices as arrays of MPoly ---- */

#define MAXDIM 40

static int mat_dims (Node * m, int * rows, int * cols)	/* a list of lists of equal length */
{
	int i;
	m = deref(m);
	if (! is_head(m, "list", -1)) return 0;
	* rows = list_len(m);
	* cols = -1;
	for (i = 0; i < * rows; i++)
		{
		Node * r = deref(arg(m, i));
		if (! is_head(r, "list", -1)) return 0;
		if (* cols < 0) * cols = list_len(r);
		else if (list_len(r) != * cols) return 0;
		}
	return * rows > 0 && * cols > 0;
}

static Node * mat_entry (Node * m, int i, int j)
{
	return arg(deref(arg(deref(m), i)), j);
}

static Node * mat_build (Node * e[], int rows, int cols)	/* takes the entries */
{
	Node * r[MAXDIM];
	int i;
	for (i = 0; i < rows; i++) r[i] = mk_list(e + i * cols, cols);
	return mk_list(r, rows);
}

static Node * transpose_impl (Node * a[], int n, Symbol * f)
{
	Node * e[MAXDIM * MAXDIM];
	int rows, cols, i, j;
	if (n != 1 || ! mat_dims(a[0], & rows, & cols) || rows > MAXDIM || cols > MAXDIM) return NULL;
	for (i = 0; i < cols; i++)
		for (j = 0; j < rows; j++)
			e[i * rows + j] = tcpy(mat_entry(a[0], j, i));
	return mat_build(e, cols, rows);
}

static Node * s_identity (Node * a[], int n, Symbol * f)
{
	Node * e[MAXDIM * MAXDIM];
	double v;
	int k, i, j;
	if (n != 1 || ! is_num(a[0], & v) || v != floor(v) || v < 1 || v > MAXDIM) return NULL;
	k = (int) v;
	for (i = 0; i < k; i++)
		for (j = 0; j < k; j++)
			e[i * k + j] = mk_int(i == j);
	return mat_build(e, k, k);
}

/* sum of a[i]*b[i], like terms collected but sums in the factors not
 * multiplied out (as Mathematica's Dot) */
static Node * dot_sum (Node * a[], Node * b[], int n)
{
	TList l = {0};
	int i;
	for (i = 0; i < n; i++)
		{
		Node * p = mk_mul(tcpy(a[i]), tcpy(b[i]));
		summands_to(p, & l, 0);
		delete(p);
		}
	return nice(tl_collect(& l));
}

static Node * dot_impl (Node * a[], int n, Symbol * f)
{
	Node * u[MAXDIM], * v[MAXDIM], * e[MAXDIM * MAXDIM], * r;
	int ra, ca, rb, cb, ma, mb, i, j, k;
	if (n != 2 || ! is_head(a[0], "list", -1) || ! is_head(a[1], "list", -1)) return NULL;
	ma = mat_dims(a[0], & ra, & ca);
	mb = mat_dims(a[1], & rb, & cb);
	if (! ma) { ra = 1; ca = list_len(a[0]); }	/* a vector */
	if (! mb) { rb = list_len(a[1]); cb = 1; }
	if (ca != rb || ra > MAXDIM || ca > MAXDIM || cb > MAXDIM) return NULL;
	for (i = 0; i < ra; i++)
		for (j = 0; j < cb; j++)
			{
			for (k = 0; k < ca; k++)
				{
				u[k] = ma ? mat_entry(a[0], i, k) : arg(deref(a[0]), k);
				v[k] = mb ? mat_entry(a[1], k, j) : arg(deref(a[1]), k);
				}
			e[i * cb + j] = dot_sum(u, v, ca);
			}
	if (! ma && ! mb) return e[0];			/* vector . vector */
	if (! ma || ! mb)				/* a vector */
		return mk_list(e, ma ? ra : cb);
	r = mat_build(e, ra, cb);
	return r;
}

/* Bareiss' elimination of the rows x cols matrix m (rows <= cols) in place:
 * afterwards m is upper triangular and m[rows-1][rows-1] is +-det of the
 * left square part; *sign the sign of the row swaps. 0: singular, -1: a
 * division was not exact (rounding of real numbers) */
static int bareiss (MPoly * m, int rows, int cols, int * sign)
{
	MPoly prev = mp_const(1);
	int k, i, j;
	* sign = 1;
	for (k = 0; k < rows; k++)
		{
		if (m[k * cols + k].n == 0)		/* pivot 0: swap with a row below */
			{
			for (i = k + 1; i < rows && m[i * cols + k].n == 0; i++)
				;
			if (i == rows) { mp_free(& prev); return 0; }
			for (j = 0; j < cols; j++)
				{ MPoly h = m[k * cols + j]; m[k * cols + j] = m[i * cols + j]; m[i * cols + j] = h; }
			* sign = - * sign;
			}
		for (i = k + 1; i < rows; i++)
			{
			for (j = k + 1; j < cols; j++)
				{
				MPoly c = mp_cross(& m[k * cols + k], & m[i * cols + j], & m[i * cols + k], & m[k * cols + j]), q;
				if (! mp_div(& c, & prev, & q)) { mp_free(& c); mp_free(& prev); return -1; }
				mp_free(& c);
				mp_free(& m[i * cols + j]);
				m[i * cols + j] = q;
				}
			mp_free(& m[i * cols + k]);	/* below the pivot: 0 */
			}
		mp_free(& prev);
		prev = mp_dup(& m[k * cols + k]);
		}
	mp_free(& prev);
	return 1;
}

static MPoly * mat_poly (Node * m, int rows, int cols, Node * b, int bcols)
{
	MPoly * p = (MPoly *) calloc(rows * (cols + bcols), sizeof(MPoly));
	int i, j, w = cols + bcols;
	if (! p) fatal("symmat : no room");
	for (i = 0; i < rows; i++)
		{
		for (j = 0; j < cols; j++)
			p[i * w + j] = mp_from(mat_entry(m, i, j));
		for (j = 0; j < bcols; j++)		/* b: a vector or a matrix */
			p[i * w + cols + j] = mp_from(bcols == 1 && ! is_head(arg(deref(b), i), "list", -1)
			                              ? arg(deref(b), i) : mat_entry(b, i, j));
		}
	return p;
}

static void mat_free (MPoly * p, int n)
{
	int i;
	for (i = 0; i < n; i++) mp_free(& p[i]);
	free(p);
}

static Node * det_impl (Node * a[], int n, Symbol * f)
{
	MPoly * m;
	Node * r = NULL;
	int rows, cols, sign, ok;
	if (n != 1 || ! mat_dims(a[0], & rows, & cols) || rows != cols || rows > MAXDIM) return NULL;
	m = mat_poly(a[0], rows, cols, NULL, 0);
	ok = bareiss(m, rows, cols, & sign);
	if (ok == 0) r = mk_int(0);
	else if (ok > 0)
		{
		r = mp_term(& m[rows * cols - 1]);
		if (sign < 0) r = mk_neg(r);
		r = nice(r);
		}
	mat_free(m, rows * cols);
	return r;
}

/* the monomial gcd of p and d (smallest exponents of the common bases),
 * divided out of both */
static void mp_cancel_monomial (MPoly * p, MPoly * d)
{
	MPoly * ps[2] = { p, d };
	Mono * g;
	int i, j, k, s;
	if (p->n == 0 || d->n == 0) return;
	g = & d->m[0];
	for (k = 0; k < g->nf; k++)
		{
		double e = g->f[k].e;
		for (s = 0; s < 2 && e > 0; s++)
			for (i = 0; i < ps[s]->n && e > 0; i++)
				{
				Mono * m = & ps[s]->m[i];
				double em = 0;
				for (j = 0; j < m->nf; j++)
					if (tequal(m->f[j].base, g->f[k].base)) em = m->f[j].e;
				if (em < e) e = em;
				}
		if (e <= 0) continue;
		{
		Node * base = tcpy(g->f[k].base);
		for (s = 0; s < 2; s++)
			for (i = 0; i < ps[s]->n; i++)
				{
				mono_put(& ps[s]->m[i], tcpy(base), - e);
				mono_sort(& ps[s]->m[i]);
				}
		delete(base);
		}
		k = -1;			/* g has changed: again from the start */
		g = & d->m[0];
		}
}

/* ---- gcd of two polynomials in the same single atom v (Euclid) ---- */

#define MAXPDEG 64

static Node * mp_single_atom (MPoly * a, MPoly * b)
{
	MPoly * ps[2] = { a, b };
	Node * v = NULL;
	int s, i;
	for (s = 0; s < 2; s++)
		for (i = 0; i < ps[s]->n; i++)
			{
			Mono * m = & ps[s]->m[i];
			if (m->nf == 0) continue;
			if (m->nf > 1 || m->f[0].e > MAXPDEG) return NULL;
			if (! v) v = m->f[0].base;
			else if (! tequal(v, m->f[0].base)) return NULL;
			}
	return v;
}

static int mp_coeffs (MPoly * p, double c[])		/* degree, or -1 for 0 */
{
	int i, d = -1;
	for (i = 0; i <= MAXPDEG; i++) c[i] = 0;
	for (i = 0; i < p->n; i++)
		{
		int k = p->m[i].nf ? (int) p->m[i].f[0].e : 0;
		c[k] += p->m[i].c;
		if (k > d) d = k;
		}
	return d;
}

static int poly_trim (double c[], int d)	/* drop the leading zeros (rounding) */
{
	double mx = 0;
	int i;
	for (i = 0; i <= d; i++) if (fabs(c[i]) > mx) mx = fabs(c[i]);
	while (d >= 0 && fabs(c[d]) <= 1e-10 * mx) d--;
	return d;
}

/* the monic gcd of a and b in v as an MPoly; NULL-size if it is 1 */
static MPoly mp_gcd1 (MPoly * a, MPoly * b, Node * v, int exact)
{
	double x[MAXPDEG + 1], y[MAXPDEG + 1], * p = x, * q = y, * h;
	MPoly g = { NULL, 0, 0 };
	int dp = mp_coeffs(a, x), dq = mp_coeffs(b, y), i, k;
	if (dp < dq) { h = p; p = q; q = h; k = dp; dp = dq; dq = k; }
	dq = poly_trim(q, dq);
	while (dq >= 0)				/* p mod q */
		{
		dp = poly_trim(p, dp);
		while (dp >= dq)
			{
			double f = p[dp] / q[dq];
			for (i = 0; i <= dq; i++) p[dp - dq + i] -= f * q[i];
			p[dp] = 0;
			dp = poly_trim(p, dp - 1);
			}
		h = p; p = q; q = h; k = dp; dp = dq; dq = k;
		}
	if (dp < 1) return g;			/* gcd 1 */
	for (i = 0; i <= dp; i++)
		{
		Mono m = { p[i] / p[dp], NULL, 0, 0, exact };
		if (m.c == 0) continue;
		if (i > 0) mono_put(& m, tcpy(v), i);
		mp_add_mono(& g, m);
		}
	return g;
}

static double dgcd (double a, double b)
{
	a = fabs(a); b = fabs(b);
	while (b > 0.5) { double t = fmod(a, b); a = b; b = t; }
	return a;
}

/* the common factors of nu and de divided out: a polynomial gcd in a
 * single atom, the integer content; the denominator's leading coefficient
 * positive */
static void mp_cancel (MPoly * nu, MPoly * de)
{
	MPoly * ps[2] = { nu, de };
	Node * v = mp_single_atom(nu, de);
	double g = 0;
	int s, i, exact = 1;
	for (s = 0; s < 2; s++)
		for (i = 0; i < ps[s]->n; i++) exact &= ps[s]->m[i].exact;
	if (v && nu->n > 0)
		{
		MPoly gp = mp_gcd1(nu, de, v, exact), q1, q2;
		if (gp.n > 0 && mp_div(nu, & gp, & q1))
			{
			if (mp_div(de, & gp, & q2))
				{
				mp_free(nu); * nu = q1;
				mp_free(de); * de = q2;
				}
			else
				mp_free(& q1);
			}
		mp_free(& gp);
		}
	for (s = 0; s < 2 && g >= 0; s++)		/* integer content */
		for (i = 0; i < ps[s]->n; i++)
			{
			double c = ps[s]->m[i].c;
			if (! ps[s]->m[i].exact || c != floor(c) || fabs(c) > 1e15) { g = -1; break; }
			g = dgcd(g, c);
			}
	if (g <= 0) g = 1;
	if (de->n > 0 && de->m[mp_lead(de)].c < 0) g = -g;
	if (g != 1)
		for (s = 0; s < 2; s++)
			for (i = 0; i < ps[s]->n; i++)
				ps[s]->m[i].c /= g;
}

/* x = num/den as a term: exact quotient, else with the common factors
 * (polynomial gcd in one atom, monomial, integer content) divided out */
static Node * mp_quotient (MPoly * num, MPoly * den)
{
	MPoly q, nu = mp_dup(num), de = mp_dup(den);
	Node * r;
	if (mp_div(& nu, & de, & q))
		{
		r = nice(mp_term(& q));
		mp_free(& q);
		}
	else
		{
		mp_cancel_monomial(& nu, & de);
		mp_cancel(& nu, & de);
		if (de.n == 1 && de.m[0].nf == 0)	/* a number */
			{
			int i;
			for (i = 0; i < nu.n; i++) nu.m[i].c /= de.m[0].c, nu.m[i].exact &= de.m[0].exact;
			r = nice(mp_term(& nu));
			}
		else				/* (n*p - b*q)/(a*n - b*g), -(b/(a*n - b*g)) */
			{
			Node * t = nice(mp_term(& nu));
			if (is_head(t, "-", 1))
				{
				Node * u = tcpy(arg(t, 0));
				delete(t);
				r = mk_f1("-", mk_f2("/", u, nice(mp_term(& de))));
				}
			else
				r = mk_f2("/", t, nice(mp_term(& de)));
			}
		}
	mp_free(& nu);
	mp_free(& de);
	return r;
}

/* solution of m.x = b for a square m, b a vector or a matrix (several
 * right-hand sides); NULL if m is singular */
static Node * mat_solve (Node * m, Node * b, int bvector)
{
	MPoly * p, * x;
	Node * e[MAXDIM * MAXDIM], * r;
	int rows, cols, bc, brows, bcols, w, sign, i, j, k, ok;
	if (! mat_dims(m, & rows, & cols) || rows != cols || rows > MAXDIM) return NULL;
	if (bvector)
		{
		if (! is_head(b, "list", -1) || list_len(b) != rows) return NULL;
		bc = 1;
		}
	else
		{
		if (! mat_dims(b, & brows, & bcols) || brows != rows || bcols > MAXDIM) return NULL;
		bc = bcols;
		}
	w = cols + bc;
	p = mat_poly(m, rows, cols, b, bc);
	ok = bareiss(p, rows, w, & sign);
	if (ok <= 0) { mat_free(p, rows * w); return NULL; }
	/* fraction-free back substitution: x_i = X_i / D, D = U[n-1][n-1],
	 * X_i = (D*U[i][rhs] - sum_j>i U[i][j]*X_j) / U[i][i], exact */
	x = (MPoly *) calloc(rows * bc, sizeof(MPoly));
	if (! x) fatal("symmat : no room");
	for (k = 0; k < bc && ok > 0; k++)
		for (i = rows - 1; i >= 0 && ok > 0; i--)
			{
			MPoly s = { NULL, 0, 0 };
			mp_addmul(& s, & p[(rows - 1) * w + rows - 1], & p[i * w + cols + k], 1);
			for (j = i + 1; j < rows; j++)
				mp_addmul(& s, & p[i * w + j], & x[j * bc + k], -1);
			if (! mp_div(& s, & p[i * w + i], & x[i * bc + k])) ok = -1;
			mp_free(& s);
			}
	r = NULL;
	if (ok > 0)
		{
		MPoly * d = & p[(rows - 1) * w + rows - 1];
		for (i = 0; i < rows; i++)
			for (k = 0; k < bc; k++)
				e[i * bc + k] = mp_quotient(& x[i * bc + k], d);
		r = bvector ? mk_list(e, rows) : mat_build(e, rows, bc);
		}
	mat_free(x, rows * bc);
	mat_free(p, rows * w);
	return r;
}

static Node * linsolve_impl (Node * a[], int n, Symbol * f)
{
	int r, c;
	if (n != 2) return NULL;
	return mat_solve(a[0], a[1], ! mat_dims(a[1], & r, & c));
}

static Node * inverse_impl (Node * a[], int n, Symbol * f)
{
	Node * id, * r, * k;
	int rows, cols;
	if (n != 1 || ! mat_dims(a[0], & rows, & cols) || rows != cols || rows > MAXDIM) return NULL;
	k = mk_int(rows);
	id = s_identity(& k, 1, f);
	delete(k);
	r = mat_solve(a[0], id, 0);
	delete(id);
	return r;
}

/* ---- thread(u): arithmetic on lists element by element (Listable) ----
 * list(1,2) + list(a,b) = list(1+a, 2+b), x*list(a,b) = list(x*a, x*b),
 * sin(list(a,b)) = list(sin(a), sin(b)); nested lists (matrices) too.
 * Symbolic C functions (det, dot, length, ...) are not threaded. */

static int has_list (Node * u)
{
	int k, n;
	u = deref(u);
	if (! u || u->type != Func) return 0;
	if (is_head(u, "list", -1)) return 1;
	n = term_nargs(u);
	for (k = 0; k < n; k++)
		if (has_list(arg(u, k))) return 1;
	return 0;
}

static Node * thread (Node * u)
{
	Node * t[MAXDIM], * e[MAXDIM], * args, * r;
	int k, n, len = -1, i;
	u = deref(u);
	if (! u || u->type != Func || ! has_list(u)) return tcpy(u);
	n = term_nargs(u);
	if (n > MAXDIM) return tcpy(u);
	for (k = 0; k < n; k++) t[k] = thread(arg(u, k));
	if (! is_head(u, "list", -1) && ! builtin(TERM_HEAD(u)))
		for (k = 0; k < n; k++)
			if (is_head(t[k], "list", -1))
				{
				int l = list_len(t[k]);
				if (len >= 0 && l != len) { len = -2; break; }
				len = l;
				}
	if (len > 0 && len <= MAXDIM)		/* f(.., list(a1..an), ..) = list(f(.., ai, ..)) */
		{
		for (i = 0; i < len; i++)
			{
			Node * c;
			args = NULL;
			for (k = n - 1; k >= 0; k--)
				{
				c = is_head(t[k], "list", -1) ? tcpy(arg(t[k], i)) : tcpy(t[k]);
				args = args ? mknod(Terms, c, args) : c;
				}
			if (n == 2 && (is_head(u, "*", 2) || is_head(u, "+", 2)))	/* 1*x = x, 0+x = x */
				{
				Node * x0 = tcpy(args->l), * x1 = tcpy(args->r);
				delete(args);
				c = is_head(u, "*", 2) ? mk_mul(x0, x1) : mk_add(x0, x1);
				}
			else
				c = mknod(Func, u->l, args);
			e[i] = thread(c);
			delete(c);
			}
		r = mk_list(e, len);
		}
	else
		{
		args = NULL;
		for (k = n - 1; k >= 0; k--)
			args = args ? mknod(Terms, tcpy(t[k]), args) : tcpy(t[k]);
		r = mknod(Func, u->l, args);
		}
	for (k = 0; k < n; k++) delete(t[k]);
	return r;
}

static Node * s_thread (Node * a[], int n, Symbol * f)
{
	if (n != 1) return NULL;
	return thread(a[0]);
}

static Node * s_threadq (Node * a[], int n, Symbol * f)	/* thread(u) would change u */
{
	Node * u;
	int k, m;
	if (n != 1) return NULL;
	u = deref(a[0]);
	if (! u || u->type != Func || is_head(u, "list", -1) || builtin(TERM_HEAD(u)))
		return mk_bool(0, f);
	m = term_nargs(u);
	for (k = 0; k < m; k++)
		if (is_head(arg(u, k), "list", -1)) return mk_bool(1, f);
	return mk_bool(0, f);
}

/* the matrix functions thread their arguments first: det(m - x*identity(2)) */
typedef Node * (* sfn) (Node * a[], int n, Symbol * f);

static Node * with_thread (sfn fn, Node * a[], int n, Symbol * f)
{
	Node * b[4], * own[4], * r;
	int i;
	if (n > 4) return fn(a, n, f);
	for (i = 0; i < n; i++)
		{
		own[i] = NULL;
		b[i] = a[i];
		if (! is_head(a[i], "list", -1) && has_list(a[i]))
			b[i] = own[i] = thread(a[i]);
		}
	r = fn(b, n, f);
	for (i = 0; i < n; i++) delete(own[i]);
	return r;
}

static Node * s_transpose (Node * a[], int n, Symbol * f) { return with_thread(transpose_impl, a, n, f); }
static Node * s_dot (Node * a[], int n, Symbol * f) { return with_thread(dot_impl, a, n, f); }
static Node * s_det (Node * a[], int n, Symbol * f) { return with_thread(det_impl, a, n, f); }
static Node * s_linsolve (Node * a[], int n, Symbol * f) { return with_thread(linsolve_impl, a, n, f); }
static Node * s_inverse (Node * a[], int n, Symbol * f) { return with_thread(inverse_impl, a, n, f); }
