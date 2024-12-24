#include "../header/shiptype.h"

void Ship::setSymbol(char c) {
    symbol = c;
};
char Ship::getSymbol() const {return symbol;}

std::string Team::getTeamName() const {
    return Team::teamName;
};
void Team::setTeamName(std::string s) {
    Team::teamName = s;
};
void Team::setShips(int size) {
    shipAmount = size;
    ships = new Ship*[size];
}

void Team::setShipsCol(int index,Ship* obj){
    ships[index] = obj;
}