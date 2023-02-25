#include "dariu.hpp"

#include <cmath>

#include "iostream"
#include "tilemap.hpp"
#include "tools.hpp"

using namespace std;

Dariu::Dariu() {
    dariu_tex_fall.loadFromFile("./asset/Free/Main Characters/Virtual Guy/Fall (32x32).png");
    dariu_tex_idle.loadFromFile("./asset/Free/Main Characters/Virtual Guy/Idle (32x32).png");
    dariu_tex.loadFromFile("./asset/Free/Main Characters/Virtual Guy/Run (32x32).png");
    dariu_spr.setTexture(dariu_tex_fall);
    pos = sf::FloatRect(640.f, 64.f, 32.f, 32.f);
    velocity = sf::Vector2f(0.f, 0.f);
    direction_x = 1;
    i_idle_sprite = 1;
    ground_y = 736 - (32 + 32);
    on_ground = false;
    gravity = 0.9;
    lift = -17;

    font_vibes.loadFromFile("./asset/fonts/RobotoFlex-Regular.ttf");
    deb.setFont(font_vibes);
    deb.setCharacterSize(20);
    deb.setFillColor(sf::Color::White);
    deb.setPosition(sf::Vector2f(100, 100));
    deb.setString("");
}
void Dariu::update(Tilemap *tilemap) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->up();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        pos = sf::FloatRect(700.f, 100.f, 32.f, 32.f);
    }

    velocity.y += gravity;
    pos.top += velocity.y;
    if (pos.top > ground_y) {
        pos.top = ground_y;
        velocity.y = 0;
        on_ground = true;
    }

    // Right left

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x += 3;
        velocity.x = std::min(5.f, velocity.x);
        direction_x = 1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x -= 3;
        velocity.x = std::max(-5.f, velocity.x);
        direction_x = -1;
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

    pos.left += velocity.x;

    int i = pos.top / 32;
    int j = pos.left / 32;
    int i2 = (pos.top + pos.height) / 32;
    int j2 = (pos.left + pos.width) / 32;

    deb.setString("on_ground: " + to_string(on_ground) + " map[" + to_string(i) + "][" + to_string(j) + "] = ' " + tilemap->map[i][j] + " ' i2: " + to_string(i2) + " j2: " + to_string(j2));

    // collision_x(tilemap);
    collision_y(tilemap);

    dariu_spr.setPosition(pos.left, pos.top);

    deb.setPosition(sf::Vector2f(pos.left - 620, 100));
}
void Dariu::draw(sf::RenderWindow *w) {
    if (on_ground) {
        if (velocity.x == 0) {
            dariu_spr.setTexture(dariu_tex_idle);
            dariu_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)i_idle_sprite % 11, direction_x) * 32, 0, direction_x * 32, 32));
            i_idle_sprite += 0.2;
        } else {
            dariu_spr.setTexture(dariu_tex);
            dariu_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 12, direction_x) * 32, 0, direction_x * 32, 32));
        }
    }
    w->draw(dariu_spr);
    w->draw(deb);
}

void Dariu::up() {
    if (on_ground) {
        velocity.y += lift;
        on_ground = false;
    }
}
void Dariu::collision_x(Tilemap *tilemap) {
    // i = 384/12=12 < 384+32=416/32=13
    for (int i = pos.top / 32; i < (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j < (pos.left + pos.width) / 32; j++) {
            if (tilemap->map[i][j] == 'B') {
                // cout << "[" << i << "][" << j << "] pos.height = " << pos.height << " width: " << pos.width << "\n";
                // PARA o X
                if (velocity.x > 0) {
                    pos.left = j * 32 - pos.width;
                }
                if (velocity.x < 0) {
                    pos.left = j * 32 + 32;
                }
            }
        }
    }
}

void Dariu::collision_y(Tilemap *tilemap) {
    // i = 384/12=12 < 384+32=416/32=13
    for (int i = pos.top / 32; i < (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j < (pos.left + pos.width) / 32; j++) {
            if (tilemap->map[i][j] == 'B') {
                if (velocity.y > 0) {
                    pos.top = i * 32 - pos.height;
                    on_ground = true;
                }
                if (velocity.y < 0) {
                    pos.top = i * 32 + 32;
                }
                velocity.y = 0;
            }

            if (tilemap->map[i][j] == '0') {
                tilemap->map[i][j] = ' ';
            }
            if (tilemap->map[i][j] == 'T') {
                tilemap->map[i][j] = ' ';
            }
            if (tilemap->map[i][j] == 'X') {
                // fase_1 = true;
            }
        }
    }
}
