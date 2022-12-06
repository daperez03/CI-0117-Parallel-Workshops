// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <mpi.h>
#include <omp.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int calculate_start(int rank, int end, int workers, int begin);
int calculate_finish(int rank, int end, int workers, int begin);

int main(int argc, char* argv[]) {
  try {
    if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
      int process_number = -1;  // rank
      MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

      int process_count = -1;
      MPI_Comm_size(MPI_COMM_WORLD, &process_count);

      char process_hostname[MPI_MAX_PROCESSOR_NAME];
      int hostname_length = -1;
      MPI_Get_processor_name(process_hostname, &hostname_length);
      int overall_start = 0;
      int overall_finish = 0;
      if (argc == 3) {
        overall_start = atoi(argv[1]);
        overall_finish = atoi(argv[2]);
      } else {
        if (process_number == 0) {
          std::cin >> overall_start;
          std::cin >> overall_finish;
          for (size_t index = 1; index
            < static_cast<size_t>(process_count); ++index) {
            if (MPI_Send(&overall_start, 1, MPI_INT
              , index, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
              throw std::runtime_error("cloud dont send overall_start");
            }
            if (MPI_Send(&overall_finish, 1, MPI_INT
              , index, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
              throw std::runtime_error("cloud dont send overall_start");
            }
          }
        } else {
          if (MPI_Recv(&overall_start, 1, MPI_INT, 0, 0
            , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
            throw std::runtime_error("cloud dont recive overall_start");
          }
          if (MPI_Recv(&overall_finish, 1, MPI_INT, 0, 0
            , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
            throw std::runtime_error("cloud dont recive overall_finish");
          }
        }
      }

      const int process_start = calculate_start(process_number, overall_finish
        , process_count, overall_start);
      const int process_finish = calculate_finish(process_number, overall_finish
        , process_count, overall_start);
      const int process_size = process_finish - process_start;

      std::cout << process_hostname << ':' << process_number << ": range ["
        << process_start << ", " << process_finish << "[ size " << process_size
        << std::endl;

      #pragma omp parallel default(none) shared(std::cout, process_hostname) \
        shared(process_number, process_start, process_finish)
      {  // NOLINT(whitespace/braces)
        int thread_start = -1;
        int thread_finish = -1;

        #pragma omp for schedule(static)
        for (int index = process_start; index < process_finish; ++index) {
          if (thread_start == -1) {
            thread_start = index;
          }
          thread_finish = index;
        }

        ++thread_finish;
        const int thread_size = thread_finish - thread_start;

        #pragma omp critical(can_print)
        std::cout << '\t' << process_hostname << ':' << process_number << '.'
          << omp_get_thread_num() << ": range [" << thread_start << ", " <<
          thread_finish << "[ size " << thread_size << std::endl;
      }
      MPI_Finalize();
    }
  } catch(const std::exception& exception) {
    std::cerr << "ERROR: "<< exception.what() << std::endl;
  }
  return 0;
}

/// Calula el start de un mapeo en bloque
int calculate_start(int rank, int end, int workers, int begin) {
  const int range = end - begin;
  return begin + rank * (range / workers) + std::min(rank, range % workers);
}

/// Calula el finish de un mapeo en bloque
int calculate_finish(int rank, int end, int workers, int begin) {
  return calculate_start(rank + 1, end, workers, begin);
}
