#ifndef SHIPTYPE_H
#define SHIPTYPE_H
#include <iostream>
#include "../header/vector.h"
class Ship
{
    int shipPositionX;
    int shipPositionY;
    char symbol;
    int life;

public: // find a virtual func for base
    Ship() : life(3) {}
    virtual void action() = 0;
    void setSymbol(char c);
    char getSymbol() const;
    virtual ~Ship() {}
};

class Team
{
    std::string teamName;
    int shipAmount; //in a team
    Ship** ships;
    public:
    std::string getTeamName() const;
    void setTeamName(std::string s);
    void setShips(int size);
    ~Team() {
    for(int i = 0; i < shipAmount; i++) {
        delete[] ships[i];
    }
    delete[] ships;
}
};

// no overlapping method and attribute for subclasses

class SeeingRobot : virtual public Ship
{
public:
    virtual void look() = 0;
    virtual ~SeeingRobot() {}
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


class Battleship : public MovingShip, public SeeingRobot, public ShootingShip
{
};

class Cruiser : public SeeingRobot, public MovingShip, public RamShip
{
};

class Destroyer : public MovingShip, public SeeingRobot, public ShootingShip, public RamShip
{
};
class Frigate : public ShootingShip
{ // start up clockwise
};
class Corvette : public ShootingShip
{ // immediate nearby random
};
class Amphibious : public MovingShip, public SeeingRobot, public ShootingShip {
    //can walk land & water
} ;
class Supership : public SeeingRobot, public MovingShip, public RamShip {
    //
} ;

#endif