# Rule-based integration

This folder contains indefinite integration rules for rewrite, translated
from [Rubi](https://github.com/RuleBasedIntegration/Rubi), the rule-based
integrator by Albert D. Rich, version 4.17.3 (commit 61e9c18). Rubi is
published under the MIT license, see [LICENSE.Rubi](LICENSE.Rubi).

There are two rule sets:

- **`Integrate`** uses a small subset of 15 rules translated by hand
  (files in this folder). It loads in a fraction of a second and covers
  powers of linear expressions, exponentials, sine and cosine, and
  polynomials times them.
- **`RubiIntegrate`** uses the rules in [rubi](rubi), which the script
  [tools/rubi2rewrite.py](../../tools/rubi2rewrite.py) translates
  automatically from Rubi's rule files. About 90% of Rubi's
  rules are translated. Loading takes about half a second.

## Usage

```text
INC "inc/all"
INC "inc/integration/all"
REWR Int(x^2*cos(x),x) : Integrate
2 * cos (x )* x + x ^ 2 * sin (x )- 2 * sin (x )

INC "inc/integration/rubi/all"
REWR Int(1/(1+x^3),x) : RubiIntegrate
(1/3) * ln (1 + x )+ 0.57735 * arctan (-0.57735 + 1.1547 * x )- (1/6) * ln (1 + x ^ 2 - x )
REWR Int(sqrt(1-x^2),x) : RubiIntegrate
(1/2) * arcsin (x )+ (1/2) * (1 - x ^ 2 )^ (1/2) * x
REWR Int(x/(1+x^4),x) : RubiIntegrate
(1/2) * arctan (x ^ 2 )
```

`Int(f,x)` is the indefinite integral without integration constant. If no
rule applies, the remaining integral is returned unchanged.

Numbers are exact where possible: the integration package loads
[inc/exact](../exact), so `1/3` stays the fraction `(1/3)`, and roots like
`sqrt(3)` become real numbers. Rubi also uses complex numbers, which the
rules here do not have:

- Rules whose result needs `I` (the imaginary unit) are not translated.
- A rule whose result contains a NaN, for example the square root of a
  negative number, counts as not applicable; the next rule is tried.
- Logarithms keep Rubi's arguments, e.g. `ln(-2 + x)`, which is NaN for
  `x < 2` in real arithmetic. Its derivative is still correct.

## The translated Rubi rules

[tools/rubi2rewrite.py](../../tools/rubi2rewrite.py) reads Rubi's rule files
and writes one rewrite file per Rubi file into [rubi](rubi), with the
Mathematica original of every rule as a comment, plus
[rubi/STATISTICS.txt](rubi/STATISTICS.txt) with the reasons for the rules it
could not translate. Generated files should not be edited by hand; changes
belong in the script.

```text
python3 tools/rubi2rewrite.py RUBI/Rubi/IntegrationRules inc/integration/rubi \
        --order RUBI/Rubi/Rubi.m [--stats]
```

`--order` loads the files in the order of Rubi's loader, which matters
because the first applicable rule wins.

A Rubi rule translates almost one to one:

```text
Int[(a_. + b_.*x_)^m_, x_Symbol] := (a + b*x)^(m + 1)/(b*(m + 1)) /;
    FreeQ[{a, b, m}, x] && NeQ[m, -1]

ADDSPEC RubiRules : IF NIN(Xv,O_a,O_b,P_m), (neq(P_m,(-1)))
    Int(((O_a)+((O_b)*(Xv)))^(P_m),Xv) = ...
```

| Rubi | rewrite |
| --- | --- |
| `x_Symbol` | `Xv` |
| `a_` | `P_a`, a `VAR` |
| `a_.` | `O_a`, a `VAR` declared with `OPT` |
| default of `a_.` in `+`, `*`, exponent | `DEFAULT + = 0`, `DEFAULT * = 1`, `DEFAULT RIGHT ^ = 1` |
| order of factors and summands | `COMM +,*` |
| negative number in a pattern, e.g. `-1` | a `NUM` variable `K_1` with the condition `(K_1 == (-1))` |
| `FreeQ[{a,b},x]` | `NIN(Xv,O_a,O_b)` |
| `c1 && c2` | `IF c1, c2` |
| `With[{q = ...}, ...]`, `Module` with values only | `q` replaced by its value |
| helpers defined in the rule files (`IntBinomialQ`, ...) | inlined |
| `ExpandIntegrand`, `PolyQ`, `Subst`, `Rt`, `D`, ... | the C helpers of [inc/helpers](../helpers) |
| Rubi's inert trig functions `sin`, `cos`, ... | the normal functions |
| `LinearQ[{u,v},x]` (a predicate on a list) | `linearq(u,x) && linearq(v,x)` |
| `ReplaceAll[u, x -> v]` | `replaceall(u,x,v)` |
| `ExpandTrig`, `ExpandTrigReduce` | `expandintegrand`, `expandtrigreduce` |
| `Erf`, `FresnelS`, `SinIntegral`, `ExpIntegralEi`, `Gamma`, `EllipticF`, `Hypergeometric2F1`, ... | the special functions of [inc/alg](../alg) (`erf`, `fresnels`, `sinint`, `expint`, `Gamma`, `ellipticf`, `hyp2f1`, ...) |

The rules are stored in Rubi's order in a rule list (see "Rule lists" in
the main README). The matcher handles optional parts and commutative
operators by backtracking, and the conditions are part of the match.

