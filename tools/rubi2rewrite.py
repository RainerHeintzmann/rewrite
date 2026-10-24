#!/usr/bin/env python3
"""
rubi2rewrite.py -- translate Rubi integration rules into rewrite rules.

Rubi (https://github.com/RuleBasedIntegration/Rubi, MIT license) states its
rules in Mathematica syntax, for example

    Int[(a_. + b_.*x_)^m_, x_Symbol] := (a + b*x)^(m + 1)/(b*(m + 1)) /;
        FreeQ[{a, b, m}, x] && NeQ[m, -1]

This script parses such rules and writes rewrite rules like

    ADDSPEC RubiRules : IF NIN(Xv,O_a,O_b,P_m), (neq(P_m,(-1))) \
        Int((O_a+O_b*Xv)^P_m,Xv) = ...

Rules that use constructs or functions which rewrite does not have are not
translated; the output file lists them with the reason.

Usage:
    rubi2rewrite.py RUBI_RULE_DIR OUT_DIR [--order RUBI_M] [--stats]

RUBI_RULE_DIR contains the rule files "*.m" of Rubi (Rubi/IntegrationRules,
the sub-folders are searched too). With --order, the file Rubi/Rubi.m gives
the files and their order, exactly as Rubi loads them; otherwise all files
are used in the order of their section numbers.
For every rule file one rewrite file is written to OUT_DIR, together with
"declarations", a loader "all" and a summary "STATISTICS.txt".
"""

import os
import re
import sys
from fractions import Fraction

# ======================================================================
#  Lexer
# ======================================================================

TOKEN_RE = re.compile(r'''
    (?P<ws>\s+)
  | (?P<num>\d+\.\d*|\.\d+|\d+)
  | (?P<pat>[A-Za-z$][A-Za-z0-9$]*_(?:\.|[A-Za-z][A-Za-z0-9]*)?)
  | (?P<id>[A-Za-z$][A-Za-z0-9$]*)
  | (?P<op>:=|/;|->|===|==|!=|<=|>=|&&|\|\||[-+*/^<>!=,\[\](){};])
''', re.X)


class Untranslatable(Exception):
    """Raised for rules that cannot be translated; the message is the reason."""


def tokenize(s):
    s = s.replace('\\[Star]', '*')     # Rubi's u \[Star] v = Dist[u,v,x] = u*v
    pos, out = 0, []
    while pos < len(s):
        m = TOKEN_RE.match(s, pos)
        if not m:
            raise Untranslatable("unknown character %r" % s[pos])
        pos = m.end()
        kind = m.lastgroup
        if kind == 'ws':
            continue
        out.append((kind, m.group(kind)))
    out.append(('eof', ''))
    return out

# ======================================================================
#  Parser (Pratt) -> nested tuples
#   ('num', Fraction) | ('sym', name) | ('pat', name, optional, head)
#   ('call', head, [args])   with heads Plus, Times, Power, ... as in
#   Mathematica's FullForm
# ======================================================================

INFIX = {
    ';': 1, '=': 2, '/;': 2, '->': 3, '||': 4, '&&': 5,
    '==': 7, '!=': 7, '===': 7, '<': 7, '>': 7, '<=': 7, '>=': 7,
    '+': 10, '-': 10, '*': 20, '/': 20, '^': 30, '[': 40,
}
COMPARE = {'==': 'Equal', '!=': 'Unequal', '===': 'SameQ', '<': 'Less',
           '>': 'Greater', '<=': 'LessEqual', '>=': 'GreaterEqual'}


def call(head, *args):
    return ('call', head, list(args))


NEG1 = ('num', Fraction(-1))


class Parser:
    def __init__(self, toks):
        self.t, self.i = toks, 0

    def peek(self):
        return self.t[self.i]

    def next(self):
        tok = self.t[self.i]
        self.i += 1
        return tok

    def expect(self, v):
        k, val = self.next()
        if val != v:
            raise Untranslatable("parse error: expected %r, got %r" % (v, val))

    def lbp(self):
        k, v = self.peek()
        if k == 'op' and v in INFIX:
            return INFIX[v]
        if k in ('num', 'id', 'pat') or (k == 'op' and v == '('):
            return 20            # implicit multiplication
        return 0

    def parse(self, rbp=0):
        left = self.nud()
        while self.lbp() > rbp:
            left = self.led(left)
        return left

    def nud(self):
        k, v = self.next()
        if k == 'num':
            return ('num', Fraction(v))
        if k == 'id':
            return ('sym', v)
        if k == 'pat':
            name, rest = v.split('_', 1)
            return ('pat', name, rest == '.', rest if rest not in ('', '.') else None)
        if v == '(':
            e = self.parse(0)
            self.expect(')')
            return e
        if v == '{':
            items = []
            if self.peek()[1] != '}':
                while True:
                    items.append(self.parse(1))
                    if self.peek()[1] == ',':
                        self.next()
                        continue
                    break
            self.expect('}')
            return call('List', *items)
        if v == '-':
            return call('Times', NEG1, self.parse(25))
        if v == '+':
            return self.parse(25)
        if v == '!':
            return call('Not', self.parse(7))
        raise Untranslatable("parse error at %r" % v)

    def led(self, left):
        k, v = self.peek()
        if not (k == 'op' and v in INFIX):           # implicit multiplication
            return call('Times', left, self.parse(20))
        self.next()
        if v == '+':
            return call('Plus', left, self.parse(10))
        if v == '-':
            return call('Plus', left, call('Times', NEG1, self.parse(10)))
        if v == '*':
            return call('Times', left, self.parse(20))
        if v == '/':
            return call('Times', left, call('Power', self.parse(20), NEG1))
        if v == '^':
            return call('Power', left, self.parse(29))
        if v == '[':
            if left[0] == 'pat' and left[3] is None:      # F_[u]: function variable
                head = '?' + left[1]
            elif left[0] != 'sym':
                raise Untranslatable("call of a non-symbol")
            else:
                head = left[1]
            args = []
            if self.peek()[1] != ']':
                while True:
                    args.append(self.parse(1))
                    if self.peek()[1] == ',':
                        self.next()
                        continue
                    break
            self.expect(']')
            return ('call', head, args)
        if v in COMPARE:
            return call(COMPARE[v], left, self.parse(7))
        if v == '&&':
            return call('And', left, self.parse(5))
        if v == '||':
            return call('Or', left, self.parse(4))
        if v == '->':
            return call('Rule', left, self.parse(2))
        if v == '/;':
            return call('Condition', left, self.parse(2))
        if v == '=':
            return call('Set', left, self.parse(1))
        if v == ';':
            raise Untranslatable("compound expression (;)")
        raise Untranslatable("operator %r" % v)


def parse(s):
    p = Parser(tokenize(s))
    e = p.parse(0)
    if p.peek()[0] != 'eof':
        raise Untranslatable("parse error near %r" % p.peek()[1])
    return e

