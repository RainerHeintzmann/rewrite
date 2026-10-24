# rewrite

A computer language that first has to learn Math from Include files.

`rewrite` is a small system for manipulating symbolic expressions and for
numerical calculations. It knows almost nothing by itself: data types,
operators and the rules of algebra are defined in plain-text include files.
Expressions are then transformed by *rewriting* them with these rule sets
("algebras"). This is enough for things like symbolic differentiation,
simplification, solving simple equations, numerical integration and
physics calculations with vectors, matrices and complex numbers.

It was written by Rainer Heintzmann around 1992 to 1996, based on a scanner
and parser framework by Prof. Axel T. Schreiner, and ran on Unix and the
Amiga. In 2026 it was ported to current compilers (64 bit, Linux and
Windows). The original German manual is in [tex/rewrite/readme.tex](tex/rewrite/readme.tex)
(with a [PDF](tex/rewrite/readme.pdf)) and in [readme](readme). This README is
an English summary of it.

## Quick start

```text
$ rewrite
> INC "inc/all"
> REWR D(sin cos x,x) : All
- cos (cos (x ))* sin (x )
> REWR D(x^2*sin x,x) : All
2 * x * sin (x )+ x ^ 2 * cos (x )
> REWR I(0,1,x^2,x) : numerik,rechne
0.333333
> sqrt(16), ln(e), sin(pi/2)
4 1 1
> [1,0,0] _x_ [0,1,0]
[0,0,1]
> a = 3
> a + 1
4
> a = nothing
> a + 1
a + 1
> QUIT
```

`INC "inc/all"` loads the standard library. `REWR term : All` rewrites the
term with the rule list `All`, here computing the derivative of
`sin(cos(x))`. Constants such as `a` either have a value or stand for
themselves: `a = nothing` removes the value again, because the library
constant `nothing` never has one.

There are an interactive and a non-interactive way to run rewrite:

| Command | Mode |
| --- | --- |
| `rewrite` | Interactive: a welcome message, then a `>` prompt for each statement (`-->` inside an open block). |
| `rewrite file ...` | Runs the files one after the other (like `INC "file"`), then exits. |
| `rewrite -i file ...` | Runs the files, then continues interactively, e.g. with a library already loaded. |
| `rewrite < file` | Reads the program from a pipe or file, without welcome message and prompts (for scripts and the tests). |
| `rewrite -h` | Shows these options. |

`QUIT` or the end-of-file key (Ctrl-D, on Windows Ctrl-Z and Enter) ends an
interactive session. Whether the input is interactive is decided by the
terminal: in the MSYS2 terminal (mintty), standard input is a pipe for
Windows programs, so use `rewrite -i` there to get the prompts.

Paths in `INC` and `DATA` are relative to the current directory, so start
`rewrite` in the project folder when you use the standard library.

## Building

You need `gcc`, `flex`, `bison`, `make` and the GMP library (for exact
numbers; it is linked statically).

**Linux:**

```text
sudo apt install gcc flex bison make libgmp-dev    # Debian/Ubuntu
make
make test
```

