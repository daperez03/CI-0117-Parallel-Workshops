// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <cstdlib>
#include <iostream>
#include  "../../Mpi.hpp"

void analyseArguments(int argc, char* argv[], uint64_t& cota
  , double* efectividadJugador) {
  if (argc == 4) {
    cota = static_cast<uint64_t>(atoi(argv[1]));
    efectividadJugador[0] = atof(argv[2]);
    efectividadJugador[1] = atof(argv[3]);
  } else {
    throw std::runtime_error("cloud arguments is invalid");
  }
}

int main(int argc, char* argv[]) {
  try {
    uint64_t cota = 0;
    double efectividadJugador[2] = {0};
    analyseArguments(argc, argv, cota, efectividadJugador);
    Mpi mpi(argc, argv);
    if (mpi.getProcessCount() == 2) {
      int processNumber = mpi.getProcessNumber();
      uint64_t wins = 0;
      uint64_t set = 0;
      uint32_t seed = static_cast<uint32_t>(processNumber);
      while (set < 3) {
        uint64_t points = 0;
        uint64_t passes = 0;
        // Saque libre
        if (processNumber == 0) {
          mpi[!processNumber] << 0;
        }
        while (points != cota) {
          int ball = 0;
          // Se recive pelota
          mpi[!processNumber] >> ball;
          if (ball == 2) {
            // Si rival gano me salgo
            break;
          } else if (ball == 1) {
            // Sumo puntos
            points += ball;
          }
          if (points != cota) {
            ++passes;
            // Indica si el jugador fallo o no
            ball = !((rand_r(&seed) % 101) < efectividadJugador[processNumber]);
            mpi[!processNumber] << ball;
          }
        }
        if (points == cota) {
          std::cout << set + 1 << ": " << passes << " "
            << processNumber << std::endl;
          mpi[!processNumber] << 2;
          ++wins;
        }
        ++set;
      }
      if (wins > 1) {
        std::cout << processNumber << " wins " << wins
          << " to " << 3 - wins << std::endl;
      }
    } else {
      throw std::runtime_error("cloud process count is invalid");
    }
  }
  catch(const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }
}
