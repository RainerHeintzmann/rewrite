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

Like Rubi, rewrite can show the solution steps: each rule applied, with
its Rubi section and number, the Mathematica original, and the integral
before and after (as an intermediate term, e.g. with `eE` for `e`):

```text
STEPS RubiRules "inc/integration/rubi/steps"
REWR Int(x^2*sqrt(1-x^2),x) : RubiIntegrate
Step 1: 1.1.2.2 (c x)^m (a+b x^2)^p, rule 9
  Int[(c_.*x_)^m_.*(a_+b_.*x_^2)^p_,x_Symbol] := (c*x)^(m+1)*(a+b*x^2)^p/(c*(m+2*p+1)) + ...
  Int (x ^ 2 * (1 + -1 * x ^ 2 )^ (1/2) ,x )
    = x ^ 3 * (1 + -1 * x ^ 2 )^ (1/2) * (1/4) + (1/4) * Int (x ^ 2 * (1 + -1 * x ^ 2 )^ (-1/2) ,x )
Step 2: 1.1.2.2 (c x)^m (a+b x^2)^p, rule 23
  ...
Step 3: 1.1.2.1 (a+b x^2)^p, rule 17
  Int[1/Sqrt[a_+b_.*x_^2],x_Symbol] := ArcSin[Rt[-b,2]*x/Sqrt[a]]/Rt[-b,2] /; ...
  Int ((1 + -1 * x ^ 2 )^ (-1/2) ,x )
    = arcsin (x )
(1/8) * arcsin (x )+ (1/4) * (1 - x ^ 2 )^ (1/2) * x ^ 3 - (1/8) * (1 - x ^ 2 )^ (1/2) * x
STEPS RubiRules ""
```

The labels come from `rubi/steps`, which the translator writes along with
the rules. Steps done inside C helpers (partial fractions, substitutions)
appear as one step.

Numbers are exact where possible: the integration package loads
[inc/exact](../exact), so `1/3` stays the fraction `(1/3)`, and roots
stay exact in Mathematica's normal form: `Int(1/(x^4+1),x)` gives
`(1/2) * arctan (1 + 2 ^ (1/2) * x )/ 2 ^ (1/2) + ...` and `Int(1/sqrt(x^2+x+1),x)`
gives `arcsinh (1 / 3 ^ (1/2) + 2 * x / 3 ^ (1/2) )`. Rubi also uses complex numbers,
which the rules here do not have:

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
        --order RUBI/Rubi/Rubi.m --util RUBI/Rubi/RubiUtilityFunctions.m [--stats]
