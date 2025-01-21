#ifndef SHIPTYPE_H
#define SHIPTYPE_H
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "./grid.h"
#include "./vector.h"
#include "./externalOutput.h"
#include "../header/linkedlist.h"
using namespace std;
class Node;
class LinkedList;
class queue;
class Ship
{
    std::string type;
    std::string display;
    std::string teamName;
    int life;
    int totalKilled;
    int teamIndex;
    int shipPositionX;
    int shipPositionY;
public:
    Ship() : life(3),totalKilled(0){}
    virtual void action() = 0;
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
    void setTeamIndex(int index);
    int getTeamIndex() const;
    void setShipPositionX(int x);
    int getShipPositionX() const;
    void setShipPositionY(int x);
    int getShipPositionY() const;
    bool oneOfFourNeighbour(int gridX,int gridY,int shipPositionX,int shipPositionY);
    virtual ~Ship() {}
};

// no overlapping method and attribute for subclasses

class SeeingShip : virtual public Ship
{
public:
    virtual void look() = 0;
    virtual ~SeeingShip() {}
};

class MovingShip : virtual public Ship
{
public:
    virtual void move() = 0;
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
    struct position {
        int x;
        int y;
    };
    Vector<position> availableMove;
    int infiniteLoopDetector = 0;
    int shootX,shootY;
    public:
        bool friendlyShip();
        void move();
        void look();
        void shoot();
        void action() {
            srand(time(0));
            cout << "Battleship" << endl;
        }
};

class Cruiser : public SeeingShip, public MovingShip, public RamShip
{
    struct position {
        int x;
        int y;
    };
    Vector<position> availableMove;
    public:
        bool friendlyShip();
        void move();
        void look();
        void ram();
        void action() {
            cout << "Cruiser" << endl;
        }
};
class Destroyer : public MovingShip, public SeeingShip, public ShootingShip, public RamShip
{
    public:
        void move() {

        }
        void look() {

        }
        void shoot() {

        }
        void ram() {

        }
        void action() {
            cout << "Destroyer" << endl;
        }
};
class Frigate : public ShootingShip
{ // start up clockwise
    public:
        void shoot() {

        }
        void action() {
            cout << "Frigate" << endl;
        }
};
class Corvette : public ShootingShip
{ // immediate nearby random
    public:
        void shoot() {

        }
        void action() {
            cout << "Corvette" << endl;
        }
};
class Amphibious : public MovingShip, public SeeingShip, public ShootingShip {
    //can walk land & water
    public:
        void move() {

        }
        void look() {

        }
        void shoot() {

        }
        void action() {
            cout << "Amphibious" << endl;
        }
} ;
class Supership : public SeeingShip, public MovingShip, public RamShip, public ShootingShip {
    public:
        void move() {

        }
        void look() {

        }
        void shoot() {

        }
        void ram() {
            
        }
        void action() {
            cout << "Supership" << endl;
        }
};
#endif