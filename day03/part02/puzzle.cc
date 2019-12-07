
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

// #include <range/v3/all.hpp>

template <typename T> class TD;

namespace {

struct Point {
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
    Point& operator+=(const Point& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    int x{0};
    int y{0};
};
inline bool operator==(Point p1, Point p2) { return (p1.x == p2.x) and (p1.y == p2.y); }
inline std::ostream& operator<<(std::ostream& os, Point p) {
    return os << '(' << p.x << ',' << p.y << ')';
}

std::vector<Point> path_to_points(std::string_view path) {
    std::vector<Point> result;
    const std::map<std::string_view, Point> steps{{"L", {-1, 0}},
                                                  {"R", {+1, 0}},
                                                  {"U", {0, +1}},
                                                  {"D", {0, -1}}};
    Point pos{0, 0};
    result.push_back(pos);
    std::regex reg(R"(([LRUD])([1-9][0-9]*),?)");
    const std::cregex_iterator rbeg = std::cregex_iterator(std::begin(path), std::end(path), reg);
    const std::cregex_iterator rend = std::cregex_iterator();
    for (auto it = rbeg; it != rend; ++it) {
        const auto match = *it;
        const auto dir = match[1].str();
        const auto step = steps.at(dir);
        const auto dist = std::stoi(match[2].str());
        for (int d = 0; d < dist; ++d) {
            pos += step;
            result.push_back(pos);
        }
    }
    return result;
}

std::vector<Point> intersections(const std::vector<Point>& path1, const std::vector<Point>& path2) {
    std::vector<Point> result;
    for (auto p : path1) {
        if (p == Point{0, 0}) continue;
        const auto same_point = [p1 = p](auto p2){ return p1 == p2; };
        if (not std::any_of(std::begin(path2), std::end(path2), same_point)) continue;
        if (std::any_of(std::begin(result), std::end(result), same_point)) continue;
        result.push_back(p);
    }
    return result;
}

inline unsigned find_shortest_intersection_distance(std::string_view path1,
                                                    std::string_view path2) {
    const auto p1 = path_to_points(path1);
    const auto p2 = path_to_points(path2);
    const auto cross = intersections(p1, p2);
    std::vector<unsigned> distances;
    for (const auto x : cross) {
        const auto it1 = std::find(std::begin(p1), std::end(p1), x);
        const auto it2 = std::find(std::begin(p2), std::end(p2), x);
        const auto d1 = std::distance(std::begin(p1), it1);
        const auto d2 = std::distance(std::begin(p2), it2);
        const auto tot = d1 + d2;
        distances.push_back(tot);
    }
    const auto result = std::min_element(std::begin(distances), std::end(distances));
    return *result;
}

} // namespace

#if not defined(DO_UNIT_TEST)

#include <filesystem>
#include <fstream>
#include <iostream>

int main() {
    using std::filesystem::path;
    std::ifstream input(path(BINARY_DIR) / path("..") / path("input"));
    std::string path1, path2;
    std::getline(input, path1);
    std::getline(input, path2);
    const auto result = find_shortest_intersection_distance(path1, path2);
    std::cout << result << std::endl;
}

#else // DO_UNIT_TEST
#include <gtest/gtest.h>

TEST(DAY03_PART02, TEST01) {
    const std::string_view path1 = "R8,U5,L5,D3";
    const std::string_view path2 = "U7,R6,D4,L4";
    const auto result = find_shortest_intersection_distance(path1, path2);
    ASSERT_EQ(result, 30U);
}

TEST(DAY03_PART02, TEST02) {
    const std::string_view path1 = "R75,D30,R83,U83,L12,D49,R71,U7,L72";
    const std::string_view path2 = "U62,R66,U55,R34,D71,R55,D58,R83";
    const auto result = find_shortest_intersection_distance(path1, path2);
    ASSERT_EQ(result, 610U);
}

TEST(DAY03_PART02, TEST03) {
    const std::string_view path1 = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51";
    const std::string_view path2 = "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7";
    const auto result = find_shortest_intersection_distance(path1, path2);
    ASSERT_EQ(result, 410U);
}

TEST(DAY03_PART02, TEST04) {
    const std::string_view path1 = "R8,U5,L5,D6";
    const std::string_view path2 = "U7,R6,D4,L7";
    const auto result = find_shortest_intersection_distance(path1, path2);
    ASSERT_EQ(result, 30U);
}

TEST(DAY03_PART02, TEST05) {
    const std::string_view path1 = "R8,U5,L5,D6,L4";
    const std::string_view path2 = "U7,R6,D4,L7,D4";
    const auto result = find_shortest_intersection_distance(path1, path2);
    ASSERT_EQ(result, 30U);
}

#endif // DO_UNIT_TEST
