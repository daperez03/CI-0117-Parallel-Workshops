#include <mpi.h>
#include <omp.h>
#include <iostream>

int main(int argc, char* argv[]) {

  // Inicializamos el MPI
  if(MPI_Init(&argc, &argv) == MPI_SUCCESS) {

    /* Variable en la que queremos establecer el numero
      de proceso que estan establecidos*/
    int process_number = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    /* Variable en la que queremos establecer el total
      de los proceso que estan establecidos*/
    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    /* La funcion de abajo obtiene  el nombre de la maquina actual
      respecto a todo el mundo y hostname_length nos indica el length
      de ese nombre
    */
    char process_hostname[MPI_MAX_PROCESSOR_NAME] = {0};
    int hostname_length = -1;
    MPI_Get_processor_name(process_hostname, &hostname_length);

    std::cout << "Hello from main thread of process " << process_number
      << " of " << process_count << " on " << process_hostname << std::endl;

    int thread_count = omp_get_max_threads();
    if(argc == 2) {
      thread_count = atoi(argv[1]);
    }

    #pragma omp parallel num_threads(thread_count) default(none) \
    shared(std::cout, process_number, process_count, process_hostname)
    {
      #pragma omp critical(stdout)
      std::cout << "\tHello from thread" << omp_get_thread_num() <<" of "
        << omp_get_num_threads() << " of process " << process_number
          << " of " << process_count << " on " << process_hostname << std::endl;
    }

    MPI_Finalize();

  } else {
    std::cerr << "error: cloud not init MPI" << std::endl;
  }
  return 0;
}