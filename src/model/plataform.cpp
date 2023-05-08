#include "plataform.hpp"

#include <cmath>

#include "iostream"
#include "tools.hpp"

using namespace std;

Plataform::Plataform() {
    textura.loadFromFile("./src/asset/Free/plataform.png");
    sprite.setTexture(textura);
    pos = sf::FloatRect(672.f, 672.f, 32.f, 32.f);
    vel_step = 0.9f;
    velocity = sf::Vector2f(vel_step, 0.f);
    direction_x = 1;
    i_idle_sprite = 1;
}
void Plataform::update() {
    sprite.setPosition(pos.left, pos.top);
    i_idle_sprite += 0.1;
    pos.left += velocity.x;
    pos.top += velocity.y;
}
void Plataform::draw(sf::RenderWindow *w) {
    sprite.setTextureRect(sf::IntRect(Tools::getStartSprite((int)i_idle_sprite % 6, direction_x) * 32, 0, direction_x * 32, 32));
    w->draw(this->sprite);
}
