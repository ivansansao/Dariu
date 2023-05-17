#include "actor.hpp"

#include <cmath>

#include "animation.hpp"
#include "iostream"
#include "tilemap.hpp"
#include "tools.hpp"

using namespace std;

Actor::Actor() {
    actorJetpack.init(3, 0.5f, "./src/asset/image/Dariu-jetpack.png", sf::IntRect(0, 0, 32, 32), true);
    actorRun.init(8, 0.5f, "./src/asset/image/Dariu-run.png", sf::IntRect(0, 0, 32, 32), true);
    actorIdle.init(1, 0.f, "./src/asset/image/Dariu-idle.png", sf::IntRect(0, 0, 32, 32), true);
    actorJump.init(1, 0.f, "./src/asset/image/Dariu-jump.png", sf::IntRect(0, 0, 32, 32), true);

    actor_tex.loadFromFile("./src/asset/image/Dariu-run.png");
    actor_tex_idle.loadFromFile("./src/asset/image/Dariu-idle.png");
    actor_tex_jump.loadFromFile("./src/asset/image/Dariu-jump.png");
    actor_tex_fall.loadFromFile("./src/asset/image/Dariu-run.png");
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

point Actor::getCoord(Tilemap *tilemap, int offset_i, int offset_j) {
    point coord;
    coord.i = (int)(pos.top + offset_i) / pos.height;
    coord.j = (int)(pos.left + offset_j) / pos.width;

    if (coord.i < 0) coord.i = 0;
    if (coord.i > tilemap->H - 1) coord.i = tilemap->H - 1;

    if (coord.j < 0) coord.j = 0;
    if (coord.j > tilemap->W) coord.j = tilemap->W - 1;

    return coord;
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
    this->pos = sf::FloatRect(start_pos.left, start_pos.top, 32.f, 32.f);
}
void Actor::update(Tilemap *tilemap, Sounds *sounds) {
    if (this->jetPack) {
        this->updateFly(tilemap, sounds);
    } else {
        this->updateWalk(tilemap, sounds);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, sf::Joystick::X)) {
        if (space_released) {
            space_released = false;
            if (this->jetPack) {
                this->jetPack = false;
            } else if (this->jetPackFuel > 0) {
                this->jetPack = true;
            }
        }
    }
}
void Actor::updateWalk(Tilemap *tilemap, Sounds *sounds) {
    // ---------------- Y ----------------

    if (sf::Joystick::isButtonPressed(0, 2)) {
    }
    // cout << "isButtonPressed " << sf::Joystick::getButtonCount(0) << "\n";

    /*
     *  [Letter My_control]
     *
     *      [X1]
     *  []        []
     *      [Z3]
     */

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::isButtonPressed(0, sf::Joystick::Z)) {
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

    float controll_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);  // -100 to 100

    if (controll_x != 0) {
        velocity.x = (controll_x / 100) * 5;
        if (controll_x > 0) {
            direction_x = 1;
        } else if (controll_x < 0) {
            direction_x = -1;
        }
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x += 1;
            direction_x = 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x -= 1;
            direction_x = -1;
        } else {
            velocity.x = 0;
        }
    }
    if (velocity.x > 5) velocity.x = 5;
    if (velocity.x < -5) velocity.x = -5;

    pos.left += velocity.x;

    collision_x(tilemap, sounds);

    // -----------------------------------

    collision_other(tilemap, sounds);

    collision_portal(tilemap, sounds);
}
void Actor::updateFly(Tilemap *tilemap, Sounds *sounds) {
    if (this->jetPackFuel > 0) {
        this->jetPackFuel -= this->jetPackConsume;
    }
    if (this->jetPackFuel <= 0) {
        this->jetPack = false;
        this->jetPackFuel = 0;
    }

    // ---------------- Y ----------------
    float controll_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);  // -100 to 100

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || controll_y < 0) {
        velocity.y = -5;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || controll_y > 0) {
        velocity.y = 5;
    } else {
        velocity.y = 0;
    }

    pos.top += velocity.y;
    collision_y(tilemap, sounds);

    // ---------------- X ----------------

    float controll_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);  // -100 to 100

    if (controll_x != 0) {
        velocity.x = (controll_x / 100) * 5;
        if (controll_x > 0) {
            direction_x = 1;
        } else if (controll_x < 0) {
            direction_x = -1;
        }
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x += 1;
            direction_x = 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x -= 1;
            direction_x = -1;
        } else {
            velocity.x = 0;
        }
    }
    if (velocity.x > 5) velocity.x = 5;
    if (velocity.x < -5) velocity.x = -5;

    pos.left += velocity.x;

    collision_x(tilemap, sounds);

    // -----------------------------------

    collision_other(tilemap, sounds);

    collision_portal(tilemap, sounds);
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
    if (this->jetPack) {
        actorJetpack.anime(sf::IntRect(Tools::getStartSprite(actorJetpack.getFrame(), direction_x) * pos.width, 0, direction_x * pos.width, pos.height), direction_x);
        actorJetpack.draw(pos.left, pos.top, w);
        this->drawJetpackTime(w);
    } else {
        if (on_ground) {
            if (velocity.x == 0) {
                actorIdle.anime(sf::IntRect(Tools::getStartSprite(0, direction_x) * pos.width, 0, direction_x * pos.width, pos.height), direction_x);
                actorIdle.draw(pos.left, pos.top, w);

            } else {
                actorRun.anime(sf::IntRect(Tools::getStartSprite((int)pos.left % actorRun.q_frame, direction_x) * pos.width, 0, direction_x * pos.width, pos.height), direction_x);
                actorRun.draw(pos.left, pos.top, w);
            }
        } else {
            actorJump.anime(sf::IntRect(Tools::getStartSprite(0, direction_x) * pos.width, 0, direction_x * pos.width, pos.height), direction_x);
            actorJump.draw(pos.left, pos.top, w);
        }
    }

    if (false) {
        // We can make a variable specific for sprite and turn pos minor!
        sf::RectangleShape rectangle(sf::Vector2f(pos.left, pos.top));
        rectangle.setSize(sf::Vector2f(pos.width, pos.height));
        rectangle.setPosition(sf::Vector2f(pos.left, pos.top));
        w->draw(rectangle);
    }
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