# ======================================================================
#  Normalization: flat Plus/Times, numbers folded, Sqrt -> Power
# ======================================================================

# helper functions defined in the rule files themselves, e.g.
#   IntBinomialQ[a_, b_, c_, n_, m_, p_, x_] := IGtQ[p, 0] || ...
# They are inlined ((name, arity) -> (parameter names, body)).
MACROS = {}
_macro_depth = [0]


def is_num(e):
    return e[0] == 'num'


def normalize(e):
    if e[0] != 'call':
        return e
    head, args = e[1], [normalize(a) for a in e[2]]
    if head in ('Plus', 'Times', 'And', 'Or'):
        flat = []
        for a in args:
            if a[0] == 'call' and a[1] == head:
                flat.extend(a[2])
            else:
                flat.append(a)
        args = flat
        if head == 'Times':
            nums = [a for a in args if is_num(a)]
            rest = [a for a in args if not is_num(a)]
            if len(nums) > 1 or (nums and nums[0][1] == 1 and rest):
                c = Fraction(1)
                for n in nums:
                    c *= n[1]
                args = ([('num', c)] if c != 1 or not rest else []) + rest
            if len(args) == 1:
                return args[0]
    if head == 'ActivateTrig' and len(args) == 1:      # trig is always active here
        return args[0]
    if head == 'DeactivateTrig' and len(args) == 2:
        return args[0]
    if head == 'Log' and len(args) == 2:              # Log[b, z] = Log[z]/Log[b]
        return normalize(call('Times', call('Log', args[1]),
                              call('Power', call('Log', args[0]), ('num', Fraction(-1)))))
    if (head, len(args)) in MACROS and _macro_depth[0] < 20:
        params, body = MACROS[(head, len(args))]
        _macro_depth[0] += 1
        try:
            return normalize(resolve_with(substitute(body, dict(zip(params, args)))))
        finally:
            _macro_depth[0] -= 1
    if head == 'Sqrt' and len(args) == 1:
        return normalize(call('Power', args[0], ('num', Fraction(1, 2))))
    if head == 'Exp' and len(args) == 1:
        return call('Power', ('sym', 'E'), args[0])
    if head == 'Power' and len(args) == 2 and is_num(args[0]) and is_num(args[1]):
        b, x = args[0][1], args[1][1]
        if x.denominator == 1 and b != 0:
            return ('num', b ** int(x))
    if (head == 'Power' and len(args) == 2 and is_num(args[1])
            and args[1][1].denominator == 1 and args[0][0] == 'call'
            and args[0][1] == 'Power' and is_num(args[0][2][1])):
        # (u^p)^n = u^(p n) for integer n, as Mathematica does automatically
        return normalize(call('Power', args[0][2][0],
                              ('num', args[0][2][1][1] * args[1][1])))
    if (head == 'Power' and len(args) == 2 and is_num(args[1])
            and args[1][1].denominator == 1 and args[0][0] == 'call'
            and args[0][1] == 'Times'):
        # (u v)^n = u^n v^n for integer n, as Mathematica does automatically:
        # 1/((a+b x) (c+d x)) is Times[Power[a+b x,-1], Power[c+d x,-1]]
        return normalize(call('Times', *[call('Power', f, args[1]) for f in args[0][2]]))
    return ('call', head, args)


def substitute(e, defs):
    """replace symbols by expressions (for With)"""
    if e[0] == 'sym' and e[1] in defs:
        return defs[e[1]]
    if e[0] == 'call':
        return ('call', e[1], [substitute(a, defs) for a in e[2]])
    return e


def resolve_with(e):
    """With[{q = u, ...}, body] -> body with q replaced by u"""
    if e[0] != 'call':
        return e
    if e[1] in ('With', 'Module'):     # a Module that only defines values is a With
        if len(e[2]) != 2 or e[2][0][0] != 'call' or e[2][0][1] != 'List':
            raise Untranslatable("%s with unusual form" % e[1])
        defs = {}
        for d in e[2][0][2]:
            if d[0] != 'call' or d[1] != 'Set' or d[2][0][0] != 'sym':
                raise Untranslatable("%s with a local variable without value" % e[1])
            defs[d[2][0][1]] = resolve_with(substitute(d[2][1], defs))
        return resolve_with(substitute(e[2][1], defs))
    return ('call', e[1], [resolve_with(a) for a in e[2]])

# ======================================================================
#  Translation into rewrite syntax
# ======================================================================

