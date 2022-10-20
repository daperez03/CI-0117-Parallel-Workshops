#ifndef BITS_ARRAY_H
#define BITS_ARRAY_H

#include <stdint.h>
#include <stdbool.h>

typedef struct bits_array {
  uint8_t* array;
  size_t count;
} bits_array_t;

// Todo(you) extraido de stack overflow y documentar
void init_array(bits_array_t* bits_array, size_t capacity);

void  set_bit(bits_array_t* bits_array,  uint64_t index);

uint64_t test_bit(bits_array_t* bits_array,  uint64_t index);

#endif
