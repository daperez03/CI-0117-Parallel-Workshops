// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include "My_Producer.hpp"

My_Producer::My_Producer(size_t thread_number, size_t count, void*data) {
  this->thread_number = thread_number;
  this->count = count;
  this->shared_data = reinterpret_cast<Common*>(data);
}

int My_Producer::run() {
  this->produce();
  return EXIT_SUCCESS;
}

void My_Producer::produce() {
  // const private_data_t* private_data = (private_data_t*)data;
  while (true) {
    // declare my_unit := 0
    size_t my_unit = 0;
    // lock(can_access_next_unit)
    this->shared_data->can_access_next_unit.lock();
    // If is there pending work, take a unit for producing
      if (this->shared_data->next_unit < this->shared_data->unit_count) {
        my_unit = ++this->shared_data->next_unit;
      } else {
        // unlock(can_access_next_unit)
        this->shared_data->can_access_next_unit.unlock();
        // break while
        break;
      }
    // unlock(can_access_next_unit)
    this->shared_data->can_access_next_unit.unlock();
    usleep(1000 * this->shared_data->random_between(
      this->shared_data->producer_min_delay
        , this->shared_data->producer_max_delay));
    this->shared_data->queue_to_use.enqueue(my_unit);
    std::string consumer_message;
    consumer_message += "Produced ";
    consumer_message += my_unit + '0';
    consumer_message += '\n';
    std::cout << consumer_message;
    // signal(can_consume)
    // sem_post(&this->shared_data->can_consume);
  }
}
