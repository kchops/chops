#include "container_vector.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define ABORT_WITH_ERROR_MSG(msg) \
    assert(0 && msg);

typedef struct {
    uint64_t element_size_;
    uint64_t length_;
    uint64_t capacity_;
    char buffer_[1];
} vector_header_t;

void vector_init(void** buffer, uint64_t element_size) {
    static const unsigned char INITIAL_CAPACITY = 16;
    uint64_t total_size_in_bytes = offsetof(vector_header_t, buffer_) + 
                                   (INITIAL_CAPACITY * element_size);
    vector_header_t* hdr = malloc(total_size_in_bytes);
    memset(hdr, 0, total_size_in_bytes);
    hdr->element_size_ = element_size;
    hdr->length_ = 0;
    hdr->capacity_ = INITIAL_CAPACITY;
    *buffer = hdr->buffer_;
}

uint64_t vector_length(const void * const buffer) {
    const vector_header_t * const hdr = buffer - offsetof(vector_header_t, buffer_);
    return hdr->length_;
}

void vector_grow(void** buffer) {
    vector_header_t* hdr = *buffer - offsetof(vector_header_t, buffer_);
    uint64_t new_capacity_ = hdr->capacity_ * 2;
    uint64_t element_size = hdr->element_size_;
    uint64_t length = hdr->length_;
    uint64_t new_total_size_in_bytes = offsetof(vector_header_t, buffer_) + 
                                       (new_capacity_ * hdr->element_size_);
    uint64_t old_total_size_in_bytes = offsetof(vector_header_t, buffer_) + 
                                       (hdr->capacity_ * hdr->element_size_);

    vector_header_t* hdr_new = malloc(new_total_size_in_bytes);
    memset(hdr_new, 0, new_total_size_in_bytes);
    memcpy(hdr_new, hdr, old_total_size_in_bytes);
    hdr_new->element_size_ = element_size;
    hdr_new->length_ = length;
    hdr_new->capacity_ = new_capacity_;
    *buffer = hdr_new->buffer_;

    free(hdr);
}

void vector_push_back(void ** buffer, const void * const elem) {
    vector_header_t* hdr = *buffer - offsetof(vector_header_t, buffer_);
    if(hdr->length_ == hdr->capacity_) {
        vector_grow(buffer);
    }
    hdr = *buffer - offsetof(vector_header_t, buffer_);
    memcpy(*buffer + (hdr->length_ * hdr->element_size_) , elem, hdr->element_size_);
    hdr->length_++;
}

void vector_shrink(void** buffer) {
    vector_header_t* hdr = *buffer - offsetof(vector_header_t, buffer_);
    uint64_t new_capacity_ = hdr->capacity_ / 2;
    uint64_t element_size = hdr->element_size_;
    uint64_t length = hdr->length_;
    uint64_t new_total_size_in_bytes = offsetof(vector_header_t, buffer_) + 
                                       (new_capacity_ * hdr->element_size_);

    vector_header_t* hdr_new = malloc(new_total_size_in_bytes);
    memset(hdr_new, 0, new_total_size_in_bytes);
    memcpy(hdr_new, hdr, new_total_size_in_bytes);
    hdr_new->element_size_ = element_size;
    hdr_new->length_ = length;
    hdr_new->capacity_ = new_capacity_;
    *buffer = hdr_new->buffer_;

    free(hdr);
}

void vector_pop_back(void ** buffer) {
    vector_header_t* hdr = *buffer - offsetof(vector_header_t, buffer_);
    hdr->length_--;
    if(2 * hdr->length_ <=  hdr->capacity_) {
        vector_shrink(buffer);
    }
}

void * const vector_at_checked(void * const buffer, uint64_t idx) {
    vector_header_t* hdr = buffer - offsetof(vector_header_t, buffer_);
    void* res = NULL;
    if(idx < hdr->length_) {
        res = buffer + (idx * hdr->element_size_);
    }
    return res;
}

void * const vector_at(void * const buffer, uint64_t idx) {
    vector_header_t* hdr = buffer - offsetof(vector_header_t, buffer_);
    void* res = NULL;
    if(idx < hdr->length_) {
        res = buffer + (idx * hdr->element_size_);
    }
    return res;
}

void vector_free(void** buffer) {
    vector_header_t* hdr = *buffer - offsetof(vector_header_t, buffer_);
    free(hdr);
    *buffer = NULL;
}