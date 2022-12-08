// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include <stdexcept>

void* reader(void* data);
void* writer(void* data);

typedef struct {
  pthread_mutex_t* can_access_medium;
  pthread_mutex_t* can_access_reading;
  size_t* reading_count;
  size_t thread_number;
} tourniquet_t;

// procedure main:
int main() {
  try {
    // shared can_access_medium := create_semaphore(1)
    pthread_mutex_t can_access_medium;
    // shared can_access_reading := create_semaphore(1)
    pthread_mutex_t can_access_reading;
    // shared reading_count := 0
    size_t reading_count = 0;
    std::vector<pthread_t> threads;
    std::vector<tourniquet_t*> tourniquets;
    if (pthread_mutex_init(&can_access_medium, nullptr) != EXIT_SUCCESS) {
      throw std::runtime_error("because dont init mutex <can_access_medium>");
    }
    if (pthread_mutex_init(&can_access_reading, nullptr) != EXIT_SUCCESS) {
      throw std::runtime_error("because dont init mutex <can_access_reading>");
    }
    char input_case;
    // while true:
    // EOF: return
    size_t thread_count = 0;
    while (std::cin >> input_case) {
      // case read_char() of:
      // 'R': create_thread(reader)
      if (input_case == 'R' || input_case == 'W') {
        threads.push_back(pthread_t());
        tourniquets.push_back(new tourniquet_t);
        tourniquets[thread_count]->can_access_medium = &can_access_medium;
        tourniquets[thread_count]->can_access_reading = &can_access_reading;
        tourniquets[thread_count]->reading_count = &reading_count;
        tourniquets[thread_count]->thread_number = thread_count;
        if (input_case == 'R') {
          if (pthread_create(&threads.back(), nullptr, writer
            , static_cast<void*>(tourniquets[thread_count++])) != EXIT_SUCCESS) {
            throw std::runtime_error("dont init thread");
          }
        // 'W': create_thread(writer)
        } else {
          if (pthread_create(&threads.back(), nullptr, writer
            , static_cast<void*>(tourniquets[thread_count++])) != EXIT_SUCCESS) {
            throw std::runtime_error("dont init thread");
          }
        }
      }
      // end case
    }
    for (size_t index = 0; index < threads.size(); ++index) {
      if (pthread_join(threads[index], nullptr) != EXIT_SUCCESS) {
        throw std::runtime_error("dont wait threads");
      }
      delete tourniquets[index];
    }
    if (pthread_mutex_destroy(&can_access_medium) != EXIT_SUCCESS) {
      throw std::runtime_error
      ("because dont destroy mutex <can_access_medium>");
    }
    if (pthread_mutex_destroy(&can_access_reading) != EXIT_SUCCESS) {
      throw std::runtime_error
        ("because dont destroy mutex <can_access_reading>");
    }
  } catch(const std::exception& exception) {
    std::cerr << "Error: " << exception.what() << std::endl;
  }

  // end while
  return EXIT_SUCCESS;
// end procedure
}

// procedure reader:
void* reader(void* data) {
  tourniquet_t& tourniquet = *static_cast<tourniquet_t*>(data);
  // wait(can_access_reading)
  pthread_mutex_lock(tourniquet.can_access_reading);
  // reading_count := reading_count + 1
  // if reading_count = 1 then
  if (++(*tourniquet.reading_count) == 1) {
    // wait(can_access_medium)
    pthread_mutex_lock(tourniquet.can_access_medium);
  // end if
  }
  // signal(can_access_reading)
  pthread_mutex_unlock(tourniquet.can_access_reading);
  // read()
  std::cout << "Thread " << tourniquet.thread_number
    << " is reading" << std::endl;
  sleep(1);
  // wait(can_access_reading)
  pthread_mutex_lock(tourniquet.can_access_reading);
  // reading_count := reading_count - 1
  // if reading_count = 0 then
  if (--(*tourniquet.reading_count) == 0) {
    // signal(can_access_medium)
    pthread_mutex_unlock(tourniquet.can_access_medium);
  // end if
  }
  // signal(can_access_reading)
  pthread_mutex_unlock(tourniquet.can_access_reading);
  return nullptr;
// end procedure
}

// procedure writer:
void* writer(void* data) {
  tourniquet_t& tourniquet = *static_cast<tourniquet_t*>(data);
  // wait(can_access_medium)
  pthread_mutex_lock(tourniquet.can_access_medium);
  // write()
  std::cout << "Thread " << tourniquet.thread_number
    << " is writing" << std::endl;
  sleep(1);
  // signal(can_access_medium)
  pthread_mutex_unlock(tourniquet.can_access_medium);
  return nullptr;
// end procedure
}
