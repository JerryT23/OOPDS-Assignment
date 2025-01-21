#include "../header/grid.h"
int Grid::height = 0;
int Grid::width = 0;
Grid::Grid():ship(nullptr){}
void Grid::setTaken(bool b)
{
    taken = b;
}
bool Grid::getTaken() const
{
    return taken;
}
void Grid::setVal(std::string value)
{
    if(value == "0" || value == "1")
        landtype = value;
    val = value;
}
std::string Grid::getVal() const
{
    return val;
}
std::string Grid::getType() const
{
    return landtype;
}
void Grid::setship(Ship* ship) {
    this->ship = ship;
}
Ship* Grid::getship() const {
    return this->ship;
}
void Grid::setHeight(int x) {height = x;}
int Grid::getHeight(){return height;}
void Grid::setwidth(int x) {width = x;}
int Grid::getwidth(){return width;}