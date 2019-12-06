
#include <stdexcept>
#include <vector>

namespace {
template <typename T> inline std::vector<T>& run(std::vector<T>& code) {
    for (size_t pc = 0; pc < code.size();) {
        const T op = code[pc];
        if (op == 99) return code;
        if (op != 1 and op != 2) throw std::runtime_error("unknown opcode");
        static_cast<void>(code.at(pc + 4));
        const T addr1 = code.at(pc + 1);
        const T addr2 = code.at(pc + 2);
        const T addr3 = code.at(pc + 3);
        if (op == 1)
            code[addr3] = code[addr1] + code[addr2];
        else
            code[addr3] = code[addr1] * code[addr2];
        pc += 4;
    }
    throw std::runtime_error("missing end of code");
}
} // namespace

#if not defined(DO_UNIT_TEST)

#include <iostream>

std::vector<unsigned> code = {
#include "../input"
};

int main() {
    code.at(1) = 12;
    code.at(2) = 2;
    std::cout << run(code).at(0) << std::endl;
}

#else // DO_UNIT_TEST

#include <gtest/gtest.h>

#define ASSERT_VECTOR_EQ(arr1, arr2)                                                               \
    ASSERT_EQ(arr1.size(), arr2.size());                                                           \
    for (size_t n = 0; n < arr1.size(); n++) {                                                     \
        ASSERT_EQ(arr1[n], arr2[n]) << "  Vectors different at index " << n;                       \
    }

TEST(DAY02_PART01, TEST01) {
    std::vector<unsigned> code{1, 0, 0, 0, 99};
    const std::vector<unsigned> expected{2, 0, 0, 0, 99};
    const std::vector<unsigned>& result = run(code);
    ASSERT_VECTOR_EQ(result, expected);
}

TEST(DAY02_PART01, TEST02) {
    std::vector<unsigned> code{2, 3, 0, 3, 99};
    const std::vector<unsigned> expected{2, 3, 0, 6, 99};
    const std::vector<unsigned>& result = run(code);
    ASSERT_VECTOR_EQ(result, expected);
}

TEST(DAY02_PART01, TEST03) {
    std::vector<unsigned> code{2, 4, 4, 5, 99, 0};
    const std::vector<unsigned> expected{2, 4, 4, 5, 99, 9801};
    const std::vector<unsigned>& result = run(code);
    ASSERT_VECTOR_EQ(result, expected);
}

TEST(DAY02_PART01, TEST04) {
    std::vector<unsigned> code{1, 1, 1, 4, 99, 5, 6, 0, 99};
    const std::vector<unsigned> expected{30, 1, 1, 4, 2, 5, 6, 0, 99};
    const std::vector<unsigned>& result = run(code);
    ASSERT_VECTOR_EQ(result, expected);
}

#endif // DO_UNIT_TEST
