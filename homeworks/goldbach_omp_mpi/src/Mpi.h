/// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
#ifndef MPI_H
#define MPI_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <mpi.h>

#define ERROR_SEND_MSG "Error: the data cloud not be sent\n"
#define ERROR_RECEIVE_MSG "Error: the data cloud not be receive\n"
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

/// @brief Data of process
typedef struct mpi_data {
  /// @brief process hostname
  char* process_hostname;
  /// @brief process number
  int process_number;
  /// @brief process count
  int process_count;
  ssize_t pending_process;
} mpi_data_t;

/// @brief Initialised of a process
/// @param mpi_data Data of process
/// @param argc Argument count
/// @param argv Argument vector
/// @return error code
uint64_t init_mpi(mpi_data_t* mpi_data, int* argc, char*** argv);

/// @brief Close of a process
void uninit_mpi();

/// @brief Send a boolean data
/// @param value Boolean value
/// @param toProcess Receiving process
/// @param tag Tag of send
/// @return 0 if it's success or 5 if it's error
uint64_t send_bool(const bool* value, int toProcess, int tag);

/// @brief Send integer values
/// @param values Integer values
/// @param count Amount of data
/// @param toProcess Receiving process
/// @param tag Tag of send
/// @return 0 if it's success or 5 if it's error
uint64_t send_int32_t(const int32_t* values, int count
  , int toProcess, int tag);

/// @brief Send integer values
/// @param values Integer values
/// @param count Amount of data
/// @param toProcess Receiving process
/// @param tag Tag of send
/// @return 0 if it's success or 5 if it's error
uint64_t send_int64_t(const int64_t* values, int count
  , int toProcess, int tag);

/// @brief Send unsigned integer values
/// @param values Unsigned Integer values
/// @param count Amount of data
/// @param toProcess Receiving process
/// @param tag Tag of send
/// @return 0 if it's success or 5 if it's error
uint64_t send_uint64_t(const uint64_t* values, int count
  , int toProcess, int tag);

/// @brief Receive boolean value
/// @param value Boolean container
/// @param fromProcess Issuing process
/// @param tag Tag of receive
/// @return 0 if it's success or 6 if it's error
uint64_t receive_bool(bool* value, int fromProcess, int tag);

/// @brief Receive integer values
/// @param values Integer container
/// @param capacity Amount of data
/// @param fromProcess Issuing process
/// @param tag Tag of receive
/// @return 0 if it's success or 6 if it's error
uint64_t receive_int32_t(int32_t* values, int capacity
  , int fromProcess, int tag);

/// @brief Receive integer values
/// @param values Integer container
/// @param capacity Amount of data
/// @param fromProcess Issuing process
/// @param tag Tag of receive
/// @return 0 if it's success or 6 if it's error
uint64_t receive_int64_t(int64_t* values, int capacity
  , int fromProcess, int tag);

/// @brief Receive unsigned integer values
/// @param values Unsigned integer container
/// @param capacity Amount of data
/// @param fromProcess Issuing process
/// @param tag Tag of receive
/// @return 0 if it's success or 6 if it's error
uint64_t receive_uint64_t(uint64_t* values, int capacity
  , int fromProcess, int tag);

#endif
