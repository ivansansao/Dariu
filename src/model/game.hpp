#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <experimental/random>
#include <iostream>

class Game
{
public:
    Game();
    sf::RenderWindow window;
    bool gameover;
    bool paused;

    void play();
    void game_over();
    void pause();
    void loop_events();
    void run();
};
#endif
