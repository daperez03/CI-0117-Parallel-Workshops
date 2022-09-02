/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/

#include <chrono>
#include <inttypes.h>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <thread>
#include <vector>

  //  thread_shared_data_t
typedef struct shared_data {
  uint64_t thread_count;
} share_data_t;

  //  thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;
  share_data_t* shared_data;
} private_data_t;

/**
 * Aca se documenta las clase
 * @brief  Genera un mensaje en la salida standar
 * 
 * @param data NULL
 * @return void* NULL
 */
void* greet(void* data);

/**
 * @brief Metodo el cual crea hilos de ejecucion del programa greet
 * 
 * @param thread_count Indica numero de hilos que se quiere ejecutar
 * @return Numero entero indicando si la ejecucion fue exitosa o surgio un error
 */
int create_threads(share_data_t* share_data);

//  procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  auto start = std::chrono::high_resolution_clock::now();
  int error = EXIT_SUCCESS;
  //  thread_count := integer(argv[1])
  uint64_t thread_count =  std::thread::hardware_concurrency();
  //  strol(argv[1], .....) //strtol(string): convierte de string a long
  //  Escanea vector
  //  assert(argc == 2);
  if (argc == 2) {
    std::istringstream get(argv[1]);
    try
    {
      get >> thread_count;
    }
    catch(...) {
      std::cerr <<  "Error: invalid thread count\n";
      error = 11;
    }
  }

  share_data_t* share_data = new share_data_t[1];
  if (share_data) {
    share_data->thread_count = thread_count;
    error = create_threads(share_data);
    delete []share_data;
  } else {
    std::cerr << "Error: could not allocate shared data\n";
    error = 12;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << "Time of the process: "<< diff.count() << " s\n";
  return error;
}  //  end procedure


int create_threads(share_data_t* share_data) {
  int error = EXIT_SUCCESS;
  pthread_t* threads = new pthread_t[share_data->thread_count];
  private_data_t* private_data = new private_data_t[share_data->thread_count];
  if (threads && private_data) {
    for (uint64_t thread_number = 0; thread_number < share_data->thread_count
      ; ++thread_number) {
        private_data[thread_number].thread_number = thread_number;
        private_data[thread_number].shared_data = share_data;
      //  create_thread(great(), thread_number)
      //  CREA HILO SECUNDARIO
      error = pthread_create(&threads[thread_number] ,
      /*attr*/ NULL , greet , &private_data[thread_number]);
      if (error != EXIT_SUCCESS) {
        std::cerr << "Error: could not create secundary thread\n";
        error = 21;
      }
    }

    std::cout << "Hello from main thread\n";
    for (uint64_t thread_number = 0; thread_number < share_data->thread_count
      ; ++thread_number) {
      //  usleep(2);  //  indeterminismo
      //  ENVIA A DORMIR HILO PRINCIPAL
      pthread_join(threads[thread_number], /*value_ptr*/ NULL);
    }

      //  print "Hello from main thread"
    delete []private_data;
    delete []threads;
  } else {
    std::cerr << "Error: could not allocate " << share_data->thread_count <<
    "threads\n";
    error = 22;
  }
  return error;
}


  //  procedure great():
void* greet(void* data) {
  private_data_t* private_data = (private_data_t*)data;
  share_data_t* shared_data = private_data->shared_data;
  //  print "Hello from secundary thread"
  std::cout << "Hello from secundary thread " <<private_data->thread_number <<" of " << shared_data->thread_count <<"\n";
  return NULL;
}  //  end procedure
