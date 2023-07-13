#!/bin/bash -e

gcc -g -Wall  main.c -o main.o -c
gcc -g -Wall  rotation.c -o rotation.o -c
gcc -g -Wall  insertion.c -o insertion.o -c
gcc -g -Wall validate.c -o validate.o -c
gcc -g -o a.out main.o rotation.o insertion.o validate.o
rm -f *.o vgcore.* log.core.*
