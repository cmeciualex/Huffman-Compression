// Node.h
#pragma once
#include <cstdint>

class Node {
public:
    uint8_t symbol;
    uint64_t frequency;
    Node* left;
    Node* right;

    Node(uint8_t symbol, uint64_t frequency);

    static Node* combine(Node* left, Node* right);
};