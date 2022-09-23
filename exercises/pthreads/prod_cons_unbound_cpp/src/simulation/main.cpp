// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Simulates a producer and a consumer that share a unbounded buffer

#include <cstdlib>
#include <iostream>

#include "Simulation.hpp"

int main(int argc, char* argv[]) {
  Simulation simulation;
  simulation.run(argc, argv);
  return EXIT_SUCCESS;
}
