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

**Profiling.** With the environment variable `REWRITE_PROFILE=1`, rewrite
prints at the end how often each symbolic helper was called and how much
time it took, together with the time of the rule matching, of the
evaluation of right-hand sides and of the checks for progress:

```text
REWRITE_PROFILE=1 ./rewrite.exe < problem.rw
```

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
| `FUNC name : sorts >> sort [LA1..LA5\|RA\|RU] [ATT [SYMBOLIC [HOLD]] name \| ATT RULES alglist]` | Defines a function or operator, see below. |
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
`userfunction` in [userfkt.c](src/userfkt.c). It is called when all arguments
have numerical values. Otherwise the function stays symbolic.
`ATT SYMBOLIC name` connects it to a symbolic C function in
[symfkt.c](src/symfkt.c) instead, which gets the argument terms (see
[Symbolic helper functions](#symbolic-helper-functions));
`ATT SYMBOLIC HOLD name` passes them unevaluated.

A function can also be written in the rewrite language itself, with
`ATT ( argument definitions ) block`:

```text
FUNC fma3 : real,real,real >> real ATT (CONST aa,bb : real; TERM cc : real) { RETURN cc+aa*bb }
fma3(2,3,4)          # prints 10
fma3(2,3,y)          # y has no value: prints fma3 (2 ,3 ,y )
```

`RETURN term` sets the result of such a function. It does not end the
function.

**Functions defined by rules.** With `ATT RULES alglist` a function is
calculated by rewriting: `f(a,b)` becomes `REWR f(a,b) : alglist`. If the
result is still a call of `f`, the function does not apply and the call
stays as it is. Unlike the other functions, it is also calculated when its
arguments are terms, also in the condition of a rule and from the C helpers.
While its rule list works on a call, `f` is not calculated again: the rules
rewrite the inner calls themselves. The rules are added after the
declaration, so the algebra is declared first:

```text
ALG PdDef
ALG PdConst
FUNC pd : real,real >> real ATT RULES PdDef,(PdConst,Linear,diff)
SPEC PdDef : pd(X,Y) = D(X,Y)
SPEC PdConst : IF NIN(Z,X) D(X,Z) = 0     # every term without x is constant
REWR pd(nn*sin(x)^2,x) : All              # prints 2 * cos (x )* sin (x )* nn
```

This is how knowledge of the library reaches the C helpers: the derivative
`deriv` of [inc/helpers](inc/helpers) is defined like `pd` above, with the
rules `diff` of [inc/alg](inc/alg), and Rubi's `FixInertTrigFunction` is the
rule function `fixinert`, translated from Rubi.

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
matches wins. The matcher ([listmatch.c](src/listmatch.c)) tries the swapped
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
number sorts implemented with the GMP library ([exact.c](src/exact.c)):
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
| `SHOW f ATT name` | Prints the terms with the function `f` (all its variants) with the C print function `name` instead of the usual form; `SHOW f` alone switches back. [inc/list](inc/list) uses it for lists (`show_list`). |
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

**Precedence of variants.** A variant that fits the argument sorts exactly
is always used; conversions are only the fallback, and among the variants
reached by conversions the one with the fewest wins, like the most
specific method in Julia. [inc/alg](inc/alg) declares `real < complex`
(`SUBSORT real,complex ATT real2cpx`): functions for complex numbers also
take real ones (`Re(2.5)` is 2.5), while the explicit mixed variants such as
`+ : real,complex` keep precedence over converting the real number. If two
variants need equally many conversions (a `natural` argument fits both an
`integer` and a `nonneg` variant), the first declared one is used and a
warning names the function and the argument sorts, once; a more specific
variant resolves it, as `/ : natural,natural` in [inc/exact](inc/exact):

```text
FUNC tst : complex >> real ATT c_real
OTHER tst : real >> real ATT r_abs
tst(-2.5)            # prints 2.5: the real variant fits exactly
tst(-2.5+i)          # prints -2.5: the complex one
```

**The sort `number`.** [inc/alg](inc/alg) also declares the sort `number`
for symbolic scalar expressions, above `real` and `complex` (`SUBSORT
real,number`, `SUBSORT complex,number`), like `Number` in Julia. The
arithmetic and the elementary and special functions have variants on
`number` without a C function; they only stand for the symbolic term.
A term becomes of sort `number` only when one of its parts is, such as the
imaginary unit `im` of [inc/integration/base](inc/integration/base); a term
of reals keeps its real variants and is calculated as before. Rules written
with variables of sort `number` apply to every term below it:

- A variable whose sort has no wider sort (`number`) matches any term, and
  a function in a pattern whose variant is declared on such sorts
  (`+ : number,number`) also matches its narrower variants (`+ :
  real,real`, `+ : complex,real`), as a method for `Number` in Julia
  applies to `Float64`. Variants on sorts below others (`real`, `integer`)
  still match only themselves, so the older libraries are unchanged.
- After a rule is applied, the operators of the new term are chosen again
  for the sorts of the actual arguments, and a condition such as `m > 0`
  or `integerq(2*m)` is calculated with the real or exact variant, so
  `Int(3,x)` satisfies a rule `IF (Uq > 2) Int(Uq,Xv) = ...` written for
  `number`.

The derivative rules (ALG `diff`) and the Rubi rules are written for
`number` in this way, so `deriv(sin(im*x),x)` gives `im*cos(im*x)` and
`REWR Int(sin(im*x),x) : RubiIntegrate` gives `im * cos (im * x )`. The
general simplification `All` is still written for `real`.

**Roots.** A power of exact numbers is exact when the result is
rational: `4^(1/2)` is 2, `(8/27)^(2/3)` is `(4/9)`. Otherwise it stays a
term inside a term, in the normal form Mathematica uses: perfect powers
are taken out and the exponent is reduced, so `8^(1/2)` becomes
`2 * 2 ^ (1/2)`, `(4/3)^(1/2)` becomes `2 * 3 ^ (-1/2)`, `(2^(1/2))^2`
becomes 2, and in a simplified product `2/2^(1/2)` becomes `2^(1/2)`. A
real number makes the expression numeric, as in Mathematica
(`x*2^(1/2)*0.5` gives `0.707107 * x`). Asking for the value of a closed
expression (`2^(1/2)` on its own) still prints the real number 1.41421.

```text
REWR x*8^(1/2) : All          # prints 2 * 2 ^ (1/2) * x
REWR x*(4/3)^(1/2) : All      # prints 2 * 3 ^ (-1/2) * x
REWR x*2^(1/2)*0.5 : All      # prints 0.707107 * x
```

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
| `SYMBOLIC "role" = "symbol"` | The symbolic C functions (helpers) use `symbol` where they need the function or constant `role` (`"cos"`, `"+"`, `"pi"`, ...), see [Symbolic helper functions](#symbolic-helper-functions). `SYMBOLIC` alone clears the mapping. |
| `STEPS Alg "file"` | Shows each applied rule of the rule list of `Alg` (solution steps), labelled from `file` (lines `index<TAB>label<TAB>text`); `STEPS Alg ""` switches it off. |
| `QUIT` | Ends the program. |

## The standard library

`INC "inc/all"` loads the following files in this order. The comments in
the files are in German.

| File | Contents |
| --- | --- |
| [inc/list](inc/list) | Lists as terms, `list(a,b,c)` and `nil`, with `part`, `length`, `table`, `select`, ... (load it after `inc/all`). |
| [inc/solve](inc/solve) | Equations: `solve(lhs == rhs, x)` with PRESS-style rules (isolation, polynomials, a new unknown, ...), linear systems (load it after `inc/list`). |
| [inc/linalg](inc/linalg) | Symbolic matrices on lists: `transpose`, `dot`, `identity`, `det`, `linsolve`, `inverse`, `thread` (load it after `inc/list`). |
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
[specfun.c](src/specfun.c) with Mathematica's definitions and parameter
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

### Lists

[inc/list](inc/list) adds lists, as terms with the head `list`, like
Mathematica's `List`: `list(a,b,c)`, the empty list `nil`, and lists of
lists. Their elements and results have the sort `real`, so that lists nest
freely; the sort system cannot know the sort of `part(m,1)` before the list
is there. The functions are symbolic C functions, so their results are seen
with `REWR` (a plain expression is calculated numerically), and they stay
unevaluated if an argument is no list:

| Function | Meaning |
| --- | --- |
| `list(a,b,..)`, `nil` | a list, the empty list |
| `listq(u)`, `length(l)` | `u` is a list; the number of elements |
| `part(l,i)`, `part(l,i,j)` | element `i` (from 1, `-1` is the last), element `j` of element `i` |
| `first(l)`, `last(l)`, `rest(l)`, `most(l)` | first, last element; without the first, without the last |
| `append(l,x)`, `prepend(l,x)`, `join(l1,l2,..)`, `reverse(l)` | |
| `range(n)`, `range(a,b)`, `range(a,b,d)` | `1..n`, `a..b` in steps of 1 or `d` |
| `table(body,x,l)`, `table(body,x,n)` | `body` for each `x` in `l` (or `1..n`), Mathematica's `Table` |
| `select(l,x,cond)` | the elements `x` of `l` for which `cond` is true |
| `total(l)` | the sum of the elements |

Lists are printed by their shape, as Julia prints arrays: inline as
`{a, b, {c, d}}`, and a rectangular list of lists that is the whole printed
term as a grid with aligned columns (numbers right-aligned), deeper ones in
slices `[1, :, :] = ...`. This is a print function attached with
`SHOW list ATT show_list`; `SHOW list` prints `list(a,b)` again, in the form
that can be read back.

```text
REWR identity(2) : All          # [ 1  0 ]
                                # [ 0  1 ]
REWR list(1,list(2,3)) : All    # {1, {2, 3}}
```

`table` and `select` get their body and condition unevaluated (`HOLD`) and
replace `x` first. `x` must be declared (`CONST kk : real`): an undeclared
name is a numerical variable with the value 0.

```text
INC "inc/list"
CONST aa,kk : real
REWR table(aa^kk, kk, range(3)) : All           # {aa, aa ^ 2, aa ^ 3}
REWR select(range(10), kk, kk > 6) : All        # {7, 8, 9, 10}
REWR part(list(list(1,2),list(3,4)), 2, 1) : All   # 3
```

### Symbolic matrices

[inc/linalg](inc/linalg) (load it after `inc/list`) works with matrices as
lists of rows, `list(list(a,b),list(c,d))`, and vectors as lists. The
entries may be any terms. The functions are symbolic C functions
([symmat.c](src/symmat.c)):

| Function | Meaning |
| --- | --- |
| `transpose(m)`, `identity(n)` | rows as columns; the n x n unit matrix |
| `dot(a,b)` | matrix product, matrix times vector, scalar product (like terms collected, sums not multiplied out) |
| `det(m)` | determinant |
| `linsolve(m,b)` | the solution `x` of `m.x = b`, `b` a vector or a matrix (several right-hand sides); unevaluated if `m` is singular |
| `inverse(m)` | the inverse matrix |
| `thread(u)` | arithmetic and functions of lists element by element: `list(1,2)*x + list(a,b)` is `list(x+a, 2*x+b)` |

`det`, `linsolve` and `inverse` use Bareiss' fraction-free elimination:
the entries become sparse polynomials in their atoms (every factor that is
no number and no natural power, such as `sin(x)`, `a^-1` or `2^(1/2)`), and
every division during the elimination is an exact division of polynomials,
so no nested fractions arise. A solution is a polynomial divided by the
determinant; common monomial factors, a common polynomial factor in a
single atom and integer contents are cancelled (`1/(a+2)`), a common
factor of several variables is not yet. The matrix functions thread their
arguments first, so `det(m - x*identity(2))` is the characteristic
polynomial of `m`; the rule set `Listable` does this for any term, like
Mathematica's `Listable` functions:

```text
INC "inc/list"
INC "inc/linalg"
CONST g : real
REWR det(list(list(a,b),list(g,n))) : All                    # a * n - b * g
REWR linsolve(list(list(a,1,1),list(1,a,1),list(1,1,a)),list(1,1,1)) : All
                                                             # {1 / (2 + a ), 1 / (2 + a ), 1 / (2 + a )}
REWR det(list(list(2,1),list(1,2)) - x*identity(2)) : All    # 3 + x ^ 2 - 4 * x
REWR list(1,2)*x + list(a,b) : Listable                      # {x + a, 2 * x + b}
```

### Equations

[inc/solve](inc/solve) solves equations with rules in the style of PRESS
(Bundy and Welham 1981), where the form of the equation chooses the
method. `solve(lhs == rhs, x)` gives the list of the solutions (`nil` if
there is none) and stays unevaluated if no method applies; `==` is the
symbolic equation here. The methods for `f = lhs - rhs = 0` are tried in
this order:

| Method | Applies when | Example |
| --- | --- | --- |
| isolation | `x` occurs once: the functions around it are inverted | `(x+1)^3 = 8`, `exp(2x+1) = 5`, `sin(x) = 1/2` |
| polynomials | degree 1 and 2, `x^n = c`, polynomials in `x^2`, rational roots; after a common denominator | `x^3 - 6x^2 + 11x - 6 = 0`, `1/x + 1/(x+1) = 1` |
| attraction | several logarithms with `x`: `ln(u) + ln(v) = ln(u v)` | `ln(x) + ln(x+1) = ln(6)` |
| new unknown | `f` is a polynomial in `g(x)` (`exp(c x)`, `x^(1/n)`, `sin(x)`, ...) | `exp(2x) - 3 exp(x) + 2 = 0`, `x + sqrt(x) - 6 = 0` |
| radicals | `a + b c^(1/2) = 0` is squared to `a^2 - b^2 c = 0` | `sqrt(x+1) = x - 1` |

Complex roots use the imaginary unit `im`; trigonometric equations give
the principal solutions, as Mathematica's `Solve` without the integer
constant. Every solution is checked (numerically where possible), so the
extra solutions of squaring and those that make the equation undefined are
removed. A system of linear equations, `solve(list(eq1, eq2), list(x, y))`,
gives the list of the values of the unknowns, solved with Bareiss'
elimination of [inc/linalg](inc/linalg); nonlinear systems stay unevaluated.
The analysis is done by C helpers ([symsolve.c](src/symsolve.c)), the
methods themselves are an ordered rule list.

```text
INC "inc/all"
INC "inc/integration/all"       # im
INC "inc/list"
INC "inc/solve"
REWR solve(x^2 + 4*x + 7 == 0, x) : Solve               # {3 ^ (1/2) * im - 2, -2 - 3 ^ (1/2) * im}
REWR solve(exp(2*x) - 3*exp(x) + 2 == 0, x) : Solve     # {0.693147, 0}
REWR solve(sqrt(x+1) == x - 1, x) : Solve               # {3}
REWR solve(list(x + y == 3, x - y == 1), list(x, y)) : Solve   # {2, 1}
```

Numbers in the results are calculated: `ln(2)` prints as `0.693147`.

### Symbolic helper functions

[inc/helpers](inc/helpers) declares helper functions written in C
([symfkt.c](src/symfkt.c)) with `ATT SYMBOLIC`. Unlike numerical functions,
they work on the terms themselves: they get the argument terms and return a
new term, or nothing if they do not apply (then the call stays as it is).
Their names follow the helpers of Rubi in lower case. They are loaded by the
integration rules and can also be used on their own.

The helpers know the operators and functions of the library through
**roles**: `"+"`, `"*"`, `"^"`, `"-"`, `"/"`, `"mi"` (1/x), `"sin"`, `"cos"`,
..., `"ln"`, `"exp"`, the constants `"pi"` and `"eE"`, `"Int"` and `"D"`. By
default a role is played by the symbol of the same name, which fits
[inc/alg](inc/alg). A library with other names maps them; all variants of an
operator for different sorts count as the same function:

```text
FUNC kos : real >> real ATT cosinus
SYMBOLIC "cos" = "kos"                    # kos is the cosine for the helpers
REWR expandtrigreduce(kos(x)^2,x) : All   # prints 0.5 + 0.5 * kos (2 * x )
SYMBOLIC                                  # back to the names
```

The helpers assume the usual properties of these roles: `+` and `*` are
commutative and associative, `mi(x)` is 1/x, `cos` is the cosine, and so on.
The rules themselves make no such assumptions. Where a helper needs more
than the name, such as a derivative, it uses a function of the library
defined by rules (`ATT RULES`, see above), so that this knowledge stays in
the rules: `deriv` and `fixinert`.

`matchq(u, pattern, cond)` is Rubi's `MatchQ[u, pattern /; cond]` (the
translator also inlines Rubi's `LinearMatchQ`, `BinomialMatchQ`, ... as
`matchq`, from their definitions in Rubi's utility file): it tests
`u` against a pattern with the matcher of the rule lists (optional operands,
commutative operators, see [Rule sets](#rule-sets-algebras-and-rewriting)),
then the condition with the bindings, and undoes the bindings afterwards.
It is declared with `HOLD`, so that the pattern and the condition arrive
unevaluated; its pattern variables must not be bound by the rule that
calls it:

```text
SPEC tm : IF (matchq(Uu, (Mc+Md*Xx)^Mm, freeq(Mc,Xx) && freeq(Md,Xx))) lin(Uu,Xx) = 1
```

The helpers are:

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
| `deriv(u,x)` | derivative, every term without `x` constant; defined by rules (`ATT RULES`, the rules `diff` of inc/alg); `D(f(x),x)` remains for unknown functions |
| `collect(u)` | like summands combined, e.g. `2*a+b-a` gives `a+b` |
| `replaceall(u,x,v)` | `u` with `x` replaced by `v` at once |
| `expandtrigreduce(u,x)`, `expandtrigreduce(v,u,x)` | products and powers of `sin`, `cos`, `sinh`, `cosh` as sums of multiple angles, e.g. `sin(x)^3` gives `(3/4)*sin(x) - (1/4)*sin(3*x)`; times `v` |
| `binomialq(u,x)`, `binomialdegree(u,x)`, `trinomialq(u,x)`, `quadraticq(u,x)` | `u` is `a+b*x^n` (and its `n`), `a+b*x^n+c*x^(2n)`, a quadratic |
| `rationalfunctionq(u,x)`, `algebraicfunctionq(u,x)`, `inversefunctionfreeq(u,x)` | kind of function of `x` |
| `leafcount(u)`, `simplerq(u,v)`, `sumsimplerq(u,v)`, `simplersqrtq(u,v)` | size of a term (as Mathematica's `LeafCount`) and Rubi's simplicity comparisons |
| `knownsineintegrandq(u,x)` (also `tangent`, `cotangent`, `secant`), `piecewiselinearq`, `linearpairq` | Rubi's tests for integrands it knows |
| `functionofq(v,u,x)`, `substfor(h,v,u,x)` | `u` is a function of `v` (also through identities: `cos(w)^2 = 1-sin(w)^2`, ...); `h*u` with `v` replaced by `x` |
| `substexp(u,x)`, `intsubst(u,x,v)`, `hyp2exp(u,x)` | Rubi's substitution `x -> F^(g x)` for functions of exponentials; `Subst[Int[u,x],x,v]`; hyperbolic functions as exponentials |
| `hyp2trig(u,x)`, `imagfn(u)` | Rubi's `DeactivateTrig` for hyperbolic functions, `sinh(v) = -im*sin(im*v)`, ... (only for functions of trig or hyperbolic functions of linear arguments); back as Mathematica evaluates: `sin(im*w) = im*sinh(w)`, `arctan(im*w) = im*arctanh(w)`, `sin(-u) = -sin(u)`, ... |
| `nonsumq(u)` | `u` is no sum |
| `derivdivides(y,u,x)`, `falseq(u)` | `u/y'` if it is free of `x` (else unevaluated); `u` is an unevaluated helper, i.e. Rubi's `False` |
| `trignorm(u,x)`, `removecontent(u,x)` | `1/sin = csc` and Rubi's `FixInertTrigFunction` for products of trig functions; `u` without constant factors, `cos(pi/2+x)` as `-sin(x)` |
| `normform(u)` | the final form of a result in one pass: products with a sum as factor distributed, like summands combined, positive summands first, then `- ...`, negative powers as a denominator (used by `RubiIntegrate` instead of `All`) |
| `trigexpand(u,x)` | trig functions of multiples of one angle with `sin`, `cos` of the angle (Mathematica's `TrigExpand`); not for polynomials in sin and cos |
| `substfracpow(u,x)`, `substsqrtquad(u,x)` | Rubi's substitutions `t = (a+b*x)^(1/n)` and Euler's for `sqrt(a+b*x+c*x^2)` (the transformed integral) |
| `binomsum(u,x)` | `x^m/(a+b*x^n)` for odd `n` or `n = 2 mod 4` as a sum of integrals of linear and quadratic partial fractions with coefficients `cos(k*pi/n)` (exact for `n` up to 6) |
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
fractions ([apart.c](src/apart.c), like Mathematica's `Apart`); the
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
`userfunction` in [userfkt.c](src/userfkt.c). A function gets an array of
pointers to its arguments and returns a pointer to a newly allocated result:

```c
double * r_abs (double * arg[]) { return mkreal(fabs(* arg[0])); }
```

Examples are in [real.c](src/real.c), [complex.c](src/complex.c),
[vector.c](src/vector.c) and [matrix.c](src/matrix.c). The function is then
connected with `ATT` in a `FUNC` or `OTHER` declaration.

Symbolic functions, which work on terms instead of numbers, are entered in
the list `symfunction` in [symfkt.c](src/symfkt.c). They get the argument terms
and return a new term, or `NULL` if they do not apply, and are connected with
`ATT SYMBOLIC name` (or `ATT SYMBOLIC HOLD name` for unevaluated arguments;
plain `ATT name` also finds them if no numerical function has that name). To
recognize or build a term they use roles, not symbols: `is_head(t, "+", 2)`,
`fsym("cos")`, `role_find("pi")`; `SYMBOLIC "role" = "symbol"` maps them.

## Source files

The sources are in [src/](src) (the headers of the original project in
[src/include/](src/include)); `make` builds `rewrite` in the main folder,
where the library [inc/](inc) and the tests are used from.

| File | Purpose |
| --- | --- |
| [scan.l](src/scan.l) | Scanner (flex). |
| [syn.y](src/syn.y) | Grammar (bison). The appendix of the manual summarizes it. |
| [sync.c](src/sync.c) | Main program, input handling and runtime commands. |
| [defs.c](src/defs.c) | Declarations, blocks and local symbols. |
| [run.c](src/run.c), [forms.c](src/forms.c) | Rewriting engine and numerical evaluation. |
| [expand.c](src/expand.c) | Settings `OPT`, `DEFAULT`, `COMM` and condition lists. |
| [listmatch.c](src/listmatch.c) | Rule lists with a backtracking matcher. |
| [symfkt.c](src/symfkt.c) | Symbolic helper functions (`expand`, `coeff`, `polyq`, ...). |
| [numsort.c](src/numsort.c), [exact.c](src/exact.c) | Subsorts (`SUBSORT`, `INTNUM`) and the exact number sorts with GMP. |
| [specfun.c](src/specfun.c) | Special functions (erf, Fresnel, Ei, Gamma, zeta, elliptic integrals, 2F1, ...). |
| [apart.c](src/apart.c) | Partial fractions of rational functions with exact coefficients (GMP). |
| [symsolve.c](src/symsolve.c) | Helpers of the equation solver: polynomial roots, the new unknown, square roots, checking (included by symfkt.c). |
| [symmat.c](src/symmat.c) | Symbolic matrices on lists: Bareiss elimination on sparse polynomials (included by symfkt.c). |
| [tools/rubi2rewrite.py](tools/rubi2rewrite.py) | Translator of Rubi's integration rules. |
| [tools/rubitest.py](tools/rubitest.py) | Runs Rubi's test suite and checks the results numerically. |
| [nodes.h](src/nodes.h) | Named access to the node structures built by the parser. |
| [sym.c](src/sym.c), [node.c](src/node.c), [stack.c](src/stack.c) | Symbol table and memory for nodes and symbols. |
| [userfkt.c](src/userfkt.c), [real.c](src/real.c), [bool.c](src/bool.c), [complex.c](src/complex.c), [vector.c](src/vector.c), [matrix.c](src/matrix.c) | Built-in numerical functions. |
| [inout.c](src/inout.c) | Output, output redirection and data input. |

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
- Symbolic helper functions in C ([symfkt.c](src/symfkt.c), [inc/helpers](inc/helpers))
  and further elementary functions (`csc`, `sec`, `cot`, `arccot`, the
  hyperbolic and inverse hyperbolic functions, `polylog`, `productlog`).
- Special functions ([specfun.c](src/specfun.c)) with derivative rules, and
  more of Rubi's helper functions in [symfkt.c](src/symfkt.c), among them
  partial fractions ([apart.c](src/apart.c)).
- Exact numbers: sorts `integer` and `rational` with GMP ([inc/exact](inc/exact)),
  the statements `SUBSORT` and `INTNUM`, and the choice of operator
  variants by the sorts of their arguments.
- Rule lists with a backtracking matcher for rules with `OPT`, `DEFAULT`
  and `COMM`, instead of expanding each rule into its variants. Rules that
  make no progress or give NaN are skipped, and `REWR` has a step limit.
- [tools/rubi2rewrite.py](tools/rubi2rewrite.py) translates 96% of
  Rubi's rules automatically ([inc/integration/rubi](inc/integration/rubi),
  `RubiIntegrate`); [tools/rubitest.py](tools/rubitest.py) measures them
  with Rubi's test suite.
- Equations ([inc/solve](inc/solve)): `solve(lhs == rhs, x)` with rules in
  the style of PRESS, linear systems.
- Symbolic matrices on lists ([inc/linalg](inc/linalg)): `det`, `linsolve`,
  `inverse`, `dot`, `transpose` with fraction-free elimination; arithmetic
  on lists element by element.
- Lists as terms ([inc/list](inc/list)): `list(a,b,c)`, `part`, `table`,
  `select`, ...
- `SUBSORT real,complex`: complex functions take real arguments; exact
  variants keep precedence over conversions, ties are reported.
- The sort `number` above `real` and `complex` for symbolic expressions:
  rules written for `number` apply to real and complex terms, and the
  integration rules know the imaginary unit `im` (`im^2 = -1`).
- Functions defined by rule lists (`ATT RULES`), also usable in conditions
  and from C: the derivative `deriv` and Rubi's `FixInertTrigFunction`
  are rules now instead of C tables.
- Symbolic C functions are connected with `ATT SYMBOLIC` (`HOLD` for
  unevaluated arguments) and know the library's operators through roles,
  which `SYMBOLIC "role" = "symbol"` maps; `matchq` gives Rubi's `MatchQ`
  with the matcher of the rule lists.
- Internal cleanup: named accessors for the node structures
  ([nodes.h](src/nodes.h)) instead of chains like `np->r->r->l`.
- [LiNbO3/abso1](LiNbO3/abso1) runs again, and the test suite was added.

## License

MIT, see [LICENSE](LICENSE).
