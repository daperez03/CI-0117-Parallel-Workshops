// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#ifndef CYCLIC_HPP
#define CYCLIC_HPP

#include <cstdlib>
#include <mutex>
#include <vector>
#include "Thread.hpp"

class Cyclic : public Thread{
 private:
  uint64_t thread_number;
  uint64_t thread_count;
  uint64_t* mapping;
  std::vector<uint64_t>* data;
 public:
  Cyclic(uint64_t thread_number, uint64_t thread_count
    , uint64_t* mapping, std::vector<uint64_t>* data);
  int run();
};

#endif
