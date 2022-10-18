#include <stdlib.h>
#include <assert.h>
#include "my_math.h"

void init_array(bits_array_t* bits_array, size_t capacity) {
  if (bits_array != NULL) {
    bits_array->count = capacity;
    bits_array->array = (uint8_t*) calloc(bits_array->count/8 + 1, sizeof(uint8_t));
    if(bits_array->array != NULL) set_prime_numbers(bits_array);
  }
}

void  set_bit(bits_array_t* bits_array,  uint64_t index) {
  assert(bits_array);
  assert(bits_array->array);
  assert(bits_array->count > index);
  bits_array->array[index/8] |= 1 << (index%8);
}

uint64_t test_bit(bits_array_t* bits_array,  uint64_t index ) {
  assert(bits_array);
  assert(bits_array->array);
  assert(bits_array->count > index/8);
  return (bits_array->array[index/8] & (1 << (index%8) )) != 0;
}
