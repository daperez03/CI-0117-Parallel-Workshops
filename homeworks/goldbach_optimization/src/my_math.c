/*
 *Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
 */

#include <assert.h>
#include "my_math.h"

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

/**
 * @brief Secundary function for storing combinations for even numbers
 * 
 * @param struct_number Struct containing the base number and vector of sums
 * @param number number to be reviewed
 * @return uint64_t An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t combination_of_even_numbers
  (number_t* struct_number, uint64_t number);

/**
 * @brief Secundary function for storing combinations for odd numbers
 * 
 * @param struct_number Struct containing the base number and vector of sums
 * @param number number to be reviewed
 * @return uint64_t An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t combination_of_odd_numbers
  (number_t* struct_number, uint64_t number);

/**
 * @brief Find goldbach sums whith bits array
 * 
 * @param struct_number Struct containing the base number and vector of sums
 * @param primes_numbers Pointer to struct with the bits array
 * @return uint64_t An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t fast_combinations
  (number_t * struct_number, bits_array_t* primes_numbers);

/**
 * @brief Secundary function for storing combinations for even numbers whith bits array
 * 
 * @param struct_number Struct containing the base number and vector of sums
 * @param number Evaluated number
 * @param primes_numbers Pointer to struct with the bits array
 * @return uint64_t An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t fast_combination_of_even_numbers
  (number_t* struct_number, uint64_t number, bits_array_t* primes_numbers);

/**
 * @brief Secundary function for storing combinations for odd numbers whith bits array
 * 
 * @param struct_number Struct containing the base number and vector of sums
 * @param number Evaluated number
 * @param primes_numbers Pointer to struct with the bits array
 * @return uint64_t An error code:
 * 0 for succes
 * =! 0 error by function resize_sums
 */
uint64_t fast_combination_of_odd_numbers
  (number_t* struct_number, uint64_t number, bits_array_t* primes_numbers);

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

//  function solve(my_goldbach_sums)
void* solve(void* data) {
  goldbach_sums_t* my_goldbach_sums = (goldbach_sums_t*)data;
  uint64_t error = EXIT_SUCCESS;
  uint64_t my_solution = 0;
  //  while (true)
  while (true) {
      //  tools->count := 0
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
    number_t* struct_number = &my_goldbach_sums->numbers[my_solution];
    //  combinations(number_t)
    error = (my_goldbach_sums->prime_numbers == NULL
      && my_goldbach_sums->prime_numbers->array == NULL) ?
    combinations(struct_number):
    fast_combinations(struct_number
      , my_goldbach_sums->prime_numbers);
  }
  return (void*)error;
}

void set_prime_numbers(bits_array_t* primes_numbers) {
  assert(primes_numbers);
  assert(primes_numbers->array);
  set_bit(primes_numbers, 2);
  set_bit(primes_numbers, 3);
  set_bit(primes_numbers, 5);
  set_bit(primes_numbers, 7);
  for (size_t number = 11; number < primes_numbers->count;
    number += (number % 10 == 3) ? 4 : 2) {
    if (is_prime(number)) {
      set_bit(primes_numbers, number);
    }
  }
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
uint64_t combinations(number_t* struct_number) {
  uint64_t error = EXIT_SUCCESS;
  uint64_t number = struct_number->number < 0 ?
    struct_number->number * -1 : struct_number->number;
  //  if (my_number_t->number is even)
  if (number % 2 == 0) {
    error = combination_of_even_numbers(struct_number, number);
  } else {
    error = combination_of_odd_numbers(struct_number, number);
  }
  return error;
}

uint64_t fast_combinations
  (number_t * struct_number, bits_array_t* primes_numbers) {
  uint64_t error = EXIT_SUCCESS;
  uint64_t number = struct_number->number < 0 ?
    struct_number->number * -1 : struct_number->number;
  //  if (my_number_t->number is even)
  if (number % 2 == 0) {
    error = fast_combination_of_even_numbers
      (struct_number, number, primes_numbers);
  } else {
    error = fast_combination_of_odd_numbers
      (struct_number, number, primes_numbers);
  }
  return error;
}

uint64_t combination_of_even_numbers
  (number_t* struct_number, uint64_t number) {
  uint64_t error = EXIT_SUCCESS;
  // for (i = 0 to number_t->number/2)
  for (size_t i = 2; i <= number/2; i +=
    (i <= 10) ? 1 : (i % 10 == 3) ? 4 : 2) {
    // define complement = number_t->number - i
    uint64_t complement = number - i;
    // if (is_prime(i) && is_prime(complement)) save sums numbers
    if (is_prime(i) && is_prime(complement)) {
      error = save_goldbach_sums(struct_number, i, complement, 0);
    }
  }
  return error;
}

uint64_t combination_of_odd_numbers
  (number_t* struct_number, uint64_t number) {
  uint64_t error = EXIT_SUCCESS;
  // for (i = 0 to number_t->number/2)
  for (size_t i = 2; i <= number/2; i +=
    (i <= 10) ? 1 : (i%10 == 3) ? 4 : 2) {
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
          error = save_goldbach_sums(struct_number, i, j, complement);
        }
      }
    }
  }
  return error;
}

uint64_t fast_combination_of_even_numbers
  (number_t* struct_number, uint64_t number, bits_array_t* primes_numbers) {
  uint64_t error = EXIT_SUCCESS;
  // for (i = 0 to number_t->number/2)
  for (size_t i = 2; i <= number/2; i +=
    (i <= 10) ? 1 : (i % 10 == 3) ? 4 : 2) {
    // define complement = number_t->number - i
    uint64_t complement = number - i;
    // if (is_prime(i) && is_prime(complement)) save sums numbers
    if (test_bit(primes_numbers, i) && test_bit(primes_numbers, complement)) {
      error = save_goldbach_sums(struct_number, i, complement, 0);
    }
  }
  return error;
}

uint64_t fast_combination_of_odd_numbers
  (number_t* struct_number, uint64_t number, bits_array_t* primes_numbers) {
  uint64_t error = EXIT_SUCCESS;
  // for (i = 0 to number_t->number/2)
  for (size_t i = 2; i <= number/2; i +=
    (i <= 10) ? 1 : (i%10 == 3) ? 4 : 2) {
    if (test_bit(primes_numbers, i)) {
      // for (j = i to number_t->number/2)
      for (size_t j = i; j <= number/2; j +=
        (j <= 10) ? 1 : (j%10 == 3) ? 4 : 2) {
        // if (is_prime(i) && is_prime(j) && is_prime(complement)
          // && complement >= i && complement >= j) save sums numbers
        uint64_t complement = number - (i+j);
        if (test_bit(primes_numbers, j) && test_bit(primes_numbers, complement)
          && complement >= i && complement >= j) {
          error = save_goldbach_sums(struct_number, i, j, complement);
        }
      }
    }
  }
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

