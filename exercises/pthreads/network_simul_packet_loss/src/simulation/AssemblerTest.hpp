// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#ifndef ASSEMBLERTEST_HPP
#define ASSEMBLERTEST_HPP

#include "./prodcons/Assembler.hpp"
#include "ProducerTest.hpp"

class AssemblerTest
  : public Assembler<NetworkMessage, NetworkMessage> {
 private:
  float losingPackages;
  size_t consumerCount;
 public:
  AssemblerTest(float losingPackages, size_t consumerCount);
  int run() override;
  void consume(NetworkMessage data) override;
};

#endif
