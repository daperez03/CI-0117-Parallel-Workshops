/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#include <unistd.h>
#include "buffer.h"
#include "goldbach_sums.h"
#include "Mpi.h"
#include "my_math.h"

#define is_error(x) x != EXIT_SUCCESS

uint64_t dispatcher(int process_count);
uint64_t calculator(int process_number);

/**
 * @brief Main funtion
 * @param argc Argument counter
 * @param argv Arguments
 * @return An error code
 */
int main(int argc, char* argv[]) {  //  function main(argv[])
  uint64_t error = EXIT_SUCCESS;
  mpi_data_t my_process_data;
  error = init_mpi(&my_process_data, &argc, &argv);
  if (!is_error(error)) {
    size_t threads_number = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc == 2) {
      //  define threads_number := argv[1]
      if (sscanf(argv[1], "%" SCNu64, &threads_number) != 1) {
        fprintf(stderr , "Error: invalid thread count\n");
        error = 11;
      }
    }
    if (!is_error(error)) {
      if (my_process_data.process_count > 1) {
        if (my_process_data.process_number == 0) {
          dispatcher(my_process_data.process_count);
        } else {
          calculator(my_process_data.process_number);
        }
        uninit_mpi();
      } else {
        printf("Here");
        goldbach_sums_t my_goldbach_sums;
        error = init_goldbach_sums(&my_goldbach_sums);
        error = read_data(&my_goldbach_sums);
        error = regular_solution(&my_goldbach_sums);
        result(&my_goldbach_sums);
      }
    }
  } else {
    fprintf(stderr , "Error: cloud not init MPI\n");
  }
  return error;
}

uint64_t dispatcher(int process_count) {
  assert(process_count > 1);
  uint64_t error = EXIT_SUCCESS;
  goldbach_sums_t my_goldbach_sums;
  error = init_goldbach_sums(&my_goldbach_sums);
  if(!is_error(error)) {
    error = read_data(&my_goldbach_sums);
    if(!is_error(error)) {
      int32_t id_pending_process = 0;
      size_t pending_solution = 0;
      ssize_t pending_process = (ssize_t)process_count - 1;

      while (true) {
        error = receive_int32_t(&id_pending_process, 1, MPI_ANY_SOURCE, 0);
        if(!is_error(error)) {
          pending_solution = my_goldbach_sums.solution_count++;

          if (!(pending_solution < my_goldbach_sums.count)) {

            int64_t data_report[2] = {false};
            error = send_int64_t(&data_report[0], 2, id_pending_process, 0);
            if (!is_error(error)) {
              if (--pending_process <= 0) break;
            }  else {
              destroy_goldbach_sums(&my_goldbach_sums);
              fprintf(stderr , ERROR_SEND_MSG);
              return error;
            }

          } else {

            number_t* pending_number = &my_goldbach_sums.numbers[pending_solution];
            pending_number->id_responsible_process = id_pending_process;
            int64_t data_report[2] = {true, pending_number->number};
            error = send_int64_t(data_report, 2, id_pending_process, 0);

          }
        } else {
          destroy_goldbach_sums(&my_goldbach_sums);
          fprintf(stderr , ERROR_RECEIVE_MSG);
          return error;
        }
      }

      bool ready_process = true;
      for (size_t index = 0; index < my_goldbach_sums.count; ++index) {
        int64_t capacity = 0;
        number_t* current_number = &my_goldbach_sums.numbers[index];
        int32_t process = current_number->id_responsible_process;
        error = send_bool(&ready_process, process, 0);
        if (!is_error(error)) {
          error = receive_int64_t(&capacity, 1, process, TAG_DATA_REPORT);
          if (!is_error(error)) {
            current_number->capacity = capacity;
            current_number->sum_count = capacity;
            current_number->sums = (uint64_t*) malloc(capacity * sizeof(uint64_t));
            // Se obtienen los datos
            error = receive_uint64_t(current_number->sums, capacity, process, 0);
            if (is_error(error)) {
              destroy_goldbach_sums(&my_goldbach_sums);
              fprintf(stderr , ERROR_RECEIVE_MSG);
              return error;
            }
          } else {
            destroy_goldbach_sums(&my_goldbach_sums);
            fprintf(stderr , ERROR_RECEIVE_MSG);
            return error;
          }
        } else {
          destroy_goldbach_sums(&my_goldbach_sums);
          fprintf(stderr , ERROR_SEND_MSG);
          return error;
        }
      }

      result(&my_goldbach_sums);
      destroy_goldbach_sums(&my_goldbach_sums);
    } else {
      int64_t data_report[2] = {false};
      for (int index = 1; index < process_count; ++index) {
        error = send_int64_t(&data_report[0], 2, index, 0);
      }
      destroy_goldbach_sums(&my_goldbach_sums);
      return error;
    }
  }  else {
    fprintf(stderr , "Error: cloud not possible init goldbach_sums\n");
  }
  return error;
}

