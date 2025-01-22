#ifndef GAME_H
#define GAME_H
#include "grid.h"
#include "team.h"
#include "vector.h"
#include "queue.h"

class Game {
    private:
        bool gameRunning;
        Team* teams;
        Vector<int> teamShipTotal; //team A have 16 ship team B have 5 ship then => {16,5}
        int width;
        int height;
        int iterations;
        Grid** grid;
        queue reenterShips;
    public:
    Game();
    void printGrid() const;
    // void reenterBattlefield();
    void init();
    void terminate();
    void reenterBattlefield();
    void shipRandomGenerate();
    void start();
};
#endif