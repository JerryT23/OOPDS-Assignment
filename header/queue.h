#ifndef QUEUE_H
#define QUEUE_H
#include "./shiptype.h"
class queue
{
    struct Node
    {
        Ship* value;
        Node* next;
    };
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