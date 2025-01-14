#include "../header/team.h"
#include "../header/shiptype.h"
void Team::initShipPositions(int size) {
    shipPositions = new int[size][2];
}
void Team::setShipPosition(int index, int x, int y)
{
    shipPositions[index][0] = x;
    shipPositions[index][1] = y;
}
int *Team::getShipPosition(int index) const
{
    return shipPositions[index];
}
void Team::pushbackShips(Ship *ship)
{
    ships.pushback(ship);
}
Ship *Team::searchShip(int index)
{
    return ships.search(index);
}