### Differences to Mathematica that the rule list handles

Rubi relies on Mathematica's automatic simplification. Rewrite does not
have it, so a few steps are added:

- `RubiNorm` brings the integrand into a similar normal form first:
  `x-y` becomes `x+(-1)*y`, `x/y` becomes `x*y^(-1)`, `sqrt(x)` becomes
  `x^0.5`, numeric factors move to the front. Unlike `IntNorm` of the
  hand-translated subset, it does not multiply out products with sums,
  because Mathematica does not do that either.
- `exp(u)` is written as `e^u` with the number `e`, as Mathematica writes
  `E^u`, so that rules for `F^u` apply to it. `IntOut` turns it back into
  `exp(u)`.
- The first rules of `RubiRules` write polynomials in the integrand as
  `c0 + c1*x + c2*x^2 + ...` with collected coefficients (`normpoly`), and
  split integrals of sums and constant factors.
- Every rule result is simplified trivially: `u^0`, `u^1`, `1*u`, `0*u`,
  `0+u`.
- A rule whose result equals the term (no progress), contains a NaN, or
  equals one of the last terms that rules replaced (a cycle like
  expanding and factoring again), is skipped and the next rule is tried.
- An optional variable that occurs twice, like `e.` in
  `(c+d*tan(e.+f.*x))/(a+b*tan(e.+f.*x))`, may be missing in both places.
- `RubiCollect` combines like summands of the result (`collect`).

The algebra list is

```text
SPEC RubiIntegrate : (RubiNorm,IntRubi,RubiRules),RubiCollect,IntOut,All
```

## Measuring with Rubi's test suite

[tools/rubitest.py](../../tools/rubitest.py) runs problems of Rubi's test
suite ([MathematicaSyntaxTestSuite](https://github.com/RuleBasedIntegration/MathematicaSyntaxTestSuite),
MIT license) through `RubiIntegrate` and checks each result numerically:
the derivative of the result must equal the integrand at several points.

```text
python3 tools/rubitest.py SUITE --files Apostol --report report.txt
```

On the four collections of independent problems in the test suite
(textbooks of Apostol, Hearn, Stewart and Timofeev, 1540 problems), the
results are:

| Result | Problems | Share of tested |
| --- | --- | --- |
| solved and verified | 847 | 55.0% |
| no antiderivative found | 673 | 43.7% |
| wrong | 3 | 0.2% |
| crash or time-out | 7 | 0.5% |
| not verifiable | 9 | 0.6% |

One problem uses a function that rewrite does not have and is not tested.
The three wrong results contain special functions outside their real
domain, where the check compares different complex branches. A run takes
about ten minutes. The harness needs `mpmath` for the special functions
(`pacman -S mingw-w64-ucrt-x86_64-python-mpmath` in MSYS2).

## The hand-translated subset

The files in this folder translate 13 Rubi rules into 15 rewrite rules:

| Integrand | Rubi section |
| --- | --- |
| constants, sums, constant factors | 9.1 Integrand simplification rules |
| `L^m`, including `1/L` and `sqrt(L)` | 1.1.1.1 (a+b x)^m |
| `L1^m*L2^n` for an integer `m > 0` (multiplied out) | 1.1.1.2 (a+b x)^m (c+d x)^n |
| `exp(L)`, `F^L` for a number `F` | 2.3 Miscellaneous exponentials |
| `L^m*exp(L)` for `m = 1/2, 1, 3/2, 2, ...` | 2.1 (c+d x)^m (a+b (F^(g (e+f x)))^n)^p |
| `sin(L)`, `cos(L)` | 4.1.1.1 (a+b sin)^n |
| `L^m*sin(L)`, `L^m*cos(L)` for `m > 0` | 4.1.10 (c+d x)^m (a+b sin)^n |

Here `L` stands for a linear expression `a+b*x`, where `a` and `b` may be
numbers or symbols. The test
[tests/cases/16_integration.rw](../../tests/cases/16_integration.rw)
checks every result by differentiating it again, and
[tests/cases/19_rubi.rw](../../tests/cases/19_rubi.rw) does the same for
`RubiIntegrate`.

## Files

| File | Contents |
| --- | --- |
| [all](all) | Loads the hand-translated subset and defines `Integrate`. |
| [base](base) | Declarations, normal forms `IntNorm` and `RubiNorm`, output form `IntOut`, settings and linearity rules. |
| [1.1.1.1_linear_power](1.1.1.1_linear_power) | Powers of linear expressions. |
| [1.1.1.2_linear_products](1.1.1.2_linear_products) | Products of powers of linear expressions. |
| [2_exponentials](2_exponentials) | Exponentials, and polynomials times exponentials. |
| [4.1_sine](4.1_sine) | Sine and cosine, and polynomials times them. |
| [rubi/all](rubi/all) | Loads the automatically translated rules and defines `RubiIntegrate`. |
| [rubi/](rubi) | One file per Rubi rule file, `declarations`, `STATISTICS.txt`. |
| [LICENSE.Rubi](LICENSE.Rubi) | License of the original rules. |
