#ifndef GAME_H
#define GAME_H
#include "shiptype.h"
class Grid {
    bool taken;
    int val;
    public:
    void setTaken(bool b);
    bool getTaken() const;
    void setVal(int value);
    int getVal() const;
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
};
#endif