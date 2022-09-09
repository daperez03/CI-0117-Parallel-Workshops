#include "buffer.h"

uint64_t readData(goldbach_sums_t* my_goldbach_sums){
  uint64_t error = EXIT_SUCCESS;
  int64_t number_read = 0;
  uint64_t scanner_status = 1;
  while (scanner_status == 1) {  //  falta validar numero
    errno = 0;
    scanner_status = fscanf(stdin, "%" SCNi64, &number_read);
    if(scanner_status == 1 && !errno){
      if(my_goldbach_sums->count == my_goldbach_sums->capacity){
        error = resize(my_goldbach_sums);
      }
      if (error == EXIT_SUCCESS) {
        if(number_read >= 0){
          error = save_data(&my_goldbach_sums->numbers[my_goldbach_sums->count],
            number_read, positive_t, 1);
        } else {
          error = save_data(&my_goldbach_sums->numbers[my_goldbach_sums->count],
            number_read, negative_t, 24);
        } 
      }
    } else if(errno || scanner_status != 1) {
      fprintf(stderr,"Error: invalid input\n");
      error = 21;
      scanner_status = 0;
    }
  }
  return error;
}

uint64_t save_data(number_t* number, uint16_t number_read, enum resolt_t resolt, uint16_t capacity) {
  uint64_t error = EXIT_SUCCESS;
  number->number = number_read;
  number->result = resolt;
  number->capacity = capacity;
  number->sum_count = 0;
  number->sums = (uint64_t*)calloc(capacity, sizeof(uint64_t));
  if (number->sums == NULL) {
    error = 22;
    fprintf(stderr, "Error: could not create array of sums\n");
  }
  return error;
}