/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#include "buffer.h"

/**
 * @brief Stores numbers in the arrray of number_t
 * @details This function is responsible for saving the indicated
 * number and initialising array of sums
 * @param struct_number Array in which you want to save the number
 * @param number_read Number to keep
 * @param capacity Capacity for goldbach sums
 * @return An error code:
 * 0 for success.
 * 22 invalid create data
 */
uint64_t save_data(number_t* struct_number,
  int64_t number_read, uint64_t capacity);
  //  function readData(my_goldbach_sums)
uint64_t read_data(goldbach_sums_t* my_goldbach_sums, size_t* max) {
  uint64_t error = EXIT_SUCCESS;
  int64_t number_read = 0;
  int64_t scanner_status = 1;
  errno = 0;
    //  while not end stdin
  while (scanner_status != EOF) {
      //  my_goldbach_sums->numbers[my_goldbach_sums->count]->number
      //  := read(stdin)
      //  stdin>nextLine
    scanner_status = scanf("%" SCNd64, &number_read);
    if (!errno && scanner_status == 1) {
      if (my_goldbach_sums->count == my_goldbach_sums->capacity - 1) {
        error = resize_numbers(my_goldbach_sums);
      }
      if (error == EXIT_SUCCESS) {
        if (number_read > 3) {
            //  my_goldbach_sums->count := my_goldbach_sums->count + 1
          error = save_data(&my_goldbach_sums->numbers
            [my_goldbach_sums->count++], number_read, 1);
        } else if (number_read < -3) {
            //  my_goldbach_sums->count := my_goldbach_sums->count + 1
          error = save_data(&my_goldbach_sums->numbers
            [my_goldbach_sums->count++], number_read, (number_read*-1)/2);
        } else {
            //  my_goldbach_sums->count := my_goldbach_sums->count + 1
          error = save_data(&my_goldbach_sums->numbers
            [my_goldbach_sums->count++], number_read, 0);
        }
        if(((number_read >= 0)? (number_read) : (number_read*-1)) > (int64_t)*max){
          *max = (size_t)(number_read > 0? (number_read) : (number_read*-1));
        }
      }
    } else if (scanner_status == 0 || errno) {
      fprintf(stderr, "Error: invalid input\n");
      error = 21;
      break;
    }
  }
  return error;
}

uint64_t save_data(number_t* struct_number,
  int64_t number_read, uint64_t capacity) {
  uint64_t error = EXIT_SUCCESS;
  struct_number->number = number_read;
  struct_number->capacity = capacity;
  struct_number->sum_count = 0;
  if (capacity) {
    struct_number->sums = (uint64_t*)calloc(capacity, sizeof(uint64_t));
    if (struct_number->sums == NULL) {
      fprintf(stderr, "Error: invalid create array\n");
      error = 22;
    }
  } else {
    struct_number->sums = NULL;
  }
  return error;
}
