// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#ifndef MPI_HPP
#define MPI_HPP
#include <mpi.h>
#include <cassert>
#include <string>
#include "MpiError.hpp"

/// @brief Class error code
#define MPI_FAILURE -1
/// @brief Error message for the constructor
#define ERROR01 "The MPI ambiance cloud not be started"
/// @brief Error message for the get process number
#define ERROR02 "Not possible to access process number"
/// @brief Error message for the get process count
#define ERROR03 "Not possible to access process count"
/// @brief Error message for the get hostname
#define ERROR04 "Not possible to access hostname"

class Mpi{
 public:
  /// @brief Generic MPI constructor
  /// @param argc Arguments count
  /// @param argv Arguments value
  Mpi(int& argc, char**& argv) {
    assert(argv);
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
      throw MpiError(ERROR01);
    } else {
      if (MPI_Comm_rank(MPI_COMM_WORLD, &this->process_number) != MPI_SUCCESS) {
        throw MpiError(ERROR02);
      } else {
        if (MPI_Comm_size(MPI_COMM_WORLD, &this->process_count)
          != MPI_SUCCESS) {
          throw MpiError(ERROR03);
        } else {
          char process_hostname[MPI_MAX_PROCESSOR_NAME] = {0};
          int hostname_length = -1;
          if (MPI_Get_processor_name(process_hostname, &hostname_length)
            != MPI_SUCCESS) {
            throw MpiError(ERROR04);
          } else {
            this->process_hostname = std::string(process_hostname);
          }
        }
      }
    }
  }

  /// @brief Generic MPI destructor
  ~Mpi() {
    MPI_Finalize();
  }

  /// @brief Get the number of the process in progress
  /// @return number of the process
  int getProcessNumber() const {
    return process_number;
  }

  /// @brief Get the count of the process in progress
  /// @return count of the process
  int getProcessCount() const {
    return process_count;
  }

  /// @brief Get the current hostname
  /// @return current hostname
  std::string getHostname() const {
    return process_hostname;
  }

 protected:
  /// @brief process hostname
  std::string process_hostname;
  /// @brief process number
  int process_number = 0;
  /// @brief process count
  int process_count = 0;
};
#endif
