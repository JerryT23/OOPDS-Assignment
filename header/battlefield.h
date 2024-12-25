#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include "shiptype.h"
class Game {
    private:
        Team* teams;
        int width;
        int height;
        int iterations;
        Team* teamsSizeInc(Team* teams, int& currentSize); //to do
    public:
    void init();
    void terminate();
};
#endif