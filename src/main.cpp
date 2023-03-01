#include <SFML/Graphics.hpp>
#include <iostream>

#include "model/game.hpp"

using namespace std;

int main() {
    Game *game = new Game();
    game->run();
    delete game;
    game = nullptr;

    return EXIT_SUCCESS;
}