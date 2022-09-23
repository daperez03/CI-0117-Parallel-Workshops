// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

  //  This queue is thread safe

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <semaphore.h>
#include <stdbool.h>

#include <iostream>
#include <mutex>
#include <queue>

template <typename DataType>
class Queue{
 protected:
  std::mutex mutex;
  sem_t canConsume;
  std::queue<DataType> queue;

 public :
  Queue() {
    if (sem_init(&canConsume, 0, 0) != EXIT_SUCCESS) {
      std::cerr << "Error: not init mutex\n";
    }
  }

  ~Queue() {
    sem_destroy(&canConsume);
  }

  bool empty() {
    this->mutex.lock();
      bool empty = queue.empty();
    this->mutex.unlock();
    return empty;
  }

  void enqueue(const DataType& data) {
    this->mutex.lock();
      queue.push(data);
    this->mutex.unlock();
    sem_post(&this->canConsume);
  }

  DataType dequeue() {
    sem_wait(&this->canConsume);
    this->mutex.lock();
      DataType result = this->queue.front();
      this->queue.pop();
    this->mutex.unlock();
    return result;
  }
};

#endif
