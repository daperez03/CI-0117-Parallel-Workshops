// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#ifndef MPI_HPP
#define MPI_HPP
#include <mpi.h>
#include <cassert>
#include <string>
#include <vector>
#include "MpiError.hpp"

class Mpi {
 protected:
  /// @brief process hostname
  std::string process_hostname;
  /// @brief process number
  int process_number = 0;
  /// @brief process count
  int process_count = 0;

 public:
  /// @brief Generic MPI constructor
  /// @param argc Arguments count
  /// @param argv Arguments value
  Mpi(int& argc, char**& argv) {
    assert(argv);
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
      throw MpiError(ERROR_01);
    } else {
      if (MPI_Comm_rank(MPI_COMM_WORLD, &this->process_number) != MPI_SUCCESS) {
        throw MpiError(ERROR_02);
      } else {
        if (MPI_Comm_size(MPI_COMM_WORLD, &this->process_count)
          != MPI_SUCCESS) {
          throw MpiError(ERROR_03);
        } else {
          char process_hostname[MPI_MAX_PROCESSOR_NAME] = {0};
          int hostname_length = -1;
          if (MPI_Get_processor_name(process_hostname, &hostname_length)
            != MPI_SUCCESS) {
            throw MpiError(ERROR_04);
          } else {
            this->process_hostname = std::string(process_hostname);
          }
        }
      }
    }
  }

  /// @brief Generic MPI destructor
  ~Mpi() {
    MPI_Finalize();
  }

  /// @brief Get the number of the process in progress
  /// @return number of the process
  int getProcessNumber() const {
    return process_number;
  }

  /// @brief Get the count of the process in progress
  /// @return count of the process
  int getProcessCount() const {
    return process_count;
  }

  /// @brief Get the current hostname
  /// @return current hostname
  std::string getHostname() const {
    return process_hostname;
  }

  /// @brief Send data through MPI_Send
  /// @tparam Type generic value
  /// @param value Value sent
  /// @param toProcess Process number to be sent
  /// @param tag Tag to send
  template<typename Type>
  void send(const Type& value, int toProcess, int tag = 0) {
    if (MPI_Send(&value, 1, this->map(Type()), toProcess, tag
      , MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw MpiError(ERROR_05, (*this));
    }
  }

  /// @brief Send vector data through MPI_Send
  /// @tparam Type generic value
  /// @param values Values sent
  /// @param count Count of values
  /// @param toProcess Process number to be sent
  /// @param tag Tag to send
  template<typename Type>
  void send(const Type* values, int count, int toProcess, int tag = 0) {
    if (MPI_Send(values, count, this->map(Type()), toProcess, tag
      , MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw MpiError(ERROR_05, (*this));
    }
  }

  /// @brief Send std::vector data through MPI_Send
  /// @tparam Type generic value
  /// @param values Values sent
  /// @param toProcess Process number to be sent
  /// @param tag Tag to send
  template<typename Type>
  void send(const std::vector<Type>& values, int toProcess, int tag = 0) {
    if (MPI_Send(values.data(), values.size(), this->map(Type()), toProcess, tag
      , MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw MpiError(ERROR_05, (*this));
    }
  }

  /// @brief Send string data through MPI_Send
  /// @param text String message
  /// @param toProcess Process number to be sent
  /// @param tag Tag to send
  void send(const std::string& text, int toProcess, int tag = 0) {
    if (MPI_Send(text.data(), text.length(), map(char()), toProcess, tag
      , MPI_COMM_WORLD) != MPI_SUCCESS) {
      throw MpiError(ERROR_05, (*this));
    }
  }

  /// @brief Receive value through MPI_Send
  /// @tparam Type generic data
  /// @param value Value received
  /// @param fromProcess Process number to receive form
  /// @param tag Tag to receive
  // template<typename Type>
  template<typename Type>
  void receive(Type& value, int fromProcess, int tag = MPI_ANY_TAG) {
    if (MPI_Recv(&value, 1, this->map(Type()), fromProcess, tag
      , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
      throw MpiError(ERROR_06, (*this));
    }
  }

  /// @brief Receive vector data through MPI_Send
  /// @tparam Type generic data
  /// @param values Values received
  /// @param capacity Capacity of vector
  /// @param fromProcess Process number to receive form
  /// @param tag Tag to receive
  template<typename Type>
  void receive(Type* values, int capacity
    , int fromProcess, int tag = MPI_ANY_TAG) {
    if (MPI_Recv(values, capacity, this->map(Type()), fromProcess, tag
      , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
      throw MpiError(ERROR_06, (*this));
    }
  }

  /// @brief Receive std::vector data through MPI_Send
  /// @tparam Type 
  /// @param values Values received
  /// @param capacity Capacity of vector
  /// @param fromProcess Process number to receive form
  /// @param tag Tag to receive
  template<typename Type>
  void receive(std::vector<Type>& values, int capacity
    , int fromProcess, int tag = MPI_ANY_TAG) {
    if (MPI_Recv(&values[0], capacity, map(Type()), fromProcess, tag
      , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
      throw MpiError(ERROR_06, (*this));
    }
  }

  /// @brief Receive std::string data through MPI_Send
  /// @param text String container
  /// @param capacity Capacity of string
  /// @param fromProcess Process number to receive form
  /// @param tag Tag to receive
  void receive(std::string& text, int capacity
    , int fromProcess, int tag = MPI_ANY_TAG) {
    std::vector<char> message(capacity);
    if (MPI_Recv(&message[0], capacity, map(char()), fromProcess, tag
      , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
      throw MpiError(ERROR_06, (*this));
    } else {
      text.assign(message.data());
    }
  }

 public:
  /// @brief Identifier for bool type data
  /// @param  type data
  /// @return Identifier for bool
  static inline MPI_Datatype map(bool) { return MPI_C_BOOL; }
  /// @brief Identifier for char type data
  /// @param  type data
  /// @return Identifier for char
  static inline MPI_Datatype map(char) { return MPI_CHAR; }
  /// @brief Identifier for unsigned char type data
  /// @param  type data
  /// @return Identifier for unsigned char
  static inline MPI_Datatype map(unsigned char) { return MPI_UNSIGNED_CHAR; }
  /// @brief Identifier for short type data
  /// @param  type data
  /// @return Identifier for short
  static inline MPI_Datatype map(short) { return MPI_SHORT; }
  /// @brief Identifier for unsigned short type data
  /// @param  type data
  /// @return Identifier for unsigned short
  static inline MPI_Datatype map(unsigned short) { return MPI_UNSIGNED_SHORT; }
  /// @brief Identifier for int type data
  /// @param  type data
  /// @return Identifier for int
  static inline MPI_Datatype map(int) { return MPI_INT; }
  /// @brief Identifier for unsigned type data
  /// @param  type data
  /// @return Identifier for unsigned
  static inline MPI_Datatype map(unsigned) { return MPI_UNSIGNED; }
  /// @brief Identifier for long type data
  /// @param  type data
  /// @return Identifier for long
  static inline MPI_Datatype map(long) { return MPI_LONG; }
  /// @brief Identifier for unsigned long type data
  /// @param  type data
  /// @return Identifier for unsigned long
  static inline MPI_Datatype map(unsigned long) { return MPI_UNSIGNED_LONG; }
  /// @brief Identifier for long long type data
  /// @param  type data
  /// @return Identifier for long long
  static inline MPI_Datatype map(long long) { return MPI_LONG_LONG; }
  /// @brief Identifier for unsigned long long type data
  /// @param  type data
  /// @return Identifier for unsigned long long
  static inline MPI_Datatype map(unsigned long long)
    { return MPI_UNSIGNED_LONG_LONG; }
  /// @brief Identifier for float type data
  /// @param  type data
  /// @return Identifier for float
  static inline MPI_Datatype map(float) { return MPI_FLOAT; }
  /// @brief Identifier for double type data
  /// @param  type data
  /// @return Identifier for double
  static inline MPI_Datatype map(double) { return MPI_DOUBLE; }
  /// @brief Identifier for long double type data
  /// @param  type data
  /// @return Identifier for long double
  static inline MPI_Datatype map(long double) { return MPI_LONG_DOUBLE; }
};
#endif
