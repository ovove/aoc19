
unsigned fuel_from_mass_calulator(unsigned mass) { return mass / 3 - 2; }

#if not defined(DO_UNIT_TEST)
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
    // std::ifstream ifs("input");
    std::istream_iterator<unsigned> beg(std::cin);
    std::istream_iterator<unsigned> end;
    const std::vector mass(beg, end);
    auto get_fuel = [fun = fuel_from_mass_calulator](const auto& vec) {
        std::vector<unsigned> res(vec.size());
        std::transform(std::begin(vec), std::end(vec), std::begin(res), fun);
        return res;
    };
    const auto fuel = get_fuel(mass);
    const auto tot = std::accumulate(std::begin(fuel), std::end(fuel), 0);
    std::cout << tot << std::endl;
}

#else

#include <gtest/gtest.h>

TEST(DAY01_PART01, TEST01) { ASSERT_EQ(fuel_from_mass_calulator(12), 2); }
TEST(DAY01_PART01, TEST02) { ASSERT_EQ(fuel_from_mass_calulator(12), 2); }
TEST(DAY01_PART01, TEST03) { ASSERT_EQ(fuel_from_mass_calulator(12), 2); }
TEST(DAY01_PART01, TEST04) { ASSERT_EQ(fuel_from_mass_calulator(12), 2); }

#endif
