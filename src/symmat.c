/*
 *	symmat.c (2026)
 *
 *	Symbolic matrices on lists, included by symfn.c (it uses its static
 *	helpers). A matrix is a list of rows, [[a,b],[c,d]], a vector a
 *	list [a,b] (inc/list, inc/linalg):
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
	Node * r;
	t = tcalc(t);			/* exact roots and numbers first: 12^(1/2) = 2*3^(1/2) */
	r = s_normform(& t, 1, NULL);
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
/* ---- gcd of polynomials in several atoms ----
 * Euclid's algorithm with primitive pseudo-remainders, recursive in the
 * atoms: as a polynomial in a main atom v, the gcd is the gcd of the
 * contents (the gcds of the coefficients, polynomials in the other atoms)
 * times the gcd of the primitive parts. Exact coefficients only. */

static int mp_is_const (MPoly * p)
{
	int i;
	for (i = 0; i < p->n; i++)
		if (p->m[i].nf > 0) return 0;
	return 1;
}

static int mp_deg (MPoly * p, Node * v)		/* degree in v; -1 for 0 */
{
	int i, j, d = p->n ? 0 : -1;
	for (i = 0; i < p->n; i++)
		for (j = 0; j < p->m[i].nf; j++)
			if (tequal(p->m[i].f[j].base, v) && p->m[i].f[j].e > d) d = (int) p->m[i].f[j].e;
	return d;
}

/* the coefficient of v^k (a polynomial without v) */
static MPoly mp_coef (MPoly * p, Node * v, int k)
{
	MPoly r = { NULL, 0, 0 };
	int i, j;
	for (i = 0; i < p->n; i++)
		{
		Mono * m = & p->m[i];
		double e = 0;
		for (j = 0; j < m->nf; j++)
			if (tequal(m->f[j].base, v)) e = m->f[j].e;
		if (e == k)
			{
			Mono c = mono_dup(m);
			if (k > 0)
				{
				mono_put(& c, tcpy(v), - k);
				mono_sort(& c);
				}
			mp_add_mono(& r, c);
			}
		}
	return r;
}

static MPoly mp_vpow (MPoly * p, Node * v, int k)	/* p * v^k */
{
	MPoly r = { NULL, 0, 0 };
	int i;
	for (i = 0; i < p->n; i++)
		{
		Mono c = mono_dup(& p->m[i]);
		if (k > 0) { mono_put(& c, tcpy(v), k); mono_sort(& c); }
		mp_add_mono(& r, c);
		}
	return r;
}

static Node * mp_main_atom (MPoly * a, MPoly * b)	/* an atom of a or b (the first by tcmp) */
{
	MPoly * ps[2] = { a, b };
	Node * v = NULL;
	int s, i, j;
	for (s = 0; s < 2; s++)
		for (i = 0; i < ps[s]->n; i++)
			for (j = 0; j < ps[s]->m[i].nf; j++)
				if (! v || tcmp(ps[s]->m[i].f[j].base, v) < 0) v = ps[s]->m[i].f[j].base;
	return v;
}

static MPoly mp_gcd (MPoly * a, MPoly * b);

/* the content of p in v: the gcd of its coefficients */
static MPoly mp_content (MPoly * p, Node * v)
{
	int d = mp_deg(p, v), k;
	MPoly g = { NULL, 0, 0 };
	for (k = 0; k <= d; k++)
		{
		MPoly c = mp_coef(p, v, k), h;
		if (c.n == 0) { mp_free(& c); continue; }
		if (g.n == 0) { g = c; }
		else
			{
			h = mp_gcd(& g, & c);
			mp_free(& g);
			mp_free(& c);
			g = h;
			}
		if (mp_is_const(& g)) break;
		}
	return g;
}

/* the integer content made 1 and the leading coefficient positive */
static void mp_normalize (MPoly * p)
{
	double g = 0;
	int i;
	for (i = 0; i < p->n; i++)
		{
		double c = p->m[i].c;
		if (c != floor(c) || fabs(c) > 1e15) { g = 0; break; }
		g = dgcd(g, c);
		}
	if (p->n && g == 0) g = fabs(p->m[mp_lead(p)].c);	/* fractions: leading coefficient 1 */
	if (p->n && p->m[mp_lead(p)].c < 0) g = -g;
	if (g != 0 && g != 1)
		for (i = 0; i < p->n; i++) p->m[i].c /= g;
}

