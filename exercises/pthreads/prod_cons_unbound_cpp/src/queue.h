// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

  //  This queue is thread safe

#ifndef CONSUMER_H
#define CONSUMER_H

#include <threads.h>
#include <iostream>
#include <queue>


template <class T>
class queue{
 private:
  mtx_t can_access_queue;
  std::queue<T> my_queue;

 public :
  queue() {
    if (mtx_init(&can_access_queue, mtx_plain) == thrd_error) {
      std::cerr << "Error: not init mutex\n";
    }
  }

  ~queue() {
    mtx_destroy(&can_access_queue);
  }

  int empty() {
    mtx_lock(&can_access_queue);
      int empty = my_queue.empty();
    mtx_unlock(&can_access_queue);
    return empty;
  }

  void queue_enqueue(T element) {
    mtx_lock(&can_access_queue);
      my_queue.push(element);
    mtx_unlock(&can_access_queue);
  }

  T queue_dequeue() {
    mtx_lock(&can_access_queue);
      T element = my_queue.front();
      my_queue.pop();
    mtx_unlock(&can_access_queue);
    return element;
  }
};

#endif
