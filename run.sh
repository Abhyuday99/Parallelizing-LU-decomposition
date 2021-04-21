#!/bin/sh


if [ "$4" == "0" ]
then 
./seq $1 $2 $3
elif [ "$4" ==  "1" ]
then
./strat1 $1 $2 $3
elif [ "$4" ==  "2" ]
then
./strat2 $1 $2 $3
elif [ "$4" ==  "3" ]
then
./strat3 $1 $2 $3
elif [ "$4" ==  "4" ]
then
mpiexec -n $3 ./strat4 $1 $2 $3
fi
