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
void Team::setShips(int size) {
    ships = new Ship*[size];
}

Team::~Team() {
    for(int i = 0; i < shipAmount; i++) {
        delete[] ships[i];
    }
    delete[] ships;
}