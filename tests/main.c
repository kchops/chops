#include "deps/ctest/inc/ctest.h"

int main() {
    size_t failedTests = 0;
    CTEST_RUN_TEST_SUITE(VectorTestSuite, failedTests);
    CTEST_RUN_TEST_SUITE(StringTestSuite, failedTests);
    return failedTests;
}