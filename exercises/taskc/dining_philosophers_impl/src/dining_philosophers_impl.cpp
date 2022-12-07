// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <unistd.h>
#include <queue>
#include <iostream>
#include <vector>

#include "./Mpi/Mpi.hpp"

void philosopher(Mpi& mpi, int processNumber
  , uint64_t maxTime, uint64_t minTime);
void requestChopsticks(Mpi& mpi, std::vector<int>& requestOfphilosopher);
void returnChopsticks(Mpi& mpi, std::vector<int>& requestOfphilosopher);
void waiter(Mpi& mpi);

// procedure main(argc, argv[]):
int main(int argc, char* argv[]) {
  try {
    if (argc == 3) {
      // create_process(n)
      Mpi mpi(argc, argv);
      if (mpi.getProcessCount() <= 2) {
        int processNumber = mpi.getProcessNumber();
        uint64_t maxTime = std::atol(argv[1]);
        uint64_t minTime = std::atol(argv[2]);
        // if process_number != 0 then
        if (processNumber != 0) {
          // philosopher(i)
          philosopher(mpi, processNumber, maxTime, minTime);
        // else
        } else {
          // waiter()
          waiter(mpi);
        // end if
        }
      } else {
        throw std::runtime_error("invalid count of process");
      }
    } else {
      throw std::runtime_error("invalid arguments,"
      " agrv[1] is maxTime and agrv[2] is minTime");
    }
  } catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
// end procedure
}

// procedure philosopher():
void philosopher(Mpi& mpi, int processNumber
  , uint64_t maxTime, uint64_t minTime) {
  // declare requestOfphilosopher
  std::vector<int> requestOfphilosopher(2);
  // requestOfphilosopher.philosopherNumber := process_number
  requestOfphilosopher[0] = processNumber;
  // requestOfphilosopher.requestChopstick := true
  requestOfphilosopher[1] = true;
  uint32_t seed = static_cast<uint32_t>(processNumber);
  // while true do
  while (true) {
    // think()
    std::cout << "Process " << processNumber
      << " is giving thanks" << std::endl;
    int random = minTime + (rand_r(&seed) % (maxTime - minTime));
    usleep(random);
    // requestChopsticks(requestOfphilosopher)
    requestChopsticks(mpi, requestOfphilosopher);
    // eat()
    std::cout << "Process " << processNumber
      << " is eating" << std::endl;
    random = minTime + (rand_r(&seed) % (maxTime - minTime + 1));
    usleep(random);
    returnChopsticks(mpi, requestOfphilosopher);
  // end while
  }
// end procedure
}

// procedure requestChopsticks(requestOfphilosopher):
void requestChopsticks(Mpi& mpi, std::vector<int>& requestOfphilosopher) {
  requestOfphilosopher[1] = true;
  // declare chopsticks
  int chopsticks = 1;
  // send(requestChopstick, 1, 0)
  mpi[0] << requestOfphilosopher;
  // receve(chopsticks, 1, 0)
  mpi[0] >> chopsticks;
// end procedure
}

void returnChopsticks(Mpi& mpi, std::vector<int>& requestOfphilosopher) {
  requestOfphilosopher[1] = false;
  mpi[0] << requestOfphilosopher;
}

// procedure waiter():
void waiter(Mpi& mpi) {
  // declare chopsticks
  int chopsticks = 1;
  // declare chopstick := max(n, 2)
  int chopstick = std::max(mpi.getProcessCount(), 2);
  // declare queue
  std::queue<int> requests;
  // declare requestOfphilosopher
  std::vector<int> requestOfphilosopher(2);
  // while true do
  while (true) {
    // receve(&requestOfphilosopher, 1, any_process)
    mpi[MPI_ANY_SOURCE] >> requestOfphilosopher;
    // if requestOfphilosopher.requestChopstick then
    if (requestOfphilosopher[1]) {
      // push(queue, HungryPhilosopher)
      requests.push(requestOfphilosopher[0]);
    // else
    } else {
      // chopstick += 2
      chopstick += 2;
    // end if
    }
    // if chopstick >= 2 && !Empty(queue) then
    if (chopstick >= 2 && !requests.empty()) {
      // chopstick -= 2
      chopstick -= 2;
      // send(&chopsticks, 1, pop(queue))
      mpi[requests.front()] << chopsticks;
      requests.pop();
    // end if
    }
  // end while
  }
// end procedure
}
