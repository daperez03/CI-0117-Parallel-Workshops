// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <sys/random.h>

#include <chrono>
#include <iostream>
#include <cstdlib>


#include "Simulation.hpp"

  //  Constructores
Simulation::Simulation() {}

  //  Desdructores
Simulation::~Simulation() {}

  //  Metodos
int Simulation::run(int argc, char* argv[]) {
  int error = analyze_arguments(argc, argv);
  if (error == EXIT_SUCCESS) {
    unsigned int seed = 0;
      //  getrandom(&seed, sizeof(seed), GRND_NONBLOCK);
    srandom(seed);

    auto start_time =
      std::chrono::high_resolution_clock::now();

    create_consumers_producers();
    join_threads();

    auto finish_time =
      std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_time = finish_time - start_time;

    std::cout << "Execution time: " << elapsed_time.count() << std::endl;
  }
  return error;
}

int Simulation::analyze_arguments(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  size_t index = 1;
  try {
    if (argc == 8) {
      try {
        this->shared_data.unit_count = std::atoi(argv[index++]);
        this->shared_data.producer_count = std::atoi(argv[index++]);
        this->shared_data.consumer_count = std::atoi(argv[index++]);
        this->shared_data.producer_min_delay = std::atoi(argv[index++]);
        this->shared_data.producer_max_delay = std::atoi(argv[index++]);
        this->shared_data.consumer_min_delay = std::atoi(argv[index++]);
        this->shared_data.consumer_max_delay = std::atoi(argv[index++]);
      } catch (const char* error_print) {
        std::cerr << error_print  << std::endl;
      }
    } else {
      throw "usage: producer_consumer buffer_capacity rounds"
        " producer_min_delay producer_max_delay"
        " consumer_min_delay consumer_max_delay\n";
        error = ERR_NO_ARGS;
    }
  } catch (const char* error_print) {
      std::cerr << "Data " << error_print << " is invalid" << std::endl;
  }
  return error;
}

void Simulation::create_consumers_producers() {
  this->producers.resize(this->shared_data.producer_count);
  for (size_t index = 0; index < this->shared_data.producer_count; ++index) {
    this->producers[index] = new My_Producer(index
      , this->shared_data.producer_count, &shared_data);
    this->producers[index]->startThread();
  }
  this->consumers.resize(this->shared_data.consumer_count);
  for (size_t index = 0; index < this->shared_data.consumer_count; ++index) {
    this->consumers[index] = new My_Consumer(index
    , this->shared_data.consumer_count
      , reinterpret_cast<void*>(&shared_data));
    this->consumers[index]->startThread();
  }
}

void Simulation::join_threads() {
  for (size_t index = 0; index < this->shared_data.producer_count; ++index) {
    this->producers[index]->waitToFinish();
    delete this->producers[index];
  }
  for (size_t index = 0; index < this->shared_data.consumer_count; ++index) {
    this->consumers[index]->waitToFinish();
    delete this->consumers[index];
  }
}
