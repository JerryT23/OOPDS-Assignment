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
void Team::replaceShip(int index, Ship *newShip)
{
    ships.replace(index, newShip);
}
LinkedList &Team::getShip()
{
    return ships;
}