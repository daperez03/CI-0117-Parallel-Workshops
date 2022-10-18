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

  //  other header
#include "goldbach_sums.h"
#include "bits_array.h"

struct tools;

/**
 * @brief Calculate and save the goldbach sums
 * 
 * @param data Structure that contains the goldbach sums
 * @return An error code:
 * 0 for success
 * 31 There is no space to store funtion tools
 * Errors of the functions resize_sums and resize_numbers
 */
void* solve(void* data);

void set_prime_numbers(bits_array_t* prime_numbers);

#endif
