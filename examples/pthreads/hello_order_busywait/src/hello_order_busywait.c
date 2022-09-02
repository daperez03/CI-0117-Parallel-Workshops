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
#include <time.h>
#include <unistd.h>

  //  thread_shared_data_t
typedef struct shared_data {
  uint64_t next_thread;
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

  share_data_t* share_data = (share_data_t*)
    calloc(1, sizeof(share_data_t));
  if (share_data) {
    share_data->next_thread = 0;
    share_data->thread_count = thread_count;

    struct timespec start_time, finish_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    error = create_threads(share_data);
    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;  //  1e-9 = 1 ^-9
    printf("Execution time: %9lfs\n", elapsed_time);
    free(share_data);
  } else {
    fprintf(stderr , "Error: could not allocate shared data\n");
    error = 12;
  }
  return error;
}  //  end procedure


int create_threads(share_data_t* share_data) {
  int error = EXIT_SUCCESS;
  pthread_t* threads = (pthread_t*)
  malloc(share_data->thread_count * sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(share_data->thread_count, sizeof(private_data_t));
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
        fprintf(stderr , "Error: could not create secundary thread\n");
        return 21;
      }
    }

    printf("Hello from main thread\n");
    for (uint64_t thread_number = 0; thread_number < share_data->thread_count
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
    "threads\n", share_data->thread_count);
    error = 22;
  }
  return error;
}


  //  procedure great():
void* greet(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*)data;
  share_data_t* shared_data = private_data->shared_data;

  while (shared_data->next_thread < private_data->thread_number) {  //  espera activa, prohibida
    // busy-wait
  } //  end while

  //  print "Hello from secundary thread"
  printf("Hello from secundary thread %" PRIu64 " of %" PRIu64 "\n"
  , private_data->thread_number , shared_data->thread_count);
  ++shared_data->next_thread;
  return NULL;
}  //  end procedure
