#pragma once
#include <vector>
#include <cstdint>

class Node;

typedef Node* TElem;
typedef uint64_t TPriority;

typedef bool (*Relation)(TElem p1, TElem p2);

class PriorityQueue {
private:
    Relation relation;
    int size = 0;
    TElem* elements;

public:

    int get_size();

    PriorityQueue(Relation r);

    void push(TElem e);

    TElem top() const;

    TElem pop();

    bool isEmpty() const;

    ~PriorityQueue();
};
