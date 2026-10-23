@echo off
rem Builds rewrite.exe with MSYS2 (gcc, flex, bison, make).
rem Install once:  winget install MSYS2.MSYS2
rem then in the MSYS2 shell:  pacman -S mingw-w64-ucrt-x86_64-gcc flex bison make
rem Usage:  build_windows.bat          (build)
rem         build_windows.bat clean    (remove generated files)
set MSYSTEM=UCRT64
set CHERE_INVOKING=1
pushd "%~dp0"
C:\msys64\usr\bin\bash.exe -lc "make %*"
popd
