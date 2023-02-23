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

    sf::RenderWindow window;
    sf::Texture terrain_tex;
    sf::Texture bananas_tex;
    sf::Sprite ground;
    sf::Sprite coin;
    sf::Sprite banana;
    sf::String tilemap;
    sf::RectangleShape block;

    void update();
    void draw(sf::RenderWindow *w);
};
#endif
