#ifndef SHIPTYPE_H
#define SHIPTYPE_H
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "./grid.h"
#include "./vector.h"
#include "./externalOutput.h"

class queue;
class Ship
{
    std::string type;
    std::string display;
    std::string teamName;
    int life;
    int totalKilled;
    int shipPositionIndex;
    int teamPositionIndex;
public:
    Ship() : life(3),totalKilled(0){}
    virtual void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height,queue& reenterQueue) = 0;
    void setType(std::string s);
    std::string getType() const;
    void setDisplay(std::string s);
    std::string getDisplay() const;
    void setTeamName(std::string teamname);
    std::string getTeamName() const;
    void lifeMinus1();
    int getLife() const;
    void totalKillIncrement();
    int getTotalKill() const;
    void setShipPositionIndex(int index);
    int getShipPositionIndex() const;
    void setTeamPositionIndex(int index);
    int getTeamPositionIndex() const;
    bool oneOfFourNeighbour(int gridX,int gridY,int shipPositionX,int shipPositionY);
    virtual ~Ship() {}
};

// no overlapping method and attribute for subclasses

class SeeingShip : virtual public Ship
{
public:
    virtual void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height) = 0;
    virtual ~SeeingShip() {}
};

class MovingShip : virtual public Ship
{
public:
    virtual void move(Grid** grid, int& shipPositionX, int& shipPositionY) = 0;
    virtual ~MovingShip() {}
};

class ShootingShip : virtual public Ship
{
public:
    virtual void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,queue& reenterQueue) = 0;
    virtual ~ShootingShip() {}
};

class RamShip : virtual public Ship
{
public:
    virtual void ram() = 0;
    virtual ~RamShip() {}
};


class Battleship : public MovingShip, public SeeingShip, public ShootingShip
{
    Vector<int> xNy; //store x and y for push into available move
    Vector<Vector<int>> availableMove;
    int infiniteLoopDetector = 0;
    int shootX,shootY;
    public:
        bool friendlyShip(Grid** grid, int shipAdditionX,int shipAdditionY,int shipPositionX, int shipPositionY);
        void move(Grid** grid, int& shipPositionX, int& shipPositionY);
        void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height);
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,queue& reenterQueue);
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height,queue& reenterQueue) {
            srand(time(0));
            std::cout << this->getDisplay() << " Ship look(0,0):" <<std::endl << "Ship type:"<<this->getType()<<std::endl;
            OutputFile << this->getDisplay() << " Ship look(0,0):" <<std::endl << "Ship type:"<<this->getType()<<std::endl;
            look(0,0,grid,shipPositionX,shipPositionY,width,height);
            move(grid,shipPositionX,shipPositionY);
            availableMove.clear();
            //generate shoot coordinate
            do {
                if(infiniteLoopDetector > 10000) { //if loop 10000 times still cant find a place to shoot
                    std::cout << "No Place to shoot";
                    OutputFile << "No Place to shoot";
                    break;
                }
                shootX = rand() % 6;
                shootY = rand() % 6;
                infiniteLoopDetector++;
            } while((shootX + shootY > 5) || (shootX == 0 && shootY == 0) || shipPositionX+shootX >= width ||
            shipPositionY+shootY>=height|| friendlyShip(grid,shootX,shootY,shipPositionX,shipPositionY));//
            //-------------------------------
            if(infiniteLoopDetector <= 10000) shoot(shootX,shootY,grid,shipPositionX,shipPositionY,reenterQueue);
        }
};

class Cruiser : public SeeingShip, public MovingShip, public RamShip
{
    public:
        void move(Grid** grid, int& shipPositionX, int& shipPositionY) {

        }
        void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height) {

        }
        void ram() {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height,queue& reenterQueue) {
            std::cout << "I'm Cruiser brather" << std::endl;
        }
};
class Destroyer : public MovingShip, public SeeingShip, public ShootingShip, public RamShip
{
    public:
        void move(Grid** grid, int& shipPositionX, int& shipPositionY) {

        }
        void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height) {

        }
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,queue& reenterQueue) {

        }
        void ram() {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height,queue& reenterQueue) {

        }
};
class Frigate : public ShootingShip
{ // start up clockwise
    public:
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,queue& reenterQueue) {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height,queue& reenterQueue) {

        }
};
class Corvette : public ShootingShip
{ // immediate nearby random
    public:
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,queue& reenterQueue) {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height,queue& reenterQueue) {

        }
};
class Amphibious : public MovingShip, public SeeingShip, public ShootingShip {
    //can walk land & water
    public:
        void move(Grid** grid, int& shipPositionX, int& shipPositionY) {

        }
        void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height) {

        }
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,queue& reenterQueue) {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height,queue& reenterQueue) {

        }
} ;
class Supership : public SeeingShip, public MovingShip, public RamShip, public ShootingShip {
    public:
        void move(Grid** grid, int& shipPositionX, int& shipPositionY) {

        }
        void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height) {

        }
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,queue& reenterQueue) {

        }
        void ram() {
            
        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height,queue& reenterQueue) {

        }
};
#endif