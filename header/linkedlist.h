/**********|**********|**********|
Program: linkedlist.h
Course: Object Oriented Programming And Data Structure
Trimester: 2430
Name: Chang Hoe Hin, Tee Kah Le, Loke Mun Chun, Ng Zai Kit
ID: 241UC2415N, 241UC2414Z, 241UC24160, 241UC240JT
Lecture Section: TC1L
Tutorial Section: TT4L
Email: chang.hoe.hin@student.mmu.edu.my, tee.kah.le@student.mmu.edu.my, loke.mun.chun@student.mmu.edu.my, ng.zai.kit@student.mmu.edu.my
Phone: 017-2453131, 011-2704 7627, 018-667 1883, 014-600 3652
**********|**********|**********/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "./shiptype.h"
#include "node.h"
#include <iostream>
class LinkedList
{
    Node *head;
    Node *tail;
    int size;

public:
    void pushFirst(Ship *value);
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    void pushback(Ship *value);
    bool empty();
    void deleteNode(int index);
    void deleteNode(Ship *ship);
    Ship *search(int index);
    Node *replace(Ship *oriShip, Ship *value);
    Node *getHead() const;
    Node *getTail() const;
    int getSize() const;
    ~LinkedList();
};
#endif