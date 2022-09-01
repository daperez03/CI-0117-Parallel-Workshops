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

/**
 * Aca se documenta las clase
 * @brief  Genera un mensaje en la salida standar
 * 
 * @param data NULL
 * @return void* NULL
 */
void* greet(void* data);

//  procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  #if 0
    Mecanismo espacial para omitir interpretacion de codigo
    //  Ejemplo sobre los argumentos en c
    for (int index = 0; index < argc; ++index) {
      // imprime argumentos ingresados por el usuario
      printf("argv[%d] = '%s'\n", index, argv[index]);
    }
  #endif
  int error = EXIT_SUCCESS;
  //  thread_count := integer(argv[1])
  uint64_t thread_count =  sysconf(_SC_NPROCESSORS_ONLN);
  //  strol(argv[1], .....) //strtol(string): convierte de string a long
  //  Escanea vector
  //  assert(argc == 2);
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) != 1) {
      fprintf(stderr , "Error: invalid thread count\n");
      error = EXIT_FAILURE;
    }
  }

  //  for thread_number := 0 to thread_count do
  pthread_t* threads = (pthread_t*)
  malloc(thread_count * sizeof(pthread_t));

  if (threads) {
    for (uint64_t thread_number = 0; thread_number < thread_count;
    ++thread_number) {
      //  create_thread(great(), thread_number)
      //  CREA HILO SECUNDARIO
      error = pthread_create(&threads[thread_number] ,
      /*attr*/ NULL , greet , (void*)thread_number);
      if (error == EXIT_SUCCESS) {
      } else {
        fprintf(stderr , "Error: could not create secundary thread\n");
      }
    }

    printf("Hello from main thread\n");
    for (uint64_t thread_number = 0; thread_number < thread_count;
    ++thread_number) {
      //  usleep(2);  //  indeterminismo
      //  ENVIA A DORMIR HILO PRINCIPAL
      pthread_join(threads[thread_number], /*value_ptr*/ NULL);
    }

      //  print "Hello from main thread"
    free(threads);
  } else {

    fprintf(stderr, "Error: could not allocate %" PRIu64
    "threads\n", thread_count);
    error = EXIT_FAILURE;

  }
  return error;
}  //  end procedure

  //  procedure great():

void* greet(void* data) {
  const uint64_t rank = (uint64_t)data;
  //  print "Hello from secundary thread"
  printf("Hello from secundary thread %" PRIu64 "\n", rank);
  return NULL;
}  //  end procedure
