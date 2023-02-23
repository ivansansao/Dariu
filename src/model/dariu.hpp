#ifndef DARIU_H
#define DARIU_H

#include <SFML/Graphics.hpp>

class Dariu
{
public:
    Dariu();

    sf::RenderWindow window;

    sf::Texture dariu_tex;
    sf::Sprite dariu_spr;

    sf::Vector2f pos;

    void update();
    void draw(sf::RenderWindow *w);
};
#endif