**Windows:** install [MSYS2](https://www.msys2.org), for example with
`winget install MSYS2.MSYS2`. Then open the MSYS2 shell once and install
the tools:

```text
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gmp flex bison make diffutils
```

After that, run `build_windows.bat` in the project folder, or `make` in the
"MSYS2 UCRT64" shell. `build_windows.bat test` runs the tests, and
`build_windows.bat clean` removes all generated files. The resulting
`rewrite.exe` needs no extra DLLs and also runs from `cmd` or PowerShell.

The old 32-bit Unix makefile is kept as `makefile.unix32.orig`, and the
Amiga makefile as `makefile.amiga`.

## Tests

The folder [tests](tests) contains regression tests. Each test is a small
rewrite program whose output is compared with a stored reference.

```text
make test                       # or: tests/run_tests.sh
tests/run_tests.sh --verbose    # show differences for failing tests
tests\run_tests.bat             # from cmd or PowerShell on Windows
```

See [tests/README.md](tests/README.md) for details and for how to add tests.

## The language

### Input conventions

- Input is processed line by line. Every line is executed right after it
  has been read.
- A long line can be continued with `\` at the very end of the line. No
  character, not even a space, may follow the `\`.
- A block in `{ ... }` may span several lines. Interactively, the prompt
  `-->` shows that a block is still open.
- Several instructions in one line are separated by `;`.
- Comments start with `#` and go to the end of the line.
- A text in double quotes is printed: `"Hello world"`. A comma-separated
  list prints several items: `"value of x: ",x`.
- Writing a term prints it, evaluated as far as possible. The last printed
  term is always available as the term `%`.
- Errors are reported with the offending line, and the interpreter goes on
  with the next line.

### Defining data types and operators

Without the library, the language knows no types and no operators at all.
This complete program defines them from scratch:

```text
SORT real                                   # a data type
NUM real                                    # numbers like 1.5 have type real
FUNC + : real,real >> real LA2 ATT plus     # operators with priority and
FUNC * : real,real >> real LA3 ATT mal      # the C function that computes them
FUNC ^ : real,real >> real RA  ATT hoch
1+2*3                                       # prints 7
2^3^2                                       # prints 512
CONST x,y : real
x+y*2                                       # prints x + y * 2
x=4
x+y*2                                       # prints 4 + y * 2
```

| Command | Meaning |
| --- | --- |
| `SORT name [,name ..]` | Defines a data type ("sort"), needed for functions, variables and constants. |
| `NUM sortname` | Assigns the type for all numbers typed in. Numbers are stored as `double`. Example: `SORT real` then `NUM real`. |
| `CONST name [,..] : sort` | Declares a constant. It can take any value, so it is a variable in the usual sense. Without a value it stays a symbol and is printed by its name. |
| `VAR name [,..] : sort` | Declares a meta variable. It is a placeholder for any term in rewrite rules, for example `A+0=A`. |
| `NUM name [,..] : sort` | Declares a meta variable that only matches numbers. |
| `TERM name [,..] : sort` | Declares a term variable, which stores a whole expression. |
| `FUNC name : sorts >> sort [LA1..LA5\|RA\|RU] [ATT name]` | Defines a function or operator, see below. |
| `OTHER name : sorts >> sort [ATT name]` | Adds another meaning to an existing function name, for other argument types. Example: `OTHER + : vector,vector >> vector`. |
| `BRA open close : sorts >> sort [ATT name]` | Defines a function written with brackets, like `<a,b>` for a scalar product. `a[b,c]` may be used for `[a,b,c]`, so vectors can be indexed with `v[1]`. |
| `ATT sort show,cmp,cpy,del` | Assigns the C functions that print, compare, copy and delete values of a sort. Example: `ATT complex show_complex,cmp_complex,cpy_complex,del_complex`. |

**Functions.** `FUNC name : real,real >> real` declares a function with two
`real` arguments and a `real` result. A `++` after the last argument type
allows any number of arguments of that type. The optional format word sets
how the function is written:

- `LA1` to `LA5`: left-associative binary operator. `LA5` binds tighter
  than `LA4`, and so on.
- `RA`: right-associative binary operator, for example `a^b`.
- `RU`: right unary operator, for example the factorial `3!`.
- Without a format word, the function is written as `sin x`, `sin(x)` or
  `f(x,y)`.

`ATT name` connects the function to a C function in the list
`userfunction` in [userfkt.c](userfkt.c). It is called when all arguments
have numerical values. Otherwise the function stays symbolic.

A function can also be written in the rewrite language itself, with
`ATT ( argument definitions ) block`:

```text
FUNC fma3 : real,real,real >> real ATT (CONST aa,bb : real; TERM cc : real) { RETURN cc+aa*bb }
fma3(2,3,4)          # prints 10
fma3(2,3,y)          # y has no value: prints fma3 (2 ,3 ,y )
```

`RETURN term` sets the result of such a function. It does not end the
function.

### Rule sets (algebras) and rewriting

| Command | Meaning |
| --- | --- |
| `ALG name` | Defines a new rule set ("algebra"). |
| `SPEC alg : left = right [DO block]` | Deletes the old rules of `alg` and enters this rule. |
| `ADDSPEC alg : [IF cond] left = right [DO block]` | Adds a rule to `alg`. |
| `SPEC alg : alg1, alg2, ..` | Makes `alg` stand for a list of rule sets, which are applied one after the other. |
| `REWR term : alg [,alg ..]` | Rewrites `term` with the given rule sets, one after the other, and prints the result. |
| `Termname = REWR term : alg ..` | Rewrites and stores the result in a term variable. |
| `LIFT (functions) TO (functions)` | Transfers all rules that hold for one set of functions and constants to another set. |

Rule sets in a list are separated by commas. Older versions used `;`. A
list in parentheses, like `(Linear,Compl,diff)`, is applied repeatedly
until nothing changes any more.

Meta variables (`VAR`) in a rule match any term. Meta variables declared
with `NUM` only match numbers. A rule can have conditions:

- `LB(term,term)`: "lower or between", an ordering of terms, used for
  example to sort sums.
- `IN(a,b)`: term `a` occurs in term `b`. `NIN(a,b)` is the negation.
  `NIN(x,a,b,c)` tests that `x` occurs in none of `a`, `b`, `c`.
- `(term)`: any expression with a boolean result, for example
  `(is_int(N))` or `(N > 0)`. If the expression cannot be calculated, for
  example because `N` is symbolic, the condition does not hold.

Several conditions are separated by commas, and all of them must hold:
`IF NIN(x,A), (N > 0) ...`. With `DO block`, the block is executed before
the left side is replaced by the right side.

```text
VAR A : real
ALG simp
SPEC simp : A*1=A
ADDSPEC simp : A+0=A
CONST u : real
REWR (u*1)+0 : simp         # prints u
```

**Optional parts and commutative operators.** Three statements make one
rule cover many forms of a term. They act on the rules defined after them:

| Command | Meaning |
| --- | --- |
| `OPT A,B` | The meta variables `A`, `B` may be missing in a pattern. |
| `DEFAULT + = 0` | A missing operand of `+` has the value 0. |
| `DEFAULT RIGHT ^ = 1` | Only the right operand of `^` may be missing, with value 1. |
| `COMM +,*` | Patterns with `+` and `*` also match with swapped operands. |
| `OPT`, `DEFAULT`, `COMM` | Without arguments: clear the list again. |

```text
VAR Xw : real
NUM Ca,Cb,Cm : real
OPT Ca,Cb,Cm
DEFAULT + = 0
DEFAULT * = 1
DEFAULT RIGHT ^ = 1
COMM +,*
FUNC fq : real,real >> real
FUNC gq : real,real,real >> real
ALG tq
SPEC tq : fq((Ca+Cb*Xw)^Cm,Xw) = gq(Ca,Cb,Cm)
REWR fq((x*2+3)^5,x) : tq     # prints gq (3 ,2 ,5 )
REWR fq(x+3,x) : tq           # prints gq (3 ,1 ,1 )
REWR fq(x,x) : tq             # prints gq (0 ,1 ,1 )
```

**Rule lists.** Rules defined while `OPT`, `DEFAULT` or `COMM` is active
are not merged into the rule tree. They are kept in a list in the order of
their definition, like in Mathematica or Rubi, and the first rule that
matches wins. The matcher ([listmatch.c](listmatch.c)) tries the swapped
operands of commutative operators, the other groupings of nested
operands (`u*f(x)` matches `x^2*f(x)*g` with `u = x^2*g`, up to six
operands) and the missing optional operands by backtracking, and the
conditions are part of the match: if a condition
fails, the next possibility is tried. Two more rules apply to rule lists
only:

- If the result of a rule equals the term (no progress), contains a NaN,
  or closes a cycle (it was replaced before, and the chain of the last 16
  replacements from there, also of subterms, leads back to the term), the
  rule is skipped and the next rule of the list is tried.
- The result is simplified trivially (`u^0`, `u^1`, `1*u`, `0*u`, `0+u`,
  `(u^m)^k = u^(m*k)` for integers), as Mathematica does automatically.

A rule list of several thousand rules is fast, because a quick test of the
function names skips most rules without running the matcher.

**Step limit.** One `REWR` stops after 100000 rewriting steps with the
message `REWR : step limit (100000 rewrites) reached`. Rules that loop
therefore do not hang the interpreter.

The trick behind `LIFT`: once the group rules for `+` and `-` are written,
the ring rules for `*` and `/` can be derived from them:

```text
LIFT (Aag+Aag,Aag-Aag,-Aag,0ag) TO (Ar+Ar,Ar-Ar,-Ar,0r)
LIFT (Aag+Aag,Aag-Aag,-Aag,0ag) TO (Ar*Ar,Ar/Ar,mi(Ar),1r)
```

### Exact numbers and subsorts

Each sort has its own representation in C. [inc/exact](inc/exact) adds two
number sorts implemented with the GMP library ([exact.c](exact.c)):
`integer` (any size) and `rational` (fractions). Load it after `inc/all`:

```text
INC "inc/all"
INC "inc/exact"
1/3 + 1/6           # prints (1/2)
2^100               # prints 1267650600228229401496703205376
(2/3)^-2            # prints (9/4)
1/3 + 0.5           # prints 0.833333 (a real number is involved)
sin(1/2)            # prints 0.479426
```

After `inc/exact`, a number written without a point or exponent is an
`integer`; `0.5` stays `real`. Sorts are static: the sort of a term is
known from its parts when it is built, and a value never changes its sort
at run time. Two statements connect the sorts:

| Command | Meaning |
| --- | --- |
| `SUBSORT integer,rational ATT int2rat` | Every `integer` is also a `rational`; the C function converts a value. A sort may have several wider sorts. |
| `INTNUM integer ATT read_int` | Numbers without point and exponent are of sort `integer`, made by the C function from the text. |

With `integer < rational < real`, a function declared for `real` also
accepts `integer` and `rational` arguments, and the values are converted
when it is calculated. If several variants of an operator fit, the one
with the fewest conversions is used: `1/3+1/6` uses the rational `+`,
`1/3+0.5` the real one. With `LIFT`, `rational` inherits the rules of
`real`, and `integer` those of `rational`, so `x*1+0*x+(1/2)*x` simplifies
to `(3/2) * x`. When a rule is applied, the operators of the new term are
chosen again for the sorts of their actual arguments, so a rule written
for `real` gives exact results for exact numbers.

**Sorts with a known sign.** A sort can have several wider sorts.
`inc/exact` declares

```text
natural < integer < rational < real
natural < nonneg < real          positive < nonneg
```

Numbers written without a point are `natural`; `2-5` is the `integer` -3.
`nonneg` (values >= 0) and `positive` (> 0) are real numbers whose sign is
known. A meta variable of such a sort only matches terms of that sort or
below it (a variable of sort `real` still matches any term). Rules that are
wrong for negative numbers are written for these sorts:

```text
CONST t : nonneg
CONST p : positive
REWR sqrt(t^2) : All       # prints t
REWR sqrt(x^2) : All       # stays sqrt (x ^ 2 ) for a real x
REWR ln(p*x) : All         # prints ln (p )+ ln (x )
```

The rule-based integration ([inc/integration](inc/integration)) loads
`inc/exact` itself; do not load it a second time.

### Term variables and assignments

```text
TERM tt,qq : real
tt = a+b
tt*2                # prints (a + b )* 2
%+1                 # prints (a + b )* 2 + 1
qq = x^y*a          # a term behaves like a function qq(x,y,a)
x=4
y=2
a=3
qq                  # prints 48
```

- `Termname = term` stores the term. Assigning a term variable to another
  one copies its content, so later changes do not propagate.
- `Constname = value` gives a constant a value. If the value cannot be
  calculated, the constant loses its value and is printed by its name again.
  The library constant `nothing` never has a value, so `a = nothing` clears
  `a` (for constants of any sort):

```text
a = 3
a + 1               # prints 4
a = nothing
a + 1               # prints a + 1
```

### Control flow

| Command | Meaning |
| --- | --- |
| `FOR c = n1 TO n2 [STEP n3] DO block` | Loop over a constant. Example: `FOR n = 3 TO 1 STEP -1 DO n` |
| `IF (cond) block [ELSE block]` | Condition with a boolean result. Example: `IF (n > 3) "big" ELSE "small"` |
| `WHILE (cond) block` | Loop. Example: `WHILE (n < 100) n = n*2` |
| `{ ... }` | Block. Constants declared in a block are local to it. |

```text
FOR n = 1 TO 3 DO { CONST s : real
                    s = n*10
                    PRT s }
```

This prints `10 20 30`.

### Input and output

| Command | Meaning |
| --- | --- |
| `INC "file"` | Reads and executes a file. Includes can be nested. An `INC` line cannot be continued with `\`. Inside a block, the declarations of the included file are global. |
| `PRT list` | Prints without a line break at the end. |
| `PRTNUM "format"` | Sets the C format for printing real numbers. Example: `PRTNUM "%.10g "` |
| `OUT "file"` | Redirects the output into a file, which is overwritten. `OUT "stdout"` switches back. Useful for producing data for plotting programs. |
| `DATA "file"` | Opens a data file. |
| `DATA Const` | Reads the next number from the data file into `Const`. Non-numeric text up to the end of the line is skipped. |
| `SYS "command"` | Runs a shell command. |
| `DEBUG n` | Sets the debug level of the interpreter. |
| `STEPS Alg "file"` | Shows each applied rule of the rule list of `Alg` (solution steps), labelled from `file` (lines `index<TAB>label<TAB>text`); `STEPS Alg ""` switches it off. |
| `QUIT` | Ends the program. |

## The standard library

`INC "inc/all"` loads the following files in this order. The comments in
the files are in German.

| File | Contents |
| --- | --- |
| [inc/exact](inc/exact) | Exact numbers: sorts `integer` and `rational` (GMP), subsorts of `real`. |
| [inc/alg](inc/alg) | Basic sorts (`real`, `bool`, `complex`, group, ring, field), operators, elementary functions, simplification rules and differentiation. Defines the rule list `All`. Besides `sin`, `ln`, `exp` and so on, it has `csc`, `sec`, `cot`, `arccot`, `sinh`, `cosh`, `tanh`, `coth`, `sech`, `csch`, `arcsinh`, `arccosh`, `arctanh`, `arccoth`, `polylog(n,x)` and `productlog` (Lambert W), and special functions (see below), each with a derivative rule. |
| [inc/pdiff](inc/pdiff) | Partial derivatives. |
| [inc/rvector](inc/rvector) | Real vectors `[1,2,3]`, scalar product, cross product `_x_`, `abs`, element access. |
| [inc/rmatrix](inc/rmatrix) | Real matrices: `einsmat`, `nullmat`, `chmat`, `trans`, products. Indices start at 0. |
| [inc/physik](inc/physik), [inc/theophys](inc/theophys), [inc/lagrange](inc/lagrange) | Physical units and formulas, Lagrange formalism. |
| [inc/physnum](inc/physnum), [inc/mathnum](inc/mathnum) | Numerical values of physical and mathematical constants such as `c`, `e` and `pi`. |
| [inc/eqnsolve](inc/eqnsolve) | Solving equations. |
| [inc/numerik](inc/numerik) | Numerics with the rule lists `numerik,rechne`: integral `I(a,b,f,x)`, Newton zero `newton(start,f,f',x)`, `fmin`, `fmax`, `flzero`, `flext`. |
| [LiNbO3/comp](LiNbO3/comp) | Material constants of lithium niobate crystals. |

Note that the library defines many short names, for example `c` (speed of
light), `e`, `pi`, `i` (imaginary unit), `x`, `y`, `z`, `a`, `b`, `n`.
Some examples:

```text
(1+2*i)*(3-i)                     # prints (5,5)
[1,2,3]*[4,5,6]                   # prints 32
3!                                # prints 6
REWR newton(1,x^2-2,D(x^2-2,x),x) : numerik,rechne    # prints 1.41421
REWR fmin(-1,1,(x-0.3)^2,x) : numerik,rechne          # prints 0.3
```

### Rule-based integration

[inc/integration](inc/integration) adds indefinite integration with a
translation of a subset of the [Rubi](https://github.com/RuleBasedIntegration/Rubi)
rules (MIT license). It covers powers of linear expressions, exponentials,
sine and cosine, and polynomials times them, also with symbolic
coefficients:

```text
INC "inc/integration/all"
REWR Int(x^2*cos(x),x) : Integrate      # prints 2 * cos (x )* x + x ^ 2 * sin (x )- 2 * sin (x )
REWR Int(1/(2*x+3),x) : Integrate      # prints (1/2) * ln (3 + 2 * x )
REWR Int(sin(a*x+b),x) : Integrate     # prints - cos (a * x + b )/ a
```

With [inc/integration/rubi](inc/integration/rubi), about 90% of
all Rubi rules are available. They are translated automatically by
[tools/rubi2rewrite.py](tools/rubi2rewrite.py):

```text
INC "inc/integration/rubi/all"
REWR Int(x/(1+x^4),x) : RubiIntegrate        # prints (1/2) * arctan (x ^ 2 )
REWR Int(sqrt(x)/(1+x),x) : RubiIntegrate    # prints 2 * x ^ (1/2) - 2 * arctan (x ^ (1/2) )
```

See [inc/integration/README.md](inc/integration/README.md) for what is
covered and how the rules are translated.

### Special functions

[inc/alg](inc/alg) declares special functions, implemented in
[specfun.c](specfun.c) with Mathematica's definitions and parameter
conventions (so that the translated Rubi rules can use them), each with a
derivative rule:

| Function | Meaning |
| --- | --- |
| `arcsec`, `arccsc`, `arcsech`, `arccsch` | inverse secant, cosecant and their hyperbolic forms |
| `erf`, `erfc`, `erfi` | error functions |
| `fresnels`, `fresnelc` | Fresnel integrals of `sin(pi t^2/2)`, `cos(pi t^2/2)` |
| `sinint`, `cosint`, `sinhint`, `coshint` | sine and cosine integrals Si, Ci, Shi, Chi |
| `expint(x)`, `expinte(n,x)`, `logint(x)` | exponential integrals Ei, E_n and the logarithmic integral li |
| `Gamma(a)`, `Gamma(a,x)`, `loggamma`, `polygamma(n,x)` | Gamma function, upper incomplete Gamma function, log and polygamma |
| `zeta(s)`, `zeta(s,a)` | Riemann and Hurwitz zeta functions |
| `elliptick(m)`, `ellipticf(phi,m)`, `elliptice(m)`, `elliptice(phi,m)`, `ellipticpi(n,m)`, `ellipticpi(n,phi,m)` | elliptic integrals with the parameter `m` |
| `hyp2f1(a,b,c,z)`, `appellf1(a,b1,b2,c,x,y)`, `besselj(nu,x)` | hypergeometric functions and the Bessel function |

`Gamma` is written with a capital G because `gamma` is a constant in
[inc/physik](inc/physik). Outside their real domain the functions give NaN.

### Symbolic helper functions

[inc/helpers](inc/helpers) declares helper functions written in C
([symfkt.c](symfkt.c)). Unlike numerical functions, they work on the terms
themselves. Their names follow the helpers of Rubi in lower case. They are
loaded by the integration rules and can also be used on their own:

| Function | Meaning |
| --- | --- |
| `freeq(u,x)` | `x` does not occur in `u` |
| `integerq(u)`, `integersq(u,v,..)`, `rationalq(u,..)` | `u` is an integer, all are integers, all are numbers |
| `posq(u)`, `negq(u)` | `u` has a positive or negative form (a symbol counts as positive) |
| `eqq(u,v)`, `neq(u,v)` | `u` equals `v`, numerically or as the same term |
| `igtq(u,n)`, `iltq(u,n)` | `u` is an integer greater or less than `n` |
| `polyq(u,x)`, `polyq(u,x,n)`, `linearq(u,x)` | `u` is a polynomial in `x`, of degree `n`, of degree 1 |
| `sumq(u)`, `productq(u)`, `powerq(u)` | form of the top level of `u` |
| `expand(u)` | multiply out products and integer powers of sums, collect like terms |
| `expandintegrand(u,x)`, `expandintegrand(u,v,x)` | partial fractions of a rational function with exact coefficients, else `expand(u)`, `expand(u*v)`; stays unevaluated if no sum results |
| `coeff(u,x,n)`, `coeff(u,x)`, `expon(u,x)` | coefficient of `x^n` or `x`, degree in `x` |
| `subst(u,x,v)` | `u` with `x` replaced by `v` (waits while `u` contains `Int`) |
| `simp(u,x)`, `simplify(u)`, `dist(u,v,x)`, `rt(u,n)` | `u` with like powers in a product combined, the same, `u*v`, `n`-th root |
| `intpart(u)`, `fracpart(u)` | integer and non-integer parts of numbers |
| `fractionq(u,..)`, `halfintegerq(u,..)`, `nicesqrtq(u)` | non-integer numbers, halves of odd integers, a number > 0 |
| `gcd(m,n,..)`, `numerator(u)`, `denominator(u)` | for numbers (as fractions) and for products (negative powers) |
| `freefactors(u,x)`, `nonfreefactors(u,x)` | product of the factors of `u` that do not or do contain `x` |
| `expandtosum(u,x)`, `expandtosum(u,v,x)` | polynomial `u` as `c0+c1*x+...`; `u` times that of `v` |
| `polyquotient(p,q,x)`, `polyremainder(p,q,x)` | polynomial division |
| `normpoly(u,x)` | every polynomial sum in `u` as `c0+c1*x+...` with collected coefficients |
| `deriv(u,x)` | derivative of elementary functions (stays unevaluated otherwise) |
| `collect(u)` | like summands combined, e.g. `2*a+b-a` gives `a+b` |
| `replaceall(u,x,v)` | `u` with `x` replaced by `v` at once |
| `expandtrigreduce(u,x)`, `expandtrigreduce(v,u,x)` | products and powers of `sin`, `cos`, `sinh`, `cosh` as sums of multiple angles, e.g. `sin(x)^3` gives `(3/4)*sin(x) - (1/4)*sin(3*x)`; times `v` |
| `binomialq(u,x)`, `binomialdegree(u,x)`, `trinomialq(u,x)`, `quadraticq(u,x)` | `u` is `a+b*x^n` (and its `n`), `a+b*x^n+c*x^(2n)`, a quadratic |
| `binomialmatchq`, `quadraticmatchq`, `linearmatchq` | `u` is literally written as `a+b*x^n`, `a+b*x+c*x^2`, `a+b*x` |
| `rationalfunctionq(u,x)`, `algebraicfunctionq(u,x)`, `inversefunctionfreeq(u,x)` | kind of function of `x` |
| `leafcount(u)`, `simplerq(u,v)`, `sumsimplerq(u,v)`, `simplersqrtq(u,v)` | size of a term (as Mathematica's `LeafCount`) and Rubi's simplicity comparisons |
| `knownsineintegrandq(u,x)` (also `tangent`, `cotangent`, `secant`), `piecewiselinearq`, `linearpairq` | Rubi's tests for integrands it knows |
| `functionofq(v,u,x)`, `substfor(h,v,u,x)` | `u` is a function of `v` (also through identities: `cos(w)^2 = 1-sin(w)^2`, ...); `h*u` with `v` replaced by `x` |
| `substexp(u,x)`, `intsubst(u,x,v)`, `hyp2exp(u,x)` | Rubi's substitution `x -> F^(g x)` for functions of exponentials; `Subst[Int[u,x],x,v]`; hyperbolic functions as exponentials |
| `nonsumq(u)` | `u` is no sum |
| `derivdivides(y,u,x)`, `falseq(u)` | `u/y'` if it is free of `x` (else unevaluated); `u` is an unevaluated helper, i.e. Rubi's `False` |
| `trignorm(u,x)`, `removecontent(u,x)` | `1/sin = csc` and Rubi's `FixInertTrigFunction` for products of trig functions; `u` without constant factors, `cos(pi/2+x)` as `-sin(x)` |
| `substfracpow(u,x)`, `substsqrtquad(u,x)` | Rubi's substitutions `t = (a+b*x)^(1/n)` and Euler's for `sqrt(a+b*x+c*x^2)` (the transformed integral) |
| `gtq(u,v)`, `ltq`, `geq`, `leq` | Rubi's `GtQ`, ...: false unless both are numbers |

The predicates return true or false and can be used in conditions, also
combined with `&&` and `||`:

```text
INC "inc/helpers"
FUNC sq : real,real >> real
ALG t2
SPEC t2 : IF (polyq(A,X) && (expon(A,X) == 2)) sq(A,X) = coeff(A,X,2)
REWR sq(3*x^2+1,x) : t2              # prints 3
REWR expand((x+1)^3) : t2            # prints x ^ 3 + 3 * x ^ 2 + 3 * x + 1
```

The term functions are applied during rewriting, so they are used with
`REWR`. Some are simpler than their Rubi counterparts. `expandintegrand`
splits a rational function with exact rational coefficients into partial
fractions ([apart.c](apart.c), like Mathematica's `Apart`); the
denominator is factored into its square-free parts and rational roots, and
along the factors written in the input, but other irreducible factors of
degree 2 and more are not found. Otherwise it multiplies out, and writes a
polynomial times `(c+d*x)^n` as a sum of powers of `c+d*x`. `eqq` compares
terms after multiplying out, and `simp` only combines like powers in a
product, such as `(a*b)^-1*(a^-1*b^-1)^-1 = 1`.

Larger example programs are [LiNbO3/abso1](LiNbO3/abso1) and
[LiNbO3/compute](LiNbO3/compute) (X-ray absorption and structure factors
of LiNbO3), [inc/chaos](inc/chaos), [inc/molekuel](inc/molekuel) and
[inc/esrf1](inc/esrf1).

## Adding C functions

New numerical functions are written in C and entered in the list
`userfunction` in [userfkt.c](userfkt.c). A function gets an array of
pointers to its arguments and returns a pointer to a newly allocated result:

```c
double * r_abs (double * arg[]) { return mkreal(fabs(* arg[0])); }
```

Examples are in [real.c](real.c), [complex.c](complex.c),
[vector.c](vector.c) and [matrix.c](matrix.c). The function is then
connected with `ATT` in a `FUNC` or `OTHER` declaration.

Symbolic functions, which work on terms instead of numbers, are entered in
the list `symfunction` in [symfkt.c](symfkt.c). They get the argument terms
and return a new term, or `NULL` if they do not apply. `ATT name` finds them
in the same way.

## Source files

| File | Purpose |
| --- | --- |
| [scan.l](scan.l) | Scanner (flex). |
| [syn.y](syn.y) | Grammar (bison). The appendix of the manual summarizes it. |
| [sync.c](sync.c) | Main program, input handling and runtime commands. |
| [defs.c](defs.c) | Declarations, blocks and local symbols. |
| [run.c](run.c), [forms.c](forms.c) | Rewriting engine and numerical evaluation. |
| [expand.c](expand.c) | Settings `OPT`, `DEFAULT`, `COMM` and condition lists. |
| [listmatch.c](listmatch.c) | Rule lists with a backtracking matcher. |
| [symfkt.c](symfkt.c) | Symbolic helper functions (`expand`, `coeff`, `polyq`, ...). |
| [numsort.c](numsort.c), [exact.c](exact.c) | Subsorts (`SUBSORT`, `INTNUM`) and the exact number sorts with GMP. |
| [specfun.c](specfun.c) | Special functions (erf, Fresnel, Ei, Gamma, zeta, elliptic integrals, 2F1, ...). |
| [apart.c](apart.c) | Partial fractions of rational functions with exact coefficients (GMP). |
| [tools/rubi2rewrite.py](tools/rubi2rewrite.py) | Translator of Rubi's integration rules. |
| [tools/rubitest.py](tools/rubitest.py) | Runs Rubi's test suite and checks the results numerically. |
| [nodes.h](nodes.h) | Named access to the node structures built by the parser. |
| [sym.c](sym.c), [node.c](node.c), [stack.c](stack.c) | Symbol table and memory for nodes and symbols. |
| [userfkt.c](userfkt.c), [real.c](real.c), [bool.c](bool.c), [complex.c](complex.c), [vector.c](vector.c), [matrix.c](matrix.c) | Built-in numerical functions. |
| [inout.c](inout.c) | Output, output redirection and data input. |

## Known limitations

- Some memory is still not freed: a few bytes per syntax error, and the
  definitions themselves (symbols, rules, function bodies) when they are
  redefined. Repeated calculations, rewriting and loops no longer leak.
- Not every rule one might expect exists. For example `ln(exp x)` and
  `sin(x)^2+cos(x)^2` are not simplified.
- Symbols without a value may depend on any variable, so `D(a,x)` stays in
  the result. This is intended: differential equations use `D(y,x)`.
- There are no general container types. Vectors and matrices are
  implemented as C functions.
- Commutative matching only swaps the two operands of one operator; sums
  and products are binary trees, and their terms are not reordered across
  levels. The integration rules therefore bring polynomials into a fixed
  normal form first.
- Numbers are real numbers. Exact fractions and the complex results that
  Rubi or Mathematica would give are not available to the rule sets.
- `COMM` works by function name, so `COMM *` also applies to rules for
  matrix products. Switch it off with `COMM` after the rules that need it.

## Changes in 2026

- Ported to flex 2.6 and bison 3, and to 64-bit gcc on Linux and Windows.
- Fixed a crash when a constant was assigned 0 or 1 and later reassigned.
- Fixed a crash in the cleanup after arguments that cannot be calculated.
- Constants declared in loop bodies now work in every pass of the loop.
- `INC` inside a block or loop now works. Its declarations are global.
- `abs` for real numbers and `eabs` for vectors truncated to integers. Fixed.
- Fixed memory leaks: printed terms, term assignments, `REWR` results and
  intermediate rewriting steps, the numbers 0 and 1, `DATA` reads, local
  constants of blocks and user functions. Repeated operations now run in
  constant memory.
- The derivatives of `arcsin` and `arccos` used `1+x^2` instead of `1-x^2`.
  Fixed. New derivative rules for `exp`, `sqrt`, `sinh`, `cosh`, `tanh` and
  `abs`.
- Two wrong rules in [inc/alg](inc/alg) fixed: `ln(x+y)` was turned into
  `ln x * ln y` (now `ln(x*y) = ln x + ln y`), and `a^(b^c)` into `a^(b*c)`
  (now `(a^b)^c = a^(b*c)`).
- New folder [inc/integration](inc/integration) with rule-based integration
  translated from Rubi.
- New pattern features: optional parts (`OPT`, `DEFAULT`), commutative
  operators (`COMM`) and lists of conditions (`IF c1, c2`). A condition
  that cannot be calculated no longer crashes the interpreter.
- Symbolic helper functions in C ([symfkt.c](symfkt.c), [inc/helpers](inc/helpers))
  and further elementary functions (`csc`, `sec`, `cot`, `arccot`, the
  hyperbolic and inverse hyperbolic functions, `polylog`, `productlog`).
- Special functions ([specfun.c](specfun.c)) with derivative rules, and
  more of Rubi's helper functions in [symfkt.c](symfkt.c), among them
  partial fractions ([apart.c](apart.c)).
- Exact numbers: sorts `integer` and `rational` with GMP ([inc/exact](inc/exact)),
  the statements `SUBSORT` and `INTNUM`, and the choice of operator
  variants by the sorts of their arguments.
- Rule lists with a backtracking matcher for rules with `OPT`, `DEFAULT`
  and `COMM`, instead of expanding each rule into its variants. Rules that
  make no progress or give NaN are skipped, and `REWR` has a step limit.
- [tools/rubi2rewrite.py](tools/rubi2rewrite.py) translates about 90% of
  Rubi's rules automatically ([inc/integration/rubi](inc/integration/rubi),
  `RubiIntegrate`); [tools/rubitest.py](tools/rubitest.py) measures them
  with Rubi's test suite.
- Internal cleanup: named accessors for the node structures
  ([nodes.h](nodes.h)) instead of chains like `np->r->r->l`.
- [LiNbO3/abso1](LiNbO3/abso1) runs again, and the test suite was added.

## License

MIT, see [LICENSE](LICENSE).
