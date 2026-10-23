#!/bin/sh
# Regression tests for rewrite.
#
# Each file tests/cases/NAME.rw is fed to rewrite on standard input.
# Its output (stdout and stderr) is compared with tests/expected/NAME.txt.
#
# Usage (from any directory):
#   tests/run_tests.sh               run all tests
#   tests/run_tests.sh 05 ex_abso1   run only tests whose name starts with these
#   tests/run_tests.sh --update ...  (re)write the expected output instead
#   tests/run_tests.sh --verbose ... show the diff for failing tests
#   REWRITE=path/to/rewrite tests/run_tests.sh   test another executable

cd "$(dirname "$0")/.." || exit 2   # INC paths are relative to the project root

EXE=${REWRITE:-./rewrite.exe}       # executable can be chosen with REWRITE=...
[ -f "$EXE" ] || [ -n "$REWRITE" ] || EXE=./rewrite
if [ ! -f "$EXE" ]; then
    echo "rewrite executable not found. Build it first with 'make'." >&2
    exit 2
fi

update=0
verbose=0
while [ $# -gt 0 ]; do
    case "$1" in
        --update)  update=1 ;;
        --verbose|-v) verbose=1 ;;
        *) break ;;
    esac
    shift
done

if ! command -v diff >/dev/null 2>&1; then
    echo "'diff' not found. In MSYS2 install it with: pacman -S diffutils" >&2
    exit 2
fi

if command -v timeout >/dev/null 2>&1; then
    TIMEOUT="timeout 120"
else
    TIMEOUT=""
fi

work=$(mktemp -d 2>/dev/null || echo "${TMPDIR:-/tmp}/rewrite_tests.$$")
mkdir -p "$work"
trap 'rm -rf "$work"' EXIT

pass=0
fail=0
failed=""

for case in tests/cases/*.rw; do
    name=$(basename "$case" .rw)

    if [ $# -gt 0 ]; then          # filter by name prefix
        wanted=0
        for p in "$@"; do
            case "$name" in "$p"*) wanted=1 ;; esac
        done
        [ $wanted -eq 1 ] || continue
    fi

    expected="tests/expected/$name.txt"
    actual="$work/$name.txt"

    $TIMEOUT "$EXE" < "$case" > "$actual.raw" 2>&1
    status=$?
    tr -d '\r' < "$actual.raw" > "$actual"   # Windows writes CRLF line ends
    if [ $status -ne 0 ]; then
        echo "exit status $status" >> "$actual"
    fi

    if [ $update -eq 1 ]; then
        cp "$actual" "$expected"
        echo "updated  $name"
        continue
    fi

    if [ ! -f "$expected" ]; then
        echo "MISSING  $name   (no $expected, run with --update)"
        fail=$((fail + 1)); failed="$failed $name"
        continue
    fi

    # ignore CR in the reference too (git may check it out with CRLF)
    tr -d '\r' < "$expected" > "$work/$name.expected"
    if diff "$work/$name.expected" "$actual" > "$work/$name.diff"; then
        echo "ok       $name"
        pass=$((pass + 1))
    else
        echo "FAILED   $name"
        [ $verbose -eq 1 ] && sed 's/^/         /' "$work/$name.diff"
        fail=$((fail + 1)); failed="$failed $name"
    fi
done

[ $update -eq 1 ] && exit 0

echo
echo "$pass passed, $fail failed"
if [ $fail -gt 0 ]; then
    echo "failed:$failed"
    echo "rerun with --verbose to see the differences"
    exit 1
fi
exit 0
