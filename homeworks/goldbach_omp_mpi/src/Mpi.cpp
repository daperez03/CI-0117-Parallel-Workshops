#include "Mpi.h"
#include <stdlib.h>

#define MPI_MAX_PROCESSOR_NAME 100
#define ERROR_MPI_INIT 1
#define ERROR_MPI_RANK 2
#define ERROR_MPI_SIZE 3
#define ERROR_PROCESSOR_NAME 4 

typedef struct mpi_data {
  /// @brief process hostname
  char* process_hostname;
  /// @brief process number
  int process_number = 0;
  /// @brief process count
  int process_count = 0;
} mpi_data_t;

uint64_t mpi_init(mpi_data_t* mpi_data, int argc, char** argv) {
  assert(mpi_data);
  assert(argv);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
    error = ERROR_MPI_INIT;
  } else {
    if (MPI_Comm_rank(MPI_COMM_WORLD, &mpi_data->process_number) != MPI_SUCCESS) {
      error = ERROR_MPI_RANK;
    } else {
      if (MPI_Comm_size(MPI_COMM_WORLD, &mpi_data->process_count)
        != MPI_SUCCESS) {
        error = ERROR_MPI_SIZE;
      } else {
        char process_hostname[MPI_MAX_PROCESSOR_NAME] = {0};
        int hostname_length = -1;
        if (MPI_Get_processor_name(process_hostname, &hostname_length)
          != MPI_SUCCESS) {
          error = ERROR_PROCESSOR_NAME;
        } else {
          mpi_data->process_hostname = process_hostname;
        }
      }
    }
  }
}

uint64_t send(mpi_data_t* mpi_data, const bool value, int toProcess, int tag = 0) {
  if (MPI_Send(&value, 1, MPI_C_BOOL, toProcess, tag
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    throw MpiError(ERROR_05, (*this));
  }
}

void send(mpi_data_t* mpi_data, const int64t value, int toProcess, int tag = 0) {

}

void receive(mpi_data_t* mpi_data, uint64_t* values, int capacity = 1, int fromProcess = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG) {

}
