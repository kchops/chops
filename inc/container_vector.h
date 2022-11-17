#pragma once
#include <stdint.h>

void vector_init(void** buffer, uint64_t element_size);
void vector_push_back(void ** buffer, const void * const elem);
void vector_pop_back(void ** buffer);
uint64_t vector_length(const void * const buffer);
void * const vector_at_checked(void * const buffer, uint64_t idx);
void * const vector_at(void * const buffer, uint64_t idx);