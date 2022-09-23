/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#ifndef PARALLELISM_H
#define PARALLELISM_H

#include "goldbach_sums.h"

/**
 * @brief Create threads of execution for a subroutine
 * 
 * @param subroutine Subroutine where you want to implement the threads
 * @param threads_number number of threads
 * @param data Data for subrutine
 * @return pthread_t* Threads of subroutine
 */
pthread_t* create_threads(void*(*subroutine)(void*)
    , uint64_t threads_number, void* data);

/**
 * @brief Wait for execution threads
 * 
 * @param threads Structure containing threads
 * @return uint64_t An error code:
 * 0 for success
 * != 0 thread join error
 */
uint64_t join_threads(pthread_t* threads, uint64_t threads_number);

#endif
