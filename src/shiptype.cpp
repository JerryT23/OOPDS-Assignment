#include "../header/shiptype.h"
#include "../header/queue.h"
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
void Ship::setShipPositionIndex(int index)
{
    shipPositionIndex = index;
}
int Ship::getShipPositionIndex() const
{
    return shipPositionIndex;
}
void Ship::setTeamPositionIndex(int index)
{
    teamPositionIndex = index;
}
int Ship::getTeamPositionIndex() const
{
    return teamPositionIndex;
}
bool Ship::oneOfFourNeighbour(int gridX, int gridY, int shipPositionX, int shipPositionY)
{
    bool right = (gridY == shipPositionY) && (gridX == shipPositionX + 1);
    bool left = (gridY == shipPositionY) && (gridX == shipPositionX - 1);
    bool up = (gridY == shipPositionY - 1) && (gridX == shipPositionX);
    bool down = (gridY == shipPositionY + 1) && (gridX == shipPositionX);
    return (right || left || up || down);
}
bool Battleship::friendlyShip(Grid **grid, int shipAdditionX, int shipAdditionY, int shipPositionX, int shipPositionY)
{
    int locationX = shipPositionX + shipAdditionX;
    int locationY = shipPositionY + shipAdditionY;
    if (grid[locationY][locationX].getship() == nullptr)
    {
        return false;
    }
    else if (grid[locationY][locationX].getship()->getTeamName() == this->getTeamName())
    {
        return true;
    }
    return false;
}
void Battleship::look(int x, int y, Grid **grid, int shipPositionX, int shipPositionY, int width, int height)
{
    position temp;
    for (int gridY = shipPositionY - 1; gridY <= shipPositionY + 1; gridY++)
    { // get the grid of nine-square area centered on (x,y)
        if (gridY < 0 || gridY >= height)
            continue; // if outside of grid
        for (int gridX = shipPositionX - 1; gridX <= shipPositionX + 1; gridX++)
        {
            if (gridX < 0 || gridX >= width)
                continue;
            if (gridX == shipPositionX && gridY == shipPositionY)
                continue; // ignore self;
            if (grid[gridY][gridX].getship())
            { // if there's ship at the position
                if (grid[gridY][gridX].getship()->getTeamName() == this->getTeamName())
                {
                    std::cout << "Friendly ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
                    OutputFile << "Friendly ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
                }
                else
                {
                    std::cout << "Enemy ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
                    OutputFile << "Enemy ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
                }
            }
            else if (grid[gridY][gridX].getType() == "0" && oneOfFourNeighbour(gridX, gridY, shipPositionX, shipPositionY))
            { // if it's land && one of four neighbour
            std::cout << "pushback" ;
                temp.x = gridX;
                temp.y = gridY;
                std::cout << temp.x << temp.y << std::endl;
                availableMove.push_back(temp);
            }
        }
    }
}

void Battleship::move(Grid **grid, int &shipPositionX, int &shipPositionY)
{
    if (availableMove.get_size() == 0)
    {
        std::cout << "Ship have nowhere to move!" << std::endl;
        OutputFile << "Ship have nowhere to move!" << std::endl;
        return;
    }
    int index = rand() % availableMove.get_size();
    // set back to the land type after ship leave
    grid[shipPositionY][shipPositionX].setVal(grid[shipPositionY][shipPositionX].getType());
    grid[shipPositionY][shipPositionX].setTaken(false);
    grid[shipPositionY][shipPositionX].setship(nullptr);
    //---------------------
    grid[availableMove[index].y][availableMove[index].x].setVal(this->getDisplay());
    grid[availableMove[index].y][availableMove[index].x].setTaken(true);
    grid[availableMove[index].y][availableMove[index].x].setship(this);
    shipPositionX = availableMove[index].x;
    shipPositionY = availableMove[index].y;
    std::cout << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
    OutputFile << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
}
void Battleship::shoot(int x, int y, Grid **grid, int shipPositionX, int shipPositionY, queue &reenterQueue)
{
    int shootLocationX = shipPositionX + x;
    int shootLocationY = shipPositionY + y;
    std::cout << this->getDisplay() << " Ship shoot at Y:" << shootLocationY << " X:" << shootLocationX;
    OutputFile << this->getDisplay() << " Ship shoot at Y:" << shootLocationY << " X:" << shootLocationX;
    if (grid[shootLocationY][shootLocationX].getship() == nullptr)
    {
        std::cout << " which has no ship." << std::endl;
        OutputFile << " which has no ship." << std::endl;
    }
    else
    {
        std::cout << " which destroyed " << grid[shootLocationY][shootLocationX].getship()->getDisplay() << std::endl;
        OutputFile << " which destroyed " << grid[shootLocationY][shootLocationX].getship()->getDisplay() << std::endl;

        grid[shootLocationY][shootLocationX].getship()->lifeMinus1();
        this->totalKillIncrement();
        // to be do upgrade, queue
        std::cout << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;
        OutputFile << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;

        std::cout << grid[shootLocationY][shootLocationX].getship()->getDisplay() << " Life remaining: " << grid[shootLocationY][shootLocationX].getship()->getLife() << std::endl;
        OutputFile << grid[shootLocationY][shootLocationX].getship()->getDisplay() << " Life remaining: " << grid[shootLocationY][shootLocationX].getship()->getLife() << std::endl;
        reenterQueue.enqueue(grid[shootLocationY][shootLocationX].getship());
        // set back to the land type after ship leave
        grid[shootLocationY][shootLocationX].setTaken(false);
        grid[shootLocationY][shootLocationX].setVal(grid[shootLocationY][shootLocationX].getType());
        grid[shootLocationY][shootLocationX].setship(nullptr);
        //-------------------------------
    }
}