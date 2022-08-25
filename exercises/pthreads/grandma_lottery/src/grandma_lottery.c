#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void* loterry(void* data);

int main(void) {
  time_t seed = time(NULL);
  void* number1 = NULL;
  void* number2 = NULL;
  pthread_t thread1;  //  Designa primer hilo
  pthread_t thread2;  //  Designa segundo hilo
  int error1 = pthread_create(&thread1 , NULL, loterry, &seed);
  int error2 = pthread_create(&thread2 , NULL, loterry, &seed);
  if(error1 == EXIT_SUCCESS) {
    pthread_join(thread1, &number1);
    printf("Boleto 1: %i\n", *(int*)number1);
  }else{
    fprintf(stderr , "Error: could not create secundary thread\n");
  }
  if(error2 == EXIT_SUCCESS) {
    pthread_join(thread2, &number2);
    printf("Boleto 2: %i\n", *(int*)number2);
  }else{
    fprintf(stderr , "Error: could not create third thread\n");
  }
}

void* loterry(void* data) {
  unsigned int* seed = (unsigned int*) data;
  int number = rand_r(seed) % 100 + 1;
  int* numberP = (int*)calloc(1, sizeof(int));
  *numberP = number;
  return (void*)numberP;
}
