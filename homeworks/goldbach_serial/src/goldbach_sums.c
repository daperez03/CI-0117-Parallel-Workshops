#include "goldbach_sums.h"
#include "my_math.h"

uint64_t init(goldbach_sums_t* my_goldbach_sums) {
  uint64_t error = EXIT_SUCCESS;
  my_goldbach_sums->capacity = 10;
  my_goldbach_sums->count = 0;
  my_goldbach_sums->numbers = (number_t*)calloc(10, sizeof(number_t));
  if (my_goldbach_sums->numbers == NULL) {
    fprintf(stderr, "Error: no struct_number vector could be created\n");
    error = 11;
  }
  return error;
}

uint64_t resize(goldbach_sums_t* my_goldbach_sums) {
  uint64_t error = EXIT_SUCCESS;
  my_goldbach_sums->capacity += 10;
  my_goldbach_sums->numbers = 
    (number_t*)realloc(my_goldbach_sums->numbers, 
      my_goldbach_sums->capacity *  sizeof(my_goldbach_sums));
  if (my_goldbach_sums->numbers == NULL) {
    fprintf(stderr, "Error: cloud not resize the struct_number vector\n");
    error = 12;
  }
  return error;
}

void result(goldbach_sums_t* my_goldbach_sums) {
  uint64_t sums = 0;
  number_t* struct_number = NULL;
  for (uint64_t i = 0; my_goldbach_sums->count; ++i) {
    struct_number = &my_goldbach_sums->numbers[i]; 
    if(struct_number->result == positive_t){
      sums += struct_number->sums[0]; 
    }else 
    if (struct_number->result == negative_t) {
      if (is_even(struct_number->number)) {
        sums += struct_number->sum_count / 2;
      } else {
        sums += struct_number->sum_count / 3;
      }
    }
  }
  printf("Total: %" SCNu64 " numbers %" SCNu64 "sums\n", my_goldbach_sums->count, sums);
  for (uint64_t i = 0; i < my_goldbach_sums->count; ++i) {
    struct_number = &my_goldbach_sums->numbers[i];
    if (struct_number->result == negative_t) {
      uint64_t div = is_even(struct_number->number)? 2 : 3;
        if(is_even(struct_number->number)){
          print();
        } else {
          print();
        }
    } else if(struct_number->result == positive_t) {
      print(struct_number->number, struct_number->sums[0], 0, NULL, false);
    } else {
      print(struct_number->number, 0, 0, NULL, true);
    }
  }
}

void print(int64_t number, uint64_t sums_count, uint64_t number_of_sums, uint64_t* sums, bool is_NA) {
  if (is_NA) {
    printf("%" SCNu64 ": NA\n", number);
  }else{
    printf("%" SCNi64 ": %" SCNu64 " sums ",number, sums_count);
    for (uint64_t i = 0; i < sums_count; i++) {
      printf(": ");
      for (uint64_t j = 0; j < number_of_sums; j++){    
        printf("%" SCNu64, sums[i * j]);
        j != number_of_sums - 1 ? printf(" + "): NULL;
      }
      i != sums_count - 1 ? printf(", "): NULL; 
    }
    printf("\n");
  }
}

void destroy(goldbach_sums_t* my_goldbach_sums) {
  for (uint64_t i = 0; i < my_goldbach_sums->count; ++i) {
    free(my_goldbach_sums->numbers->sums);
  }
  free(my_goldbach_sums->numbers);
}

