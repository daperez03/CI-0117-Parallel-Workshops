/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#ifndef GOLDBACH_SUMS_H
#define GOLDBACH_SUMS_H

//#include <assert.h>
#include <inttypes.h>
#include <math.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum resolt_t{negative_t, positive_t, error_t};

typedef struct number{
  uint64_t number;
  enum resolt_t result;
  uint64_t capacity;
  uint64_t sum_count;
  uint64_t* sums;
}number_t;

typedef struct goldbach_sums {
  uint64_t capacity;
  uint64_t count;
  number_t* numbers;
}goldbach_sums_t;

uint64_t init(goldbach_sums_t* my_goldbach_sums);
uint64_t resize(goldbach_sums_t* my_goldbach_sums);
void resume(goldbach_sums_t* my_goldbach_sums);
void destroy(goldbach_sums_t* my_goldbach_sums);

#endif