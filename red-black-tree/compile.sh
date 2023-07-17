#!/bin/bash -e

gcc -g -Wall  main.c -o main.o -c
gcc -g -Wall  rotation.c -o rotation.o -c
gcc -g -Wall  insertion.c -o insertion.o -c
gcc -g -Wall  deletion.c -o deletion.o -c
gcc -g -Wall validate.c -o validate.o -c
gcc -g -Wall utilities.c -o utilities.o -c
gcc -g -o a.out main.o rotation.o insertion.o validate.o deletion.o utilities.o

rm -f *.o vgcore.* log.core.*
