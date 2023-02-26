#include <SFML/Graphics.hpp>
#include <iostream>

#include "model/game.hpp"

using namespace std;

int main() {
    cout << (int)12.0 << "\n";
    cout << (int)12.1 << "\n";
    cout << (int)12.5 << "\n";
    cout << (int)12.9 << "\n";
    cout << (int)12.9999999999999999999999999 << "\n";

    Game *game = new Game();
    game->run();
    delete game;
    game = nullptr;

    return EXIT_SUCCESS;
}