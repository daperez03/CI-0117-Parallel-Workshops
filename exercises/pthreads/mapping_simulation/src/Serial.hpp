// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <cstdlib>
#include <mutex>
#include <vector>
#include "Thread.hpp"

class Serial : public Thread{
 private:
  std::vector<uint64_t>* data;
 public:
  explicit Serial(std::vector<uint64_t>* data);
  int run();
};
#endif
