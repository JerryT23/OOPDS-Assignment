#ifndef TEAM_H
#define TEAM_H
#include <string>
#include "./linkedlist.h"

class Team
{
    int (*shipPositions)[2];
    LinkedList ships;
    public:
    void initShipPositions(int size);
    void setShipPosition(int index, int x, int y);
    int* getShipPosition(int index) const;
    Node* getLinkedListHead() const;
     Node* getLinkedListTail() const; //maybe not needed
    void pushbackShips(Ship* ship);
    Ship* searchShip(int index);
    void replaceShip(int index,Ship* newShip);
    ~Team() {
        delete[] shipPositions;
    }
};
#endif