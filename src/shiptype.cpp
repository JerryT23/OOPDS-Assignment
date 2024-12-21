#include "../header/shiptype.h"

Ship::Ship() : life(3) {}
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
void Team::setShips() {
    Team::ships;
};