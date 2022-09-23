/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

  //  thread_shared_data_t
typedef struct shared_data {
  char** _names;
  sem_t** can_greet;
  uint64_t thread_count;
} shared_data_t;

  //  thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;
  shared_data_t* shared_data;
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
int create_threads(shared_data_t* share_data);


//  procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  //  thread_count := integer(argv[1])
  uint64_t thread_count =  sysconf(_SC_NPROCESSORS_ONLN);
  //  strol(argv[1], .....) //strtol(string): convierte de string a long
  //  Escanea vector
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) != 1) {
      fprintf(stderr , "Error: invalid thread count\n");
      return 11;
    }
  }

  shared_data_t* share_data = (shared_data_t*)
    calloc(1, sizeof(shared_data_t));
  if (share_data) {
    share_data->can_greet = (sem_t**)calloc(thread_count, sizeof(sem_t*));
    share_data->thread_count = thread_count;
    share_data->_names = (char**)calloc(thread_count, sizeof(char*));

    for (uint64_t thread_number = 0; thread_number < thread_count
      ; ++thread_number) {
      share_data->_names[thread_number] = (char*)calloc(256, sizeof(char));
      snprintf(share_data->_names[thread_number]
        , (size_t)256, "sem%zu", thread_number);
      share_data->can_greet[thread_number] =
        sem_open(share_data->_names[thread_number]
          , O_CREAT | O_EXCL, 0644, !thread_number);
    }

    if (share_data->can_greet) {
      struct timespec start_time, finish_time;
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      error = create_threads(share_data);
      clock_gettime(CLOCK_MONOTONIC, &finish_time);
      double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
        (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;  //  1e-9 = 1 ^-9
      printf("Execution time: %9lfs\n", elapsed_time);
      for (uint64_t thread_number = 0; thread_number
      < share_data->thread_count; ++thread_number) {
        sem_unlink(share_data->_names[thread_number]);
        free(share_data->_names[thread_number]);
      }
      free(share_data->_names);
      free(share_data->can_greet);
    } else {
      fprintf(stderr , "Error: could not allocate semaphoro\n");
      error = 13;
    }
    free(share_data);
  } else {
    fprintf(stderr , "Error: could not allocate shared data\n");
    error = 12;
  }
  return error;
}  //  end procedure


int create_threads(shared_data_t* share_data) {
  int error = EXIT_SUCCESS;
  pthread_t* threads = (pthread_t*)
  malloc(share_data->thread_count * sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(share_data->thread_count, sizeof(private_data_t));
  printf("Hello from main thread\n");
  if (threads && private_data) {
    for (uint64_t thread_number = 0; thread_number < share_data->thread_count
      ; ++thread_number) {
      //  can_greet[thread_number] := create_semaphore(not thread_number)
      if (share_data->can_greet[thread_number] != SEM_FAILED) {
        private_data[thread_number].thread_number = thread_number;
        private_data[thread_number].shared_data = share_data;
        //  create_thread(great(), thread_number)
        //  CREA HILO SECUNDARIO
        error = pthread_create(&threads[thread_number] ,
          /*attr*/ NULL , greet , &private_data[thread_number]);
        if (errno != EXIT_SUCCESS && error == EXIT_SUCCESS) {
          fprintf(stderr , "Error: could not create secundary thread\n");
          return 21;
        }
        //  sem_close(share_data->can_greet[thread_number]);
      } else {
        fprintf(stderr , "Error: could not init semaphore\n");
        error = 22;
        break;
      }
    }

    for (uint64_t thread_number = 0; thread_number
      < share_data->thread_count; ++thread_number) {
      if (error == (int)EXIT_SUCCESS) {
        pthread_join(threads[thread_number], /*value_ptr*/ NULL);
      }
    }
    free(private_data);
    free(threads);
  } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64
    "threads\n", share_data->thread_count);
    error = 23;
  }
  return error;
}


  //  procedure great():
void* greet(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*)data;
  shared_data_t* shared_data = private_data->shared_data;
  //  wait(can_greet[thread_number])
  int error = sem_wait(shared_data->can_greet[private_data->thread_number]);
  if (error) {
    fprintf(stderr, "error: could not wait for semaphore %d\n", errno);
  }

  //  print "Hello from secundary thread"
  printf("Hello from secundary thread %" PRIu64 " of %" PRIu64 "\n"
  , private_data->thread_number , shared_data->thread_count);
  //  signal(can_greet[(thread_number + 1) mod thread_count])
  const uint64_t next_thread = (private_data->thread_number + 1)
    % shared_data->thread_count;
  error = sem_post(shared_data->can_greet[next_thread]);
  if (error) {
    fprintf(stderr, "error: could not increment semaphore%d \n", errno);
  }

  return NULL;
}  //  end procedure