# Mathematica function -> rewrite function (name, number of arguments or None)
FUNCS = {
    'Sin': 'sin', 'Cos': 'cos', 'Tan': 'tan', 'Cot': 'cot', 'Sec': 'sec',
    'Csc': 'csc', 'ArcSin': 'arcsin', 'ArcCos': 'arccos', 'ArcTan': 'arctan',
    'ArcCot': 'arccot', 'Sinh': 'sinh', 'Cosh': 'cosh', 'Tanh': 'tanh',
    'Coth': 'coth', 'Sech': 'sech', 'Csch': 'csch', 'ArcSinh': 'arcsinh',
    'ArcCosh': 'arccosh', 'ArcTanh': 'arctanh', 'ArcCoth': 'arccoth',
    'Log': 'ln', 'PolyLog': 'polylog', 'ProductLog': 'productlog',
    'Abs': 'abs',
    # special functions (inc/alg, specfun.c)
    'ArcSec': 'arcsec', 'ArcCsc': 'arccsc', 'ArcSech': 'arcsech', 'ArcCsch': 'arccsch',
    'Erf': 'erf', 'Erfc': 'erfc', 'Erfi': 'erfi', 'FresnelS': 'fresnels',
    'FresnelC': 'fresnelc', 'SinIntegral': 'sinint', 'CosIntegral': 'cosint',
    'SinhIntegral': 'sinhint', 'CoshIntegral': 'coshint', 'ExpIntegralEi': 'expint',
    'ExpIntegralE': 'expinte', 'LogIntegral': 'logint', 'Gamma': 'Gamma',
    'LogGamma': 'loggamma', 'PolyGamma': 'polygamma', 'Zeta': 'zeta',
    'EllipticK': 'elliptick', 'EllipticF': 'ellipticf', 'EllipticE': 'elliptice',
    'EllipticPi': 'ellipticpi', 'Hypergeometric2F1': 'hyp2f1', 'AppellF1': 'appellf1',
    'BesselJ': 'besselj',
    # Rubi's inert trig functions (lower case) in the trig sections
    'sin': 'sin', 'cos': 'cos', 'tan': 'tan', 'cot': 'cot', 'sec': 'sec', 'csc': 'csc',
}
# helper functions on the right-hand side
RHS_HELPERS = {
    'Int': 'Int', 'Simp': 'simp', 'Simplify': 'simplify', 'Dist': 'dist',
    'FullSimplify': 'simplify',
    'Subst': 'subst', 'ExpandIntegrand': 'expandintegrand', 'Expand': 'expand',
    'Coeff': 'coeff', 'Coefficient': 'coeff', 'Expon': 'expon', 'Rt': 'rt',
    'IntPart': 'intpart', 'FracPart': 'fracpart', 'IntHide': 'inthide',
    'Unintegrable': 'unintegrable', 'D': 'deriv',
    'GCD': 'gcd', 'Numerator': 'numerator', 'Denominator': 'denominator',
    'Denom': 'denominator', 'FreeFactors': 'freefactors',
    'NonfreeFactors': 'nonfreefactors', 'ExpandToSum': 'expandtosum',
    'PolynomialQuotient': 'polyquotient', 'PolynomialRemainder': 'polyremainder',
    'SimplifyIntegrand': 'simp',
    'ExpandTrig': 'expandintegrand', 'ExpandTrigReduce': 'expandtrigreduce',
    'LeafCount': 'leafcount', 'BinomialDegree': 'binomialdegree',
    'Numer': 'numerator', 'SubstFor': 'substfor', 'DerivativeDivides': 'derivdivides',
}
# predicates in conditions
PREDICATES = {
    'EqQ': 'eqq', 'NeQ': 'neq', 'IntegerQ': 'integerq', 'IntegersQ': 'integersq',
    'RationalQ': 'rationalq', 'PosQ': 'posq', 'NegQ': 'negq', 'IGtQ': 'igtq',
    'ILtQ': 'iltq', 'PolyQ': 'polyq', 'LinearQ': 'linearq', 'SumQ': 'sumq', 'NonsumQ': 'nonsumq',
    'ProductQ': 'productq', 'PowerQ': 'powerq',
    'FractionQ': 'fractionq', 'HalfIntegerQ': 'halfintegerq',
    'PolynomialQ': 'polyq', 'NiceSqrtQ': 'nicesqrtq',
    'BinomialQ': 'binomialq', 'QuadraticQ': 'quadraticq',
    'RationalFunctionQ': 'rationalfunctionq', 'InverseFunctionFreeQ': 'inversefunctionfreeq',
    'FunctionOfQ': 'functionofq', 'FalseQ': 'falseq',
    'SimplerQ': 'simplerq', 'SumSimplerQ': 'sumsimplerq', 'SimplerSqrtQ': 'simplersqrtq',
    'KnownSineIntegrandQ': 'knownsineintegrandq', 'KnownTangentIntegrandQ': 'knowntangentintegrandq',
    'KnownCotangentIntegrandQ': 'knowncotangentintegrandq',
    'KnownSecantIntegrandQ': 'knownsecantintegrandq',
    'PiecewiseLinearQ': 'piecewiselinearq', 'LinearMatchQ': 'linearmatchq',
    'BinomialMatchQ': 'binomialmatchq', 'QuadraticMatchQ': 'quadraticmatchq',
    'TrinomialQ': 'trinomialq', 'IndependentQ': 'freeq', 'LinearPairQ': 'linearpairq',
    'AlgebraicFunctionQ': 'algebraicfunctionq',
}
ORDER = {'GtQ': '>', 'LtQ': '<', 'GeQ': '>=', 'LeQ': '<='}
CONSTANTS = {'Pi': 'pi', 'E': 'eE', 'True': '1', 'False': '0'}


def fmt_num(q):
    if q.denominator == 1:
        return str(q.numerator)
    return repr(float(q))


class Ctx:
    """per rule: pattern variables, numeric placeholders, conditions"""

    def __init__(self):
        self.pvars = {}          # Mathematica name -> rewrite name
        self.xname = None        # name of the integration variable
        self.kvars = []          # NUM placeholders for negative numbers
        self.extra = []          # extra conditions (placeholders)

    def var(self, name, optional):
        if name == self.xname:
            return 'Xv'
        if name not in self.pvars:
            self.pvars[name] = ('O_' if optional else 'P_') + name
        return self.pvars[name]

    def knum(self, q):
        k = 'K_%d' % (len(self.kvars) + 1)
        self.kvars.append(k)
        self.extra.append('(%s == %s)' % (k, fmt_rhs_num(q)))
        return k


def fmt_rhs_num(q):
    if q < 0:
        return '(-%s)' % fmt_rhs_num(-q)
    if q.denominator == 1:
        return str(q.numerator)
    return '(%d/%d)' % (q.numerator, q.denominator)


def paren(s):
    return '(' + s + ')'


def tr_lhs(e, ctx):
    """pattern on the left side"""
    kind = e[0]
    if kind == 'num':
        q = e[1]
        if q < 0:
            return ctx.knum(q)
        return fmt_num(q)
    if kind == 'pat':
        name, optional, head = e[1], e[2], e[3]
        if head == 'Symbol':
            ctx.xname = name
            return 'Xv'
        if head is not None:
            raise Untranslatable("typed pattern %s_%s" % (name, head))
        return ctx.var(name, optional)
    if kind == 'sym':
        if e[1] in ctx.pvars or e[1] == ctx.xname:
            return ctx.var(e[1], False)
        if e[1] == 'Pi':
            return repr(3.141592653589793)
        if e[1] == 'E':
            return 'eE'                  # symbolic e (inc/integration/base)
        raise Untranslatable("symbol %s in pattern" % e[1])
    head, args = e[1], e[2]
    if head == 'Plus':
        return '+'.join(paren(tr_lhs(a, ctx)) for a in args)
    if head == 'Times':
        return '*'.join(paren(tr_lhs(a, ctx)) for a in args)
    if head == 'Power':
        if args[0] == ('sym', 'E'):
            # E^u: the symbolic constant eE, as Mathematica's E
            return 'eE^' + paren(tr_lhs(args[1], ctx))
        return paren(tr_lhs(args[0], ctx)) + '^' + paren(tr_lhs(args[1], ctx))
    if head in FUNCS:
        return FUNCS[head] + paren(','.join(tr_lhs(a, ctx) for a in args))
    raise Untranslatable("function %s in pattern" % head)


