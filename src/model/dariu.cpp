#include <cmath>
#include "dariu.hpp"
#include "iostream"

Dariu::Dariu()
{
    dariu_tex.loadFromFile("./asset/dariu.png");
    dariu_spr.setTexture(dariu_tex);
    pos = sf::Vector2f(400.f, 400.f);
    speed = sf::Vector2f(0.f, 0.f);
    velocity = sf::Vector2f(0.f, 0.f);
    ground_y = 680;
    gravity = 0.9;
    lift = -20;
}
void Dariu::update()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->up();
    }

    velocity.y += gravity;
    pos.y += velocity.y;
    if (pos.y > ground_y)
    {
        pos.y = ground_y;
        velocity.y = 0;
    }

    // Right left

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x += 3;
        velocity.x = std::min(5.f, velocity.x);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x -= 3;
        velocity.x = std::max(-5.f, velocity.x);
    }
    else
    {
        if (velocity.x > 0.f)
        {
            velocity.x -= 0.2f;
            velocity.x = std::max(0.f, velocity.x);
        }
        else if (velocity.x < 0.f)
        {
            velocity.x += 0.2f;
            velocity.x = std::min(0.f, velocity.x);
        }
    }

    pos.x += velocity.x;

    dariu_spr.setPosition(pos);
}
void Dariu::draw(sf::RenderWindow *w)
{
    w->draw(dariu_spr);
}
bool Dariu::onFloor()
{
    return (pos.y == ground_y);
}

void Dariu::up()
{
    if (this->onFloor())
        velocity.y += lift;
}