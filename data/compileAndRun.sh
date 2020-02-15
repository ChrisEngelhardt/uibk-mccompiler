#!/bin/bash

#Remove old stuff
rm *.o
rm test

# Compile buildins
gcc -m32 -c stdmclib.c -o buildins.o
# Compile assembly file
gcc -m32 -c a.s -o a.o
# Link
gcc -m32 buildins.o a.o -o test

# Execute
./test