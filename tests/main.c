#include "deps/ctest/inc/ctest.h"

size_t FinalFailedTestCount = 0;
size_t FailedTests = 0;
#define RECORD_FAILED_TESTS() \
    FinalFailedTestCount += FailedTests;

int main() {
    CTEST_RUN_TEST_SUITE(VectorTestSuite, FailedTests);
    RECORD_FAILED_TESTS()
        
    CTEST_RUN_TEST_SUITE(StringTestSuite, FailedTests);
    RECORD_FAILED_TESTS()
    
    return FinalFailedTestCount;
}