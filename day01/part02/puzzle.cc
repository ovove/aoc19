
namespace {
inline unsigned fuel_from_mass_calulator(unsigned mass) {
    unsigned result = 0;
    while (mass > 0) {
        const unsigned fuel = ((mass / 3) >= 2) ? ((mass / 3) - 2) : 0;
        result += fuel;
        mass = fuel;
    }
    return result;
}
} // namespace

#if not defined(DO_UNIT_TEST)

#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <filesystem>

#include <range/v3/all.hpp>

#if !defined(BINARY_DIR)
error "BINARY_DIR not defined"
#endif

int main() {
    using std::filesystem::path;
    std::ifstream ifs(path(BINARY_DIR) / path("..") / path("input"));
    const std::vector mass(std::istream_iterator<unsigned>{ifs}, std::istream_iterator<unsigned>{});
    using ranges::accumulate;
    using ranges::view::transform;
    const auto tot = accumulate(mass | transform(fuel_from_mass_calulator), 0);
    std::cout << tot << std::endl;
}

#else

#include <gtest/gtest.h>

TEST(DAY01_PART02, TEST01) { ASSERT_EQ(fuel_from_mass_calulator(14), 2); }
TEST(DAY01_PART02, TEST02) { ASSERT_EQ(fuel_from_mass_calulator(1969), 966); }
TEST(DAY01_PART02, TEST03) { ASSERT_EQ(fuel_from_mass_calulator(100756), 50346); }

#endif
