#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include "../header/shiptype.h"
#include "../header/game.h"
#include "../header/node.h"
#include "../header/externalOutput.h"
using namespace std;

// 1. vectors, queues and linked lists is not allowed in this assignment
// 2. must employ the OOP concepts you have learnt such as
//    INHERITANCE, POLYMORPHISM, OPERATOR OVERLOADING, MOVE
//    SEMANTICS and any number of C++ object oriented features

Game::Game() : teams(nullptr),gameRunning(true) {}
void Game::printGrid() const {
for (int o = 0; o < height; o++)
{
    for (int i = 0; i < width; i++)
    {
        if(grid[o][i].getVal().length() == 1) { //if no ship in current coordinate
            cout << grid[o][i].getVal() << "  ";
            OutputFile << grid[o][i].getVal() << "  ";
        }
        else {
            cout << grid[o][i].getVal() << ' ';
            OutputFile << grid[o][i].getVal() << ' ';
        }
    }
    cout << endl;
    OutputFile << endl;
    }
    cout << "-----------------------------------------" <<endl;
    OutputFile << "-----------------------------------------" <<endl;
}
Node* Game::upgradeShip(Ship* oriShip) {
    Ship* upgradedShip;
    if(oriShip->getType() == "Battleship" || oriShip->getType() == "Cruiser" ) {
        upgradedShip = new Destroyer();
        upgradedShip->setType("Destroyer");
        cout << oriShip->getDisplay() <<" upgraded to Destroyer!" <<endl;
        OutputFile << oriShip->getDisplay() <<" upgraded to Destroyer!" <<endl;
    }
    else if(oriShip->getType() == "Destroyer") {
        upgradedShip = new Supership();
        upgradedShip->setType("Supership");
        cout << oriShip->getDisplay() <<" upgraded to Supership!" <<endl;
        OutputFile << oriShip->getDisplay() <<" upgraded to Supership!" <<endl;
    }
    upgradedShip->setDisplay(oriShip->getDisplay());
    upgradedShip->setTeamName(oriShip->getTeamName());
    upgradedShip->setTeamIndex(oriShip->getTeamIndex());
    upgradedShip->setLife(oriShip->getLife());
    upgradedShip->setShipPositionX(oriShip->getShipPositionX());
    upgradedShip->setShipPositionY(oriShip->getShipPositionY());
    grid[oriShip->getShipPositionY()][oriShip->getShipPositionX()].setship(upgradedShip);

    // Replace in the LinkedList
    Node* ret;
    ret = teams[oriShip->getTeamIndex()].getShip().replace(oriShip,upgradedShip);
    return ret;
}
void Game::init()
{
    string temp;
    ifstream configFile("game.txt");
    // iteration
    getline(configFile, temp);
    iterations = stoi(temp.substr(11));
    // width
    getline(configFile, temp);
    width = stoi(temp.substr(6));
    Grid::setwidth(stoi(temp.substr(6)));
    // height
    getline(configFile, temp);
    height = stoi(temp.substr(7));
    Grid::setHeight(stoi(temp.substr(7)));
    // get ship amount in a team then to array;
    {
        int sum, typeAmount;
        string line;
        ifstream tempFile("game.txt"); // to calculate each team ship amount
        getline(tempFile, line);
        getline(tempFile, line);
        getline(tempFile, line); // skip first three line

        getline(tempFile, line);
        while (line.substr(0, 4) == "Team")
        {
            sum = 0;
            typeAmount = stoi(line.substr(7));
            for (int i = 0; i < typeAmount; i++)
            {
                getline(tempFile, line);
                sum += stoi(line.substr(line.find(' ') + 3)); // type amount
            }
            teamShipTotal.push_back(sum);
            getline(tempFile, line);
        }
        tempFile.close();
    }
    // above explanation: if team A have 16 total ship & B have 5,
    //                    teamShipTotal = {16,5};
    //----------------------------------------------------------------

    // Team
    {
        int typeLeft;              // ships that are done/doing init
        int count;                 // trace number of the type
        string converter;          // convert char to string
        string teamName;           // to store team name for ship
        getline(configFile, temp); // first Team / space if no team
        teams = new Team[teamShipTotal.get_size()];
        for (int i = 0; i < teamShipTotal.get_size(); i++) // if two team run two time
        {   
            teamName = temp.substr(0,6);
            getline(configFile, temp); // first type of the team
            typeLeft = stoi(temp.substr(temp.find(' ') + 3));
            count = 1;
            converter = "";
            for (int y = 0; y < teamShipTotal[i]; y++) // if team A have 16 loop 16 times
            {
                converter = "";
                // check what shiptype and allocate new object
                if (temp.substr(0, 2) == "Ba")
                {
                    teams[i].pushbackShips(new Battleship);
                    teams[i].searchShip(y)->setType("Battleship");
                    teams[i].searchShip(y)->setDisplay(converter + temp[temp.find(' ') + 1] + static_cast<char>(count + 48));
                    teams[i].searchShip(y)->setTeamName(teamName);                
                }
                else if (temp.substr(0, 2) == "Cr")
                {
                    teams[i].pushbackShips(new Cruiser);
                    teams[i].searchShip(y)->setType("Cruiser");
                    teams[i].searchShip(y)->setDisplay(converter + temp[temp.find(' ') + 1] + static_cast<char>(count + 48));
                    teams[i].searchShip(y)->setTeamName(teamName);                
                }
                else if (temp.substr(0, 2) == "De")
                {
                    teams[i].pushbackShips(new Destroyer);
                    teams[i].searchShip(y)->setType("Destroyer");
                    teams[i].searchShip(y)->setDisplay(converter + temp[temp.find(' ') + 1] + static_cast<char>(count + 48));
                    teams[i].searchShip(y)->setTeamName(teamName);                
                }
                else if (temp.substr(0, 2) == "Fr")
                {
                    teams[i].pushbackShips(new Frigate);
                    teams[i].searchShip(y)->setType("Frigate");
                    teams[i].searchShip(y)->setDisplay(converter + temp[temp.find(' ') + 1] + static_cast<char>(count + 48));
                    teams[i].searchShip(y)->setTeamName(teamName);                
                }
                else if (temp.substr(0, 2) == "Co")
                {
                    teams[i].pushbackShips(new Corvette);
                    teams[i].searchShip(y)->setType("Corvette");
                    teams[i].searchShip(y)->setDisplay(converter + temp[temp.find(' ') + 1] + static_cast<char>(count + 48));
                    teams[i].searchShip(y)->setTeamName(teamName);                
                }
                else if (temp.substr(0, 2) == "Am")
                {
                    teams[i].pushbackShips(new Amphibious);
                    teams[i].searchShip(y)->setType("Amphibious");
                    teams[i].searchShip(y)->setDisplay(converter + temp[temp.find(' ') + 1] + static_cast<char>(count + 48));
                    teams[i].searchShip(y)->setTeamName(teamName);                
                }
                else if (temp.substr(0, 2) == "Su")
                {
                    teams[i].pushbackShips(new Supership);
                    teams[i].searchShip(y)->setType("Supership");
                    teams[i].searchShip(y)->setDisplay(converter + temp[temp.find(' ') + 1] + static_cast<char>(count + 48));
                    teams[i].searchShip(y)->setTeamName(teamName);                
                }
                count++;
                if (y + 1 == typeLeft)
                { // go to next line after allocated last obj of a type
                    getline(configFile, temp);
                    count = 1;
                    if (!temp.empty() && temp.substr(0, 4) != "Team")
                        typeLeft += stoi(temp.substr(temp.find(' ') + 3));
                }
            }
        }
    }

    // create 2d array game map (grid) using height and width
    grid = new Grid *[height];
    for (int i = 0; i < height; i++)
    {
        grid[i] = new Grid[width];
    }
    //-------------

    // init 2d array game map (grid)
    {
        char num; // num = 0/1 on map
        string converter = "";
        for (int o = 0; o < height; o++)
        {
            for (int i = 0; i < width; i++)
            {
                configFile >> num;
                grid[o][i].setVal(converter + num);
                grid[o][i].setTaken(false);  // no ship in current coordinate
            }
        }
    }
    //---------------------------

    configFile.close();
}

