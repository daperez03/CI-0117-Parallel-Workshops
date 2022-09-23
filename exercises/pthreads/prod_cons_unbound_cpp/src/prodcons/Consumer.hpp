// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include "Thread.hpp"

class Consumer : public Thread {
 public:
  virtual void consume() = 0;
};

#endif
