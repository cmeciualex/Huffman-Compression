//
// Created by acmec on 5/4/2025.
//

#ifndef CODE_H
#define CODE_H
#include <cstdint>
#define ALPHABET 256
#define MAX_CODE_SIZE (256 /8)
#include <ostream>
#include "Huffman.h"


class Code {
public:
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
    Code();
    uint32_t codeSize()const;
    bool codeFull();
    bool push_bit(Code *code,uint8_t bit);
    bool code_pop_bit(Code *code);
    friend std::ostream& operator<<(std::ostream& os, const Code& code);
    bool operator==(const Code& other) const;
    bool operator<(const Code& other) const;
    bool code_get_bit(uint32_t index, uint8_t* bit) const;
};

#endif //CODE_H