def tr_rhs(e, ctx):
    """expression on the right side or in a condition"""
    kind = e[0]
    if kind == 'num':
        return fmt_rhs_num(e[1])
    if kind == 'pat':
        raise Untranslatable("pattern on the right side")
    if kind == 'sym':
        n = e[1]
        if n == ctx.xname:
            return 'Xv'
        if n in ctx.pvars:
            return ctx.pvars[n]
        if n in CONSTANTS:
            return CONSTANTS[n]
        raise Untranslatable("symbol %s" % n)
    head, args = e[1], e[2]
    if head == 'Plus':
        return paren('+'.join(paren(tr_rhs(a, ctx)) for a in args))
    if head == 'Times':
        return paren('*'.join(paren(tr_rhs(a, ctx)) for a in args))
    if head == 'Power':
        if args[0] == ('sym', 'E'):
            return paren('eE^' + paren(tr_rhs(args[1], ctx)))
        return paren(paren(tr_rhs(args[0], ctx)) + '^' + paren(tr_rhs(args[1], ctx)))
    if head in FUNCS:
        return FUNCS[head] + paren(','.join(tr_rhs(a, ctx) for a in args))
    if head == 'Subst' and len(args) == 2 and args[1][0] == 'call' and args[1][1] == 'Rule':
        args = [args[0]] + args[1][2]
    if (head == 'Subst' and len(args) == 3 and args[0][0] == 'call' and args[0][1] == 'Int'
            and len(args[0][2]) == 2 and args[0][2][1] == args[1]):
        # Subst[Int[u, x], x, v]: integrate in a fresh variable (nonneg for roots)
        return 'intsubst' + paren(','.join(tr_rhs(a, ctx) for a in [args[0][2][0], args[1], args[2]]))
    if head == 'ReplaceAll' and len(args) == 2 and args[1][0] == 'call' and args[1][1] == 'Rule':
        return 'replaceall' + paren(','.join(tr_rhs(a, ctx) for a in [args[0]] + args[1][2]))
    if head == 'RemoveContent' and len(args) == 2:
        # without constant factors, also the sign of cos(pi/2+u) = -sin(u):
        # ln(sin x), not ln(-sin x)
        return 'removecontent' + paren(','.join(tr_rhs(a, ctx) for a in args))
    if head in RHS_HELPERS:
        return RHS_HELPERS[head] + paren(','.join(tr_rhs(a, ctx) for a in args))
    if head in PREDICATES or head in ORDER or head in ('And', 'Or', 'Not', 'FreeQ'):
        return tr_bool(e, ctx)
    raise Untranslatable("function %s" % head)


def tr_bool(e, ctx):
    """boolean expression (inside conditions)"""
    if e[0] == 'sym' and e[1] in ('True', 'False'):
        return 'true' if e[1] == 'True' else 'false'
    if e[0] != 'call':
        raise Untranslatable("non-boolean condition")
    head, args = e[1], e[2]
    if head == 'And':
        return paren(' && '.join(paren(tr_bool(a, ctx)) for a in args))
    if head == 'Or':
        return paren(' || '.join(paren(tr_bool(a, ctx)) for a in args))
    if head == 'Not':
        return 'not' + paren(tr_bool(args[0], ctx))
    if head == 'TrueQ':                      # only $UseGamma etc.: False
        return 'false'
    if head == 'FreeQ':
        items = args[0][2] if args[0][0] == 'call' and args[0][1] == 'List' else [args[0]]
        x = tr_rhs(args[1], ctx)
        return paren(' && '.join('freeq(%s,%s)' % (tr_rhs(i, ctx), x) for i in items))
    if head in ('EqQ', 'NeQ') and len(args) != 2:
        # invalid in Rubi too (CheckArguments gives Null): the rule never applies
        raise Untranslatable("%s with %d arguments (never true in Rubi either)" % (head, len(args)))
    if head in PREDICATES and args and args[0][0] == 'call' and args[0][1] == 'List':
        # P[{u, v}, x] = P[u, x] && P[v, x]
        return paren(' && '.join(paren(tr_bool(('call', head, [item] + args[1:]), ctx))
                                 for item in args[0][2]))
    if head in PREDICATES:
        return PREDICATES[head] + paren(','.join(tr_rhs(a, ctx) for a in args))
    if head in ORDER:
        # gtq(u,v), ...: false unless both are numbers, as Rubi's GtQ
        # (so that Not[GtQ[a^2,0]] is true for a symbol a)
        fn = {'GtQ': 'gtq', 'LtQ': 'ltq', 'GeQ': 'geq', 'LeQ': 'leq'}[head]
        parts = [tr_rhs(a, ctx) for a in args]
        pairs = ['(%s(%s,%s))' % (fn, parts[i], parts[i + 1]) for i in range(len(parts) - 1)]
        return paren(' && '.join(pairs))
    if head in ('Equal', 'Unequal', 'Less', 'Greater', 'LessEqual', 'GreaterEqual'):
        op = {'Equal': '==', 'Unequal': '!=', 'Less': '<', 'Greater': '>',
              'LessEqual': '<=', 'GreaterEqual': '>='}[head]
        return '(%s %s %s)' % (tr_rhs(args[0], ctx), op, tr_rhs(args[1], ctx))
    raise Untranslatable("predicate %s" % head)


def simplify_bool(e):
    """remove the always-false TrueQ[$UseGamma] parts"""
    if e[0] != 'call':
        return e
    head, args = e[1], [simplify_bool(a) for a in e[2]]
    if head == 'TrueQ':
        return ('sym', 'False')
    if head == 'Not' and args[0] == ('sym', 'False'):
        return ('sym', 'True')
    if head == 'Not' and args[0] == ('sym', 'True'):
        return ('sym', 'False')
    if head == 'And':
        if ('sym', 'False') in args:
            return ('sym', 'False')
        args = [a for a in args if a != ('sym', 'True')]
        if not args:
            return ('sym', 'True')
        if len(args) == 1:
            return args[0]
    if head == 'Or':
        if ('sym', 'True') in args:
            return ('sym', 'True')
        args = [a for a in args if a != ('sym', 'False')]
        if not args:
            return ('sym', 'False')
        if len(args) == 1:
            return args[0]
    return ('call', head, args)


def tr_conditions(e, ctx):
    """top-level condition -> list of rewrite conditions"""
    e = simplify_bool(e)
    if e == ('sym', 'True'):
        return []
    if e == ('sym', 'False'):
        raise Untranslatable("condition is never true")
    if e[0] == 'call' and e[1] == 'And':
        out = []
        for a in e[2]:
            out.extend(tr_conditions(a, ctx))
        return out
    if e[0] == 'call' and e[1] == 'FreeQ' and e[2][1] == ('sym', ctx.xname):
        items = e[2][0][2] if e[2][0][0] == 'call' and e[2][0][1] == 'List' else [e[2][0]]
        return ['NIN(Xv,%s)' % ','.join(tr_rhs(i, ctx) for i in items)]
    return [paren(tr_bool(e, ctx))]

# ======================================================================
#  Number of variants of a pattern (as expand.c would create)
# ======================================================================

def count_variants(e):
    """e: normalized pattern; Plus/Times are binarized left to right"""
    def opt(a):
        return a[0] == 'pat' and a[2]

    def binary(head, args, comm):
        c = count_variants(args[0])
        left = args[0]
        for a in args[1:]:
            ca, cb = c, count_variants(a)
            c = ca * cb * (2 if comm else 1)
            if opt(left) and not opt(a):
                c += cb
            if opt(a) and not opt(left):
                c += ca
            left = ('call', head, [left, a])
        return c

    if e[0] != 'call':
        return 1
    head, args = e[1], e[2]
    if head in ('Plus', 'Times'):
        return binary(head, args, True)
    if head == 'Power':
        c = count_variants(args[0]) * count_variants(args[1])
        if opt(args[1]):
            c += count_variants(args[0])
        return c
    c = 1
    for a in args:
        c *= count_variants(a)
    return c

