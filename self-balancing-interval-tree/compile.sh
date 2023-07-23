#!/bin/bash -e

gcc -g -Wall main.c                  -o main.o -c
gcc -g -Wall rotation.c              -o rotation.o -c
gcc -g -Wall insertion.c             -o insertion.o -c
gcc -g -Wall deletion.c              -o deletion.o -c
gcc -g -Wall validate.c              -o validate.o -c
gcc -g -Wall utilities.c             -o utilities.o -c
gcc -g -Wall linkedlist.c            -o linkedlists.o -c
gcc -g -Wall sweep_line_algorithm.c  -o sweep_line_algorithm.o -c
gcc -g -Wall rectangles_generation.c -o rectangles_generation.o -c


gcc -g -o a.out main.o rotation.o insertion.o validate.o deletion.o utilities.o \
          linkedlists.o sweep_line_algorithm.o rectangles_generation.o

rm -f *.o vgcore.* log.core.*
