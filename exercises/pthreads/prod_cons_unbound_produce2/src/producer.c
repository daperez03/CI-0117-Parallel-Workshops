// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <errno.h>
#include <stdio.h>
#include "common.h"
#include "producer.h"

  //  procedure produce2:
void* produce(void* data) {
  // const private_data_t* private_data = (private_data_t*)data;
  simulation_t* simulation = (simulation_t*)data;
    //  while true do
  while (true) {
      //  declare my_unit = 0
    size_t my_unit = 0;
      //  lock(can_access_next_unit)
    pthread_mutex_lock(&simulation->can_access_next_unit);
      errno = 0;
      sem_trywait(&simulation->production_sem);
        //  if next_unit < unit_count then
      if (errno != EAGAIN) {
          //  next_unit := next_unit + 1
          //  my_unit := next_unit
        my_unit = ++simulation->next_unit;
      } else {
          //  unlock(can_access_next_unit)
        pthread_mutex_unlock(&simulation->can_access_next_unit);
          //  break while
        break;
      }
      //  unlock(can_access_next_unit)
    pthread_mutex_unlock(&simulation->can_access_next_unit);
      //  delay(random_between(producer_min_delay, producer_max_delay))
    usleep(1000 * random_between(simulation->producer_min_delay
      , simulation->producer_max_delay));
      //  lock(can_access_queue)
      //  enqueue(queue, my_unit)
    queue_enqueue(&simulation->queue, my_unit);
      //  unlock(can_access_queue)
      //  print("Produced ", my_unit)
    printf("Produced %zu\n", my_unit);
      //  signal(can_consume)
      sem_post(&simulation->can_consume);
  }
  return NULL;
}

