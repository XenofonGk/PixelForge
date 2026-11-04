#ifndef FORGE_QUEUE_H
#define FORGE_QUEUE_H
// Day 19: a linked-list queue, and the standard sequential containers.
// Notes: H-Deeper-Detail/linked-list-technology, E-STL/containers-and-iterations
#include "Common.h"
#include "Pixel.h"
#include <deque>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class Queue {
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head{nullptr};
    Node* tail{nullptr};
    int count{0};
public:
    Queue() = default;
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    ~Queue() {
        // TODO Day 19: delete every node.
    }
    void push(const T& value) {
        // TODO Day 19: add at the tail. Remember the empty-queue case.
        NOT_IMPLEMENTED();
    }
    T pop() {
        // TODO Day 19: remove from the head. Throw std::out_of_range if empty. Reset tail when the queue becomes empty.
        NOT_IMPLEMENTED();
    }
    bool empty() const { return head == nullptr; }
    int size() const { return count; }
};

// The last few commands, newest first.
class Recent {
    std::deque<std::string> items;
    std::size_t capacity;
public:
    explicit Recent(std::size_t cap) : capacity(cap) {}
    void add(const std::string& command);    // push_front; pop_back when over capacity
    const std::string& at(std::size_t i) const { return items.at(i); }
    std::size_t size() const { return items.size(); }
};

void removeDark(std::list<Pixel>& pixels, int level);  // erase with iterators
std::vector<int> reversedWithStack(const std::vector<int>& values); // use std::stack

#endif
