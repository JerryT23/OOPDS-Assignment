#ifndef GAME_H
#define GAME_H
#include "shiptype.h"
#include "team.h"
#include "vector.h"
class Grid {
    bool taken;
    std::string val; //string bcs store *1 if ship is at the location
    std::string type; // 0/1
    public:
    void setTaken(bool b);
    bool getTaken() const;
    void setVal(std::string value);
    std::string getVal() const;
    std::string getType() const;
};

class Game {
    private:
        Team* teams;
        Vector<int> teamShipTotal; //team A have 16 ship team B have 5 ship then => {16,5}
        int width;
        int height;
        int iterations;
        Grid** grid;
    public:
    Game();
    void init();
    void terminate();
    void shipRandomGenerate();
    void start();
};
#endif