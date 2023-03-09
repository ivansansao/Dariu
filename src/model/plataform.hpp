#ifndef PLATAFORM_H
#define PLATAFORM_H

#include <SFML/Graphics.hpp>

class Plataform {
   public:
    Plataform();

    sf::Texture textura;
    sf::Sprite sprite;
    int direction_x;
    float i_idle_sprite;
    float vel_step;
    sf::Vector2f velocity;

    sf::FloatRect pos;
    void draw(sf::RenderWindow *w);
    void update();
};
#endif
