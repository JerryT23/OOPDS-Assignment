/**********|**********|**********|
Program: grid.h
Course: Object Oriented Programming And Data Structure
Trimester: 2430
Name: Chang Hoe Hin, Tee Kah Le, Loke Mun Chun, Ng Zai Kit
ID: 241UC2415N, 241UC2414Z, 241UC24160, 241UC240JT
Lecture Section: TC1L
Tutorial Section: TT4L
Email: chang.hoe.hin@student.mmu.edu.my, tee.kah.le@student.mmu.edu.my, loke.mun.chun@student.mmu.edu.my, ng.zai.kit@student.mmu.edu.my
Phone: 017-2453131, 011-2704 7627, 018-667 1883, 014-600 3652
**********|**********|**********/
#ifndef GRID_H
#define GRID_H
#include <string>

class Ship;
class Grid
{
    bool taken;
    std::string val;      // string bcs store *1 if ship is at the location
    std::string landtype; // 0/1
    Ship *ship;
    static int height;
    static int width;

public:
    Grid();
    void setTaken(bool b);
    bool getTaken() const;
    void setVal(std::string value);
    std::string getVal() const;
    std::string getType() const;
    void setship(Ship *ship);
    Ship *getship() const;
    static void setHeight(int x);
    static int getHeight();
    static void setwidth(int x);
    static int getwidth();
};
#endif