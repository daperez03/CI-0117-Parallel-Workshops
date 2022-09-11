#include "buffer.h"


uint64_t save_data(number_t*, int64_t, uint64_t);



uint64_t readData(goldbach_sums_t* my_goldbach_sums){
  uint64_t error = EXIT_SUCCESS;
  int64_t number_read = 0;
  int64_t scanner_status = 1;
  errno = 0;
  while (scanner_status != EOF) {
    scanner_status = scanf("%" SCNd64, &number_read);
    if (!errno && scanner_status == 1) {
      if(my_goldbach_sums->count == my_goldbach_sums->capacity - 1){
        error = resize_numbers(my_goldbach_sums);
      }
      if (error == EXIT_SUCCESS) {
        if(number_read > 3){
          error = save_data(&my_goldbach_sums->numbers[my_goldbach_sums->count++],
            number_read, 1);
        } else if(number_read < -3) {
          error = save_data(&my_goldbach_sums->numbers[my_goldbach_sums->count++],
            number_read, 30);
        } else {          
          error = save_data(&my_goldbach_sums->numbers[my_goldbach_sums->count++],
            number_read, 0);
        }
        
      }
    } else if(scanner_status == 0 || errno) {
      fprintf(stderr,"Error: invalid input\n");
      error = 21;
      break;
    }
  }
  return error;
}

uint64_t save_data(number_t* struct_number, int64_t number_read, uint64_t capacity) {
  uint64_t error = EXIT_SUCCESS;
  struct_number->number = number_read;
  struct_number->capacity = capacity;
  struct_number->sum_count = 0;
  if(capacity){
    struct_number->sums = (uint64_t*)calloc(capacity, sizeof(uint64_t));
  }
  return error;
}