#include <iostream>
#include <omp.h> // include para funciones de omp
int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads();
  if (argc == 2) {
    thread_count = atoi(argv[1]);
  }
  
  // base de OpenMP: #pragma omp
  //Las instrucciones deben estar encerradas por bloque {}
  // si solo se coloca el pragma va a parelisar la instruccion de abajo
  #pragma omp parallel num_threads(thread_count) // pasa numero de hilos a crearmake

  {
    // Genera una region critica en omp(mutex), se puede nombrar mutex para
    // excluir varias regiones criticas
    #pragma omp critical(mutex1)
    {
      std::cout << "Hello form secundary thread " << omp_get_thread_num() << " of "
      << omp_get_num_threads() << std::endl; // se implementan funciones de omp
    }
  }
}