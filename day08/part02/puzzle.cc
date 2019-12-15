
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

    std::string final_image(Width * Height, '2');

    for (size_t pos = 0; pos < final_image.size(); ++pos) {
        for (const auto layer: layers) {
            if (layer[pos] != '2') {
                final_image[pos] = layer[pos];
                break;
            }
        }
    }

    for (size_t row = 0; row < Height; ++row) {
        std::cout << final_image.substr(row * Width, Width) << std::endl;
    }

    std::cout << std::endl;

    for (size_t p = 0; p < final_image.size(); ++p) {
        if (final_image[p] == '0') final_image[p] = ' ';
        if (final_image[p] == '1') final_image[p] = '*';
    }

    for (size_t row = 0; row < Height; ++row) {
        std::cout << final_image.substr(row * Width, Width) << std::endl;
    }
}

#else

#include <gtest/gtest.h>

TEST(DAY08_PART02, TEST01) { ASSERT_TRUE(true); }

#endif
