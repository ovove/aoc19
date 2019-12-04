
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <algorithm>

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
inline bool operator==(Point p1, Point p2) {
    return (p1.x == p2.x) and (p1.y == p2.y);
}

std::vector<Point> path_to_points(std::string_view path) {
    std::vector<Point> result;
    const std::map<std::string_view, Point> steps{{"L", {-1, 0}},
                                                  {"R", {+1, 0}},
                                                  {"U", {0, +1}},
                                                  {"D", {0, -1}}};
    Point pos{0, 0};
    for (std::string_view::size_type  beg = 0; beg != std::string_view::npos;) {
        const auto end = path.find(',', beg);
        const auto motion = path.substr(beg, end - beg);
        beg = (end != std::string_view::npos) ? end + 1 : std::string_view::npos;
        const auto direction = motion.substr(0, 1);
        const auto& step = steps.at(direction);
        const auto distance = motion.substr(1);
        for (int dist = std::stoi(std::string(distance)); dist; --dist) {
            pos += step;
            if (std::find(std::begin(result), std::end(result), pos) == std::end(result)) {
                result.push_back(pos);
            }
        }
    }
    return result;
}

std::vector<Point> intersections(const std::vector<Point>& path1, const std::vector<Point>& path2) {
    std::vector<Point> result;
    for (auto p: path1) {
        if (std::find(std::begin(path2), std::end(path2), p) == std::end(path2)) continue;
        result.push_back(p);
    }
    return result;
}

unsigned manhattan(Point p) {
    return std::abs(p.x) + std::abs(p.y);
}

inline unsigned find_shortest_intersection_distance(std::string_view path1,
                                                    std::string_view path2) {
    const auto p1 = path_to_points(path1);
    const auto p2 = path_to_points(path2);
    const auto cross = intersections(p1, p2);
    std::vector<unsigned> distances(cross.size());
    std::transform(std::begin(cross), std::end(cross), std::begin(distances), manhattan);
    const auto result = std::min_element(std::begin(distances), std::end(distances));
    return *result;
}

} // namespace

#if not defined(DO_UNIT_TEST)

#include <iostream>
#include <fstream>
#include <filesystem>

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

TEST(DAY03_PART01, TEST01) {
    const std::string_view path1 = "R8,U5,L5,D3";
    const std::string_view path2 = "U7,R6,D4,L4";
    const auto result = find_shortest_intersection_distance(path1, path2);
    ASSERT_EQ(result, 6U);
}

TEST(DAY03_PART01, TEST02) {
    const std::string_view path1 = "R75,D30,R83,U83,L12,D49,R71,U7,L72";
    const std::string_view path2 = "U62,R66,U55,R34,D71,R55,D58,R83";
    const auto result = find_shortest_intersection_distance(path1, path2);
    ASSERT_EQ(result, 159U);
}

TEST(DAY03_PART01, TEST03) {
    const std::string_view path1 = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51";
    const std::string_view path2 = "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7";
    const auto result = find_shortest_intersection_distance(path1, path2);
    ASSERT_EQ(result, 135U);
}

#endif // DO_UNIT_TEST
