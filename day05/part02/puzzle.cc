
#include <ios>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {

using Code = std::vector<int>;
using PC = std::size_t;

PC add(Code& code, PC pc) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = (mod123 / 10) % 10;
    const int mod3 = mod123 / 100;
    if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1 in add");
    if (mod2 != 0 and mod2 != 1) throw std::runtime_error("Illegal mod2 in add");
    if (mod3 != 0) throw std::runtime_error("Illegal mod3 in add");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int val2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    const int addr3 = code.at(pc + 3);
    code.at(addr3) = val1 + val2;
    return pc + 4;
}

PC mul(Code& code, PC pc) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = (mod123 / 10) % 10;
    const int mod3 = mod123 / 100;
    if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1 in mul");
    if (mod2 != 0 and mod2 != 1) throw std::runtime_error("Illegal mod2 in mul");
    if (mod3 != 0) throw std::runtime_error("Illegal mod3 in mul");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int val2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    const int addr3 = code.at(pc + 3);
    code.at(addr3) = val1 * val2;
    return pc + 4;
}

PC in(Code& code, PC pc, std::istream& is) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = mod123 / 10;
    if (mod1 != 0) throw std::runtime_error("Illegal mod1 in in");
    if (mod2 != 0) throw std::runtime_error("Illegal mod2 in in");
    const int addr1 = code.at(pc + 1);
    int val;
    is >> val;
    code.at(addr1) = val;
    return pc + 2;
}

PC out(Code& code, PC pc, std::ostream& os) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = mod123 / 10;
    if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1 in out");
    if (mod2 != 0) throw std::runtime_error("Illegal mod2 in add");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    os << val1;
    return pc + 2;
}

PC jt(Code& code, PC pc) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = (mod123 / 10) % 10;
    const int mod3 = mod123 / 100;
    if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1 in jt");
    if (mod2 != 0 and mod2 != 1) throw std::runtime_error("Illegal mod2 in jt");
    if (mod3 != 0) throw std::runtime_error("Illegal mod3 in jt");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int addr2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    return (val1 != 0) ? addr2 : (pc + 3);
}

PC jf(Code& code, PC pc) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = (mod123 / 10) % 10;
    const int mod3 = mod123 / 100;
    if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1 in jf");
    if (mod2 != 0 and mod2 != 1) throw std::runtime_error("Illegal mod2 in jf");
    if (mod3 != 0) throw std::runtime_error("Illegal mod3 in jf");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int addr2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    return (val1 == 0) ? addr2 : (pc + 3);
}

PC lt(Code& code, PC pc) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = (mod123 / 10) % 10;
    const int mod3 = (mod123 / 100) % 10;
    if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1 in lt");
    if (mod2 != 0 and mod2 != 1) throw std::runtime_error("Illegal mod2 in lt");
    if (mod3 != 0) throw std::runtime_error("Illegal mod3 in lt");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int val2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    const int addr3 = code.at(pc + 3);
    code.at(addr3) = (val1 < val2) ? 1 : 0;
    return pc + 4;
}

PC eq(Code& code, PC pc) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = (mod123 / 10) % 10;
    const int mod3 = (mod123 / 100) % 10;
    if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1 in lt");
    if (mod2 != 0 and mod2 != 1) throw std::runtime_error("Illegal mod2 in lt");
    if (mod3 != 0) throw std::runtime_error("Illegal mod3 in lt");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int val2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    const int addr3 = code.at(pc + 3);
    code.at(addr3) = (val1 == val2) ? 1 : 0;
    return pc + 4;
}

PC execute(Code& code, PC pc, std::istream& is, std::ostream& os) {
    const int mod_op = code.at(pc);
    const int op = mod_op % 100;
    switch (op) {
    case 1: return add(code, pc);
    case 2: return mul(code, pc);
    case 3: return in(code, pc, is);
    case 4: return out(code, pc, os);
    case 5: return jt(code, pc);
    case 6: return jf(code, pc);
    case 7: return lt(code, pc);
    case 8: return eq(code, pc);
    case 99: return code.size();
    default: throw std::runtime_error("Illegal op code");
    }
}

Code& run(Code& code, std::istream& is, std::ostream& os) {
    for (size_t pc = 0; pc < code.size();) {
        pc = execute(code, pc, is, os);
    }
    return code;
}

} // namespace

#if not defined(DO_UNIT_TEST)

#include <iostream>
#include <sstream>
#include <string>

std::vector code = {
#include "../input"
};

int main() {
    std::istringstream iss(std::string("5"));
    std::ostringstream oss;
    run(code, iss, oss);
    const auto pos_non_zero = oss.str().find_first_not_of("0");
    const auto result = oss.str().substr(pos_non_zero);
    std::cout << result << std::endl;
}

#else // DO_UNIT_TEST

