// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#include "Thread.hpp"

Thread::Thread() {}

Thread::~Thread() {
  if (this->thread != nullptr) {
    delete this->thread;
  }
}

void Thread::startThread() {
  this->thread = new std::thread(&Thread::run, this);
}

void Thread::waitToFinish() {
  this->thread->join();
  delete this->thread;
  this->thread = nullptr;
}
