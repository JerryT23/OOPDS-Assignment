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
    teams = new Team[1]; //first team
    teams[0].setTeamName(temp.substr(0,6)); //first team
    //to do: every new team delete old teams[] and create new arry;
    //initialise every details of team;
    do {
        amount = stoi(temp.substr(7));
        for(int i = 0;i < amount; i++) { 
            //only allow team name with one char;
            //example Team A ok but Team AA not ok;
            getline(configFile,temp);
        }
        getline(configFile,temp);
    } while(temp.substr(0,4) == "Team");
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