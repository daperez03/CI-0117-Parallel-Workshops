/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include <cstdlib>
#include <iostream>
#include <mutex>

#include "ProducerConsumerTest.hpp"
#include "ConsumerTest.hpp"
#include "DemuxTest.hpp"
#include "ProducerTest.hpp"

const char* const usage =
  "Usage: prodcons packages consumers prod_delay disp_delay cons_delay\n"
  "\n"
  "  packages    number of packages to be produced\n"
  "  producers   number of producers threads\n"
  "  prod_delay  delay of producer to create a package\n"
  "  disp_delay  delay of demux to dispatch a package\n"
  "  cons_delay  delay of consumer to consume a package\n"
  "\n"
  "Delays are in millisenconds, negatives are maximums for random delays\n";

ProducerConsumerTest::~ProducerConsumerTest() {
  for ( ProducerTest* producer : this->producers )
    delete producer;
  delete this->demux;
  for ( ConsumerTest* consumer : this->consumers )
    delete consumer;
}

int ProducerConsumerTest::start(int argc, char* argv[]) {
  // Parse arguments and store values in object members
  if ( int error = this->analyzeArguments(argc, argv) ) {
    return error;
  }
  this->consumerCount = 1;
  // Create objects for the simulation
  this->demux = new DemuxTest
    (this->dispatcherDelay, this->producerCount);
  this->demux->createOwnQueues();
  this->producers.resize(this->producerCount);
  size_t productionCount = 0;
  std::mutex mutex;
  for ( size_t index = 0; index < this->producerCount; ++index ) {
    this->producers[index] = new ProducerTest
      (this->packageCount, this->productorDelay,
        this->consumerCount, &productionCount, &mutex);
    assert(this->producers[index]);
    this->producers[index]->setProducingQueue
      (this->demux->getConsumingQueues(index));
  }
  // Create each producer
  this->consumers.resize(this->consumerCount);
  for ( size_t index = 0; index < this->consumerCount; ++index ) {
    this->consumers[index] = new ConsumerTest(this->consumerDelay);
    assert(this->consumers[index]);
    this->consumers[index]->createOwnQueue();
  }
  // Communicate simulation objects
  // Producer push network messages to the demux queue
  // Dispatcher delivers to each consumer, and they should be registered
  for ( size_t index = 0; index < this->consumerCount; ++index ) {
    this->demux->registerRedirect(index + 1
      , this->consumers[index]->getConsumingQueue());
  }

  // Start the simulation
  for ( size_t index = 0; index < this->producerCount; ++index ) {
    this->producers[index]->startThread();
  }
  this->demux->startThread();
  for ( size_t index = 0; index < this->consumerCount; ++index ) {
    this->consumers[index]->startThread();
  }

  // Wait for objets to finish the simulation
  for ( size_t index = 0; index < this->producerCount; ++index ) {
    this->producers[index]->waitToFinish();
  }
  this->demux->waitToFinish();
  for ( size_t index = 0; index < this->consumerCount; ++index ) {
    this->consumers[index]->waitToFinish();
  }

  // Simulation finished
  return EXIT_SUCCESS;
}

int ProducerConsumerTest::analyzeArguments(int argc, char* argv[]) {
  // 5 + 1 arguments are mandatory
  if ( argc != 6 ) {
    std::cout << usage;
    return EXIT_FAILURE;
  }

  int index = 1;
  this->packageCount = std::strtoull(argv[index++], nullptr, 10);
  this->producerCount = std::strtoull(argv[index++], nullptr, 10);
  this->productorDelay = std::atoi(argv[index++]);
  this->dispatcherDelay = std::atoi(argv[index++]);
  this->consumerDelay = std::atoi(argv[index++]);

  // todo: Validate that given arguments are fine
  return EXIT_SUCCESS;
}
