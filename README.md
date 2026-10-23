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
INC "inc/all"
REWR D(sin cos x,x) : All
- cos (cos (x ))* sin (x )
REWR D(x^2*sin x,x) : All
2 * x * sin (x )+ x ^ 2 * cos (x )
REWR I(0,1,x^2,x) : numerik,rechne
0.333333
sqrt(16), ln(e), sin(pi/2)
4 1 1
[1,0,0] _x_ [0,1,0]
[0,0,1]
QUIT
```

`INC "inc/all"` loads the standard library. `REWR term : All` rewrites the
term with the rule list `All`, here computing the derivative of
`sin(cos(x))`. A program can also be read from a file:

```text
rewrite < myprogram
```

Paths in `INC` and `DATA` are relative to the current directory, so start
`rewrite` in the project folder when you use the standard library.

## Building

You need `gcc`, `flex`, `bison` and `make`.

**Linux:**

```text
make
make test
```

**Windows:** install [MSYS2](https://www.msys2.org), for example with
`winget install MSYS2.MSYS2`. Then open the MSYS2 shell once and install
the tools:

```text
pacman -S mingw-w64-ucrt-x86_64-gcc flex bison make diffutils
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
- `(term)`: any expression with a boolean result, for example
  `(is_int(N))` or `(N > 0)`.

Several conditions are combined with a logical and. With `DO block`, the
block is executed before the left side is replaced by the right side.

```text
VAR A : real
ALG simp
SPEC simp : A*1=A
ADDSPEC simp : A+0=A
CONST u : real
REWR (u*1)+0 : simp         # prints u
```

The trick behind `LIFT`: once the group rules for `+` and `-` are written,
the ring rules for `*` and `/` can be derived from them:

```text
LIFT (Aag+Aag,Aag-Aag,-Aag,0ag) TO (Ar+Ar,Ar-Ar,-Ar,0r)
LIFT (Aag+Aag,Aag-Aag,-Aag,0ag) TO (Ar*Ar,Ar/Ar,mi(Ar),1r)
```

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
| `QUIT` | Ends the program. |

## The standard library

`INC "inc/all"` loads the following files in this order. The comments in
the files are in German.

| File | Contents |
| --- | --- |
| [inc/alg](inc/alg) | Basic sorts (`real`, `bool`, `complex`, group, ring, field), operators, elementary functions, simplification rules and differentiation. Defines the rule list `All`. |
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

## Source files

| File | Purpose |
| --- | --- |
| [scan.l](scan.l) | Scanner (flex). |
| [syn.y](syn.y) | Grammar (bison). The appendix of the manual summarizes it. |
| [sync.c](sync.c) | Main program, input handling and runtime commands. |
| [defs.c](defs.c) | Declarations, blocks and local symbols. |
| [run.c](run.c), [forms.c](forms.c) | Rewriting engine and numerical evaluation. |
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
- [LiNbO3/abso1](LiNbO3/abso1) runs again, and the test suite was added.

## License

MIT, see [LICENSE](LICENSE).
