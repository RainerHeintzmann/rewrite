/*
 *	pretty.c (2026)
 *
 *	The output with Unicode (PRETTY 1), included by symfn.c (it uses its
 *	helpers): x² and x⁻¹ for integer powers, √x for x^(1/2) and sqrt(x),
 *	the names of ALIAS .. SHOW (π, ·, ≤, ∞), spaces only around + and -
 *	and the comparisons, f(a, b) for calls. Everything else (lists, rules)
 *	is printed by tprint, whose parts come here again. The input reads all
 *	of it back (superscripts in latex.c, the names by ALIAS).
 */

#include <ctype.h>

static const char * pretty_name (Symbol * s)
{
	const char * a = print_alias(name(s));
	return a ? a : name(s);
}

/* a power with an integer exponent as superscript digits */
static void print_superscript (long n)
{
	static const char * digit[] = { "\xe2\x81\xb0", "\xc2\xb9", "\xc2\xb2", "\xc2\xb3", "\xe2\x81\xb4",
	                                "\xe2\x81\xb5", "\xe2\x81\xb6", "\xe2\x81\xb7", "\xe2\x81\xb8", "\xe2\x81\xb9" };
	char buf[24];
	int i;
	if (n < 0) printfOut("\xe2\x81\xbb");		/* superscript minus */
	snprintf(buf, sizeof buf, "%ld", n < 0 ? -n : n);
	for (i = 0; buf[i]; i++) printfOut("%s", digit[buf[i] - '0']);
}

/* an atom or a call f(..): needs no parentheses as a base or after √ */
static int pretty_atomic (Node * t)
{
	double v;
	t = deref(t);
	if (! t) return 1;
	if (t->type == SYM_TYPE && lexval((Symbol *) t) == Term) return t->l ? pretty_atomic(t->l) : 1;
	if (t->type == Const) t = t->l;
	if (t->type == SYM_TYPE) return ! (is_num(t, & v) && v < 0);	/* (-2)², but 2², (1/2)² */
	return t->type == Func && lexval(TERM_HEAD(t)) == Func && ! showfn(TERM_HEAD(t))
	       && ! is_head(t, "^", 2);
}

static void pretty_operand (Node * t)		/* in parentheses unless atomic */
{
	if (pretty_atomic(t)) { tprint(t, 0); return; }
	printfOut("(");
	tprint(t, 0);
	printfOut(")");
}

static void pretty_number (Node * t)		/* the number as printed, without blanks */
{
	char * s;
	size_t n;
	out_capture_begin();
	pretty_output = 0;
	tprint(t, 0);
	pretty_output = 1;
	s = out_capture_end();
	n = strlen(s);
	while (n > 0 && s[n - 1] == ' ') s[--n] = 0;
	printfOut("%s", s + strspn(s, " "));
	free(s);
}

/* the pretty form of np; 0: tprint prints it */
int pretty_tprint (Node * np, int last)
{
	Symbol * h;
	int lex, n;
	double e;
	if (! np) return 0;
	if (np->type == SYM_TYPE)
		{
		Symbol * s = (Symbol *) np;
		if (lexval(s) == Term) return 0;
		if (number_symbol(s)) { pretty_number(np); return 1; }
		printfOut("%s", pretty_name(s));
		return 1;
		}
	if (np->type == Terms)
		{
		tprint(np->l, 0);
		if (np->r) { printfOut(", "); tprint(np->r, 0); }
		return 1;
		}
	if (np->type != Func) return 0;
	h = TERM_HEAD(np);
	if (showfn(h)) return 0;			/* its own print function (lists) */
	lex = lexval(h);
	n = term_nargs(np);
	if (is_head(np, "^", 2) && num_value(arg(np, 1), & e))
		{
		if (e == 0.5)				/* √x, √(1 + x) */
			{
			printfOut("\xe2\x88\x9a");
			pretty_operand(arg(np, 0));
			return 1;
			}
		if (e == floor(e) && fabs(e) < 1e9)	/* x², (1 + x)³, x⁻¹ */
			{
			pretty_operand(arg(np, 0));
			print_superscript((long) e);
			return 1;
			}
		}
	if (lex == Func)
		{
		const char * nm = pretty_name(h);
		if (n == 1 && ! isalnum((unsigned char) nm[0]) && nm[0] != '_')	/* √x, ¬a */
			{
			printfOut("%s", nm);
			pretty_operand(arg(np, 0));
			return 1;
			}
		printfOut("%s(", nm);
		tprint(np->r, 0);
		printfOut(")");
		return 1;
		}
	if (lex == La1 || lex == La2 || lex == La3 || lex == La4 || lex == La5 || lex == Ra)
		{
		const char * sep = (lex == La1 || lex == La2) ? " " : "";
		if (last > lex) printfOut("(");
		if (n == 1)			/* -x */
			{
			printfOut("%s", pretty_name(h));
			tprint(arg(np, 0), lex + 1);
			}
		else if (lex == Ra)
			{
			tprint(arg(np, 0), lex + 1);
			printfOut("%s%s%s", sep, pretty_name(h), sep);
			tprint(arg(np, 1), lex);
			}
		else
			{
			tprint(arg(np, 0), lex);
			printfOut("%s%s%s", sep, pretty_name(h), sep);
			tprint(arg(np, 1), lex + 1);
			}
		if (last > lex) printfOut(")");
		return 1;
		}
	return 0;
}
