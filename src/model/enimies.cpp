#include "enimies.hpp"

#include <iostream>

using namespace std;

/**
 * Base class for enimies
 */

Enimy::Enimy(){

};

void Enimy::update(Tilemap *tilemap, Sounds *sounds) {
    switch (state) {
        case (States::Normal): {
            // ---------------- Y ----------------
            add_gravity();
            collision_y(tilemap, sounds);

            // ---------------- X ----------------

            if (direction_x == 1) velocity.x = 0.5;
            if (direction_x == -1) velocity.x = -0.5;

            pos.left += velocity.x;

            collision_x(tilemap, sounds);
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

void Enimy::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
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

void Enimy::die(Sounds *sounds) {
    if (state == States::Normal) {
        cout << "*die (eminy)\n";
        state = States::DieStart;
        if (sounds->enimydie_sound.getStatus() == 0) {
            sounds->enimydie_sound.play();
            cout << "play() => " << sounds->enimydie_sound.getStatus();
        };
    }
}
/**
 * Catraca is enimy
 */

Catraca::Catraca() {
    cout << "Catraca 1.0\n";
    actor_tex_fall.loadFromFile("./asset/Free/Main Characters/Mask Dude/Fall (32x32).png");
    actor_tex.loadFromFile("./asset/Free/Main Characters/Mask Dude/Run (32x32).png");
    actor_tex_idle.loadFromFile("./asset/Free/Main Characters/Mask Dude/Idle (32x32).png");
    cout << "Catraca 2.0\n";
};

void Catraca::update(Tilemap *tilemap, Sounds *sounds) {
    Enimy::update(tilemap, sounds);
}
void Catraca::draw(sf::RenderWindow *w) {
    Enimy::draw(w);
}
void Catraca::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide(where, i, j, tilemap, sounds);
}
void Catraca::die(Sounds *sounds) {
    Enimy::die(sounds);
}
/**
 * Sova is enimy
 */

Sova::Sova() {
    actor_tex_fall.loadFromFile("./asset/Free/sova.png");
    actor_tex.loadFromFile("./asset/Free/sova.png");
    actor_tex_idle.loadFromFile("./asset/Free/sova.png");
};

void Sova::update(Tilemap *tilemap, Sounds *sounds) {
    Enimy::update(tilemap, sounds);
}
void Sova::draw(sf::RenderWindow *w) {
    if (on_ground) {
        actor_spr.setTexture(actor_tex);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 6, direction_x * -1) * 32, 0, (direction_x * -1) * 32, 32));
    }
    w->draw(actor_spr);
}
void Sova::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide(where, i, j, tilemap, sounds);
}
void Sova::die(Sounds *sounds) {
    Enimy::die(sounds);
}
/**
 * Cannon is enimy
 */

Cannon::Cannon() {
    actor_tex_fall.loadFromFile("./asset/Free/cannon.png");
    actor_tex.loadFromFile("./asset/Free/cannon.png");
    actor_tex_idle.loadFromFile("./asset/Free/cannon.png");
};

void Cannon::update(Tilemap *tilemap, Sounds *sounds) {
    switch (state) {
        case (States::Normal): {
            // ---------------- Y ----------------
            add_gravity();
            collision_y(tilemap, sounds);

            // ---------------- X ----------------

            if (direction_x == 1) velocity.x = 0.5;
            if (direction_x == -1) velocity.x = -0.5;

            // pos.left += velocity.x;

            // collision_x(tilemap);
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
void Cannon::draw(sf::RenderWindow *w) {
    if (on_ground) {
        actor_spr.setTexture(actor_tex);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 2, direction_x * -1) * 32, 0, (direction_x * -1) * 32, 32));
    }
    w->draw(actor_spr);
}
void Cannon::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide(where, i, j, tilemap, sounds);
}
void Cannon::die(Sounds *sounds) {
    Enimy::die(sounds);
}
/**
 * Bulletc is enimy
 */

Bulletc::Bulletc() {
    actor_tex_fall.loadFromFile("./asset/Free/bulletc.png");
    actor_tex.loadFromFile("./asset/Free/bulletc.png");
    actor_tex_idle.loadFromFile("./asset/Free/bulletc.png");
    on_ground = true;
    direction_x = -1;
};

void Bulletc::update(Tilemap *tilemap) {
    switch (state) {
        case (States::Normal): {
            // ---------------- Y ----------------
            // add_gravity();
            // collision_y(tilemap);

            // ---------------- X ----------------

            if (direction_x == 1) velocity.x = 0.9;
            if (direction_x == -1) velocity.x = -0.9;

            pos.left += velocity.x;

            if (pos.left < 0) {
                reset_position();
            } else {
                if (pos.left + pos.width > tilemap->W * 32) {
                    reset_position();
                }
            }

            // collision_x(tilemap);
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
            state = States::Normal;
            reset_position();
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
void Bulletc::draw(sf::RenderWindow *w) {
    if (on_ground) {
        actor_spr.setTexture(actor_tex);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 5, direction_x * -1) * 32, 0, (direction_x * -1) * 32, 32));
    }
    w->draw(actor_spr);
}
void Bulletc::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide(where, i, j, tilemap, sounds);
}
void Bulletc::die(Sounds *sounds) {
    Enimy::die(sounds);
}
