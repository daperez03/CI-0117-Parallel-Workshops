// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include <cstdlib>
#include <mutex>
#include <vector>
#include "Thread.hpp"

class Dynamic : public Thread{
 private:
  uint64_t* index;
  uint64_t thread_number;
  std::mutex* can_access;
  uint64_t* mapping;
  std::vector<uint64_t>* data;
 public:
  Dynamic(uint64_t* index, std::mutex* can_access
    , uint64_t thread_number, uint64_t* mapping, std::vector<uint64_t>* data);
  int run();
};

#endif
