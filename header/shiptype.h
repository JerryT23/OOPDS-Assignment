#ifndef SHIPTYPE_H
#define SHIPTYPE_H
#include <iostream>
#include <unordered_map>
#include "../header/vector.h"
class Ship
{
    std::string type;
    std::string display;
    int life;

public:
    Ship() : life(3) {}
    virtual void action() = 0;
    void setType(std::string s);
    std::string getType() const;
    void setDisplay(std::string s);
    std::string getDisplay() const;
    virtual ~Ship() {}
};

class Team
{
    std::string teamName;
    int (*shipPositions)[2];
    int shipAmount; //in a team
    Ship** ships;
    public:
    std::string getTeamName() const;
    void setTeamName(std::string s);
    void setShipPosition(int index, int x, int y);
    int* getShipPosition(int index) const;
    void setShips(int size);
    void setShipsCol(int index,Ship* obj);
    int getShipAmount() const;
    Ship* getShip(int index);
    ~Team() {
        delete[] shipPositions;
    for(int i = 0; i < shipAmount; i++) {
        delete ships[i];
    }
    delete[] ships;
    }
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
    public:
        void move() {

        }
        void look() {

        }
        void shoot() {

        }
        void action() {
            std::cout << "I'm battleship brather";
        }
};

class Cruiser : public SeeingShip, public MovingShip, public RamShip
{
    public:
        void move() {

        }
        void look() {

        }
        void ram() {

        }
        void action() {
            std::cout << "I'm Cruiser brather";
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

        }
} ;

#endif