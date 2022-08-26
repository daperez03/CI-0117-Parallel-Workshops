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

//  procedure main():
int main(void) {
  //  create_thread(great())
  pthread_t thread;
  //  CREA HILO SECUNDARIO
  int error = pthread_create(&thread , /*attr*/ NULL , greet , /*arg*/ NULL);
  if (error == EXIT_SUCCESS) {
    //  print "Hello from main thread"
    // usleep(2);  //  indeterminismo
    printf("Hello from main thread\n");
    pthread_join(thread, /*value_ptr*/ NULL);  //  ENVIA A DORMIR HILO PRINCIPAL
  } else {
    fprintf(stderr , "Error: could not create secundary thread\n");
  }
  return error;
}  //  end procedure

//  procedure great():

void* greet(void* data) {
  (void)data;
  //  print "Hello from secundary thread"
  printf("Hello from secundary thread\n");
  return NULL;
}  //  end procedure
