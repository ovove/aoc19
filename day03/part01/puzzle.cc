
#if not defined(DO_UNIT_TEST)

#include <iostream>

int main() {
}

#else // DO_UNIT_TEST

#include <gtest/gtest.h>

TEST(DAY03_PART01, TEST01) {
    ASSERT_TRUE(true);
}

#endif // DO_UNIT_TEST
