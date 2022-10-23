// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#include "Block.hpp"
#include <unistd.h>
#include <iostream>

Block::Block(uint64_t thread_number, uint64_t thread_count
    , uint64_t* mapping, std::vector<uint64_t>* data) {
  this->thread_number = thread_number;
  this->thread_count = thread_count;
  this->mapping = mapping;
  this->data = data;
}

// procedure block(data, data_count)
int Block::run() {
  // declare my_start := start(thread_number, data_count, thread_count)
  uint64_t my_start = start(thread_number, data->size(), thread_count);
  // declare my_finish
  uint64_t my_finish = finish(thread_number, data->size(), thread_count);
  // for(index := my_start; index < my_finish; index++)
  for (uint64_t index = my_start; index < my_finish; ++index) {
    // process(data(index))
    sleep(this->data->at(index));
    mapping[this->thread_number] += this->data->at(index);
  }
  // end for
  return EXIT_SUCCESS;
}

uint64_t Block::start(uint64_t thread_number
  , uint64_t data_count, uint64_t thread_count) {
  uint64_t my_start = thread_number * (data_count / thread_count);
  uint64_t mod = data_count % thread_count;
  return my_start + ((thread_number < mod)? thread_number : mod);
}

uint64_t Block::finish(uint64_t thread_number
  , uint64_t data_count, uint64_t thread_count) {
  return start(thread_number + 1, data_count, thread_count);
}
