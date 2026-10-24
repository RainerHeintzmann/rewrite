#!/usr/bin/env python3
"""
rubitest.py - run Rubi's integration test suite through rewrite.

Usage:
  python3 tools/rubitest.py TESTDIR [options]

  TESTDIR        folder with the .m files of Rubi's MathematicaSyntaxTestSuite
                 (github.com/RuleBasedIntegration/MathematicaSyntaxTestSuite,
                 MIT license); sub folders are searched too
  --files TEXT   only test files whose name contains TEXT (may be repeated)
  --max N        at most N problems per file
  --batch N      problems per rewrite run (default 20)
  --timeout S    seconds per rewrite run (default 60)
  --exe PATH     rewrite executable (default ./rewrite.exe or ./rewrite)
  --report FILE  write one line per problem to FILE
  --verbose      print every problem

Each problem {integrand, x, steps, antiderivative} is integrated with
  REWR Int(integrand, x) : RubiIntegrate
Symbols other than the integration variable become symbolic parameters.
The result counts as

  solved       no Int(...) is left and d/dx of the result equals the integrand
               numerically (5-point difference quotient at several points,
               with fixed values for the parameters)
  wrong        no Int(...) is left, but the derivative does not match
  unverified   no Int(...) is left, but the result could not be evaluated
  unsolved     an Int(...) is left (or the step limit was reached)
  failed       rewrite crashed or timed out
  skipped      the integrand uses something rewrite does not know (I, Erf, ...)

Must be started in the rewrite folder (the INC paths are relative).
"""

import cmath
import math

try:
    import mpmath           # special functions in the numerical check
except ImportError:
    mpmath = None
import os
import re
import subprocess
import sys
import time
from fractions import Fraction

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import rubi2rewrite as r2r          # noqa: E402  (parser of the translator)

# ----------------------------------------------------------------------
#  Problems
# ----------------------------------------------------------------------


def problems_of(path):
    """yields (line number, text) of the problems {...} in a test file"""
    with open(path, encoding='utf-8', errors='replace') as f:
        text = f.read()
    text = re.sub(r'\(\*.*?\*\)', lambda m: '\n' * m.group(0).count('\n'), text, flags=re.S)
    stmt, depth, start = None, 0, 0
    for no, line in enumerate(text.split('\n'), 1):
        s = line.strip()
        if stmt is None:
            if not s.startswith('{'):
                continue
            stmt, depth, start = s, 0, no
        else:
            stmt += ' ' + s
        depth += sum(s.count(c) for c in '[({') - sum(s.count(c) for c in '])}')
        if depth <= 0:
            yield start, stmt
            stmt = None


class Skip(Exception):
    pass


# Mathematica -> rewrite (functions of the integrand)
RW_FUNCS = dict(r2r.FUNCS)
RW_FUNCS.update({'Sqrt': 'sqrt', 'Exp': 'exp'})
# Mathematica -> Python (cmath) for the numerical check
PY_FUNCS = {
    'Sin': 'sin', 'Cos': 'cos', 'Tan': 'tan', 'Cot': 'cot', 'Sec': 'sec', 'Csc': 'csc',
    'ArcSin': 'asin', 'ArcCos': 'acos', 'ArcTan': 'atan', 'ArcCot': 'acot',
    'Sinh': 'sinh', 'Cosh': 'cosh', 'Tanh': 'tanh', 'Coth': 'coth', 'Sech': 'sech',
    'Csch': 'csch', 'ArcSinh': 'asinh', 'ArcCosh': 'acosh', 'ArcTanh': 'atanh',
    'ArcCoth': 'acoth', 'Log': 'log', 'Sqrt': 'sqrt', 'Exp': 'exp', 'Abs': 'abs',
}

