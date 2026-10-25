# Tests for rewrite

Each file in [cases](cases) is a small rewrite program. The test runner
feeds it to `rewrite` on standard input and compares everything the
program prints, including error messages, with the reference output in
[expected](expected). A test passes when the two are identical.

## Running the tests

Build `rewrite` first, then run the tests from the project folder:

```text
make test                          # build if needed, then run all tests
tests/run_tests.sh                 # run all tests
tests/run_tests.sh 05 ex_abso1     # run tests whose names start with these
tests/run_tests.sh --verbose       # show the differences for failing tests
REWRITE=./other.exe tests/run_tests.sh   # test another executable
```

On Windows, the same works in the "MSYS2 UCRT64" shell. From `cmd` or
PowerShell, use `tests\run_tests.bat` or `build_windows.bat test`. The
runner needs `diff`, which MSYS2 installs with `pacman -S diffutils`.

The runner exits with status 0 when all tests pass and 1 otherwise, so it
can be used in scripts and CI.

## The tests

| Test | What it checks |
| --- | --- |
| `01_core_language` | Sorts, number type, operators with priorities, constants, terms, rewrite rules and strings, without the library. |
| `02_arithmetic` | Numerical evaluation with `inc/all`, number format, booleans. |
| `03_differentiation` | Symbolic derivatives with the rule list `All`. |
| `04_simplification` | Algebraic simplification. |
| `05_numerics` | Integral, Newton zero, minimum and maximum from `inc/numerik`. |
| `06_terms` | Term variables, the last result `%`, terms used as functions. |
| `07_control_flow` | `IF`/`ELSE`, `WHILE`, `FOR`, blocks, declarations inside loops. |
| `08_user_functions` | Functions written in rewrite itself with `ATT (...) { RETURN ... }`. |
| `09_complex_vector_matrix` | Complex numbers, vectors and matrices. |
| `10_data_input` | Reading numbers with `DATA` from [data/numbers.txt](data/numbers.txt). |
| `11_include` | `INC` at top level, inside a block and inside a loop. |
| `12_errors` | Error messages and recovery after errors. |
| `13_regressions` | Crashes fixed in 2026. |
| `14_rule_conditions` | Rules with conditions (`IF (...)`, `NIN`) and `NUM` meta variables. |
| `15_memory_paths` | The code paths that free memory, so that a tree freed too early shows up. |
| `16_integration` | Rule-based integration from [inc/integration](../inc/integration), each result checked by differentiation. |
| `17_pattern_features` | Optional pattern parts (`OPT`, `DEFAULT`), commutative operators (`COMM`) and condition lists. |
| `18_helpers` | Symbolic helper functions (`inc/helpers`) and the elementary functions added in 2026, with numerical derivative checks. |
| `19_rubi` | Integration with the automatically translated Rubi rules (`RubiIntegrate`), each result checked by differentiation. |
| `20_exact` | Exact numbers from `inc/exact`: integers and fractions, widening to real, LIFTed rules, exact roots and numeric contagion. |
| `21_specfun` | Special functions (erf, Fresnel, sine and cosine integrals, Ei, Gamma, zeta, elliptic integrals, 2F1, ...): values and derivative rules. |
| `22_steps` | Solution steps of the Rubi rules (`STEPS RubiRules "inc/integration/rubi/steps"`), and switching them off. |
| `ex_*` | The example programs of the original project, for example `LiNbO3/abso1`. |

Files used by the tests are in [data](data). All paths in the tests are
relative to the project folder, because the runner starts `rewrite` there.

## Adding a test

1. Write a program `tests/cases/NN_name.rw`. Start it with a comment that
   says what it checks. Most tests begin with `INC "inc/all"`.
2. Create the reference output:

   ```text
   tests/run_tests.sh --update NN_name
   ```

3. Read `tests/expected/NN_name.txt` carefully and check that every result
   is really correct. The reference is only as good as this check.
4. Commit both files.

When a change in rewrite is meant to change an output, run the tests with
`--verbose`, check the differences, and then update the references with
`--update`.

Do not use `OUT` or `SYS` in tests, because they write files or depend on
the operating system. For the same reason, `LiNbO3/absorb` is not part of
the tests: it overwrites the file `absorbtion`.
