/**********|**********|**********|
Program: grid.cpp
Course: Object Oriented Programming And Data Structure
Trimester: 2430
Name: Chang Hoe Hin, Tee Kah Le, Loke Mun Chun, Ng Zai Kit
ID: 241UC2415N, 241UC2414Z, 241UC24160, 241UC240JT
Lecture Section: TC1L
Tutorial Section: TT4L
Email: chang.hoe.hin@student.mmu.edu.my, tee.kah.le@student.mmu.edu.my, loke.mun.chun@student.mmu.edu.my, ng.zai.kit@student.mmu.edu.my
Phone: 017-2453131, 011-2704 7627, 018-667 1883, 014-600 3652
**********|**********|**********/
#include "../header/grid.h"
int Grid::height = 0;
int Grid::width = 0;
Grid::Grid() : ship(nullptr) {}
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
    if (value == "0" || value == "1")
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
void Grid::setship(Ship *ship)
{
    this->ship = ship;
}
Ship *Grid::getship() const
{
    return this->ship;
}
void Grid::setHeight(int x) { height = x; }
int Grid::getHeight() { return height; }
void Grid::setwidth(int x) { width = x; }
int Grid::getwidth() { return width; }