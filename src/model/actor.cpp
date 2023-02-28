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
    pos = sf::FloatRect(448.f, 672.f, 32.f, 32.f);
    abs_pos = pos;
    velocity = sf::Vector2f(0.f, 0.f);
    direction_x = 1;
    i_idle_sprite = 1;
    ground_y = 736 - (32 + 32);
    on_ground = false;
    gravity = 1.0;
    lift = -17;
    jump.loadFromFile("./asset/sound/jump.ogg");
    jump_sound.setBuffer(jump);
    jump_sound.setVolume(9.f);

    crash.loadFromFile("./asset/sound/crash.ogg");
    crash_sound.setBuffer(crash);
    crash_sound.setVolume(9.f);

    pop.loadFromFile("./asset/sound/pop.wav");
    pop_sound0.setBuffer(pop);
    pop_sound1.setBuffer(pop);
    pop_sound2.setBuffer(pop);
    pop_sound3.setBuffer(pop);
    pop_sound4.setBuffer(pop);
    pop_sound5.setBuffer(pop);
    pop_sound6.setBuffer(pop);
    pop_sound7.setBuffer(pop);
    pop_sound8.setBuffer(pop);
    pop_sound9.setBuffer(pop);

    pop_sound0.setVolume(7.f);
    pop_sound1.setVolume(7.f);
    pop_sound2.setVolume(7.f);
    pop_sound3.setVolume(7.f);
    pop_sound4.setVolume(7.f);
    pop_sound5.setVolume(7.f);
    pop_sound6.setVolume(7.f);
    pop_sound7.setVolume(7.f);
    pop_sound8.setVolume(7.f);
    pop_sound9.setVolume(7.f);

    font_vibes.loadFromFile("./asset/fonts/RobotoFlex-Regular.ttf");
    deb.setFont(font_vibes);
    deb.setCharacterSize(20);
    deb.setFillColor(sf::Color::White);
    deb.setPosition(sf::Vector2f(100, 100));
    deb.setString("");
}

void Actor::up() {
    if (on_ground) {
        velocity.y += lift;
    }
}
void Actor::update(Tilemap *tilemap) {
    // ---------------- Y ----------------

    // cout << "E: " << (int)pos.top / 32 << "," << (int)pos.left / 32 << "\n";

    if (tilemap->map[(int)pos.top / 32][(int)pos.left / 32] == 'B') {
        cout << "Iniciou com B\n";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (up_released) {
            if (on_ground) {
                jump_sound.play();
                velocity.y += lift;
                up_released = false;
            }
        }
    }

    velocity.y += 1;
    pos.top += velocity.y;
    collision_y(tilemap);

    if (tilemap->map[((int)pos.top / 32)][(int)pos.left / 32] == 'B') {
        cerr << "******************* Erro local 1\n";
    }

    // ---------------- X ----------------

    // Bug: Right direction climb block!

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

    collision_x(tilemap);

    if (tilemap->map[((int)pos.top / 32)][(int)pos.left / 32] == 'B') {
        cerr << "******************* Erro local 2\n";
    }

    // -----------------------------------

    collision_other(tilemap);

    if (tilemap->map[(int)pos.top / 32][(int)pos.left / 32] == 'B') {
        cout << "Ended com B\n";
    }

    actor_spr.setPosition(pos.left, pos.top);

    // Just debug
    int i = pos.top / 32;
    int j = pos.left / 32;
    int i2 = (pos.top + pos.height) / 32;
    int j2 = (pos.left + pos.width) / 32;
    deb.setString("on_ground: " + to_string(on_ground) + " map[" + to_string(i) + "][" + to_string(j) + "] = ' " + tilemap->map[i][j] + " ' i2: " + to_string(i2) + " j2: " + to_string(j2) + " on_block: " + to_string(0));

    // cout << "S: " << (int)pos.top / 32 << "," << (int)pos.left / 32 << "\n";
}