# ======================================================================
#  One rule
# ======================================================================

def split_top(s, sep):
    """split s at the first top-level occurrence of sep"""
    depth = 0
    for i in range(len(s)):
        ch = s[i]
        if ch in '[({':
            depth += 1
        elif ch in '])}':
            depth -= 1
        elif depth == 0 and s.startswith(sep, i):
            return s[:i], s[i + len(sep):]
    return s, None


# function variables F_[...]: the admissible functions, from the condition
FUNCTION_SETS = {
    'TrigQ': ['Sin', 'Cos', 'Tan', 'Cot', 'Sec', 'Csc'],
    'InertTrigQ': ['sin', 'cos', 'tan', 'cot', 'sec', 'csc'],
    'HyperbolicQ': ['Sinh', 'Cosh', 'Tanh', 'Coth', 'Sech', 'Csch'],
    'InverseTrigQ': ['ArcSin', 'ArcCos', 'ArcTan', 'ArcCot', 'ArcSec', 'ArcCsc'],
    'InverseHyperbolicQ': ['ArcSinh', 'ArcCosh', 'ArcTanh', 'ArcCoth', 'ArcSech', 'ArcCsch'],
}


def function_vars(e, out):
    if e[0] == 'call':
        if e[1].startswith('?'):
            out.add(e[1][1:])
        for a in e[2]:
            function_vars(a, out)
    return out


def function_sets(conds, fvars):
    """{F: [admissible heads]} from predicates like TrigQ[F], MemberQ[{..}, F]"""
    sets = {}

    def scan(e):
        if e[0] != 'call':
            return
        h, args = e[1], e[2]
        if h in FUNCTION_SETS and len(args) == 1 and args[0][0] == 'sym' and args[0][1] in fvars:
            sets[args[0][1]] = FUNCTION_SETS[h]
        elif (h == 'MemberQ' and len(args) == 2 and args[1][0] == 'sym' and args[1][1] in fvars
              and args[0][0] == 'call' and args[0][1] == 'List'
              and all(a[0] == 'sym' for a in args[0][2])):
            sets[args[1][1]] = [a[1] for a in args[0][2]]
        elif h in ('EqQ', 'Or'):           # EqQ[F, Cos] || EqQ[F, cos]
            alts = [e] if h == 'EqQ' else args
            if all(a[0] == 'call' and a[1] == 'EqQ' and len(a[2]) == 2
                   and a[2][0][0] == 'sym' and a[2][0][1] in fvars
                   and a[2][1][0] == 'sym' for a in alts) \
                    and len(set(a[2][0][1] for a in alts)) == 1:
                sets[alts[0][2][0][1]] = [a[2][1][1] for a in alts]
        if h == 'And':
            for a in args:
                scan(a)
    for c in conds:
        scan(c)
    return sets


def instantiate(e, assign):
    """F_[u] -> Sin[u] for F = Sin; the predicates on F become True"""
    if e[0] == 'sym' and e[1] in assign:
        return ('sym', assign[e[1]])
    if e[0] != 'call':
        return e
    h, args = e[1], e[2]
    if h.startswith('?') and h[1:] in assign:
        h = assign[h[1:]]
    elif h in assign:                       # F[u] on the right-hand side
        h = assign[h]
    if ((h in FUNCTION_SETS and len(args) == 1 and args[0][0] == 'sym' and args[0][1] in assign)
            or (h == 'MemberQ' and len(args) == 2 and args[1][0] == 'sym' and args[1][1] in assign)):
        return ('sym', 'True')
    if (h == 'EqQ' and len(args) == 2 and args[0][0] == 'sym' and args[0][1] in assign
            and args[1][0] == 'sym'):
        return ('sym', 'True' if assign[args[0][1]] == args[1][1] else 'False')
    return ('call', h, [instantiate(a, assign) for a in args])


# extra conditions for rules that are only valid in real numbers under a
# condition: Mathematica calculates with complex intermediate values
REAL_CONDITIONS = [
    # Cardano: the square root of the discriminant must be real
    ('Sqrt[4*b^3*d+27*a^2*d^2]', 'PosQ[4*b^3*d+27*a^2*d^2]'),
]


def translate_rule(text):
    """returns a list of (rewrite rule, number of variants, ctx); raises
    Untranslatable. A rule with function variables F_[...] gives one rule
    per admissible function."""
    for key, cond in REAL_CONDITIONS:
        if key in text and '/;' in text:
            text = text.rstrip() + ' && ' + cond
    lhs_s, rhs_s = split_top(text, ':=')
    if rhs_s is None:
        raise Untranslatable("not a rule")
    for bad in ('If[', 'Block[', 'ShowStep', 'Map[', 'Function['):
        if bad in rhs_s:
            raise Untranslatable(bad.rstrip('['))
    lhs = normalize(parse(lhs_s))
    rhs = normalize(resolve_with(parse(rhs_s)))
    if lhs[0] != 'call' or lhs[1] != 'Int' or len(lhs[2]) != 2:
        raise Untranslatable("left side is not Int[u, x]")
    fvars = function_vars(lhs, set())
    if not fvars:
        return [translate_parsed(lhs, rhs)]
    conds = []
    r = rhs
    while r[0] == 'call' and r[1] == 'Condition':
        conds.append(r[2][1])
        r = r[2][0]
    sets = function_sets(conds, fvars)
    if any(f not in sets for f in fvars):
        raise Untranslatable("function variable without a finite set of functions")
    combos = [{}]
    for f in sorted(fvars):
        combos = [dict(c, **{f: g}) for c in combos for g in sets[f]]
    out = []
    for assign in combos:
        try:
            r = translate_parsed(normalize(instantiate(lhs, assign)),
                                 normalize(instantiate(rhs, assign)))
            if all(r[0] != o[0] for o in out):     # Cos and cos: the same rule
                out.append(r)
        except Untranslatable:
            pass                    # e.g. a function rewrite does not have
    if not out:
        raise Untranslatable("no instance of the function variable translatable")
    return out


def default_guards(pattern, result, conds, ctx):
    """An optional variable b_. that occurs neither in the conditions nor in
    the result can only have its default value: Mathematica writes
    (b*tan[u])^3 as b^3*tan[u]^3, so Rubi's pattern (b_.*tan[u])^n_ sees
    b = 1 there. rewrite keeps (-tan(u))^3, so the rule must check it."""
    out = []
    used = result + ' ' + ' '.join(conds)
    for v in sorted(set(ctx.pvars.values())):
        if not v.startswith('O_') or re.search(r'\b%s\b' % v, used):
            continue
        r = re.escape('(%s)' % v)
        if re.search(r'\+' + r + '|' + r + r'\+', pattern):
            out.append('(eqq(%s,0))' % v)
        elif re.search(r'[*^]' + r + '|' + r + r'\*', pattern):
            out.append('(eqq(%s,1))' % v)
    return out


