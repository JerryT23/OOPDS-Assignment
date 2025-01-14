#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "./shiptype.h"
class LinkedList {
    struct Node{
        Ship* value;
        Node* next;
    };
    Node* head;
    Node* tail;
    int size;
    public:
    void pushFirst(Ship* value);
    LinkedList(): head(nullptr),tail(nullptr),size(0) {

    }
    void pushback(Ship* value);
    ~LinkedList(); 
};
#endif