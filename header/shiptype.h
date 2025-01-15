#ifndef SHIPTYPE_H
#define SHIPTYPE_H
#include <iostream>
#include <unordered_map>
#include "./grid.h"
class Ship
{
    std::string type;
    std::string display;
    std::string teamName;
    int life;

public:
    Ship() : life(3) {}
    virtual void action(Grid** grid) = 0;
    void setType(std::string s);
    std::string getType() const;
    void setDisplay(std::string s);
    std::string getDisplay() const;
    void setTeamName(std::string teamname);
    std::string getTeamName() const;
    virtual ~Ship() {}
};

// no overlapping method and attribute for subclasses

class SeeingShip : virtual public Ship
{
public:
    virtual void look(int x, int y, Grid** grid, int shipIndex) = 0;
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
        void look(int x, int y, Grid** grid, int shipIndex) {

        }
        void shoot() {

        }
        void action(Grid** grid) {
            move();
        }
};

class Cruiser : public SeeingShip, public MovingShip, public RamShip
{
    public:
        void move() {

        }
        void look(int x, int y, Grid** grid, int shipIndex) {

        }
        void ram() {

        }
        void action(Grid** grid) {
            std::cout << "I'm Cruiser brather";
        }
};

class Destroyer : public MovingShip, public SeeingShip, public ShootingShip, public RamShip
{
    public:
        void move() {

        }
        void look(int x, int y, Grid** grid, int shipIndex) {

        }
        void shoot() {

        }
        void ram() {

        }
        void action(Grid** grid) {

        }
};
class Frigate : public ShootingShip
{ // start up clockwise
    public:
        void shoot() {

        }
        void action(Grid** grid) {

        }
};
class Corvette : public ShootingShip
{ // immediate nearby random
    public:
        void shoot() {

        }
        void action(Grid** grid) {

        }
};
class Amphibious : public MovingShip, public SeeingShip, public ShootingShip {
    //can walk land & water
    public:
        void move() {

        }
        void look(int x, int y, Grid** grid, int shipIndex) {

        }
        void shoot() {

        }
        void action(Grid** grid) {

        }
} ;
class Supership : public SeeingShip, public MovingShip, public RamShip, public ShootingShip {
    public:
        void move() {

        }
        void look(int x, int y, Grid** grid, int shipIndex) {

        }
        void shoot() {

        }
        void ram() {
            
        }
        void action(Grid** grid) {

        }
};
#endif