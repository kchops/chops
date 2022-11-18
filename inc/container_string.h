#pragma once
#include <stdint.h>

void string_init_empty(char const** buffer);
void string_init(char const** buffer, char const* str, uint64_t size);

uint64_t string_length(char const * const buffer);

char string_char_at(char const * const buffer, uint64_t idx);
void string_update_char_at(char const** buffer, uint64_t idx, char c);

void string_concatenate(char const** str1, char const * const str2);
char const* get_substring(char const * const str, uint64_t id1, uint64_t id2);

void string_free(char const** str1);