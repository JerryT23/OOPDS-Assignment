#include "../header/shiptype.h"
#include "../header/linkedlist.h"
#include "../header/queue.h"
#include "../header/node.h"
void Ship::setType(std::string s)
{
    type = s;
}
std::string Ship::getType() const
{
    return type;
}
void Ship::setDisplay(std::string s)
{
    display = s;
}
std::string Ship::getDisplay() const
{
    return display;
}
void Ship::setTeamName(std::string teamname)
{
    teamName = teamname;
}
std::string Ship::getTeamName() const
{
    return teamName;
}
void Ship::lifeMinus1()
{
    life -= 1;
}
int Ship::getLife() const
{
    return life;
}
void Ship::totalKillIncrement()
{
    totalKilled++;
}
int Ship::getTotalKill() const
{
    return totalKilled;
}
void Ship::setTeamIndex(int index)
{
    teamIndex = index;
}
int Ship::getTeamIndex() const
{
    return teamIndex;
}
void Ship::setShipPositionX(int x) {
    shipPositionX = x;
}
int Ship::getShipPositionX() const {return shipPositionX;}
void Ship::setShipPositionY(int y) {
    shipPositionY = y;
}
int Ship::getShipPositionY() const {
    return shipPositionY;
}
bool Ship::oneOfFourNeighbour(int gridX, int gridY, int shipPositionX, int shipPositionY)
{
    bool right = (gridY == shipPositionY) && (gridX == shipPositionX + 1);
    bool left = (gridY == shipPositionY) && (gridX == shipPositionX - 1);
    bool up = (gridY == shipPositionY - 1) && (gridX == shipPositionX);
    bool down = (gridY == shipPositionY + 1) && (gridX == shipPositionX);
    return (right || left || up || down);
}

bool Battleship::friendlyShip()
{
    // int locationX = shipPositionX + shipAdditionX;
    // int locationY = shipPositionY + shipAdditionY;
    // if (grid[locationY][locationX].getship() == nullptr)
    // {
    //     return false;
    // }
    // else if (grid[locationY][locationX].getship()->getTeamName() == this->getTeamName())
    // {
    //     return true;
    // }
    // return false;
}
void Battleship::look()
{
    // position temp;
    // for (int gridY = shipPositionY - 1; gridY <= shipPositionY + 1; gridY++)
    // { // get the grid of nine-square area centered on (x,y)
    //     if (gridY < 0 || gridY >= height)
    //         continue; // if outside of grid
    //     for (int gridX = shipPositionX - 1; gridX <= shipPositionX + 1; gridX++)
    //     {
    //         if (gridX < 0 || gridX >= width)
    //             continue;
    //         if (gridX == shipPositionX && gridY == shipPositionY)
    //             continue; // ignore self;
    //         if (grid[gridY][gridX].getship())
    //         { // if there's ship at the position
    //             if (grid[gridY][gridX].getship()->getTeamName() == this->getTeamName())
    //             {
    //                 std::cout << "Friendly ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
    //                 OutputFile << "Friendly ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
    //             }
    //             else
    //             {
    //                 std::cout << "Enemy ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
    //                 OutputFile << "Enemy ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
    //             }
    //         }
    //         else if (grid[gridY][gridX].getType() == "0" && oneOfFourNeighbour(gridX, gridY, shipPositionX, shipPositionY))
    //         { // if it's land && one of four neighbour
    //             temp.x = gridX;
    //             temp.y = gridY;
    //             availableMove.push_back(temp);
    //         }
    //     }
    // }
}

