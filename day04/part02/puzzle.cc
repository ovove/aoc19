
#include <iostream>
#include <array>
#include <stdexcept>

// #include <range/v3/all.hpp>

namespace {

std::array<int, 6> pwd_to_array(int pwd) {
    if (pwd < 100000 or pwd > 999999) throw std::out_of_range("pwd is out of range");
    std::array<int, 6> result;
    result[5] = pwd % 10; pwd /= 10;
    result[4] = pwd % 10; pwd /= 10;
    result[3] = pwd % 10; pwd /= 10;
    result[2] = pwd % 10; pwd /= 10;
    result[1] = pwd % 10; pwd /= 10;
    result[0] = pwd % 10;
    return result;
}

inline bool check(int pwd) {
    const auto digits = pwd_to_array(pwd);
    // clang-format off
    const bool result =
        (digits[0] <= digits[1]) and (digits[1] <= digits[2]) and (digits[2] <= digits[3]) and
        (digits[3] <= digits[4]) and (digits[4] <= digits[5]) and
                                   ((digits[0] == digits[1] and digits[1] != digits[2]) or
         (digits[0] != digits[1] and digits[1] == digits[2] and digits[2] != digits[3]) or
         (digits[1] != digits[2] and digits[2] == digits[3] and digits[3] != digits[4]) or
         (digits[2] != digits[3] and digits[3] == digits[4] and digits[4] != digits[5]) or
         (digits[3] != digits[4] and digits[4] == digits[5]));
    // clang-format off
    return result;
}

}

#if not defined(DO_UNIT_TEST)

int main() {
    // 109165-576723
    const int beg = 109165;
    const int end = 576723;
    unsigned nr_of_possible_pwds = 0;
    for (int pwd = beg; pwd <= end; ++pwd) {
        if (not check(pwd)) continue;
        ++nr_of_possible_pwds;
    }
    std::cout << nr_of_possible_pwds << std::endl;
}

#else // DO_UNIT_TEST
#include <gtest/gtest.h>

TEST(DAY04_PART02, TEST01) {
    ASSERT_TRUE(check(112233));
}

TEST(DAY04_PART02, TEST02) {
    ASSERT_FALSE(check(123444));
}

TEST(DAY04_PART02, TEST03) {
    ASSERT_TRUE(check(111122));
}

#endif // DO_UNIT_TEST