# special functions: name in the check -> mpmath function
SPECIAL = {
    'erf': 'erf', 'erfc': 'erfc', 'erfi': 'erfi', 'fresnels': 'fresnels',
    'fresnelc': 'fresnelc', 'sinint': 'si', 'cosint': 'ci', 'sinhint': 'shi',
    'coshint': 'chi', 'expint': 'ei', 'expinte': 'expint', 'logint': 'li',
    'Gamma': None, 'loggamma': 'loggamma', 'polygamma': 'psi', 'zeta': 'zeta',
    'elliptick': 'ellipk', 'ellipticf': 'ellipf', 'elliptice': 'ellipe',
    'ellipticpi': 'ellippi', 'hyp2f1': 'hyp2f1', 'appellf1': 'appellf1',
    'besselj': 'besselj', 'asec': 'asec', 'acsc': 'acsc', 'asech': 'asech',
    'acsch': 'acsch',
}
for _m, _r in [('Erf', 'erf'), ('Erfc', 'erfc'), ('Erfi', 'erfi'), ('FresnelS', 'fresnels'),
               ('FresnelC', 'fresnelc'), ('SinIntegral', 'sinint'), ('CosIntegral', 'cosint'),
               ('SinhIntegral', 'sinhint'), ('CoshIntegral', 'coshint'),
               ('ExpIntegralEi', 'expint'), ('ExpIntegralE', 'expinte'),
               ('LogIntegral', 'logint'), ('Gamma', 'Gamma'), ('LogGamma', 'loggamma'),
               ('PolyGamma', 'polygamma'), ('Zeta', 'zeta'), ('EllipticK', 'elliptick'),
               ('EllipticF', 'ellipticf'), ('EllipticE', 'elliptice'),
               ('EllipticPi', 'ellipticpi'), ('Hypergeometric2F1', 'hyp2f1'),
               ('AppellF1', 'appellf1'), ('BesselJ', 'besselj'), ('ArcSec', 'asec'),
               ('ArcCsc', 'acsc'), ('ArcSech', 'asech'), ('ArcCsch', 'acsch')]:
    PY_FUNCS[_m] = _r
    RW_FUNCS.setdefault(_m, {'asec': 'arcsec', 'acsc': 'arccsc', 'asech': 'arcsech',
                             'acsch': 'arccsch'}.get(_r, _r))


def _mp_gamma(*a):
    return mpmath.gamma(a[0]) if len(a) == 1 else mpmath.gammainc(a[0], a[1])


def _special_env(real):
    """special functions for eval: complex results, or real only (else ValueError)"""
    env = {}
    if mpmath is None:
        return env
    for name, mp in SPECIAL.items():
        f = _mp_gamma if name == 'Gamma' else getattr(mpmath, mp)

        def wrap(*a, f=f):
            v = complex(f(*a))
            if real:
                if abs(v.imag) > 1e-12 * (1 + abs(v.real)):
                    raise ValueError('complex value')
                return v.real
            return v
        env[name] = wrap
    return env


# values of the parameters for the numerical check
PARAM_VALUES = {'a': 1.7, 'b': 0.6, 'c': 1.3, 'd': 0.9, 'e': 1.1, 'f': 0.7,
                'g': 1.4, 'h': 0.8, 'm': 1.3, 'n': 2.2, 'p': 0.7, 'q': 1.6,
                'A': 1.2, 'B': 0.5, 'C': 0.9, 'D': 1.15, 'k': 0.4, 'j': 0.45,
                'r': 0.35, 's': 0.55, 't': 0.65, 'u': 0.75, 'v': 0.85, 'w': 0.95}


def pname(sym):
    return 'qq' + sym          # parameter name in rewrite (c, e, n are taken)


def fmt_frac(q):
    if q.denominator == 1:
        s = str(q.numerator)
    else:
        s = '%d/%d' % (q.numerator, q.denominator)
    return '(' + s + ')' if q < 0 or q.denominator != 1 else s


