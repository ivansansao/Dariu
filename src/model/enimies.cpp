#include "enimies.hpp"

#include <iostream>

using namespace std;

/**
 * Base class for enimies
 */

Enimy::Enimy(){};

void Enimy::update(Tilemap *tilemap) {
    // Actor::update(tilemap);

    // ---------------- Y ----------------
    velocity.y += 1;
    pos.top += velocity.y;
    collision_y(tilemap);

    // ---------------- X ----------------

    if (direction_x == 1) velocity.x = 0.5;
    if (direction_x == -1) velocity.x = -0.5;

    pos.left += velocity.x;

    collision_x(tilemap);

    actor_spr.setPosition(pos.left, pos.top);
}
void Enimy::draw(sf::RenderWindow *w) {
    if (velocity.x == 0) {
        actor_spr.setTexture(actor_tex_idle);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)i_idle_sprite % 11, direction_x) * 32, 0, direction_x * 32, 32));
        i_idle_sprite += 0.2;
    } else {
        actor_spr.setTexture(actor_tex);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 12, direction_x) * 32, 0, direction_x * 32, 32));
    }
    w->draw(actor_spr);
}

void Enimy::on_collide(std::string where, int i, int j, Tilemap *tilemap) {
    const float j32 = pos.left / 32;
    int left_block = Tools::floor_special(j32 + 1, 0.71);
    int right_block = Tools::ceil_special(j32, 0.39);

    if (where == "left") direction_x = 1;
    if (where == "right") direction_x = -1;

    if (tilemap->map[i][left_block] == 'F') {
        if (fired_sound.getStatus() == 0) fired_sound.play();
    } else if (tilemap->map[i][right_block] == 'F') {
        if (fired_sound.getStatus() == 0) fired_sound.play();
    }
}
/**
 * Catraca is enimy
 */

Catraca::Catraca() {
    actor_tex_fall.loadFromFile("./asset/Free/Main Characters/Mask Dude/Fall (32x32).png");
    actor_tex.loadFromFile("./asset/Free/Main Characters/Mask Dude/Run (32x32).png");
    actor_tex_idle.loadFromFile("./asset/Free/Main Characters/Mask Dude/Idle (32x32).png");
};

void Catraca::update(Tilemap *tilemap) {
    Enimy::update(tilemap);
}
void Catraca::draw(sf::RenderWindow *w) {
    Enimy::draw(w);
}
void Catraca::on_collide(std::string where, int i, int j, Tilemap *tilemap) {
    Enimy::on_collide(where, i, j, tilemap);
}