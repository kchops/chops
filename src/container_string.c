#include "container_vector.h"
#include "container_string.h"
#include <stddef.h>

void string_add_zero_terminate(char ** buffer) {
    char eol = '\0';
    vector_push_back(buffer, &eol);
}

void string_remove_zero_terminate(char ** buffer) {
    vector_pop_back(buffer);
}

void string_init(char ** buffer, char const* str, uint64_t size) {
    vector_init(buffer, 1);
    for(uint64_t i = 0; i < size; ++i) {
        vector_push_back(buffer, str + i);
    }
    string_add_zero_terminate(buffer);
}

void string_init_empty(char ** buffer) {
    vector_init(buffer, 1);
    string_add_zero_terminate(buffer);
}

uint64_t string_length(const char * const buffer) {
    return vector_length(buffer) - 1;
}

char string_char_at(char const * const buffer, uint64_t idx) {
    char const * const e = (char const * const) vector_at((char * const)buffer, idx);
    return *e;
}

void string_update_char_at(char ** buffer, uint64_t idx, char c) {
    ((char *)*buffer)[idx] = c;
}

void string_concatenate(char ** str1, char const * const str2) {
    string_remove_zero_terminate(str1);
    for(uint64_t i = 0; i < string_length(str2); ++i) {
        vector_push_back(str1, str2 + i);
    }
}

char * get_substring(char const * const str, uint64_t id1, uint64_t id2) {
    char* substr = NULL;
    string_init_empty(&substr);
    string_remove_zero_terminate(&substr);
    for(uint64_t i = id1; i < id2; ++i) {
        vector_push_back(&substr, str + i);
    }
    string_add_zero_terminate(&substr);
    return substr;
}

void string_free(char ** str1) {
    vector_free(str1);
}