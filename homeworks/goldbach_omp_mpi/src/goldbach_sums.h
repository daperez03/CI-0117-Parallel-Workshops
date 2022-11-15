/*
 *Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
 */

#ifndef GOLDBACH_SUMS_H
#define GOLDBACH_SUMS_H

#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Data structure of a number
 * @details Save a number with a array with
 * its goldbach sums, vector capacity, metre
 * by which the vector is found
 */
typedef struct number {
  int64_t number;
  size_t capacity;
  size_t sum_count;
  uint64_t *sums;
} number_t;

/**
 * @brief Save a vector eith the @a number structure and and concurrency data
 * @details It has a @a count variable to know what
 * vector writing position
 */
typedef struct goldbach_sums {
  size_t capacity;
  size_t count;
  number_t *numbers;
  size_t solution_count;
} goldbach_sums_t;

/**
 * @brief Initialise the strcut @a goldbach_sums_t
 *
 * @param my_goldbach_sums Pointer to struct @a goldbach_sums_t
 * @return An error code:
 * 0 for success
 * 11 for not creating numbers vector
 */
uint64_t init_goldbach_sums (goldbach_sums_t *my_goldbach_sums);

void init_number_t(number_t* number);

/**
 * @brief It modifies the capacity of the numbers vector
 *
 * @param my_goldbach_sums Structure that contains the numbers vector
 * @return An error code:
 * 0 for success
 * 12 for no new space was obtained for the vector
 */
uint64_t resize_numbers(goldbach_sums_t *my_goldbach_sums);

/**
 * @brief It modifies the capacity of the sums vector
 *
 * @param number Structure that contains the sums vector
 * @return An error code:
 * 0 for success
 * 13 for no new space was obtained for the vector
 */
uint64_t resize_sums(number_t *number);

/**
 * @brief returns the reult of the goldbach sums
 * at the standard output(stdout)
 *
 * @param my_goldbach_sums Structure that contains the goldbach sums
 */
void result(goldbach_sums_t *my_goldbach_sums);

void destroy_numbert_t (number_t* number);

/**
 * @brief Destroy the data structure used to store the goldbach sums
 *
 * @see result
 */
void destroy_goldbach_sums(goldbach_sums_t *my_goldbach_sums);

#endif
