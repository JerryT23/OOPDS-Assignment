#ifndef SHIPTYPE_H
#define SHIPTYPE_H
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "./grid.h"
#include "./vector.h"
#include "./externalOutput.h"
class Ship
{
    std::string type;
    std::string display;
    std::string teamName;
    int life;
    int totalKilled;
    int positionIndex;

public:
    Ship() : life(3),totalKilled(0){}
    virtual void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) = 0;
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
    void setPositionIndex(int index);
    int getPositionIndex() const;
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
    virtual void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY) = 0;
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
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY) {
            int shootLocationX = shipPositionX + x;
            int shootLocationY = shipPositionY + y;
            std::cout << this->getDisplay() << " Ship shoot at Y:" << shootLocationY << " X:" << shootLocationX;
            OutputFile << this->getDisplay() << " Ship shoot at Y:" << shootLocationY << " X:" << shootLocationX;
            if(grid[shootLocationY][shootLocationX].getship() == nullptr) {
                std::cout << " which has no ship." << std::endl;
                OutputFile << " which has no ship." << std::endl;
            } else {
                std::cout << " which destroyed " << grid[shootLocationY][shootLocationX].getship()->getDisplay() << std::endl;
                OutputFile << " which destroyed " << grid[shootLocationY][shootLocationX].getship()->getDisplay() << std::endl;
                
                grid[shootLocationY][shootLocationX].getship()->lifeMinus1();
                this->totalKillIncrement();
                //to be do upgrade, queue
                std::cout << this->getDisplay() << " Total Kill:"<< this->getTotalKill()<< std::endl;
                OutputFile << this->getDisplay() << " Total Kill:"<< this->getTotalKill()<< std::endl;

                std::cout << grid[shootLocationY][shootLocationX].getship()->getDisplay() <<
                " Life remaining: " << grid[shootLocationY][shootLocationX].getship()->getLife() << std::endl;
                OutputFile << grid[shootLocationY][shootLocationX].getship()->getDisplay() <<
                " Life remaining: " << grid[shootLocationY][shootLocationX].getship()->getLife() << std::endl;

                // set back to the land type after ship leave
                grid[shootLocationY][shootLocationX].setTaken(false);
                grid[shootLocationY][shootLocationX].setVal(grid[shootLocationY][shootLocationX].getType());
                grid[shootLocationY][shootLocationX].setship(nullptr);
                //-------------------------------
            }
        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {
            srand(time(0));
            std::cout << this->getDisplay() << " Ship look(0,0):" <<std::endl << "Ship type:"<<this->getType()<<std::endl;
            OutputFile << this->getDisplay() << " Ship look(0,0):" <<std::endl << "Ship type:"<<this->getType()<<std::endl;
            look(0,0,grid,shipPositionX,shipPositionY,width,height);
            move(grid,shipPositionX,shipPositionY);
            availableMove.clear();
            //generate shoot coordinate
            do {
                if(infiniteLoopDetector > 1000) { //if loop 1000 times still cant find a place to shoot
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
            if(infiniteLoopDetector <= 1000) shoot(shootX,shootY,grid,shipPositionX,shipPositionY);
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
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {
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
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY) {

        }
        void ram() {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {

        }
};
class Frigate : public ShootingShip
{ // start up clockwise
    public:
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY) {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {

        }
};
class Corvette : public ShootingShip
{ // immediate nearby random
    public:
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY) {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {

        }
};
class Amphibious : public MovingShip, public SeeingShip, public ShootingShip {
    //can walk land & water
    public:
        void move(Grid** grid, int& shipPositionX, int& shipPositionY) {

        }
        void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height) {

        }
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY) {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {

        }
} ;
class Supership : public SeeingShip, public MovingShip, public RamShip, public ShootingShip {
    public:
        void move(Grid** grid, int& shipPositionX, int& shipPositionY) {

        }
        void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height) {

        }
        void shoot(int x, int y, Grid** grid, int shipPositionX, int shipPositionY) {

        }
        void ram() {
            
        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {

        }
};
#endif