// Copyright 2022 Daniel Perez-Morera <daniel.perezmorera@ucr.ac.cr> CC-BY-4
#ifndef ARRAY_RWLOCK_H
#define ARRAY_RWLOCK_H

#include <stddef.h>

#define array_not_found (size_t)-1

typedef struct array array_rwlock_t;

array_rwlock_t*  array_rwlock_create(size_t capacity);
void  array_rwlock_destroy(array_rwlock_t* array);
int  array_rwlock_append(array_rwlock_t* array, void* element);
size_t  array_rwlock_get_count(array_rwlock_t* array);
void* array_rwlock_get_element(array_rwlock_t* array, size_t index);
size_t array_rwlock_find_first(array_rwlock_t* array
    , const void* element, size_t start_pos);
int array_rwlock_remove_first(array_rwlock_t* array
    , const void* element, size_t start_pos);

#endif  // ARRAY_H
