// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <mutex>
#include <string>
#include <iostream>
#include <vector>
#include "Block.hpp"
#include "Cyclic.hpp"
#include "Dynamic.hpp"
#include "Serial.hpp"

#define speedup(Tbefore, Tafter) Tbefore/Tafter
#define efficiency(speedup, workers) speedup/workers
enum mappings{serial_t, block_t, cyclic_t, dynamic_t};

double getTime(struct timespec start_time, struct timespec finish_time);
void statistics(enum mappings type, uint64_t thread_count
  , double* time, uint64_t* mapping);

int main(int argc, char* argv[]) {
  struct timespec start_time, finish_time;
  // shared thread_count := argv[1]
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  double time[4] = {0};
  try {
    if (argc == 2) thread_count = std::strtoull(argv[1], nullptr, 10);
    // declare data[]
    uint64_t mapping[thread_count] = {0};
    std::vector<uint64_t> data;
    // while(input != Fin)
    std::string input;
    while (!std::cin.eof()) {
      // data.push_back(get(input))
      std::getline(std::cin, input);
      data.push_back(std::strtoull(input.c_str(), nullptr, 10));
      // end while
    }

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    // declare serial := createThread(serial(data, data_count))
    Serial* serial = new Serial(&data);
    serial->startThread();
    // waitThread(serial)
    serial->waitToFinish();
    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    time[serial_t] = getTime(start_time, finish_time);
    std::cout << time[serial_t] << "\t\t";
    for (size_t i = 0; i < thread_count; i++) std::cout << i << "\t\t";
    std::cout << "Duration\tSpeedup\t\tEfficiency" << std::endl;

    // declare blocks =: createThreads
    // (block(copy(data), data_count), thread_count)
    std::vector<Block*> blocks;
    blocks.resize(thread_count);
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (uint64_t i = 0; i < thread_count; ++i) {
      blocks[i] = new Block(i, thread_count, mapping, &data);
      blocks[i]->startThread();
    }
    // waitThreads(blocks)
    for (uint64_t i = 0; i < thread_count; ++i) {
      blocks[i]->waitToFinish();
    }
    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    time[block_t] = getTime(start_time, finish_time);
    std::cout << "Block\t\t";
    statistics(block_t, thread_count, time, mapping);

    // declare cyclicals := createThreads
    // (cyclic(copy(data), data_count), thread_count)
    std::vector<Cyclic*> cyclicals;
    cyclicals.resize(thread_count);
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (uint64_t i = 0; i < thread_count; ++i) {
      cyclicals[i] = new Cyclic(i, thread_count, mapping, &data);
      cyclicals[i]->startThread();
    }
    // waitThreads(cyclicals)
    for (uint64_t i = 0; i < thread_count; ++i) {
      cyclicals[i]->waitToFinish();
    }
    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    time[cyclic_t] = getTime(start_time, finish_time);
    std::cout << "Cyclic\t\t";
    statistics(cyclic_t, thread_count, time, mapping);

    // shared index := 0
    uint64_t index = 0;
    // shared can_access := mutex()
    std::mutex can_access;
    // declare dynamics := createThreads(dynamic(copy(data), data_count))
    std::vector<Dynamic*> dynamics;
    dynamics.resize(thread_count);
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (uint64_t i = 0; i < thread_count; ++i) {
      dynamics[i] = new Dynamic(&index, &can_access, i, mapping, &data);
      dynamics[i]->startThread();
    }
    // waitThreads(dynamics)
    for (uint64_t i = 0; i < thread_count; ++i) {
      dynamics[i]->waitToFinish();
    }
    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    time[dynamic_t] = getTime(start_time, finish_time);
    std::cout << "Dynamic\t\t";
    statistics(dynamic_t, thread_count, time, mapping);

    // print(Statistics(blocks, cyclicals, dynamics))
    delete serial;
    for (uint64_t i = 0; i < thread_count; ++i) {
      delete dynamics[i];
      delete blocks[i];
      delete cyclicals[i];
    }
  }catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void statistics(enum mappings type, uint64_t thread_count
  , double* time, uint64_t* mapping) {
  for (size_t i = 0; i < thread_count; i++) {
    std::cout << mapping[i] << "\t\t";
    mapping[i] = 0;
  }
  double speedup = speedup(time[serial_t], time[type]);
  double efficiency = efficiency(speedup, thread_count);
  std::cout << time[type] << "\t\t" << speedup << "\t\t" << efficiency << '\n';
}

double getTime(struct timespec start_time, struct timespec finish_time) {
  return finish_time.tv_sec - start_time.tv_sec
    + (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
}
