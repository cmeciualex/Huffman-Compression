//
// Created by acmec on 5/4/2025.
//

#include "Code.h"
#include <string.h>
#include <cstring>  // pentru C++


Code::Code() {
    this->top=0;
    memset(this->bits, 0, sizeof(this->bits));
}

uint32_t Code:: codeSize() const{
    return this->top;
}

bool Code::codeFull() {
    return this->top == MAX_CODE_SIZE;
}

bool Code::push_bit(Code *code,uint8_t bit) {
    if (codeFull())
        return false;
    uint32_t byte_index = code->top / 8;
    uint8_t bit_index = code->top % 8;

    if (bit) {
        code->bits[byte_index] |= (1 << bit_index);
    } else {
        code->bits[byte_index] &= ~(1 << bit_index);
    }

    code->top++;
    return true;
}

bool Code::code_pop_bit(Code *code) {
    if (this->top==0) {
        return false;
    }
    code->top--;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Code& code) {
    for (uint32_t i = 0; i < code.top; ++i) {
        uint32_t byte_index = i / 8;
        uint8_t bit_index = i % 8;
        uint8_t bit = (code.bits[byte_index] >> bit_index) & 1;
        os << (int)bit;
    }
    return os;
}

bool Code::operator==(const Code& other) const {
    if (this->top != other.top) {
        return false;
    }

    for (size_t i = 0; i < MAX_CODE_SIZE; ++i) {
        if (this->bits[i] != other.bits[i]) {
            return false;
        }
    }
    return true;
}

bool Code::operator<(const Code& other) const {
    if (this->top != other.top) {
        return this->top < other.top;
    }
    return std::memcmp(this->bits, other.bits, MAX_CODE_SIZE) < 0;
}

bool Code::code_get_bit(uint32_t index, uint8_t* bit) const {
    if (index >= this->top) {
        return false; // Index invalid
    }

    uint32_t byte_index = index / 8;
    uint8_t bit_index = index % 8;

    *bit = (this->bits[byte_index] >> bit_index) & 1;
    return true;
}



