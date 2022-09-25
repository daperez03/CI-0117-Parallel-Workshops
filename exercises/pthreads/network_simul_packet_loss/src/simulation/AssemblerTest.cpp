// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#include "AssemblerTest.hpp"
#include "Util.hpp"
  //  #include <iostream>

AssemblerTest::AssemblerTest(float losingPackages, size_t consumerCount) {
  this->losingPackages = losingPackages;
  this->consumerCount = consumerCount;
}

int AssemblerTest::run() {
  consumeForever();
  return EXIT_SUCCESS;
}

void AssemblerTest::consume(NetworkMessage data) {
  const float probabilityOfLose = (Util::random(0, 100000000) / 1000000.0);
  if (probabilityOfLose > this->losingPackages) {
    int target = 1 + Util::random(0
      , static_cast<int>(this->consumerCount));
    this->producingQueue->push
      (NetworkMessage(target, data.source, data.messageNumber));
  }
}
