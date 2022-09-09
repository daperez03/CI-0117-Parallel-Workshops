#include "buffer.h"

uint64_t readData(goldbach_sums_t* my_goldbach_sums){
  int64_t error = EXIT_SUCCESS;

  int64_t read_number = 0;
  while (feof(stdin) == 0) {  //  falta validar numero
    fscanf(stdin, "%" SCNi64, &read_number);
    if(my_goldbach_sums->count == my_goldbach_sums->capacity){
      error = resize(my_goldbach_sums);
    }
    if (error == EXIT_SUCCESS) {
      my_goldbach_sums->numbers[my_goldbach_sums->count].number = read_number;
      if(read_number >= 0){
        my_goldbach_sums->numbers[my_goldbach_sums->count].result = positive_t;
        my_goldbach_sums->numbers[my_goldbach_sums->count].capacity = 1;
        my_goldbach_sums->numbers[my_goldbach_sums->count].sum_count = 0;
        my_goldbach_sums->numbers[my_goldbach_sums->count].sums = 
          (uint64_t*)calloc(1, sizeof(uint64_t));
      } else {
        my_goldbach_sums->numbers[my_goldbach_sums->count].result = negative_t;
        my_goldbach_sums->numbers[my_goldbach_sums->count].capacity = 24;
        my_goldbach_sums->numbers[my_goldbach_sums->count].sum_count = 0;
        my_goldbach_sums->numbers[my_goldbach_sums->count].sums = 
          (uint64_t*)calloc(24, sizeof(uint64_t));
      } //  error
    }
  }

  //  ferror;
  //  errno
  return error;
}