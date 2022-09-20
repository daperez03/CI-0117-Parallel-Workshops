// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdbool.h>
#include <stdio.h>

#include "common.h"
#include "consumer.h"

void is_there_pending_work_consume(simulation_t* simulation
  , bool* ptr_is_there_pending_work);

void* consume(void* data) {
  simulation_t* simulation = (simulation_t*)data;
  bool is_there_pending_work = false;
  is_there_pending_work_consume(simulation, &is_there_pending_work);
  while (is_there_pending_work) {
      //  wait(can_consume)
    sem_wait(&simulation->can_consume);
    size_t value = 0;
    queue_dequeue(&simulation->queue, &value);
    printf("\tConsuming %zu\n", value);
    usleep(1000 * random_between(simulation->consumer_min_delay
      , simulation->consumer_max_delay));
        is_there_pending_work_consume(simulation, &is_there_pending_work);
  }

  return NULL;
}

  //  procedure is_there_pending_work_consume0(ptr_is_there_pending_work):
void is_there_pending_work_consume(simulation_t* simulation
    , bool* ptr_is_there_pending_work) {
  //  lock(can_access_consumed_count)
  pthread_mutex_lock(&simulation->can_access_consumed_count);
    //  *ptr_is_there_pending_work = consumed_count < unit_count
    *ptr_is_there_pending_work = simulation->consumed_count
      < simulation->unit_count;
    //  if ptr_is_there_pending_work then
    if (*ptr_is_there_pending_work) {
      //  consumed_count := consumed_count + 1
      ++simulation->consumed_count;
      //  end if
    }
  pthread_mutex_unlock(&simulation->can_access_consumed_count);
    //  unlock(can_access_consumed_count)
}
  //  end procedure