def translate_parsed(lhs, rhs):

    conds_ast = []
    while rhs[0] == 'call' and rhs[1] == 'Condition':     # rhs /; cond
        conds_ast.append(rhs[2][1])
        rhs = rhs[2][0]
    if 'Condition' in repr(rhs):
        raise Untranslatable("condition inside the right side")

    ctx = Ctx()
    x = tr_lhs(lhs[2][1], ctx)         # first: sets the integration variable
    integrand = tr_lhs(lhs[2][0], ctx)
    if x != 'Xv':
        raise Untranslatable("integration variable is not x_Symbol")
    pattern = 'Int(%s,Xv)' % integrand
    result = tr_rhs(rhs, ctx)
    conds = []
    for c in conds_ast:
        conds.extend(tr_conditions(normalize(c), ctx))
    conds = ctx.extra + conds
    conds += default_guards(pattern, result, conds, ctx)
    rule = 'ADDSPEC RubiRules : '
    if conds:
        rule += 'IF ' + ', '.join(conds) + ' '
    rule += pattern + ' = ' + result
    return rule, count_variants(lhs[2][0]), ctx

# ======================================================================
#  Files
# ======================================================================

HEADER = """# %s
# Automatisch uebersetzt aus Rubi 4.17.3 (github.com/RuleBasedIntegration/Rubi)
# mit tools/rubi2rewrite.py, Abschnitt
#   %s
# Copyright (c) 2018 Rule-Based-Integration Organization, MIT-Lizenz,
# siehe inc/integration/LICENSE.Rubi.
# Nicht von Hand aendern: Aenderungen gehoeren in das Uebersetzungsprogramm.
"""


def safe_name(path):
    base = os.path.splitext(os.path.basename(path))[0]
    num = base.split(' ', 1)[0]
    if re.fullmatch(r'[0-9.]+[a-z]?', num):
        return 'r' + num.replace('.', '_')
    return 'r_' + re.sub(r'[^A-Za-z0-9]+', '_', base).strip('_')[:40]


CONTINUES = (':=', '/;', '&&', '||', '+', '-', '*', '/', '^', ',', '=', '->', r'\[Star]')


def rules_of(path):
    """A rule may span several lines. It is complete when all brackets are
    closed and the last line does not end with an operator."""
    stmt, depth = None, 0
    with open(path, encoding='utf-8', errors='replace') as f:
        text = f.read()
    text = re.sub(r'\(\*.*?\*\)', ' ', text, flags=re.S)      # comments
    if True:
        for line in text.split('\n'):
            line = line.strip()
            if stmt is None:
                if not line.startswith('Int['):
                    continue
                stmt, depth = line, 0
            else:
                stmt += ' ' + line
            depth += sum(line.count(c) for c in '[({') - sum(line.count(c) for c in '])}')
            # If[TrueQ[$LoadShowSteps], rule with ShowStep, rule without]:
            # the first rule ends with ',', the second with the ']' of If
            if depth <= 0 and stmt.rstrip().endswith(',') and 'ShowStep[' in stmt:
                yield stmt.rstrip()[:-1]
                stmt = None
                continue
            if depth <= 0 and not stmt.rstrip().endswith(CONTINUES):
                while depth < 0 and stmt.rstrip().endswith(']'):
                    stmt = stmt.rstrip()[:-1]
                    depth += 1
                yield stmt
                stmt = None
        if stmt is not None:
            yield stmt


def definitions_of(path):
    """helper definitions Name[a_, b_, ...] := body in a rule file"""
    with open(path, encoding='utf-8', errors='replace') as f:
        text = f.read()
    text = re.sub(r'\(\*.*?\*\)', ' ', text, flags=re.S)      # comments
    stmt, depth = None, 0
    for line in text.split('\n'):
        line = line.strip()
        if stmt is None:
            if not re.match(r'[A-Z][A-Za-z0-9]*\[', line) or line.startswith('Int['):
                continue
            stmt, depth = line, 0
        else:
            stmt += ' ' + line
        depth += sum(line.count(c) for c in '[({') - sum(line.count(c) for c in '])}')
        if depth <= 0 and not stmt.rstrip().endswith(CONTINUES):
            yield stmt
            stmt = None


def collect_macros(files):
    for path in files:
        for text in definitions_of(path):
            lhs_s, rhs_s = split_top(text, ':=')
            if rhs_s is None:
                continue
            try:
                lhs = parse(lhs_s)
                body = parse(rhs_s)
            except Exception:
                continue
            if lhs[0] != 'call' or 'Condition' in repr(body):
                continue
            params = []
            for a in lhs[2]:
                if a[0] != 'pat' or a[2] or a[3] not in (None, 'Symbol'):
                    break
                params.append(a[1])
            else:
                key = (lhs[1], len(params))
                if key not in MACROS and lhs[1] not in PREDICATES \
                        and lhs[1] not in RHS_HELPERS and lhs[1] not in FUNCS:
                    MACROS[key] = (params, body)


# rules that cannot be translated, but whose work a C helper does: the start
# of the Mathematica text -> the rule in rewrite (at the same place in the
# order). The helper stays unevaluated if it does not apply, and the rule
# list then skips the rule (symfkt.c, term_has_nan).
HAND_RULES = [
    # Rubi 2.3: integrand a function of F^(c x): substitute x -> F^(g x)
    ('Int[u_, x_Symbol] := With[{v = FunctionOfExponential[u, x]}',
     'ADDSPEC RubiRules : Int(P_u,Xv) = substexp(P_u,Xv)'),
    # Rubi 9.3: x -> (a+b*x)^(1/n) for fractional powers of a linear function
    ('Int[u_,x_Symbol] := With[{lst=SubstForFractionalPowerOfLinear[u,x]}, lst',
     'ADDSPEC RubiRules : Int(P_u,Xv) = substfracpow(P_u,Xv)'),
    # Rubi 9.3: Euler's substitutions for functions of x and Sqrt[a+b*x+c*x^2]
    ('Int[u_,x_Symbol] := With[{lst=FunctionOfSquareRootOfQuadratic[u,x]}, 2',
     'ADDSPEC RubiRules : Int(P_u,Xv) = substsqrtquad(P_u,Xv)'),
]