def to_rw(e, var, params):
    """integrand as rewrite text"""
    k = e[0]
    if k == 'num':
        return fmt_frac(e[1])
    if k == 'sym':
        n = e[1]
        if n == var:
            return 'x'
        if n == 'Pi':
            return 'pi'
        if n == 'E':
            return 'e'
        if n == 'I' or n[0] == '$':
            raise Skip('symbol %s' % n)
        params.add(n)
        return pname(n)
    if k != 'call':
        raise Skip('pattern')
    head, args = e[1], e[2]
    if head == 'Plus':
        return '(' + '+'.join(to_rw(a, var, params) for a in args) + ')'
    if head == 'Times':
        return '(' + '*'.join(to_rw(a, var, params) for a in args) + ')'
    if head == 'Power':
        if args[0] == ('sym', 'E'):
            return 'exp(' + to_rw(args[1], var, params) + ')'
        return '((' + to_rw(args[0], var, params) + ')^(' + to_rw(args[1], var, params) + '))'
    if head == 'Log' and len(args) == 2:
        return '(ln(' + to_rw(args[1], var, params) + ')/ln(' + to_rw(args[0], var, params) + '))'
    if head in RW_FUNCS:
        return RW_FUNCS[head] + '(' + ','.join(to_rw(a, var, params) for a in args) + ')'
    raise Skip('function %s' % head)


def to_py(e, var):
    """integrand as Python expression (variable X, parameters P_name)"""
    k = e[0]
    if k == 'num':
        return '(%r)' % float(e[1])
    if k == 'sym':
        n = e[1]
        if n == var:
            return 'X'
        if n == 'Pi':
            return 'pi'
        if n == 'E':
            return 'E'
        return 'P_' + n
    head, args = e[1], e[2]
    if head == 'Plus':
        return '(' + '+'.join(to_py(a, var) for a in args) + ')'
    if head == 'Times':
        return '(' + '*'.join(to_py(a, var) for a in args) + ')'
    if head == 'Power':
        return 'pw(' + to_py(args[0], var) + ',' + to_py(args[1], var) + ')'
    if head == 'Log' and len(args) == 2:
        return '(log(' + to_py(args[1], var) + ')/log(' + to_py(args[0], var) + '))'
    if head in PY_FUNCS:
        return PY_FUNCS[head] + '(' + ','.join(to_py(a, var) for a in args) + ')'
    raise Skip('function %s' % head)

# ----------------------------------------------------------------------
#  Numerics (complex, principal branches as in Mathematica)
# ----------------------------------------------------------------------


def pw(a, b):
    if isinstance(a, (int, float)) and isinstance(b, (int, float)):
        if a > 0 or (b == int(b) and a != 0):
            return float(a) ** b
    if a == 0:
        return 0.0 if (b.real if isinstance(b, complex) else b) > 0 else complex('nan')
    return cmath.exp(b * cmath.log(a))


def _inv(f):
    return lambda z: 1 / f(z)


NUMENV = {
    'sin': cmath.sin, 'cos': cmath.cos, 'tan': cmath.tan,
    'cot': lambda z: 1 / cmath.tan(z), 'sec': _inv(cmath.cos), 'csc': _inv(cmath.sin),
    'asin': cmath.asin, 'acos': cmath.acos, 'atan': cmath.atan,
    'acot': lambda z: cmath.atan(1 / z),
    'sinh': cmath.sinh, 'cosh': cmath.cosh, 'tanh': cmath.tanh,
    'coth': lambda z: 1 / cmath.tanh(z), 'sech': _inv(cmath.cosh), 'csch': _inv(cmath.sinh),
    'asinh': cmath.asinh, 'acosh': cmath.acosh, 'atanh': cmath.atanh,
    'acoth': lambda z: cmath.atanh(1 / z),
    'log': cmath.log, 'sqrt': cmath.sqrt, 'exp': cmath.exp, 'abs': abs,
    'pi': math.pi, 'E': math.e, 'pw': pw,
}
NUMENV.update(_special_env(False))

