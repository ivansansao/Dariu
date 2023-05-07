#pragma once

#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include <fstream>

#include "animation.hpp"
#include "plataform.hpp"

struct point {
    int i;
    int j;
    char l;
    bool found = false;
};

class Tilemap {
   public:
    Tilemap();
    const float height_floor = 23.f;
    int W = 0;
    static const int H = 23;

    bool door_opened = false;

    bool isPortal(int i, int j);

    int getPortalNumber(int i, int j);

    point getMapOppositPortal(int i, int j);

    Animation jetpack;
    Animation banana;
    Animation portalP;
    Animation portalQ;
    Animation trophy;

    sf::RenderWindow window;
    sf::Texture terrain_tex;
    sf::Texture terrain2_tex;
    sf::Texture door_tex;
    sf::Texture background_tex;
    sf::Sprite ground;
    sf::Sprite ground_ora;
    sf::Sprite ground_door_opened;
    sf::Sprite ground_door_closed;
    sf::Sprite coin;
    sf::Sprite background;

    sf::Sprite ground_left;
    sf::Sprite ground_mid;
    sf::Sprite ground_right;
    sf::Sprite ground_left2;
    sf::Sprite ground_mid2;
    sf::Sprite ground_right2;

    sf::Texture start_tex;
    sf::Sprite start;

    sf::Texture fire_tex;
    sf::Sprite fire;
    float i_fire = 0;
    const int q_fire = 4;

    static std::string map[H];
    std::vector<Plataform *> plataforms;

    void update();
    void draw(sf::RenderWindow *w);
    void load_from_file(int phase);
    void load_plataforms();
    void replaceAll(char a, char b);
    void clear();
};
#endif
