#include "../header/shiptype.h"
#include "../header/grid.h"
#include "../header/queue.h"
#include <chrono>

Ship::Ship() : life(3), totalKilled(0), killedShip(new queue), inBattlefield(true), upgradeFlag(false) {}
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
void Ship::setLife(int upgradedShipLife)
{
    life = upgradedShipLife;
}
int Ship::getLife() const
{
    return life;
}
void Ship::totalKillIncrement()
{
    totalKilled++;
}
void Ship::resetKillCount() { totalKilled = 0; }
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
queue *Ship::getKilledShips()
{
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
void Ship::setInBattlefield(bool b)
{
    inBattlefield = b;
}
bool Ship::getInBattlefield() const
{
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
//----------------------------------------------Battleship----------------------------------------------------------------//
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
            return;
        }
        shootx = rand() % 6;
        shooty = rand() % 6;
        infiniteLoopDetector++;
    } while ((shootx + shooty > 5) || (shootx == 0 && shooty == 0) || (this->getShipPositionX() + shootx) >= Grid::getwidth() ||
             (this->getShipPositionY() + shooty) >= Grid::getHeight() ||
             friendlyShip(grid, shootx, shooty));
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
    if (this->getTotalKill() == 4)
    {
        this->setUpgradeFlag(1);
        this->resetKillCount();
    }
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
            if (grid[gridY][gridX].getship() && grid[gridY][gridX].getship()->getTeamName() != this->getTeamName() && grid[gridY][gridX].getType() == "0" && oneOfFourNeighbour(gridX, gridY, this->getShipPositionX(), this->getShipPositionY()))
            {
                temp.x = gridX;
                temp.y = gridY;
                ramPosition.push_back(temp);
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
    this->setShipPositionX(availableMove[index].x);
    this->setShipPositionY(availableMove[index].y);
    std::cout << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
    OutputFile << this->getDisplay() << " Ship move to Y:" << availableMove[index].y << " X:" << availableMove[index].x << std::endl;
}

void Cruiser::ram(Grid **grid)
{
    if (ramPosition.get_size() > 0)
    {
        int index = rand() % ramPosition.get_size();
        // set back to the land type after ship leave
        grid[this->getShipPositionY()][this->getShipPositionX()].setVal(grid[this->getShipPositionY()][this->getShipPositionX()].getType());
        grid[this->getShipPositionY()][this->getShipPositionX()].setTaken(false);
        grid[this->getShipPositionY()][this->getShipPositionX()].setship(nullptr);

        std::cout << this->getDisplay() << " Ship move to Y:" << ramPosition[index].y << " X:" << ramPosition[index].x;
        OutputFile << this->getDisplay() << " Ship move to Y:" << ramPosition[index].y << " X:" << ramPosition[index].x;

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
    else
    {
        std::cout << "Ship have nowhere to ram!" << std::endl;
        OutputFile << "Ship have nowhere to ram!" << std::endl;
        move(grid);
    }
}

void Cruiser::action(Grid **grid)
{
    srand(chrono::system_clock::now().time_since_epoch().count());
    cout << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
         << this->getDisplay() << ": look from Y:" << this->getShipPositionY()
         << " X:" << this->getShipPositionX() << endl;
    OutputFile << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
               << this->getDisplay() << ": look from Y:" << this->getShipPositionY()
               << " X:" << this->getShipPositionX() << endl;

    look(grid);
    ram(grid);
    availableMove.clear();
    if (this->getTotalKill() == 3)
    {
        this->setUpgradeFlag(1);
        this->resetKillCount();
    }
}

//----------------------------------------------Destroyer----------------------------------------------------------------//
void Destroyer::look(Grid **grid)
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
            if (grid[gridY][gridX].getship() && grid[gridY][gridX].getship()->getTeamName() != this->getTeamName() && grid[gridY][gridX].getType() == "0" && oneOfFourNeighbour(gridX, gridY, this->getShipPositionX(), this->getShipPositionY()))
            {
                temp.x = gridX;
                temp.y = gridY;
                ramPosition.push_back(temp);
            }
        }
    }
}

void Destroyer::move(Grid **grid)
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

void Destroyer::shoot(Grid **grid)
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
            return;
        }
        shootx = rand() % 6;
        shooty = rand() % 6;
        infiniteLoopDetector++;
    } while ((shootx + shooty > 5) || (shootx == 0 && shooty == 0) || (this->getShipPositionX() + shootx) >= Grid::getwidth() ||
             (this->getShipPositionY() + shooty) >= Grid::getHeight() ||
             friendlyShip(grid, shootx, shooty));
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

