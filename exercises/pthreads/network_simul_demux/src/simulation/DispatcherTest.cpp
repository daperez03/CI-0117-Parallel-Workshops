/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include "DispatcherTest.hpp"
#include "Util.hpp"

#include <iostream>

DispatcherTest::DispatcherTest(int dispatcherDelay)
  : dispatcherDelay(dispatcherDelay) {
}

int DispatcherTest::run() {
  // Dispatch all the network messages we receive to their respective queues
  this->consumeForever();

  // If we exited from the forever loop, the finish message was received
  // For this simulation is OK to propagate it to all the queues
  for ( const auto& pair : this->toQueues ) {
    pair.second->push(NetworkMessage());
  }

  return EXIT_SUCCESS;
}

void DispatcherTest::consumeForever() {
  while (true) {
  for(uint64_t index = 0; index < this->consumingQueues.size(); ++index){
      // Get the next data to consume, or block while queue is empty
      std::cout<<"Here"<<this->consumingQueues.size() <<std::endl;
      const NetworkMessage& data = this->consumingQueues[index]->pop();
      // If data is the stop condition, stop the loop
      if ( data == this->stopCondition ) {
        break;
        break;
      }
      // Process this data
      this->consume(data);
    }
  }
}

void DispatcherTest::createOwnQueues(uint64_t capacity) {
  consumingQueues.resize(capacity);
  for(uint64_t index = 0; index < capacity; ++index){
    this->consumingQueues.push_back(new Queue<NetworkMessage>());
  }
}

Queue<NetworkMessage>* DispatcherTest::getConsumingQueue(int index) {
  return this->consumingQueues[index];
}

int DispatcherTest::extractKey(const NetworkMessage& data) const {
  // Propagate a message requires time, simulate it
  // IMPORTANT: This simulation uses sleep() to mimic the process of propagating
  // a message. However, you must NEVER use sleep() for real projects
  Util::sleepFor(this->dispatcherDelay);

  // Return the target where this message is going to
  // as the key to find the queue
  return data.target;
}

