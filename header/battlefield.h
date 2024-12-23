#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include "shiptype.h"
class Game {
    private:
        Team* teams;
        int width;
        int height;
        int iterations;
    public:
    void init();
    void terminate();
};
#endif