// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#ifndef ARRAY_MUTEX_H
#define ARRAY_MUTEX_H

#include <stddef.h>

#define array_not_found (size_t)-1

typedef struct array array_mutex_t;

array_mutex_t* array_mutex_create(size_t capacity);
void array_mutex_destroy(array_mutex_t* array);
int array_mutex_append(array_mutex_t* array, void* element);
size_t array_mutex_get_count(array_mutex_t* array);
void* array_mutex_get_element(array_mutex_t* array, size_t index);
size_t array_mutex_find_first(array_mutex_t* array
    , const void* element, size_t start_pos);
int array_mutex_remove_first(array_mutex_t* array
    , const void* element, size_t start_pos);

#endif  // ARRAY_H