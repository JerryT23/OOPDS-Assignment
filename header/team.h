#ifndef TEAM_H
#define TEAM_H
#include <string>
#include "./linkedlist.h"

class Team
{
    std::string teamName;
    int (*shipPositions)[2];
    int shipAmount; //in a team
    LinkedList ships;
    public:
    void setShipPosition(int index, int x, int y);
    int* getShipPosition(int index) const;
    void pushbackShips(Ship* ship);
    LinkedList getShips() {
        return ships;
    }
    Ship* searchShip(int index);
    int getShipAmount() const;
    ~Team() {
        delete[] shipPositions;
    }
};
#endif