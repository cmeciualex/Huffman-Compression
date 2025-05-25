//
// Created by acmec on 4/23/2025.
//
#include "Node.h"
#ifndef HUFFMAN_H
#define HUFFMAN_H
#define BLOCK 4096
#define ALPHABET 256
#define MAGIC 0xDEADEAEF
#define MAX_CODE_SIZE (ALPHABET / 8)
#define MAX_TREE_SIZE (3 * ALPHABET - 1)

class Huffman {
public:
    static Node *buildTree(const uint64_t histogram[ALPHABET]);
    static bool rel(Node* a, Node* b);
};


#endif //HUFFMAN_H
