#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include <fstream>

#include "animation.hpp"

class Tilemap {
   public:
    Tilemap();
    const float height_floor = 23.f;
    static const int W = 115;
    static const int H = 23;
    float i_banana = 0;
    const int q_banana = 17;
    float i_trophy = 0;
    const int q_trophy = 8;

    Animation ban(int q_frame, float step, std::string file);

    sf::RenderWindow window;
    sf::Texture terrain_tex;
    sf::Texture banana_tex;
    sf::Texture trophy_tex;
    sf::Texture background_tex;
    sf::Sprite ground;
    sf::Sprite ground_ora;
    sf::Sprite ground_door_opened;
    sf::Sprite ground_door_closed;
    sf::Sprite coin;
    sf::Sprite banana;
    sf::Sprite trophy;
    sf::Sprite background;
    sf::RectangleShape block;

    sf::Texture fire_tex;
    sf::Sprite fire;
    float i_fire = 0;
    const int q_fire = 4;

    static std::string map[H];
    static std::string enimies[H];

    void update();
    void draw(sf::RenderWindow *w);
    void load_from_file(int phase);
};
#endif
