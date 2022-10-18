/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#ifndef BUFFER_H
#define BUFFER_H

  //  system header
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

  //  other header
#include "goldbach_sums.h"

/**
 * @brief Read numbers entered in standar input(stdin)
 * and saves them goldbach_sums
 *  
 * @exception Numbers thet generate a carry and characters
 * 
 * @param my_goldbach_sums Structure in charge of saving the
 * number entered and their goldbach sums 
 * 
 * @return An error code:
 * 0 for success.
 * 21 invalid input
 */
uint64_t read_data(goldbach_sums_t* my_goldbach_sums, uint64_t* max);

#endif
