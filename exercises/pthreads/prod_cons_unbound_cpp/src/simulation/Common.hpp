// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#ifndef COMMON_H
#define COMMON_H

#include <semaphore.h>
#include <unistd.h>

#include <cstdlib>
#include <mutex>

#include "../prodcons/Queue.hpp"

enum {
  ERR_NOMEM_SHARED = EXIT_FAILURE + 1,
  ERR_NOMEM_BUFFER,
  ERR_NO_ARGS,
  ERR_UNIT_COUNT,
  ERR_PRODUCER_COUNT,
  ERR_CONSUMER_COUNT,
  ERR_MIN_PROD_DELAY,
  ERR_MAX_PROD_DELAY,
  ERR_MIN_CONS_DELAY,
  ERR_MAX_CONS_DELAY,
  ERR_CREATE_THREAD,
};

class Common{
 public:
  Common();
  ~Common();
  useconds_t random_between(useconds_t min, useconds_t max);
  //  Struct
  size_t unit_count;
  size_t producer_count;
  size_t consumer_count;
  useconds_t producer_min_delay;
  useconds_t producer_max_delay;
  useconds_t consumer_min_delay;
  useconds_t consumer_max_delay;

  Queue<size_t> queue_to_use;
  std::mutex can_access_next_unit;
  size_t next_unit;
  //  sem_t can_consume;
  std::mutex can_access_consumed_count;
  size_t consumed_count;
};

#endif  // COMMON_H