/* pseudo-remainder of a by b in v: lc(b)^k a - q b with deg r < deg b */
static MPoly mp_prem (MPoly * a, MPoly * b, Node * v)
{
	MPoly r = mp_dup(a), lb = mp_coef(b, v, mp_deg(b, v));
	int db = mp_deg(b, v), steps = 0;
	while (r.n > 0 && mp_deg(& r, v) >= db && steps++ < 1000)
		{
		int dr = mp_deg(& r, v);
		MPoly lr = mp_coef(& r, v, dr), t = { NULL, 0, 0 }, sh = mp_vpow(b, v, dr - db);
		mp_addmul(& t, & lb, & r, 1);		/* lc(b)*r - lc(r)*v^(dr-db)*b */
		mp_addmul(& t, & lr, & sh, -1);
		mp_free(& r);
		mp_free(& lr);
		mp_free(& sh);
		r = t;
		}
	mp_free(& lb);
	return r;
}

static MPoly mp_gcd (MPoly * a, MPoly * b)
{
	Node * v;
	MPoly ca, cb, pa, pb, c, g;
	if (a->n == 0) { g = mp_dup(b); mp_normalize(& g); return g; }
	if (b->n == 0) { g = mp_dup(a); mp_normalize(& g); return g; }
	if (mp_is_const(a) || mp_is_const(b)) return mp_const(1);
	v = mp_main_atom(a, b);
	if (mp_deg(a, v) == 0 || mp_deg(b, v) == 0)	/* v in one of them only */
		{
		MPoly * with = mp_deg(a, v) > 0 ? a : b, * without = with == a ? b : a, cw;
		cw = mp_content(with, v);
		g = mp_gcd(& cw, without);
		mp_free(& cw);
		return g;
		}
	ca = mp_content(a, v);
	cb = mp_content(b, v);
	c = mp_gcd(& ca, & cb);
	if (! mp_div(a, & ca, & pa)) pa = mp_dup(a);
	if (! mp_div(b, & cb, & pb)) pb = mp_dup(b);
	mp_free(& ca);
	mp_free(& cb);
	if (mp_deg(& pa, v) < mp_deg(& pb, v)) { MPoly h = pa; pa = pb; pb = h; }
	while (pb.n > 0 && mp_deg(& pb, v) > 0)		/* primitive remainder sequence */
		{
		MPoly r = mp_prem(& pa, & pb, v), cr, pr;
		mp_free(& pa);
		pa = pb;
		if (r.n == 0) { pb = r; break; }
		cr = mp_content(& r, v);
		if (! mp_div(& r, & cr, & pr)) pr = mp_dup(& r);
		mp_free(& r);
		mp_free(& cr);
		pb = pr;
		}
	if (pb.n > 0)				/* a remainder free of v: the primitive gcd is 1 */
		{
		mp_free(& pa);
		pa = mp_const(1);
		}
	mp_free(& pb);
	{
	MPoly cp = mp_content(& pa, v), pp;		/* primitive part of the last one */
	if (! mp_div(& pa, & cp, & pp)) pp = mp_dup(& pa);
	mp_free(& cp);
	mp_free(& pa);
	g = (MPoly) { NULL, 0, 0 };
	mp_addmul(& g, & c, & pp, 1);
	mp_free(& c);
	mp_free(& pp);
	}
	mp_normalize(& g);
	return g;
}

