#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <unistd.h>


constexpr size_t REG_BITS = 4;
constexpr size_t REGS_COUNT = (1 << REG_BITS) - 1;
constexpr size_t REG_BITS_MASK = (1 << REG_BITS) - 1;

[[noreturn]] void error(const std::string& msg) {
    std::cout << msg << std::endl;
    exit(1);
}

void assert_valid_reg(size_t reg) {
    if (reg > REGS_COUNT) {
        std::cout << "invalid register: " << reg << std::endl;
        exit(1);
    }
}

int64_t sign_extend(uint64_t arg, size_t bits) {
    return (static_cast<int64_t>(arg) << bits) >> bits;
}


constexpr size_t ZERO_FLAG_BIT = 1;
constexpr size_t WINNING_FLAG_BIT = 4;

constexpr size_t ZERO_FLAG_MASK = 1 << WINNING_FLAG_BIT;
constexpr size_t WINNING_FLAG_MASK = 1 << WINNING_FLAG_BIT;

struct State {
    size_t ip = 0;
    uint64_t regs[REGS_COUNT];
    uint64_t flags = 0;
    bool stopped = false;
};


class Op {
public:
    virtual void Execute(State* state) const = 0;
};


class AddOp : public Op {
public:
    AddOp(uint64_t encoding) {
        reg_ = encoding & REG_BITS_MASK;
        encoding >>= REG_BITS;
        arg_ = sign_extend(encoding, REG_BITS);
        assert_valid_reg(reg_);
    }

    void Execute(State* state) const override {
        state->regs[reg_] += arg_;
    }

private:
    int reg_ = 0;
    int64_t arg_ = 0;
};


class MulOp : public Op {
public:
    MulOp(uint64_t encoding) {
        reg_ = encoding & REG_BITS_MASK;
        encoding >>= REG_BITS;
        arg_ = sign_extend(encoding, REG_BITS);
        assert_valid_reg(reg_);
    }

    void Execute(State* state) const override {
        state->regs[reg_] *= arg_;
    }

private:
    int reg_ = 0;
    int64_t arg_ = 0;
};


class CmpOp : public Op {
public:
    CmpOp(uint64_t encoding) {
        left_ = encoding & REG_BITS_MASK;
        encoding >>= REG_BITS;
        right_ = encoding & REG_BITS_MASK;
        encoding >>= REG_BITS;

        assert_valid_reg(left_);
        assert_valid_reg(right_);
        if (encoding != 0) {
            error("Invalid encoding of `cmp` instruction.");
        }
    }

    void Execute(State* state) const override {
        uint64_t res = state->regs[left_] - state->regs[right_];
        if (res == 0) {
            state->flags |= ZERO_FLAG_MASK;
        }
    }

private:
    size_t left_ = 0;
    size_t right_ = 0;
};


class JmpOp : public Op {
public:
    static constexpr size_t CONDITION_BITS = 4;
    static constexpr uint64_t CONDITION_MASK = (1 << CONDITION_BITS) - 1;
    static constexpr uint64_t JMP = 0;
    static constexpr uint64_t JZ = 1;

    JmpOp(uint64_t encoding) {
        condition_ = encoding & CONDITION_MASK;
        encoding >>= CONDITION_BITS;
        offset_ = sign_extend(encoding, CONDITION_BITS);
    }

    void Execute(State* state) const override {
        switch (condition_) {
            case JMP:
                state->ip += offset_;
                break;
            case JZ:
                if (state->flags & ZERO_FLAG_MASK) {
                    state->ip += offset_;
                }
                break;
            default:
                error("Invalid condition in `jmp` instruction.");
        }
    }

private:
    uint64_t condition_ = 0;
    int64_t offset_ = 0;
};


class HaltOp : public Op {
public:
    HaltOp(uint64_t encoding) {
        if (encoding != 0xdeadbeef) {
            error("Invalid encoding of `halt` instruction.");
        }
    }

    void Execute(State* state) const override {
        state->stopped = true;
    }
};


std::unique_ptr<Op> Decode(char op, uint64_t encoding) {
    switch (op) {
        case 1:
            return std::make_unique<HaltOp>(encoding);
        case 2:
            return std::make_unique<AddOp>(encoding);
        case 3:
            return std::make_unique<MulOp>(encoding);
        case 4:
            return std::make_unique<CmpOp>(encoding);
        case 5:
            return std::make_unique<JmpOp>(encoding);
        default:
            error("Invalid instruction encoding found.");
    }
}

std::vector<std::unique_ptr<Op>> ReadProgram() {
    char buf[20000];
    ssize_t buf_size = read(0, buf, sizeof(buf));
    if (buf_size < 0) {
        error("Cannot read program.");
    }

    size_t op_size = *reinterpret_cast<const uint64_t*>(buf);
    if (op_size + sizeof(uint64_t) != buf_size) {
        error("Invalid program header.");
    }

    std::vector<std::unique_ptr<Op>> ops;
    const char* data = buf + sizeof(uint64_t);
    size_t pos = 0;
    while (pos + 4 < op_size) {
        char op = data[pos];
        uint64_t encoding = *reinterpret_cast<const uint64_t*>(data + pos + 1);
        ops.emplace_back(Decode(op, encoding));
        pos += sizeof(char) + sizeof(uint64_t);
    }

    return ops;
}


int main() {
    std::vector<std::unique_ptr<Op>> ops = ReadProgram();

    State state;

    for (size_t i = 0; i < REGS_COUNT; i++) {
        state.regs[i] = 0;
    }

    while (!state.stopped) {
        if (state.ip >= ops.size()) {
            error("Invalid program: ip is out-of-bounds. Did you forget `hlt` instruction?");
        }

        ops[state.ip]->Execute(&state);
        ++state.ip;
    }

    if (state.flags & WINNING_FLAG_MASK) {
        std::cout << "here is your flag: skoltech{vms_4r3_4w3s0m3}" << std::endl;
    }

    return 0;
}
