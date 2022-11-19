/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/
#include <assert.h>
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

uint64_t init_goldbach_sums(goldbach_sums_t* my_goldbach_sums) {
  assert(my_goldbach_sums);
  uint64_t error = EXIT_SUCCESS;
  my_goldbach_sums->solution_count = 0;
  my_goldbach_sums->capacity = 120;
  my_goldbach_sums->count = 0;
  my_goldbach_sums->numbers = (number_t*)malloc(120 * sizeof(number_t));
  if (my_goldbach_sums->numbers == NULL) {
    fprintf(stderr, "Error: not create numbers vector\n");
    error = 11;
  }
  my_goldbach_sums->solution_count = 0;
  return error;
}

uint64_t init_number_t(number_t* number) {
  number->capacity = 100;
  // number->number = 0;
  number->id_responsible_process = 0;
  number->sum_count = 0;
  number->sums = (uint64_t*) malloc(100 * sizeof(uint64_t));
  number->sums[0] = 0;
  return number->sums == NULL? EXIT_FAILURE : EXIT_SUCCESS;
}

void append_number_t(number_t* data, number_t* destiny) {
  for (size_t i = 0; i < data->sum_count; i++) {
    if (!(destiny->sum_count < destiny->capacity))
      resize_sums(destiny);
    destiny->sums[i] = data->sums[i];
    ++destiny->sum_count;
  }
}

uint64_t resize_numbers(goldbach_sums_t* my_goldbach_sums) {
  uint64_t error = EXIT_SUCCESS;
  my_goldbach_sums->capacity += my_goldbach_sums->capacity/3;
  number_t* previous_array = my_goldbach_sums->numbers;
  number_t* new_array = (number_t*)
    malloc(my_goldbach_sums->capacity * sizeof(number_t));
  if (new_array == NULL) {
    fprintf(stderr, "Error: cloud not resize the number vector\n");
    error = 12;
  } else {
    for (size_t i = 0; i < my_goldbach_sums->count; ++i) {
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
  number->capacity += number->capacity/3;
  uint64_t error = EXIT_SUCCESS;
  uint64_t* previous_array = number->sums;
  uint64_t* new_array_sums = (uint64_t*)
    malloc(number->capacity * sizeof(uint64_t));
  if (new_array_sums != NULL) {
    for (size_t i = 0; i < number->sum_count; i++) {
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
  for (size_t i = 0; i < my_goldbach_sums->count; ++i) {
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
  for (size_t i = 0; i < my_goldbach_sums->count; ++i) {
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
      for (size_t i = 0; i < number_of_sums; i++) {
        uint64_t repetitions = number % 2 == 0? 2 : 3;
        for (size_t j = 0; j < repetitions; j++) {
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
void destroy_goldbach_sums(goldbach_sums_t* my_goldbach_sums) {
  assert(my_goldbach_sums);
  //  delete everything stored in my_goldbach_sums
  if (my_goldbach_sums->numbers != NULL) {
    for (size_t i = 0; i < my_goldbach_sums->count; ++i) {
      if (my_goldbach_sums->numbers[i].sums !=  NULL)
        free(my_goldbach_sums->numbers[i].sums);
    }
    free(my_goldbach_sums->numbers);
  }
}

void destroy_numbert_t (number_t* number) {
  assert(number->sums);
  free(number->sums);
}
