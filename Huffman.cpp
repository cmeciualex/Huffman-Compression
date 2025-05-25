//
// Created by acmec on 4/23/2025.
//

#include "Huffman.h"
#include "PriorityQueue.h"

bool Huffman::rel(Node* a, Node* b) {
    return a->frequency > b->frequency;
}

Node* Huffman::buildTree(const uint64_t histogram[ALPHABET]) {
    PriorityQueue pq(rel);
    for (int i=0;i<256;i++) {
        if (histogram[i]!=0) {
            Node *node = new Node((char)i, histogram[i]);
            pq.push(node);
        }
    }
    while (pq.get_size()!=1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = Node::combine(left, right);
        pq.push(parent);
    }
    if (pq.get_size()==1)
        return pq.top();
    else
        return nullptr;
}
