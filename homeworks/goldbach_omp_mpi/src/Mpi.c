#include "Mpi.h"

uint64_t init_mpi(mpi_data_t* mpi_data, int* argc, char*** argv) {
  assert(mpi_data);
  assert(argv);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Init(argc, argv) != MPI_SUCCESS) {
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
  return error;
}

void uninit_mpi() {
  MPI_Finalize();
}

uint64_t send_bool(const bool* value, int toProcess, int tag) {
  assert(value);
  assert(toProcess >= 0);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Send(value, 1, MPI_C_BOOL, toProcess, tag
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    error = ERROR_SEND;
  }
  return error;
}

uint64_t send_int32_t(const int32_t* values, int count, int toProcess, int tag) {
  assert(values);
  assert(toProcess >= 0);
  assert(count >= 1);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Send(values, count, MPI_INT, toProcess, tag
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    error = ERROR_SEND;
  }
  return error;
}

uint64_t send_int64_t(const int64_t* values, int count, int toProcess, int tag) {
  assert(values);
  assert(toProcess >= 0);
  assert(count >= 1);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Send(values, count, MPI_INT64_T , toProcess, tag
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    error = ERROR_SEND;
  }
  return error;
}

uint64_t send_uint64_t(const uint64_t* values, int count, int toProcess, int tag) {
  assert(values);
  assert(toProcess >= 0);
  assert(count >= 1);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Send(values, count, MPI_UNSIGNED_LONG, toProcess, tag
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    error = ERROR_SEND;
  }
  return error;
}

uint64_t receive_bool(bool* value, int fromProcess, int tag) {
  // assert(fromProcess >= 0);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Recv(value, 1, MPI_C_BOOL, fromProcess, tag
    , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
    error = ERROR_RECEIVE;
  }
  return error;
}

uint64_t receive_int32_t(int32_t* values, int capacity
  , int fromProcess, int tag) {
  assert(values);
  assert(capacity >= 1);
  // assert(fromProcess >= 0);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Recv(values, capacity, MPI_INT, fromProcess, tag
    , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
    error = ERROR_RECEIVE;
  }
  return error;
}

uint64_t receive_int64_t(int64_t* values, int capacity
  , int fromProcess, int tag, MPI_Status* status) {
  assert(values);
  assert(capacity >= 1);
  // assert(fromProcess >= 0);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Recv(values, capacity, MPI_INT64_T , fromProcess, tag
    , MPI_COMM_WORLD, status) != MPI_SUCCESS) {
    error = ERROR_RECEIVE;
  }
  return error;
}

uint64_t receive_uint64_t(uint64_t* values, int capacity
  , int fromProcess, int tag) {
  assert(values);
  assert(capacity >= 1);
  // assert(fromProcess >= 0);
  uint64_t error = EXIT_SUCCESS;
  if (MPI_Recv(values, capacity, MPI_UNSIGNED_LONG, fromProcess, tag
    , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
    error = ERROR_RECEIVE;
  }
  return error;
}
