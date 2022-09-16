// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdio.h>

#include "common.h"
#include "producer.h"

void is_there_pending_work(simulation_t* simulation, size_t* ptr_my_unit, bool* ptr_is_there_pending_work);

void* produce(void* data) {
  // const private_data_t* private_data = (private_data_t*)data;
  simulation_t* simulation = (simulation_t*)data;
  size_t my_unit = 0;
  bool bool_is_there_pending_work = false;
  is_there_pending_work(simulation, &my_unit, &bool_is_there_pending_work);
  while (bool_is_there_pending_work) {
      //  lock(can_access_next_unit)
    usleep(1000 * random_between(simulation->producer_min_delay
      , simulation->producer_max_delay));
    queue_enqueue(&simulation->queue, my_unit);
    printf("Produced %zu\n", my_unit);

      //  signal(can_consume)
      sem_post(&simulation->can_consume);
      is_there_pending_work(simulation, &my_unit, &bool_is_there_pending_work);
  }

  return NULL;
}

  // procedure is_there_pending_work(ptr_my_unit, ptr_is_there_pending_work){
void is_there_pending_work(simulation_t* simulation, size_t* ptr_my_unit, bool* ptr_is_there_pending_work) {
  //  lock(can_access_next_unit)
  pthread_mutex_lock(&simulation->can_access_next_unit);
    //  ptr_is_there_pending_work := next_unit < unit_count
    *ptr_is_there_pending_work = simulation->next_unit < simulation->unit_count;
    //  if ptr_is_there_pending_work then
    if (*ptr_is_there_pending_work) {
      //  next_unit := next_unit + 1
      ++simulation->next_unit;
      //  ptr_my_unit := next_unit
      *ptr_my_unit = simulation->next_unit;
    }
    //  end if
    //  unlock(can_access_next_unit)
  pthread_mutex_unlock(&simulation->can_access_next_unit);
}
