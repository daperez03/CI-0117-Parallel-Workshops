// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdio.h>

#include "common.h"
#include "producer.h"

void* produce(void* data) {
  privated_data_t* privated_data = (privated_data_t*) data;
  simulation_t* simulation = privated_data->data_shared;

  while (true) {
    size_t my_unit = 0;
      //  lock(can_access_next_unit)
    pthread_mutex_lock(&simulation->can_access_next_unit);
        //  if is there pending work, take a unit for producing
      if (simulation->next_unit < simulation->unit_count) {
        my_unit = ++simulation->next_unit;
      } else {
          //  unlock(can_access_next_unit)
        pthread_mutex_unlock(&simulation->can_access_next_unit);
        break;
      }
      //  unlock(can_access_next_unit)
    pthread_mutex_unlock(&simulation->can_access_next_unit);
    usleep(1000 * random_between(simulation->producer_min_delay
      , simulation->producer_max_delay));
    queue_enqueue(&simulation->queue, my_unit);
    printf("I am thread %zu of %zu and produced %zu\n"
      , privated_data->thread_number, privated_data->threads_number, my_unit);

      //  signal(can_consume)
      sem_post(&simulation->can_consume);
  }

  return NULL;
}