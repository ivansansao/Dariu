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
    gravity = 1.0;
    lift = -17;

    font_vibes.loadFromFile("./asset/fonts/RobotoFlex-Regular.ttf");
    deb.setFont(font_vibes);
    deb.setCharacterSize(20);
    deb.setFillColor(sf::Color::White);
    deb.setPosition(sf::Vector2f(100, 100));
    deb.setString("");
}
void Dariu::up() {
    if (on_ground) {
        velocity.y += lift;
        on_ground = false;
    }
}
void Dariu::update(Tilemap *tilemap) {
    // ---- Y ----

    // cout << "E: " << (int)pos.top / 32 << "," << (int)pos.left / 32 << "\n";

    if (tilemap->map[(int)pos.top / 32][(int)pos.left / 32] == 'B') {
        cout << "Iniciou com B\n";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (on_ground) {
            velocity.y += lift;
        }
    }
    velocity.y += 1;
    pos.top += velocity.y;
    // cout << "pos.top: " << pos.top << " velocity.y: " << velocity.y << "\n";

    collision_y(tilemap);

    if (tilemap->map[((int)pos.top / 32)][(int)pos.left / 32] == 'B') {
        cerr << "******************* Erro local 1\n";
    }

    // ---- X ----

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pos.left += 3;
        direction_x = 1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pos.left -= 3;
        direction_x = -1;
    }

    collision_x(tilemap);  // There is a issue here!

    // ---- END ----

    if (tilemap->map[(int)pos.top / 32][(int)pos.left / 32] == 'B') {
        cout << "Ended com B\n";
    }

    dariu_spr.setPosition(pos.left, pos.top);

    // Just debug
    int i = pos.top / 32;
    int j = pos.left / 32;
    int i2 = (pos.top + pos.height) / 32;
    int j2 = (pos.left + pos.width) / 32;
    deb.setString("on_ground: " + to_string(on_ground) + " map[" + to_string(i) + "][" + to_string(j) + "] = ' " + tilemap->map[i][j] + " ' i2: " + to_string(i2) + " j2: " + to_string(j2) + " on_block: " + to_string(0));

    // cout << "S: " << (int)pos.top / 32 << "," << (int)pos.left / 32 << "\n";
}

void Dariu::collision_y(Tilemap *tilemap) {
    on_ground = false;
    // i = 384/12=12 < 384+32=416/32=13
    for (int i = pos.top / 32; i <= (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j <= (pos.left + pos.width) / 32; j++) {
            if (tilemap->map[i][j] == 'B') {
                if (velocity.y > 0) {
                    pos.top = i * 32 - pos.height;
                    on_ground = true;
                    // cout << "A\n";
                }
                if (velocity.y < 0) {
                    pos.top = i * 32 + 32;
                    cout << "Toin..\n";
                }
                velocity.y = 0;
            }
        }
    }
}
void Dariu::collision_x(Tilemap *tilemap) {
    // i = 384/12=12 < 384+32=416/32=13
    int i = pos.top / 32;
    int j = pos.left / 32;
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

void Dariu::collision_other(Tilemap *tilemap) {
    for (int i = pos.top / 32; i < (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j < (pos.left + pos.width) / 32; j++) {
            if (tilemap->map[i][j] == '0') {
                tilemap->map[i][j] = ' ';
            }
            if (tilemap->map[i][j] == 'T') {
                tilemap->map[i][j] = ' ';
            }
            if (tilemap->map[i][j] == 'X') {
            }
        }
    }
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

    deb.setPosition(sf::Vector2f(pos.left - 620, 100));
    w->draw(dariu_spr);
    w->draw(deb);
}