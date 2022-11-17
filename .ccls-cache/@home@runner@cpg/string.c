#include "vector.h"
#include "string.h"

void string_init(char** buffer, const char* str, uint64_t size) {
    vector_init(buffer, 1);
    for(uint64_t i = 0; i < size; ++i) {
        vector_push_back(buffer, str + i);
    }
}

uint64_t string_length(const char * const buffer) {
    return vector_length(buffer);
}

char string_char_at(char * const buffer, uint64_t idx) {
    char* e = (char*) vector_at(buffer, idx);
    return *e;
}