#!/bin/sh
export LD_LIBRARY_PATH=${PWD}/sample/lib:${PWD}/walker/lib:${PWD}/mean_std/lib

mpirun -n $1 ${PWD}/test/mpi_prac $2
