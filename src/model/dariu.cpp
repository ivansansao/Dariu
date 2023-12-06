#include "dariu.hpp"

#include <cmath>

#include "iostream"
#include "tilemap.hpp"
#include "tools.hpp"

using namespace std;

Dariu::Dariu() {
    font_vibes.loadFromFile("./src/asset/fonts/RobotoFlex-Regular.ttf");
    text_score.setFont(font_vibes);
    text_score.setCharacterSize(14);
    text_score.setFillColor(sf::Color::White);
    start_pos = sf::FloatRect(32.f, 672.f, 32.f, 32.f);
    reset_position();
    score.bananas = 0;
    score.bananas_total = 0;
    score.darius = 10;
    score.thophy = 0;
    score.thophy_total = 3;
    win = false;
    over = false;
}
Dariu::~Dariu() {
}
void Dariu::reset_position() {
    Actor::reset_position();
}
void Dariu::die(Tilemap *tilemap, Sounds *sounds) {
    if (state == States::Normal) {
        const uint16_t i = this->pos.top / 32;
        const uint16_t j = this->pos.left / 32;
        if (tilemap->map[i][j] != '@') {
            state = States::DieStart;
            if (sounds->fired_sound.getStatus() == 0) sounds->fired_sound.play();
        }
    }
}

void Dariu::update(Tilemap *tilemap, Sounds *sounds) {
    switch (state) {
        case (States::Normal): {
            Actor::update(tilemap, sounds);
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
            state = States::ReviveStart;
            score.darius--;
            tilemap->replaceAll('j', 'J');
            this->jetPackFuel = 0;
            break;
        }
        case (States::ReviveStart): {
            state = States::Reviving;
            reset_position();
            jump(true);

            break;
        }
        case (States::Reviving): {
            add_gravity();
            state = States::Revived;

            break;
        }
        case (States::Revived): {
            state = States::Normal;

            break;
        }
    }

    if (score.darius < 0) {
        over = true;
    }
    actor_spr.setPosition(pos.left, pos.top);
}
void Dariu::draw(sf::RenderWindow *w, int phase, int phase_total) {
    Actor::draw(w);
    sf::String xscore = L"Vidas: ";
    xscore += to_string(score.darius) + "          Bananas: " + to_string(score.bananas) + "/" + to_string(score.bananas_total);
    xscore += L"          Artefatos: ";
    xscore += to_string(score.thophy) + "/" + to_string(score.thophy_total);
    xscore += "          Fase: " + to_string(phase) + " / " + to_string(phase_total);  // + " debug " + to_string(this->pos.left);
    if (this->jetPackFuel > 0) {
        xscore += "          Mochila a jato: " + to_string((int)this->jetPackFuel) + " / 100";
    }

    text_score.setString(xscore);
    w->draw(text_score);
}

void Dariu::on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Actor::on_collide(where, i, j, tilemap, sounds);

    const float j32 = pos.left / 32;
    int left_block = Tools::floor_special(j32 + 1, 0.71);
    int right_block = Tools::ceil_special(j32, 0.39);

    if (where == "top") {
        if (tilemap->getTileChar(i, j) == 'b') {
            tilemap->map[i][j] = ' ';
            if (sounds->crash_sound.getStatus() == 0) sounds->crash_sound.play();
        };
    }
    if (tilemap->map[i][left_block] == 'R') {
        die(tilemap, sounds);
    } else if (tilemap->map[i][right_block] == 'R') {
        die(tilemap, sounds);
    }

    // if (tilemap->getTileChar(i, j) == 'W') {
    //     die(tilemap, sounds);
    // }
}

void Dariu::on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds) {
    Actor::on_collide_other(i, j, tilemap, sounds);
    const char tileChar = tilemap->getTileChar(i, j);

    const float j32 = pos.left / 32;
    int left_block = Tools::floor_special(j32 + 1, 0.71);
    int right_block = Tools::ceil_special(j32, 0.39);

    if (score.thophy >= score.thophy_total) {
        if (!tilemap->door_opened) {
            if (score.darius >= 0) {
                if (sounds->dooropen_sound.getStatus() == 0) sounds->dooropen_sound.play();
                tilemap->replaceAll('X', 'x');
                tilemap->door_opened = true;
            }
        }
    }

    if (tilemap->map[i][left_block] == 'W') {
        die(tilemap, sounds);
    } else if (tilemap->map[i][right_block] == 'W') {
        die(tilemap, sounds);
    }

    if (tileChar == '.') {
        tilemap->map[i][j] = ' ';
        play_sound_pop(sounds);
        score.bananas++;
        if (score.bananas % 30 == 0) {
            score.bananas -= 30;
            score.bananas_total -= 30;
            score.darius++;
        }
    }
    if (tileChar == 'T') {
        tilemap->map[i][j] = ' ';
        score.thophy++;
    }
    if (tileChar == 'R') {
    }
    if (tileChar == 'b') {
        tilemap->map[i][j] = 'B';
    }
    if (tileChar == 'J') {
        if (this->jetPackFuel < this->jetPackCapacity) {
            this->jetPackFuel = this->jetPackCapacity;
            tilemap->map[i][j] = 'j';
        }
    }
    if (tileChar == 'x') {
        if (sounds->levelcomplete_sound.getStatus() == 0) {
            sounds->levelcomplete_sound.play();
        }
        win = true;
    }
    if (tileChar == 'K') {
        for (int t = 0; t <= 999; t++) {
            const int number = tilemap->getTileNumber(i, j);
            const auto gate = tilemap->getTileByNameNumber('G', number);

            if (gate.found) {
                tilemap->map[i][j] = 'k';
                tilemap->map[gate.i][gate.j] = 'g';
                sounds->chain_sound.play();
            } else {
                break;
            }
        }
    }
}

void Dariu::shot(Sounds *sounds) {
    Actor::shot(sounds);
    sounds->shot_sound.play();
}
