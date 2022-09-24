// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#ifndef MY_PRODUCER_HPP
#define MY_PRODUCER_HPP

#include "../prodcons/Producer.hpp"
#include "Common.hpp"

class My_Producer : public Producer {
 private:
  size_t thread_number;
  size_t count;
  Common* shared_data;
 public:
  My_Producer(size_t thread_number, size_t count,  void* data);
  int run() override;
  void produce() override;
};
#endif
