#include "simulation.h"

int simulation(shared_data_t* shared_data) {
  int error = EXIT_SUCCESS;
    //  crea buffer
  shared_data->buffer = (double*)
  calloc(shared_data->buffer_capacity, sizeof(double));
  if (shared_data->buffer) {
    sem_init(&shared_data->can_produce, 0
      , shared_data->buffer_capacity);
    sem_init(&shared_data->can_consume, 0, 0);
      unsigned int seed = 0u;
      //  solicita al sistema obtener una semilla en hardware
      //  GRND_NONBLOCK hace referencia a numero de entropia
    getrandom(&seed, sizeof(seed), GRND_NONBLOCK);
    srandom(seed);  //  se utiliza la semilla

    struct timespec start_time;
    clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &start_time);

      // crea hilos
    error = create_threads(shared_data);

    struct timespec finish_time;
    clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &finish_time);

    double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
    printf("execution time: %.9lfs\n", elapsed);
    sem_destroy(&shared_data->can_consume);
    sem_destroy(&shared_data->can_produce);
    free(shared_data->buffer);
  } else {
    fprintf(stderr, "error: could not create buffer\n");
    error = ERR_NOMEM_BUFFER;
  }
  return error;
}

int create_threads(shared_data_t* shared_data) {
  assert(shared_data);
  int error = EXIT_SUCCESS;
  //  Hilos productor y consumidor
  pthread_t producer, consumer;
  error = pthread_create(&producer, /*attr*/ NULL, produce, shared_data);
  if (error == EXIT_SUCCESS) {
    error = pthread_create(&consumer, /*attr*/ NULL, consume, shared_data);
    if (error != EXIT_SUCCESS) {
      fprintf(stderr, "error: could not create consumer\n");
      error = ERR_CREATE_THREAD;
    }
  } else {
    fprintf(stderr, "error: could not create producer\n");
    error = ERR_CREATE_THREAD;
  }

  if (error == EXIT_SUCCESS) {
    pthread_join(producer, /*value_ptr*/ NULL);
    pthread_join(consumer, /*value_ptr*/ NULL);
  }

  return error;
}

useconds_t random_between(useconds_t min, useconds_t max) {
  return min + (max > min ? (random() % (max - min)) : 0);
}