static void mp_cancel (MPoly * nu, MPoly * de)
{
	MPoly * ps[2] = { nu, de };
	Node * v = mp_single_atom(nu, de);
	double g = 0;
	int s, i, exact = 1;
	for (s = 0; s < 2; s++)
		for (i = 0; i < ps[s]->n; i++) exact &= ps[s]->m[i].exact;
	if (exact && nu->n > 0 && de->n > 0)	/* exact: the gcd in all atoms */
		{
		MPoly gp = mp_gcd(nu, de), q1, q2;
		if (! mp_is_const(& gp) && mp_div(nu, & gp, & q1))
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
	else if (v && nu->n > 0)		/* real numbers: Euclid in one atom */
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

static Node * mp_quotient_free (MPoly * num, MPoly * den)	/* frees num and den */
{
	Node * r = mp_quotient(num, den);
	mp_free(num);
	mp_free(den);
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
 * [1,2] + [a,b] = [1+a, 2+b], x*[a,b] = [x*a, x*b],
 * sin([a,b]) = [sin(a), sin(b)]; nested lists (matrices) too.
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

/* force: u is threaded although its head is a symbolic C function (the
 * arithmetic of vectors and matrices, listop) */
static Node * thread_f (Node * u, int force)
{
	Node * t[MAXDIM], * e[MAXDIM], * args, * r;
	int k, n, len = -1, i;
	u = deref(u);
	if (! u || u->type != Func || ! has_list(u)) return tcpy(u);
	n = term_nargs(u);
	if (n > MAXDIM) return tcpy(u);
	for (k = 0; k < n; k++) t[k] = thread_f(arg(u, k), 0);
	if (! is_head(u, "list", -1) && (force || ! builtin(TERM_HEAD(u))))
		for (k = 0; k < n; k++)
			if (is_head(t[k], "list", -1))
				{
				int l = list_len(t[k]);
				if (len >= 0 && l != len) { len = -2; break; }
				len = l;
				}
	if (len > 0 && len <= MAXDIM)		/* f(.., [a1..an], ..) = [f(.., ai, ..)] */
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
			else		/* the variant for the sorts of the elements */
				c = mknod(Func, (Node *) getsymbol((Symbol *) u->l, args), args);
			e[i] = thread_f(c, force);
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

static Node * thread (Node * u)
{
	return thread_f(u, 0);
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

/* ---- the arithmetic of explicit vectors and matrices (inc/list) ----
 * [1,2] + [a,b] = [1+a, 2+b], x*[a,b] = [x*a, x*b]: element by element
 * (listop); the product of matrices, and of a matrix and a vector, is the
 * matrix product (matmul), its integer powers repeated products (matpow).
 * Symbolic matrices (CONST A : matrix) stay as they are. */

static Node * nice_elems (Node * t)	/* nice for each entry of a nested list (takes t) */
{
	Node * e[MAXDIM];
	int i, n;
	if (! is_head(t, "list", -1) || (n = list_len(t)) > MAXDIM) return nice(t);
	for (i = 0; i < n; i++) e[i] = nice_elems(tcpy(arg(t, i)));
	delete(t);
	return mk_list(e, n);
}

static Node * s_listop (Node * a[], int n, Symbol * f)
{
	Node * args = NULL, * u, * r;
	int k, any = 0;
	for (k = 0; k < n; k++)
		if (is_head(a[k], "list", -1)) any = 1;
	if (! any) return NULL;
	for (k = n - 1; k >= 0; k--)
		args = args ? mknod(Terms, tcpy(a[k]), args) : tcpy(a[k]);
	u = mknod(Func, (Node *) f, args);
	r = thread_f(u, 1);
	delete(u);
	return nice_elems(r);
}

static Node * s_matmul (Node * a[], int n, Symbol * f)
{
	return with_thread(dot_impl, a, n, f);
}

static Node * s_matpow (Node * a[], int n, Symbol * f)	/* m^k, k an integer */
{
	Node * m, * r, * b[2];
	double v;
	int k, rows, cols;
	if (n != 2 || ! mat_dims(a[0], & rows, & cols) || rows != cols
	    || ! is_num(a[1], & v) || v != floor(v) || fabs(v) > 64) return NULL;
	k = (int) v;
	if (k == 0)
		{
		Node * c = mk_int(rows);
		r = s_identity(& c, 1, f);
		delete(c);
		return r;
		}
	m = k > 0 ? tcpy(a[0]) : inverse_impl(a, 1, f);
	if (! m) return NULL;
	if (k < 0) k = -k;
	r = tcpy(m);
	while (--k > 0)
		{
		Node * p;
		b[0] = r;
		b[1] = m;
		p = dot_impl(b, 2, f);
		delete(r);
		r = p;
		if (! r) break;
		}
	delete(m);
	return r;
}

/* sortleq(u, v): the sort of u is the sort of v or below it (SUBSORT),
 * e.g. not(sortleq(x, nil)): x is no vector (inc/linalg) */
static Node * s_sortleq (Node * a[], int n, Symbol * f)
{
	Node * su, * sv;
	if (n != 2) return NULL;
	su = arg_sort(deref(a[0]));
	sv = arg_sort(deref(a[1]));
	return mk_bool(su && sv && sort_dist(su, sv) >= 0, f);
}

/* list(a,b,..) = [a,b,..]: the old name of the list */
static Node * s_tolist (Node * a[], int n, Symbol * f)
{
	Node * e[MAXLIST > 256 ? 256 : MAXLIST];
	int i;
	if (n < 1 || n > 256) return NULL;
	for (i = 0; i < n; i++) e[i] = tcpy(a[i]);
	return mk_list(e, n);
}
static Node * s_dot (Node * a[], int n, Symbol * f) { return with_thread(dot_impl, a, n, f); }
static Node * s_det (Node * a[], int n, Symbol * f) { return with_thread(det_impl, a, n, f); }
static Node * s_linsolve (Node * a[], int n, Symbol * f) { return with_thread(linsolve_impl, a, n, f); }
static Node * s_inverse (Node * a[], int n, Symbol * f) { return with_thread(inverse_impl, a, n, f); }

/* ---- printing of lists (SHOW [ ATT show_list, inc/list) ----
 * As Julia prints arrays by their shape: a rectangular list of lists of
 * depth 2 that is the whole printed term as a grid with aligned columns,
 * deeper ones as slices [i, :, :] = grid; everything else inline as
 * [a, b, [c, d]]. */

extern Node * print_root;	/* run.c */

static char * entry_text (Node * t)	/* the printed form of t, without trailing blanks */
{
	char * s;
	size_t n;
	out_capture_begin();
	tprint(t, 0);
	s = out_capture_end();
	n = strlen(s);
	while (n > 0 && s[n - 1] == ' ') s[--n] = 0;
	return s;
}

static void show_inline (Node * t)
{
	int k, n = list_len(t);
	printfOut("[");
	for (k = 0; k < n; k++)
		{
		char * s = entry_text(arg(deref(t), k));
		printfOut("%s%s", k ? ", " : "", s);
		free(s);
		}
	printfOut("] ");
}

/* the dimensions of a rectangular nested list: their number (depth), 0 if
 * it is not rectangular */
static int list_shape (Node * t, int dims[], int maxd)
{
	int d = 0;
	t = deref(t);
	while (is_head(t, "list", -1) && d < maxd)
		{
		dims[d++] = list_len(t);
		t = deref(arg(t, 0));
		}
	return d;
}

static int list_rect (Node * t, int dims[], int d, int level)	/* all elements have the shape */
{
	int k;
	t = deref(t);
	if (level == d) return ! is_head(t, "list", -1);
	if (! is_head(t, "list", -1) || list_len(t) != dims[level]) return 0;
	for (k = 0; k < dims[level]; k++)
		if (! list_rect(arg(t, k), dims, d, level + 1)) return 0;
	return 1;
}

static void show_grid (Node * m, int rows, int cols)
{
	char ** e = (char **) malloc(rows * cols * sizeof(char *));
	int * w = (int *) calloc(cols, sizeof(int)), * num = (int *) calloc(cols, sizeof(int)), i, j;
	if (! e || ! w || ! num) fatal("symmat : no room");
	for (j = 0; j < cols; j++) num[j] = 1;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			{
			e[i * cols + j] = entry_text(mat_entry(m, i, j));
			if ((int) strlen(e[i * cols + j]) > w[j]) w[j] = (int) strlen(e[i * cols + j]);
			if (! num_sym(mat_entry(m, i, j))) num[j] = 0;
			}
	for (i = 0; i < rows; i++)		/* columns of numbers right-aligned, as in Julia */
		{
		printfOut("%s[ ", i ? "\n" : "");
		for (j = 0; j < cols; j++)
			printfOut(num[j] ? "%*s%s" : "%-*s%s", w[j], e[i * cols + j], j < cols - 1 ? "  " : " ]");
		}
	free(num);
	for (i = 0; i < rows * cols; i++) free(e[i]);
	free(e);
	free(w);
}

static void show_slices (Node * t, int dims[], int d, int level, int idx[])
{
	int k, j;
	if (d - level == 2)
		{
		printfOut("\n[");
		for (j = 0; j < level; j++) printfOut("%d, ", idx[j] + 1);
		printfOut(":, :] =\n");
		show_grid(t, dims[level], dims[level + 1]);
		printfOut("\n");
		return;
		}
	for (k = 0; k < dims[level]; k++)
		{
		idx[level] = k;
		show_slices(arg(deref(t), k), dims, d, level + 1, idx);
		}
}

static int show_list (Node * t, int prec)
{
	int dims[8], idx[8], d;
	t = deref(t);
	if (! is_head(t, "list", -1)) return 0;
	d = list_shape(t, dims, 8);
	if (t == print_root && d >= 2 && list_rect(t, dims, d, 0) && dims[d - 1] > 0)
		{
		if (d == 2) show_grid(t, dims[0], dims[1]);
		else show_slices(t, dims, d, 0, idx);
		printfOut(" ");
		}
	else
		show_inline(t);
	return 1;
}

static const struct { const char * name; show_function * fn; } pfn_tab[] = {
	{ "show_list", show_list },
	{ NULL, NULL } };

show_function * give_pfn (const char * name)
{
	int i;
	for (i = 0; pfn_tab[i].name; i++)
		if (! strcmp(pfn_tab[i].name, name)) return pfn_tab[i].fn;
	printfErr(" --ERROR SHOW : print function %s is not implemented\n", name);
	return NULL;
}

void show_def (Node * np)		/* FUNC(show_def, PARAM(f, print function or NULL)) */
{
	Node * p = np->r;
	Symbol * f = (Symbol *) p->l, * s = f;
	show_function * fn = (show_function *) p->r;
	p->l = p->r = NULL;		/* a symbol and a C function: not deleted */
	do	{
		showfn(s) = (void *) fn;
		s = variants(s);
		} while (s && s != f);
}
