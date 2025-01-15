#ifndef TEAM_H
#define TEAM_H
#include <string>
#include "./linkedlist.h"

class Team
{
    std::string teamName;
    int (*shipPositions)[2];
    LinkedList ships;
    public:
    void initShipPositions(int size);
    void setShipPosition(int index, int x, int y);
    int* getShipPosition(int index) const;
    Node* getLinkedListHead() const;
     Node* getLinkedListTail() const;
    void pushbackShips(Ship* ship);
    LinkedList getShips() {
        return ships;
    }
    Ship* searchShip(int index);
    ~Team() {
        delete[] shipPositions;
    }
};
#endif