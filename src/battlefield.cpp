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

Team* Game::teamsSizeInc(Team* teams, int& currentSize) {
    Team* temp = new Team[currentSize+1];
    for(int i = 0; i < currentSize; i++) {
        temp[i] = teams[i];
    }
    delete[] teams;
    currentSize += 1;
    return temp;
}

void Game::init()
{
    string temp;
    int amount, teamAmount = 1;
    ifstream configFile("game.txt");
    //iteration
    getline(configFile, temp);
    iterations = stoi(temp.substr(11));
    //width
    getline(configFile,temp);
    width =  stoi(temp.substr(6));
    //height
    getline(configFile,temp);
    height << stoi(temp.substr(7));
    //Team (assume at least one team)
    getline(configFile,temp);
    teams = new Team[teamAmount]; //first team
    teams[teamAmount-1].setTeamName(temp.substr(0,6)); //first team
    {
        int typeAmount; 
        do {
            amount = stoi(temp.substr(7));
            teams[teamAmount-1].setShips(amount); //set ships row for every shipType for each team
            for(int i = 0;i < amount; i++) { 
                //only allow team name with one char;
                //example Team A ok but Team AA not ok;
                getline(configFile,temp);

                if(temp.substr(0,2) == "Ba") {
                    typeAmount = stoi(temp.substr(13));
                    teams[teamAmount-1].setShipsCol(i,new Battleship[typeAmount]);
                } else if (temp.substr(0,2) == "Cr") {
                    typeAmount = stoi(temp.substr(10));
                    teams[teamAmount-1].setShipsCol(i,new Cruiser[typeAmount]);
                } else if (temp.substr(0,2) == "De") {
                    typeAmount = stoi(temp.substr(12));
                    teams[teamAmount-1].setShipsCol(i,new Destroyer[typeAmount]);
                } else if (temp.substr(0,2) == "Fr") {
                    typeAmount = stoi(temp.substr(10));
                    teams[teamAmount-1].setShipsCol(i,new Frigate[typeAmount]);
                } else if (temp.substr(0,2) == "Co") {
                    typeAmount = stoi(temp.substr(11));
                    teams[teamAmount-1].setShipsCol(i,new Corvette[typeAmount]);
                } else if (temp.substr(0,2) == "Am") {
                    typeAmount = stoi(temp.substr(13));
                    teams[teamAmount-1].setShipsCol(i,new Amphibious[typeAmount]);
                } else if (temp.substr(0,2) == "Su") {
                    typeAmount = stoi(temp.substr(12));
                    teams[teamAmount-1].setShipsCol(i,new Supership[typeAmount]);
                }
            } 
            getline(configFile,temp);
            } while(temp.substr(0,4) == "Team");
    }
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