/*
 *	plot.c (2026)
 *
 *	Plots by gnuplot, as in Julia: plot(u, x, a, b [, n]) is a term that
 *	draws the curve of u for x from a to b (n points, 400 if not given)
 *	when it is printed as a result (SHOW plot ATT show_plot, inc/plot),
 *	plot!(u, x, a, b [, n]) adds curves to the last plot; u may be a list
 *	[u, v, ..]. So REWR plot(Pade(..), x, a, b) : All simplifies u first. A
 *	point where u has no real value ends a piece of the curve (poles of
 *	tan, ln of x <= 0); the legend is the name of a TERM, else the term.
 *	The statement PLOT "gnuplot command" adds a setting for the following
 *	plots, PLOT alone removes them.
 *
 *	gnuplot is ENV REWRITE_GNUPLOT, else gnuplot in the PATH or, on
 *	Windows, in C:\Program Files\gnuplot\bin ("none": the arguments are
 *	checked, nothing is drawn, as in the tests). One gnuplot process draws
 *	into its window; with a setting "set term ..." or "set output ..." a
 *	new one is started for each plot and rewrite waits for it, so that a
 *	plot in the terminal (set term dumb) or a file is complete in its place.
 *	Included by symfn.c (it uses replace and num_value_r).
 */

#include <signal.h>

#define MAXPLOTSET 32
#define MAXCURVES 16
static char * plot_set[MAXPLOTSET];	/* the gnuplot commands of PLOT "..." */
static int nplot_set = 0;

typedef struct { char * title; double * x, * y; int n; } Curve;	/* y NaN: a gap */
static Curve curves[MAXCURVES];		/* the last plot, for plot! */
static int ncurves = 0;
static FILE * gnuplot = NULL;		/* the process that draws into its window */
static void * gnuplot_proc = NULL;	/* for child_close */
static char plot_xname[64];		/* the label of the x axis: the variable */

/* PLOT "set grid": a gnuplot command for the following plots; PLOT alone
   removes them all */
void plot_set_fn (Node * np)
{
	if (! np->r)
		{
		while (nplot_set > 0) free(plot_set[--nplot_set]);
		return;
		}
	if (nplot_set == MAXPLOTSET) { printfErr("PLOT : too many settings (PLOT alone removes them)\n"); return; }
	plot_set[nplot_set++] = strdup(name((Symbol *) np->r));
}

static int file_exists (const char * f)
{
	FILE * fp = fopen(f, "rb");
	if (fp) fclose(fp);
	return fp != NULL;
}

/* the gnuplot program with its path, NULL if not found; "none" for no plots */
static const char * gnuplot_program (void)
{
	static char path[1024];
	const char * g = getenv("REWRITE_GNUPLOT"), * p, * e;
#ifdef _WIN32
	const char sep = ';', * exe[] = { "gnuplot.exe", NULL };
	if (! (g && * g) && file_exists("C:\\Program Files\\gnuplot\\bin\\gnuplot.exe"))
		return "C:\\Program Files\\gnuplot\\bin\\gnuplot.exe";
#else
	const char sep = ':', * exe[] = { "gnuplot", NULL };
#endif
	int i;
	if (g && * g) return strcmp(g, "none") == 0 || file_exists(g) ? g : NULL;
	for (p = getenv("PATH"); p && * p; p = * e ? e + 1 : e)
		{
		e = strchr(p, sep);
		if (! e) e = p + strlen(p);
		for (i = 0; exe[i]; i++)
			{
			snprintf(path, sizeof path, "%.*s/%s", (int) (e - p), p, exe[i]);
			if (e > p && file_exists(path)) return path;
			}
		}
	return NULL;
}

/* the legend of a curve: the name of a TERM, else the term (Unicode,
   shortened); ' doubled for gnuplot's '...' */
