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
  #pragma omp parallel for num_threads(thread_count) schedule(runtime) \
    default(none) shared(values) reduction(+:total_sums)
    // reduction(op:var) es como una funcio pre escrita que lo que hace es
    // simplificar algunas operaciones, en este caso una sumatoria,
    // lo hace con omp atomic
    for (size_t index = 0; index < values.size(); ++index) {
      total_sums += values[index];
    }
  const double average = values.size() ? total_sums / values.size() : 0.0;
  std::cout << average << std::endl;
}

