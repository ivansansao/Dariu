#ifndef DARIU_H
#define DARIU_H
#include <SFML/Graphics.hpp>

#include "tilemap.hpp"

class Dariu {
   public:
    Dariu();

    sf::RenderWindow window;

    sf::Texture dariu_tex_fall;
    sf::Texture dariu_tex_idle;
    sf::Texture dariu_tex;
    sf::Sprite dariu_spr;

    sf::FloatRect pos;
    sf::Vector2f velocity;
    int direction_x;
    float i_idle_sprite;
    float ground_y;
    float gravity;
    float lift;
    bool on_ground;

    sf::Font font_vibes;
    sf::Text deb;

    void update(Tilemap *tilemap);
    void draw(sf::RenderWindow *w);
    void up();
    bool onFloor();
    void collision_x(Tilemap *);
    void collision_y(Tilemap *);
};
#endif
