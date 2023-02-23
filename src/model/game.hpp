#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <experimental/random>
#include <iostream>

#include "dariu.hpp"

class Game
{
public:
    Game();
    sf::RenderWindow window;

    sf::Music music;

    sf::Texture hammer;
    sf::Sprite ham;

    bool gameover;
    bool paused;

    Dariu dariu;

    void play();
    void pause();
    void game_over();
    void loop_events();
    void run();
};
#endif
