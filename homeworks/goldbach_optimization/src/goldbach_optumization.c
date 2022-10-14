/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "buffer.h"
#include "goldbach_sums.h"
#include "my_math.h"
#include "parallelism.h"

/**
 * @brief Main funtion
 * @param argc Argument counter
 * @param argv Arguments
 * @return An error code
 */
int main(int argc, char* argv[]) {  //  function main(argv[])
  uint64_t error = EXIT_SUCCESS;
    //  create goldbach_sums_t my_goldbach_sums
  goldbach_sums_t my_goldbach_sums;
  error = init(&my_goldbach_sums);
  if (error == EXIT_SUCCESS) {
    uint64_t threads_number = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc == 2) {
        //  define threads_number := argv[1]
      if (sscanf(argv[1], "%" SCNu64, &threads_number) != 1) {
        fprintf(stderr , "Error: invalid thread count\n");
        error = 11;
      }
    }
    if (error == EXIT_SUCCESS) {
        //  buffer->read_data(my_goldbach_sums)
      error = readData(&my_goldbach_sums);
      if (error == EXIT_SUCCESS) {
        struct timespec start_time, finish_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time);
          //  threads[] = parallelism->create_threads
          //  (my_math->solve, threads_number, my_goldbach_sums)
        pthread_t* threads = create_threads
          (solve, threads_number, (void*)&my_goldbach_sums);
          //  join_threads(threads, threads_number)
        if (threads != NULL) {
          error = join_threads(threads, threads_number);
          clock_gettime(CLOCK_MONOTONIC, &finish_time);
          double block_time = finish_time.tv_sec - start_time.tv_sec +
            (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9; // Esta bien?
          fprintf(stderr, "Time: %lf\n", block_time);
          if (error == EXIT_SUCCESS) {
              //  goldbach_sums->result(my_goldbach_sums)
            result(&my_goldbach_sums);
          } else {
            fprintf(stderr , "Error: no threads were joined\n");
            error = 12;
          }
        }
      }
    }
  }
    //  goldbach_sums->destroy(my_goldbach_sums)
  destroy(&my_goldbach_sums);
  return error;
}
