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
bool LinkedList::empty() {
    return head == nullptr;
}

void LinkedList::deleteNode(int index) {
    if(index >= size) {
            std::cout << "invalid access\n " << __LINE__ << " lines";
            exit(-1);
        }
        if(index==0) {
            if(head == tail) tail=nullptr;
            Node* ptr = head;
            head = head->next;
            delete ptr;
        } else {
            Node* indexNode = head;
            Node* prev;
            for(int i = 0; i < index; i++) {
                prev = indexNode;
                indexNode = indexNode->next;
            }
            if(index == (size-1)) {
                tail = prev;
                prev->next = nullptr;
            } else
                prev->next = indexNode->next;
            delete indexNode;
        }
        size--;
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
Node* LinkedList::getHead() const{ return head;};
LinkedList::~LinkedList() {
    Node* n = head;
    Node* deleteptr = head;
    for(int i = 0; i < size; i++) {
        n = deleteptr->next;
        delete deleteptr;
        deleteptr = n;
    }
}