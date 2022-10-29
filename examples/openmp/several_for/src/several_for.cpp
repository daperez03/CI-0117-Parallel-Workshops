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
  #pragma omp parallel num_threads(thread_count) \
   default(none) shared(iteration_count, std::cout)
  {
    #pragma omp for // paraleliza fors y contiene barrera implicita
    for (int iteration = 0; iteration < iteration_count; ++iteration) {
        #pragma omp critical(stdout)
        {
        std::cout << "stage 1:" << omp_get_thread_num() << "/" 
        << omp_get_num_threads() << ": iteration " << iteration
        << '/' << iteration_count << std::endl;
            // se implementan funciones de omp
        }
    }
    #pragma omp single // indica a omp que un unico hilo
    // puede ejecutar el bloque, contiene barrera implicita
    std::cout << std ::endl;
    // #pragma omp barrier // crea barreras para los hilos

    #pragma omp for
    for (int iteration = 0; iteration < iteration_count; ++iteration) {
        #pragma omp critical(stdout)
        {
        std::cout << "stage 2:" << omp_get_thread_num() << "/" 
        << omp_get_num_threads() << ": iteration " << iteration
        << '/' << iteration_count << std::endl;
            // se implementan funciones de omp
        }
    }

    #pragma omp single
    std::cout << std ::endl;
    // #pragma omp barrier

    #pragma omp for
    for (int iteration = 0; iteration < iteration_count; ++iteration) {
      #pragma omp critical(stdout)
      {
        std::cout << "stage 3:" << omp_get_thread_num() << "/" 
        << omp_get_num_threads() << ": iteration " << iteration
        << '/' << iteration_count << std::endl;
            // se implementan funciones de omp
      }
    }
  }
}
