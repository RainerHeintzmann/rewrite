@echo off
rem Runs the rewrite test suite with the MSYS2 shell (see tests/README.md).
rem Usage:  tests\run_tests.bat [--verbose] [--update] [name ...]
set MSYSTEM=UCRT64
set CHERE_INVOKING=1
pushd "%~dp0.."
C:\msys64\usr\bin\bash.exe -lc "tests/run_tests.sh %*"
set RESULT=%ERRORLEVEL%
popd
exit /b %RESULT%
