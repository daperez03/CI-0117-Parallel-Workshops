/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#include "goldbach_sums.h"

/**
 * @brief Print the goldbach sums at the standard output
 * 
 * @param number Base number
 * @param number_of_sums Number of goldbach sums
 * @param sums Pointer to array that contains the sums
 * @param is_NA Indicate not has sums
 */
void print(int64_t number, uint64_t number_of_sums
  , uint64_t* sums, bool is_NA);

uint64_t init(goldbach_sums_t* my_goldbach_sums) {
  uint64_t error = EXIT_SUCCESS;
  my_goldbach_sums->capacity = 10;
  my_goldbach_sums->count = 0;
  my_goldbach_sums->numbers = (number_t*)calloc(10, sizeof(number_t));
  if (my_goldbach_sums->numbers == NULL) {
    fprintf(stderr, "Error: not create numbers vector\n");
    error = 11;
  }
  if (pthread_mutex_init(&my_goldbach_sums->can_access_solution_count
    , NULL) != EXIT_SUCCESS) {
    fprintf(stderr, "Error: not init mutex \n");
    error = 12;
  }
  my_goldbach_sums->solution_count = 0;
  return error;
}


uint64_t resize_numbers(goldbach_sums_t* my_goldbach_sums) {
  uint64_t error = EXIT_SUCCESS;
  my_goldbach_sums->capacity += 20;
  number_t* previous_array = my_goldbach_sums->numbers;
  number_t* new_array = (number_t*)
    calloc(my_goldbach_sums->capacity, sizeof(number_t));
  if (new_array == NULL) {
    fprintf(stderr, "Error: cloud not resize the number vector\n");
    error = 12;
  } else {
    for (uint64_t i = 0; i < my_goldbach_sums->count; ++i) {
      new_array[i].capacity = my_goldbach_sums->numbers[i].capacity;
      new_array[i].number = my_goldbach_sums->numbers[i].number;
      new_array[i].sum_count = my_goldbach_sums->numbers[i].sum_count;
      new_array[i].sums = my_goldbach_sums->numbers[i].sums;
    }
    my_goldbach_sums->numbers = new_array;
  }
  free(previous_array);
  return error;
}

uint64_t resize_sums(number_t* number) {
  number->capacity += 30;
  uint64_t error = EXIT_SUCCESS;
  uint64_t* previous_array = number->sums;
  uint64_t* new_array_sums = (uint64_t*)
    calloc(number->capacity, sizeof(uint64_t));
  if (new_array_sums != NULL) {
    for (uint64_t i = 0; i < number->sum_count; i++) {
      new_array_sums[i] = number->sums[i];
    }
    number->sums = new_array_sums;
  } else {
    fprintf(stderr, "Error: cloud not resize the sums vector\n");
    error = 13;
  }
  free(previous_array);
  return error;
}

  //  function result(my_goldbach_sums)
void result(goldbach_sums_t* my_goldbach_sums) {
  uint64_t sums = 0;
  number_t* struct_number = NULL;
  for (uint64_t i = 0; i < my_goldbach_sums->count; ++i) {
    struct_number = &my_goldbach_sums->numbers[i];
    if (struct_number->number > 3 && struct_number->number != 5) {
      sums += struct_number->sums[0];
    } else if (struct_number->number < -3 && struct_number->number != -5) {
      if (struct_number->number % 2 == 0) {
        sums += struct_number->sum_count / 2;
      } else {
        sums += struct_number->sum_count / 3;
      }
    }
  }
  printf("Total %" SCNu64 " numbers %" SCNu64 " sums\n\n"
    , my_goldbach_sums->count, sums);
    //  for (i := 0 to my_goldbach_sums->count)
  for (uint64_t i = 0; i < my_goldbach_sums->count; ++i) {
    struct_number = &my_goldbach_sums->numbers[i];
    if (struct_number->number < -3 && struct_number->number != -5) {
      uint64_t repetitions = struct_number->number % 2 == 0? 2 : 3;
        //  print my_goldbach_sums->numbers[i]->number, ": "
        //  , my_goldbach_sums->numbers[i]->sums
      print(struct_number->number,
        struct_number->sum_count / repetitions, struct_number->sums, false);
    } else if (struct_number->number > 3 && struct_number->number != 5) {
        //  print my_goldbach_sums->numbers[i]->number, ": "
        //  , my_goldbach_sums->numbers[i]->sums
      print(struct_number->number, struct_number->sums[0], NULL, false);
    } else {
        //  print my_goldbach_sums->numbers[i]->number, ": "
        //  , my_goldbach_sums->numbers[i]->sums
      print(struct_number->number, 0, NULL, true);
    }
  }
}

void print(int64_t number, uint64_t number_of_sums
  , uint64_t* sums, bool is_NA) {
  if (is_NA) {
    printf("%" SCNd64 ": NA\n", number);
  } else {
    printf("%" SCNd64 ": %" SCNu64 " sums", number, number_of_sums);
    if (number < -3) {
      printf(": ");
      uint64_t count = 0;
      for (uint64_t i = 0; i < number_of_sums; i++) {
        uint64_t repetitions = number % 2 == 0? 2 : 3;
        for (uint64_t j = 0; j < repetitions; j++) {
          printf("%" SCNd64, sums[count++]);
          if (j != repetitions - 1) {
            printf(" + ");
          }
        }
        if (i != number_of_sums - 1) {
          printf(", ");
        }
      }
    }
    printf("\n");
  }
}

  //  function destroy(my_goldbach_sums)
void destroy(goldbach_sums_t* my_goldbach_sums) {
    //  delete everything stored in my_goldbach_sums
  for (uint64_t i = 0; i < my_goldbach_sums->count; ++i) {
    if (my_goldbach_sums != NULL && my_goldbach_sums->numbers[i].sums != NULL) {
      free(my_goldbach_sums->numbers[i].sums);
    }
  }
  if (my_goldbach_sums != NULL && my_goldbach_sums->numbers != NULL) {
    free(my_goldbach_sums->numbers);
  }
  if (pthread_mutex_destroy
    (&my_goldbach_sums->can_access_solution_count) != EXIT_SUCCESS) {
    fprintf(stderr, "Error: not destroyed mutex \n");
  }
}
