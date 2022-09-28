/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include "ProducerTest.hpp"
#include "Log.hpp"
#include "Util.hpp"

ProducerTest::ProducerTest(size_t packageCount, int productorDelay
  , size_t consumerCount, size_t* productionCount
    , std::mutex* canAccessProduction)
  : packageCount(packageCount)
  , productorDelay(productorDelay)
  , consumerCount(consumerCount)
  , productionCount(productionCount)
  ,canAccessProduction(canAccessProduction){
}

int ProducerTest::run() {
  // Produce each asked message
  while (true) {
    this->canAccessProduction->lock();
    if(*this->productionCount >= this->packageCount) {
      this->canAccessProduction->unlock();
      break;
    }
    ++(*this->productionCount);
    this->canAccessProduction->unlock();
    this->produce(this->createMessage(this->myPackageCount));
    ++this->myPackageCount;
  }
  // Produce an empty message to communicate we finished
  this->produce(NetworkMessage());

  // Report production is done
  Log::append(Log::INFO, "Producer", std::to_string(this->myPackageCount)
    + " menssages sent");
  return EXIT_SUCCESS;
}

NetworkMessage ProducerTest::createMessage(size_t index) const {
  // Source is always 1: this producer
  const uint16_t source = 1;
  // Target is selected by random
  const uint16_t target = 1 + Util::random(0
    , static_cast<int>(this->consumerCount));
  // IMPORTANT: This simulation uses sleep() to mimics the process of
  // producing a message. However, you must NEVER use sleep() for real projects
  Util::sleepFor(this->productorDelay);
  // Create and return a copy of the network message
  return NetworkMessage(target, source, index);
}
