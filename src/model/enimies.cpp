#include "enimies.hpp"

#include <iostream>

using namespace std;

/**
 * Base class for enimies
 */

Enimy::Enimy() {
    enimydie.loadFromFile("./asset/sound/enimydie.ogg");
    enimydie_sound.setBuffer(enimydie);
};

void Enimy::update(Tilemap *tilemap) {
    switch (state) {
        case (States::Normal): {
            // ---------------- Y ----------------
            add_gravity();
            collision_y(tilemap);

            // ---------------- X ----------------

            if (direction_x == 1) velocity.x = 0.5;
            if (direction_x == -1) velocity.x = -0.5;

            pos.left += velocity.x;

            collision_x(tilemap);
            break;
        }
        case (States::DieStart): {
            state = States::Dieing;
            jump(true);
            break;
        }
        case (States::Dieing): {
            add_gravity();
            if (pos.top > (tilemap->H * 32) + 32) state = States::Died;
            break;
        }
        case (States::Died): {
            break;
        }
        case (States::ReviveStart): {
            break;
        }
        case (States::Reviving): {
            break;
        }
        case (States::Revived): {
            break;
        }
    }

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

    if (tilemap->map[i][left_block] == 'R') {
        // if (fired_sound.getStatus() == 0) fired_sound.play();
    } else if (tilemap->map[i][right_block] == 'R') {
        // if (fired_sound.getStatus() == 0) fired_sound.play();
    }
}

void Enimy::die() {
    if (state == States::Normal) {
        cout << "*die (eminy)\n";
        state = States::DieStart;
        if (enimydie_sound.getStatus() == 0) enimydie_sound.play();
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
void Catraca::die() {
    Enimy::die();
}
/**
 * Sova is enimy
 */

Sova::Sova() {
    actor_tex_fall.loadFromFile("./asset/Free/sova.png");
    actor_tex.loadFromFile("./asset/Free/sova.png");
    actor_tex_idle.loadFromFile("./asset/Free/sova.png");
};

void Sova::update(Tilemap *tilemap) {
    Enimy::update(tilemap);
}
void Sova::draw(sf::RenderWindow *w) {
    if (on_ground) {
        actor_spr.setTexture(actor_tex);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 6, direction_x * -1) * 32, 0, (direction_x * -1) * 32, 32));
    }
    w->draw(actor_spr);
}
void Sova::on_collide(std::string where, int i, int j, Tilemap *tilemap) {
    Enimy::on_collide(where, i, j, tilemap);
}
void Sova::die() {
    Enimy::die();
}