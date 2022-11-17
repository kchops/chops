#pragma once
#include <stdint.h>

void string_init(char** buffer, const char* str, uint64_t size);
uint64_t string_length(const char * const buffer);
char string_char_at(char * const buffer, uint64_t idx);