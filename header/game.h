/**********|**********|**********|
Program: game.h
Course: Object Oriented Programming And Data Structure
Trimester: 2430
Name: Chang Hoe Hin, Tee Kah Le, Loke Mun Chun, Ng Zai Kit
ID: 241UC2415N, 241UC2414Z, 241UC24160, 241UC240JT
Lecture Section: TC1L
Tutorial Section: TT4L
Email: chang.hoe.hin@student.mmu.edu.my, tee.kah.le@student.mmu.edu.my, loke.mun.chun@student.mmu.edu.my, ng.zai.kit@student.mmu.edu.my
Phone: 017-2453131, 011-2704 7627, 018-667 1883, 014-600 3652
**********|**********|**********/
#ifndef GAME_H
#define GAME_H
#include "grid.h"
#include "team.h"
#include "vector.h"
#include "queue.h"

class Ship;
class Game
{
private:
    bool gameRunning;
    Team *teams;
    Vector<int> teamShipTotal; // team A have 16 ship team B have 5 ship then => {16,5}
    int width;
    int height;
    int iterations;
    Grid **grid;
    queue reenterShips;

public:
    Game();
    void printGrid() const;
    Node *upgradeShip(Ship *oriShip);
    void init();
    void terminate();
    void reenterBattlefield();
    void shipRandomGenerate();
    void start();
};
#endif