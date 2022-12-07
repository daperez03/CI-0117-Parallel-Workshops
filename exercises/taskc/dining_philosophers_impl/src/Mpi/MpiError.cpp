// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include "MpiError.hpp"
#include "Mpi.hpp"

MpiError::MpiError(const std::string& message)
  : std::runtime_error(message) {}

MpiError::MpiError(const std::string& message, const Mpi& mpi)
  : std::runtime_error(mpi.getHostname() + std::string(":")
    + std::to_string(mpi.getProcessNumber()) + std::string(": ") + message) {
}

MpiError::MpiError(const std::string& message, const Mpi& mpi
  , const int threadNumber) : std::runtime_error(mpi.getHostname()
    + std::string(":") + std::to_string(mpi.getProcessNumber())
      + std::string(".") + std::to_string(threadNumber) + std::string(": ")
        + message) {}
