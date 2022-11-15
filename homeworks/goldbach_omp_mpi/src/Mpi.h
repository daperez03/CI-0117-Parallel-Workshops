#ifndef MPI_H
#define MPI_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <mpi.h>

#define ERROR_MPI_INIT 1
#define ERROR_MPI_RANK 2
#define ERROR_MPI_SIZE 3
#define ERROR_PROCESSOR_NAME 4
#define ERROR_SEND 5
#define ERROR_RECEIVE 6
#define TAG_DATA 0
#define TAG_DATA_REPORT 1
#define TAG_ID_PROCESS 2
#define TAG_STOPPING_CONDITION 3

enum DATA_REPORT{index_data, count_data, number_data = 1};

typedef struct mpi_data {
  /// @brief process hostname
  char* process_hostname;
  /// @brief process number
  int process_number;
  /// @brief process count
  int process_count;
  ssize_t pending_process;
} mpi_data_t;

// typedef struct _MPI_Status {
//   int count;
//   int cancelled;
//   int MPI_SOURCE;
//   int MPI_TAG;
//   int MPI_ERROR;
// } MPI_Status, *PMPI_Status;

uint64_t init_mpi(mpi_data_t* mpi_data, int* argc, char*** argv);
void uninit_mpi();
uint64_t send_bool(const bool* value, int toProcess, int tag);
uint64_t send_int32_t(const int32_t* values, int count, int toProcess, int tag);
uint64_t send_int64_t(const int64_t* values, int count, int toProcess, int tag);
uint64_t send_uint64_t(const uint64_t* values, int count, int toProcess, int tag);
uint64_t receive_bool(bool* value, int fromProcess, int tag);
uint64_t receive_int32_t(int32_t* values, int capacity
  , int fromProcess, int tag);
uint64_t receive_int64_t(int64_t* values, int capacity
  , int fromProcess, int tag, MPI_Status* status);
uint64_t receive_uint64_t(uint64_t* values, int capacity
  , int fromProcess, int tag);

#endif
