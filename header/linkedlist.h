#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "./shiptype.h"
#include "node.h"
#include <iostream>
class LinkedList {
    Node* head;
    Node* tail;
    int size;
    public:
    void pushFirst(Ship* value);
    LinkedList(): head(nullptr),tail(nullptr),size(0) {}
    void pushback(Ship* value);
    bool empty();
    void deleteNode(int index);
    Ship* search(int index);
    Node* getHead() const;
    Node* getTail() const;
    void print() {
        Node* ptr = head;
        while(ptr!=nullptr) {
            std::cout << ptr->value->getType() << ' ';
            ptr = ptr->next;
        }
    }
    ~LinkedList(); 
};
#endif