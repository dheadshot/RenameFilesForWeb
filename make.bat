REM Replace gcc with tcc if using Tiny C Compiler instead of MinGW
gcc -c rffw.c
gcc rffw.o -lkernel32 -o rffw.exe