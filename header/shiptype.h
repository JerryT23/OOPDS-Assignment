#ifndef SHIPTYPE_H
#define SHIPTYPE_H
class Ship {
    int shipPositionX;
    int shipPositionY;
    public:
    void setShipPositionX(int x);
    void setShipPositionY(int y);
    int getShipPositionX() const;
    int getShipPositionY() const;
};
class Battleship : public Ship{
    static char symbol;
    static int amount;
    public:
    void setSymbol(char c);
    void setAmount(int x);
    int getSymbol() const;
    int getAmount() const;
};
class Cruiser : public Ship{
    static char symbol;
    static int amount;
    public:
    void setSymbol(char c);
    void setAmount(int x);
    int getSymbol() const;
    int getAmount() const;
};
class Destroyer : public Ship{
    static char symbol;
    static int amount;
    public:
    void setSymbol(char c);
    void setAmount(int x);
    int getSymbol() const;
    int getAmount() const;
};
class Frigate : public Ship{
    static char symbol;
    static int amount;
    public:
    void setSymbol(char c);
    void setAmount(int x);
    int getSymbol() const;
    int getAmount() const;
};
class Corvette : public Ship{
    static char symbol;
    static int amount;
    public:
    void setSymbol(char c);
    void setAmount(int x);
    int getSymbol() const;
    int getAmount() const;
};
class Amphibious : public Ship{
    static char symbol;
    static int amount;
    public:
    void setSymbol(char c);
    void setAmount(int x);
    int getSymbol() const;
    int getAmount() const;
};
class Supership : public Ship{
    static char symbol; //what symbol oh?
    static int amount;
    public:
    void setSymbol(char c);
    void setAmount(int x);
    int getSymbol() const;
    int getAmount() const;
};
#endif