#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include <stdlib.h>

// creates dynamicly growing array for type
#define DA_FOR(type)                                                           \
  typedef struct {                                                             \
    type *array;                                                               \
    size_t size;                                                               \
    size_t capacity;                                                           \
  } DA_##type;                                                                 \
                                                                               \
  DA_##type da_##type##_init(size_t init_size) {                               \
    DA_##type da;                                                              \
    da.array = (type *)malloc(init_size * sizeof(type));                       \
    if (da.array == NULL) {                                                    \
      da.size = 0;                                                             \
      da.capacity = 0;                                                         \
      return da;                                                               \
    }                                                                          \
    da.size = 0;                                                               \
    da.capacity = init_size;                                                   \
    return da;                                                                 \
  }                                                                            \
                                                                               \
  void da_##type##_resize(DA_##type *da) {                                     \
    if (da->size == da->capacity) {                                            \
      size_t new_capacity = (da->capacity == 0) ? 1 : da->capacity * 2;        \
      type *new_array =                                                        \
          (type *)realloc(da->array, new_capacity * sizeof(type));             \
      if (new_array) {                                                         \
        da->array = new_array;                                                 \
        da->capacity = new_capacity;                                           \
      }                                                                        \
    }                                                                          \
  }                                                                            \
                                                                               \
  void da_##type##_append(DA_##type *da, type element) {                       \
    da_##type##_resize(da);                                                    \
    if (da->size < da->capacity) {                                             \
      da->array[da->size++] = element;                                         \
    }                                                                          \
  }                                                                            \
                                                                               \
  void da_##type##_free(DA_##type *da) {                                       \
    free(da->array);                                                           \
    da->array = NULL;                                                          \
    da->size = 0;                                                              \
    da->capacity = 0;                                                          \
  }

#endif // DYNAMIC_ARRAY_H_
