#ifndef QUEUE_H
#define QUEUE_H
#include "./shiptype.h"
#include "node.h"
class queue
{
    Node* front;
    Node* rear;
public:
    queue() : front(nullptr), rear(nullptr) {}
    bool empty();
    void enqueue(Ship* value);
    void dequeue();
    ~queue();
};
#endif