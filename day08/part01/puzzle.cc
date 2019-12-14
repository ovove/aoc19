
#if not defined(DO_UNIT_TEST)

#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

constexpr auto Width = 25U;
constexpr auto Height = 6U;

int main() {
    using std::filesystem::path;
    std::ifstream ifs(path(BINARY_DIR) / path("..") / path("input"));
    std::string image;
    std::getline(ifs, image);

    std::vector<std::string> layers;
    layers.reserve(image.size()/(Width * Height));
    for (size_t pos = 0; pos < image.size(); pos += Width * Height)
        layers.emplace_back(image.substr(pos, Width * Height));

    const auto cmp_nr_of_zeros = [](const std::string& l1, const std::string& l2) {
        return std::count(std::begin(l1), std::end(l1), '0') <
               std::count(std::begin(l2), std::end(l2), '0');
    };
    const auto min_zero_layer =
        std::min_element(std::begin(layers), std::end(layers), cmp_nr_of_zeros);

    const auto nr_of_ones = std::count(std::begin(*min_zero_layer), std::end(*min_zero_layer), '1');
    const auto nr_of_twos = std::count(std::begin(*min_zero_layer), std::end(*min_zero_layer), '2');

    std::cout << (nr_of_ones * nr_of_twos) << std::endl;
}

#else

#include <gtest/gtest.h>

TEST(DAY08_PART01, TEST01) { ASSERT_TRUE(true); }

#endif
