#ifndef SHIPTYPE_H
#define SHIPTYPE_H
class Ship {
    int shipPositionX;
    int shipPositionY;
    public:
    virtual void looks() = 0;
    virtual void moves() = 0;
    virtual void shoots() = 0;
    virtual void idkyet() = 0;
};

//no overlapping method and attribute for subclasses

class SeeingRobot : public Ship {
   
};

class MovingShip : public Ship {
   
};

class ShootingShip : public Ship {

};

class RamShip : public Ship {

};

class Battleship : 


#endif