
#include <stdexcept>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

namespace {

class Computer {
public:
    using Code = std::vector<int>;
    using Queue = std::queue<int>;

    explicit Computer(const Code& code) : code_{code} {}

    Computer(const Code& code, const Queue& inq) : code_{code}, inq_{inq} {}

    void run() {
        yield_ = false;
        if (pc_ >= code_.size()) {
            outq_.push(inq_.front());
            inq_.pop();
        }
        while (pc_ < code_.size() and not yield_) execute();
    }

    Queue& inq() { return inq_; }
    Queue& outq() { return outq_; }

private:
    using Mod123 = std::tuple<int, int, int>;
    using PC = std::size_t;

    Code code_;

    Queue inq_{};
    Queue outq_{};

    PC pc_{0};
    bool yield_{false};

    void execute() {
        const int mod_op = code_.at(pc_);
        const int op = mod_op % 100;
        switch (op) {
        case 1: add(); break;
        case 2: mul(); break;
        case 3: in(); break;
        case 4: out(); break;
        case 5: jt(); break;
        case 6: jf(); break;
        case 7: lt(); break;
        case 8: eq(); break;
        case 99: hlt(); break;
        default: throw std::runtime_error("Illegal op code");
        }
    }

    Mod123 mod123() const {
        const int mod_op = code_.at(pc_);
        const int mod123 = mod_op / 100;
        const int mod1 = mod123 % 10;
        const int mod2 = (mod123 / 10) % 10;
        const int mod3 = mod123 / 100;
        if (mod1 != 0 and mod1 != 1) throw std::runtime_error("Illegal mod1.");
        if (mod2 != 0 and mod2 != 1) throw std::runtime_error("Illegal mod2.");
        if (mod3 != 0) throw std::runtime_error("Illegal mod3.");
        return {mod1, mod2, mod3};
    }

    void add() {
        const auto [mod1, mod2, mod3] = mod123();
        const int val1 = (mod1 == 0) ? code_.at(code_.at(pc_ + 1)) : code_.at(pc_ + 1);
        const int val2 = (mod2 == 0) ? code_.at(code_.at(pc_ + 2)) : code_.at(pc_ + 2);
        const int addr3 = code_.at(pc_ + 3);
        code_.at(addr3) = val1 + val2;
        pc_ += 4;
    }

    void mul() {
        const auto [mod1, mod2, mod3] = mod123();
        const int val1 = (mod1 == 0) ? code_.at(code_.at(pc_ + 1)) : code_.at(pc_ + 1);
        const int val2 = (mod2 == 0) ? code_.at(code_.at(pc_ + 2)) : code_.at(pc_ + 2);
        const int addr3 = code_.at(pc_ + 3);
        code_.at(addr3) = val1 * val2;
        pc_ += 4;
    }

    void in() {
        yield_ = (inq_.size() == 0);
        if (yield_) return;
        const auto [mod1, mod2, _] = mod123();
        if (mod1 != 0) throw std::runtime_error("Illegal mod1 in in");
        if (mod2 != 0) throw std::runtime_error("Illegal mod2 in in");
        const int addr1 = code_.at(pc_ + 1);
        int val;
        val = inq_.front();
        inq_.pop();
        code_.at(addr1) = val;
        pc_ += 2;
    }

    void out() {
        const auto [mod1, mod2, _] = mod123();
        if (mod2 != 0) throw std::runtime_error("Illegal mod2");
        const int val1 = (mod1 == 0) ? code_.at(code_.at(pc_ + 1)) : code_.at(pc_ + 1);
        outq_.push(val1);
        pc_ += 2;
    }

    void jt() {
        const auto [mod1, mod2, mod3] = mod123();
        const int val1 = (mod1 == 0) ? code_.at(code_.at(pc_ + 1)) : code_.at(pc_ + 1);
        const int addr2 = (mod2 == 0) ? code_.at(code_.at(pc_ + 2)) : code_.at(pc_ + 2);
        pc_ = (val1 != 0) ? addr2 : (pc_ + 3);
    }

