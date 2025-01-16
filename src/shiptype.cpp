#include "../header/shiptype.h"
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
                xNy.push_back(gridX);
                xNy.push_back(gridY);
                availableMove.push_back(xNy);
                xNy.clear();
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
    grid[availableMove[index][1]][availableMove[index][0]].setVal(this->getDisplay());
    grid[availableMove[index][1]][availableMove[index][0]].setTaken(true);
    grid[availableMove[index][1]][availableMove[index][0]].setship(this);
    shipPositionX = availableMove[index][0];
    shipPositionY = availableMove[index][1];
    std::cout << this->getDisplay() << " Ship move to Y:" << availableMove[index][1] << " X:" << availableMove[index][0] << std::endl;
    OutputFile << this->getDisplay() << " Ship move to Y:" << availableMove[index][1] << " X:" << availableMove[index][0] << std::endl;
}