void Game::terminate()
{
    // delete teams
    delete[] teams;
    // delete grid
    for (int i = 0; i < height; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

void Game::reenterBattlefield() {
    srand(time(0));
    int randx;
    int randy;
    Ship* reenterShip = reenterShips.getFront()->value;
    do {
        randx = rand() % width;
        randy = rand() % height;
    }while(grid[randy][randx].getTaken()||(grid[randy][randx].getVal() == "1" && reenterShips.getFront()->value->getType() != "Amphibious"));
    //set new ship position
    reenterShip->setShipPositionX(randx);
    reenterShip->setShipPositionY(randy);
    grid[randy][randx].setVal(reenterShip->getDisplay());
    grid[randy][randx].setship(reenterShip);
    grid[randy][randx].setTaken(true);
    std::cout << reenterShip->getDisplay() <<" New location: Y->" << randy << " X->" << randx << std::endl;
    OutputFile << reenterShip->getDisplay() <<" New location: Y->" << randy << " X->" << randx << std::endl;
}
void Game::shipRandomGenerate() //generate random position for ship
{
    srand(time(0));
    int randx, randy;
    int infiniteLoopDetector = 0;
    for(int teamI = 0; teamI < teamShipTotal.get_size();teamI++) //loop "team" amount
    {
        for(int shipI = 0; shipI < teamShipTotal[teamI];shipI++) {
            do {
                if(infiniteLoopDetector > 1000) { //if loop 100 times still cant find a position
                    cout << "POSSIBLY NOT ENOUGH LAND FOR SHIPS TO INITIALIZE, ENDING PROGRAM.";
                    OutputFile << "POSSIBLY NOT ENOUGH LAND FOR SHIPS TO INITIALIZE, ENDING PROGRAM.";
                    throw runtime_error("NOT ENOUGH LAND FOR SHIPS TO INITIALIZE");
                }
                randx = rand() % width;
                randy = rand() % height;
                infiniteLoopDetector++;
            }
            while(grid[randy][randx].getTaken() || (grid[randy][randx].getVal() == "1" && teams[teamI].searchShip(shipI)->getType() != "Amphibious"));
            grid[randy][randx].setVal(teams[teamI].searchShip(shipI)->getDisplay());
            grid[randy][randx].setship(teams[teamI].searchShip(shipI));
            grid[randy][randx].setTaken(true);
            teams[teamI].searchShip(shipI)->setShipPositionX(randx);
            teams[teamI].searchShip(shipI)->setShipPositionY(randy);
            teams[teamI].searchShip(shipI)->setTeamIndex(teamI);
        }
    }
    cout << "Initialised ships position: " << endl;
    OutputFile << "Initialised ships position: " << endl;
    printGrid();
}

void Game::start() {
    int teamI = 0;
    Node* shipPtr = teams[teamI].getLinkedListHead(); //get first team head
    for(int i = 0; i < iterations && gameRunning; i++) {//iteration //tobedo: gamerunning
        while(!shipPtr) { //move to next team after all ships done/ team have no remaining ships
            teamI++;
            if(teamI == teamShipTotal.get_size()) //if teamI out of range reset back to zero
                teamI = 0;
            shipPtr = teams[teamI].getLinkedListHead();
        }
        if(shipPtr->value->getInBattlefield())
            shipPtr->value->action(grid); //action
        else {
            cout << shipPtr->value->getDisplay() << " turn. But the ship is not in the battlefield. Skipping...." << endl;
            OutputFile << shipPtr->value->getDisplay() << " turn. But the ship is not in the battlefield. Skipping...." << endl;
        }
        printGrid();
        //check if any killed ship need to enter queue to reenter battlefield
        {
            while(!shipPtr->value->getKilledShips()->empty()) {
                reenterShips.enqueue(shipPtr->value->getKilledShips()->getFront()->value);
                shipPtr->value->getKilledShips()->getFront()->value->setInBattlefield(false);
                shipPtr->value->getKilledShips()->dequeue();
            }
        }
        //check upgrade flag
        if(shipPtr->value->getUpgradeFlag()) {
            shipPtr = upgradeShip(shipPtr->value);
            shipPtr->value->setUpgradeFlag(0);
        }
        //reenter battlefield
        {
            int reenterCount = 0;
            while(!reenterShips.empty() && reenterCount < 2) {
                reenterShips.getFront()->value->lifeMinus1();
                if(reenterShips.getFront()->value->getLife() < 0) {
                    cout << reenterShips.getFront()->value->getDisplay() << " is removed from the battlefield. " << endl;
                    OutputFile << reenterShips.getFront()->value->getDisplay() << " is removed from the battlefield. " << endl;
                    teams[reenterShips.getFront()->value->getTeamIndex()].getShip().deleteNode(reenterShips.getFront()->value);
                    reenterShips.dequeue();
                } else {
                    cout << reenterShips.getFront()->value->getDisplay() << " Life remaining: " << reenterShips.getFront()->value->getLife() << endl;
                    OutputFile << reenterShips.getFront()->value->getDisplay() << " Life remaining: " << reenterShips.getFront()->value->getLife() << endl;
                    reenterBattlefield();
                    reenterShips.getFront()->value->setInBattlefield(true);
                    reenterCount++;
                    reenterShips.dequeue();
                }
            }
        }
        //check game condition
        {
            int teamRemaining = 0;
            for(int i = 0; i < teamShipTotal.get_size();i++) {
                if(teams[i].getLinkedListTail()) teamRemaining++;
            }
            if(teamRemaining==1) {
                cout << "Only One Team Remaining, ending the simulation." << endl;
                OutputFile << "Only One Team Remaining, ending the simulation." << endl;
                gameRunning = false;
            }
        }
        //-------------------------------
        shipPtr = shipPtr->next;
        if (i == iterations - 1) 
        {
            cout << "Iterations reached. Simulation END." << endl;
            OutputFile << "Iterations reached. Simulation END." << endl;
        }
    }
}