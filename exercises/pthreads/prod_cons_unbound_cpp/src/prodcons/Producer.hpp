// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "Thread.hpp"

class Producer : public Thread {
 public:
  Producer() {}
  virtual void produce() = 0;
};
#endif
