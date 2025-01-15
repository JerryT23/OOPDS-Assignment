#ifndef GRID_H
#define GRID_H
#include<string>
#include"shiptype.h"
class Grid {
    bool taken;
    std::string val; //string bcs store *1 if ship is at the location
    std::string landtype; // 0/1
    Ship* ship;
    public:
    Grid();
    void setTaken(bool b);
    bool getTaken() const;
    void setVal(std::string value);
    std::string getVal() const;
    std::string getType() const;
    void setship(Ship* ship);
    Ship* getship() const;
};
#endif