// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#include "Dynamic.hpp"
#include <unistd.h>
#include <iostream>

Dynamic::Dynamic(uint64_t* index, std::mutex* can_access
  , uint64_t thread_number, uint64_t* mapping, std::vector<uint64_t>* data) {
  this->index = index;
  this->thread_number = thread_number;
  this->can_access = can_access;
  this->mapping = mapping;
  this->data = data;
}

// procedure dynamic(data, data_count)
int Dynamic::run() {
  // while(true)
  uint64_t index = 0;
  while (true) {
    // lock(can_access)
    this->can_access->lock();
    // if(index = data_count) break while
    if (*(this->index) >= this->data->size()) {
      this->can_access->unlock();
      break;
    }
    index = (*(this->index))++;
    this->can_access->unlock();
    // process(data(index))
    sleep(this->data->at(index));
    mapping[this->thread_number] += this->data->at(index);
    // index := index + 1
    // unlock(can_access)
    // end while
  }
  // end procedure
  return EXIT_SUCCESS;
}
