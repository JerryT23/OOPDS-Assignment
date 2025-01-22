#include "../header/team.h"
#include "../header/shiptype.h"
Node *Team::getLinkedListHead() const
{
    return ships.getHead();
}
Node *Team::getLinkedListTail() const
{
    return ships.getTail();
}
void Team::pushbackShips(Ship *ship)
{
    ships.pushback(ship);
}
Ship *Team::searchShip(int index)
{
    return ships.search(index);
}
void Team::replaceShip(Ship* oriShip, Ship *newShip)
{
    ships.replace(oriShip, newShip);
}
LinkedList &Team::getShip()
{
    return ships;
}