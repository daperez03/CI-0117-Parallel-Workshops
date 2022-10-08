/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef PRODUCERCONSUMERTEST_HPP
#define PRODUCERCONSUMERTEST_HPP

#include <cstddef>
#include <vector>

#include "common.hpp"

// Forward declarations
class ConsumerTest;
class DemuxTest;
class ProducerTest;

/**
 * @brief Controller class that simulates the message passing between
 * producer and cosumers through a demux
 */
class ProducerConsumerTest {
  DISABLE_COPY(ProducerConsumerTest);

 private:
  /// Number of packages to be produced
  size_t packageCount = 0;
  /// Number of producer threads
  size_t producerCount = 0;
  /// Number of consumer threads
  /// Delay of producer to create a package, negative for max random
  int productorDelay = 0;
  /// Delay of demux to dispatch a package, negative for max random
  int dispatcherDelay = 0;
  /// Delay of consumer to consume a package, negative for max random
  int consumerDelay = 0;

 private:
  /// Producers of the simulated network messages
  std::vector<ProducerTest*> producers;
  /// A demux of the of the simulated network messages
  DemuxTest* demux = nullptr;
  /// Consumers of the simulated network messages
  ConsumerTest* consumer;

 public:
  /// Constructor
  ProducerConsumerTest() = default;
  /// Destructor
  ~ProducerConsumerTest();
  /// Start the simulation
  int start(int argc, char* argv[]);

 private:
  /// Analyze the command line arguments
  int analyzeArguments(int argc, char* argv[]);
};

#endif  // PRODUCERCONSUMERTEST_HPP
