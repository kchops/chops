#include "container_vector.h"
#include "container_string.h"
#include <stdio.h>

int main(void) {
    float *arr = NULL;
    vector_init(&arr, sizeof(int));

    for(int i = 0; i < 100000001; ++i) {
        float e = i;
        vector_push_back(&arr, &e);
    }
    
    printf("size of vector is: %lu\n", vector_length(arr));

    double accum = 0.0;
    for(int i = 0; i < vector_length(arr); ++i) {
        float* e = (float*) vector_at(arr, i);
        accum += *e;
    }
    printf("%f, \n", accum);
    printf("%f, \n", *((float*) vector_at(arr, 100000000)));
        
    const char* str1 = NULL;
    string_init(&str1, "Hello,", 6);
    const char* str2 = NULL;
    string_init(&str2, " World!", 7);
    
    string_concatenate(&str1, str2);
    printf("str=%s\n", str1);

    printf("char at 5=%c\n", string_char_at(str1, 5));
    printf("char at 12=%c\n", string_char_at(str1, 12));
    
    const char* substr = get_substring(str1, 5, 12);
    printf("substr(5, 12)=%s\n", substr);
    string_update_char_at(&substr, 1, ':');
    printf("substr(5, 12)=%s\n", substr);
    
    return 0;
}