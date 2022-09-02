/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/


#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

  //  thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;
  uint64_t thread_count;
}private_data_t;

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
int create_threads(uint64_t thread_count);

//  procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  //  thread_count := integer(argv[1])
  uint64_t thread_count =  sysconf(_SC_NPROCESSORS_ONLN);
  //  strol(argv[1], .....) //strtol(string): convierte de string a long
  //  Escanea vector
  //  assert(argc == 2);
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) != 1) {
      fprintf(stderr , "Error: invalid thread count\n");
      error = 11;
    }
  }
  error = create_threads(thread_count);
  return error;
}  //  end procedure


int create_threads(uint64_t thread_count) {
  int error = EXIT_SUCCESS;
  pthread_t* threads = (pthread_t*)
  malloc(thread_count * sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(thread_count, sizeof(private_data_t));
  if (threads && private_data) {
    for (uint64_t thread_number = 0; thread_number < thread_count
      ; ++thread_number) {
        private_data[thread_number].thread_number = thread_number;
        private_data[thread_number].thread_count = thread_count;
      //  create_thread(great(), thread_number)
      //  CREA HILO SECUNDARIO
      error = pthread_create(&threads[thread_number] ,
      /*attr*/ NULL , greet , &private_data[thread_number]);
      if (error != EXIT_SUCCESS) {
        fprintf(stderr , "Error: could not create secundary thread\n");
        error = 21;
      }
    }

    printf("Hello from main thread\n");
    for (uint64_t thread_number = 0; thread_number < thread_count
      ; ++thread_number) {
      //  usleep(2);  //  indeterminismo
      //  ENVIA A DORMIR HILO PRINCIPAL
      pthread_join(threads[thread_number], /*value_ptr*/ NULL);
    }

      //  print "Hello from main thread"
    free(private_data);
    free(threads);
  } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64
    "threads\n", thread_count);
    error = 22;
  }
  return error;
}


  //  procedure great():
void* greet(void* data) {
  private_data_t* private_data = (private_data_t*)data;
  //  print "Hello from secundary thread"
  printf("Hello from secundary thread %" PRIu64 " of %" PRIu64 "\n"
  , private_data->thread_number , private_data->thread_count);
  return NULL;
}  //  end procedure
