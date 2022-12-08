// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <assert.h>
#include <stdlib.h>

#include "array.h"

typedef struct array {
  void** elements;
  size_t capacity;
  size_t count;
} array_t;

array_t* array_create(size_t capacity) {
  assert(capacity);
  array_t* array = (array_t*)malloc(sizeof(array_t));
  array->capacity = capacity;
  array->count = 0;
  array->elements = (void**)malloc( capacity * sizeof(void*) );
  return array;
}

void array_destroy(array_t* array) {
  assert(array);
  free(array->elements);
  free(array);
}

int array_increase_capacity(array_t* array) {
  assert(array);
  size_t new_capacity = 10 * array->capacity;
  void** new_elements = (void**)
    realloc( array->elements, new_capacity * sizeof(void*) );
  if ( new_elements == NULL )
    return -1;

  array->capacity = new_capacity;
  array->elements = new_elements;

  return 0;  // Success
}

int array_decrease_capacity(array_t* array) {
  assert(array);
  size_t new_capacity = array->capacity / 10;
  if ( new_capacity < 10 )
    return 0;

  void** new_elements = (void**)realloc( array, new_capacity * sizeof(void*) );
  if ( new_elements == NULL )
    return -1;

  array->capacity = new_capacity;
  array->elements = new_elements;

  return 0;  // Success
}

size_t array_get_count(const array_t* array) {
  assert(array);
  return array->count;
}

void* array_get_element(const array_t* array, size_t index) {
  assert(array);
  assert(index < array_get_count(array));
  return array->elements[index];
}

int array_append(array_t* array, void* element) {
  if ( array->count == array->capacity)
    if (!array_increase_capacity(array))
      return -1;

  array->elements[array->count++] = element;
  return 0;  // Success
}

size_t array_find_first(const array_t* array
  , const void* element, size_t start_pos) {
  for ( size_t index = start_pos; index < array->count; ++index )
    if ( array->elements[index] == element )
      return index;

  return array_not_found;
}

int array_remove_first(array_t* array, const void* element, size_t start_pos) {
  size_t index = array_find_first(array, element, start_pos);
  if ( index == array_not_found )
    return -1;

  for ( --array->count; index < array->count; ++index )
    array->elements[index] = array->elements[index + 1];
  if ( array->count == array->capacity / 10 )
    array_decrease_capacity(array);

  return 0;  // Removed
}
