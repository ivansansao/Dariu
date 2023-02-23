#include "dariu.hpp"
#include "iostream"

// Constructor of class
Dariu::Dariu()
{
    std::cout << "Inside dariu.cpp constructor\n";

    dariu_tex.loadFromFile("./asset/dariu.png");
    dariu_spr.setTexture(dariu_tex);
    pos = sf::Vector2f(400.f, 400.f);
}
void Dariu::update()
{
    pos.x += 0.5;
    dariu_spr.setPosition(pos);
}
void Dariu::draw(sf::RenderWindow *w)
{
    w->draw(dariu_spr);
}
