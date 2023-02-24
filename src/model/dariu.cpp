#include "dariu.hpp"

#include <cmath>

#include "iostream"
#include "tools.hpp"

Dariu::Dariu() {
    dariu_tex_idle.loadFromFile("./asset/Free/Main Characters/Virtual Guy/Idle (32x32).png");
    dariu_tex.loadFromFile("./asset/Free/Main Characters/Virtual Guy/Run (32x32).png");
    pos = sf::Vector2f(400.f, 400.f);
    velocity = sf::Vector2f(0.f, 0.f);
    direction = 1;
    i_idle_sprite = 1;
    ground_y = 736 - 32 - 32;
    gravity = 0.9;
    lift = -17;
}
void Dariu::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->up();
    }

    velocity.y += gravity;
    pos.y += velocity.y;
    if (pos.y > ground_y) {
        pos.y = ground_y;
        velocity.y = 0;
    }

    // Right left

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x += 3;
        velocity.x = std::min(5.f, velocity.x);
        direction = 1;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x -= 3;
        velocity.x = std::max(-5.f, velocity.x);
        direction = -1;
    } else {
        if (velocity.x > 0.f) {
            velocity.x -= 0.2f;
            velocity.x = std::max(0.f, velocity.x);
        } else if (velocity.x < 0.f) {
            velocity.x += 0.2f;
            velocity.x = std::min(0.f, velocity.x);
        }
        velocity.x = 0;
    }

    pos.x += velocity.x;

    dariu_spr.setPosition(pos);
}
void Dariu::draw(sf::RenderWindow *w) {
    if (onFloor()) {
        if (velocity.x == 0) {
            dariu_spr.setTexture(dariu_tex_idle);
            dariu_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)i_idle_sprite % 11, direction) * 32, 0, direction * 32, 32));
            i_idle_sprite += 0.2;
        } else {
            dariu_spr.setTexture(dariu_tex);
            dariu_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.x % 12, direction) * 32, 0, direction * 32, 32));
        }
    }
    w->draw(dariu_spr);
}
bool Dariu::onFloor() {
    return (pos.y == ground_y);
}

void Dariu::up() {
    if (this->onFloor())
        velocity.y += lift;
}