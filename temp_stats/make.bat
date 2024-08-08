@echo off
REM Set the compiler and flags
set CC=gcc
set CFLAGS=-Wall -g
REM Build the object files
echo Compiling main.c...
%CC% %CFLAGS% -c main.c
echo Compiling temp_functions.c...
%CC% %CFLAGS% -c temp_functions.c
REM Link the object files
echo Linking...
%CC% %CFLAGS% main.o temp_functions.o -o temp_stats
echo Done!