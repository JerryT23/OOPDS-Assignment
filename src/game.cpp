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

Game::Game() : teams(nullptr) {}
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
    int shipI = 0;
    Node* shipPtr = teams[teamI].getLinkedListHead(); //get first team head
    for(int i = 0; i < iterations; i++) {//iteration 
        if(!shipPtr) { //move to next team after all ships done
            teamI++;
            shipI = 0;
            if(teamI == teamShipTotal.get_size()) //if teamI out of range reset back to zero
                teamI = 0;
            shipPtr = teams[teamI].getLinkedListHead();
        }
        if(shipPtr->value->getLife() != 0){
            shipPtr->value->action(grid); //action
            printGrid();
        }
        shipPtr = shipPtr->next;
        shipI++;
    }
    
    //--------------------------------- testing
    // cout << endl;
    // shipPtr->value->action();
    // printGrid();
    //----------------------------------
}