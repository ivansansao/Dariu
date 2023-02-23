#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>

class Tilemap {
   public:
    Tilemap();
    const float height_floor = 23.f;
    const int H = 23;
    const int W = 80;
    float i_banana = 0;
    const int q_banana = 17;
    float i_trophy = 0;
    const int q_trophy = 8;

    sf::RenderWindow window;
    sf::Texture terrain_tex;
    sf::Texture banana_tex;
    sf::Texture trophy_tex;
    sf::Texture background_tex;
    sf::Sprite ground;
    sf::Sprite coin;
    sf::Sprite banana;
    sf::Sprite trophy;
    sf::Sprite background;
    sf::RectangleShape block;
    sf::String tilemap;

    void update();
    void draw(sf::RenderWindow *w);
};
#endif