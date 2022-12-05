// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <iostream>
#include "./../Mpi.hpp"
int main(int argc, char* argv[]) {
  try {
    Mpi mpi(argc, argv);
    if (mpi.getProcessCount() == 2) {
      int ball = 0;
      if (mpi.getProcessNumber() == 0) {
        mpi[1] << ball;
      }
      while (true) {
        mpi[!mpi.getProcessNumber()] >> ball << ball;
      }
    } else {
      throw std::runtime_error("cloud process count is invalid");
    }
  }
  catch(const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }
}
