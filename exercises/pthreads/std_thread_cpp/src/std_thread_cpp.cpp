/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/

#include <chrono>
#include <iostream>
#include <sstream>
#include <memory>
#include <thread>
#include <vector>


  //  thread_shared_data_t
typedef struct shared_data {
  uint64_t thread_count;
} shared_data_t;

  //  thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;
  std::shared_ptr<shared_data_t> shared_data;
} private_data_t;

int create_threads(std::shared_ptr<shared_data_t> shared_data);
int greet(void* data);

//  procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  //  thread_count := integer(argv[1])
  uint64_t thread_count =  std::thread::hardware_concurrency();
  //  strol(argv[1], .....) //strtol(string): convierte de string a long
  //  Escanea vector
  //  assert(argc == 2);
  if (argc == 2) {
    try {
      std::istringstream get(argv[1]);
      get >> thread_count;
      if (get.fail()) {
        std::cerr <<  "Error: invalid thread count\n";
        error = 11;
      }
    } catch(...) {
      std::cerr <<  "Error: invalid parameter removals\n";
    }
  }
  try {
    std::shared_ptr<shared_data_t> share_data_ptr(new shared_data_t);
    if (share_data_ptr) {
      share_data_ptr->thread_count = thread_count;

      auto start = std::chrono::high_resolution_clock::now();

      error = create_threads(share_data_ptr);

      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff = end - start;

      std::cout << "Time of the process: "<< diff.count() << " s\n";
    } else {
      std::cerr << "Error: could not allocate shared data\n";
      error = 12;
    }
  } catch (...) {
    std::cerr << "Error: could not allocate shared data\n";
  }
  return error;
}  //  end procedure


int create_threads(std::shared_ptr<shared_data_t> shared_data_ptr) {
  int error = EXIT_SUCCESS;
  std::vector<std::thread> threads;
  std::vector<private_data_t> private_data(shared_data_ptr->thread_count);
  for (uint64_t thread_number = 0; thread_number <
    shared_data_ptr->thread_count; ++thread_number) {
      private_data[thread_number].thread_number = thread_number;
      private_data[thread_number].shared_data = shared_data_ptr;
    //  create_thread(great(), thread_number)
    //  CREA HILO SECUNDARIO
    try {
      threads.emplace_back(std::thread(greet, &private_data[thread_number]));
     } catch (...) {
      std::cerr << "Error: could not create secundary thread\n";
    }
  }

  std::cout << "Hello from main thread\n";
  for (uint64_t thread_number = 0; thread_number < shared_data_ptr->thread_count
    ; ++thread_number) {
    //  usleep(2);  //  indeterminismo
    //  ENVIA A DORMIR HILO PRINCIPAL
    threads[thread_number].join();
  }
    //  print "Hello from main thread"
  return error;
}


  //  procedure great():
int greet(void* data) {
  private_data_t* private_data = reinterpret_cast<private_data_t*> (data);
  std::shared_ptr<shared_data_t> shared_data = private_data->shared_data;
  //  print "Hello from secundary thread"
  std::cout << "Hello from secundary thread " << private_data->thread_number
  << " of " << shared_data->thread_count <<"\n";
  return EXIT_SUCCESS;
}  //  end procedure
