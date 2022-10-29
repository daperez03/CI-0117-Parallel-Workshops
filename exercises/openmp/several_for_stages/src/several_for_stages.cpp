// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#include <omp.h>
#include <iostream>

int main(int argc, char* argv[]) {
  size_t thread_count = omp_get_max_threads();
  size_t  stages = 3;
  if (argc >= 2) {
    thread_count = atoi(argv[1]);
  }
  size_t iteration_count = thread_count;
  if (argc >= 3) {
    iteration_count = atoi(argv[2]);
  }
  if (argc >= 4) {
    stages = atoi(argv[3]);
  }
  #pragma omp parallel num_threads(thread_count) \
    default(none) shared(iteration_count, stages, std::cout)
  {
    for (size_t firts_iterator = 0; firts_iterator < stages
      ; ++firts_iterator) {
      #pragma omp for
      for (size_t second_iteration = 0; second_iteration < iteration_count
        ; ++second_iteration) {
        #pragma omp critical(stdout)
        {
          std::cout << "Stage " << firts_iterator + 1 << ": "
          << omp_get_thread_num() + 1 << "/" << omp_get_num_threads()
          << ": iteration " << second_iteration + 1 << '/'
          << iteration_count << std::endl;
        }
      }
      #pragma omp single
        std::cout << std ::endl;
    }
  }
}
