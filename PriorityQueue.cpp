#include "PriorityQueue.h"
#include <stdexcept>
using namespace std;

PriorityQueue::PriorityQueue(Relation r) {
    this->elements = new TElem[1];
    this->size = 0;
    this->relation = r;
}

int PriorityQueue::get_size() {
    return this->size;
}

void PriorityQueue::push(TElem e) {
    TElem* newElements = new TElem[this->size + 1];
    int index = 0;

    while (index < this->size && !relation(elements[index], e)) {
        newElements[index] = elements[index];
        index++;
    }
    newElements[index] = e;
    for (int i = index; i < this->size; i++) {
        newElements[i + 1] = elements[i];
    }

    delete[] elements;
    elements = newElements;
    size++;
}

TElem PriorityQueue::top() const {
    if (size == 0)
        throw exception();
    return elements[0];
}

TElem PriorityQueue::pop() {
    if (size == 0) {
        throw exception();
    }
    TElem topElem = elements[0];
    for (int i = 0; i < size - 1; i++) {
        elements[i] = elements[i + 1];
    }
    size--;
    return topElem;
}

bool PriorityQueue::isEmpty() const {
    return size == 0;
}

PriorityQueue::~PriorityQueue() {
    delete[] elements;
}
