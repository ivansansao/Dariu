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
    sf::Vector2f speed;
    sf::Vector2f velocity;
    float ground_y;
    float gravity;
    float lift;

    void update();
    void draw(sf::RenderWindow *w);
    void up();
    bool onFloor();
};
#endif
