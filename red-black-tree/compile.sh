#!/bin/bash -e

gcc -Wall  main.c -o main.o -c
gcc -Wall  rotation.c -o rotation.o -c
gcc -Wall  insertion.c -o insertion.o -c
gcc -o a.out main.o rotation.o insertion.o
