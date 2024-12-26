#include <iostream>
#include <string>
#include <fstream>
#include "../header/shiptype.h"
#include "../header/battlefield.h"
using namespace std;

// 1. vectors, queues and linked lists is not allowed in this assignment
// 2. must employ the OOP concepts you have learnt such as
//    INHERITANCE, POLYMORPHISM, OPERATOR OVERLOADING, MOVE
//    SEMANTICS and any number of C++ object oriented features

Team *Game::teamsSizeInc(Team *teams, int &currentSize)
{
    Team *temp = new Team[currentSize + 1];
    for (int i = 0; i < currentSize; i++)
    {
        temp[i] = teams[i];
    }
    if (teams)
    {
        delete[] teams;
    }
    currentSize += 1;
    return temp;
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
    height << stoi(temp.substr(7));

    // get ship amount in a team then to array;
    Vector<int> teamShipTotal;
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
    //
    
    {
        // Team
        int typeLeft;
        getline(configFile, temp);
        teams = new Team[teamShipTotal.get_size()];
        for (int i = 0; i < teamShipTotal.get_size(); i++) //if two team run two time
        {
            teams[i].setShips(teamShipTotal[i]);
            getline(configFile, temp); // first type of the team
            typeLeft = stoi(temp.substr(temp.find(' ') + 3));
            for (int y = 0; y < teamShipTotal[i]; y++) // if team A have 16 loop 16 times
            { 
                if( y < typeLeft ) {
                    //check what shiptype and allocate new object
                    if(temp.substr(0,2) == "Ba") {
                        teams[i].setShipsCol(y,new Battleship);
                    } else if (temp.substr(0,2) == "Cr") {
                        teams[i].setShipsCol(y,new Cruiser);
                    } else if (temp.substr(0,2) == "De") {
                        teams[i].setShipsCol(y,new Destroyer);
                    } else if (temp.substr(0,2) == "Fr") {
                        teams[i].setShipsCol(y,new Frigate);
                    } else if (temp.substr(0,2) == "Co") {
                        teams[i].setShipsCol(y,new Corvette);
                    } else if (temp.substr(0,2) == "Am") {
                        teams[i].setShipsCol(y,new Amphibious);
                    } else if (temp.substr(0,2) == "Su") {
                        teams[i].setShipsCol(y,new Supership);
                    }
                } 
                if(y+1 == typeLeft) { //go to next line after allocated last obj of a type
                    getline(configFile, temp);
                    if(!temp.empty() && temp.substr(0,4) != "Team")
                        typeLeft += stoi(temp.substr(temp.find(' ') + 3));
                }
            }
        }
    }

    teams[1].getShip(1)->action();
    configFile.close();
}

void Game::terminate()
{
    delete[] teams;
}

void display_battlefield(int position_ship1, int position_ship2, int position_ship3, int position_ship4, int position_ship5, int position_ship6)
{
    // const int iterations = 100;

    // const int width = 10;
    // const int height = 10;

    // char battlefield[height][width];

    // char battleship = '*';
    // char cruiser = '$';
    // char destroyer = '#';
    // char frigate = '@';
    // char carvette = '&';
    // char amphibious = '~';

    // Initialize battlefield
    // for (int i = 0; i < height; i++)
    //     for (int j = 0; j < width; j++)
    //         battlefield[i][j] = '0';
}