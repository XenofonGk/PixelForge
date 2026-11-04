#ifndef FORGE_STACK_H
#define FORGE_STACK_H
// Day 16: a linked-list stack, written as a class template.
// Notes: H-Deeper-Detail/linked-list-technology, C-Class-Relationships/class-templates
#include "Common.h"
#include <stdexcept>

template <typename T>
class Stack {
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n) : data(d), next(n) { ++liveNodes(); }
        ~Node() { --liveNodes(); }
    };
    Node* head{nullptr};
    int count{0};
public:
    static int& liveNodes() { static int n = 0; return n; }  // used by the leak test

    Stack() = default;
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    ~Stack() {
        // TODO Day 16: walk the list and delete every node.
    }
    void push(const T& value) {
        // TODO Day 16: add a new node at the head.
        NOT_IMPLEMENTED();
    }
    T pop() {
        // TODO Day 16: throw std::out_of_range if empty. Otherwise copy the value, unlink the head, delete it, and return the copy.
        NOT_IMPLEMENTED();
    }
    const T& top() const {
        // TODO Day 16: throw std::out_of_range if empty. Otherwise return the head's data.
        NOT_IMPLEMENTED();
    }
    void clear() {
        // TODO Day 16: remove every element.
        NOT_IMPLEMENTED();
    }
    bool empty() const { return head == nullptr; }
    int size() const { return count; }
};

#endif
