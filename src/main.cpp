#include "model/game.hpp"
#include <iostream>

int main()
{
    Game *game = new Game();
    game->run();
    delete game;
    game = nullptr;

    return EXIT_SUCCESS;
}