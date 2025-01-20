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
void LinkedList::replace(int index,Ship* value) {
    if(index >= size) {
            std::cout << "invalid access\n " << __LINE__ << " lines";
            exit(-1);
        }
        if(index==0) {
            Node* newship = new Node;
            newship->value = value; 
            newship->next = head->next;
            delete head;
            head = newship;
            if (size == 1) { //if there's only one node, update tail
            tail = newship; 
        }
        } else {
            Node* indexNode = head;
            Node* prev;
            Node* newship = new Node;
            for(int i = 0; i < index; i++) {
                prev = indexNode;
                indexNode = indexNode->next;
            }
            newship->value = value;
            newship->next = indexNode->next;
            prev->next = newship;
            if(index == (size-1)) {
                tail = newship;
            }
            delete indexNode;
            }
}
Node* LinkedList::getHead() const{ return head;}
Node* LinkedList::getTail() const {return tail;}
void LinkedList::print() {
        Node* ptr = head;
        while(ptr!=nullptr) {
            std::cout << ptr->value->getType() << ' ';
            ptr = ptr->next;
        }
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