void Battleship::move()
{
    // if (availableMove.get_size() == 0)
    // {
    //     std::cout << "Ship have nowhere to move!" << std::endl;
    //     OutputFile << "Ship have nowhere to move!" << std::endl;
    //     return;
    // }
    // int index = rand() % availableMove.get_size();
    // // set back to the land type after ship leave
    // grid[shipPositionY][shipPositionX].setVal(grid[shipPositionY][shipPositionX].getType());
    // grid[shipPositionY][shipPositionX].setTaken(false);
    // grid[shipPositionY][shipPositionX].setship(nullptr);
    // //---------------------
    // grid[availableMove[index].y][availableMove[index].x].setVal(this->getDisplay());
    // grid[availableMove[index].y][availableMove[index].x].setTaken(true);
    // grid[availableMove[index].y][availableMove[index].x].setship(this);
    // shipPositionX = availableMove[index].x;
    // shipPositionY = availableMove[index].y;
    // std::cout << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
    // OutputFile << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
}
void Battleship::shoot()
{
    // int shootLocationX = shipPositionX + x;
    // int shootLocationY = shipPositionY + y;
    // std::cout << this->getDisplay() << " Ship shoot at Y:" << shootLocationY << " X:" << shootLocationX;
    // OutputFile << this->getDisplay() << " Ship shoot at Y:" << shootLocationY << " X:" << shootLocationX;
    // if (grid[shootLocationY][shootLocationX].getship() == nullptr)
    // {
    //     std::cout << " which has no ship." << std::endl;
    //     OutputFile << " which has no ship." << std::endl;
    // }
    // else
    // {
    //     std::cout << " which destroyed " << grid[shootLocationY][shootLocationX].getship()->getDisplay() << std::endl;
    //     OutputFile << " which destroyed " << grid[shootLocationY][shootLocationX].getship()->getDisplay() << std::endl;

    //     grid[shootLocationY][shootLocationX].getship()->lifeMinus1();
    //     this->totalKillIncrement();
    //     // to be do upgrade, queue
    //     std::cout << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;
    //     OutputFile << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;

    //     std::cout << grid[shootLocationY][shootLocationX].getship()->getDisplay() << " Life remaining: " << grid[shootLocationY][shootLocationX].getship()->getLife() << std::endl;
    //     OutputFile << grid[shootLocationY][shootLocationX].getship()->getDisplay() << " Life remaining: " << grid[shootLocationY][shootLocationX].getship()->getLife() << std::endl;
    //     reenterQueue.enqueue(grid[shootLocationY][shootLocationX].getship());
    //     // set back to the land type after ship leave
    //     grid[shootLocationY][shootLocationX].setTaken(false);
    //     grid[shootLocationY][shootLocationX].setVal(grid[shootLocationY][shootLocationX].getType());
    //     grid[shootLocationY][shootLocationX].setship(nullptr);
    //     //-------------------------------
        
    // }
    // if (this->getTotalKill() == 1) {
    //     // Upgrade to Cruiser
    //     int index = this->getShipPositionIndex();
    //     Ship* upgradedShip = new Cruiser();
    //     upgradedShip->setType("Cruiser");
    //     upgradedShip->setDisplay(this->getDisplay());
    //     upgradedShip->setTeamName(this->getTeamName());
    //     upgradedShip->setShipPositionIndex(index);
    //     upgradedShip->setTeamPositionIndex(this->getTeamPositionIndex());

    //     // Replace in the LinkedList
    //     gameShipPtr = ships.replace(index, upgradedShip);

    //     std::cout << "Battleship upgraded to Cruiser!" << std::endl;
    //     OutputFile << "Battleship upgraded to Cruiser!" << std::endl;
    // }       
}
// //----------------------------------------------Cruiser----------------------------------------------------------------//
bool Cruiser::friendlyShip()
{
    // int locationX = shipPositionX + shipAdditionX;
    // int locationY = shipPositionY + shipAdditionY;
    // if (grid[locationY][locationX].getship() == nullptr)
    // {
    //     return false;
    // }
    // else if (grid[locationY][locationX].getship()->getTeamName() == this->getTeamName())
    // {
    //     return true;
    // }
    // return false;
}
void Cruiser::look()
{
    // position temp;
    // for (int gridY = shipPositionY - 1; gridY <= shipPositionY + 1; gridY++)
    // { // get the grid of nine-square area centered on (x,y)
    //     if (gridY < 0 || gridY >= height)
    //         continue; // if outside of grid
    //     for (int gridX = shipPositionX - 1; gridX <= shipPositionX + 1; gridX++)
    //     {
    //         if (gridX < 0 || gridX >= width)
    //             continue;
    //         if (gridX == shipPositionX && gridY == shipPositionY)
    //             continue; // ignore self;
    //         if (grid[gridY][gridX].getship())
    //         { // if there's ship at the position
    //             if (grid[gridY][gridX].getship()->getTeamName() == this->getTeamName())
    //             {
    //                 std::cout << "Friendly ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
    //                 OutputFile << "Friendly ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
    //             }
    //             else
    //             {
    //                 std::cout << "Enemy ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
    //                 OutputFile << "Enemy ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
    //             }
    //         }
    //         else if (grid[gridY][gridX].getType() == "0" && oneOfFourNeighbour(gridX, gridY, shipPositionX, shipPositionY))
    //         { // if it's land && one of four neighbour
    //             temp.x = gridX;
    //             temp.y = gridY;
    //             availableMove.push_back(temp);
    //         }
    //     }
    // }
}

