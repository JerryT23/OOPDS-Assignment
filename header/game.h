#ifndef GAME_H
#define GAME_H
#include "grid.h"
#include "team.h"
#include "vector.h"

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
    void printGrid() const;
    void init();
    void terminate();
    void shipRandomGenerate();
    void start();
};
#endif