static char * curve_title (Node * u)
{
	char * s, * t, * p, * q;
	int save = pretty_output, n = 0;
	if (u->type == Const) u = u->l;
	if (u->type == SYM_TYPE && lexval((Symbol *) u) == Term)
		s = strdup(name((Symbol *) u));
	else
		{
		out_capture_begin();
		pretty_output = 1;
		tprint(u, 0);
		pretty_output = save;
		s = out_capture_end();
		}
	t = (char *) malloc(2 * strlen(s) + 4);
	for (p = s + strspn(s, " "), q = t; * p && n < 60; p++, n++)
		{
		if (* p == '\'') * q++ = '\'';
		* q++ = * p;
		}
	while (q > t && q[-1] == ' ') q--;
	strcpy(q, * p ? "..." : "");
	free(s);
	return t;
}

static int plot_value (Node * u, Node * x, double xv, double * y)
{
	Node * xn = mk_num(xv), * t = replace(u, x, xn);
	int ok = num_value_r(t, y) && isfinite(* y);
	delete(t);
	delete(xn);
	return ok;
}

static void curves_free (void)
{
	while (ncurves > 0)
		{
		Curve * c = & curves[--ncurves];
		free(c->title);
		free(c->x);
		free(c->y);
		}
}

/* the curves of plot(u, x, a, b [, n]) added to the last plot; 0 (with a
   message) if the arguments are wrong */
static int add_curves (Node * t)
{
	Node * a[5], * u, * x, * c[MAXCURVES], * ce[MAXCURVES];
	double lo, hi, v, y;
	int na = term_nargs(t), nc = 0, npts = 400, i, k, any = 0;
	if (na < 4 || na > 5) { printfErr("plot : expected plot(u, x, a, b)  or  plot(u, x, a, b, n)\n"); return 0; }
	for (i = 0; i < na; i++) a[i] = term_arg(t, i);
	x = deref(a[1]);
	if (x->type == Const) x = x->l;
	if (x->type != SYM_TYPE || lexval((Symbol *) x) != Const
	    || find_symbol(name((Symbol *) x)) != (Symbol *) x)		/* a declared name, no number */
		{ printfErr("plot : the second argument must be the variable, a symbol without a value\n"); return 0; }
	if (hasval((Symbol *) x))
		{ printfErr("plot : %s has a value (%s = nothing removes it)\n", name((Symbol *) x), name((Symbol *) x)); return 0; }
	if (! num_value_r(a[2], & lo) || ! num_value_r(a[3], & hi) || ! (lo < hi))
		{ printfErr("plot : the range a, b must be numbers with a < b\n"); return 0; }
	if (na == 5 && (! num_value_r(a[4], & v) || v < 2 || v > 100000))
		{ printfErr("plot : the number of points must be 2 .. 100000\n"); return 0; }
	if (na == 5) npts = (int) v;
	if (ncurves == 0) snprintf(plot_xname, sizeof plot_xname, "%s", name((Symbol *) x));
	u = deref(a[0]);
	if (is_head(u, "list", -1))
		for (k = 0; k < list_len(u) && nc < MAXCURVES; k++) c[nc++] = term_arg(u, k);	/* P, not its term */
	else
		c[nc++] = a[0];
	if (ncurves + nc > MAXCURVES) { printfErr("plot : at most %d curves in a plot\n", MAXCURVES); return 0; }
	for (k = 0; k < nc; k++)	/* calculated once: a C function in a TERM, R = ratinterp(..) */
		ce[k] = tcalc(tcpy(deref(c[k])));
	for (k = 0; k < nc && ! any; k++)		/* one real value somewhere? */
		for (i = 0; i < npts && ! any; i++)
			any = plot_value(ce[k], x, lo + (hi - lo) * i / (npts - 1), & y);
	if (! any)
		{
		printfErr("plot : no real values of %s for %s from %g to %g\n",
		          nc > 1 ? "the terms" : "the term", name((Symbol *) x), lo, hi);
		for (k = 0; k < nc; k++) delete(ce[k]);
		return 0;
		}
	for (k = 0; k < nc; k++)
		{
		Curve * cv = & curves[ncurves++];
		cv->title = curve_title(c[k]);
		cv->n = npts;
		cv->x = (double *) malloc(npts * sizeof(double));
		cv->y = (double *) malloc(npts * sizeof(double));
		if (! cv->x || ! cv->y) fatal("plot : no room");
		for (i = 0; i < npts; i++)
			{
			cv->x[i] = lo + (hi - lo) * i / (npts - 1);
			if (! plot_value(ce[k], x, cv->x[i], & cv->y[i])) cv->y[i] = NAN;
			}
		delete(ce[k]);
		}
	return 1;
}

