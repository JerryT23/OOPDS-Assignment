#include "../header/shiptype.h"
void Ship::setType(std::string s)
{
    type = s;
}
std::string Ship::getType() const
{
    return type;
}
void Ship::setDisplay(std::string s) {
    display = s;
}
std::string Ship::getDisplay() const {
 return display;
}

std::string Team::getTeamName() const
{
    return Team::teamName;
};
void Team::setTeamName(std::string s)
{
    Team::teamName = s;
};

void Team::setShipPosition(int index, int x, int y) {
    shipPositions[index][0] = x;
    shipPositions[index][1] = y;
}
int* Team::getShipPosition(int index) const {
    return shipPositions[index];
}

void Team::setShips(int size)
{
    shipAmount = size;
    ships = new Ship *[size];

    //init ship position after getting shipAmount
    shipPositions = new int[shipAmount][2];
}
void Team::setShipsCol(int index, Ship *obj)
{
    ships[index] = obj;
}
int Team::getShipAmount() const {return shipAmount;}
Ship* Team::getShip(int index) {
    return ships[index];
}