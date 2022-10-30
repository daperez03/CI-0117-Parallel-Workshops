#include <omp.h>
#include <iostream>
#include <vector>

void print_mapping(const char* type, const std::vector<int>& mapping);

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

  double sums = 0;

  /* #pragma omp parallel for num_threads(thread_count) schedule(runtime) \
  default(none) shared(iteration_count, mapping)*/
  for (unsigned int index = 0; index < values.size(); ++index) {
    sums += values[index];
  }

  const double average = values.size() ? sums / values.size() : 0.0;
  std::cout << average << std::endl;
}