static int own_terminal (void)		/* a setting set term .. or set output .. */
{
	int i;
	for (i = 0; i < nplot_set; i++)
		if (strncmp(plot_set[i] + strspn(plot_set[i], " "), "set term", 8) == 0
		    || strncmp(plot_set[i] + strspn(plot_set[i], " "), "set output", 10) == 0) return 1;
	return 0;
}

static void gnuplot_close (void)
{
	if (gnuplot) child_close(gnuplot, gnuplot_proc);
	gnuplot = NULL;
}

/* the last plot, drawn by gnuplot */
static void draw (void)
{
	const char * prog = gnuplot_program();
	FILE * gp;
	void * proc = gnuplot_proc;
	int i, k, once = own_terminal(), failed;
	if (prog && strcmp(prog, "none") == 0) return;
	if (! prog)
		{
		printfErr("plot : gnuplot not found; install it (gnuplot.info) or set REWRITE_GNUPLOT\n"
		          "  to the path of the program\n");
		return;
		}
	if (once) gnuplot_close();
	gp = gnuplot;
	if (! gp)
		{
		static int registered = 0;
		fflush(stdout);
		/* the window stays after rewrite: without rewrite's output, so
		   that a pipe it writes into (rewrite f.rw | less) ends */
		gp = child_open(prog, "-persist", ! once, & proc);
		if (! gp) { printfErr("plot : could not start %s\n", prog); return; }
		if (! registered) { atexit(gnuplot_close); registered = 1; }
		}
#ifdef SIGPIPE
	signal(SIGPIPE, SIG_IGN);		/* gnuplot ended: no end of rewrite */
#endif
	fprintf(gp, "reset\nset encoding utf8\nset xlabel '%s'\n", plot_xname);
	for (i = 0; i < nplot_set; i++) fprintf(gp, "%s\n", plot_set[i]);
	fprintf(gp, "plot ");
	for (k = 0; k < ncurves; k++)
		fprintf(gp, "%s'-' with lines title '%s'", k ? ", " : "", curves[k].title);
	fprintf(gp, "\n");
	for (k = 0; k < ncurves; k++)
		{
		for (i = 0; i < curves[k].n; i++)
			if (isnan(curves[k].y[i])) fprintf(gp, "\n");	/* a gap */
			else fprintf(gp, "%.10g %.10g\n", curves[k].x[i], curves[k].y[i]);
		fprintf(gp, "e\n");
		}
	failed = fflush(gp) != 0 || ferror(gp);
	if (once) failed |= child_close(gp, proc) != 0;
	else { gnuplot = gp; gnuplot_proc = proc; }
#ifdef SIGPIPE
	signal(SIGPIPE, SIG_DFL);
#endif
	if (failed)
		{
		printfErr("plot : gnuplot (%s) did not take the plot\n", prog);
		if (! once) gnuplot_close();
		}
}

/* SHOW plot ATT show_plot: plot(..) or plot!(..) printed as the result
   draws; inside another term, or printed into a string, it is a term */
static int show_plot (Node * t, int prec)
{
	t = deref(t);
	if (t != print_root || out_capturing()) return 0;
	if (strcmp(name(TERM_HEAD(t)), "plot") == 0) curves_free();
	if (add_curves(t)) draw();
	return 1;
}
