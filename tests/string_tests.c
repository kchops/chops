#include "deps/ctest/inc/ctest.h"
#include <container_string.h>

CTEST_BEGIN_TEST_SUITE(StringTestSuite)

CTEST_FUNCTION(StringrBasicTests) {
    const char *str1 = NULL;
    string_init(&str1, "Hello,", 6);
    const char *str2 = NULL;
    string_init(&str2, " World!", 7);

    string_concatenate(&str1, str2);
    CTEST_ASSERT_ARE_EQUAL(char_ptr, "Hello, World!", str1);

    const char *substr = get_substring(str1, 5, 12);
    CTEST_ASSERT_ARE_EQUAL(char_ptr, ", World", substr);
    string_update_char_at(&substr, 1, ':');
    CTEST_ASSERT_ARE_EQUAL(char_ptr, ",:World", substr);
}

CTEST_END_TEST_SUITE(StringTestSuite)