#include "model/dariu.hpp"
#include "model/game.hpp"
#include <iostream>

// using namespace std;

int main()
{
    Game *game = new Game();
    game->run();
    delete game;
    game = nullptr;

    // cout << "Working..";
    return EXIT_SUCCESS;
}