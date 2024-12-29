#ifndef GAME_H
#define GAME_H
#include "shiptype.h"
class Game {
    private:
        Team* teams;
        Vector<int> teamShipTotal; //team A have 16 ship team B have 5 ship then => {16,5}
        int width;
        int height;
        int iterations;
        int** grid;
        Team* teamsSizeInc(Team* teams, int& currentSize); //to do
    public:
    Game();
    void init();
    void terminate();
    void shipRandomGenerate();
};
#endif