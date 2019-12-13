
#include <ios>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <sstream>
#include <sstream>
#include <fstream>
#include <array>
#include <iterator>
#include <algorithm>

//#include <fmt/format.h>

namespace {

using Code = std::vector<int>;
using PC = std::size_t;

using Mod123 = std::tuple<int, int, int>;

Mod123 mod123(const Code& code, PC pc) {
    const int mod_op = code.at(pc);
    const int mod123 = mod_op / 100;
    const int mod1 = mod123 % 10;
    const int mod2 = (mod123 / 10) % 10;
    const int mod3 = mod123 / 100;
    // if (mod1 != 0 and mod1 != 1) throw std::runtime_error(fmt::format("Illegal mod1 {} at pc {}"));
    // if (mod2 != 0 and mod2 != 1) throw std::runtime_error(fmt::format("Illegal mod2 {} at pc {}"));
    // if (mod3 != 0) throw std::runtime_error(fmt::format("Illegal mod3 {} at pc {}"));
    if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1.");
    if (mod2 != 0 and mod2 != 1) throw std::runtime_error("Illegal mod2.");
    if (mod3 != 0) throw std::runtime_error("Illegal mod3.");
    return {mod1, mod2, mod3};
}

PC add(Code& code, PC pc) {
    const auto [mod1, mod2, mod3] = mod123(code, pc);
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int val2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    const int addr3 = code.at(pc + 3);
    code.at(addr3) = val1 + val2;
    return pc + 4;
}

PC mul(Code& code, PC pc) {
    const auto [mod1, mod2, mod3] = mod123(code, pc);
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int val2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    const int addr3 = code.at(pc + 3);
    code.at(addr3) = val1 * val2;
    return pc + 4;
}

PC in(Code& code, PC pc, std::istream& is) {
    const auto [mod1, mod2, _] = mod123(code, pc);
    if (mod1 != 0) throw std::runtime_error("Illegal mod1 in in");
    if (mod2 != 0) throw std::runtime_error("Illegal mod2 in in");
    const int addr1 = code.at(pc + 1);
    int val;
    is >> val;
    code.at(addr1) = val;
    return pc + 2;
}

PC out(Code& code, PC pc, std::ostream& os) {
    const auto [mod1, mod2, _] = mod123(code, pc);
    if (mod2 != 0) throw std::runtime_error("Illegal mod2");
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    os << val1;
    return pc + 2;
}

PC jt(Code& code, PC pc) {
    const auto [mod1, mod2, mod3] = mod123(code, pc);
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int addr2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    return (val1 != 0) ? addr2 : (pc + 3);
}

PC jf(Code& code, PC pc) {
    const auto [mod1, mod2, mod3] = mod123(code, pc);
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int addr2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    return (val1 == 0) ? addr2 : (pc + 3);
}

PC lt(Code& code, PC pc) {
    const auto [mod1, mod2, mod3] = mod123(code, pc);
    const int val1 = (mod1 == 0) ? code.at(code.at(pc + 1)) : code.at(pc + 1);
    const int val2 = (mod2 == 0) ? code.at(code.at(pc + 2)) : code.at(pc + 2);
    const int addr3 = code.at(pc + 3);
    code.at(addr3) = (val1 < val2) ? 1 : 0;
    return pc + 4;
}

PC eq(Code& code, PC pc) {
    const auto [mod1, mod2, mod3] = mod123(code, pc);
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

class Amp {
public:
    explicit Amp(const Code& code, int phase) : code_{code}, phase_{phase} {}
    int run(int in) {
        std::ostringstream tmp;
        tmp << phase_ << ' ' << in;
        std::istringstream iss(tmp.str());
        std::ostringstream oss;
        ::run(code_, iss, oss);
        int res = std::stoi(oss.str());
        return res;
    }
private:
    Code code_;
    const int phase_;
};

class AmpRack {
public:
    template <typename Phases>
    AmpRack(const Code& code, Phases&& phases)
        : amps_{construct_(code, std::forward<Phases>(phases))} {}

    int run(int init = 0) {
        int output = init;
        for (auto& amp : amps_) {
            int input = output;
            output = amp.run(input);
        }
        return output;
    }
private:
    template <typename Phases>
    static std::vector<Amp> construct_(const Code& code, Phases&& phases) {
        std::vector<Amp> amps;
        amps.reserve(phases.size());
        for (int phase : std::forward<Phases>(phases)) amps.emplace_back(code, phase);
        return amps;
    }
    std::vector<Amp> amps_;
};

} // namespace

#if not defined(DO_UNIT_TEST)

#include <iostream>
#include <sstream>
#include <string>

std::vector code = {
#include "../input"
};

int main() {
    std::vector phases{0, 1, 2, 3, 4};
    int max_out = 0;
    do {
        AmpRack amps(code, phases);
        const int out = amps.run();
        if (out > max_out) max_out = out;
    } while (std::next_permutation(std::begin(phases), std::end(phases)));
    std::cout << max_out << std::endl;
}

#else // DO_UNIT_TEST

#include <gtest/gtest.h>
#include <string>

#define ASSERT_VECTOR_EQ(arr1, arr2)                                                               \
    ASSERT_EQ(arr1.size(), arr2.size());                                                           \
    for (size_t n = 0; n < arr1.size(); n++) {                                                     \
        ASSERT_EQ(arr1[n], arr2[n]) << "  Vectors different at index " << n;                       \
    }

TEST(DAY07_PART01, TEST01) {
    const std::vector code { 3, 15, 3, 16, 1002, 16, 10, 16, 1, 16, 15, 15, 4, 15, 99, 0, 0 };
    AmpRack amps(code, std::vector{4, 3, 2, 1, 0});
    const auto output = amps.run();
    ASSERT_EQ(output, 43210);
}

TEST(DAY07_PART01, TEST02) {
    const std::vector code{3, 23, 3,  24, 1002, 24, 10, 24, 1002, 23, -1, 23, 101,
                           5, 23, 23, 1,  24,   23, 23, 4,  23,   99, 0,  0};
    AmpRack amps(code, std::vector{0, 1, 2, 3, 4});
    const auto output = amps.run();
    ASSERT_EQ(output, 54321);
}

TEST(DAY07_PART01, TEST03) {
    const std::vector code{3,    31, 3,  32, 1002, 32, 10, 32, 1001, 31, -2, 31,
                           1007, 31, 0,  33, 1002, 33, 7,  33, 1,    33, 31, 31,
                           1,    32, 31, 31, 4,    31, 99, 0,  0,    0};
    AmpRack amps(code, std::vector{1, 0, 4, 3, 2});
    const auto output = amps.run();
    ASSERT_EQ(output, 65210);
}


#endif // DO_UNIT_TEST
