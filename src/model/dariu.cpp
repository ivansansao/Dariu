#include "dariu.hpp"

#include <cmath>

#include "iostream"
#include "tilemap.hpp"
#include "tools.hpp"

using namespace std;

Dariu::Dariu() {
    text_score.setFont(font_vibes);
    text_score.setCharacterSize(20);
    text_score.setFillColor(sf::Color::White);
    reset_position();
    score.bananas = 0;
    score.bananas_total = 282;
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
void Dariu::update(Tilemap *tilemap) {
    Actor::update(tilemap);

    if (score.darius < 0) {
        over = true;
    }
}
void Dariu::draw(sf::RenderWindow *w) {
    Actor::draw(w);
    text_score.setString("Darius: " + to_string(score.darius) + " Bananas: " + to_string(score.bananas) + "/" + to_string(score.bananas_total) + " Trofeus: " + to_string(score.thophy) + "/" + to_string(score.thophy_total));
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
    if (tilemap->map[i][left_block] == 'F') {
        if (fired_sound.getStatus() == 0) fired_sound.play();
        cout << "Uuuuu meu pé esquerdo! \n";
        score.darius--;
        reset_position();
    } else if (tilemap->map[i][right_block] == 'F') {
        if (fired_sound.getStatus() == 0) fired_sound.play();
        cout << "Hahhhh meu pé direito!\n";
        score.darius--;
        reset_position();
    }
}

void Dariu::on_collide_other(int i, int j, Tilemap *tilemap) {
    Actor::on_collide_other(i, j, tilemap);

    if (score.darius >= 0) {
        if (score.bananas >= score.bananas_total) {
            if (score.thophy >= score.thophy_total) {
                if (tilemap->map[21][99] != 'd') {
                    dooropen_sound.play();
                    tilemap->map[21][99] = 'd';
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
    if (tilemap->map[i][j] == 'F') {
    }
    if (tilemap->map[i][j] == 'b') {
        tilemap->map[i][j] = 'B';
    }
    if (tilemap->map[i][j] == 'd') {
        win = true;
    }
}