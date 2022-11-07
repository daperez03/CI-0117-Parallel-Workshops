// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#ifndef MPIERROR_HPP
#define MPIERROR_HPP
#include <string>
#include <stdexcept>

/// @brief Class error code
#define MPI_FAILURE -1
/// @brief Error message for the constructor
#define ERROR_01 "the MPI ambiance cloud not be started"
/// @brief Error message for the get process number
#define ERROR_02 "not possible to access process number"
/// @brief Error message for the get process count
#define ERROR_03 "not possible to access process count"
/// @brief Error message for the get hostname
#define ERROR_04 "not possible to access hostname"
/// @brief Error could not send message
#define ERROR_05 "could not send message"
/// @brief Error could not receive message
#define ERROR_06 "could not receive message"

class Mpi;
/// @brief MPI error handling class
class MpiError : public std::runtime_error {
 public:
  /// @brief String constructor of MpiError
  /// @param message data string
  explicit MpiError(const std::string& message);
  /// @brief interactive MPI error constructor
  /// @param message data string
  /// @param mpi Instance of mpi
  MpiError(const std::string& message, const Mpi& mpi);
  /// @brief interactive MPI error constructor of parallel process
  /// @param message
  /// @param mpi
  /// @param threadNumber
  MpiError(const std::string& message, const Mpi& mpi, const int threadNumber);
};

#endif