def rpw(a, b):
    """real power; ValueError outside the real domain"""
    if a < 0 and b != int(b):
        raise ValueError('negative base')
    return float(a) ** b


# real evaluation: a point is only used if every intermediate value of the
# integrand is real (math raises ValueError otherwise)
REALENV = {
    'sin': math.sin, 'cos': math.cos, 'tan': math.tan,
    'cot': lambda z: 1 / math.tan(z), 'sec': lambda z: 1 / math.cos(z),
    'csc': lambda z: 1 / math.sin(z), 'asin': math.asin, 'acos': math.acos,
    'atan': math.atan, 'acot': lambda z: math.atan(1 / z),
    'sinh': math.sinh, 'cosh': math.cosh, 'tanh': math.tanh,
    'coth': lambda z: 1 / math.tanh(z), 'sech': lambda z: 1 / math.cosh(z),
    'csch': lambda z: 1 / math.sinh(z), 'asinh': math.asinh, 'acosh': math.acosh,
    'atanh': math.atanh, 'acoth': lambda z: math.atanh(1 / z),
    'log': math.log, 'sqrt': math.sqrt, 'exp': math.exp, 'abs': abs,
    'pi': math.pi, 'E': math.e, 'pw': rpw,
}
REALENV.update(_special_env(True))

# rewrite's output -> Python
RW_TO_PY = {
    'sin': 'sin', 'cos': 'cos', 'tan': 'tan', 'cot': 'cot', 'sec': 'sec', 'csc': 'csc',
    'arcsin': 'asin', 'arccos': 'acos', 'arctan': 'atan', 'arccot': 'acot',
    'sinh': 'sinh', 'cosh': 'cosh', 'tanh': 'tanh', 'coth': 'coth', 'sech': 'sech',
    'csch': 'csch', 'arcsinh': 'asinh', 'arccosh': 'acosh', 'arctanh': 'atanh',
    'arccoth': 'acoth', 'ln': 'log', 'sqrt': 'sqrt', 'exp': 'exp', 'abs': 'abs',
    'pi': 'pi', 'e': 'E',
}
RW_TO_PY.update({n: n for n in SPECIAL if not n.startswith('a')})
RW_TO_PY.update({'arcsec': 'asec', 'arccsc': 'acsc', 'arcsech': 'asech', 'arccsch': 'acsch'})

OUT_TOKEN = re.compile(r'\s*(?:(?P<num>(?:\d+\.?\d*|\.\d+)(?:e[-+]?\d+)?)|(?P<id>[A-Za-z_][A-Za-z0-9_]*)|(?P<op>[-+*/^(),]))')


def rw_result_to_py(s, params):
    """result printed by rewrite -> Python expression, or None"""
    out, pos, prev_glued = [], 0, False
    s = s.strip()
    while pos < len(s):
        m = OUT_TOKEN.match(s, pos)
        if not m:
            return None
        pos = m.end()
        if m.group('num') is not None:
            tok = m.group('num')
            # a '-' glued to a number after an operator is a negative literal
            if out and out[-1] == '-' and prev_glued and (len(out) == 1 or out[-2] in '(,^*/+-'):
                out[-1] = '(-' + tok + ')'
            else:
                out.append(tok)
        elif m.group('id') is not None:
            n = m.group('id')
            if n == 'x':
                out.append('X')
            elif n.startswith('qq') and n[2:] in params:
                out.append('P_' + n[2:])
            elif n in RW_TO_PY:
                out.append(RW_TO_PY[n])
            else:
                return None
        else:
            op = m.group('op')
            out.append('**' if op == '^' else op)
        prev_glued = pos < len(s) and not s[pos].isspace()
    return ' '.join(out)


