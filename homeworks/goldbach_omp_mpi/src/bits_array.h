/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/
#ifndef BITS_ARRAY_H
#define BITS_ARRAY_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Contains the bits vector and its respective count
 * 
 */
typedef struct bits_array {
  // define array[]
  uint8_t* array;
  // define count;
  size_t count;
} bits_array_t;

/**
 * @brief It is responsible for initialising bits array
 * 
 * @param bits_array Pointer to struct with the bits array
 * @param capacity Capacity of array
 */
void init_array(bits_array_t* bits_array, size_t capacity);

/**
 * @brief Set the bits in the array
 * 
 * @param bits_array Pointer to struct with the bits array
 * @param index Index to place the bit
 */
void  set_bit(bits_array_t* bits_array,  uint64_t index);

/**
 * @brief Get bit in of an index
 * 
 * @param bits_array Pointer to struct with the bits array
 * @param index Index to get the bit
 * @return Bit wanted
 */
uint64_t test_bit(bits_array_t* bits_array,  uint64_t index);

#endif
