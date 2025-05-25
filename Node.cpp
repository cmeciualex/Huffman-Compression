// Node.cpp
#include "Node.h"

Node::Node(uint8_t symbol, uint64_t frequency) {
    this->left = nullptr;
    this->right = nullptr;
    this->symbol = symbol;
    this->frequency = frequency;
}
Node* Node::combine(Node* left, Node* right) {
    Node* node = new Node('$', left->frequency + right->frequency);
    node->left = left;
    node->right = right;
    return node;
}