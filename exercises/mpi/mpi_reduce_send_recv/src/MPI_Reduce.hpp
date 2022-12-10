// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#ifndef MPI_REDUCE
#define MPI_REDUCE

#include <mpi.h>

int reduce(const int& input, int& output
    , const int MPI_OPERATION, int root = 0);

#endif
