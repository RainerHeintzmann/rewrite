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
> REWR I(0,1,x^2,x) : numerik,calc
0.333333
> sqrt(16), ln(e), sin(pi/2)
4 1 1
> [[1,2],[3,4]] * [5,6]
[17, 39]
> SYM a : real
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
`sin(cos(x))`. The library declares the variables `x`, `y`, `z`; other
names are declared with `SYM`. A symbol such as `a` either has a value or
stands for itself: `a = nothing` removes the value again, because the
library constant `nothing` never has one. Lists and matrices are written in
brackets; the product of matrices is the matrix product. `?REWR` (or `?` alone) shows
help, and [examples/](examples/README.md) has small programs to start from,
e.g. `rewrite examples/03_integration.rw`.

There are an interactive and a non-interactive way to run rewrite:

| Command | Mode |
| --- | --- |
| `rewrite` | Interactive: a welcome message, then a `>` prompt for each statement (`-->` inside an open block). |
| `rewrite file ...` | Runs the files one after the other (like `INC "file"`), then exits. |
| `rewrite -i file ...` | Runs the files, then continues interactively, e.g. with a library already loaded. |
| `rewrite < file` | Reads the program from a pipe or file, without welcome message and prompts (for scripts and the tests). |
| `rewrite -h` | Shows these options. |
| `rewrite --no-startup` | Interactive without the startup file. |
| `rewrite --max-steps n` | Sets the step limit of `REWR` (as `MAXSTEPS n`). |
| `rewrite --max-depth n` | Sets the depth limit of `REWR` (as `MAXDEPTH n`). |

An interactive session first runs the startup file `.rewrite/startup.rw`
if it exists, as Julia's `startup.jl`. It is looked for in `HOME` (in the
MSYS2 shell `C:\msys64\home\<user>`), then in the Windows profile folder
(`C:\Users\<user>`), so one file there serves all terminals. A UTF-8 byte
order mark (Notepad) at the start of a line is ignored.
Scripts and pipes do not run it. A line `INC "inc/all"` in it loads the
library in every session.

`QUIT` or the end-of-file key (Ctrl-D, on Windows Ctrl-Z and Enter) ends an
interactive session. Whether the input is interactive is decided by the
terminal: in the MSYS2 terminal (mintty), standard input is a pipe for
Windows programs, so use `rewrite -i` there to get the prompts.

A file in `INC` (such as `inc/all`) that is not found from the current
folder is looked for in the library folders: those listed in the
environment variable `REWRITE_PATH` (separated by `:`, on Windows by `;`),
the folder of the installation (`make install`), and the folder of the
program and `../share/rewrite` next to it. So rewrite works from any folder
when it is installed or started from the project folder's `rewrite.exe`.
`DATA` files are relative to the current folder.

## Building

You need `gcc`, `flex`, `bison`, `make` and the GMP library (for exact
numbers; it is linked statically).

**Linux:**

```text
sudo apt install gcc flex bison make libgmp-dev    # Debian/Ubuntu
make
make test
sudo make install            # /usr/local/bin/rewrite, /usr/local/share/rewrite
```

`make install PREFIX=$HOME/.local` installs for one user (`bin/` must be
in `PATH`); `make uninstall` removes it again, and `DESTDIR` stages the
files for a package. `make bindist` makes a tarball of the program with its
library (`rewrite-VERSION-linux-x86_64.tar.gz`) that runs wherever it is
unpacked: GMP is linked statically, the program needs only the C library.
`make dist` makes the source tarball of the last commit. `rewrite --version`
shows the version.

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

### Terminal with line editing, history and `\alpha` completion

