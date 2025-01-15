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
bool Ship::oneOfFourNeighbour(int gridX,int gridY,int shipPositionX,int shipPositionY){
            bool right = (gridY == shipPositionY) && (gridX == shipPositionX+1);
            bool left = (gridY == shipPositionY) && (gridX == shipPositionX-1);
            bool up = (gridY == shipPositionY-1) && (gridX == shipPositionX);
            bool down = (gridY == shipPositionY+1) && (gridX == shipPositionX);
            return (right||left||up||down);
        }
void Battleship::look(int x, int y, Grid** grid, int shipPositionX, int shipPositionY,int width, int height)
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
                }
                else
                {
                    std::cout << "Enemy ship found at -> Y:" << gridY << " X:" << gridX << std::endl;
                }
            }
            else if (grid[gridY][gridX].getType() == "0" && oneOfFourNeighbour(gridX,gridY,shipPositionX,shipPositionY))
            { // if it's land && one of four neighbour
                xNy.push_back(gridX);
                xNy.push_back(gridY);
                availableMove.push_back(xNy);
                xNy.clear();
            }
        }
    }
}