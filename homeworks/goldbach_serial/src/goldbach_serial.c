/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#include "buffer.h"
#include "goldbach_sums.h"
#include "my_math.h"

/**
 * @brief Main funtion
 * 
 * @return An error code
 */
int main() {
  uint64_t error = EXIT_SUCCESS;
    //    create goldbach_sums_t my_goldbach_sums
  goldbach_sums_t my_goldbach_sums;
  error = init(&my_goldbach_sums);
  if (error == EXIT_SUCCESS) {
      //    Buffer->read_data(my_goldbach_sums)
    error = readData(&my_goldbach_sums);
    if (error == EXIT_SUCCESS) {
        //    my_math->solve(my_goldbach_sums)
      error = solve(&my_goldbach_sums);
      if (error == EXIT_SUCCESS) {
          //  goldbach_sums->result(my_goldbach_sums)
        result(&my_goldbach_sums);
      }
    }
  }
    //  goldbach_sums->destroy(my_goldbach_sums)
  destroy(&my_goldbach_sums);
  return error;
}
