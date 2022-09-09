/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#ifndef MY_MATH_H
#define MY_MATH_H

//#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "goldbach_sums.h"
#include <math.h>

struct tools;

uint64_t solve(goldbach_sums_t*);
bool is_even(uint64_t);


#endif