void Destroyer::ram(Grid **grid)
{
    if (ramPosition.get_size() > 0)
    {
        int index = rand() % ramPosition.get_size();
        // set back to the land type after ship leave
        grid[this->getShipPositionY()][this->getShipPositionX()].setVal(grid[this->getShipPositionY()][this->getShipPositionX()].getType());
        grid[this->getShipPositionY()][this->getShipPositionX()].setTaken(false);
        grid[this->getShipPositionY()][this->getShipPositionX()].setship(nullptr);

        std::cout << this->getDisplay() << " Ship move to Y:" << ramPosition[index].y << " X:" << ramPosition[index].x;
        OutputFile << this->getDisplay() << " Ship move to Y:" << ramPosition[index].y << " X:" << ramPosition[index].x;

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
    else
    {
        std::cout << "Ship have nowhere to ram!" << std::endl;
        OutputFile << "Ship have nowhere to ram!" << std::endl;
        move(grid);
    }
}

void Destroyer::action(Grid **grid)
{
    srand(chrono::system_clock::now().time_since_epoch().count());
    cout << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
         << this->getDisplay() << ": look from Y:" << this->getShipPositionY()
         << " X:" << this->getShipPositionX() << endl;
    OutputFile << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
               << this->getDisplay() << ": look from Y:" << this->getShipPositionY()
               << " X:" << this->getShipPositionX() << endl;

    look(grid);
    ram(grid);
    availableMove.clear();
    shoot(grid);
    shoot(grid);
    if (this->getTotalKill() == 3)
    {
        this->setUpgradeFlag(1);
        this->resetKillCount();
    }
}

//----------------------------------------------Frigate----------------------------------------------------------------//
void Frigate::shoot(Grid **grid)
{
    int shootPositionX;
    int shootPositionY;
    // 4, because there's four direction
    // and check if all 4 direction is invalid then
    // output no place to shoot
    for (int i = 0; i <= 4; i++)
    {
        if (shootDirection == RIGHT)
        {
            shootPositionY = this->getShipPositionY();
            shootPositionX = this->getShipPositionX() + 1;

            if (shootPositionX >= Grid::getwidth() || (grid[shootPositionY][shootPositionX].getship() && (grid[shootPositionY][shootPositionX].getship()->getTeamName() == this->getTeamName())))
            {
                cout << "Switching shooting directions from right to down since it is out of range/friendly ship." << endl;
                OutputFile << "Switching shooting directions from right to down since it is out of range/friendly ship." << endl;
                shootDirection = DOWN;
                continue;
            }

            cout << this->getDisplay() << " Ship shoot right at Y:" << shootPositionY << " X:" << shootPositionX;
            OutputFile << this->getDisplay() << " Ship shoot right at Y:" << shootPositionY << " X:" << shootPositionX;
            shootDirection = DOWN;
        }
        else if (shootDirection == DOWN)
        {
            shootPositionY = this->getShipPositionY() + 1;
            shootPositionX = this->getShipPositionX();

            if (shootPositionY >= Grid::getHeight() || (grid[shootPositionY][shootPositionX].getship() && (grid[shootPositionY][shootPositionX].getship()->getTeamName() == this->getTeamName())))
            {
                cout << "Switching shooting directions from down to left since it is out of range/friendly ship." << endl;
                OutputFile << "Switching shooting directions from down to left since it is out of range/friendly ship." << endl;
                shootDirection = LEFT;
                continue;
            }

            cout << this->getDisplay() << " Ship shoot down at Y:" << shootPositionY << " X:" << shootPositionX;
            OutputFile << this->getDisplay() << " Ship shoot down at Y:" << shootPositionY << " X:" << shootPositionX;
            shootDirection = LEFT;
        }
        else if (shootDirection == LEFT)
        {
            shootPositionY = this->getShipPositionY();
            shootPositionX = this->getShipPositionX() - 1;

            if (shootPositionX < 0 || (grid[shootPositionY][shootPositionX].getship() && (grid[shootPositionY][shootPositionX].getship()->getTeamName() == this->getTeamName())))
            {
                cout << "Switching shooting directions from left to up since it is out of range/friendly ship." << endl;
                OutputFile << "Switching shooting directions from left to up since it is out of range/friendly ship." << endl;
                shootDirection = UP;
                continue;
            }

            cout << this->getDisplay() << " Ship shoot left at Y:" << shootPositionY << " X:" << shootPositionX;
            OutputFile << this->getDisplay() << " Ship shoot left at Y:" << shootPositionY << " X:" << shootPositionX;
            shootDirection = UP;
        }
        else //initialise or shootdirection == UP
        {
            shootPositionY = this->getShipPositionY() - 1;
            shootPositionX = this->getShipPositionX();
            if (shootPositionY < 0 || (grid[shootPositionY][shootPositionX].getship() && (grid[shootPositionY][shootPositionX].getship()->getTeamName() == this->getTeamName())))
            {
                cout << "Switching shooting directions from up to right since it is out of range/friendly ship." << endl;
                OutputFile << "Switching shooting directions from up to right since it is out of range/friendly ship." << endl;
                shootDirection = RIGHT;
                continue;
            }

            cout << this->getDisplay() << " Ship shoot up at Y:" << shootPositionY << " X:" << shootPositionX;
            OutputFile << this->getDisplay() << " Ship shoot up at Y:" << shootPositionY << " X:" << shootPositionX;
            shootDirection = RIGHT;
        }
        if (i == 4)
        {
            cout << "Ship have nowhere to shoot!" << endl;
            OutputFile << "Ship have nowhere to shoot!" << endl;
            return;
        }
        break;
    }
    if (grid[shootPositionY][shootPositionX].getship() == nullptr)
    {
        std::cout << " which has no ship." << std::endl;
        OutputFile << " which has no ship." << std::endl;
    }
    else
    {
        std::cout << " which destroyed " << grid[shootPositionY][shootPositionX].getship()->getDisplay() << std::endl;
        OutputFile << " which destroyed " << grid[shootPositionY][shootPositionX].getship()->getDisplay() << std::endl;

        this->totalKillIncrement();
        std::cout << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;
        OutputFile << this->getDisplay() << " Total Kill:" << this->getTotalKill() << std::endl;
        this->getKilledShips()->enqueue(grid[shootPositionY][shootPositionX].getship());
        // set back to the land type after ship leave
        grid[shootPositionY][shootPositionX].setTaken(false);
        grid[shootPositionY][shootPositionX].setVal(grid[shootPositionY][shootPositionX].getType());
        grid[shootPositionY][shootPositionX].setship(nullptr);
        //-------------------------------
    }
}

void Frigate::action(Grid **grid)
{
    cout << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
         << this->getDisplay() << ": From Y:" << this->getShipPositionY()
         << " X:" << this->getShipPositionX() << endl;
    OutputFile << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
               << this->getDisplay() << ": From Y:" << this->getShipPositionY()
               << " X:" << this->getShipPositionX() << endl;

    shoot(grid);
}

//----------------------------------------------Corvette----------------------------------------------------------------//
void Corvette::shoot(Grid** grid) {
    srand(chrono::system_clock::now().time_since_epoch().count());
    int shootx, shooty;
    infiniteLoopDetector = 0;
    do
    {
        if (infiniteLoopDetector > 10000)
        { // if loop 10000 times still cant find a place to shoot
            cout << "No Place to shoot" << endl;
            OutputFile << "No Place to shoot" << endl;
            return;
        }
        shootx = rand() % 3;
        shooty = rand() % 3;
        if(shootx == 2) shootx = -1;
        if(shooty == 2) shooty = -1;
        infiniteLoopDetector++;
        cout << this->getShipPositionY() + shooty << ' ' <<  this->getShipPositionX() + shootx;
    } while ((shootx == 0 && shooty == 0) || (this->getShipPositionX() + shootx) >= Grid::getwidth() ||
             (this->getShipPositionY() + shooty) >= Grid::getHeight() ||
             (this->getShipPositionY() + shooty) < 0 || (this->getShipPositionX() + shootx) < 0 || friendlyShip(grid, shootx, shooty));
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

void Corvette::action(Grid** grid) {
    cout << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
         << this->getDisplay() << ": From Y:" << this->getShipPositionY()
         << " X:" << this->getShipPositionX() << endl;
    OutputFile << this->getDisplay() << " turn. Ship Type: " << this->getType() << endl
               << this->getDisplay() << ": From Y:" << this->getShipPositionY()
               << " X:" << this->getShipPositionX() << endl;

    shoot(grid);
}
Ship::~Ship()
{
    delete killedShip;
}