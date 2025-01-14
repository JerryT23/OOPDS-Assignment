#include "../header/queue.h"

bool queue::empty()
{
    return front == nullptr;
}

void queue::enqueue(Ship *value)
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    if (empty())
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

void queue::dequeue()
{
    Node *frontNode = front;
    front = front->next;
    delete frontNode;
    if (front == nullptr)
    {
        rear = nullptr;
    }
}