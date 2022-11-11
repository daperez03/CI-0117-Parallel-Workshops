// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#if 0
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "../Mpi.hpp"

#define fail(msg) throw std::runtime_error(msg)

const size_t MESSAGE_CAPACITY = 512;

void greet(Mpi& mpi);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  try {
      Mpi mpi(argc, argv);
      greet(mpi);
  } catch (const std::runtime_error& exception) {
      std::cerr << "error: " << exception.what() << std::endl;
      error =  EXIT_FAILURE;
  }
  return error;
}

void greet(Mpi& mpi) {
  std::stringstream buffer;
  buffer << "Hello from main thread of process " << mpi.getProcessNumber()
    << " of " << mpi.getProcessCount() << " on " << mpi.getHostname();

  if (mpi.getProcessNumber() != 0) {
    const std::string& message = buffer.str();
    mpi.send(message, 0);
  } else {
    std::cout << mpi.getProcessNumber() << " said " << buffer.str()
      << std::endl;
    for (int source = 1; source < mpi.getProcessCount(); ++source) {
      std::string message;
      mpi.receive(message, MESSAGE_CAPACITY, source);
      std::cout << source << " sent " << message << std::endl;
    }
  }
}
#endif
