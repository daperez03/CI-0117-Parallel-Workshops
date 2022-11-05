// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#ifndef MPIERROR_HPP
#define MPIERROR_HPP
#include <string>
#include <stdexcept>
class Mpi;

class MpiError : public std::runtime_error {
 public:
  explicit MpiError(const std::string& message);
  MpiError(const std::string& message, const Mpi& mpi);
  MpiError(const std::string& message, const Mpi& mpi, const int threadNumber);
};

#endif
