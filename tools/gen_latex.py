"""Generates src/latex.c from Julia's REPL.REPLCompletions.latex_symbols
(dumped by latex_dump.jl to latex_symbols.tsv). Julia: MIT license."""
import sys, os
tsv, out = sys.argv[1], sys.argv[2]
d = {}
for line in open(tsv, encoding='utf-8'):
    k, v = line.rstrip('\n').split('\t', 1)
    assert k.startswith('\\')
    d[k[1:]] = v
short = sorted(k for k in d if len(k) <= 1)
print('one-letter names:', short)
for esc in ('n', 't', 'r', 'a', 'b', 'f', 'v', '0'):
    print('escape', esc, 'in table:', esc in d)

def c_str(s):
    out = []
    for ch in s:
        if ch in '\\"':
            out.append('\\' + ch)
        elif 32 <= ord(ch) < 127:
            out.append(ch)
        else:
            out.extend('\\x%02x' % b for b in ch.encode('utf-8'))
    # a hex escape followed by a hex digit would be read on: split the string
    res, prev_hex = '', False
    for piece in out:
        if prev_hex and piece[0] in '0123456789abcdefABCDEF' and not piece.startswith('\\'):
            res += '" "'
        res += piece
        prev_hex = piece.startswith('\\x')
    return '"' + res + '"'

keys = sorted(d, key=lambda k: k.encode('utf-8'))      # strcmp order
with open(out, 'w', encoding='utf-8', newline='\n') as f:
    f.write('''/*
 *	latex.c (2026)
 *
 *	LaTeX-like names of Unicode characters, as in Julia: \\alpha is α,
 *	\\le is ≤. The input is converted before scanning (scan.l), the output
 *	prints the characters. The table is Julia's
 *	REPL.REPLCompletions.latex_symbols (MIT license, Copyright (c) 2009-2024
 *	Jeff Bezanson, Stefan Karpinski, Viral B. Shah, and other contributors),
 *	generated with tools/gen_latex.py; do not edit by hand.
 */

#include <string.h>
#include <stdlib.h>
#include "latex.h"

typedef struct { const char * name, * utf8; } LatexSym;

static const LatexSym latex_tab[] = {
''')
    for k in keys:
        f.write('\t{ %s, %s },\n' % (c_str(k), c_str(d[k])))
    f.write('''};

#define NLATEX (sizeof(latex_tab) / sizeof(latex_tab[0]))
#define MAXNAME %d

static int cmp_name (const void * a, const void * b)
{
	return strcmp(((const LatexSym *) a)->name, ((const LatexSym *) b)->name);
}

static int is_letter (char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/* the character of the longest name at s (after the backslash) and the
   length of that name, or NULL. A name that ends with a letter must not be
   followed by one: \\alphax stays as it is. */
const char * latex_symbol (const char * s, int * len)
{
	char buf[MAXNAME + 1];
	int n;
	for (n = 0; n < MAXNAME && s[n] && s[n] != ' ' && s[n] != '\\t' && s[n] != '\\n'; n++)
		buf[n] = s[n];
	for ( ; n > 0; n--)
		{
		LatexSym key, * r;
		buf[n] = 0;
		if (is_letter(buf[n - 1]) && is_letter(s[n])) continue;
		key.name = buf;
		r = (LatexSym *) bsearch(& key, latex_tab, NLATEX, sizeof(LatexSym), cmp_name);
		if (r)
			{
			* len = n;
			return r->utf8;
			}
		}
	return NULL;
}

/* a copy of the line with the names replaced (\\alpha -> α); NULL if there
   is none. The caller frees it. */
char * latex_convert (const char * line)
{
	const char * p, * u;
	char * out, * q;
	int len, any = 0;
	for (p = strchr(line, '\\\\'); p; p = strchr(p + 1, '\\\\'))
		if (latex_symbol(p + 1, & len)) { any = 1; break; }
	if (! any) return NULL;
	out = (char *) malloc(4 * strlen(line) + 1);	/* a name is not shorter than its character */
	if (! out) return NULL;
	for (p = line, q = out; * p; )
		if (* p == '\\\\' && (u = latex_symbol(p + 1, & len)) != NULL)
			{
			strcpy(q, u);
			q += strlen(u);
			p += len + 1;
			}
		else
			* q++ = * p++;
	* q = 0;
	return out;
}
''' % max(len(k.encode('utf-8')) for k in keys))
print(len(keys), 'entries written to', out)
# the names and characters for rlwrap's completion (tools/latex.rlwrap):
# \alpha<TAB>α, one per line
tsv_out = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'latex_symbols.tsv')
with open(tsv_out, 'w', encoding='utf-8', newline='\n') as f:
    for k in sorted(d):
        f.write('\\' + k + '\t' + d[k] + '\n')
print(len(d), 'names written to', tsv_out)
