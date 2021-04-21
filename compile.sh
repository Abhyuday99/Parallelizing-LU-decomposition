#!/bin/sh
gcc -o seq seq.c ;
gcc -o strat1 -fopenmp strat1.c ;
gcc -o strat2 -fopenmp strat2.c ; 
gcc -o strat3 -fopenmp strat3.c  ;