void Actor::collision_portal(Tilemap *tilemap, Sounds *sounds) {
    auto posMap = getCoord(tilemap, pos.height / 2, pos.width / 2);

    if (onPortal) {
        if (!tilemap->isPortal(posMap.i, posMap.j)) {
            onPortal = false;
        }
    } else {
        if (tilemap->isPortal(posMap.i, posMap.j)) {
            onPortal = true;
            const auto point = tilemap->getMapOppositPortal(posMap.i, posMap.j);

            if (point.found) {
                this->pos.top = point.i * this->pos.height;
                this->pos.left = point.j * this->pos.width;
                this->velocity.y = this->velocity.y * -1;
            }
        }
    }
}
void Actor::die(Sounds *sounds) {
}

bool Actor::is_block(char el) {
    return el == 'A' || el == 'B' || el == 'C' || el == 'D' || el == 'E' || el == 'F' || el == 'b' || el == 'R' || el == 'X' || el == 'G';
}
bool Actor::is_alive() {
    return state == States::Normal;
}
void Actor::drawJetpackTime(sf::RenderWindow *w) {
    float xLeft = pos.left + pos.width;
    float barTotal = this->jetPackCapacity * 0.1;
    float barFuel = this->jetPackFuel * 0.1;

    if (direction_x > 0)
        xLeft = pos.left - barTotal;

    sf::RectangleShape border(sf::Vector2f(pos.left, pos.top));
    border.setFillColor(sf::Color(255, 0, 0, 255));
    border.setPosition(sf::Vector2f(xLeft, pos.top + barTotal));
    border.setSize(sf::Vector2f(10, 3));
    w->draw(border);

    sf::RectangleShape rectangle(sf::Vector2f(pos.left, pos.top));
    rectangle.setFillColor(sf::Color(255, 255, 255, 255));
    rectangle.setPosition(sf::Vector2f(xLeft, pos.top + barTotal));
    rectangle.setSize(sf::Vector2f(barFuel, 3));
    w->draw(rectangle);
}