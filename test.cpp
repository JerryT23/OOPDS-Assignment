// this file is for testing certain function only:)))
#include <iostream>

using namespace std;

class queue
{
    struct Node
    {
        int value;
        Node *next;
    };
    Node *front;
    Node *rear;
public:
    queue() : front(nullptr), rear(nullptr) {}
    bool empty() {
        return front == nullptr;
    }
    void enqueue(int value) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        if(empty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    void dequeue() {
        Node* frontNode = front;
        front = front->next;
        delete frontNode;
        if(front == nullptr) {
            rear = nullptr;
        }
    }
    void display() {
        Node* n = front;
        while(n!=nullptr) {
            cout << n->value << ' ';
            n = n->next;
        }
    }
};

int main()
{
    queue list;
    list.enqueue(3);
    list.enqueue(5);
    list.enqueue(8);
    list.display();
    list.dequeue();
    list.display();
    return 0;
}