void Actor::collision_y(Tilemap *tilemap) {
    on_ground = false;
    // i = 384/12=12 < 384+32=416/32=13
    // Y
    for (int i = pos.top / 32; i <= (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j < (pos.left + pos.width) / 32; j++) {
            if (tilemap->map[i][j] == 'B' || tilemap->map[i][j] == 'b') {
                if (velocity.y > 0) {
                    on_collide("ground", i, j, tilemap);
                    pos.top = i * 32 - pos.height;
                    on_ground = true;
                    // cout << "A\n";
                }
                if (velocity.y < 0) {
                    on_collide("top", i, j, tilemap);
                    pos.top = i * 32 + 32;
                    cout << "Toin..\n";
                }
                velocity.y = 0;
            }
        }
    }
}
void Actor::collision_x(Tilemap *tilemap) {
    // i = 384/12=12 < 384+32=416/32=13
    // cout << " > ";
    for (int i = pos.top / 32; i < (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j <= (pos.left + pos.width) / 32; j++) {
            if (is_block(tilemap->map[i][j])) {
                // PARA o X
                if (velocity.x < 0) {
                    on_collide("left", i, j, tilemap);
                    cout << i << "," << j << "\n";
                    cout << "Pahhh!!\n";
                    const int j2 = ((int)pos.left / 32) + 1;
                    if (is_block(tilemap->map[i][j2])) {
                        cerr << "MOV CANCEL: Has block\n";
                    } else {
                        pos.left = j * 32 + 32;
                        cout << pos.left / 32 << "\n";
                    }
                }
                if (velocity.x > 0) {
                    on_collide("right", i, j, tilemap);
                    cout << i << "," << j << "\n";
                    cout << "Pufff!!\n";
                    pos.left = j * 32 - 32;
                    cout << pos.left / 32 << "\n";
                }
            }
        }
    }
}

void Actor::collision_other(Tilemap *tilemap) {
    for (int i = pos.top / 32; i < (pos.top + pos.height) / 32; i++) {
        for (int j = pos.left / 32; j < (pos.left + pos.width) / 32; j++) {
            if (tilemap->map[i][j] == '0') {
                tilemap->map[i][j] = ' ';
                play_sound_pop();
            }
            if (tilemap->map[i][j] == 'T') {
                tilemap->map[i][j] = ' ';
            }
            if (tilemap->map[i][j] == 'b') {
                tilemap->map[i][j] = 'B';
            }
            if (tilemap->map[i][j] == 'X') {
                pos.left = 910.f;
                pos.top = 672.f;
            }
        }
    }
}
void Actor::draw(sf::RenderWindow *w) {
    if (on_ground) {
        if (velocity.x == 0) {
            actor_spr.setTexture(actor_tex_idle);
            actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)i_idle_sprite % 11, direction_x) * 32, 0, direction_x * 32, 32));
            i_idle_sprite += 0.2;
        } else {
            actor_spr.setTexture(actor_tex);
            actor_spr.setTextureRect(sf::IntRect(Tools::getStartSprite((int)pos.left % 12, direction_x) * 32, 0, direction_x * 32, 32));
        }
    }

    deb.setPosition(sf::Vector2f(pos.left - 620, 100));
    w->draw(actor_spr);
    // w->draw(deb);
}
void Actor::play_sound_pop() {
    if (pop_sound0.getStatus() == 0) {
        pop_sound0.play();
        cout << "sound0\n";
    } else if (pop_sound1.getStatus() == 0) {
        pop_sound1.play();
        cout << "sound1\n";
    } else if (pop_sound2.getStatus() == 0) {
        pop_sound2.play();
        cout << "sound2\n";
    } else if (pop_sound3.getStatus() == 0) {
        pop_sound3.play();
        cout << "sound3\n";
    } else if (pop_sound4.getStatus() == 0) {
        pop_sound4.play();
        cout << "sound4\n";
    } else if (pop_sound5.getStatus() == 0) {
        pop_sound5.play();
        cout << "sound5\n";
    } else if (pop_sound6.getStatus() == 0) {
        pop_sound6.play();
        cout << "sound6\n";
    } else if (pop_sound7.getStatus() == 0) {
        pop_sound7.play();
        cout << "sound7\n";
    } else if (pop_sound8.getStatus() == 0) {
        pop_sound8.play();
        cout << "sound8\n";
    } else if (pop_sound9.getStatus() == 0) {
        pop_sound9.play();
        cout << "sound9\n";
    }
}
void Actor::on_collide(std::string where, int i, int j, Tilemap *tilemap) {
    if (where == "top") {
        if (tilemap->map[i][j] == 'b') {
            tilemap->map[i][j] = ' ';
            crash_sound.play();
        };
    }
}

bool Actor::is_block(char el) {
    return el == 'B' || el == 'b';
}