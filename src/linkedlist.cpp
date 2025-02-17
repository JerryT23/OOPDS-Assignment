/**********|**********|**********|
Program: linkedlist.cpp
Course: Object Oriented Programming And Data Structure
Trimester: 2430
Name: Chang Hoe Hin, Tee Kah Le, Loke Mun Chun, Ng Zai Kit
ID: 241UC2415N, 241UC2414Z, 241UC24160, 241UC240JT
Lecture Section: TC1L
Tutorial Section: TT4L
Email: chang.hoe.hin@student.mmu.edu.my, tee.kah.le@student.mmu.edu.my, loke.mun.chun@student.mmu.edu.my, ng.zai.kit@student.mmu.edu.my
Phone: 017-2453131, 011-2704 7627, 018-667 1883, 014-600 3652
**********|**********|**********/
#include "../header/linkedlist.h"

void LinkedList::pushFirst(Ship *value)
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    head = newNode;
    tail = newNode;
    size = 1;
}

void LinkedList::pushback(Ship *value)
{
    if (!head)
    {
        pushFirst(value);
    }
    else
    {
        Node *newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
        size++;
    }
}
bool LinkedList::empty()
{
    return head == nullptr;
}

void LinkedList::deleteNode(int index)
{
    if (index >= size)
    {
        std::cout << "invalid access\n " << __LINE__ << " lines";
        throw runtime_error("LinkedList Invalid Access");
    }
    if (index == 0)
    {
        if (head == tail)
            tail = nullptr;
        Node *ptr = head;
        head = head->next;
        delete ptr->value;
        delete ptr;
    }
    else
    {
        Node *indexNode = head;
        Node *prev;
        for (int i = 0; i < index; i++)
        {
            prev = indexNode;
            indexNode = indexNode->next;
        }
        if (index == (size - 1))
        {
            tail = prev;
            prev->next = nullptr;
        }
        else
            prev->next = indexNode->next;
        delete indexNode->value;
        delete indexNode;
    }
    size--;
}
void LinkedList::deleteNode(Ship *ship)
{
    int index = 0;
    Node *shipptr = head;
    while (shipptr->value != ship)
    {
        shipptr = shipptr->next;
        index++;
        if (index == size)
            throw runtime_error("Ship not found in the linkedlist, therefore cant be deleted.");
    }
    if (index == 0)
    {
        if (head == tail)
            tail = nullptr;
        Node *ptr = head;
        head = head->next;
        delete ptr->value;
        delete ptr;
    }
    else
    {
        Node *indexNode = head;
        Node *prev;
        for (int i = 0; i < index; i++)
        {
            prev = indexNode;
            indexNode = indexNode->next;
        }
        if (index == (size - 1))
        {
            tail = prev;
            prev->next = nullptr;
        }
        else
            prev->next = indexNode->next;
        delete indexNode->value;
        delete indexNode;
    }
    size--;
}
Ship *LinkedList::search(int index)
{
    if (index >= size)
    {
        std::cout << "violation access\n " << __LINE__ << " lines";
        throw runtime_error("LinkedList Invalid Access");
    }
    Node *ret = head;
    for (int i = 0; i < index; i++)
    {
        ret = ret->next;
    }
    return ret->value;
}
Node *LinkedList::replace(Ship *oriShip, Ship *value)
{
    // find oriship index
    int index = 0;
    Node *shipptr = head;
    while (shipptr->value != oriShip)
    {
        shipptr = shipptr->next;
        index++;
        if (index == size)
            throw runtime_error("Ship not found in the linkedlist, therefore cant be deleted.");
    }
    //////////////////
    Node *newship = new Node;
    if (index >= size)
    {
        std::cout << "invalid access\n " << __LINE__ << " lines";
        throw runtime_error("LinkedList Invalid Access");
    }
    if (index == 0)
    {
        newship->value = value;
        newship->next = head->next;
        delete head->value;
        delete head;
        head = newship;
        if (size == 1)
        { // if there's only one node, update tail
            tail = newship;
        }
    }
    else
    {
        Node *indexNode = head;
        Node *prev;
        for (int i = 0; i < index; i++)
        {
            prev = indexNode;
            indexNode = indexNode->next;
        }
        newship->value = value;
        newship->next = indexNode->next;
        prev->next = newship;
        if (index == (size - 1))
        {
            tail = newship;
        }
        delete indexNode->value;
        delete indexNode;
    }
    return newship;
}
Node *LinkedList::getHead() const { return head; }
Node *LinkedList::getTail() const { return tail; }
int LinkedList::getSize() const { return size; }
LinkedList::~LinkedList()
{
    Node *n = head;
    Node *deleteptr = head;
    for (int i = 0; i < size; i++)
    {
        n = deleteptr->next;
        delete deleteptr->value;
        delete deleteptr;
        deleteptr = n;
    }
}