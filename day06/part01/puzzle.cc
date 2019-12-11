
#include <string>
#include <string_view>
#include <iostream>
#include <regex>
#include <algorithm>
#include <map>

// #include <range/v3/all.hpp>

namespace {

using SatelliteGraph = std::map<std::string, std::vector<std::string>>;

SatelliteGraph map2graph(std::istream& map) {
    SatelliteGraph result;
    const std::regex regex(R"(([A-Z0-9]+)\)([A-Z0-9]+))");
    for (std::string line; std::getline(map, line);) {
        std::smatch match;
        if (not std::regex_match(line, match, regex)) continue;
        const auto& center = match[1];
        const auto& satellite = match[2];
        result[center].push_back(satellite);
        static_cast<void>(result[satellite]);
    }
    return result;
}

using SatelliteDistances = std::map<std::string, unsigned>;

void checksum_(const SatelliteGraph& graph,
               const std::string& satellite,
               SatelliteDistances& satellite_distances,
               unsigned distance) {
    satellite_distances[satellite] = distance;
    for (const auto next_satellite : graph.at(satellite)) {
        checksum_(graph, next_satellite, satellite_distances, distance + 1);
    }
}

unsigned checksum(const SatelliteGraph& graph) {
    SatelliteDistances satellite_distances;
    checksum_(graph, "COM", satellite_distances, 0);
    unsigned tot_dist = 0;
    for (auto [satellite, distance] : satellite_distances) tot_dist += distance;
    return tot_dist;
}

} // namespace

#if not defined(DO_UNIT_TEST)

#include <filesystem>
#include <fstream>

int main() {
    using std::filesystem::path;
    std::ifstream input(path(BINARY_DIR) / path("..") / path("input"));
    const auto graph = map2graph(input);
    const auto chksum = checksum(graph);
    std::cout << chksum << std::endl;
}

#else // DO_UNIT_TEST
#include <gtest/gtest.h>
#include <sstream>

TEST(DAY03_PART01, TEST01) {
    const std::string map = R"(
COM)B
B)C
C)D
D)E
E)F
B)G
G)H
D)I
E)J
J)K
K)L)";
    std::istringstream iss(map);
    const auto graph = map2graph(iss);
    const auto chksum = checksum(graph);
    ASSERT_EQ(chksum, 42);
}

#endif // DO_UNIT_TEST
