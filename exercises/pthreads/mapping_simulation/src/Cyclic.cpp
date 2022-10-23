// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#include "Cyclic.hpp"
#include <unistd.h>
#include <iostream>

Cyclic::Cyclic(uint64_t thread_number, uint64_t thread_count
  , uint64_t* mapping, std::vector<uint64_t>* data) {
  this->thread_number = thread_number;
  this->thread_count = thread_count;
  this->mapping = mapping;
  this->data = data;
}

// procedure cyclic(data, data_count)
int Cyclic::run() {
  // for(index := thread_number; index < data_count; index += thread_count)
  for (uint64_t index = thread_number
    ; index < data->size(); index += thread_count) {
    // process(data(index))
    sleep(this->data->at(index));
    mapping[this->thread_number] += this->data->at(index);
    // end for
  }
  // end procedure
  return EXIT_SUCCESS;
}
