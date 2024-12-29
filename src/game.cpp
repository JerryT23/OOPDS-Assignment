#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include "../header/shiptype.h"
#include "../header/game.h"
using namespace std;

// 1. vectors, queues and linked lists is not allowed in this assignment
// 2. must employ the OOP concepts you have learnt such as
//    INHERITANCE, POLYMORPHISM, OPERATOR OVERLOADING, MOVE
//    SEMANTICS and any number of C++ object oriented features

void Grid::setTaken(bool b) {
    taken = b;
}
bool Grid::getTaken() const {
    return taken;
}
void Grid::setVal(int value) {
    val = value;
}
int Grid::getVal() const {
    return val;
}

Game::Game() : teams(nullptr) {}

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
    // height
    getline(configFile, temp);
    height = stoi(temp.substr(7));

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
        int typeLeft;
        getline(configFile, temp); // first Team / space if no team
        teams = new Team[teamShipTotal.get_size()];
        for (int i = 0; i < teamShipTotal.get_size(); i++) // if two team run two time
        {
            teams[i].setShips(teamShipTotal[i]);
            getline(configFile, temp); // first type of the team
            typeLeft = stoi(temp.substr(temp.find(' ') + 3));
            for (int y = 0; y < teamShipTotal[i]; y++) // if team A have 16 loop 16 times
            {
                if (y < typeLeft)
                {
                    // check what shiptype and allocate new object
                    if (temp.substr(0, 2) == "Ba")
                    {
                        teams[i].setShipsCol(y, new Battleship);
                        teams[i].getShip(y)->setType("Battleship");
                        teams[i].setSymbol("Battleship", temp[temp.find(' ') + 1]);
                    }
                    else if (temp.substr(0, 2) == "Cr")
                    {
                        teams[i].setShipsCol(y, new Cruiser);
                        teams[i].getShip(y)->setType("Cruiser");
                        teams[i].setSymbol("Cruiser", temp[temp.find(' ') + 1]);
                    }
                    else if (temp.substr(0, 2) == "De")
                    {
                        teams[i].setShipsCol(y, new Destroyer);
                        teams[i].getShip(y)->setType("Destroyer");
                        teams[i].setSymbol("Destroyer", temp[temp.find(' ') + 1]);
                    }
                    else if (temp.substr(0, 2) == "Fr")
                    {
                        teams[i].setShipsCol(y, new Frigate);
                        teams[i].getShip(y)->setType("Frigate");
                        teams[i].setSymbol("Frigate", temp[temp.find(' ') + 1]);
                    }
                    else if (temp.substr(0, 2) == "Co")
                    {
                        teams[i].setShipsCol(y, new Corvette);
                        teams[i].getShip(y)->setType("Corvette");
                        teams[i].setSymbol("Corvette", temp[temp.find(' ') + 1]);
                    }
                    else if (temp.substr(0, 2) == "Am")
                    {
                        teams[i].setShipsCol(y, new Amphibious);
                        teams[i].getShip(y)->setType("Amphibious");
                        teams[i].setSymbol("Amphibious", temp[temp.find(' ') + 1]);
                    }
                    else if (temp.substr(0, 2) == "Su")
                    {
                        teams[i].setShipsCol(y, new Supership);
                        teams[i].getShip(y)->setType("Supership");
                        teams[i].setSymbol("Supership", temp[temp.find(' ') + 1]);
                    }
                }
                if (y + 1 == typeLeft)
                { // go to next line after allocated last obj of a type
                    getline(configFile, temp);
                    if (!temp.empty() && temp.substr(0, 4) != "Team")
                        typeLeft += stoi(temp.substr(temp.find(' ') + 3));
                }
            }
        }
    }
    // cout << teams->getSymbol(teams[0].getShip(2)->getType());
    // upper explanation: to get symbol of first team third ship symbol

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
        for (int o = 0; o < height; o++)
        {
            for(int i = 0; i < width; i++) {
                configFile >> num;
                grid[o][i].setVal(num - 48); //conv char to int
                grid[o][i].setTaken(false); //no ship in current coordinate
            }
        }
    }
    //---------------------------

    configFile.close();
}

void Game::terminate()
{
    //delete teams
    delete[] teams;
    //delete grid
    for (int i = 0; i < height; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

// void Game::shipRandomGenerate() //generate random position for ship
// {
//     srand(time(0));
//     int randx, randy;
//     for(int teamI = 0; teamI < teamShipTotal.get_size();teamI++) //loop "team" amount
//     {
//         for(int shipI = 0; shipI < teams[teamI].getShipAmount();shipI++) {
//             do {
//                 randx = rand() % width;
//                 randy = rand() % height;
//             }
//             while((grid[randy][randx] != 0 && grid[randy][randx] != 1) || (grid[randy][randx] == 1 && teams[teamI].getShip(shipI)->getType() != "Amphibious"));
//         }
//     } 
// }