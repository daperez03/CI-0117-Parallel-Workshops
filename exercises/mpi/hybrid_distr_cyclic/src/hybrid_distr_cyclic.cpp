// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <mpi.h>
#include <omp.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <sstream>

int main(int argc, char* argv[]) {
  try {
    if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
      const double start_time = MPI_Wtime();
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
        }
        if (MPI_Bcast(&overall_start, /*count*/ 1, MPI_INT, /*root*/ 0
          , MPI_COMM_WORLD) != MPI_SUCCESS ) {
          throw std::runtime_error("could not broadcast overall_start");
        }
        if (MPI_Bcast(&overall_finish, /*count*/ 1, MPI_INT, /*root*/ 0
          , MPI_COMM_WORLD) != MPI_SUCCESS ) {
          throw std::runtime_error("could not broadcast overall_finish");
        }
      }

      int process_size = 0;
      #pragma omp parallel default(none) shared(std::cout, process_hostname) \
        shared(process_number, process_count, process_size) \
        shared(overall_start, overall_finish)
      {  // NOLINT(whitespace/braces)
        std::string numbers("\t\t");
        #pragma omp for schedule(guided)
        for (int index = process_number + overall_start;
          index < overall_finish; index += process_count) {
          numbers += std::to_string(index);
          numbers += " - ";
          #pragma omp critical(can_access_process_size)
          ++process_size;
        }
        #pragma omp critical(can_print)
        std::cout << '\t' << process_hostname << ':' << process_number << '.'
          << omp_get_thread_num() << ": I process these numbers" << std::endl
          << numbers << std::endl;
      }
      const double elapsed = MPI_Wtime() - start_time;
      std::cout << process_hostname << ':' << process_number << ": "
      "size " << process_size << " in " << elapsed << "s" << std::endl;
      MPI_Finalize();
    }
  } catch(const std::exception& exception) {
    std::cerr << "ERROR: "<< exception.what() << std::endl;
  }
  return 0;
}
