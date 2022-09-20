#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <cassert>

#include "Queue.hpp"
#include "Thread.hpp"

template <typename DataType>
class Producer : public virtual Thread {

 protected:
  Queue<DataType>* producingQueue;

 public:
  explicit Producer(Queue<DataType>* producingQueue = nullptr)
    : producingQueue(producingQueue) {
  }

  virtual ~Producer(){}

  inline Queue<DataType>* get

  inline void setProducingQueue(Queue<DataType>* producingQueue) {
    this->producingQueue = producingQueue;
  }

  virtual void produce(const DataType& data) {
    assert(this->producingQueue);
    this->producingQueue->push(data);
  }

};

#endif
