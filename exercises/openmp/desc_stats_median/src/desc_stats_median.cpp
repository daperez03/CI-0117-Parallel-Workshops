// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <omp.h>
#include <cmath>
#include <iostream>
#include <vector>

void concurrent_odd_even_sort(size_t n, double* arr);
void swap(double& number1, double& number2);
int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads();
  if (argc >= 2) {
    thread_count = atoi(argv[1]);
  }
  (void)thread_count;
  std::vector<double> values;

  double value = 0.0;
  while (std::cin >> value) {
    values.push_back(value);
  }

  double min_value = INFINITY;
  double max_value = -1 * INFINITY;
  double total_sums = 0;
  double variance = 0;
  double mean = 0;
  #pragma omp parallel num_threads(thread_count) \
    default(none) shared(values, max_value, min_value, \
      total_sums, variance, mean)
  {
    #pragma omp for schedule(runtime) reduction(min:min_value) \
      reduction(max:max_value) reduction(+:total_sums)
    for (size_t index = 0; index < values.size(); ++index) {
      total_sums += values[index];
      max_value = std::max(max_value, values[index]);
      min_value = std::min(min_value, values[index]);
    }
    # pragma omp single
    mean = values.size() ? total_sums / values.size() : 0.0;
    #pragma omp for schedule(runtime) reduction(+:variance)
    for (size_t index = 0; index < values.size(); ++index) {
      variance += pow(values[index] - mean, 2);
    }
    concurrent_odd_even_sort(values.size(), values.data());
  }
  const double standard_deviation = values.size() ?
    variance / values.size() : 0.0;
  const double median = (values[(values.size() / 2)
    - !(values.size() % 2)]);
  std::cout << "Mean: " << mean << std::endl;
  std::cout << "Max value: " << max_value << std::endl;
  std::cout << "Min value: " << min_value << std::endl;
  std::cout << "Standar deviation: " << standard_deviation << std::endl;
  std::cout << "Median: " << median << std::endl;
}

void concurrent_odd_even_sort(size_t n, double* arr) {
  for (size_t phase = 0; phase < n; ++phase) {
    if (phase % 2 == 0) {
      # pragma omp for
      for (size_t i = 1; i < n; i += 2) {
          if (arr[i - 1] > arr[i]) {
            swap(arr[i - 1], arr[i]);
          }
      }
    } else {
      # pragma omp for
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
