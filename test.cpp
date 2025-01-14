// this file is for testing certain function only:)))
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
    public:
    void pushFirst(int value);
    LinkedList(): head(nullptr),tail(nullptr),size(0) {

    }
    void pushback(int value);
    ~LinkedList(); 
};
void LinkedList::pushFirst(int value)  {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    head = newNode;
    tail = newNode;
    size = 1;
}

void LinkedList::pushback(int value){
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

LinkedList::~LinkedList();
int main()
{
    LinkedList* list = new LinkedList;
    list->pushback(3);
    list->pushback(5);
    list->pushback(8);
    delete list;
    return 0;
}