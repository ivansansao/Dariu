#include <iostream>

#include "model/game.hpp"

int main() {
    Game *game = new Game();
    game->run();
    delete game;
    game = nullptr;

    return EXIT_SUCCESS;
}