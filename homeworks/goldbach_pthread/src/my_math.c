/*
 *Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
 */

#include "my_math.h"

/**
 * @brief Struct containing prime number array, count and capacity of array
 *
 */
struct tools {
  uint64_t *array_prime_number;
  uint64_t count;
  uint64_t capacity;
};

/**
 * @brief Find and save all prime numbers from 0 to a number
 *
 * @param basic_tools Struct containing prime number array
 * @param struct_number Struct containing number
 */
void numPrimos(struct tools *basic_tools, number_t *struct_number);

/**
 * @brief Find goldbach sums and save in array sums
 *
 * @param basic_tools Struct containing prime number array
 * @param struct_number Struct containing the base number and vector of sums
 * @return An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t combinations(struct tools *basic_tools, number_t *struct_number);

/**
 * @brief Secundary function for storing combinations for even numbers
 * 
 * @param basic_tools Struct containing prime number array
 * @param struct_number Struct containing the base number and vector of sums
 * @param number number to be reviewed
 * @return uint64_t An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t combination_of_even_numbers
  (struct tools* basic_tools, number_t* struct_number, uint64_t number);

/**
 * @brief Secundary function for storing combinations for odd numbers
 * 
 * @param basic_tools Struct containing prime number array
 * @param struct_number Struct containing the base number and vector of sums
 * @param number number to be reviewed
 * @return uint64_t An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t combination_of_odd_numbers
  (struct tools* basic_tools, number_t* struct_number, uint64_t number);

//  function solve(my_goldbach_sums)
void* solve(void* data) {
  goldbach_sums_t* my_goldbach_sums = (goldbach_sums_t*)data;
  uint64_t error = EXIT_SUCCESS;
  uint64_t my_solution = 0;
  struct tools basic_tools;
  //  while (true)
  while (true) {
      //  tools->count := 0
    basic_tools.count = 0;
      //  lock(my_goldbach_sums->can_access_solution_count)
    pthread_mutex_lock(&my_goldbach_sums->can_access_solution_count);
        // if(my_goldbach_sums->solution_count < my_goldbach_sums->count)
      if (my_goldbach_sums->solution_count < my_goldbach_sums->count) {
          //  define my_solution := my_goldbach_sums->solution_count
          //  my_goldbach_sums->solution_count :=
          //  my_goldbach_sums->solution_count + 1
          my_solution = my_goldbach_sums->solution_count++;
      } else {
          //  unlock(my_goldbach_sums->can_access_solution_count)
        pthread_mutex_unlock(&my_goldbach_sums->can_access_solution_count);
          //   break while
        break;
      }
      //  unlock(my_goldbach_sums->can_access_solution_count)
    pthread_mutex_unlock(&my_goldbach_sums->can_access_solution_count);
      //  number_t := my_goldbach_sums->numbers[my_solution]
    number_t *struct_number = &my_goldbach_sums->numbers[my_solution];
    uint64_t number = struct_number->number < 0 ?
      struct_number->number * -1 : struct_number->number;
    basic_tools.capacity = number / (10 / 4) + 1;
    basic_tools.array_prime_number = (uint64_t *)
        malloc(basic_tools.capacity * sizeof(uint64_t));
    if (basic_tools.array_prime_number != NULL) {
      //  tools->array_prime_number := get prime numbers form number_t->number
      numPrimos(&basic_tools, struct_number);
      //  combinations(number_t)
      error = combinations(&basic_tools, struct_number);
      free(basic_tools.array_prime_number);
    } else {
      fprintf(stderr, "Error: No work space\n");
      error = 31;
      break;
    }
  }
  return (void*)error;
}

void numPrimos(struct tools *basic_tools, number_t *struct_number) {
  bool is_prime = true;
  uint64_t number = struct_number->number < 0 ?
    struct_number->number * -1 : struct_number->number;
    //  Check if prime number contains a multiple
  for (uint64_t prime_number = 2; prime_number < number; ++prime_number) {
    is_prime = true;
    for (uint64_t i = 2; i < prime_number / 2 + 1 && is_prime; ++i) {
      if (prime_number % i == 0) {
        is_prime = false;
      }
    }
    if (is_prime) {
      basic_tools->array_prime_number[basic_tools->count++] = prime_number;
    }
  }
}

//  function combinations(number_t)
uint64_t combinations(struct tools *basic_tools, number_t *struct_number) {
  uint64_t error = EXIT_SUCCESS;
  uint64_t number = struct_number->number < 0 ?
    struct_number->number * -1 : struct_number->number;
  //  if (my_number_t->number is even)
  if (number % 2 == 0) {
    error = combination_of_even_numbers(basic_tools, struct_number, number);
  } else {
    error = combination_of_odd_numbers(basic_tools, struct_number, number);
  }
  return error;
}

uint64_t combination_of_even_numbers
  (struct tools* basic_tools, number_t* struct_number, uint64_t number) {
  uint64_t error = EXIT_SUCCESS;
  //  for(i = 0 to tools->count)
  for (uint64_t i = 0; i < basic_tools->count && error == EXIT_SUCCESS; ++i) {
    //  for(j = i to tools->count)
    for (uint64_t j = i; j < basic_tools->count
      && error == EXIT_SUCCESS; ++j) {
      //  if my_number_t->number = tools->array_prime_number[i]
      //  + tools->array_prime_number[j] save sums numbers
      if (number == basic_tools->array_prime_number[i]
        + basic_tools->array_prime_number[j]) {
        //  if my_number_t->number is negative_t save sums
        if (struct_number->number > 3 && struct_number->number != 5) {
          ++struct_number->sums[0];
        } else {
          if (struct_number->sum_count >= struct_number->capacity - 3) {
            error = resize_sums(struct_number);
          }
          if (error == EXIT_SUCCESS) {
            struct_number->sums[struct_number->sum_count++]
            = basic_tools->array_prime_number[i];
            struct_number->sums[struct_number->sum_count++]
            = basic_tools->array_prime_number[j];
          }
        }
      }
    }
  }
  return error;
}

uint64_t combination_of_odd_numbers
  (struct tools* basic_tools, number_t* struct_number, uint64_t number) {
  uint64_t error = EXIT_SUCCESS;
  //  for(i = 0 to tools->count)
  for (uint64_t i = 0; i < basic_tools->count
  && error == EXIT_SUCCESS; ++i) {
    //  for(j = i to tools->count)
    for (uint64_t j = i; j < basic_tools->count
      && error == EXIT_SUCCESS; ++j) {
      //  for(h = j to tools->count)
      for (uint64_t h = j; h < basic_tools->count
      && error == EXIT_SUCCESS; ++h) {
        //  if my_number_t->number = tools->array_prime_number[i]
        //  + tools->array_prime_number[j] save sums numbers
        if (number == (basic_tools->array_prime_number[i]
          + basic_tools->array_prime_number[j]
            + basic_tools->array_prime_number[h])) {
          //  if my_number_t->number is negative_t save sums
          if (struct_number->number >= 0) {
            ++struct_number->sums[0];
          } else {
            if (struct_number->sum_count >= struct_number->capacity - 4) {
              error = resize_sums(struct_number);
            }
            if (error == EXIT_SUCCESS) {
              struct_number->sums[struct_number->sum_count++]
                = basic_tools->array_prime_number[i];
              struct_number->sums[struct_number->sum_count++]
                = basic_tools->array_prime_number[j];
              struct_number->sums[struct_number->sum_count++]
                = basic_tools->array_prime_number[h];
            }
          }
        }
      }
    }
  }
  return error;
}