    void jf() {
        const auto [mod1, mod2, mod3] = mod123();
        const int val1 = (mod1 == 0) ? code_.at(code_.at(pc_ + 1)) : code_.at(pc_ + 1);
        const int addr2 = (mod2 == 0) ? code_.at(code_.at(pc_ + 2)) : code_.at(pc_ + 2);
        pc_ =  (val1 == 0) ? addr2 : (pc_ + 3);
    }

    void lt() {
        const auto [mod1, mod2, mod3] = mod123();
        const int val1 = (mod1 == 0) ? code_.at(code_.at(pc_ + 1)) : code_.at(pc_ + 1);
        const int val2 = (mod2 == 0) ? code_.at(code_.at(pc_ + 2)) : code_.at(pc_ + 2);
        const int addr3 = code_.at(pc_ + 3);
        code_.at(addr3) = (val1 < val2) ? 1 : 0;
        pc_ += 4;
    }

    void eq() {
        const auto [mod1, mod2, mod3] = mod123();
        const int val1 = (mod1 == 0) ? code_.at(code_.at(pc_ + 1)) : code_.at(pc_ + 1);
        const int val2 = (mod2 == 0) ? code_.at(code_.at(pc_ + 2)) : code_.at(pc_ + 2);
        const int addr3 = code_.at(pc_ + 3);
        code_.at(addr3) = (val1 == val2) ? 1 : 0;
        pc_ += 4;
    }

    void hlt() { pc_ = code_.size(); }

}; // Computer

class Amp {
public:
    Amp(const Computer::Code& code, int phase) : comp_{code} { comp_.inq().push(phase); }

    int run(int in) {
        comp_.inq().push(in);
        comp_.run();
        const int out = comp_.outq().front();
        comp_.outq().pop();
        return out;
    }

private:
    Computer comp_;
};

class AmpRack {
public:
    using Phases = std::vector<int>;

    AmpRack(const Computer::Code& code, const Phases& phases)
        : amps_{construct_(code, phases)} {}

    int run(int init = 0) {
        int prev_output = -1;
        int output = init;
        while (output != prev_output) {
            prev_output = output;
            for (auto& amp : amps_) {
                int input = output;
                output = amp.run(input);
            }
        }
        return output;
    }

private:
    static std::vector<Amp> construct_(const Computer::Code& code, const Phases& phases) {
        std::vector<Amp> amps;
        amps.reserve(phases.size());
        for (int phase : phases) amps.emplace_back(code, phase);
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
    std::vector phases{5, 6, 7, 8, 9};
    int max_out = 0;
    do {
        AmpRack amps(code, phases);
        const int out = amps.run();
        if (out > max_out) max_out = out;
    } while (std::next_permutation(std::begin(phases), std::end(phases)));
    std::cout << max_out << std::endl; // 63103596
}

#else // DO_UNIT_TEST

#include <gtest/gtest.h>
#include <string>

TEST(DAY07_PART02, TEST01) {
    const Computer::Code code{3,  26, 1001, 26,   -4, 26, 3,  27,   1002, 27, 2,  27, 1, 27, 26,
                              27, 4,  27,   1001, 28, -1, 28, 1005, 28,   6,  99, 0,  0, 5};
    const AmpRack::Phases phases{9, 8, 7, 6, 5};
    AmpRack amps(code, phases);
    const auto output = amps.run();
    ASSERT_EQ(output, 139629729);
}

TEST(DAY07_PART02, TEST02) {
    const Computer::Code code{3,    52, 1001, 52, -5,   52, 3,    53,   1,    52, 56,   54,
                              1007, 54, 5,    55, 1005, 55, 26,   1001, 54,   -5, 54,   1105,
                              1,    12, 1,    53, 54,   53, 1008, 54,   0,    55, 1001, 55,
                              1,    55, 2,    53, 55,   53, 4,    53,   1001, 56, -1,   56,
                              1005, 56, 6,    99, 0,    0,  0,    0,    10};
    const AmpRack::Phases phases{9, 7, 8, 5, 6};
    AmpRack amps(code, phases);
    const auto output = amps.run();
    ASSERT_EQ(output, 18216);
}

#endif // DO_UNIT_TEST
