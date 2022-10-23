// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstdlib>
#include <mutex>
#include <vector>
#include "Thread.hpp"

class Block : public Thread{
 private:
  uint64_t thread_number;
  uint64_t thread_count;
  uint64_t* mapping;
  std::vector<uint64_t>* data;
  uint64_t start(uint64_t thread_number
    , uint64_t data_count, uint64_t thread_count);
  uint64_t finish(uint64_t thread_number, uint64_t data_count
  , uint64_t thread_count);
 public:
  Block(uint64_t thread_number, uint64_t thread_count
    , uint64_t* mapping, std::vector<uint64_t>* data);
  int run();
};

#endif