uint64_t calculator(int process_number) {
  assert(process_number > 0);
  uint64_t error = EXIT_SUCCESS;
  goldbach_sums_t sums_container;
  error = init_goldbach_sums(&sums_container);
  if (!is_error(error)) {
    while (true) {
      error = send_int32_t(&process_number, 1, 0, 0);
      if (!is_error(error)) {
        // Se obtienen los datos
        int64_t data_report[2] = {0};
        error = receive_int64_t(&data_report[0], 2, 0, 0);
        if (!is_error(error)) {
          if (data_report[0] == false) {
            break;
          } else {
            // Se trabajan los datos
            if (sums_container.count >= sums_container.capacity) {
              error = resize_numbers(&sums_container);
            }
            if (!is_error(error)) {
              number_t* my_number = &sums_container.numbers[sums_container.count++];
              error = init_number_t(my_number);
              if (!is_error(error)) {
                my_number->number = data_report[1];
                error = solve(my_number);
              } else {
                destroy_goldbach_sums(&sums_container);
                fprintf(stderr , "Error: cloud not possible init number_t\n");
                return error;
              }
            } else {
              destroy_goldbach_sums(&sums_container);
              fprintf(stderr , ERROR_SEND_MSG);
              return error;
            }
          }
        } else {
          destroy_goldbach_sums(&sums_container);
          fprintf(stderr , ERROR_SEND_MSG);
          return error;
        }
      } else {
        destroy_goldbach_sums(&sums_container);
        fprintf(stderr , ERROR_SEND_MSG);
        return error;
      }
    }

    bool run = false;
    for (size_t index = 0; index < sums_container.count; ++index) {
      error = receive_bool(&run, 0, 0);
      if (!is_error(error)) {
        number_t* my_number = &sums_container.numbers[index];
        int64_t capacity = 0;
        if (my_number->number > -6 && my_number->number != -4) {
          capacity = 1;
        } else {
          capacity = my_number->sum_count;
        }
        error = send_int64_t(&capacity, 1, 0, TAG_DATA_REPORT);
        if (!is_error(error)) {
          error = send_uint64_t(my_number->sums, capacity, 0, 0);
          if (is_error(error)) {
            destroy_goldbach_sums(&sums_container);
            fprintf(stderr , ERROR_SEND_MSG);
            return error;
          }
        } else {
          destroy_goldbach_sums(&sums_container);
          fprintf(stderr , ERROR_SEND_MSG);
          return error;
        }
      } else {
        destroy_goldbach_sums(&sums_container);
        fprintf(stderr , ERROR_RECEIVE_MSG);
        return error;
      }
    }
    destroy_goldbach_sums(&sums_container);
  } else {
    fprintf(stderr , "Error: cloud not possible init goldbach_sums\n");
  }
  return EXIT_SUCCESS;
}
