#include <iostream>
#include "./header/game.h"
#include "./header/vector.h"
#include "./header/externalOutput.h"
using namespace std;
ofstream OutputFile("output.txt");

int main(){
    Game game;
    game.init();
    game.shipRandomGenerate();
    game.start();
    game.terminate();
}