/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/
#ifndef BUFFER_H
#define BUFFER_H

  //  #include <assert.h>
#include <errno.h>
#include "goldbach_sums.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t readData(goldbach_sums_t*);

#endif