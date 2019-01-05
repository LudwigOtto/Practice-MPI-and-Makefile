#!/bin/sh
export LD_LIBRARY_PATH=${PWD}/sample
echo $LD_LIBRARY_PATH

mpirun -n $1 ${PWD}/send_recv
