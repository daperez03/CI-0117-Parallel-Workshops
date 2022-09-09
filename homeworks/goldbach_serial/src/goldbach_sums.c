#include "goldbach_sums.h"
#include "my_math.h"

uint64_t init(goldbach_sums_t* my_goldbach_sums) {
  uint64_t error = EXIT_SUCCESS;
  my_goldbach_sums->capacity = 10;
  my_goldbach_sums->count = 0;
  my_goldbach_sums->numbers = (number_t*)calloc(10, sizeof(number_t));
  if (my_goldbach_sums->numbers == NULL) {
    fprintf(stderr, "Error: no number vector could be created\n");
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
    fprintf(stderr, "Error: cloud not resize the number vector\n");
    error = 12;
  }
  return error;
}

void resume(goldbach_sums_t* my_goldbach_sums) {
  uint64_t sums = 0;
  for (uint64_t i = 0; my_goldbach_sums->count; ++i) {
    if(my_goldbach_sums->numbers[i].result == positive_t){
      sums += my_goldbach_sums->numbers[i].sums[0]; 
    }else 
    if (my_goldbach_sums->numbers[i].result == negative_t) {
      if (is_even(my_goldbach_sums->numbers[i].number)) {
        sums += my_goldbach_sums->numbers[i].sum_count / 2;
      } else {
        sums += my_goldbach_sums->numbers[i].sum_count / 3;
      }
    }
  }
  printf("Total: %" SCNu64 " numbers %" SCNu64 "sums\n", my_goldbach_sums->count, sums);
  for (uint64_t i = 0; i < my_goldbach_sums->count; ++i) {
    if (my_goldbach_sums->numbers[i].result == negative_t) {
      uint64_t div = is_even(my_goldbach_sums->numbers[i].number)? 2 : 3;
      printf("-%" SCNu64 ": %" SCNu64 " sums: ",
        my_goldbach_sums->numbers[i].number,
          my_goldbach_sums->numbers[i].sum_count/div);
        if(is_even(my_goldbach_sums->numbers[i].number)){
          for(uint64_t j = 0; j < my_goldbach_sums->numbers[i].sum_count; j){
              printf("%" SCNu64 " + %" SCNu64
                , my_goldbach_sums->numbers[i].sums[j++]
                  , my_goldbach_sums->numbers[i].sums[j++]);
            if (j != my_goldbach_sums->numbers[i].sum_count - 2) {
              printf(", ");
            } else {
              printf("\n ");
            }
          }
        } else {
          for(uint64_t j = 0; j < my_goldbach_sums->numbers[i].sum_count; j){
            printf("%" SCNu64 " + %" SCNu64 " + %" SCNu64
                , my_goldbach_sums->numbers[i].sums[j++]
                  , my_goldbach_sums->numbers[i].sums[j++]
                    , my_goldbach_sums->numbers[i].sums[j++]);
            if (j != my_goldbach_sums->numbers[i].sum_count - 3) {
              printf(", ");
            } else {
              printf("\n ");
            }
          }
        }
    } else if(my_goldbach_sums->numbers[i].result == positive_t) {
      printf("%" SCNu64 ": %" SCNu64 " sums\n",
        my_goldbach_sums->numbers[i].number,
          my_goldbach_sums->numbers[i].sums[0]);
    } else {
      printf("%" SCNu64 ": NA", my_goldbach_sums->numbers[i].number);
    }

  }
}

void destroy(goldbach_sums_t* my_goldbach_sums) {
  for (u_int64_t i = 0; i < my_goldbach_sums->count; ++i) {
    free(my_goldbach_sums->numbers->sums);
  }
  free(my_goldbach_sums->numbers);
}

