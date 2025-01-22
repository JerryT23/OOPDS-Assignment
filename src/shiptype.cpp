#include "../header/shiptype.h"
#include "../header/grid.h"
#include "../header/queue.h"
#include <chrono> 

Ship::Ship() : life(3), totalKilled(0),killedShip(new queue),inBattlefield(true){}
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
void Ship::setShipPositionX(int x)
{
    shipPositionX = x;
}
int Ship::getShipPositionX() const { return shipPositionX; }
void Ship::setShipPositionY(int y)
{
    shipPositionY = y;
}
int Ship::getShipPositionY() const
{
    return shipPositionY;
}
queue* Ship::getKilledShips() {
    return killedShip;
}
void Ship::setUpgradeFlag(bool b)
{
    upgradeFlag = b;
}
bool Ship::getUpgradeFlag() const
{
    return upgradeFlag;
}
void Ship::setInBattlefield(bool b) {
    inBattlefield = b;
}
bool Ship::getInBattlefield() const {
    return inBattlefield;
}
bool Ship::oneOfFourNeighbour(int gridX, int gridY, int shipPositionX, int shipPositionY)
{
    bool right = (gridY == shipPositionY) && (gridX == shipPositionX + 1);
    bool left = (gridY == shipPositionY) && (gridX == shipPositionX - 1);
    bool up = (gridY == shipPositionY - 1) && (gridX == shipPositionX);
    bool down = (gridY == shipPositionY + 1) && (gridX == shipPositionX);
    return (right || left || up || down);
}
bool Ship::friendlyShip(Grid **grid, int shootX, int shootY)
{
    int locationX = this->getShipPositionX() + shootX;
    int locationY = this->getShipPositionY() + shootY;
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
// //----------------------------------------------Battleship----------------------------------------------------------------//
void Battleship::look(Grid **grid)
{
    position temp;
    for (int gridY = this->getShipPositionY() - 1; gridY <= this->getShipPositionY() + 1; gridY++)
    { // get the grid of nine-square area centered on (x,y)
        if (gridY < 0 || gridY >= Grid::getHeight())
            continue; // if outside of grid
        for (int gridX = this->getShipPositionX() - 1; gridX <= this->getShipPositionX() + 1; gridX++)
        {
            if (gridX < 0 || gridX >= Grid::getwidth())
                continue;
            if (gridX == this->getShipPositionX() && gridY == this->getShipPositionY())
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
            else if (grid[gridY][gridX].getType() == "0" && oneOfFourNeighbour(gridX, gridY, this->getShipPositionX(), this->getShipPositionY()))
            { // if it's land && one of four neighbour
                temp.x = gridX;
                temp.y = gridY;
                availableMove.push_back(temp);
            }
        }
    }
}

void Battleship::move(Grid **grid)
{
    int shipPositionY = this->getShipPositionY();
    int shipPositionX = this->getShipPositionX();
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
    this->setShipPositionX(availableMove[index].x);
    this->setShipPositionY(availableMove[index].y);
    std::cout << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
    OutputFile << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
}
void Battleship::shoot(Grid **grid)
{
    srand(chrono::system_clock::now().time_since_epoch().count());
    int shootx, shooty;
    infiniteLoopDetector = 0;
    do
    {
        if (infiniteLoopDetector > 10000)
        { // if loop 10000 times still cant find a place to shoot
            cout << "No Place to shoot" << endl;
            OutputFile << "No Place to shoot" << endl;
            break;
        }
        shootx = rand() % 6;
        shooty = rand() % 6;
        infiniteLoopDetector++;
    } while ((shootx + shooty > 5) || (shootx == 0 && shooty == 0) || (this->getShipPositionX() + shootx) >= Grid::getwidth() ||
             (this->getShipPositionY() + shooty) >= Grid::getHeight() ||
             friendlyShip(grid, shootx, shooty));
    if (infiniteLoopDetector <= 10000)
    {
        int shootLocationX = this->getShipPositionX() + shootx;
        int shootLocationY = this->getShipPositionY() + shooty;
        cout << this->getDisplay() << " Ship shoot at Y:" << shootLocationY << " X:" << shootLocationX;
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

            this->totalKillIncrement();
            // to be do upgrade, queue
            std::cout << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;
            OutputFile << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;
            this->getKilledShips()->enqueue(grid[shootLocationY][shootLocationX].getship());
            // set back to the land type after ship leave
            grid[shootLocationY][shootLocationX].setTaken(false);
            grid[shootLocationY][shootLocationX].setVal(grid[shootLocationY][shootLocationX].getType());
            grid[shootLocationY][shootLocationX].setship(nullptr);
            //-------------------------------
        }
    }
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
void Battleship::action(Grid **grid)
{
    cout << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
         << this->getDisplay() << ": look from Y:" << this->getShipPositionY()
         << " X:" << this->getShipPositionX() << endl;
    OutputFile << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
               << this->getDisplay() << ": look from Y:" << this->getShipPositionY()
               << " X:" << this->getShipPositionX() << endl;
    look(grid);
    move(grid);
    availableMove.clear();
    // generate random shoot x and y; shoot (shipPositionX + x, shipPositionY + y)
    shoot(grid);
    shoot(grid);
}
//----------------------------------------------Cruiser----------------------------------------------------------------//
void Cruiser::look(Grid **grid)
{
    position temp;
    for (int gridY = this->getShipPositionY() - 1; gridY <= this->getShipPositionY() + 1; gridY++)
    { // get the grid of nine-square area centered on (x,y)
        if (gridY < 0 || gridY >= Grid::getHeight())
            continue; // if outside of grid
        for (int gridX = this->getShipPositionX() - 1; gridX <= this->getShipPositionX() + 1; gridX++)
        {
            if (gridX < 0 || gridX >= Grid::getwidth())
                continue;
            if (gridX == this->getShipPositionX() && gridY == this->getShipPositionY())
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
            else if (grid[gridY][gridX].getType() == "0" && oneOfFourNeighbour(gridX, gridY, this->getShipPositionX(), this->getShipPositionY()))
            { // if it's land && one of four neighbour
                temp.x = gridX;
                temp.y = gridY;
                availableMove.push_back(temp);
            }
        }
    }
}

void Cruiser::move(Grid **grid)
{
    int shipPositionY = this->getShipPositionY();
    int shipPositionX = this->getShipPositionX();
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

void Cruiser::ram(Grid **grid)
{
    position temp;
    for (int gridY = this->getShipPositionY() - 1; gridY <= this->getShipPositionY() + 1; gridY++)
    { // get the grid of nine-square area centered on (x,y)
        if (gridY < 0 || gridY >= Grid::getHeight())
            continue; // if outside of grid
        for (int gridX = this->getShipPositionX() - 1; gridX <= this->getShipPositionX() + 1; gridX++)
        {
            if (gridX < 0 || gridX >= Grid::getwidth())
                continue;
            if (gridX == this->getShipPositionX() && gridY == this->getShipPositionY())
                continue; // ignore self;
            else if (grid[gridY][gridX].getship())
            { // if there's ship at the position
                if (grid[gridY][gridX].getship()->getTeamName() != this->getTeamName() && grid[gridY][gridX].getType() == "0"
                 && oneOfFourNeighbour(gridX, gridY, this->getShipPositionX(), this->getShipPositionY()))
                {
                    temp.x = gridX;
                    temp.y = gridY;
                    ramPosition.push_back(temp);
                }
            }
        }
    }
    if (ramPosition.get_size() > 0)
    {
        int index = rand() % ramPosition.get_size();
        // set back to the land type after ship leave
        grid[this->getShipPositionY()][this->getShipPositionX()].setVal(grid[this->getShipPositionY()][this->getShipPositionX()].getType());
        grid[this->getShipPositionY()][this->getShipPositionX()].setTaken(false);
        grid[this->getShipPositionY()][this->getShipPositionX()].setship(nullptr);
        
        std::cout << this->getDisplay() << " Ship move to Y:" << ramPosition[index].y << " X:" << ramPosition[index].x ;
        OutputFile << this->getDisplay() << " Ship move to Y:" << ramPosition[index].y << " X:" << ramPosition[index].x ;

        std::cout << " which destroyed " << grid[ramPosition[index].y][ramPosition[index].x].getship()->getDisplay() << std::endl;
        OutputFile << " which destroyed " << grid[ramPosition[index].y][ramPosition[index].x].getship()->getDisplay() << std::endl;

        this->getKilledShips()->enqueue(grid[ramPosition[index].y][ramPosition[index].x].getship());

        //---------------------
        grid[ramPosition[index].y][ramPosition[index].x].setVal(this->getDisplay());
        grid[ramPosition[index].y][ramPosition[index].x].setTaken(true);
        grid[ramPosition[index].y][ramPosition[index].x].setship(this);
        this->setShipPositionX(ramPosition[index].x);
        this->setShipPositionY(ramPosition[index].y);
        this->totalKillIncrement();

        std::cout << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;
        OutputFile << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;

        ramPosition.clear();
    }
    else {
        std::cout << "Ship have nowhere to ram!" << std::endl;
        OutputFile << "Ship have nowhere to ram!" << std::endl;
        move(grid);
        return; //exit the function when no target to ram
    }
}

void Cruiser::action(Grid **grid)
{
    cout << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
         << this->getDisplay() << ": look from Y:" << this->getShipPositionY()
         << " X:" << this->getShipPositionX() << endl;
    OutputFile << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
               << this->getDisplay() << ": look from Y:" << this->getShipPositionY()
               << " X:" << this->getShipPositionX() << endl;
    
    look(grid);
    ram(grid);
    availableMove.clear();
}

Ship::~Ship() {
    delete killedShip;
}