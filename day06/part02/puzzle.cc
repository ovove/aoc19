
#include <string>
#include <string_view>
#include <iostream>
#include <regex>
#include <algorithm>
#include <map>
#include <vector>
#include <deque>
#include <stdexcept>

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

using SatellitePath = std::deque<std::string>;

SatellitePath path2(const SatelliteGraph& graph, const std::string& satellite) {
    SatellitePath path;
    for (std::string sat = satellite; sat != "COM";) {
        const auto is_in_next_satellite = [&sat](const auto& itm) {
            const auto [center, satellites] = itm;
            const auto it = std::find(std::begin(satellites), std::end(satellites), sat);
            return it != std::end(satellites);
        };
        const auto it = std::find_if(std::begin(graph), std::end(graph), is_in_next_satellite);
        if (it == std::end(graph)) throw std::runtime_error("Satellite not found in graph");
        sat = it->first;
        path.push_front(sat);
    }
    return path;
}

void drop_common_prefix(SatellitePath& p1, SatellitePath& p2) {
    auto it1 = std::begin(p1);
    auto it2 = std::begin(p2);
    while (it1 != std::end(p1) and it2 != std::end(p2) and *it1 == *it2) {
        it1 = std::next(it1);
        it2 = std::next(it2);
        p1.pop_front();
        p2.pop_front();
    }
}

} // namespace

#if not defined(DO_UNIT_TEST)

#include <filesystem>
#include <fstream>

int main() {
    using std::filesystem::path;
    std::ifstream input(path(BINARY_DIR) / path("..") / path("input"));
    const auto graph = map2graph(input);
    auto path_to_you = path2(graph, "YOU");
    auto path_to_san = path2(graph, "SAN");
    drop_common_prefix(path_to_you, path_to_san);
    const auto dist = path_to_you.size() + path_to_san.size();
    std::cout << dist << std::endl;
}

#else // DO_UNIT_TEST
#include <gtest/gtest.h>
#include <sstream>

TEST(DAY06_PART02, TEST01) {
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
K)L
K)YOU
I)SAN
)";
    /*
                               YOU
                              /
             G - H       J - K - L
            /           /
     COM - B - C - D - E - F
                    \
                     I - SAN
    */
    std::istringstream iss(map);
    const auto graph = map2graph(iss);
    auto path_to_you = path2(graph, "YOU");
    auto path_to_san = path2(graph, "SAN");
    drop_common_prefix(path_to_you, path_to_san);
    const auto dist = path_to_you.size() + path_to_san.size();
    ASSERT_EQ(dist, 4);
}

#endif // DO_UNIT_TEST
