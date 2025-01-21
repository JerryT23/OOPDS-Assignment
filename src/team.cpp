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
int* Team::getShipPosition(int index) const
{
    return shipPositions[index];
}
 Node* Team::getLinkedListHead() const {
    return ships.getHead();
}
  Node* Team::getLinkedListTail() const {
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
void Team::replaceShip(int index,Ship* newShip) {
    ships.replace(index,newShip);
}
LinkedList& Team::getShip(){
    return ships;
}