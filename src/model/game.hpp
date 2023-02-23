#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <experimental/random>
#include <iostream>

#include "dariu.hpp"
#include "tilemap.hpp"

class Game {
   public:
    Game();
    sf::RenderWindow window;

    sf::Music music;
    sf::View view;

    bool gameover;
    bool paused;

    Dariu dariu;
    Tilemap tilemap;

    void play();
    void pause();
    void game_over();
    void loop_events();
    void run();
};
#endif
