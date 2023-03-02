#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <experimental/random>
#include <iostream>
#include <vector>

#include "dariu.hpp"
#include "enimies.hpp"
#include "inimigo.hpp"
#include "tilemap.hpp"

class Game {
   public:
    Game();
    sf::RenderWindow window;

    sf::Music music;
    sf::View view;
    sf::Font font_roboto;
    sf::Font font_greatvibes;
    sf::Text text_gameover;

    sf::Music music_gameover;
    bool gameover = false;
    bool gameover_trigged = false;

    sf::Music music_gamewin;
    sf::Text text_gamewin;
    bool gamewin = false;
    bool gamewin_trigged = false;
    void game_win();

    bool paused = false;
    bool playing = false;

    std::vector<Inimigo> inimigos;
    std::vector<Catraca> catracas;
    std::vector<Catraca *> catas;

    Dariu dariu;
    Tilemap tilemap;

    void play();
    void pause();
    void game_over();
    void loop_events();
    void run();
    bool is_fullscreen();
};
#endif