```

`--order` loads the files in the order of Rubi's loader, which matters
because the first applicable rule wins. `--util` reads Rubi's utility
functions, from which the cosine unification rules are translated.

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
  `x^0.5`, numeric factors move to the front, and `(u*v)^k` becomes
  `u^k*v^k` for integer `k`, so `1/(x*(a+b*x))` is `x^-1*(a+b*x)^-1`. The
  translator writes Rubi's patterns in the same form, as Mathematica does.
  Unlike `IntNorm` of the hand-translated subset, it does not multiply out
  products with sums, because Mathematica does not do that either.
- `exp(u)` is written as `eE^u` with the symbolic constant `eE` (sort
  `positive`, no numerical value), as Mathematica writes `E^u`, so that
  rules for `F^u` apply to it and `ln(eE) = 1` stays exact. `IntOut` turns
  it back into `exp(u)`.
- Cosine forms: Rubi has most of its rules only for sine and rewrites
  cosine forms first (`UnifyInertTrigFunction`: `a+b*cos(e+f*x)` becomes
  `a+b*sin(e+pi/2+f*x)`, `sec` becomes `csc`, ...). These 69 definitions
  are translated from Rubi's utility file into the rules of
  [rubi/r4_0_unify](rubi/r4_0_unify), loaded before the trigonometric rules;
  a definition with a single trig factor also gets a variant with a factor
  `(g+h*x)^k`, as Rubi's `DeactivateTrig` keeps that factor. `IntOut` turns
  `sin(pi/2+u)` back into `cos(u)`, and `cos(pi+u)` into `-cos(u)`.
  Rubi's `RemoveContent` (`removecontent`) applies the shift and drops
  constant factors, so that `Int[cot(x)]` gives `ln(sin(x))`, not
  `ln(-sin(x))`.
- Mathematica writes `1/Sin[x]` as `Csc[x]` and `Sin[x]^-3` as `Csc[x]^3`,
  and Rubi's `FixInertTrigFunction` then rewrites products of trig
  functions: `sec(x)*sin(x)^2` becomes `cos(x)^-1*sin(x)^2`, `csc(x)`
  next to a power of a sum of cosines becomes `sin(x)^-1`, ... The first
  rule of `RubiRules` after the constant factors does both: `trignorm`
  (symfkt.c) does Mathematica's step and combines `sin(x)*csc(x)^3 =
  csc(x)^2`, then calls `fixinert`, a function defined by rules (`ATT
  RULES`) that the translator writes from Rubi's definitions
  ([rubi/r4_0_fixinert](rubi/r4_0_fixinert)). In Rubi these definitions
  work on inert functions inside `DeactivateTrig`; here they see every
  integrand, and the rules do not tell active from inert functions, so 12
  of them are left out (products of two secants, `tan` or `cot` next to a
  sum `a+b*sin`, functions next to `a*sin+b*cos`): they would take
  integrands away from the rules that solve them.
- Multiple angles: for a function of trig functions of different multiples
  of one angle (and no `x` outside them), as `sin(x)/cos(2*x)`,
  `sin(2*x)*sqrt(1+3*cos(x)^2)` or `exp(sin(x))*sin(2*x)`, the next rule
  writes all of them with `sin` and `cos` of the angle (`trigexpand`,
  Mathematica's `TrigExpand`: `cos(2*x) = cos(x)^2 - sin(x)^2`, ...).
  Shifts by multiples of `pi/2` from the cosine unification are removed
  first. Not expanded are polynomials in sines and cosines, which Rubi
  reduces from products to sums (`cos(3*x)*cos(5*x)`, the expansion would
  undo that), and multiples of sines under a root (`sin(2*x)^(3/2)` would
  become a power of a product).
- Hyperbolic functions: Rubi turns `sinh(u)` into `-i*sin(i*u)`, which needs
  complex numbers. Instead, the last rule of `RubiRules` writes hyperbolic
  functions for which no rule applies with exponentials (`hyp2exp`):
  `sinh(u) = (e^u-e^-u)/2`, ... The result then contains `exp`.
- Substitutions. Rubi's `FunctionOfQ[v,u,x]` and `SubstFor[h,v,u,x]`
  (`functionofq`, `substfor`) decide whether `u` is a function of `v` and
  write it with `v` replaced by `x`; for `v = sin(w)` also `csc(w) = 1/v`,
  `cos(w)^(2m) = (1-v^2)^m`, ..., likewise for cos, tan, cot and the
  hyperbolic functions. So `Int[u*cos(w)]` with `u` a function of
  `sin(w)` becomes an integral in `sin(w)`. Rubi's `DerivativeDivides[y,u,x]`
  (`derivdivides`) gives `u/y'` if it is free of `x`, so that
  `Int[u*f(y)] = q*Subst[Int[f(x)],x,y]`; if not, it stays unevaluated,
  and `falseq` (Rubi's `FalseQ`) is true for such a helper. Rubi's substitution
  `x -> F^(g*x)` for functions of exponentials (`FunctionOfExponential`,
  section 2.3) is the C function `substexp`; the translator puts it in
  place of Rubi's rule (`HAND_RULES`). `FullSimplify` becomes `simplify`,
  which is enough for ratios like `ln(F)/ln(F)`, and `IntOut` writes
  `ln(e^u)` as `u`. Likewise, Rubi's substitutions in section 9.3, which
  pass a list of results (`lst[[2]]`), are C functions in place of the
  rules: `substfracpow` substitutes `t = (a+b*x)^(1/n)` for fractional
  powers of a linear function, `substsqrtquad` does Euler's substitutions
  for functions of `x` and `sqrt(a+b*x+c*x^2)`. Rubi writes these rules
  twice (with and without `ShowStep`); the translator takes the second.
  The rules for `x^m/(a+b*x^n)` with an odd `n` or `n = 2 mod 4` (sections
  1.1.3.1/2) use `Module` with several statements and `Sum[u, {k, ...}]`;
  the C function `binomsum` gives the same sum of integrals of linear and
  quadratic partial fractions, with `cos(k*pi/n)` exact for `n` up to 6:
  `Int(1/(1+x^5),x)` is exact, `Int(1/(1+x^7),x)` has real coefficients.
- Rubi's form tests `LinearMatchQ`, `BinomialMatchQ`, `QuadraticMatchQ`,
  `TrinomialMatchQ` and the others are defined in its utility file as
  `MatchQ[u, pattern /; cond]`; the translator reads these definitions
  (`--util`) and inlines them, so they are no C functions.
- `MatchQ[u, pattern /; cond]` in a condition becomes
  `matchq(u, pattern, cond)`, which uses the matcher of the rule lists.
  Its pattern variables get new names (`P_mq_c`, `O_mq_d` for `c_`, `d_.`),
  since the rule's own variables are bound at that time; other symbols in
  the pattern, like `m` in `(d_.+e_.*x)^m`, refer to the rule's variables.
- Rubi's `GtQ[u,v]` (also `LtQ`, `GeQ`, `LeQ`) is false unless both are
  numbers, so that `Not[GtQ[a^2,0]]` is true for a symbol `a`. The
  translator writes `gtq(u,v)`, ... instead of `u > v`, which cannot be
  calculated for symbols (and made `Not[...]` fail as well).
- The first rules of `RubiRules` take constant factors out of the integral
  (first, as Mathematica does, so that `-1*x*u` does not become
  `(-1*x)*u`, which rules for `(c*x)^m` would match with `c = -1`), write
  polynomials in the integrand as `c0 + c1*x + c2*x^2 + ...` with collected
  coefficients (`normpoly`, which also combines like powers in a product,
  `x*x^-1 = 1`), and split integrals of sums.
- Rubi's `ExpandIntegrand` splits rational functions into partial fractions
  (Mathematica's `Apart`). `expandintegrand` does this with exact rational
  coefficients ([apart.c](../../src/apart.c)), as `c*p(x)*b(x)^-k` with the
  number in front. Rubi's general rule `Int[u] := Int[ExpandIntegrand[u]]`
  for a sum then integrates a rational function term by term. `simp`
  combines like powers in a product, so that factors like
  `((x-1)*(x+1)^2)^-1*((x-1)^-1*(x+1)^-2)^-1` from Rubi's rules become 1.
- Every rule result is simplified trivially: `u^0`, `u^1`, `1*u`, `0*u`,
  `0+u`, and `(u^m)^k = u^(m*k)` for integers `m`, `k`.
- A rule whose result equals the term (no progress), contains a NaN, or
  closes a cycle, is skipped and the next rule is tried. A cycle: the
  result was replaced before, and the chain of the last replacements from
  there (also of subterms, as in `A -> subst(B)`, `B -> A`) leads back to
  the term, like expanding and factoring again. A term that was replaced
  in another branch may come up again.
- Rubi's `IntHide` integrates, `inthide` leaves `Int(u,x)`. In
  `InverseFunctionFreeQ[IntHide[u,x],x]` (integration by parts),
  `inversefunctionfreeq` decides for a rational `u` from its partial
  fractions (`c/b(x)` gives `ln` or `arctan`); other integrands count as
  free, since integration by parts is valid anyway.
- Mathematica's `Times` is flat: `u_*(a_+b_.*ArcTan[x])` matches
  `x^2*ArcTan[x]/(1+x^2)` with `u = x^2/(1+x^2)`. Terms in rewrite are
  binary trees, so the matcher of rule lists also tries all other ways to
  split a nested product (or sum) of up to six operands into two groups
  for a commutative operator. `normpoly` writes a product with powers
  first and other functions last.
- A rule whose result still contains `polyquotient` or `polyremainder`
  (division of a non-polynomial, which Mathematica's `PolynomialQuotient`
  does in its own way) or `expandintegrand` (for example partial fractions
  with symbolic coefficients) is skipped like a rule without progress.
- `PolyQ[u, x^n]` checks that `u` is a polynomial in `x` with only the
  powers `x^(k*n)`.
- Mathematica calculates with complex intermediate values; rewrite only
  with real ones. Rules that need real intermediate values under a
  condition get it from a table in the translator (`REAL_CONDITIONS`):
  Cardano's formula for cubic polynomials only with a positive
  discriminant, `PosQ[4*b^3*d+27*a^2*d^2]`.
- An optional variable that occurs twice, like `e.` in
  `(c+d*tan(e.+f.*x))/(a+b*tan(e.+f.*x))`, may be missing in both places.
- `RubiCollect` combines like summands of the result (`collect`).
- `Subst[Int[u,x],x,v]` becomes `intsubst(u,x,v)`: `u` is integrated in a
  fresh variable, which has the sort `nonneg` when `v` is a square root or
  another non-negative expression. Then `sqrt(x^2) = x` holds inside, as
  Rubi assumes.
- Mathematica writes `(b*tan(u))^3` as `b^3*tan(u)^3`, so in a Rubi pattern
  like `(b_.*tan[u])^n_` with integer `n`, `b` is always 1, and some rules
  ignore it. Rewrite keeps `(-tan(u))^3`. The translator therefore adds the
  condition `eqq(b,1)` (or `eqq(b,0)` in a sum) to every rule whose optional
  variable occurs neither in the conditions nor in the result (20 rules).
- Rules with a function variable (`F_[...]` with `TrigQ[F]`,
  `MemberQ[{Sin,Cos},F]`, ...) become one rule per admissible function.

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
python3 tools/rubitest.py SUITE --every 5 --files Apostol --files Hearn         --files Stewart --files Timofeev            # development set
```

It runs 8 rewrite processes in parallel (`--jobs N`); the four collections
below take about 2 minutes. `--every 5` takes every fifth problem of each
file (309 problems, about 30 seconds) and is meant for development, with
the full set as the final check. The numerical check of special functions
needs the Python package mpmath (MSYS2: `pacman -S mingw-w64-ucrt-x86_64-python-mpmath`);
without it, such results count as not verifiable.

On the four collections of independent problems in the test suite
(textbooks of Apostol, Hearn, Stewart and Timofeev, 1540 problems), the
results are:

| Result | Problems | Share of tested |
| --- | --- | --- |
| solved and verified | 1390 | 90.3% |
| no antiderivative found | 126 | 8.2% |
| wrong | 3 | 0.2% |
| crash or time-out | 0 | 0.0% |
| not verifiable | 20 | 1.3% |

One problem uses a function that rewrite does not have and is not tested.
Two wrong results contain special functions outside their real domain,
where the check compares different complex branches. The third splits
`sqrt(sin(x)*cos(x)^3)` into `cos(x)^(3/2)*sin(x)^(1/2)` (Rubi's rules for
fractional powers of products), which is wrong where both factors are
negative. A run takes
about five minutes. The harness needs `mpmath` for the special functions
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
| [rubi/](rubi) | One file per Rubi rule file, `declarations`, `STATISTICS.txt`, `steps` (labels for `STEPS`). |
| [LICENSE.Rubi](LICENSE.Rubi) | License of the original rules. |
