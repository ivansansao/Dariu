#include "actor.hpp"

#include <cmath>

#include "iostream"
#include "tilemap.hpp"
#include "tools.hpp"

using namespace std;

Actor::Actor() {
    actor_tex_fall.loadFromFile("./asset/Free/Main Characters/Virtual Guy/Fall (32x32).png");
    actor_tex_idle.loadFromFile("./asset/Free/Main Characters/Virtual Guy/Idle (32x32).png");
    actor_tex.loadFromFile("./asset/Free/Main Characters/Virtual Guy/Run (32x32).png");
    actor_spr.setTexture(actor_tex_fall);
    start_pos = sf::FloatRect(672.f, 32.f, 32.f, 32.f);
    abs_pos = pos;
    velocity = sf::Vector2f(0.f, 0.f);
    direction_x = 1;
    i_idle_sprite = 1;
    on_ground = false;
    gravity = 1.0;
    lift = -17;
    reset_position();
}

void Actor::jump() {
    velocity.y = lift;
}
void Actor::jump(bool little) {
    velocity.y = lift * 0.3;
}
void Actor::add_gravity() {
    velocity.y += 1;
    pos.top += velocity.y;
}
void Actor::set_position(float left, float top) {
    pos.left = left;
    pos.top = top;
    start_pos.left = left;
    start_pos.top = top;
}
void Actor::reset_position() {
    pos = sf::FloatRect(start_pos.left, start_pos.top, 32.f, 32.f);
}
void Actor::update(Tilemap *tilemap, Sounds *sounds) {
    // ---------------- Y ----------------

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (up_released) {
            if (on_ground) {
                if (sounds->jump_sound.getStatus() == 0) {
                    sounds->jump_sound.play();
                }
                jump();
                up_released = false;
            }
        }
    }

    add_gravity();
    collision_y(tilemap, sounds);

    // ---------------- X ----------------

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x += 1;
        direction_x = 1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x -= 1;
        direction_x = -1;
    } else {
        velocity.x = 0;
    }
    if (velocity.x > 5) velocity.x = 5;
    if (velocity.x < -5) velocity.x = -5;

    pos.left += velocity.x;

    collision_x(tilemap, sounds);

    // -----------------------------------

    collision_other(tilemap, sounds);

    actor_spr.setPosition(pos.left, pos.top);

}

void Actor::collision_y(Tilemap *tilemap, Sounds *sounds) {
    on_ground = false;

    for (int i = pos.top / 32; i <= (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j < (pos.left + pos.width) / 32; j++) {
            if (is_block(tilemap->map[i][j])) {
                if (velocity.y > 0) {
                    on_collide("ground", i, j, tilemap, sounds);
                    pos.top = i * 32 - pos.height;
                    on_ground = true;
                }
                if (velocity.y < 0) {
                    on_collide("top", i, j, tilemap, sounds);
                    pos.top = i * 32 + 32;
                }
                velocity.y = 0;
                break; 
            }
        }
    }

    sf::FloatRect pos1 = sf::FloatRect(pos.left, pos.top + 1, pos.width, pos.height);
    for (auto &plataform : tilemap->plataforms) {
        if (plataform->pos.intersects(pos1)) {
            if (velocity.y > 0) {
                pos.top = plataform->pos.top - pos.height;
                pos.left += plataform->velocity.x;
                on_ground = true;
            } else if (velocity.y < 0) {
                pos.top = plataform->pos.top + plataform->pos.height;
            }
            velocity.y = 0;
            break;
        }
    }
}
void Actor::collision_x(Tilemap *tilemap, Sounds *sounds) {
    for (int i = pos.top / 32; i < (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j <= (pos.left + pos.width) / 32; j++) {
            if (is_block(tilemap->map[i][j])) {
                if (velocity.x < 0) {
                    on_collide("left", i, j, tilemap, sounds);
                    const int j2 = ((int)pos.left / 32) + 1;
                    if (!is_block(tilemap->map[i][j2])) {
                        pos.left = j * 32 + 32;
                    }
                }
                if (velocity.x > 0) {
                    on_collide("right", i, j, tilemap, sounds);
                    pos.left = j * 32 - pos.width;
                }
            }
        }
    }

    for (auto &plataform : tilemap->plataforms) {
        if (plataform->pos.intersects(pos)) {
            if (velocity.x > 0) {
                pos.left = plataform->pos.left - pos.width;
            } else if (velocity.x < 0) {
                pos.left = plataform->pos.left + plataform->pos.height;
            }
            velocity.x = 0;
            break;
        }
    }
}

void Actor::collision_other(Tilemap *tilemap, Sounds *sounds) {
    for (int i = pos.top / 32; i < (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j < (pos.left + pos.width) / 32; j++) {
            on_collide_other(i, j, tilemap, sounds);
        }
    }
}
void Actor::draw(sf::RenderWindow *w) {
    if (on_ground) {
        if (velocity.x == 0) {
            actor_spr.setTexture(actor_tex_idle);
            actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)i_idle_sprite % 11, direction_x) * pos.width, 0, direction_x * pos.width, pos.height));
            i_idle_sprite += 0.2;
        } else {
            actor_spr.setTexture(actor_tex);
            actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 12, direction_x) * pos.width, 0, direction_x * pos.width, pos.height));
        }
    }

    if (false) {
        // We can make a variable specific for sprite and turn pos minor!
        sf::RectangleShape rectangle(sf::Vector2f(pos.left, pos.top));
        rectangle.setSize(sf::Vector2f(pos.width, pos.height));
        rectangle.setPosition(sf::Vector2f(pos.left, pos.top));
        w->draw(rectangle);
    }
    w->draw(actor_spr);
}
void Actor::play_sound_pop(Sounds *sounds) {
    if (sounds->pop_sound0.getStatus() == 0) {
        sounds->pop_sound0.play();
    } else if (sounds->pop_sound1.getStatus() == 0) {
        sounds->pop_sound1.play();
    } else if (sounds->pop_sound2.getStatus() == 0) {
        sounds->pop_sound2.play();
    } else if (sounds->pop_sound3.getStatus() == 0) {
        sounds->pop_sound3.play();
    } else if (sounds->pop_sound4.getStatus() == 0) {
        sounds->pop_sound4.play();
    } else if (sounds->pop_sound5.getStatus() == 0) {
        sounds->pop_sound5.play();
    } else if (sounds->pop_sound6.getStatus() == 0) {
        sounds->pop_sound6.play();
    } else if (sounds->pop_sound7.getStatus() == 0) {
        sounds->pop_sound7.play();
    } else if (sounds->pop_sound8.getStatus() == 0) {
        sounds->pop_sound8.play();
    } else if (sounds->pop_sound9.getStatus() == 0) {
        sounds->pop_sound9.play();
    }
}
void Actor::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
}
void Actor::on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds) {
}

void Actor::die(Sounds *sounds) {
}

bool Actor::is_block(char el) {
    return el == 'A' || el == 'B' || el == 'C' || el == 'D' || el == 'E' || el == 'F' || el == 'b' || el == 'R' || el == 'X';
}
bool Actor::is_alive() {
    return state == States::Normal;
}