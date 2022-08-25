/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief  Genera un mensaje en la salida standar
 * 
 * @param data NULL
 * @return void* NULL
 */
void* greet(void* data);

//  procedure main():
int main(void) {
  const size_t greet_number = 2;
  //  create_thread(great())
  pthread_t thread;
  //  CREA HILO SECUNDARIO
  int error = pthread_create(&thread , /*attr*/NULL,
  greet, (void*)greet_number);
  if (error == EXIT_SUCCESS) {
    //  print "Hello from main thread"
    printf("Hello from main thread\n");
    pthread_join(thread, /*value_ptr*/NULL);  //  ENVIA A DORMIR HILO PRINCIPAL
  } else {
    fprintf(stderr , "Error: could not create secundary thread\n");
  }
  return error;
}  //  end procedure

//  procedure great():

void * greet(void* data) {
  const size_t greet_number = (size_t) data;
  int error = 0;
  pthread_t thread;
  if (greet_number == 0) {
    printf("Bye\nNumber: %zu\n" , greet_number);
  } else if (greet_number > 0) {
    printf("Hello from secundary thread\nNumber: %zu\n"
     , greet_number);
    error = pthread_create(&thread , /*attr*/NULL ,
    greet , (void*)greet_number - 1);
    if (error == EXIT_SUCCESS) {
      pthread_join(thread, /*value_ptr*/NULL);
    } else {
      fprintf(stderr , "Error: could not create secundary thread\n");
    }
  } else {
    fprintf(stderr , "Error: Out of range number\n");
  }
  return NULL;
}   //  end procedure
