#ifndef SHIPTYPE_H
#define SHIPTYPE_H
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "./vector.h"
#include "./externalOutput.h"
using namespace std;

class Grid;
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
    Vector<Ship*> killedShip;
    bool upgradeFlag;
public:
    Ship();
    virtual void action(Grid** grid) = 0;
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
    void pushKilledShip(Ship* pkilledShip);
    Ship* getKilledShip(int index);
    Vector<Ship*> getVecKilledShip();
    void setUpgradeFlag(bool b);
    bool getUpgradeFlag() const;
    bool oneOfFourNeighbour(int gridX,int gridY,int shipPositionX,int shipPositionY);
    bool friendlyShip(Grid** grid,int shootX, int shootY);
    virtual ~Ship() {}
};

// no overlapping method and attribute for subclasses

class SeeingShip : virtual public Ship
{
public:
    virtual void look(Grid** grid) = 0;
    virtual ~SeeingShip() {}
};

class MovingShip : virtual public Ship
{
public:
    virtual void move(Grid** grid) = 0;
    virtual ~MovingShip() {}
};

class ShootingShip : virtual public Ship
{
public:
    virtual void shoot(Grid** grid) = 0;
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
    public:
        void move(Grid** grid);
        void look(Grid** grid);
        void shoot(Grid** grid);
        void action(Grid** grid);
};

class Cruiser : public SeeingShip, public MovingShip, public RamShip
{
    struct position {
        int x;
        int y;
    };
    Vector<position> availableMove;
    public:
        void move(Grid** grid);
        void look(Grid** grid);
        void ram();
        void action(Grid** grid) {
            cout << "Cruiser" << endl;
        }
};
class Destroyer : public MovingShip, public SeeingShip, public ShootingShip, public RamShip
{
    public:
        void move(Grid** grid) {

        }
        void look(Grid** grid) {

        }
        void shoot(Grid** grid) {

        }
        void ram() {

        }
        void action(Grid** grid) {
            cout << "Destroyer" << endl;
        }
};
class Frigate : public ShootingShip
{ // start up clockwise
    public:
        void shoot(Grid** grid) {

        }
        void action(Grid** grid) {
            cout << "Frigate" << endl;
        }
};
class Corvette : public ShootingShip
{ // immediate nearby random
    public:
        void shoot(Grid** grid) {

        }
        void action(Grid** grid) {
            cout << "Corvette" << endl;
        }
};
class Amphibious : public MovingShip, public SeeingShip, public ShootingShip {
    //can walk land & water
    public:
        void move(Grid** grid) {

        }
        void look(Grid** grid) {

        }
        void shoot(Grid** grid) {

        }
        void action(Grid** grid) {
            cout << "Amphibious" << endl;
        }
} ;
class Supership : public SeeingShip, public MovingShip, public RamShip, public ShootingShip {
    public:
        void move(Grid** grid) {

        }
        void look(Grid** grid) {

        }
        void shoot(Grid** grid) {

        }
        void ram() {
            
        }
        void action(Grid** grid) {
            cout << "Supership" << endl;
        }
};
#endif