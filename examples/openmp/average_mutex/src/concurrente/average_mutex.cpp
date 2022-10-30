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
  double total_sums = 0.0;
  #pragma omp parallel num_threads(thread_count) \
    default(none) shared(values, total_sums)
  {
    double my_partial_sum = 0.0;
    #pragma omp for schedule(runtime)
    for (size_t index = 0; index < values.size(); ++index) {
      #pragma omp critical(can_sum)
      my_partial_sum += values[index];
    }
    // #pragma omp critical(can_sum)
    #pragma omp atomic // Esto es una opereacion atomica, es como un
    // mutex pero a nivel de hardware, solo se puede aplicar a operaciones
    // sencillas
    total_sums += my_partial_sum;
  }
  const double average = values.size() ? total_sums / values.size() : 0.0;
  std::cout << average << std::endl;
}

