#pragma once

#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "animation.hpp"
#include "dariu.hpp"
#include "enimies.hpp"
#include "sounds.hpp"
#include "tilemap.hpp"

class Game {
   public:
    Game();

    sf::RenderWindow window;

    sf::View view;
    sf::Font font_roboto;
    sf::Font font_greatvibes;
    sf::Font font_irishgrooverregular;
    sf::Text text_gameover;

    bool gameover_loaded = false;
    int phase_current = 0;
    int phase_total = 0;

    sf::Text text_gamewin;
    sf::Text text_generic;

    enum pages {
        GAME_PLAY,
        GAME_OVER,
        GAME_WIN,
        GAME_PAUSE,
        GAME_RESUME,
        GAME_CLOSE,
        MENU_MAIN,
        MENU_VOLUME
    };
    int page = pages::MENU_MAIN;

    bool gamewin = false;
    bool gamewin_loaded = false;
    bool gamepause_loaded = false;
    bool game_loaded = false;
    bool menumain_loaded = false;

    Animation menuDariu;

    sf::Texture fireworks_tex;
    sf::Sprite fireworks_spr;
    float fireworks_i;
    float fireworks_j;

    bool paused = false;

    std::vector<Catraca *> catracas;
    std::vector<Sova *> sovas;
    std::vector<Cannon *> cannons;
    std::vector<Bulletc *> bulletcs;

    static const int menuopc_size = 5;
    static std::string menuopc[menuopc_size];
    const std::string version = "1.1";

    int menuopc_selected = 0;
    bool key_released = true;
    bool editing = false;
    int editing_framecount = 1;

    struct profile {
        int completed_phases = 0;
        int lifes = 0;
        int miliseconds_playtime = 0;
        uint32_t locker = 0;
        std::string password = "";
    } profile;

    Dariu dariu;
    Tilemap tilemap;
    Sounds sounds;
    void load_profile();
    void save_profile();
    bool is_valid_profile();
    void new_profile();
    void play();
    void pause();
    void resume();
    void reset();
    void close();
    void win();
    void over();
    void load();
    void loop_events();
    void run();
    bool is_fullscreen();
    void load_enimies();
    void check_collisions_mobiles();
    void check_collisions_enimies();
    void load_phase();
    void menu_main();
};
#endif
