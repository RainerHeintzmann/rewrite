# Examples

Small programs that show what rewrite can do. Run one from the project
folder (the `INC` paths are relative to it):

```text
rewrite examples/03_integration.rw
```

or, in an interactive session, `INC "examples/03_integration.rw"`. The
results are printed in order, under short headings; open the file next to
it to see the input. `?name` explains a keyword or function.

| File | Contents |
| --- | --- |
| [01_basics.rw](01_basics.rw) | numbers, symbols (`SYM`) with and without a value, terms (`TERM`), `TYPEOF` |
| [02_differentiation.rw](02_differentiation.rw) | derivatives with `D`, second and partial derivatives (`deriv`) |
| [03_integration.rw](03_integration.rw) | indefinite integrals with `Integrate` and `RubiIntegrate`, a check by differentiation |
| [04_exact.rw](04_exact.rw) | exact fractions and big integers, exact values of functions |
| [05_lists_matrices.rw](05_lists_matrices.rw) | lists, vectors, matrices, `det`, `inverse`, `linsolve`, covectors |
| [06_equations.rw](06_equations.rw) | equations and systems with `solve` |
| [07_own_rules.rw](07_own_rules.rw) | your own rule sets: Fibonacci numbers, the logarithm laws, rules with conditions |
| [08_numerics.rw](08_numerics.rw) | numerical integral, Newton's method, minimum, `PRTNUM`, numerical vectors, a loop |
| [09_unicode.rw](09_unicode.rw) | Unicode names, written directly or as `\alpha` |
| [10_limits.rw](10_limits.rw) | limits at infinity, definite integrals, `heaviside` and `dirac` |
| [11_laplace.rw](11_laplace.rw) | Laplace transforms and their inverses, differential equations with initial values |
| [12_fourier.rw](12_fourier.rw) | Fourier transforms and their inverses: table, integral, theorems, duality |
| [13_ode.rw](13_ode.rw) | ordinary differential equations: a solution checked, characteristic equation, integrating factor, separation of variables, an initial value problem (Laplace), Picard iteration, Runge-Kutta |
| [14_pde.rw](14_pde.rw) | partial differential equations: wave, heat and Laplace equation, separation of variables, heat and transport equation with the Fourier transform |
| [15_series.rw](15_series.rw) | Taylor polynomials around 0 and another point, of a product, the error, the derivative |

The tests run them as well (`tests/cases/ex_example_*.rw`), so they stay
correct.
