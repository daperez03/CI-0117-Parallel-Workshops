/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Simula compra de voletos de loteria
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * @brief Genera un numero random de loteria del 1 al 100, 
 * pero devuelve la direccion de una variable en el stack la cual se borra de manera automatica
 * 
 * @param data Semilla del time
 * @return void* Numero random obtenido
 */
void* lottery_Case1(void* data);

/**
 * @brief Genera un numero random de loteria del 1 al 100, devuelve un puntero falzo
 * 
 * @param data Semilla del time
 * @return void* Numero random obtenido
 */
void* lottery_Case2(void* data);

int main(void) {  //  hilo principal
  void* number1 = NULL;
  void* number2 = NULL;
  pthread_t thread1;  //  Designa segundo hilo
  pthread_t thread2;  //  Designa tercer hilo
  //  utiliza los hilos:
  int error1 = pthread_create(&thread1 , NULL, lottery_Case1, (void*) 1u );
  int error2 = pthread_create(&thread2 , NULL, lottery_Case1, (void*) 2u );
  //  Validacion de hilos:
  if (error1 == EXIT_SUCCESS) {
    //  Espera hilo y obtiene su valor de retorno
    pthread_join(thread1, &number1);
    printf("Boleto 1: %ld\n", (size_t)number1);
  } else {  //  En caso de error
    fprintf(stderr , "Error: could not create secundary thread\n");
  }
  if (error2 == EXIT_SUCCESS) {
    //  Espera hilo y obtiene su valor de retorno
    pthread_join(thread2, &number2);
    printf("Boleto 2: %ld\n", (size_t)number2);
  } else {  //  En caso de error
    fprintf(stderr , "Error: could not create third thread\n");
  }
}

void* lottery_Case1(void* data) {  // Retornan la dirección de memoria de la variable que tiene el número comprado.

  unsigned int* seed = (unsigned int*) data;  //  Obtiene la semilla
  size_t number = rand_r(seed) % 100 + 1;  //  Genera el numero random
  return (void*)(&number);  //  Devuelve el numero generado
}

void* lottery_Case2(void* data) {  // Retornan la dirección de memoria de la variable que tiene el número comprado.
  unsigned int seed = ((size_t)data);
  void* number = (void*)((size_t)(rand_r(&seed) % 100));  //  Genera el numero random
  return number;  //  Devuelve el numero generado
}
