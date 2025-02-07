/**********|**********|**********|
Program: queue.cpp
Course: Object Oriented Programming And Data Structure
Trimester: 2430
Name: Chang Hoe Hin, Tee Kah Le, Loke Mun Chun, Ng Zai Kit
ID: 241UC2415N, 241UC2414Z, 241UC24160, 241UC240JT
Lecture Section: TC1L
Tutorial Section: TT4L
Email: chang.hoe.hin@student.mmu.edu.my, tee.kah.le@student.mmu.edu.my, loke.mun.chun@student.mmu.edu.my, ng.zai.kit@student.mmu.edu.my
Phone: 017-2453131, 011-2704 7627, 018-667 1883, 014-600 3652
**********|**********|**********/
#include "../header/queue.h"
#include "../header/shiptype.h"
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
Node *queue::getFront()
{
    return front;
}

queue::~queue()
{
    Node *n = front;
    Node *deleteptr = front;
    while (deleteptr)
    {
        n = deleteptr->next;
        delete deleteptr;
        deleteptr = n;
    }
}