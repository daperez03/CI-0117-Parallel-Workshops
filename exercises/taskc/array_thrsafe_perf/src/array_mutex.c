// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

#include "array_mutex.h"

typedef struct array {
  void** elements;
  size_t capacity;
  size_t count;
  pthread_mutex_t can_acces_array;
} array_mutex_t;

array_mutex_t* array_mutex_create(size_t capacity) {
  assert(capacity);
  array_mutex_t* array = (array_mutex_t*)malloc(sizeof(array_mutex_t));
  array->capacity = capacity;
  array->count = 0;
  array->elements = (void**)malloc( capacity * sizeof(void*) );
  pthread_mutex_init(&array->can_acces_array, NULL);
  return array;
}

void array_mutex_destroy(array_mutex_t* array) {
  assert(array);
  pthread_mutex_destroy(&array->can_acces_array);
  free(array->elements);
  free(array);
}

int array_mutex_increase_capacity(array_mutex_t* array) {
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

int array_mutex_decrease_capacity(array_mutex_t* array) {
  assert(array);
  size_t new_capacity = array->capacity / 10;
  if ( new_capacity < 10 )
    return 0;

  void** new_elements = (void**)
    realloc( array->elements, new_capacity * sizeof(void*) );
  if ( new_elements == NULL )
    return -1;

  array->capacity = new_capacity;
  array->elements = new_elements;

  return 0;  // Success
}

size_t array_mutex_get_count(array_mutex_t* array) {
  assert(array);
  pthread_mutex_lock(&array->can_acces_array);
  size_t count = array->count;
  pthread_mutex_unlock(&array->can_acces_array);
  return count;
}

void* array_mutex_get_element(array_mutex_t* array, size_t index) {
  assert(array);
  assert(index < array_mutex_get_count(array));
  pthread_mutex_lock(&array->can_acces_array);
  void* element = array->elements[index];
  pthread_mutex_unlock(&array->can_acces_array);
  return element;
}

int array_mutex_append(array_mutex_t* array, void* element) {
  pthread_mutex_lock(&array->can_acces_array);
  if (array->count == array->capacity) {
    if (!array_mutex_increase_capacity(array)) {
      pthread_mutex_unlock(&array->can_acces_array);
      return -1;
    }
  }
  array->elements[array->count++] = element;
  pthread_mutex_unlock(&array->can_acces_array);
  return 0;  // Success
}

size_t array_mutex_find_first(array_mutex_t* array
  , const void* element, size_t start_pos) {
  pthread_mutex_lock(&array->can_acces_array);
  for ( size_t index = start_pos; index < array->count; ++index ) {
    if ( array->elements[index] == element ) {
      pthread_mutex_unlock(&array->can_acces_array);
      return index;
    }
  }
  pthread_mutex_unlock(&array->can_acces_array);
  return array_not_found;
}

int array_mutex_remove_first(array_mutex_t* array, const void* element, size_t start_pos) {
  size_t index = array_mutex_find_first(array, element, start_pos);
  if (index == array_not_found)
    return -1;
  pthread_mutex_lock(&array->can_acces_array);
  for ( --array->count; index < array->count; ++index )
    array->elements[index] = array->elements[index + 1];
  if ( array->count == array->capacity / 10 )
    array_mutex_decrease_capacity(array);
  pthread_mutex_unlock(&array->can_acces_array);
  return 0;  // Removed
}
