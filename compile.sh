#!/bin/sh
gcc -O0 -o seq seq.c ;
gcc -O0 -o strat1 -fopenmp strat1.c ;
gcc -O0 -o strat2 -fopenmp strat2.c ; 
gcc -O0 -o strat3 -fopenmp strat3.c  ;
mpicc -g -Wall -o strat4 strat4.c ; 