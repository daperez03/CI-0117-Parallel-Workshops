// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#ifndef THREAD_HPP
#define THREAD_HPP

#include <cstdlib>
#include <thread>

class Thread {
 protected:
  std::thread* thread = nullptr;

 public:
  Thread();
  virtual ~Thread();
  void startThread();
  void waitToFinish();

 protected:
  virtual int run() = 0;
};

#endif
