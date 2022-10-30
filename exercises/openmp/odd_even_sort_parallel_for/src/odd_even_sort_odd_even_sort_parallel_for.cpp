// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <omp.h>
#include <cstdlib>
#include <iostream>

void concurrent_odd_even_sort(size_t n, double* arr, size_t thread_count);
void swap(double& number1, double& number2);

int main(int argc, char* argv[]) {
  size_t n = 0;
  if (argc >= 2) {
    n = atoi(argv[1]);
  }
  size_t thread_count = omp_get_max_threads();
  if (argc >= 3) {
    thread_count = atoi(argv[2]);
  }
  double* arr = new double[n];
  for (size_t i = 0; i < n; i++) {
    unsigned int seedp = static_cast<unsigned int>(i);
    arr[i] = static_cast<double>(rand_r(&seedp) % 100000)
      + (static_cast<double>(rand_r(&seedp) % 100000)/1000000);
  }
    concurrent_odd_even_sort(n, arr, thread_count);
  for (size_t i = 0; i < n; i++) printf("%f - ", arr[i]);
  std::cout << std::endl;
  delete []arr;
}

void concurrent_odd_even_sort(size_t n, double* arr, size_t thread_count) {
  for (size_t phase = 0; phase < n; ++phase) {
    if (phase % 2 == 0) {
      #pragma omp parallel for num_threads(thread_count) \
        default(none) shared(arr, n)
      for (size_t i = 1; i < n; i += 2) {
          if (arr[i - 1] > arr[i]) {
            swap(arr[i - 1], arr[i]);
          }
      }
    } else {
      #pragma omp parallel for num_threads(thread_count) \
        default(none) shared(arr, n)
      for (size_t i = 1; i < n - 1; i += 2) {
        if (arr[i] > arr[i + 1]) {
          swap(arr[i], arr[i + 1]);
        }
      }
    }
  }
}

void swap(double& number1, double& number2) {
  double copy_number = number1;
  number1 = number2;
  number2 = copy_number;
}
