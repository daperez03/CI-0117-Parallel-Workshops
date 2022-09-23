// Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4

#ifndef ASSEMBLERTEST_HPP
#define ASSEMBLERTEST_HPP

#include "ConsumerTest.hpp"
#include "ProducerTest.hpp"

class AssemblerTest
  : public ConsumerTest
    , public ProducerTest {
 private:
  float losingPackages;
 public:
  AssemblerTest(float losingPackages, size_t consumerCount);
  int run() override;
};

#endif
