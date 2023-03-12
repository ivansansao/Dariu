#pragma once

#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "dariu.hpp"
#include "enimies.hpp"
#include "inimigo.hpp"
#include "sounds.hpp"
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
    int phase_current = 0;
    int phase_total = 0;

    sf::Music music_gamewin;
    sf::Text text_gamewin;
    bool gamewin = false;
    bool gamewin_loaded = false;
    void game_win();

    bool game_loaded = false;

    sf::Texture fireworks_tex;
    sf::Sprite fireworks_spr;
    float fireworks_i;
    float fireworks_j;

    bool paused = false;
    bool playing = false;

    std::vector<Catraca *> catracas;
    std::vector<Sova *> sovas;
    std::vector<Cannon *> cannons;
    std::vector<Bulletc *> bulletcs;

    Dariu dariu;
    Tilemap tilemap;
    Sounds sounds;

    void play();
    void pause();
    void game_over();
    void game_load();
    void loop_events();
    void run();
    bool is_fullscreen();
    void load_enimies();
    void check_collisions_mobiles();
    void check_collisions_enimies();
    void load_phase();
};
#endif
