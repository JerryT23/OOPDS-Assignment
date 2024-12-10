#include "../header/shiptype.h"

void Ship::setShipPositionX(int x) {
    shipPositionX = x;
}
void Ship::setShipPositionY(int y) {
    shipPositionY = y;
}
int Ship::getShipPositionX() const {
    return shipPositionX;
}
int Ship::getShipPositionY() const {
    return shipPositionY;
}

char Battleship::symbol = '\0';
char Cruiser::symbol = '\0';
char Destroyer::symbol = '\0';
char Frigate::symbol = '\0';
char Corvette::symbol = '\0';
char Amphibious::symbol = '\0';
char Supership::symbol = '\0';

int Battleship::amount = -1;
int Cruiser::amount = -1;
int Destroyer::amount = -1;
int Frigate::amount = -1;
int Corvette::amount = -1;
int Amphibious::amount = -1;
int Supership::amount = -1;

void Battleship::setSymbol(char c) {symbol= c;}
void Battleship::setAmount(int x) {amount= x;}
int Battleship::getSymbol() const {return symbol;}
int Battleship::getAmount() const {return amount;}

void Cruiser::setSymbol(char c) {symbol = c;}
void Cruiser::setAmount(int x) {amount = x;}
int Cruiser::getSymbol() const {return symbol;}
int Cruiser::getAmount() const {return amount;}

void Destroyer::setSymbol(char c) {symbol = c;}
void Destroyer::setAmount(int x) {amount = x;}
int Destroyer::getSymbol() const {return symbol;}
int Destroyer::getAmount() const {return amount;}
void Frigate::setSymbol(char c) {symbol = c;}
void Frigate::setAmount(int x) {amount = x;}
int Frigate::getSymbol() const {return symbol;}
int Frigate::getAmount() const {return amount;}
void Corvette::setSymbol(char c) {symbol = c;}
void Corvette::setAmount(int x) {amount = x;}
int Corvette::getSymbol() const {return symbol;}
int Corvette::getAmount() const {return amount;}
void Amphibious::setSymbol(char c) {symbol = c;}
void Amphibious::setAmount(int x) {amount = x;}
int Amphibious::getSymbol() const {return symbol;}
int Amphibious::getAmount() const {return amount;}
void Supership::setSymbol(char c) {symbol = c;}
void Supership::setAmount(int x) {amount = x;}
int Supership::getSymbol() const {return symbol;}
int Supership::getAmount() const {return amount;}