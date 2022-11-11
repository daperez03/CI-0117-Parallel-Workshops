#ifndef MPI_H
#define MPI_H

#include <assert.h>
#include <stdint.h>
#include <mpi.h>

typedef struct mpi_data mpi_data_t;

void mpi_init(mpi_data_t* mpi_data);
void send(mpi_data_t* mpi_data, const bool value, int toProcess, int tag = 0);
void send(mpi_data_t* mpi_data, const int64t value, int toProcess, int tag = 0);
void receive(mpi_data_t* mpi_data, uint64_t* values, int capacity = 1, int fromProcess = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG);
