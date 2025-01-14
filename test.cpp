//this file is for testing certain function only:)))
#include <iostream>

using namespace std;
class LinkedList {
    struct Node{
        int value;
        Node* next;
    };
    Node* head;
    Node* tail;
    int size;
    void pushFirst(int value) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        head = newNode;
        tail = newNode;
        size = 1;
    }
    public:
    LinkedList(): head(nullptr),tail(nullptr),size(0) {

    }
    void pushback(int value) {
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
    void print() {
        for(int i = 0; i < size;i++) {
            Node* ptr = head;
            cout << ptr->value << ' ';
            ptr = ptr->next;
        }
    }
};

int main() {
    LinkedList list;
    return 0;
}