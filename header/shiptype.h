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

public:
    Ship() : life(3) {}
    virtual void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) = 0;
    void setType(std::string s);
    std::string getType() const;
    void setDisplay(std::string s);
    std::string getDisplay() const;
    void setTeamName(std::string teamname);
    std::string getTeamName() const;
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
    virtual void shoot() = 0;
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
    public:
        void move(Grid** grid, int& shipPositionX, int& shipPositionY);
        void look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height);
        void shoot() {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {
            std::cout << this->getDisplay() << " Ship look(0,0):" <<std::endl;
            OutputFile << this->getDisplay() << " Ship look(0,0):" <<std::endl;
            look(0,0,grid,shipPositionX,shipPositionY,width,height);
            move(grid,shipPositionX,shipPositionY);
            availableMove.clear();
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
        void shoot() {

        }
        void ram() {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {

        }
};
class Frigate : public ShootingShip
{ // start up clockwise
    public:
        void shoot() {

        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {

        }
};
class Corvette : public ShootingShip
{ // immediate nearby random
    public:
        void shoot() {

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
        void shoot() {

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
        void shoot() {

        }
        void ram() {
            
        }
        void action(Grid** grid, int& shipPositionX, int& shipPositionY,int width,int height) {

        }
};
#endif