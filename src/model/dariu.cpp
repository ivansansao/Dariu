#include "dariu.hpp"

#include <cmath>

#include "iostream"
#include "tilemap.hpp"
#include "tools.hpp"

using namespace std;

Dariu::Dariu() {
    text_score.setFont(font_vibes);
    text_score.setCharacterSize(14);
    text_score.setFillColor(sf::Color::White);
    reset_position();
    score.bananas = 0;
    score.bananas_total = 0;
    score.darius = 3;
    score.thophy = 0;
    score.thophy_total = 3;
    win = false;
    over = false;
    levelcomplete.loadFromFile("./asset/sound/levelcomplete.ogg");
    levelcomplete_sound.setBuffer(levelcomplete);
    levelcomplete_sound.setVolume(9.f);
}
Dariu::~Dariu() {
}
void Dariu::reset_position() {
    // pos = sf::FloatRect(32.f, 672.f, 32.f, 32.f);
    pos = sf::FloatRect(32.f, 672.f, 32.f, 32.f);
}
void Dariu::die() {
    if (state == States::Normal) {
        cout << "*die\n";
        state = States::DieStart;
        if (fired_sound.getStatus() == 0) fired_sound.play();
    }
}

void Dariu::update(Tilemap *tilemap) {
    switch (state) {
        case (States::Normal): {
            Actor::update(tilemap);
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
            actor_spr.setPosition(pos.left, pos.top);
            break;
        }
        case (States::Died): {
            state = States::ReviveStart;
            score.darius--;
            actor_spr.setPosition(pos.left, pos.top);
            break;
        }
        case (States::ReviveStart): {
            state = States::Reviving;
            reset_position();
            jump();
            break;
        }
        case (States::Reviving): {
            add_gravity();
            if (velocity.y == 0) {
                state = States::Revived;
            }
            actor_spr.setPosition(pos.left, pos.top);
            break;
        }
        case (States::Revived): {
            state = States::Normal;
            actor_spr.setPosition(pos.left, pos.top);
            break;
        }
    }

    if (score.darius < 0) {
        over = true;
    }
}
void Dariu::draw(sf::RenderWindow *w, int phase) {
    Actor::draw(w);
    sf::String xscore = L"Vidas: ";
    xscore += to_string(score.darius) + " Bananas: " + to_string(score.bananas) + "/" + to_string(score.bananas_total);
    xscore += L" Troféus: ";
    xscore += to_string(score.thophy) + "/" + to_string(score.thophy_total);
    xscore += "    Fase: " + to_string(phase);

    text_score.setString(xscore);
    w->draw(text_score);
}

void Dariu::on_collide(std::string where, int i, int j, Tilemap *tilemap) {
    Actor::on_collide(where, i, j, tilemap);

    const float j32 = pos.left / 32;
    int left_block = Tools::floor_special(j32 + 1, 0.71);
    int right_block = Tools::ceil_special(j32, 0.39);

    if (where == "top") {
        if (tilemap->map[i][j] == 'b') {
            tilemap->map[i][j] = ' ';
            crash_sound.play();
        };
    }
    if (tilemap->map[i][left_block] == 'R') {  // Fire

        cout << "COMECOU L\n";
        die();
    } else if (tilemap->map[i][right_block] == 'R') {  // Fire
        cout << "COMECOU R\n";
        die();
    }
}

void Dariu::on_collide_other(int i, int j, Tilemap *tilemap) {
    Actor::on_collide_other(i, j, tilemap);

    if (score.darius >= 0) {
        if (score.thophy >= score.thophy_total) {
            if (tilemap->map[21][114] != 'x') {
                dooropen_sound.play();
                tilemap->map[21][114] = 'x';
            }
        }
    }

    if (tilemap->map[i][j] == '.') {
        tilemap->map[i][j] = ' ';
        play_sound_pop();
        score.bananas++;
        if (score.bananas % 30 == 0) {
            score.bananas -= 30;
            score.bananas_total -= 30;
            score.darius++;
        }
    }
    if (tilemap->map[i][j] == 'T') {
        tilemap->map[i][j] = ' ';
        score.thophy++;
    }
    if (tilemap->map[i][j] == 'R') {
    }
    if (tilemap->map[i][j] == 'b') {
        tilemap->map[i][j] = 'B';
    }
    if (tilemap->map[i][j] == 'x') {
        levelcomplete_sound.play();
        win = true;
    }
}