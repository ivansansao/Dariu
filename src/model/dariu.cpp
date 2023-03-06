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
    score.darius = 10;
    score.thophy = 0;
    score.thophy_total = 3;
    win = false;
    over = false;
}
Dariu::~Dariu() {
}
void Dariu::reset_position() {
    pos = sf::FloatRect(32.f, 672.f, 32.f, 32.f);
}
void Dariu::die() {
    cout << "*die\n";
    state = States::Dieing;
    if (fired_sound.getStatus() == 0) fired_sound.play();
    velocity.y = lift;
    cout << " Vel: " << velocity.y << endl;
    on_ground = true;
}

void Dariu::update(Tilemap *tilemap) {
    const float posx = pos.left;
    const float posy = pos.top;

    switch (state) {
        case (States::Normal): {
            cout << "*Normal\n";
            Actor::update(tilemap);
            break;
        }
        case (States::Dieing): {
            cout << "*Dieing\n";
            velocity.y += 1;
            pos.top += velocity.y;
            if (pos.top > (tilemap->H * 32) + 32) state = States::Died;
            actor_spr.setPosition(pos.left, pos.top);
            break;
        }
        case (States::Died): {
            cout << "*Died\n";
            score.darius--;
            reset_position();
            state = States::Reviving;
            velocity.y += lift;
            actor_spr.setPosition(pos.left, pos.top);
            break;
        }
        case (States::Reviving): {
            cout << "*Reviving\n";
            velocity.y += 1;
            pos.top += velocity.y;
            if (pos.top > (tilemap->H * 32) + 32) {
                state = States::Normal;
                reset_position();
            }
            actor_spr.setPosition(pos.left, pos.top);
            break;
        }
    }
    cout << "LEFT: " << pos.left << " TOP: " << pos.top << endl;

    if (score.darius < 0) {
        over = true;
    }
}
void Dariu::draw(sf::RenderWindow *w) {
    cout << "DRAWing at: " << pos.left << " , top: " << pos.top << endl;
    Actor::draw(w);
    sf::String xscore = L"Vidas: ";
    xscore += to_string(score.darius) + " Bananas: " + to_string(score.bananas) + "/" + to_string(score.bananas_total);
    xscore += L" Troféus: ";
    xscore += to_string(score.thophy) + "/" + to_string(score.thophy_total);

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
        if (score.bananas >= score.bananas_total) {
            if (score.thophy >= score.thophy_total) {
                if (tilemap->map[21][114] != 'x') {
                    dooropen_sound.play();
                    tilemap->map[21][114] = 'x';
                }
            }
        }
    }

    if (tilemap->map[i][j] == '0') {
        tilemap->map[i][j] = ' ';
        play_sound_pop();
        score.bananas++;
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
        win = true;
    }
}