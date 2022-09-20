#include <cassert>

#include "Thread.hpp"

Thread::Thread() {}

Thread::~Thread() {}

int Thread::startThread() {
  assert(this->thread == nullptr);
  this->thread = new std::thread(&Thread::run, this);
  return EXIT_SUCCESS;
}

int Thread::waitToFinish() {
  assert(this->thread);
  this->thread->join();
  delete this->thread;
  this->thread = nullptr;
  return EXIT_SUCCESS;
}
