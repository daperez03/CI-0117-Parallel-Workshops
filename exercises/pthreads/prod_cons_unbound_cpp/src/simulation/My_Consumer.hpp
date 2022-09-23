// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#ifndef MY_CONSUMER_HPP
#define MY_CONSUMER_HPP

#include <cstdlib>

#include "Common.hpp"
#include "../prodcons/Consumer.hpp"

class My_Consumer : public Consumer {
 public:
  My_Consumer(size_t thread_number, size_t count, void* data);
  ~My_Consumer() {}
  int run() override;
  void consume() override;
  Common* shared_data;
  size_t thread_count;
  size_t thread_number;
};
#endif
