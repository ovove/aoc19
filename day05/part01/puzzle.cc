
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
    if (mod2 != 0) throw std::runtime_error("Illegal mod3 in in");
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
    if (mod2 != 0) throw std::runtime_error("Illegal mod3 in add");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    os << val1;
    return pc + 2;
}

PC execute(Code& code, PC pc, std::istream& is, std::ostream& os) {
    const int mod_op = code.at(pc);
    const int op = mod_op % 100;
    switch (op) {
    case 1: return add(code, pc);
    case 2: return mul(code, pc);
    case 3: return in(code, pc, is);
    case 4: return out(code, pc, os);
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
    std::istringstream iss(std::string("1"));
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

TEST(DAY05_PART01, TEST01) {
    std::istringstream iss;
    std::ostringstream oss;
    std::vector code{1002, 4, 3, 4, 33};
    const std::vector expected{1002, 4, 3, 4, 99};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
}

TEST(DAY05_PART01, TEST02) {
    std::istringstream iss;
    std::ostringstream oss;
    std::vector code{1101, 100, -1, 4, 0};
    const std::vector expected{1101, 100, -1, 4, 99};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
}

TEST(DAY05_PART01, TEST3) {
    const std::string answer("42");
    std::istringstream iss(answer);
    std::ostringstream oss;
    std::vector code{3, 0, 4, 0, 99};
    const std::vector expected{42, 0, 4, 0, 99};
    auto& result = run(code, iss, oss);
    ASSERT_VECTOR_EQ(result, expected);
    ASSERT_EQ(oss.str(), answer);
}

#endif // DO_UNIT_TEST
