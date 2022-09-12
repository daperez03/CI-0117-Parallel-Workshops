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

//  function solve(my_goldbach_sums)
uint64_t solve(goldbach_sums_t *my_goldbach_sums) {
  uint64_t error = EXIT_SUCCESS;
  struct tools basic_tools;
  //  for (i = 0 to my_goldbach_sums->count)
  for (uint64_t i = 0; i < my_goldbach_sums->count; ++i) {
    //  number_t my_number_t = my_goldbach_sums->numbers[i]
    number_t *struct_number = &my_goldbach_sums->numbers[i];
    basic_tools.count = 0;
    uint64_t number = struct_number->number < 0 ?
      struct_number->number * -1 : struct_number->number;
    basic_tools.capacity = number / (10 / 4) + 1;
    basic_tools.array_prime_number = (uint64_t *)
        malloc(basic_tools.capacity * sizeof(uint64_t));
    if (basic_tools.array_prime_number != NULL) {
      //  array_prime_number = get prime numbers form my_number_t->number
      numPrimos(&basic_tools, struct_number);
      //  combinaciones(my_number_t)
      error = combinations(&basic_tools, struct_number);
      free(basic_tools.array_prime_number);
    } else {
      fprintf(stderr, "Error: No work space\n");
      error = 31;
      break;
    }
  }
  return error;
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

//  function combinaciones(my_number_t)
uint64_t combinations(struct tools *basic_tools, number_t *struct_number) {
  uint64_t error = EXIT_SUCCESS;
  uint64_t number = struct_number->number < 0 ?
    struct_number->number * -1 : struct_number->number;
  //    if (my_number_t->number is even)
  if (number % 2 == 0) {
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
  } else {
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
  }
  return error;
}
