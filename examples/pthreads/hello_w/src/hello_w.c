/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
  //  #include <unistd.h>

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
  for(int index = 0; index < argc; ++index) {
    // imprime argumentos ingresados por el usuario
    printf("argv[%d] = '%s'\n", index, argv[index]);
  }
#endif
  int error = EXIT_SUCCESS;
  //  thread_count := integer(argv[1])
  long thread_count =  0; // strol(argv[1], .....)
  //Escanea vector
  if(sscanf(argv[1], "%ld", &thread_count) == 1) {
    // for thread_number := 0 to thread_count do
    for(long thread_number = 0; thread_number < thread_count; ++thread_number) {
      //  create_thread(great(), thread_number)
      pthread_t thread;
      //  CREA HILO SECUNDARIO
      error = pthread_create(&thread , /*attr*/ NULL , greet , (void*)thread_number);
      if (error == EXIT_SUCCESS) {
        //  print "Hello from main thread"
        // usleep(2);  //  indeterminismo
        printf("Hello from main thread\n");
        pthread_join(thread, /*value_ptr*/ NULL);  //  ENVIA A DORMIR HILO PRINCIPAL
      } else {
        fprintf(stderr , "Error: could not create secundary thread\n");
      }
    }
  } else {
    fprintf(stderr , "Error: invalid thread count\n");
    error = EXIT_FAILURE;
  }
  return error;
}  //  end procedure

//  procedure great():

void* greet(void* data) {
  const long rank = (long)data;
  //  print "Hello from secundary thread"
  printf("Hello from secundary thread %ld\n", rank);
  return NULL;
}  //  end procedure
