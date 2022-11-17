#include "deps/ctest/inc/ctest.h"
#include <container_vector.h>

CTEST_BEGIN_TEST_SUITE(VectorTestSuite)

CTEST_FUNCTION(VectorBasicTests) {
    float *arr = NULL;
    vector_init(&arr, sizeof(int));

    for (int i = 0; i < 100000001; ++i) {
        float e = i;
        vector_push_back(&arr, &e);
    }
    CTEST_ASSERT_ARE_EQUAL(uint64_t, 100000001, vector_length(arr));

    double accum = 0.0;
    for (int i = 0; i < vector_length(arr); ++i) {
        float *e = (float *)vector_at(arr, i);
        accum += *e;
    }
    CTEST_ASSERT_ARE_EQUAL(float, 5000000050000000.0, accum);
    CTEST_ASSERT_ARE_EQUAL(float, 10000001.0, *((float *)vector_at(arr, 10000001)));
}

CTEST_END_TEST_SUITE(VectorTestSuite)