#include <gtest/gtest.h>
#include <sstream>
#include <string>

#define ASSERT_VECTOR_EQ(arr1, arr2)                                                               \
    ASSERT_EQ(arr1.size(), arr2.size());                                                           \
    for (size_t n = 0; n < arr1.size(); n++) {                                                     \
        ASSERT_EQ(arr1[n], arr2[n]) << "  Vectors different at index " << n;                       \
    }

TEST(DAY05_PART02, TEST01) {
    std::istringstream iss(std::string("8"));
    std::ostringstream oss;
    //               0  1  2  3   4  5  6  7   8   9 10
    std::vector code{3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8};
    const std::vector expected{3, 9, 8, 9, 10, 9, 4, 9, 99, 1, 8};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
    ASSERT_EQ(oss.str(), "1");
}

TEST(DAY05_PART02, TEST02) {
    std::istringstream iss(std::string("8"));
    std::ostringstream oss;
    //               0  1  2  3   4  5  6  7   8   9 10
    std::vector code{3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8};
    const std::vector expected{3, 9, 7, 9, 10, 9, 4, 9, 99, 0, 8};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
    ASSERT_EQ(oss.str(), "0");
}

TEST(DAY05_PART02, TEST03) {
    std::istringstream iss(std::string("8"));
    std::ostringstream oss;
    //               0  1     2   3  4  5  6  7   8
    std::vector code{3, 3, 1108, -1, 8, 3, 4, 3, 99};
    const std::vector expected{3, 3, 1108, 1, 8, 3, 4, 3, 99};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
    ASSERT_EQ(oss.str(), "1");
}

TEST(DAY05_PART02, TEST04) {
    std::istringstream iss(std::string("8"));
    std::ostringstream oss;
    //               0  1     2   3  4  5  6  7   8
    std::vector code{3, 3, 1107, -1, 8, 3, 4, 3, 99};
    const std::vector expected{3, 3, 1107, 0, 8, 3, 4, 3, 99};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
    ASSERT_EQ(oss.str(), "0");
}

TEST(DAY05_PART02, TEST05) {
    std::istringstream iss(std::string("8"));
    std::ostringstream oss;
    //               0   1  2   3   4  5   6   7   8, 9, 10, 11, 12,13,14,15
    std::vector code{3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9};
    const std::vector expected{3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, 8, 1, 1, 9};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
    ASSERT_EQ(oss.str(), "1");
}

TEST(DAY05_PART02, TEST06) {
    std::istringstream iss(std::string("8"));
    std::ostringstream oss;
    //               0  1     2   3  4     5  6  7   8, 9, 10, 11,12
    std::vector code{3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1};
    const std::vector expected{3, 3, 1105, 8, 9, 1101, 0, 0, 12, 4, 12, 99, 1};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
    ASSERT_EQ(oss.str(), "1");
}

TEST(DAY05_PART02, TEST07) {
    std::istringstream iss(std::string("7"));
    std::ostringstream oss;
    std::vector code{3,    21,   1008, 21, 8,    20, 1005, 20,  22,  107,  8,    21,
                     20,   1006, 20,   31, 1106, 0,  36,   98,  0,   0,    1002, 21,
                     125,  20,   4,    20, 1105, 1,  46,   104, 999, 1105, 1,    46,
                     1101, 1000, 1,    20, 4,    20, 1105, 1,   46,  98,   99};
    run(code, iss, oss);
    ASSERT_EQ(oss.str(), "999");
}

TEST(DAY05_PART02, TEST08) {
    std::istringstream iss(std::string("8"));
    std::ostringstream oss;
    std::vector code{3,    21,   1008, 21, 8,    20, 1005, 20,  22,  107,  8,    21,
                     20,   1006, 20,   31, 1106, 0,  36,   98,  0,   0,    1002, 21,
                     125,  20,   4,    20, 1105, 1,  46,   104, 999, 1105, 1,    46,
                     1101, 1000, 1,    20, 4,    20, 1105, 1,   46,  98,   99};
    run(code, iss, oss);
    ASSERT_EQ(oss.str(), "1000");
}

TEST(DAY05_PART02, TEST09) {
    std::istringstream iss(std::string("9"));
    std::ostringstream oss;
    std::vector code{3,    21,   1008, 21, 8,    20, 1005, 20,  22,  107,  8,    21,
                     20,   1006, 20,   31, 1106, 0,  36,   98,  0,   0,    1002, 21,
                     125,  20,   4,    20, 1105, 1,  46,   104, 999, 1105, 1,    46,
                     1101, 1000, 1,    20, 4,    20, 1105, 1,   46,  98,   99};
    run(code, iss, oss);
    ASSERT_EQ(oss.str(), "1001");
}

#endif // DO_UNIT_TEST