def translate_file(path, out_dir, all_vars, stats):
    name = safe_name(path)
    section = os.path.splitext(os.path.basename(path))[0]
    lines = [HEADER % (name, section)]
    ok = 0
    used = set()
    for i, text in enumerate(rules_of(path), 1):
        hand = [r for key, r in HAND_RULES if text.startswith(key)]
        if hand:
            ok += 1
            all_vars['P'].add('P_u')
            if hand[0] in used:         # several cases of one helper: once
                lines.append('# Regel %d (von Hand, wie oben):\n#   %s\n' % (i, text))
            else:
                used.add(hand[0])
                lines.append('# Regel %d (von Hand, C-Hilfsfunktion):\n#   %s\n%s\n' % (i, text, hand[0]))
            continue
        try:
            results = translate_rule(text)
        except Untranslatable as err:
            reason = str(err)
            stats['rejected'][reason] = stats['rejected'].get(reason, 0) + 1
            lines.append('# Regel %d nicht uebersetzt: %s\n#   %s\n' % (i, reason, text))
            continue
        except (RecursionError, IndexError, ZeroDivisionError) as err:
            reason = 'internal: %s' % type(err).__name__
            stats['rejected'][reason] = stats['rejected'].get(reason, 0) + 1
            lines.append('# Regel %d nicht uebersetzt: %s\n#   %s\n' % (i, reason, text))
            continue
        ok += 1
        for k, (rule, nvar, ctx) in enumerate(results):
            all_vars['P'].update(v for v in ctx.pvars.values() if v.startswith('P_'))
            all_vars['O'].update(v for v in ctx.pvars.values() if v.startswith('O_'))
            all_vars['K'].update(ctx.kvars)
            stats['variants'].append((nvar, name, i))
            if k == 0:
                lines.append('# Regel %d (%d Varianten):\n#   %s\n%s\n' % (i, nvar, text, rule))
            else:
                lines.append(rule + '\n')
    stats['files'].append((name, section, ok, sum(1 for _ in rules_of(path))))
    with open(os.path.join(out_dir, name), 'w', encoding='utf-8', newline='\n') as f:
        f.write('\n'.join(lines))
    return name


LOADER = """# inc/integration/rubi/all
# Automatisch erzeugt von tools/rubi2rewrite.py: laedt die aus Rubi 4.17.3
# uebersetzten Regeln (Copyright (c) 2018 Rule-Based-Integration
# Organization, MIT-Lizenz, siehe inc/integration/LICENSE.Rubi).
# Benutzung:
#   INC "inc/all"
#   INC "inc/integration/all"
#   INC "inc/integration/rubi/all"
#   REWR Int(x*exp(2*x),x) : RubiIntegrate

INC "inc/integration/rubi/declarations"
DEFAULT + = 0
DEFAULT * = 1
DEFAULT RIGHT ^ = 1
COMM +,*
ALG RubiRules
# zuerst konstante Faktoren herausziehen, wie Mathematica: sonst macht normpoly
# aus -1*(x*u) den Faktor (-1*x), und Regeln fuer (c*x)^m passen mit c = -1
ADDSPEC RubiRules : IF NIN(Xv,Pa) Int(Pa*Uv,Xv) = Pa*Int(Uv,Xv)
# wie Mathematica 1/sin(u) = csc(u), und Rubis FixInertTrigFunction fuer
# Produkte zweier Winkelfunktionen: sec(u)*sin(u)^2 = cos(u)^-1*sin(u)^2
ADDSPEC RubiRules : Int(Uv,Xv) = Int(trignorm(Uv,Xv),Xv)
# Vielfache eines Winkels (sin(2x) neben cos(x)) mit sin, cos des Winkels
# schreiben, wie Mathematicas TrigExpand
ADDSPEC RubiRules : Int(Uv,Xv) = Int(trigexpand(Uv,Xv),Xv)
# Polynome im Integranden in Mathematicas Normalform c0+c1*x+...
# (ohne Aenderung wird die Regel uebersprungen)
ADDSPEC RubiRules : Int(Uv,Xv) = Int(normpoly(Uv,Xv),Xv)
# Integrale von Summen gleich hier aufteilen, bevor andere Regeln die Summe
# umformen (sonst Zyklen ausmultiplizieren/ausklammern)
ADDSPEC RubiRules : Int(Uv+Vv,Xv) = Int(Uv,Xv)+Int(Vv,Xv)
%s
# zuletzt: Hyperbelfunktionen, fuer die keine Regel passt, als e^u schreiben
# (Rubi nimmt dafuer sin, cos mit imaginaerem Argument)
ADDSPEC RubiRules : Int(Uv,Xv) = Int(hyp2exp(Uv,Xv),Xv)

# am Ende: gleiche Summanden des Ergebnisses zusammenfassen
ALG RubiCollect
ADDSPEC RubiCollect : Uv+Vv = collect(Uv+Vv)
ADDSPEC RubiCollect : Uv*Vv = simp(Uv*Vv)       # x^2*e/x^2 = e
OPT
DEFAULT
COMM

ALG RubiIntegrate
SPEC RubiIntegrate : (RubiNorm,IntRubi,RubiRules),RubiCollect,IntOut,All
"""


def ordered_files(rule_dir, order_file):
    found = {}
    for root, _, names in os.walk(rule_dir):
        for n in names:
            if n.endswith('.m'):
                found[n[:-2]] = os.path.join(root, n)
    if order_file:
        text = open(order_file, encoding='utf-8', errors='replace').read()
        names = re.findall(r'LoadRules\[FileNameJoin\[\{(?:"[^"]*", )*"([^"]*)"\}\]\]', text)
        missing = [n for n in names if n not in found]
        if missing:
            print('warning: rule files not found: %s' % ', '.join(missing), file=sys.stderr)
        return [found[n] for n in names if n in found]
    files = list(found.values())
    files.sort(key=lambda p: [int(t) if t.isdigit() else t
                              for t in re.split(r'(\d+)', os.path.basename(p))])
    return files


UNIFY_HEADER = """# r4_0_unify
# Automatisch erzeugt von tools/rubi2rewrite.py aus Rubis Hilfsfunktion
# UnifyInertTrigFunction (Rubi 4.17.3, MIT-Lizenz, siehe LICENSE.Rubi).
# Rubi hat seine Regeln fuer Potenzen meist nur fuer sin, csc, tan; vor den
# Trigonometrie-Regeln schreibt es cos(e+f x) als sin(e+pi/2+f x) usw.
# Jede Definition UnifyInertTrigFunction[P, x] := R /; C wird hier zur Regel
# Int(P, x) = Int(R, x) mit der Bedingung C. IntOut macht aus
# sin(pi/2 + u) am Ende wieder cos(u).
"""


