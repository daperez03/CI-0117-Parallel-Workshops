/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#include "parallelism.h"

  //  procedure create_threads
  //  (my_math->solve, threads_number, data)
pthread_t* create_threads(void*(*subroutine)(void*)
  , uint64_t threads_number, void* data) {
  pthread_t* threads = (pthread_t*)
    calloc(threads_number, sizeof(pthread_t));
  if (threads) {
      //  for (define threads_count := 0 to threads_number)
    for (size_t index = 0; index < threads_number; ++index) {
        //  defien threads[] =: create_thread(subroutine, data)
      if (pthread_create(&threads[index]
        , /*attr*/ NULL, subroutine, (void*)data)
         == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "error: could not create thread %zu\n", index);
        join_threads(threads, index);
        return NULL;
      }
    }
  }
    //  return threads
  return threads;
}

  //  procedure join_threads(threads, threads_number)
uint64_t join_threads(pthread_t* threads, uint64_t threads_number) {
  uint64_t error = EXIT_SUCCESS;
  uint64_t error_thread = EXIT_SUCCESS;
    //  for (define threads_count = 0 to threads_number)
  for (size_t index = 0; index < threads_number; ++index) {
    void* data = (void*)error;
      //  join_thread(threads[threads_count])
    error_thread += pthread_join(threads[index], &data);
    if (error != (uint64_t)data) {
      error = (uint64_t)data;
    }
  }
  if (error_thread != EXIT_SUCCESS) {
    error = error_thread;
  }
  free(threads);
  threads = NULL;
  return error;
}
