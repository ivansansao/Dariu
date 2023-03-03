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
    bool gameover_loaded = false;
    bool phase_loaded = false;
    bool phase_number = 1;

    sf::Music music_gamewin;
    sf::Text text_gamewin;
    bool gamewin = false;
    bool gamewin_loaded = false;
    void game_win();

    bool paused = false;
    bool playing = false;

    std::vector<Catraca *> catracas;

    Dariu dariu;
    Tilemap tilemap;

    void play();
    void pause();
    void game_over();
    void loop_events();
    void run();
    bool is_fullscreen();
    void load_enimy_catracas();
    void check_collisions_enimies();
    void load_phase();
};
#endif
