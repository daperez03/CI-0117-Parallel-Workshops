/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/

#include <chrono>
#include <inttypes.h>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <thread>
#include <vector>

  //  thread_shared_data_t
typedef struct shared_data {
  uint64_t thread_count;
} share_data_t;

  //  thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;
  std::shared_ptr<share_data_t> shared_data;
} private_data_t;

int create_threads(std::shared_ptr<share_data_t> share_data);
int greet(std::shared_ptr<private_data_t> private_data);

//  procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  //  thread_count := integer(argv[1])
  uint64_t thread_count =  std::thread::hardware_concurrency();
  //  strol(argv[1], .....) //strtol(string): convierte de string a long
  //  Escanea vector
  //  assert(argc == 2);
  if (argc == 2) {
    std::istringstream get(argv[1]);
    try
    {
      get >> thread_count;
    }
    catch(...) {
      std::cerr <<  "Error: invalid thread count\n";
      error = 11;
    }
  }

  std::shared_ptr<share_data_t> share_data(new share_data_t);
  if (share_data) {
    share_data->thread_count = thread_count;
    auto start = std::chrono::high_resolution_clock::now();
    error = create_threads(share_data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time of the process: "<< diff.count() << " s\n";
  } else {
    std::cerr << "Error: could not allocate shared data\n";
    error = 12;
  }
  return error;
}  //  end procedure


int create_threads(std::shared_ptr<share_data_t> share_data) {
  int error = EXIT_SUCCESS;
  std::vector<std::thread> threads;
  std::vector<private_data_t> private_data(share_data->thread_count);
  if (1) {
    for (uint64_t thread_number = 0; thread_number < share_data->thread_count
      ; ++thread_number) {
        private_data[thread_number].thread_number = thread_number;
        private_data[thread_number].shared_data = share_data;
      //  create_thread(great(), thread_number)
      //  CREA HILO SECUNDARIO
      threads.emplace_back(std::thread(greet, private_data[thread_number]));
      if (error != EXIT_SUCCESS) {
        std::cerr << "Error: could not create secundary thread\n";
        error = 21;
      }
    }

    std::cout << "Hello from main thread\n";
    for (uint64_t thread_number = 0; thread_number < share_data->thread_count
      ; ++thread_number) {
      //  usleep(2);  //  indeterminismo
      //  ENVIA A DORMIR HILO PRINCIPAL
      threads[thread_number].join();
    }
      //  print "Hello from main thread"
  } else {
    std::cerr << "Error: could not allocate " << share_data->thread_count <<
    "threads\n";
    error = 22;
  }
  return error;
}


  //  procedure great():
int greet(std::shared_ptr<private_data_t> private_data) {
  std::shared_ptr<share_data_t> shared_data = private_data->shared_data;
  //  print "Hello from secundary thread"
  std::cout << "Hello from secundary thread " << private_data->thread_number <<" of " << shared_data->thread_count <<"\n";
  return EXIT_SUCCESS;
}  //  end procedure
