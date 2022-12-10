// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#include <iostream>
#include <vector>
#include <queue>

typedef struct {
  sem_t wait_female;
  sem_t wait_male;
  size_t there_number_male;
  size_t there_number_female;
} peer;


// male:
void* male(void* data) {
  peer& my_peer = *static_cast<peer*>(data);
  sem_post(&my_peer.wait_male);
  sem_wait(&my_peer.wait_female);
  // dance()
  std::cout << "Thread male " << my_peer.there_number_male
    << " dancing with thread female " << my_peer.there_number_female
    << std::endl;
  return nullptr;
}

// female:
void* female(void* data) {
  peer& my_peer = *static_cast<peer*>(data);
  sem_post(&my_peer.wait_female);
  sem_wait(&my_peer.wait_male);
  // dance()
  std::cout << "Threathreadd female " << my_peer.there_number_female
    << " dancing with  male " << my_peer.there_number_male
    << std::endl;
  return nullptr;
}

// main:
int main() {
  // while true:
  char option;
  size_t thread_count = 0;
  std::vector<pthread_t> threads;
  std::vector<peer*> peers;
  std::queue<peer*> pending_peer_Male;
  std::queue<peer*> pending_peer_Female;
  std::cout << "Write M or W to create a dancer male or women" << std::endl;
  while (std::cin >> option) {
    // case read_char() of:
    if (option == 'M') {
      threads.push_back(pthread_t());
      peer* my_peer = nullptr;
      if (pending_peer_Female.empty()) {
        my_peer = new peer();
        sem_init(&my_peer->wait_male, 0, 0);
        sem_init(&my_peer->wait_female, 0, 0);
        peers.push_back(my_peer);
        pending_peer_Male.push(my_peer);
      } else {
        std::cout << "Here" << std::endl;
        my_peer = pending_peer_Female.front();
        pending_peer_Female.pop();
      }
      my_peer->there_number_male = thread_count++;
      // 'M': create_thread(male)
      pthread_create(&threads.back(), nullptr, male, my_peer);
    } else if (option == 'W') {
      threads.push_back(pthread_t());
      peer* my_peer = nullptr;
      if (pending_peer_Male.empty()) {
        my_peer = new peer();
        sem_init(&my_peer->wait_male, 0, 0);
        sem_init(&my_peer->wait_female, 0, 0);
        peers.push_back(my_peer);
        pending_peer_Female.push(my_peer);
      } else {
        my_peer = pending_peer_Male.front();
        pending_peer_Male.pop();
      }
      my_peer->there_number_female = thread_count++;
      // 'W': create_thread(female)
      pthread_create(&threads.back(), nullptr, female, my_peer);
    }
  }
  for (size_t i = 0; i < threads.size(); ++i)
    pthread_join(threads[i], nullptr);
  for (size_t i = 0; i < peers.size(); ++i) {
    sem_destroy(&peers[i]->wait_male);
    sem_destroy(&peers[i]->wait_female);
    delete peers[i];
  }
  return EXIT_SUCCESS;
  // EOF: return
}
