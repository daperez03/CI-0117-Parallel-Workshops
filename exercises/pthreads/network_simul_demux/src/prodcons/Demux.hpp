/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <exception>
#include <map>
#include <vector>

#include "Consumer.hpp"
#include "Semaphore.hpp"

/**
 * @brief A demux is both, a consumer of its own queue, and a producer
 * for many queues. For each data that is pushed to its queue, the demux
 * distributes the data to another queues, using key-values
 */
template <typename KeyType, typename DataType>
class Demux : public Consumer<DataType> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(Demux);

 protected:
  /// Alias to the inherited queue for a more meaninguful identifier
  std::vector<Queue<DataType>*> fromQueues;

  /// This thread will distribute elements to the following queues
  Queue<DataType>* toQueue;

  Semaphore canConsume;

  int producerCount;
  bool ownsQueues = false;

 public:
  /// Constructor
  explicit Demux(Queue<DataType>* consumingQueue = nullptr
    , const DataType& stopCondition = DataType()
    , bool createOwnQueue = false)
    : Consumer<DataType>(consumingQueue, stopCondition, createOwnQueue) {
  }

  /// Destructor
  virtual ~Demux() {
    if (this->ownsQueues) {
      for (int64_t i = 0; i < this->producerCount; i++)
        delete this->fromQueues[i];
    }
  }

  /// Register a map. When the data to be consumed has this key, it will be
  /// redirected to the the given queue
  inline void setToQueue(Queue<DataType>* toQueue) {
    this->toQueue = toQueue;
  }

  void createOwnQueues() {
    for (int64_t i = 0; i < this->producerCount; i++) {
      this->fromQueues.push_back(new Queue<DataType>());
    }
    this->ownsQueues = true;
  }

  inline Queue<DataType>* getConsumingQueues(int i) {
    return this->fromQueues[i];
  }

  inline Semaphore* getCanConsume() {
    return &this->canConsume;
  }

  /// Override this method to process any data extracted from the queue
  void consume(DataType data) override {
    toQueue->push(data);
  }

  void consumeForever() override {
    DataType caseDefault;
    while (true) {
      // std::cout << "here" << std::endl;
      DataType& data = caseDefault;
      this->canConsume.wait();
      // Get the next data to consume, or block while queue is empty
      for (int64_t i = 0; i < this->producerCount; ++i) {
        if (!this->fromQueues[i]->isEmpty()) {
          //  std::cout<<"Here"<<std::endl;
          data = this->fromQueues[i]->pop();
          break;
        }
      }
      // If data is the stop condition, stop the loop
      if ( data == this->stopCondition ) {
        break;
      }
      // Process this data
      this->consume(data);
    }
  }


  /// Override this method to extract the key from a data stored in fromQueue
  virtual KeyType extractKey(const DataType& data) const = 0;
};

#endif  // DISPATCHER_HPP
