// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#include <iostream>
#include <mutex>
#include <thread>
#include "My_Consumer.hpp"

My_Consumer::My_Consumer(size_t thread_number, size_t count, void*data) {
  this->shared_data = reinterpret_cast<Common*>(data);
  this->thread_count = count;
  this->thread_number = thread_number;
}

int My_Consumer::run() {
  this->consume();
  return EXIT_SUCCESS;
}

void My_Consumer::consume() {
  while (true) {
    // lock(can_access_consumed_count)
    this->shared_data->can_access_consumed_count.lock();
      if (this->shared_data->consumed_count < this->shared_data->unit_count) {
        // Reserve the next product to me
        ++this->shared_data->consumed_count;
      } else {
        // unlock(can_access_consumed_count)
        this->shared_data->can_access_consumed_count.unlock();
        // break while
        break;
      }
      // unlock(can_access_consumed_count)
    this->shared_data->can_access_consumed_count.unlock();
    //  wait(can_consume)
    //  sem_wait(&this->shared_data->can_consume);
    size_t value = this->shared_data->queue_to_use.dequeue();
    std::cout << "\tConsuming " << value << std::endl;
    usleep(1000 * this->shared_data->random_between(
      shared_data->consumer_min_delay, shared_data->consumer_max_delay));
  }
}
