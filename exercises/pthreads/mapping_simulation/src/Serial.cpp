// Copyright 2021 Daniel Perez-Morera <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
#include "unistd.h"
#include "Serial.hpp"


Serial::Serial(std::vector<uint64_t>* data) {
  this->data = data;
}

// procedure serial(data, data_count)
int Serial::run() {
    // for ( index := 0; index < data_count; index := index + 1)
  for (uint64_t index = 0; index < data->size(); ++index) {
    // process(data(index))
    sleep(this->data->at(index));
  }
  // end for
  return EXIT_SUCCESS;
}  // end procedure
