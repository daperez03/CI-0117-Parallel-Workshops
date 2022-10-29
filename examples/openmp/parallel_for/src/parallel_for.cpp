#include <iostream>
#include <omp.h> // include para funciones de omp
int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads();
  if (argc >= 2) {
    thread_count = atoi(argv[1]);
  }
  int iteration_count = thread_count;
  if (argc >= 3) {
    iteration_count = atoi(argv[2]);
  }
  // base de OpenMP: #pragma omp
  //Las instrucciones deben estar encerradas por bloque {}
  // si solo se coloca el pragma va a parelisar la instruccion de abajo
  #pragma omp parallel for num_threads(thread_count) \
   default(none) shared(iteration_count, std::cout)
  // pasa numero de hilos a crearmake
  // \ ignora cambio de linea
  // private && public indican como se deben pasar las variables
  // default none evita que omp cree valores por default
  // for de pragma nos permite hacer un for con varios hilos, utiliza mapeo
  // por bloque, por eso es necesario que el for sea con contador
  for (int iteration = 0; iteration < iteration_count; ++iteration) {
      // Genera una region critica en omp(mutex), se puede nombrar mutex para
      // excluir varias regiones criticas
      #pragma omp critical(stdout)
      {
      std::cout << omp_get_thread_num() << "/" << omp_get_num_threads()
      << ": iteration " << iteration << '/' << iteration_count << std::endl;
          // se implementan funciones de omp
      }
  }
}
