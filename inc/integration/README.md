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
```

`Int(f,x)` is the indefinite integral without integration constant. If no
rule applies, the remaining integral is returned unchanged, for example
`Int (sin (x )^ 2 ,x )`.

## What is covered

The subset handles sums of the following integrands, with numbers as
coefficients. Here `L` stands for any linear expression `a+b*x`.

| Integrand | Rubi section |
| --- | --- |
| constants, sums, constant factors | 9.1 Integrand simplification rules |
| `L^m`, including `1/L` and `sqrt(L)` | 1.1.1.1 (a+b x)^m |
| `exp(L)`, `F^L` for a number `F` | 2.3 Miscellaneous exponentials |
| `L^m*exp(L)` for `m = 1/2, 1, 3/2, 2, ...` | 2.1 (c+d x)^m (a+b (F^(g (e+f x)))^n)^p |
| `sin(L)`, `cos(L)` | 4.1.1.1 (a+b sin)^n |
| `L^m*sin(L)`, `L^m*cos(L)` for `m > 0` | 4.1.10 (c+d x)^m (a+b sin)^n |

Products of two linear factors, like `x*(x+1)`, are multiplied out first.
The test [tests/cases/16_integration.rw](../../tests/cases/16_integration.rw)
checks every result by differentiating it again.

## How the translation works

Rubi's patterns use features that rewrite's pattern matcher does not have.
The translation replaces them as follows.

- **Optional pattern parts.** Rubi writes `a_.+b_.*x_`, where a missing `a`
  means 0 and a missing `b` means 1. Here, the algebra `IntCanon` first
  rewrites every linear expression of the integration variable into a
  canonical form `lin(a,b,x)`. One rule then covers `x`, `2*x`, `x+1` and
  `3+2*x`.
- **FreeQ conditions.** Rubi tests that a parameter does not contain `x`.
  Here, the parameters are `NUM` variables, which only match numbers. That
  makes the test unnecessary, but it also limits the subset to numeric
  coefficients. Symbolic constant factors are still handled by linearity,
  so `Int(a*x,x)` works.
- **Several conditions.** A rewrite rule has only one condition, but it can
  be a boolean expression: `IF ((Km > 0) && is_int(2*Km))`.
- **Commutative matching.** Mathematica matches products in any order.
  Here, rules with two factors are written for both orders.
- **Cosine.** Rubi writes `cos(z)` as `sin(z+Pi/2)`. The cosine rules here
  are the sine rules with this shift worked out.

The integration runs as the algebra list `Integrate`:

```text
SPEC Integrate : (IntCanon,IntRubi),IntUnlin,All
```

`IntCanon` and `IntRubi` are applied repeatedly until nothing changes. Then
`IntUnlin` turns `lin(a,b,x)` back into `a+b*x`, and the standard algebra
`All` simplifies the result.

## Files

| File | Contents |
| --- | --- |
| [all](all) | Loads all files and defines `Integrate`. |
| [base](base) | Declarations, canonical form `lin`, back conversion, linearity rules. |
| [1.1.1.1_linear_power](1.1.1.1_linear_power) | Powers of linear expressions. |
| [2_exponentials](2_exponentials) | Exponentials, and polynomials times exponentials. |
| [4.1_sine](4.1_sine) | Sine and cosine, and polynomials times them. |
| [LICENSE.Rubi](LICENSE.Rubi) | License of the original rules. |

## Adding rules

1. Pick a Rubi rule file and a rule whose helper functions exist here.
2. Copy the Mathematica rule as a comment.
3. Write the pattern with `lin(...)` for linear expressions and `NUM`
   variables for numeric parameters. Turn the conditions into one boolean
   expression.
4. Add a line to the test and check it with the derivative test.

This folder translates 13 Rubi rules into 24 rewrite rules. Rubi's rule
files contain about 8500 rule definitions, and many of them use helper
functions like
`ExpandIntegrand`, `Subst` or special functions like `ExpIntegralEi`, which
rewrite does not have yet. Those sections need more infrastructure before
they can be translated.