def check(f_py, F_py, params):
    """compare dF/dx with f at some points; returns 'ok', 'bad' or 'noeval'"""
    env = dict(NUMENV)
    for p in params:
        env['P_' + p] = PARAM_VALUES.get(p, 0.77)
    renv = dict(REALENV)
    for p in params:
        renv['P_' + p] = PARAM_VALUES.get(p, 0.77)
    try:
        f_real = eval('lambda X: ' + f_py, renv)
        f = eval('lambda X: ' + f_py, env)
        F = eval('lambda X: ' + F_py, env)
    except Exception:
        return 'noeval'
    good = bad = 0
    for x0 in (0.31, 0.57, 0.83, 1.37, 2.29, 3.11, -0.43, -1.27):
        verdict = None
        try:
            f_real(x0)
        except (ValueError, ZeroDivisionError, OverflowError, TypeError):
            continue            # integrand not real here (branch cuts may differ)
        for h in (1e-3, 2e-4, 4e-5):   # smaller steps near singular points
            try:
                vals = [complex(F(x0 + k * h)) for k in (-2, -1, 1, 2)]
                d = (vals[0] - 8 * vals[1] + 8 * vals[2] - vals[3]) / (12 * h)
                fx = complex(f(x0))
            except (ZeroDivisionError, ValueError, OverflowError, TypeError):
                break
            if not all(cmath.isfinite(v) for v in vals + [fx]):
                break
            if abs(fx.imag) > 1e-12 * (1 + abs(fx)):
                break           # complex integrand here: branch cuts may differ
            scale = max(abs(v) for v in vals)
            if abs(d - fx) <= 1e-5 * (1 + abs(fx)) + 1e-10 * scale / h:
                verdict = 'good'
                break
            verdict = 'bad'
        if verdict == 'good':
            good += 1
        elif verdict == 'bad':
            bad += 1
    if good >= 1 and bad == 0:
        return 'ok'
    if good + bad == 0:
        return 'noeval'
    return 'bad'

# ----------------------------------------------------------------------
#  Running rewrite
# ----------------------------------------------------------------------

HEAD = '''INC "inc/all"
INC "inc/integration/all"
INC "inc/integration/rubi/all"
PRTNUM "%.15g "
TERM FF : real
CONST yy : real
x = yy
'''


def run_batch(exe, items, timeout):
    """items: list of (key, rewrite integrand, params); -> {key: text} or None"""
    params = set()
    for _, _, ps in items:
        params |= ps
    prog = [HEAD]
    if params:
        prog.append('CONST %s : real\n' % ','.join(pname(p) for p in sorted(params)))
    for key, integrand, _ in items:
        prog.append('PRT "@@BEGIN %s@@"\nFF = REWR Int(%s,x) : RubiIntegrate\nFF\n'
                    'PRT "@@END@@"\n' % (key, integrand))
    try:
        res = subprocess.run([exe], input=''.join(prog), capture_output=True,
                             text=True, timeout=timeout)
    except subprocess.TimeoutExpired as err:
        out = err.stdout or ''
        if isinstance(out, bytes):
            out = out.decode('utf-8', 'replace')
        return parse_output(out), True
    return parse_output(res.stdout + res.stderr), res.returncode != 0


def parse_output(text):
    found = {}
    for m in re.finditer(r'@@BEGIN (\S+)@@(.*?)@@END@@', text, re.S):
        body = [l for l in m.group(2).split('\n')
                if l.strip() and not l.startswith(('syn.y', 'def.c'))]
        found[m.group(1)] = body
    return found


def classify(body, f_py, params):
    text = ' '.join(body)
    if 'step limit' in text or 'Int (' in text or 'unintegrable' in text:
        return 'unsolved', text
    if 'Error' in text or 'error' in text or not body:
        return 'failed', text
    F_py = rw_result_to_py(body[-1], params)
    if F_py is None:
        return 'unverified', body[-1]
    r = check(f_py, F_py, params)
    return {'ok': 'solved', 'bad': 'wrong', 'noeval': 'unverified'}[r], body[-1]


