// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#include "AssemblerTest.hpp"
#include "Util.hpp"
  //  #include <iostream>

AssemblerTest::AssemblerTest(float losingPackages, size_t consumerCount) {
  this->losingPackages = losingPackages;
  this->consumerCount = consumerCount;
}

int AssemblerTest::run() {
  assert(this->consumingQueue);
  while (true) {
      // Get the next data to consume, or block while queue is empty
    const NetworkMessage& data = this->consumingQueue->pop();
      // If data is the stop condition, stop the loop
    if ( data == this->stopCondition ) {
      break;
    }
    const float probabilityOfLose =
        1 + (Util::random(0, 9999999) / 100000.0);
    if (probabilityOfLose > this->losingPackages) {
      int target = 1 + Util::random(0
        , static_cast<int>(this->consumerCount));
      this->producingQueue->push
        (NetworkMessage(target, data.source, data.messageNumber));
    }  //  else {
        //  std::cout << probabilityOfLose << "-"
          //  <<this->losingPackages<< std::endl;
      //  }
  }
  return 0;
}
