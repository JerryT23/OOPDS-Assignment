#include "../header/shiptype.h"
void Ship::setType(std::string s)
{
    type = s;
}
std::string Ship::getType() const
{
    return type;
}


std::string Team::getTeamName() const
{
    return Team::teamName;
};
void Team::setTeamName(std::string s)
{
    Team::teamName = s;
};
void Team::setSymbol(std::string type, char symbolP)
{
    symbol[type] = symbolP;
}
char Team::getSymbol(std::string type)
{
    return symbol[type];
}

void Team::setShips(int size)
{
    typeAmount = size;
    ships = new Ship *[size];
}
void Team::setShipsCol(int index, Ship *obj)
{
    ships[index] = obj;
}
Ship* Team::getShip(int index) {
    return ships[index];
}