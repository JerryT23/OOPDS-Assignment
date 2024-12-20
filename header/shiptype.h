#ifndef SHIPTYPE_H
#define SHIPTYPE_H
class Ship {
    int shipPositionX;
    int shipPositionY;
    public:
    virtual void look() = 0;
    virtual void move() = 0;
    virtual void shoot() = 0;
    virtual void ram() = 0;
};

//no overlapping method and attribute for subclasses

class SeeingRobot : public Ship {
   void look() {
    //implement look
   }
};

class MovingShip : public Ship {
   //implement look
};

class ShootingShip : public Ship {
    //implement look
};

class RamShip : public Ship {
    //implement look
};

class Battleship : public MovingShip, public SeeingRobot, public ShootingShip{

};

class Cruiser : public SeeingRobot, public MovingShip, public RamShip {

};

class Destroyer : public MovingShip, public SeeingRobot, public ShootingShip, public RamShip {

};
class Frigate : public ShootingShip, { //start up clockwise

};


#endif