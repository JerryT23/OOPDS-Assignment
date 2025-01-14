#include "../header/linkedlist.h"

void LinkedList::pushFirst(Ship* value)  {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    head = newNode;
    tail = newNode;
    size = 1;
}

void LinkedList::pushback(Ship* value){
    if(!head) {
        pushFirst(value);
    } else {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
        size++;
    }
}