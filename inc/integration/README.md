# Rule-based integration

This folder contains indefinite integration rules for rewrite. They are a
translation of a small, closed subset of [Rubi](https://github.com/RuleBasedIntegration/Rubi),
the rule-based integrator by Albert D. Rich, version 4.17.3 (commit 61e9c18).
Rubi is published under the MIT license, see [LICENSE.Rubi](LICENSE.Rubi).
The original Mathematica form of every translated rule is kept as a comment
above its translation.

## Usage

```text
INC "inc/all"
INC "inc/integration/all"
REWR Int(x^2*cos(x),x) : Integrate
2 * cos (x )* x + x ^ 2 * sin (x )- 2 * sin (x )
REWR Int(sin(a*x+b),x) : Integrate
- cos (a * x + b )/ a
```

`Int(f,x)` is the indefinite integral without integration constant. If no
rule applies, the remaining integral is returned unchanged, for example
`Int (sin (x )^ 2 ,x )`.

## What is covered

The subset handles sums of the following integrands. Here `L` stands for a
linear expression `a+b*x`, where `a` and `b` may be numbers or symbols that
do not contain `x`.

| Integrand | Rubi section |
| --- | --- |
| constants, sums, constant factors | 9.1 Integrand simplification rules |
| `L^m`, including `1/L` and `sqrt(L)` | 1.1.1.1 (a+b x)^m |
| `L1^m*L2^n` for an integer `m > 0` (multiplied out) | 1.1.1.2 (a+b x)^m (c+d x)^n |
| `exp(L)`, `F^L` for a number `F` | 2.3 Miscellaneous exponentials |
| `L^m*exp(L)` for `m = 1/2, 1, 3/2, 2, ...` | 2.1 (c+d x)^m (a+b (F^(g (e+f x)))^n)^p |
| `sin(L)`, `cos(L)` | 4.1.1.1 (a+b sin)^n |
| `L^m*sin(L)`, `L^m*cos(L)` for `m > 0` | 4.1.10 (c+d x)^m (a+b sin)^n |

Products with sums, like `x*(x+1)`, are multiplied out first. Exponents
must be numbers: a condition like `m != -1` does not hold for a symbolic
`m`, so `Int(x^n,x)` stays unevaluated. The test
[tests/cases/16_integration.rw](../../tests/cases/16_integration.rw)
checks every result by differentiating it again.

## How the translation works

The rules use the pattern features `OPT`, `DEFAULT`, `COMM` and condition
lists (see the main README). With them, a Rubi rule translates almost one
to one:

```text
Int[(a_. + b_.*x_)^m_, x_Symbol] := (a + b*x)^(m + 1)/(b*(m + 1)) /;
    FreeQ[{a, b, m}, x] && NeQ[m, -1]

ADDSPEC IntRubi : IF NIN(Xv,Qa,Qb,Pm), (Pm != -1) Int((Qa+Qb*Xv)^Pm,Xv) =
                  (Qa+Qb*Xv)^(Pm+1)/(Qb*(Pm+1))
```

| Rubi | rewrite |
| --- | --- |
| `x_` | `Xv` |
| `a_` (parameter) | `Pa`, a `VAR` |
| `a_.` (optional parameter) | `Qa`, a `VAR` declared with `OPT` |
| default of `a_.` in `+`, `*`, exponent | `DEFAULT + = 0`, `DEFAULT * = 1`, `DEFAULT RIGHT ^ = 1` |
| order of factors and summands | `COMM +,*` |
| `FreeQ[{a,b},x]` | `NIN(Xv,Qa,Qb)` |
| `c1 && c2` | `IF c1, c2` |
| `cos(z)` written as `sin(z+Pi/2)` | separate cos rules with the shift worked out |

Rubi relies on Mathematica's normal form of expressions. The rule set
`IntNorm` produces a similar form before the Rubi rules are applied:
`x-y` becomes `x+(-1)*y`, `x/y` becomes `x*y^(-1)`, `sqrt(x)` becomes
`x^0.5`, `e^x` becomes `exp(x)`, numeric factors move to the front, and
products with sums are multiplied out.

The integration runs as the algebra list `Integrate`:

```text
SPEC Integrate : (IntNorm,IntRubi),IntOut,All
```

`IntNorm` and `IntRubi` are applied repeatedly until nothing changes. Then
`IntOut` turns negative numbers and exponents back into minus signs and
fractions, and the standard algebra `All` simplifies the result.

The settings `OPT`, `DEFAULT` and `COMM` are switched on in [base](base) and
switched off again at the end of [all](all), so they do not affect rules
defined later.

## Files

| File | Contents |
| --- | --- |
| [all](all) | Loads all files and defines `Integrate`. |
| [base](base) | Declarations, normal form, settings and linearity rules. |
| [1.1.1.1_linear_power](1.1.1.1_linear_power) | Powers of linear expressions. |
| [1.1.1.2_linear_products](1.1.1.2_linear_products) | Products of powers of linear expressions. |
| [2_exponentials](2_exponentials) | Exponentials, and polynomials times exponentials. |
| [4.1_sine](4.1_sine) | Sine and cosine, and polynomials times them. |
| [LICENSE.Rubi](LICENSE.Rubi) | License of the original rules. |

## Adding rules

1. Pick a Rubi rule file and a rule whose helper functions exist here.
2. Copy the Mathematica rule as a comment.
3. Translate the pattern with the table above and add it with
   `ADDSPEC IntRubi` to a file that is loaded between `base` and the end
   of `all`.
4. Add a line to the test and check it with the derivative test.

The helper functions of Rubi that appear in the conditions and right-hand
sides, such as `ExpandIntegrand`, `PolyQ`, `IntegerQ` or `Subst`, are
available in lower case from [inc/helpers](../helpers) (see the main
README). For example, the rule in
[1.1.1.2_linear_products](1.1.1.2_linear_products) translates

```text
Int[(a_. + b_.*x_)^m_.*(c_. + d_.*x_)^n_., x_Symbol] := Int[ExpandIntegrand[(a + b*x)^m*(c + d*x)^n, x], x] /;
    FreeQ[{a, b, c, d, n}, x] && NeQ[b*c - a*d, 0] && IGtQ[m, 0] && (Not[IntegerQ[n]] || ...)
```

into a rule with `neq(Qb*Qc-Qa*Qd,0)`, `igtq(Qm,0)` and
`expandintegrand(...)`.

This folder translates 13 Rubi rules into 15 rewrite rules. When they are
defined, the optional parts and commutative operators expand them into
about 1700 variants. Rubi's rule files contain about 8500 rule definitions.
About 72% of them use only functions that rewrite now has; with a
translator that resolves Mathematica's local definitions (`With`, `Module`)
it would be about 77%. Translating all of them will need optional parts and
commutative matching inside the matcher, instead of the expansion into
variants.
