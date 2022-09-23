// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <thread>
#include <cstdlib>
#include <vector>

#include "Common.hpp"
#include "My_Consumer.hpp"
#include "My_Producer.hpp"

class Simulation {
 public:
  //  Constructores
  Simulation();
  //  Desdructores
  ~Simulation();
  //  Metodos
  int run(int argc, char* argv[]);
 private:
  std::vector<My_Consumer*> consumers;
  std::vector<My_Producer*> producers;
  Common shared_data;
  int analyze_arguments(int argc, char* argv[]);
  void create_consumers_producers();
  void join_threads();
};
#endif  // SIMULATION_HPP
