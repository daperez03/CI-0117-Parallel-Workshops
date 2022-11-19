/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#ifndef MY_MATH_H
#define MY_MATH_H

  //  system header
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//  other header
#include "goldbach_sums.h"

struct tools;

/// @brief Calculate and save the goldbach sums
/// @param struct_number Structure that contains the goldbach sums
/// @param threads_number Number of threads
/// @return An error code:
/// 0 for success
/// 31 There is no space to store funtion tools
/// Errors of the functions resize_sums and resize_numbers
uint64_t solve(number_t* struct_number, const size_t threads_number);

/// @brief Generate a solution for Goldbach sums with a single process
/// @param my_goldbach_sums Goldbach number and sums container
/// @param threads_number Thread numbers
/// @return error code
uint64_t regular_solution(goldbach_sums_t* my_goldbach_sums
  , const size_t threads_number);

#endif
