// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <mpi.h>
#include <cassert>
#include <string>
#include <system_error>
#ifndef MPI_HPP
#define MPI_HPP

/// @brief Class error code
#define MPI_FAILURE -1
/// @brief Error message for the constructor
const char* ERROR01 = "ERROR: The MPI ambiance cloud not be started\n";
/// @brief Error message for the get process number
const char* ERROR02 = "ERROR: Not possible to access process number\n";
/// @brief Error message for the get process count
const char* ERROR03 = "ERROR: Not possible to access process count\n";
/// @brief Error message for the get hostname
const char* ERROR04 = "ERROR: Not possible to access hostname\n";

class Mpi{
 public:
  /// @brief Generic MPI constructor
  /// @param argc Arguments count
  /// @param argv Arguments value
  Mpi(int& argc, char**& argv) {
    assert(argv);
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
      throw std::runtime_error(ERROR01);
    } else {
      if (MPI_Comm_rank(MPI_COMM_WORLD, &this->process_number) != MPI_SUCCESS) {
        throw std::runtime_error(ERROR02);
      } else {
        if (MPI_Comm_size(MPI_COMM_WORLD, &this->process_count)
          != MPI_SUCCESS) {
          throw std::runtime_error(ERROR03);
        } else {
          char process_hostname[MPI_MAX_PROCESSOR_NAME] = {0};
          int hostname_length = -1;
          if (MPI_Get_processor_name(process_hostname, &hostname_length)
            != MPI_SUCCESS) {
            throw std::runtime_error(ERROR04);
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
  int getProcessNumber() {
    return process_number;
  }

  /// @brief Get the count of the process in progress
  /// @return count of the process
  int getProcessCount() {
    return process_count;
  }

  /// @brief Get the current hostname
  /// @return current hostname
  std::string getHostname() {
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
