// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include "Common.hpp"

Common::Common() {
  this->unit_count = 0;
  this->producer_count = 0;
  this->consumer_count = 0;
  this->producer_min_delay = 0;
  this->producer_max_delay = 0;
  this->consumer_min_delay = 0;
  this->consumer_max_delay = 0;
  this->next_unit = 0;
  //  sem_init(&this->can_consume, 0, 0);
  this->consumed_count = 0;
}

Common::~Common() {
  //  sem_destroy(&this->can_consume);
}


useconds_t Common::random_between(useconds_t min, useconds_t max) {
  return min + (max > min ? (random() % (max - min)) : 0);
}
