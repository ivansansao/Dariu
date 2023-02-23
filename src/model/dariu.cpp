#include "dariu.hpp"
#include "iostream"

Dariu::Dariu()
{
    dariu_tex.loadFromFile("./asset/dariu.png");
    dariu_spr.setTexture(dariu_tex);
    pos = sf::Vector2f(400.f, 400.f);
}
void Dariu::update()
{
    float const speed = 4.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        pos.x += speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        pos.x -= speed;
    }

    dariu_spr.setPosition(pos);
}
void Dariu::draw(sf::RenderWindow *w)
{
    w->draw(dariu_spr);
}
