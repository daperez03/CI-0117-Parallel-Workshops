/*
 *Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
 */

#include <assert.h>
#include "my_math.h"

#define is_error(x) x != EXIT_SUCCESS

/**
 * @brief Check if a number is prime
 * 
 * @param number Number to be verified
 * @return If is prime return true
 * @return If not is prime return false
 */
bool is_prime(uint64_t number);

/**
 * @brief Find goldbach sums
 * 
 * @param struct_number Struct containing the base number and vector of sums
 * @return An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t combinations(number_t *struct_number);

/// @brief Secundary function for storing combinations for even numbers
/// @param struct_number Struct containing the base number and vector of sums
/// @param number number to be reviewed
/// @param thread_count Number of threads
/// @return error code
uint64_t combination_of_even_numbers
  (number_t* struct_number, uint64_t number, const size_t thread_count);

/// @brief Secundary function for storing combinations for odd numbers
/// @param struct_number Struct containing the base number and vector of sums
/// @param number number to be reviewed
/// @param thread_count Number of threads
/// @return uint64_t An error code:
/// 0 for succes
/// =! 0 error by function resize_sums
uint64_t combination_of_odd_numbers
  (number_t* struct_number, uint64_t number, const size_t thread_count);

/**
 * @brief Save one sums of Goldbach in struct_number
 * 
 * @param struct_number Struct containing the base number and vector of sums
 * @param number1 Firt number
 * @param number2 Second number
 * @param number3 Third number (if is even number3 = 0)
 * @return uint64_t An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t save_goldbach_sums(number_t* struct_number
  , uint64_t number1, uint64_t number2, uint64_t number3);

uint64_t regular_solution(goldbach_sums_t* my_goldbach_sums
  , size_t threads_number) {
  uint64_t error = EXIT_SUCCESS;
  uint64_t my_solution = 0;
  while (true) {
    if (my_goldbach_sums->solution_count++ >= my_goldbach_sums->count) break;
    number_t* struct_number =
      &my_goldbach_sums->numbers[my_solution++];
    // int64_t number = struct_number->number;
    error = init_number_t(struct_number);
    error = solve(struct_number, threads_number);
  }
  return error;
}

// Extracted from https://en.wikipedia.org/wiki/Primality_test
bool is_prime(uint64_t number) {
  if (number == 2 || number == 3)
      return true;

  if (number <= 1 || number % 2 == 0 || number % 3 == 0)
    return false;

  for (size_t i = 5; i * i <= number; i += 6) {
    if (number % i == 0 || number % (i + 2) == 0)
    return false;
  }
  return true;
}

// function combinations(number_t)
uint64_t solve(number_t* struct_number, const size_t threads_number) {
  uint64_t error = EXIT_SUCCESS;
  uint64_t number = struct_number->number < 0 ?
    struct_number->number * -1 : struct_number->number;
  //  if (my_number_t->number is even)
  if (number % 2 == 0) {
    error = combination_of_even_numbers(struct_number, number, threads_number);
  } else {
    error = combination_of_odd_numbers(struct_number, number, threads_number);
  }
  return error;
}

uint64_t combination_of_even_numbers
  (number_t* struct_number, uint64_t number, const size_t thread_count) {
  uint64_t error = EXIT_SUCCESS;
  // for (i = 0 to number_t->number/2)
  number_t* parallel_number = (number_t*)
    malloc(thread_count * sizeof(number_t));
  if (parallel_number == NULL) {
    fprintf(stderr, "Error: cloud si not enough memory\n");
    error = EXIT_FAILURE;
    return error;
  }
  for (size_t i = 0; i < thread_count; ++i) {
    init_number_t(&parallel_number[i]);
    parallel_number[i].number = struct_number->number;
  }
  #pragma omp parallel for num_threads(thread_count) \
    default(none) shared(parallel_number, number) schedule(static)
  for (size_t i = 2; i <= number/2; ++i) {
    // define complement = number_t->number - i
    uint64_t complement = number - i;
    // printf("thread_number = %d and i = %ld \n", thread_number, i);
    // if (is_prime(i) && is_prime(complement)) save sums numbers
    if (is_prime(i) && is_prime(complement)) {
      save_goldbach_sums(&parallel_number[omp_get_thread_num()]
        , i, complement, 0);
    }
  }

  for (size_t i = 0; i < thread_count && !is_error(error); ++i) {
    error = append_number_t(&parallel_number[i], struct_number);
  }
  free(parallel_number);
  return error;
}

uint64_t combination_of_odd_numbers
  (number_t* struct_number, uint64_t number, const size_t thread_count) {
  uint64_t error = EXIT_SUCCESS;
  number_t* parallel_number = (number_t*)
    malloc(thread_count * sizeof(number_t));
  if (parallel_number == NULL) {
    fprintf(stderr, "Error: cloud si not enough memory\n");
    error = EXIT_FAILURE;
    return error;
  }
  for (size_t i = 0; i < thread_count; ++i) {
    init_number_t(&parallel_number[i]);
    parallel_number[i].number = struct_number->number;
  }
  // for (i = 0 to number_t->number/2)
  #pragma omp parallel for num_threads(thread_count) \
    default(none) shared(parallel_number, number) schedule(static)
  for (size_t i = 2; i <= number/2; ++i) {
    if (is_prime(i)) {
      // for (j = i to number_t->number/2)
      for (size_t j = i; j <= number/2; j+=
      (j <= 10) ? 1:(j%10 == 3) ? 4 : 2) {
        // define complement = number_t->number - i - j
        uint64_t complement = number - (i+j);
        // if (is_prime(i) && is_prime(j) && is_prime(complement)
          // && complement >= i && complement >= j) save sums numbers
        if (is_prime(j) && is_prime(complement)
          && complement >= i && complement >= j) {
          save_goldbach_sums(&parallel_number[omp_get_thread_num()]
            , i, j, complement);
        }
      }
    }
  }
  for (size_t i = 0; i < thread_count && !is_error(error); ++i) {
    error = append_number_t(&parallel_number[i], struct_number);
    destroy_numbert_t(&parallel_number[i]);
  }
  free(parallel_number);
  return error;
}

uint64_t save_goldbach_sums(number_t* struct_number
  , uint64_t number1, uint64_t number2, uint64_t number3) {
  uint64_t error = EXIT_SUCCESS;
  //  if my_number_t->number is negative_t save sums
  if (struct_number->number >= 0) {
    ++struct_number->sums[0];
  } else {
    if (struct_number->sum_count >= struct_number->capacity - 4) {
      error = resize_sums(struct_number);
    }
    if (error == EXIT_SUCCESS) {
      struct_number->sums[struct_number->sum_count++] = number1;
      struct_number->sums[struct_number->sum_count++] = number2;
      if (number3 != 0)
        struct_number->sums[struct_number->sum_count++] = number3;
    }
  }
  return error;
}

