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
Ship* LinkedList::search(int index){
        if(index >= size) {
            std::cout << "violation access\n " << __LINE__ << " lines";
            exit(-1);
        }
        Node* ret = head;
        for(int i = 0; i < index; i++) {
            ret = ret->next;
        }
        return ret->value;
    }
LinkedList::~LinkedList() {
    Node* n = head;
    Node* deleteptr = head;
    for(int i = 0; i < size; i++) {
        n = deleteptr->next;
        delete deleteptr;
        deleteptr = n;
    }
}