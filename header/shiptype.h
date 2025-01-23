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
    queue* killedShip;
    bool upgradeFlag;
    bool inBattlefield;
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
    void setLife(int upgradedShipLife);
    int getLife() const;
    void totalKillIncrement();
    void resetKillCount();
    int getTotalKill() const;
    void setTeamIndex(int index);
    int getTeamIndex() const;
    void setShipPositionX(int x);
    int getShipPositionX() const;
    void setShipPositionY(int x);
    int getShipPositionY() const;
    queue* getKilledShips();
    void setUpgradeFlag(bool b);
    bool getUpgradeFlag() const;
    void setInBattlefield(bool b);
    bool getInBattlefield() const;
    bool oneOfFourNeighbour(int gridX,int gridY,int shipPositionX,int shipPositionY);
    bool friendlyShip(Grid** grid,int shootX, int shootY);
    virtual ~Ship();
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
    virtual void ram(Grid** grid) = 0;
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
    Vector<position> ramPosition;
    public:
        void move(Grid** grid);
        void look(Grid** grid);
        void ram(Grid **grid);
        void action(Grid** grid);
};
class Destroyer : public MovingShip, public SeeingShip, public ShootingShip, public RamShip
{
    struct position {
        int x;
        int y;
    };
    int infiniteLoopDetector = 0;
    Vector<position> availableMove;
    Vector<position> ramPosition;
    
    public:
        void move(Grid** grid);
        void look(Grid** grid);
        void ram(Grid **grid);
        void shoot(Grid** grid);
        void action(Grid** grid);
};
class Frigate : public ShootingShip
{ // start up clockwise
    int shootPositionX = 0;
    int shootPositionY = 0;
    int lastShootDirection = 0;
    public:
        void shoot(Grid** grid);
        void action(Grid** grid);
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
        void ram(Grid** grid) {
            
        }
        void action(Grid** grid) {
            cout << "Supership" << endl;
        }
};
#endif