void Cruiser::move()
{
    // if (availableMove.get_size() == 0)
    // {
    //     std::cout << "Ship have nowhere to move!" << std::endl;
    //     OutputFile << "Ship have nowhere to move!" << std::endl;
    //     return;
    // }
    // int index = rand() % availableMove.get_size();
    // // set back to the land type after ship leave
    // grid[shipPositionY][shipPositionX].setVal(grid[shipPositionY][shipPositionX].getType());
    // grid[shipPositionY][shipPositionX].setTaken(false);
    // grid[shipPositionY][shipPositionX].setship(nullptr);
    // //---------------------
    // grid[availableMove[index].y][availableMove[index].x].setVal(this->getDisplay());
    // grid[availableMove[index].y][availableMove[index].x].setTaken(true);
    // grid[availableMove[index].y][availableMove[index].x].setship(this);
    // shipPositionX = availableMove[index].x;
    // shipPositionY = availableMove[index].y;
    // std::cout << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
    // OutputFile << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
}

void Cruiser::ram()
{
    // for (int gridY = shipPositionY - 1; gridY <= shipPositionY + 1; gridY++)
    // { // get the grid of nine-square area centered on (x,y)
    //     if (gridY < 0 || gridY >= height)
    //         continue; // if outside of grid
    //     for (int gridX = shipPositionX - 1; gridX <= shipPositionX + 1; gridX++)
    //     {
    //         if (gridX < 0 || gridX >= width)
    //             continue;
    //         if (gridX == shipPositionX && gridY == shipPositionY)
    //             continue; // ignore self;
    //         else if (grid[gridY][gridX].getship())
    //         { // if there's ship at the position
    //             if (grid[gridY][gridX].getship()->getTeamName() != this->getTeamName())
    //             {
    //                 // set back to the land type after ship leave
    //                 grid[shipPositionY][shipPositionX].setVal(grid[shipPositionY][shipPositionX].getType());
    //                 grid[shipPositionY][shipPositionX].setTaken(false);
    //                 grid[shipPositionY][shipPositionX].setship(nullptr);
    //                 //---------------------
    //                 grid[gridY][gridX].setVal(this->getDisplay());
    //                 grid[gridY][gridX].setTaken(true);
    //                 grid[gridY][gridX].setship(this);
    //                 shipPositionX = gridX;
    //                 shipPositionY = gridY;
    //                 std::cout << this->getDisplay() << " Ship move to Y:" << gridY << " X:" << gridX << std::endl;
    //                 OutputFile << this->getDisplay() << " Ship move to Y:" << gridY << " X:" << gridX << std::endl;

    //                 std::cout << " which destroyed " << grid[gridY][gridX].getship()->getDisplay() << std::endl;
    //                 OutputFile << " which destroyed " << grid[gridY][gridX].getship()->getDisplay() << std::endl;

    //                 grid[gridY][gridX].getship()->lifeMinus1();
    //                 this->totalKillIncrement();

    //                 std::cout << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;
    //                 OutputFile << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;

    //                 std::cout << grid[gridY][gridX].getship()->getDisplay() << " Life remaining: " << grid[gridY][gridX].getship()->getLife() << std::endl;
    //                 OutputFile << grid[gridY][gridX].getship()->getDisplay() << " Life remaining: " << grid[gridY][gridX].getship()->getLife() << std::endl;
    //                 reenterQueue.enqueue(grid[gridY][gridX].getship());
    //             }
    //         }
    //     }
    // }
}
