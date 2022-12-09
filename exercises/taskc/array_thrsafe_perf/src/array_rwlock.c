// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "array_rwlock.h"

typedef struct array {
  void** elements;
  size_t capacity;
  size_t count;
  pthread_rwlock_t can_acces_array;
} array_rwlock_t;

array_rwlock_t* array_rwlock_create(size_t capacity) {
  assert(capacity);
  array_rwlock_t* array = (array_rwlock_t*)malloc(sizeof(array_rwlock_t));
  array->capacity = capacity;
  array->count = 0;
  array->elements = (void**)malloc( capacity * sizeof(void*) );
  pthread_rwlock_init(&array->can_acces_array, NULL);
  return array;
}

void array_rwlock_destroy(array_rwlock_t* array) {
  assert(array);
  pthread_rwlock_destroy(&array->can_acces_array);
  free(array->elements);
  free(array);
}

int array_rwlock_increase_capacity(array_rwlock_t* array) {
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

int array_rwlock_decrease_capacity(array_rwlock_t* array) {
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

size_t array_rwlock_get_count(array_rwlock_t* array) {
  assert(array);
  pthread_rwlock_rdlock(&array->can_acces_array);
  size_t count = array->count;
  pthread_rwlock_unlock(&array->can_acces_array);
  return count;
}

void* array_rwlock_get_element(array_rwlock_t* array, size_t index) {
  assert(array);
  assert(index < array_rwlock_get_count(array));
  pthread_rwlock_rdlock(&array->can_acces_array);
  void* element = array->elements[index];
  pthread_rwlock_unlock(&array->can_acces_array);
  return element;
}

int array_rwlock_append(array_rwlock_t* array, void* element) {
  pthread_rwlock_wrlock(&array->can_acces_array);
  if (array->count == array->capacity) {
    if (!array_rwlock_increase_capacity(array)) {
      pthread_rwlock_unlock(&array->can_acces_array);
      return -1;
    }
  }
  array->elements[array->count++] = element;
  pthread_rwlock_unlock(&array->can_acces_array);
  return 0;  // Success
}

size_t array_rwlock_find_first(array_rwlock_t* array
  , const void* element, size_t start_pos) {
  pthread_rwlock_rdlock(&array->can_acces_array);
  for ( size_t index = start_pos; index < array->count; ++index ) {
    if ( array->elements[index] == element ) {
      pthread_rwlock_unlock(&array->can_acces_array);
      return index;
    }
  }
  pthread_rwlock_unlock(&array->can_acces_array);
  return array_not_found;
}

int array_rwlock_remove_first(array_rwlock_t* array, const void* element, size_t start_pos) {
  size_t index = array_rwlock_find_first(array, element, start_pos);
  if (index == array_not_found)
    return -1;
  pthread_rwlock_wrlock(&array->can_acces_array);
  for ( --array->count; index < array->count; ++index )
    array->elements[index] = array->elements[index + 1];
  if ( array->count == array->capacity / 10 )
    array_rwlock_decrease_capacity(array);
  pthread_rwlock_unlock(&array->can_acces_array);
  return 0;  // Removed
}
