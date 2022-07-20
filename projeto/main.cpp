#include <iostream>

#include "include/structs.h"
#include "include/json.h"
#include "include/xdot.h"
#include "include/game.h"



using namespace std;

int main()
{
    // Game file
    string caminho ="game.json";
    Game game=readFromFile(caminho);
    //motor(game);
    show_xDot(game);

    return 0;
}


//g++ -o main.exe main.cpp src/game.cpp src/json.cpp src/structs.cpp src/xdot.cpp