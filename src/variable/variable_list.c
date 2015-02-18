/*
 * variable_list.c
 *
 *  Created on: Feb 5, 2015
 *      Author: dejan
 */

#include <variable_list.h>
#include <assert.h>
#include <stdlib.h>

#define INITIAL_LIST_SIZE 100
#define INITIAL_MAP_SIZE 100

static
void lp_variable_list_resize(lp_variable_list_t* list, size_t capacity) {
  assert(capacity > list->list_capacity);
  list->list = (lp_variable_t*) realloc(list->list, capacity*sizeof(lp_variable_t));
  list->list_capacity = capacity;
}

static
void lp_variable_map_resize(lp_variable_list_t* list, size_t capacity) {
  assert(capacity > list->var_to_index_map_capacity);
  list->var_to_index_map = (int*) realloc(list->var_to_index_map, capacity*sizeof(int));
  size_t i;
  for (i = list->var_to_index_map_capacity; i < capacity; ++ i) {
    list->var_to_index_map[i] = -1;
  }
  list->var_to_index_map_capacity = capacity;
}

void lp_variable_list_construct(lp_variable_list_t* list) {
  // The list
  list->list = 0;
  list->list_size = 0;
  list->list_capacity = 0;
  lp_variable_list_resize(list, INITIAL_LIST_SIZE);
  // Map to indices
  list->var_to_index_map = 0;
  list->var_to_index_map_capacity = 0;
  lp_variable_map_resize(list, INITIAL_MAP_SIZE);
}

void lp_variable_list_destruct(lp_variable_list_t* list) {
  free(list->list);
  free(list->var_to_index_map);
}

size_t lp_variable_list_size(const lp_variable_list_t* list) {
  return list->list_size;
}

int lp_variable_list_index(const lp_variable_list_t* list, lp_variable_t x) {
  if (x >= list->var_to_index_map_capacity) {
    return -1;
  } else {
    return list->var_to_index_map[x];
  }
}

void lp_variable_list_copy_into(const lp_variable_list_t* list, lp_variable_t* vars) {
  size_t i;
  for (i = 0; i < list->list_size; ++ i) {
    vars[i] = list->list[i];
  }
}

void lp_variable_list_push(lp_variable_list_t* list, lp_variable_t var) {
  if (list->list_size == list->list_capacity) {
    lp_variable_list_resize(list, list->list_capacity*2);
  }
  if (var >= list->var_to_index_map_capacity) {
    lp_variable_map_resize(list, var+1);
  }
  assert(list->var_to_index_map[var] == -1);
  list->var_to_index_map[var] = list->list_size;
  list->list[list->list_size ++] = var;
}

void lp_variable_list_pop(lp_variable_list_t* list) {
  assert(list->list_size > 0);
  lp_variable_t var = list->list[-- list->list_size];
  list->var_to_index_map[var] = -1;
}