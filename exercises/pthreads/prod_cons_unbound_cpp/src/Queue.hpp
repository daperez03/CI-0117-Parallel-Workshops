// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

  //  This queue is thread safe

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <mutex>
#include <queue>
#include <semaphore.h>

template <typename DataType>
class Queue{

 protected:
  std::mutex mutex; 
  sem_t canConsume; 
  std::queue<DataType> queue;

 public :
  Queue() {
    if (sem_init(&canConsume, NULL, 0) != EXIT_SUCCESS) {
      std::cerr << "Error: not init mutex\n";
    }
  }

  ~Queue() {
    sem_destroy(&canConsume);
  }

  int empty() {
    mtx_lock(&can_access_queue);
      int empty = my_queue.empty();
    mtx_unlock(&can_access_queue);
    return empty;
  }

  void enqueue(const DataType& data) {
    this.mutex.lock();
      queue.push(element);
    this->mutex.unlock();
    sem_post(&this.canConsume);
  }

  DataType dequeue() {
    sem_wait(&this.canConsume);
    this.mutex.lock();
      DataType result = this.queue.front();
      this.queue.pop();
    this->mutex.unlock();
    return element;
  }
};

#endif
