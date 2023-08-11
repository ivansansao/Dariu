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
            add_gravity();
            collision_y(tilemap, sounds);

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
    collision_other(tilemap, sounds);
    collision_portal(tilemap, sounds);
}
void Enimy::draw(sf::RenderWindow *w) {
    actor_spr.setPosition(pos.left, pos.top);

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
    if (where == "left") direction_x = 1;
    if (where == "right") direction_x = -1;
}
void Enimy::on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Actor::on_collide_other(i, j, tilemap, sounds);
}
void Enimy::die(Sounds *sounds) {
    if (state == States::Normal) {
        state = States::DieStart;
        if (sounds->enimydie_sound.getStatus() == 0) {
            sounds->enimydie_sound.play();
        };
    }
}
/**
 * Catraca is enimy
 */

Catraca::Catraca() {
    actor_tex_fall.loadFromFile("./src/asset/image/Main Characters/Mask Dude/Fall (32x32).png");
    actor_tex.loadFromFile("./src/asset/image/Main Characters/Mask Dude/Run (32x32).png");
    actor_tex_idle.loadFromFile("./src/asset/image/Main Characters/Mask Dude/Idle (32x32).png");
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
void Catraca::on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide_other(i, j, tilemap, sounds);
}
void Catraca::die(Sounds *sounds) {
    Enimy::die(sounds);
}
/**
 * Sova is enimy
 */

Sova::Sova() {
    actor_tex_fall.loadFromFile("./src/asset/image/sova.png");
    actor_tex.loadFromFile("./src/asset/image/sova.png");
    actor_tex_idle.loadFromFile("./src/asset/image/sova.png");
};

void Sova::update(Tilemap *tilemap, Sounds *sounds) {
    Enimy::update(tilemap, sounds);
    if ((this->updates + (this->id * 10)) % 300 == 0) {
        if (this->state == States::Normal) {
            Enimy::jump();
        }
    }
    if (this->updates % 150 == 0) {
        Enimy::shot(sounds);
    }

    Enimy::update_bullets(tilemap, sounds);
    this->updates++;
    if (this->updates > 9999) this->updates = 0;
}
void Sova::draw(sf::RenderWindow *w) {
    actor_spr.setPosition(pos.left, pos.top);
    if (on_ground) {
        actor_spr.setTexture(actor_tex);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 6, direction_x * -1) * 32, 0, (direction_x * -1) * 32, 32));
    }
    w->draw(actor_spr);
    Enimy::draw_bullets(w);
}
void Sova::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide(where, i, j, tilemap, sounds);
}
void Sova::on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide_other(i, j, tilemap, sounds);
}
void Sova::die(Sounds *sounds) {
    Enimy::die(sounds);
}
/**
 * Cannon is enimy
 */

Cannon::Cannon() {
    actor_tex_fall.loadFromFile("./src/asset/image/cannon.png");
    actor_tex.loadFromFile("./src/asset/image/cannon.png");
    actor_tex_idle.loadFromFile("./src/asset/image/cannon.png");
};

void Cannon::update(Tilemap *tilemap, Sounds *sounds) {
    switch (state) {
        case (States::Normal): {
            add_gravity();
            collision_y(tilemap, sounds);

            if (direction_x == 1) velocity.x = 0.5;
            if (direction_x == -1) velocity.x = -0.5;

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
}
void Cannon::draw(sf::RenderWindow *w) {
    actor_spr.setPosition(pos.left, pos.top);
    if (on_ground) {
        actor_spr.setTexture(actor_tex);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 2, direction_x * -1) * 32, 0, (direction_x * -1) * 32, 32));
    }
    w->draw(actor_spr);
}
void Cannon::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide(where, i, j, tilemap, sounds);
}
void Cannon::on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide_other(i, j, tilemap, sounds);
}
void Cannon::die(Sounds *sounds) {
    Enimy::die(sounds);
}
/**
 * Bulletc is enimy
 */

Bulletc::Bulletc() {
    actor_tex_fall.loadFromFile("./src/asset/image/bulletc.png");
    actor_tex.loadFromFile("./src/asset/image/bulletc.png");
    actor_tex_idle.loadFromFile("./src/asset/image/bulletc.png");
    on_ground = true;
    direction_x = -1;
};

void Bulletc::update(Tilemap *tilemap) {
    switch (state) {
        case (States::Normal): {
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
}
void Bulletc::draw(sf::RenderWindow *w) {
    actor_spr.setPosition(pos.left, pos.top);
    if (on_ground) {
        actor_spr.setTexture(actor_tex);
        actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 4, direction_x * -1) * 32, 0, (direction_x * -1) * 32, 32));
    }
    w->draw(actor_spr);
}
void Bulletc::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide(where, i, j, tilemap, sounds);
}
void Bulletc::on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Enimy::on_collide_other(i, j, tilemap, sounds);
}
void Bulletc::die(Sounds *sounds) {
    Enimy::die(sounds);
}
