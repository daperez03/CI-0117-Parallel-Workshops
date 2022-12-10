// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include "MPI_Reduce.hpp"

#include <algorithm>
#include <vector>
#include <cstdlib>

int getIndex(const std::vector<int>& vector, const int& data) {
  int index = 0;
  while (index < static_cast<int>(vector.size())
    && vector[index] != data) ++index;
  return index;
}

void operation(int MPI_OPERATION, int& object1, int object2) {
  switch (MPI_OPERATION) {
    case MPI_MIN:
      object1 = std::min(object1, object2);
      break;
    case MPI_MAX:
      object1 = std::max(object1, object2);
      break;
    case MPI_SUM:
      object1 += object2;
      break;
  }
}

void update_array(std::vector<int>& array) {
  // declare count := count(vector)
    std::vector<int> new_array;
  // for index := count to 1
  for (size_t index = 0; index < array.size(); index += 2) {
    new_array.push_back(array[index]);
    // end for
  }
  array = new_array;
}

int reduce(const int& input, int& output
  , const int MPI_OPERATION, int root) {
  int process_number = 0;
  int process_count = 0;
  int result = input;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
  MPI_Comm_size(MPI_COMM_WORLD, &process_count);
  std::vector<int> process_numbers(process_count);
  for (int index = 0; index < process_count; ++index)
    process_numbers[index] = index;

  while (true) {
    int index = getIndex(process_numbers, process_number);
    if (index % 2 == 0) {
      if (index + 1 != static_cast<int>(process_numbers.size())) {
        int new_result = 0;
        MPI_Recv(&new_result, 1, MPI_INT, process_numbers[index + 1]
          , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        operation(MPI_OPERATION, result, new_result);
      }
      if (process_numbers.size() > 2) {
        update_array(process_numbers);
      } else {
        break;
      }
    } else {
      MPI_Send(&result, 1, MPI_INT, process_numbers[index - 1]
        , 0, MPI_COMM_WORLD);
      break;
    // end if
    }
  }

  // if root != 0 && process_number == 0 then
  if (process_number == 0) {
    output = result;
    if (root != 0) {
      // send(x, count, root)
      MPI_Send(&output, 1, MPI_INT, root, 0, MPI_COMM_WORLD);
    // end if
    }
  } else if (process_number == root) {
    MPI_Recv(&output, 1, MPI_INT, 0, 0
      , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  return EXIT_SUCCESS;
// end procedure
}
