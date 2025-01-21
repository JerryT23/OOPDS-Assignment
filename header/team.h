#ifndef TEAM_H
#define TEAM_H
#include <string>
#include "./linkedlist.h"

class Team
{
    LinkedList ships;
    public:
    Node* getLinkedListHead() const;
    Node* getLinkedListTail() const; //maybe not needed
    LinkedList& getShip();
    void pushbackShips(Ship* ship);
    Ship* searchShip(int index);
    void replaceShip(int index,Ship* newShip);
};
#endif