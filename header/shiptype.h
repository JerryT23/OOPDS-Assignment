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
    void setShipsCol(int index,Ship* obj);
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
    public:
        void move() {

        }
        void look() {

        }
        void shoot() {

        }
        void action() {

        }
};

class Cruiser : public SeeingRobot, public MovingShip, public RamShip
{
    public:
        void move() {

        }
        void look() {

        }
        void ram() {

        }
        void action() {

        }
};

class Destroyer : public MovingShip, public SeeingRobot, public ShootingShip, public RamShip
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

        }
};
class Frigate : public ShootingShip
{ // start up clockwise
    public:
        void shoot() {

        }
        void action() {

        }
};
class Corvette : public ShootingShip
{ // immediate nearby random
    public:
        void shoot() {

        }
        void action() {

        }
};
class Amphibious : public MovingShip, public SeeingRobot, public ShootingShip {
    //can walk land & water
    public:
        void move() {

        }
        void look() {

        }
        void shoot() {

        }
        void action() {

        }
} ;
class Supership : public SeeingRobot, public MovingShip, public RamShip, public ShootingShip {
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

        }
} ;

#endif