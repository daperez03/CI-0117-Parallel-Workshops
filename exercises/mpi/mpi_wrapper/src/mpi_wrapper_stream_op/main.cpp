// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#if 0
#include <iostream>
#include <string>
#include "../Mpi.hpp"

int main(int argc, char* argv[]) {
  Mpi mpi(argc, argv);
  if (mpi.getProcessNumber() > 0) {
    mpi[0] << "Hello from " << mpi.getProcessNumber();
  } else {
    for (int source = 1; source < mpi.getProcessCount(); ++source) {
        std::string text;
        int rank = 0;
        mpi[source] >> text >> rank;
        std::cout << source << " says: " << text << rank << std::endl;
    }
  }
}
#endif
