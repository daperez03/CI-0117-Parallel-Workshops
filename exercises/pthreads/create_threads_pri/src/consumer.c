// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdbool.h>
#include <stdio.h>

#include "common.h"
#include "consumer.h"

void* consume(void* data) {
  privated_data_t* privated_data = (privated_data_t*) data;
  simulation_t* simulation = privated_data->data_shared;

  while (true) {
      //  lock(can_access_consumed_count)
    pthread_mutex_lock(&simulation->can_access_consumed_count);
      if (simulation->consumed_count < simulation->unit_count) {
          //  Reserve the next product to me
        ++simulation->consumed_count;
      } else {
          //  unlock(can_access_consumed_count)
        pthread_mutex_unlock(&simulation->can_access_consumed_count);
          //  break while
        break;
      }
      //  unlock(can_access_consumed_count)
    pthread_mutex_unlock(&simulation->can_access_consumed_count);

      //  wait(can_consume)
    sem_wait(&simulation->can_consume);

    size_t value = 0;
    queue_dequeue(&simulation->queue, &value);
    printf("\tI am thread %zu of %zu and consuming %zu\n"
      , privated_data->thread_number, privated_data->threads_number, value);
    usleep(1000 * random_between(simulation->consumer_min_delay
      , simulation->consumer_max_delay));
  }

  return NULL;
}
