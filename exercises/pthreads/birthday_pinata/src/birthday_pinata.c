/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/


#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

  //  thread_shared_data_t
typedef struct shared_data {
  uint64_t thread_count;
  uint64_t pinata_life;
  pthread_mutex_t can_access_position;
} shared_data_t;

  //  thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;
  uint64_t hits;
  shared_data_t* shared_data;
} private_data_t;

/**
 * @brief  funcion el cual permite que los hilos puedan golpear a la piñata uno a la vez
 * Utiliza un mutex para que esto sea posible
 * @param data Contiene los datos de la piñata
 * @return void* NULL
 */
void* hit_pinata(void* data);

/**
 * @brief Metodo el cual crea hilos de ejecucion del programa hit_pinata
 * 
 * @param thread_count Indica numero de hilos que se quiere ejecutar
 * @return Numero entero indicando si la ejecucion fue exitosa o surgio un error
 */
int create_threads(shared_data_t* share_data);

//  procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  uint64_t thread_count =  sysconf(_SC_NPROCESSORS_ONLN);
  uint64_t pinata_life = 100;
  if (argc == 3) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) != 1) {
      fprintf(stderr , "Error: invalid thread count\n");
      error = 11;
    }
    if (sscanf(argv[2], "%" SCNu64, &pinata_life) != 1) {
      fprintf(stderr , "Error: invalid life of pinata\n");
      error = 12;
    }
  }

  shared_data_t* shared_data = (shared_data_t*)
    calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    error = pthread_mutex_init(&shared_data->can_access_position, NULL);
    if (error == EXIT_SUCCESS) {
      shared_data->thread_count = thread_count;
      shared_data->pinata_life = pinata_life;
      error = create_threads(shared_data);
      free(shared_data);
    } else {
      fprintf(stderr , "Error: could not init mutex\n");
      error = 14;
    }
  } else {
    fprintf(stderr , "Error: could not allocate shared data\n");
    error = 13;
  }
  return error;
}  //  end procedure

  //  Crea hilos de ejecucion
int create_threads(shared_data_t* share_data) {
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
        error = pthread_create(&threads[thread_number] ,
          NULL , hit_pinata , &private_data[thread_number]);
      if (error != EXIT_SUCCESS) {
        fprintf(stderr , "Error: could not create secundary thread\n");
        return 21;
      }
    }

    for (uint64_t thread_number = 0; thread_number < share_data->thread_count
      ; ++thread_number) {
      pthread_join(threads[thread_number], /*value_ptr*/ NULL);
    }
    pthread_mutex_destroy(&share_data->can_access_position);
    free(private_data);
    free(threads);
  } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64
    "threads\n", share_data->thread_count);
    error = 22;
  }
  return error;
}

  //  Proceso el cuar es respondable de que los hilos golpeen a la piñata
  //  , ademas usa un mutex para evitar condicion de carrera y espera activa
void* hit_pinata(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*)data;
  shared_data_t* shared_data = private_data->shared_data;
  bool i_broke_pinata = false;
  bool is_pinata_alive = true;
  while (is_pinata_alive) {
    //  Genera una espera por los hilos, solo permite el ingreso de uno
    pthread_mutex_lock(&shared_data->can_access_position);
      if (shared_data->pinata_life != 0) {
        --shared_data->pinata_life;
        ++private_data->hits;
        if (shared_data->pinata_life == 0) {
          printf("Thread %" PRIu64 "/%" PRIu64 ": %" PRIu64
            " hits, I broke the pinata\n", private_data->thread_number
              , shared_data->thread_count, private_data->hits);
          i_broke_pinata = true;
          is_pinata_alive = false;
        }
      } else {
        is_pinata_alive = false;
      }
    pthread_mutex_unlock(&shared_data->can_access_position);
    //  Permite a un siguiente hilo ingresar y libera el hilo actual de mutex
  }

  if (!i_broke_pinata) {
    printf("Thread %" PRIu64 "/%" PRIu64 ": %" PRIu64 " hits\n",
      private_data->thread_number, shared_data->thread_count
        , private_data->hits);
  }
  return NULL;
}  //  end procedure
