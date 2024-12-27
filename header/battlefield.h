#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include "shiptype.h"
class Game {
    private:
        Team* teams;
        int width;
        int height;
        int iterations;
        int** grid;
        Team* teamsSizeInc(Team* teams, int& currentSize); //to do
    public:
    Game();
    void init();
    void terminate();
};
#endif