def translate_unify(util_path, out_dir, all_vars, stats):
    """Rubi's UnifyInertTrigFunction definitions as Int rules (file r4_0_unify)"""
    with open(util_path, encoding='utf-8', errors='replace') as f:
        text = f.read()
    text = re.sub(r'\(\*.*?\*\)', ' ', text, flags=re.S)
    stmts, stmt, depth = [], None, 0
    for line in text.split('\n'):
        line = line.strip()
        if stmt is None:
            if not line.startswith('UnifyInertTrigFunction['):
                continue
            stmt, depth = line, 0
        else:
            stmt += ' ' + line
        depth += sum(line.count(c) for c in '[({') - sum(line.count(c) for c in '])}')
        if depth <= 0 and not stmt.rstrip().endswith(CONTINUES):
            stmts.append(stmt)
            stmt = None
    lines = [UNIFY_HEADER]
    ok = 0
    for i, st in enumerate(stmts, 1):
        lhs_s, rhs_s = split_top(st, ':=')
        if rhs_s is None:
            continue
        inner = lhs_s.strip()[len('UnifyInertTrigFunction['):].rstrip()
        if not inner.endswith(']'):
            continue
        u_s, x_s = split_top(inner[:-1], ',')
        while x_s is not None and ',' in x_s:      # the last argument is x_
            more, x_s = split_top(x_s, ',')
            u_s = u_s + ',' + more
        if x_s is None or x_s.strip() != 'x_' or u_s.strip() in ('u_', 'a_*u_'):
            continue
        body, cond = split_top(rhs_s, '/;')
        rule = 'Int[%s, x_Symbol] := Int[%s, x]' % (u_s, body)
        if cond is not None:
            rule += ' /; ' + cond
        # a single trig factor: also with a polynomial factor (g+h*x)^k, as
        # Rubi's DeactivateTrig[(c+d*x)^m*(a+b*trig)^n] unifies only the trig part
        depth, single = 0, True
        for ch in u_s:
            depth += ch in '[(' and 1 or (ch in '])' and -1 or 0)
            if ch == '*' and depth == 0:
                single = False
        rules = [rule]
        if single:
            rules.append('Int[(gg_.+hh_.*x_)^kk_.*%s, x_Symbol] := Int[(gg+hh*x)^kk*(%s), x] /; '
                         'FreeQ[{gg,hh,kk},x]%s' % (u_s, body, ' && ' + cond if cond else ''))
        try:
            results = []
            for r_text in rules:
                results.extend(translate_rule(r_text))
        except (Untranslatable, RecursionError, IndexError) as err:
            lines.append('# Definition %d nicht uebersetzt: %s\n#   %s\n' % (i, err, st))
            continue
        ok += 1
        for k, (r, nvar, ctx) in enumerate(results):
            all_vars['P'].update(v for v in ctx.pvars.values() if v.startswith('P_'))
            all_vars['O'].update(v for v in ctx.pvars.values() if v.startswith('O_'))
            all_vars['K'].update(ctx.kvars)
            lines.append(('# Definition %d:\n#   %s\n' % (i, st) if k == 0 else '') + r + '\n')
    with open(os.path.join(out_dir, 'r4_0_unify'), 'w', encoding='utf-8', newline='\n') as f:
        f.write('\n'.join(lines))
    stats['unify'] = (ok, len(stmts))
    return 'r4_0_unify'


def write_steps(out_dir):
    """labels for the solution steps (STEPS RubiRules "inc/integration/rubi/steps"):
    one line 'index<TAB>label<TAB>Mathematica rule' per rule of RubiRules, in
    the order in which the files add them"""
    out = []

    def scan(path, default_label):
        section, label, text = default_label, default_label, ''
        lines = open(path, encoding='utf-8').read().split('\n')
        for k, line in enumerate(lines):
            if line.startswith('#   ') and k > 0 and lines[k - 1].rstrip().endswith('Abschnitt'):
                section = line[4:].strip()
            m = re.match(r'# (Regel|Definition) (\d+)', line)
            if m:
                label = '%s, %s %s' % (section, 'rule' if m.group(1) == 'Regel' else 'definition',
                                       m.group(2))
                text = ''
            elif line.startswith('#   ') and not text and label != section:
                text = line[4:].strip()
            m = re.match(r'INC "inc/integration/rubi/(\w+)"', line)
            if m:
                scan(os.path.join(out_dir, m.group(1)), m.group(1))
                label, text = section, ''
            if line.startswith('ADDSPEC RubiRules'):
                out.append('%d\t%s\t%s' % (len(out), label, text or line[len('ADDSPEC RubiRules : '):]))
                if label == section:
                    text = ''
    scan(os.path.join(out_dir, 'all'), 'Rubi loader')
    with open(os.path.join(out_dir, 'steps'), 'w', encoding='utf-8', newline='\n') as f:
        f.write('\n'.join(out) + '\n')


def main():
    args = [a for a in sys.argv[1:] if a != '--stats']
    order_file = None
    if '--order' in args:
        i = args.index('--order')
        order_file = args[i + 1]
        del args[i:i + 2]
    util_file = None
    if '--util' in args:
        i = args.index('--util')
        util_file = args[i + 1]
        del args[i:i + 2]
    if len(args) != 2:
        print(__doc__)
        sys.exit(1)
    rule_dir, out_dir = args
    os.makedirs(out_dir, exist_ok=True)
    files = ordered_files(rule_dir, order_file)
    collect_macros(files)
    if '--stats' in sys.argv:
        print('helper definitions found in the rule files: %s' % ', '.join('%s/%d' % k for k in sorted(MACROS)))
    all_vars = {'P': set(), 'O': set(), 'K': set()}
    stats = {'rejected': {}, 'variants': [], 'files': []}
    names = []
    for p in files:
        name = translate_file(p, out_dir, all_vars, stats)
        if name in names:
            raise SystemExit('two rule files give the same name %s' % name)
        if util_file and name.startswith('r4_') and 'r4_0_unify' not in names:
            names.append(translate_unify(util_file, out_dir, all_vars, stats))
        names.append(name)

    with open(os.path.join(out_dir, 'declarations'), 'w', newline='\n') as f:
        f.write('# Deklarationen fuer die uebersetzten Rubi-Regeln (rubi2rewrite.py)\n')
        f.write('VAR %s : real\n' % ','.join(sorted(all_vars['P'])))
        f.write('VAR %s : real\n' % ','.join(sorted(all_vars['O'])))
        f.write('OPT %s\n' % ','.join(sorted(all_vars['O'])))
        if all_vars['K']:
            f.write('NUM %s : real\n' % ','.join(sorted(all_vars['K'], key=lambda k: int(k[2:]))))
    with open(os.path.join(out_dir, 'all'), 'w', newline='\n') as f:
        f.write(LOADER % '\n'.join('INC "inc/integration/rubi/%s"' % n for n in names))
    write_steps(out_dir)

    total = sum(f[3] for f in stats['files'])
    done = sum(f[2] for f in stats['files'])
    with open(os.path.join(out_dir, 'STATISTICS.txt'), 'w', newline='\n') as f:
        f.write('translated %d of %d rules (%.0f%%) from %d files\n'
                % (done, total, 100.0 * done / max(total, 1), len(names)))
        f.write('\nreasons for rules that were not translated:\n')
        for r, n in sorted(stats['rejected'].items(), key=lambda t: -t[1]):
            f.write('%6d  %s\n' % (n, r))
        f.write('\nper file (translated / total):\n')
        for name, section, ok, tot in stats['files']:
            f.write('%4d / %4d  %-12s %s\n' % (ok, tot, name, section))
    if '--stats' in sys.argv:
        with open(os.path.join(out_dir, 'STATISTICS.txt')) as f:
            print(f.read())


if __name__ == '__main__':
    sys.setrecursionlimit(10000)
    main()