def main():
    args = sys.argv[1:]
    opts = {'files': [], 'max': None, 'batch': 20, 'timeout': 60, 'exe': None,
            'report': None, 'verbose': False}
    rest = []
    i = 0
    while i < len(args):
        a = args[i]
        if a == '--files':
            opts['files'].append(args[i + 1]); i += 2
        elif a in ('--max', '--batch', '--timeout'):
            opts[a[2:]] = int(args[i + 1]); i += 2
        elif a in ('--exe', '--report'):
            opts[a[2:]] = args[i + 1]; i += 2
        elif a == '--verbose':
            opts['verbose'] = True; i += 1
        else:
            rest.append(a); i += 1
    if len(rest) != 1:
        print(__doc__)
        sys.exit(1)
    exe = opts['exe'] or ('./rewrite.exe' if os.path.exists('rewrite.exe') else './rewrite')

    files = []
    for root, _, names in os.walk(rest[0]):
        for n in names:
            if n.endswith('.m') and (not opts['files'] or any(t in n for t in opts['files'])):
                files.append(os.path.join(root, n))
    files.sort()

    totals = {}
    report = open(opts['report'], 'w', encoding='utf-8', newline='\n') if opts['report'] else None
    t0 = time.time()
    for path in files:
        fname = os.path.basename(path)
        probs = []
        for no, text in problems_of(path):
            if opts['max'] and len(probs) >= opts['max']:
                break
            key = '%s:%d' % (re.sub(r'\W+', '_', fname)[:30], no)
            try:
                e = r2r.parse(text)
                if e[0] != 'call' or e[1] != 'List' or len(e[2]) < 2 or e[2][1][0] != 'sym':
                    raise Skip('unusual problem')
                var = e[2][1][1]
                params = set()
                integrand = to_rw(e[2][0], var, params)
                f_py = to_py(e[2][0], var)
            except (Skip, r2r.Untranslatable, RecursionError) as err:
                probs.append((key, text, None, None, None, 'skipped', str(err)))
                continue
            probs.append((key, text, integrand, f_py, params, None, None))

        counts = {}
        todo = [p for p in probs if p[5] is None]
        results = {}
        for b in range(0, len(todo), opts['batch']):
            batch = todo[b:b + opts['batch']]
            found, broken = run_batch(exe, [(p[0], p[2], p[4]) for p in batch], opts['timeout'])
            for p in batch:
                if p[0] not in found and (broken or len(batch) > 1):
                    # crash or time out in this batch: run the problem alone
                    one, _ = run_batch(exe, [(p[0], p[2], p[4])], min(opts['timeout'], 20))
                    found.update(one)
            for p in batch:
                if p[0] in found:
                    results[p[0]] = classify(found[p[0]], p[3], p[4])
                else:
                    results[p[0]] = ('failed', 'crash or timeout')
        for p in probs:
            status, info = (p[5], p[6]) if p[5] else results[p[0]]
            counts[status] = counts.get(status, 0) + 1
            totals[status] = totals.get(status, 0) + 1
            line = '%-10s %s  %s  ->  %s' % (status, p[0], p[1][:200], (info or ''))
            if report:
                report.write(line + '\n')
            if opts['verbose']:
                print(line)
        print('%-60s %s' % (fname[:60], '  '.join('%s %d' % kv for kv in sorted(counts.items()))))
        sys.stdout.flush()
    if report:
        report.close()
    n = sum(totals.values())
    tested = n - totals.get('skipped', 0)
    print('\ntotal %d problems (%.0f s):' % (n, time.time() - t0))
    for k in ('solved', 'wrong', 'unverified', 'unsolved', 'failed', 'skipped'):
        v = totals.get(k, 0)
        print('  %-11s %6d  (%5.1f%% of %s)' % (k, v, 100.0 * v / max(1, tested if k != 'skipped' else n),
                                                 'tested' if k != 'skipped' else 'all'))


if __name__ == '__main__':
    main()
