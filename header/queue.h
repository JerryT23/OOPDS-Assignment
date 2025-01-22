#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
class Ship;
class queue
{
    Node* front;
    Node* rear;
public:
    queue() : front(nullptr), rear(nullptr) {}
    bool empty();
    void enqueue(Ship* value);
    void dequeue();
    Node* getFront();
    ~queue();
};
#endif