rewrite reads plain lines. For line editing, a history across sessions
and TAB completion, start it through
[rlwrap](https://github.com/hanslub42/rlwrap) with the script
[tools/rewrite-rl](tools/rewrite-rl), from the project folder. TAB
completes the keywords and the names of the libraries (`TYP` TAB gives
`TYPEOF`, `RubiInt` TAB `RubiIntegrate`), and the LaTeX-like names as in
Julia: `\alpha` TAB gives `α`, `\al` TAB lists the names. As in Julia, the
arrow keys browse the earlier lines that begin with what is typed already,
and down after the newest one gives the typed text back (bound in
[tools/rewrite.inputrc](tools/rewrite.inputrc), done by the filter); pasted
text arrives as it is (bracketed paste off); the history is kept in
`~/.rewrite_history`, every line is saved at once. The session is
coloured: the prompt green, errors red, warnings yellow, keywords magenta,
sort names cyan and comments grey, also in the entered lines, which are
written again in colour after Enter (`NO_COLOR=1` switches it off). The
line being typed stays plain: readline cannot colour it. The word list
`tools/rewrite_words.txt` is written by [tools/gen_words.py](tools/gen_words.py)
(run it again after changing the libraries); the replacement of `\alpha`
is the rlwrap filter [tools/latex.rlwrap](tools/latex.rlwrap) (Perl, comes
with MSYS2 and most Linux systems), with the table `tools/latex_symbols.tsv`
of [tools/gen_latex.py](tools/gen_latex.py):

```text
tools/rewrite-rl                 # interactive
tools/rewrite-rl my.rw           # runs my.rw, then interactive
```

**Linux:** `sudo apt install rlwrap` (Debian/Ubuntu), then run the script in
any terminal.

**Windows:** rlwrap runs in the MSYS2 shell, not in PowerShell or `cmd`.

1. Open the shell: "MSYS2 UCRT64" in the Start menu, or
   `C:\msys64\ucrt64.exe`. In Windows Terminal, add a profile with the
   command line `C:\msys64\msys2_shell.cmd -defterm -here -no-start -ucrt64`.
2. Install rlwrap once: `pacman -S rlwrap`.
3. Go to the project folder (drive `C:` is `/c`) and start rewrite:

   ```text
   cd /c/path/to/rewrite
   tools/rewrite-rl
   ```

With `alias rewrite='tools/rewrite-rl'` in `~/.bashrc` (in the MSYS2 home
folder, `C:\msys64\home\<user>`), `rewrite` starts it this way. After
`make install` on Linux, `rewrite-rl` is in `PATH`. Without rlwrap, rewrite runs in any terminal (also PowerShell and
`cmd`); there `\alpha` is converted as well, only without completion.
Unicode characters need a font that has them, as in Windows Terminal.

A Desktop icon (a stylus drawing an integral, [tools/rewrite.ico](tools/rewrite.ico),
drawn by [tools/make_icon.py](tools/make_icon.py)) that starts rewrite this
way in the MSYS2 terminal is made once with

```text
powershell -ExecutionPolicy Bypass -File tools\make_shortcut.ps1
```

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
- A line that begins with `?` shows help, as in Julia: `?REWR`, `?Int`,
  `?sin`; `?` alone lists the names with a help text. The texts come from
  the library (`HELP "name" "text"`, in [inc/help](inc/help) and the
  library files); without one, `?f` shows the variants of a function and
  `?x` the kind and value of a name.
- A text in double quotes is printed: `"Hello world"`. A comma-separated
  list prints several items: `"value of x: ",x`.
- Writing a term prints it, evaluated as far as possible. The last printed
  term is always available as the term `%`.
- Errors are reported with the offending line, and the interpreter goes on
  with the next line.
- Names may contain Unicode letters (UTF-8): `SYM α, θ₁ : real`. As in
  Julia, LaTeX-like names are replaced on input: `\alpha` is `α`, `\theta`
  is `θ`, `\_1` is `₁`, `\hbar` is `ħ` (Julia's table of about 2500
  names, [src/latex.c](src/latex.c)). A name that ends in a letter must not
  be followed by a letter, so `\alphax` stays as it is. The output prints
  the characters.
- Unicode operators are tokens of their own, also without blanks: `a≤b` is
  `a ≤ b`, `3×4` is `3 × 4`. These are the signs `× ÷ · ± ¬`, the arrows
  and the mathematical operators, except the ones used as names (`∂ ∇ ∞`,
  sums and integrals). Their meaning comes from the library: `inc/alg`
  declares `ALIAS "×" = "*"`, so `×` is read as `*`, and likewise
  `≤ ≥ ≠ ⋅ · ÷ − ∧ ∨ ¬ √ π` (`√16` is `sqrt 16`). The output uses the
  ASCII names. `\le`, `\times`, `\sqrt` ... give the characters.

### Defining data types and operators

Without the library, the language knows no types and no operators at all.
This complete program defines them from scratch:

```text
SORT real                                   # a data type
REALNUM real                                # numbers like 1.5 have type real
FUNC + : real,real >> real LA2 ATT plus     # operators with priority and
FUNC * : real,real >> real LA3 ATT mult      # the C function that computes them
FUNC ^ : real,real >> real RA  ATT power
1+2*3                                       # prints 7
2^3^2                                       # prints 512
SYM x,y : real
x+y*2                                       # prints x + y * 2
x=4
x+y*2                                       # prints 4 + y * 2
```

| Command | Meaning |
| --- | --- |
| `SORT name [,name ..]` | Defines a data type ("sort"), needed for functions, variables and constants. |
| `REALNUM sortname` | Assigns the type for all numbers typed in (with inc/exact, `INTNUM` takes the whole numbers). Numbers are stored as `double`. Example: `SORT real` then `REALNUM real`. Before it, a number is an error. |
| `SYM name [,..] : sort` | Declares a symbol. It stands for itself and is printed by its name, or holds a numerical value of its sort (`x = 4`, `x = nothing` removes it), like a variable in the usual sense. |
| `TERM name [,..] : sort` | Declares a term variable, which stores a whole expression (e.g. a list). |
| `PAT name [,..] : sort` | Declares a pattern variable. It is a placeholder for any term in rewrite rules, for example `A+0=A`. |
| `NUMPAT name [,..] : sort` | Declares a pattern variable that only matches numbers. |
| `TYPEOF term`, `TYPEOF f` | Prints the sort of a term; for a name also its kind (`SYM`, `TERM`, `PAT`, `NUMPAT`) and its value or term; for a function all its variants with their argument and result sorts. |
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
`userfunction` in [userfn.c](src/userfn.c). It is called when all arguments
have numerical values. Otherwise the function stays symbolic.
`ATT SYMBOLIC name` connects it to a symbolic C function in
[symfn.c](src/symfn.c) instead, which gets the argument terms (see
[Symbolic helper functions](#symbolic-helper-functions));
`ATT SYMBOLIC HOLD name` passes them unevaluated.

A function can also be written in the rewrite language itself, with
`ATT ( argument definitions ) block`:

```text
FUNC fma3 : real,real,real >> real ATT (SYM aa,bb : real; TERM cc : real) { RETURN cc+aa*bb }
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
PAT X,Y,Z : real
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

Pattern variables (`PAT`) in a rule match any term. Pattern variables
declared with `NUMPAT` only match numbers. The pattern variables of the
library all begin with `_` (`_X`, `_Xnu`, `_N`, Rubi's `_P_a`), so names
such as `X`, `A`, `Pa` are free: declare your own pattern variables for
your rules, and a `TERM Y` of yours does not change a library rule. A rule
can have conditions:

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
PAT A : real
ALG simp
SPEC simp : A*1=A
ADDSPEC simp : A+0=A
SYM u : real
REWR (u*1)+0 : simp         # prints u
```

**Optional parts and commutative operators.** Three statements make one
rule cover many forms of a term. They act on the rules defined after them:

| Command | Meaning |
| --- | --- |
| `OPT A,B` | The pattern variables `A`, `B` may be missing in a pattern. |
| `DEFAULT + = 0` | A missing operand of `+` has the value 0. |
| `DEFAULT RIGHT ^ = 1` | Only the right operand of `^` may be missing, with value 1. |
| `COMM +,*` | Patterns with `+` and `*` also match with swapped operands. |
| `OPT`, `DEFAULT`, `COMM` | Without arguments: clear the list again. |

```text
PAT Xw : real
NUMPAT Ca,Cb,Cm : real
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
message `REWR : step limit (100000 rewrites, MAXSTEPS sets it) reached`.
Rules that loop therefore do not hang the interpreter. `MAXSTEPS n` sets
the limit, `MAXSTEPS` alone shows it.

**Depth limit.** A rule that makes the term deeper on every step, such as
`lin(c) = c*lin(1)` (it applies again to `lin(1)`), would overflow the
stack of the interpreter long before the step limit. `REWR` therefore also
stops when the term becomes deeper than 1000 levels. `MAXDEPTH n` sets this
limit, `MAXDEPTH` alone shows it. A sum of 1000 summands is 1000 levels
deep; a higher limit costs time when a rule runs away (quadratic in the
limit), and a very high one can crash the interpreter.

The trick behind `LIFT`: once the group rules for `+` and `-` are written,
the ring rules for `*` and `/` can be derived from them:

```text
LIFT (_Aag+_Aag,_Aag-_Aag,-_Aag,0ag) TO (_Ar+_Ar,_Ar-_Ar,-_Ar,0r)
LIFT (_Aag+_Aag,_Aag-_Aag,-_Aag,0ag) TO (_Ar*_Ar,_Ar/_Ar,mi(_Ar),1r)
```

### Exact numbers and subsorts

Each sort has its own representation in C. [inc/exact](inc/exact) adds two
number sorts implemented with the GMP library ([exact.c](src/exact.c)):
`integer` (any size) and `rational` (fractions). `inc/all` loads it (with
the integration); plain expressions are still calculated numerically:

```text
INC "inc/all"
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
| `SHOW f ATT name` | Prints the terms with the function `f` (all its variants) with the C print function `name` instead of the usual form; `SHOW f` alone switches back. [inc/list](inc/list) uses it for lists (`SHOW [ ATT show_list`). |
| `SUBSORT integer,rational ATT int2rat` | Every `integer` is also a `rational`; the C function converts a value. A sort may have several wider sorts. |
| `SUBSORT real,number` | Without `ATT`: the wider sort has no values of its own (`number`, `algebra`, `vector`, `matrix`); a value keeps its sort, and a `SYM` of such a sort holds no value. |
| `SUBSORT vector,rvector ATT constr_vec` | From a sort without values into one with values: a term, such as the list `[1,2,3]`, becomes a value where one is expected (assigned to a `SYM`, or the argument of a numerical C function); the C function gets the values of its arguments. |
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
tst(-2.5+im)         # prints -2.5: the complex one
```

**The sort `number`.** [inc/alg](inc/alg) also declares the sort `number`
for symbolic scalar expressions, above `real` and `complex` (`SUBSORT
real,number`, `SUBSORT complex,number`), like `Number` in Julia. The
arithmetic and the elementary and special functions have variants on
`number` without a C function; they only stand for the symbolic term.
A term becomes of sort `number` only when one of its parts is; a term of
reals keeps its real variants and is calculated as before. Rules written
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

Above `number` there is the sort `algebra`, the elements of an associative
algebra, whose product need not be commutative; the symbolic matrices of
[inc/linalg](inc/linalg) are of the sort `matrix` below it. Rules for
`algebra` hold for numbers as well, while the rules for `number` (with a
commutative product, like the integration) never see a matrix product.
A pattern matches the narrower variants of a function whenever its own
variant is symbolic (no numerical C function), so the order of the sorts
alone decides which rules apply.

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

**Functions of exact numbers.** With `inc/exact`, a function of exact
numbers that has no exact value stays a term, as in Mathematica: `ln(2)`,
`sin(1/3)`, `exp(1)`, `sqrt(2)`. `pi` stays a symbol in terms as well, and
`pi/6` is not calculated. Exact values are taken: rational ones (`cos(0)`
is 1, `cos(pi/3)` is 1/2), square roots of rational ones (`sin(pi/3)` is
`(1/2) * 3 ^ (1/2)`) and, for the inverse trigonometric functions, rational
multiples of `pi` (`arcsin(1/2)` is `(1/6) * pi`). They are found from the
numerical value; since a transcendental function of a nonzero algebraic
number is transcendental, a match is no accident. A real number makes the
term numeric (`sin(0.5)` is 0.479426), conditions are calculated
numerically, and a value printed on its own is still a number (`ln(2)`
prints 0.693147).

```text
REWR x + ln(2) + pi/6 : All                # prints pi / 6 + ln (2 )+ x
REWR x + arcsin(1/2) + sin(pi/3) : All     # prints (1/2) * 3 ^ (1/2) + (1/6) * pi + x
```

**Sorts with a known sign.** A sort can have several wider sorts.
`inc/exact` declares

```text
natural < integer < rational < real
natural < nonneg < real          positive < nonneg
```

Numbers written without a point are `natural`; `2-5` is the `integer` -3.
`nonneg` (values >= 0) and `positive` (> 0) are real numbers whose sign is
known. A pattern variable of such a sort only matches terms of that sort or
below it (a variable of sort `real` still matches any term). Rules that are
wrong for negative numbers are written for these sorts:

```text
SYM t : nonneg
SYM p : positive
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
FOR n = 1 TO 3 DO { SYM s : real
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
| `ALIAS "name" = "symbol"` | The name is read as the symbol from now on, e.g. `ALIAS "×" = "*"`; mainly for Unicode operators. |
| `SYMBOLIC "role" = "symbol"` | The symbolic C functions (helpers) use `symbol` where they need the function or constant `role` (`"cos"`, `"+"`, `"pi"`, ...), see [Symbolic helper functions](#symbolic-helper-functions). `SYMBOLIC` alone clears the mapping. |
| `MAXSTEPS n`, `MAXDEPTH n` | The step and the depth limit of `REWR` (default 100000 and 1000); without `n` they are shown, see [Rule sets](#rule-sets-algebras-and-rewriting). |
| `STEPS Alg "file"` | Shows each applied rule of the rule list of `Alg` (solution steps), labelled from `file` (lines `index<TAB>label<TAB>text`); `STEPS Alg ""` switches it off. |
| `QUIT` | Ends the program. |

## The standard library

`INC "inc/all"` loads the mathematical standard library, in this order.
The comments in the older files are in German.

| File | Contents |
| --- | --- |
| [inc/alg](inc/alg) | Basic sorts (`real`, `bool`, `complex`, `number`, `algebra`, group, ring, field), operators, elementary functions, simplification rules and differentiation `D`. Defines the rule list `All`. Besides `sin`, `ln`, `exp` and so on, it has `csc`, `sec`, `cot`, `arccot`, `sinh`, `cosh`, `tanh`, `coth`, `sech`, `csch`, `arcsinh`, `arccosh`, `arctanh`, `arccoth`, `polylog(n,x)` and `productlog` (Lambert W), and special functions (see below), each with a derivative rule. |
| [inc/pdiff](inc/pdiff) | Partial derivatives. |
| [inc/numerik](inc/numerik) | Numerics with the rule lists `numerik,calc`: integral `I(a,b,f,x)`, Newton zero `newton(start,f,f',x)`, `fmin`, `fmax`, `flzero`, `flext`. |
| [inc/mathnum](inc/mathnum) | The numerical values of `e` and `pi`, angle units `_deg`, `_rad`. |
| [inc/integration/all](inc/integration/all) | Exact numbers ([inc/exact](inc/exact): `integer` and `rational`, GMP), the symbolic helpers ([inc/helpers](inc/helpers): `deriv`, `normform`, `cancel`, `expand`, ...), and integration with `Integrate`. |
| [inc/integration/rubi/all](inc/integration/rubi/all) | The translated Rubi rules, `RubiIntegrate` (about 1 s to load). |
| [inc/limits](inc/limits) | `heaviside`, `dirac`, `infinity`, limits `limit(u,x,infinity)` and definite integrals `Int(f,x,a,b)`. |
| [inc/laplace](inc/laplace) | The Laplace transform `laplace(f,t,s)` and its inverse `invlaplace(F,s,t)`. |
| [inc/fourier](inc/fourier) | The Fourier transform `fourier(f,t,w)` and its inverse `invfourier(F,w,t)`. |
| [inc/list](inc/list) | Lists `[a,b,c]` (sort `vector`) and `nil`, matrices `[[a,b],[c,d]]` (sort `matrix`), their arithmetic, `part`, `length`, `table`, `select`, ... |
| [inc/linalg](inc/linalg) | Matrices: `transpose`, `dot`, `identity`, `det`, `linsolve`, `inverse`, `thread`, covectors, symbolic matrices with `MatrixRules` and `MatrixSolve`. |
| [inc/solve](inc/solve) | Equations: `solve(lhs == rhs, x)` with PRESS-style rules (isolation, polynomials, a new unknown, ...), systems. |
| [inc/simplify](inc/simplify) | `All` ends with the normal form (`normform`): like terms collected, also in subtracted sums, so `D` and `deriv` give tidy results. |
| [inc/help](inc/help) | The help texts for `?name`. |

Optional libraries, loaded after `inc/all`:

| File | Contents |
| --- | --- |
| [inc/rvector](inc/rvector) | Numerical real vectors (C arrays): scalar product, cross product `_x_`, `abs`, element access A list becomes an rvector where one is expected: `SYM v : rvector`, `v = [1,2,3]`, `[1,0,0]*v`. |
| [inc/rmatrix](inc/rmatrix) | Numerical real matrices: `onemat`, `zeromat`, `chmat`, `trans`, products. Indices start at 0 (after `inc/rvector`). |
| [inc/physics](inc/physics) | Physics: the names of quantities and units ([inc/physik](inc/physik)), the constants with their SI values ([inc/physnum](inc/physnum): `c`, `e0`, `hq`, `g`, ...), the Lagrange formalism ([inc/theophys](inc/theophys), [inc/lagrange](inc/lagrange)). It declares many short names (`c`, `g`, `m`, `t`, `v`, `F`, `T`, ...), most of them with values, so load it only when needed. |
| [inc/eqnsolve](inc/eqnsolve) | The old rule-based equation solver (`EQN`, `SLV`); see `inc/solve` for the new one. |

The examples of the original project use their own files: [LiNbO3/comp](LiNbO3/comp)
has the material constants of lithium niobate crystals.

Note that `inc/all` defines some short names: `e` and `pi` (with their
values), the imaginary unit `im` (the complex number `Cpx(0,1)`) and the
variables `x`, `y`, `z`. Other names, such as `a`, `b`, `n`, are declared
where they are used (`SYM a, b : real`).

**The imaginary unit `im`.** Like `pi`, `im` stays a symbol in terms (with
the exact numbers of `inc/all`), as `I` in Mathematica: `2*im*x` stays as
it is, and the symbolic helpers know `im^2 = -1`. A closed expression is
calculated with complex numbers: `2+3*im` prints `(2,3)`.
Some examples:

```text
(1+2*i)*(3-i)                     # prints (5,5)
dot([1,2,3],[4,5,6])              # prints 32 (inc/list, inc/linalg)
3!                                # prints 6
REWR newton(1,x^2-2,D(x^2-2,x),x) : numerik,calc    # prints 1.41421
REWR fmin(-1,1,(x-0.3)^2,x) : numerik,calc          # prints 0.3
```

### Rule-based integration

[inc/integration](inc/integration) adds indefinite integration with a
translation of a subset of the [Rubi](https://github.com/RuleBasedIntegration/Rubi)
rules (MIT license). It covers powers of linear expressions, exponentials,
sine and cosine, and polynomials times them, also with symbolic
coefficients. `INC "inc/all"` loads it, together with exact numbers
(inc/exact: `1/3` stays a fraction, while plain expressions such as
`sqrt(2)` are still calculated numerically):

```text
REWR Int(x^2*cos(x),x) : Integrate      # prints 2 * cos (x )* x + x ^ 2 * sin (x )- 2 * sin (x )
REWR Int(1/(2*x+3),x) : Integrate      # prints (1/2) * ln (3 + 2 * x )
REWR Int(sin(a*x+b),x) : Integrate     # prints - cos (a * x + b )/ a
```

With [inc/integration/rubi](inc/integration/rubi), also loaded by
`inc/all` (about 1 s), about 90% of all Rubi rules are available. They are
translated automatically by [tools/rubi2rewrite.py](tools/rubi2rewrite.py):

```text
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
[inc/physik](inc/physik) (inc/physics). Outside their real domain the
functions give NaN.

### Lists, vectors and matrices

[inc/list](inc/list) adds lists in brackets, like Mathematica's `List`
and Julia's arrays: `[a,b,c]`, the empty list `nil`, and lists of lists.
The bracket is declared in the library (`BRA [ ]`), and the sort of a list
follows from its elements: a list of numbers is a `vector`, a list of
vectors a `matrix` (a list of rows). `vector` is a subsort of `number`, so
a vector can stand wherever a number can; `matrix` is a subsort of
`algebra` (see above), so the rules for numbers with their commutative
product never see a matrix product. `list(a,b,c)` is the old name and
gives `[a,b,c]`.

The arithmetic of explicit lists is done at once, also without `REWR`:
element by element for vectors (`[1,2] + [a,b]`, `x*[1,2]`, `[1,2]^2`), for
the sum of matrices and for a number times a matrix; the product of two
matrices, of a matrix and a vector, and the integer powers of a matrix are
the matrix products:

```text
INC "inc/all"
[1,2]*x + [a,b]                     # [x + a, 2 * x + b]
[[1,2],[3,4]] * [[0,1],[1,0]]       # [ 2  1 ]
                                    # [ 4  3 ]
[[1,2],[3,4]] * [x,y]               # [x + 2 * y, 3 * x + 4 * y]
[[1,2],[3,4]]^2                     # [  7  10 ]
                                    # [ 15  22 ]
```

The list functions are symbolic C functions; they stay unevaluated if an
argument is no list:

| Function | Meaning |
| --- | --- |
| `[a,b,..]`, `nil`, `list(a,b,..)` | a list, the empty list, the old name of `[a,b,..]` |
| `listq(u)`, `length(l)` | `u` is a list; the number of elements |
| `part(l,i)`, `part(l,i,j)` | element `i` (from 1, `-1` is the last), element `j` of element `i` |
| `first(l)`, `last(l)`, `rest(l)`, `most(l)` | first, last element; without the first, without the last |
| `append(l,x)`, `prepend(l,x)`, `join(l1,l2,..)`, `reverse(l)` | |
| `range(n)`, `range(a,b)`, `range(a,b,d)` | `1..n`, `a..b` in steps of 1 or `d` |
| `table(body,x,l)`, `table(body,x,n)` | `body` for each `x` in `l` (or `1..n`), Mathematica's `Table` |
| `select(l,x,cond)` | the elements `x` of `l` for which `cond` is true |
| `total(l)` | the sum of the elements |

Lists are printed by their shape, as Julia prints arrays. When it is the
whole printed term, a vector of up to 10 entries is a column in the form
of the input (`[1,`, then `2,` and `3]` indented on the next lines), a rectangular list of
lists a grid with aligned columns (numbers right-aligned), deeper ones in
slices `[1, :, :] = ...`; everything else is inline, `[a, b, [c, d]]`
(in the examples below, results are written inline). This is a print
function attached with `SHOW [ ATT show_list`; `SHOW [` prints the plain
term again.

`table` and `select` get their body and condition unevaluated (`HOLD`) and
replace `x` first. `x` must be declared (`SYM kk : real`): an undeclared
name is a numerical variable with the value 0.

```text
SYM aa,kk : real
REWR table(aa^kk, kk, range(3)) : All           # [aa, aa ^ 2, aa ^ 3]
REWR select(range(10), kk, kk > 6) : All        # [7, 8, 9, 10]
part([[1,2],[3,4]], 2, 1)                       # 3
[1,[2,3]]                                       # [1, [2, 3]]
```

### Matrix functions and symbolic matrices

[inc/linalg](inc/linalg) (loaded by `inc/all`) has the functions of
linear algebra. The entries may be any terms. The functions are symbolic
C functions ([symmat.c](src/symmat.c)):

| Function | Meaning |
| --- | --- |
| `transpose(m)`, `identity(n)` | rows as columns (of a vector: a covector, see below); the n x n unit matrix |
| `dot(a,b)` | matrix product, matrix times vector, scalar product (like terms collected, sums not multiplied out) |
| `det(m)` | determinant |
| `linsolve(m,b)` | the solution `x` of `m.x = b`, `b` a vector or a matrix (several right-hand sides); unevaluated if `m` is singular |
| `inverse(m)` | the inverse matrix, also `m^(-1)` |
| `thread(u)` | functions of lists element by element: `sin([a,b])` is `[sin(a), sin(b)]` |

`det`, `linsolve` and `inverse` use Bareiss' fraction-free elimination:
the entries become sparse polynomials in their atoms (every factor that is
no number and no natural power, such as `sin(x)`, `a^-1` or `2^(1/2)`), and
every division during the elimination is an exact division of polynomials,
so no nested fractions arise. A solution is a polynomial divided by the
determinant; common factors are cancelled with the polynomial gcd
(`1/(a+2)`). The matrix functions thread their
arguments first, so `det(m - x*identity(2))` is the characteristic
polynomial of `m`; the rule set `Listable` does this for any term, like
Mathematica's `Listable` functions:

```text
SYM g : real
det([[a,b],[g,n]])                                # a * n - b * g
linsolve([[a,1,1],[1,a,1],[1,1,a]],[1,1,1])       # [1 / (a + 2 ), 1 / (a + 2 ), 1 / (a + 2 )]
det([[2,1],[1,2]] - x*identity(2))                # x ^ 2 + 3 - 4 * x
REWR sin([x,2*x]) : Listable                      # [sin (x ), sin (2 * x )]
```

**Covectors.** `transpose(v)` of a vector is a covector, a row vector of
the sort `covector`, like Julia's `Transpose`: it stays a term, and the
sorts choose the product. `transpose(u)*v` is a number (the inner
product), `u*transpose(v)` a matrix (the outer product), `transpose(u)*m`
a covector. Explicit lists are calculated; for symbolic vectors
(`SYM u,v : vector`) the sort alone says that `transpose(u)*v` is a
scalar that commutes with matrices. Sums and multiples of covectors are
taken back to vectors, as `transpose` is linear. A covector that is the
whole printed term is a row `[1 2 3]` (up to 10 entries).

```text
transpose([1,2,3]) * [4,5,6]             # 32
[1,2] * transpose([3,4])                 # [ 3  4 ]
                                         # [ 6  8 ]
transpose([1,2]) * [[1,2],[3,4]]         # [7 10]
SYM uu,vv : vector
SYM MM : matrix
REWR transpose(MM*uu) : MatrixRules      # transpose (uu )* transpose (MM )
REWR MM*(transpose(uu)*vv) : MatrixRules # transpose (uu )* vv * MM
```

**Symbolic matrices.** `SYM A,B : matrix` declares symbolic matrices,
whose product does not commute; they mix with explicit ones. The rule set
`MatrixRules` knows the laws of the algebra and of matrices, and
`MatrixSolve` isolates an unknown matrix from the left or from the right:

```text
SYM A,B,C,X : matrix
REWR transpose(A*B) : MatrixRules                      # transpose (B )* transpose (A )
REWR inverse(A*B*C) : MatrixRules                      # inverse (C )* inverse (B )* inverse (A )
REWR A*(B+C) - A*B : MatrixRules                       # A * C
REWR A*B - B*A : MatrixRules                           # stays: no commutation
REWR msolve(X*A + C == B, X) : (MatrixSolve, MatrixRules)   # (B - C )* inverse (A )
REWR det(A*[[a,b],[n,y]]) : MatrixRules                # det (A )* (a * y - b * n )
REWR 2*A*[x,y] : MatrixRules                           # stays: a vector is no scalar
```

(In a library loaded after inc/alg, `A`, `B`, `C` are variables already;
the tests use `MA`, `MB`, ...)

### Limits and definite integrals

[inc/limits](inc/limits) adds the symbol `infinity` (also `∞`), the unit
step `heaviside(x)` and the delta `dirac(x)`, limits at infinity and
definite integrals:

```text
SYM t, w : real
SYM a : positive                              # a > 0 is known
limit(t^3*exp(-a*t), t, infinity)             # prints 0
limit(erf(a*t), t, -infinity)                 # prints -1
Int(exp(-a*t^2), t, -infinity, infinity)      # prints pi ^ (1/2) / a ^ (1/2)
Int(exp(-a*t)*cos(w*t), t, 0, infinity)       # prints a / (w ^ 2 + a ^ 2 )
Int(heaviside(t-1)*exp(-a*t), t, -infinity, infinity)   # prints exp (- a )/ a
Int(dirac(t-3)*t^2, t, -infinity, infinity)   # prints 9
```

- `limit(u, x, infinity)` and `limit(u, x, -infinity)` evaluate a limit
  only if it is finite and known: constants, sums of such parts, a
  decaying exponential times anything that grows at most like a power
  (also oscillating: `t^2*sin(w*t)*exp(-a*t)`), quotients of polynomials,
  and `erf`, `arctan`, `tanh`, `heaviside` of a polynomial. Otherwise the
  limit stays as it is, so `infinity - infinity` can never become 0.
- The sign of a coefficient decides: `knownpos(u)` and `knownneg(u)` are
  true for positive and negative numbers, symbols of the sort `positive`,
  and products, quotients, sums and powers of them. A parameter that has
  to be positive is declared with `SYM a : positive`. The symbols are real,
  `im` is the imaginary unit.
- `Int(f, x, a, b)` takes the antiderivative of `RubiIntegrate` at the
  bounds. That is only correct if the antiderivative is continuous, so
  the integrand must be continuous on the real line: polynomials, `exp`,
  `sin`, `cos`, `sinh`, `cosh`, `erf` and their sums, products and
  quotients by constants. `Int(1/t^2, t, -1, 1)` therefore stays as it is
  (the antiderivative `-1/t` would give the wrong -2). A step
  `heaviside(c*x+d)` with `c > 0` changes the lower bound, and a delta
  `dirac(c*x+d)` picks the value of the rest of the integrand.
- If a step fails (no antiderivative, an unknown limit), the integral stays
  as it is.

### The Laplace transform

[inc/laplace](inc/laplace) has `laplace(f, t, s)` and `invlaplace(F, s, t)`:

```text
SYM t, w : real
SYM s, a : positive
laplace(exp(-a*t)*sin(w*t), t, s)        # prints w / ((s + a )^ 2 + w ^ 2 )
laplace(heaviside(t-2), t, s)            # prints exp (- 2 * s )/ s
invlaplace(1/(s^2+3*s+2), s, t)          # prints exp (- t )- exp (- 2 * t )
invlaplace(s/(s^2+2*s+5), s, t)          # prints cos (2 * t )* exp (- t )- (1/2) * exp (- t )* sin (2 * t )
invlaplace(exp(-s)/(s+1), s, t)          # prints exp (1 - t )* heaviside (t - 1 )
```

- `laplace` uses linearity, a table (constants, powers of `t`, `exp`,
  `sin`, `cos`, `sinh`, `cosh`, `heaviside`, `dirac`), the theorems (shift
  by `exp(a*t)`, multiplication by `t` as `-D(F,s)`, delay by
  `heaviside(t-c)`, derivatives) and finally the definite integral of
  [inc/limits](inc/limits), which needs `s` declared positive. Results
  are not always in the simplest form; `cancel(...)` brings a rational
  function over a common denominator.
- `invlaplace` uses linearity, the table backwards (also `1/s^(1/2)`), the
  delay `exp(-c*s)`, a linear numerator over a quadratic without real roots
  (damped oscillations), `(s^2+c)^-2` (resonance) and partial fractions of
  rational functions with exact coefficients.
- A part that is not known stays as `laplace(...)` or `invlaplace(...)`.

**Differential equations.** `laplace(D(u(t),t),t,s)` is
`s*laplace(u(t),t,s) - initial(u(t),t)`, and `initial(u(t),t)` is `u(0)`;
for a derivative, `initial(D(u(t),t),t)` stays, so the initial values are
given by rules. Then the transformed equation is solved for the transform
`U`, and `invlaplace` gives the solution:

```text
FUNC u : real >> real                         # the unknown function
SYM U : real                                  # its transform
ALG Init
SPEC    Init : u(0) = 1
ADDSPEC Init : initial(D(u(t),t),t) = 0       # u'(0) = 0
ADDSPEC Init : laplace(u(t),t,s) = U
TERM E : real
TERM R : vector
E = REWR laplace(D(D(u(t),t),t) + u(t), t, s) : Init, All   # U * s ^ 2 + U - s
R = REWR solve(E == 0, U) : Solve                           # [s / (s ^ 2 + 1 )]
invlaplace(part(R,1), s, t)                                 # cos (t )
```

### The Fourier transform

[inc/fourier](inc/fourier) has `fourier(f, t, w)` and `invfourier(F, w, t)`
with the convention of physics and engineering (and of FFTW):

```text
F(w) = Int(f(t)*exp(-im*w*t), t, -infinity, infinity)
f(t) = 1/(2 pi) Int(F(w)*exp(im*w*t), w, -infinity, infinity)
```

```text
SYM t, w, b : real
SYM a : positive
fourier(cos(b*t), t, w)                  # prints pi * dirac (w - b )+ pi * dirac (b + w )
fourier(exp(-a*abs(t)), t, w)            # prints 2 * a / (a ^ 2 + w ^ 2 )
fourier(sin(a*t)/t, t, w)                # prints pi * heaviside (a + w )- pi * heaviside (w - a )
fourier(exp(-a*t^2), t, w)               # prints pi ^ (1/2) * exp (- (1/4) * w ^ 2 / a )/ a ^ (1/2)
REWR invfourier(2*a/(a^2+w^2), w, t) : All     # prints exp (- a * abs (t ))
```

- `fourier` combines a table with the integral: linearity first, then the
  table (constants and `dirac`,
  `exp(im*a*t)`, `cos`, `sin`, `heaviside`, `sgn`, `exp(-a*abs(t))`,
  `1/(t^2+c)`, `1/(c+im*b*t)`, `sin(a*t)/t`, Gaussians
  `exp(-c*t^2+b*t+d)` with `c > 0`), whose entries are
  distributions or need contour integrals; then the theorems (modulation by
  `exp(im*a*t)`, `cos`, `sin`; multiplication by `t` as `im*D(F,w)`;
  derivatives as `im*w*F`); and for the rest the definite integral of
  [inc/limits](inc/limits), which does one-sided exponentials and
  rectangles.
- `invfourier(F, w, t)` is `fourier(F, w, -t)/(2*pi)` (duality), so the
  same table and the same integrals work backwards.
- A part that is not known stays as `fourier(...)`.
- With `fourier(D(u(x,t),x), x, w) = im*w*U`, a linear partial differential
  equation in `x` becomes an ordinary one in `t`: the heat and the transport
  equation in [examples/14_pde.rw](examples/14_pde.rw).

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
| polynomials | degree 1 and 2, `x^n = c`, polynomials in `x^2`, rational roots, the cubic (Cardano) and quartic (Ferrari) formulas; after a common denominator | `x^3 - 6x^2 + 11x - 6 = 0`, `1/x + 1/(x+1) = 1`, `x^3 + x + 1 = 0` |
| attraction | several logarithms with `x`: `ln(u) + ln(v) = ln(u v)` | `ln(x) + ln(x+1) = ln(6)` |
| new unknown | `f` is a polynomial in `g(x)` (`exp(c x)`, `x^(1/n)`, `sin(x)`, ...) | `exp(2x) - 3 exp(x) + 2 = 0`, `x + sqrt(x) - 6 = 0` |
| radicals | `a + b c^(1/2) = 0` is squared to `a^2 - b^2 c = 0` | `sqrt(x+1) = x - 1` |

Complex roots use the imaginary unit `im`; trigonometric equations give
the principal solutions, as Mathematica's `Solve` without the integer
constant. Every solution is checked (numerically where possible), so the
extra solutions of squaring and those that make the equation undefined are
removed. A system of linear equations, `solve([eq1, eq2], [x, y])`,
gives the list of the values of the unknowns, solved with Bareiss'
elimination of [inc/linalg](inc/linalg). A nonlinear system gives the list
of the solution tuples: an unknown that occurs linearly is eliminated by
substitution, and two polynomial equations by their resultant
(`resultant(f, g, y)`, the determinant of the Sylvester matrix); every
tuple is checked in all equations. `solve([x^2 + y^2 == 5, x - y == 1],
[x, y])` gives the tuples `[2, 1]` and `[-1, -2]`, printed as the rows of
a matrix.
The analysis is done by C helpers ([symsolve.c](src/symsolve.c)), the
methods themselves are an ordered rule list.

```text
INC "inc/all"
REWR solve(x^2 + 4*x + 7 == 0, x) : Solve               # [3 ^ (1/2) * im - 2, -2 - 3 ^ (1/2) * im]
REWR solve(exp(2*x) - 3*exp(x) + 2 == 0, x) : Solve     # [0.693147, 0]
REWR solve(sqrt(x+1) == x - 1, x) : Solve               # [3]
REWR solve([x + y == 3, x - y == 1], [x, y]) : Solve   # [2, 1]
```

With exact numbers, the results are exact: `exp(2*x+1) = 5` gives
`[(1/2) * ln (5 )- (1/2)]`, `sin(x) = 1/2` gives `[(1/6) * pi, (5/6) * pi]`.

### Symbolic helper functions

[inc/helpers](inc/helpers) declares helper functions written in C
([symfn.c](src/symfn.c)) with `ATT SYMBOLIC`. Unlike numerical functions,
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
FUNC kos : real >> real ATT r_cos
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
| `cancel(u)` | `u` over a common denominator, `N/D`, with the greatest common divisor of `N` and `D` cancelled: `(x^2-y^2)/(x-y)` gives `x+y` (Mathematica's `Cancel` and `Together`) |
| `polygcd(a,b)` | greatest common divisor of two polynomials in several variables (primitive remainder sequence; exact coefficients) |
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
PAT A,X : real
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
`userfunction` in [userfn.c](src/userfn.c). A function gets an array of
pointers to its arguments and returns a pointer to a newly allocated result:

```c
double * r_abs (double * arg[]) { return mkreal(fabs(* arg[0])); }
```

Examples are in [real.c](src/real.c), [complex.c](src/complex.c),
[vector.c](src/vector.c) and [matrix.c](src/matrix.c). The function is then
connected with `ATT` in a `FUNC` or `OTHER` declaration.

Symbolic functions, which work on terms instead of numbers, are entered in
the list `symfunction` in [symfn.c](src/symfn.c). They get the argument terms
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
| [symfn.c](src/symfn.c) | Symbolic helper functions (`expand`, `coeff`, `polyq`, ...). |
| [numsort.c](src/numsort.c), [exact.c](src/exact.c) | Subsorts (`SUBSORT`, `INTNUM`) and the exact number sorts with GMP. |
| [specfun.c](src/specfun.c) | Special functions (erf, Fresnel, Ei, Gamma, zeta, elliptic integrals, 2F1, ...). |
| [apart.c](src/apart.c) | Partial fractions of rational functions with exact coefficients (GMP). |
| [symsolve.c](src/symsolve.c) | Helpers of the equation solver: polynomial roots, the new unknown, square roots, checking (included by symfn.c). |
| [symmat.c](src/symmat.c) | Symbolic matrices on lists: Bareiss elimination on sparse polynomials (included by symfn.c). |
| [tools/rubi2rewrite.py](tools/rubi2rewrite.py) | Translator of Rubi's integration rules. |
| [tools/rubitest.py](tools/rubitest.py) | Runs Rubi's test suite and checks the results numerically. |
| [nodes.h](src/nodes.h) | Named access to the node structures built by the parser. |
| [sym.c](src/sym.c), [node.c](src/node.c), [stack.c](src/stack.c) | Symbol table and memory for nodes and symbols. |
| [userfn.c](src/userfn.c), [real.c](src/real.c), [bool.c](src/bool.c), [complex.c](src/complex.c), [vector.c](src/vector.c), [matrix.c](src/matrix.c) | Built-in numerical functions. |
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

- `inc/all` declares only `x`, `y`, `z` as variables; `a`, `b`, `c`, `n`,
  ... are declared where they are used. The internal names of the old
  libraries were moved to the files that use them. The imaginary unit is
  `im` (formerly `i`, and a second symbolic `im` of the integration): a
  complex constant that stays a symbol in terms, like `pi`.
- Limits at infinity, definite integrals, `heaviside` and `dirac`
  ([inc/limits](inc/limits)); the Laplace transform and its inverse, also
  for differential equations ([inc/laplace](inc/laplace)); the Fourier
  transform and its inverse ([inc/fourier](inc/fourier)).
- Differential equations: examples for ordinary
  ([examples/13_ode.rw](examples/13_ode.rw)) and partial ones
  ([examples/14_pde.rw](examples/14_pde.rw)). For them: `All` combines
  `exp(a)*exp(b)` to `exp(a+b)` and simplifies `exp(ln(x))`,
  `exp(-ln(x))`, `exp(n*ln(x))`; `fourier` knows the Gaussians
  `exp(-c*t^2+b*t+d)` from its table (fast, and with `im` cancelled).
- All pattern variables of the library begin with `_` (`X`, `N`, `Xnu`,
  `Ag`, Rubi's `P_a`, ... are now `_X`, `_N`, `_Xnu`, `_Ag`, `_P_a`; `M`
  is `_K`, since `_M` is the unit prefix of inc/physik). A `TERM Y` of the
  user used to change the rules with `Y` (for example `Sub`); now these
  names are free, and rules of your own declare their own pattern
  variables (`PAT X : real`).
- `REWR` calculates the term before the first rule set, as it does after
  each rule set (a function defined by rules is computed before the rules
  of the user apply). After the arguments of a function defined by rules
  are calculated, its variant is chosen again for their sorts, also in the
  conditions of rules.
- In exact mode, the real numbers of rules loaded before inc/exact (the 1
  of `mi _X = 1/_X`) become exact next to exact expressions such as `2*pi`,
  so `t*mi(2*pi)` stays `t/(2*pi)` instead of `t*0.159155`. A
  calculation of such integers alone that has no integer value (the
  `mi(2)` of `D(sqrt(_X),_Z) = D(_X,_Z)*mi(2*sqrt(_X))`) is done exactly, so
  `D(sqrt(pi*t),t)` is `(1/2)*pi/sqrt(pi*t)`, not `1.5708/sqrt(pi*t)`.
- Fixed: a number of a sort that is not below `real` (complex, bool) was
  shared instead of copied by the symbolic helpers, so freeing a copy freed
  the original as well (wrong results that changed from run to run); and
  the cache of the rule lists could free an entry that was still in use
  when more than eight rule lists were nested; a calculation with an
  argument that has no value could check a stale symbol (`Not a Symbol to
  delete`).
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
- Symbolic helper functions in C ([symfn.c](src/symfn.c), [inc/helpers](inc/helpers))
  and further elementary functions (`csc`, `sec`, `cot`, `arccot`, the
  hyperbolic and inverse hyperbolic functions, `polylog`, `productlog`).
- Special functions ([specfun.c](src/specfun.c)) with derivative rules, and
  more of Rubi's helper functions in [symfn.c](src/symfn.c), among them
  partial fractions ([apart.c](src/apart.c)).
- Exact numbers: sorts `integer` and `rational` with GMP ([inc/exact](inc/exact)),
  the statements `SUBSORT` and `INTNUM`, and the choice of operator
  variants by the sorts of their arguments.
- Rule lists with a backtracking matcher for rules with `OPT`, `DEFAULT`
  and `COMM`, instead of expanding each rule into its variants. Rules that
  make no progress or give NaN are skipped, and `REWR` has a step limit.
- [tools/rubi2rewrite.py](tools/rubi2rewrite.py) translates 97% of
  Rubi's rules automatically ([inc/integration/rubi](inc/integration/rubi),
  `RubiIntegrate`); [tools/rubitest.py](tools/rubitest.py) measures them
  with Rubi's test suite.
- The sorts `algebra` (non-commutative product) above `number` and
  `matrix` below it: symbolic matrices with `MatrixRules` and matrix
  equations (`msolve`).
- Exact results: functions of exact numbers stay terms (`ln(2)`, `pi/6`) unless
  their value is exact (`cos(pi/3) = 1/2`, `arcsin(1/2) = pi/6`); a gcd of
  polynomials in several variables (`polygcd`, `cancel`).
- Equations ([inc/solve](inc/solve)): `solve(lhs == rhs, x)` with rules in
  the style of PRESS, linear systems.
- Matrices ([inc/linalg](inc/linalg)): `det`, `linsolve`, `inverse`,
  `dot`, `transpose` with fraction-free elimination.
- Lists in brackets ([inc/list](inc/list)): `[a,b,c]` is a `vector`,
  `[[a,b],[c,d]]` a `matrix`, with their arithmetic (element by element,
  matrix products) and `part`, `table`, `select`, ... The numerical
  vectors of inc/rvector are no longer loaded by inc/all.
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
