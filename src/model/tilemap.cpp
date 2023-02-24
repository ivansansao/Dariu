#include "tilemap.hpp"

#include <cmath>

#include "iostream"

Tilemap::Tilemap() {
    terrain_tex.loadFromFile("./asset/Free/Terrain/Terrain (16x16).png");
    ground.setTexture(terrain_tex);
    ground.setTextureRect(sf::IntRect(96, 0, 32, 32));
    banana_tex.loadFromFile("./asset/Free/Items/Fruits/Bananas.png");
    banana.setTexture(banana_tex);
    banana.setTextureRect(sf::IntRect(0, 0, 32, 32));

    trophy_tex.loadFromFile("./asset/Free/Items/Checkpoints/End/End (Pressed) (64x64).png");
    trophy.setTexture(trophy_tex);
    trophy.setTextureRect(sf::IntRect(0, 0, 64, 64));

    background_tex.loadFromFile("./asset/Redwood.jpg");
    background.setTexture(background_tex);
    tilemap_loaded = false;

    sf::RectangleShape block(sf::Vector2f(height_floor, height_floor));
}

std::string Tilemap::tilemap[H] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                B                                       B     B",
    "B                                B                                       B     B",
    "B                                B                                       B     B",
    "B                                B                00000000000            B     B",
    "B                                B                00000000000            B     B",
    "B                                B                00000000000            B     B",
    "B                                B               BBBBBBBBBBBBB           B     B",
    "B         0                      B                                       B     B",
    "B         0                      B                                       B     B",
    "B         0           0          B                                       B     B",
    "B        BBBB                    BBBBBB                                  B     B",
    "B                                B                           0           B     B",
    "B                   BBBBB      0 B                0   0     000        T B     B",
    "B 0                              B                0 0 0    00000         B     B",
    "B 0       0 0 0 0             BBBB                0 0 0               BBBB     B",
    "B 0                              B                                       BT    B",
    "BBB                              B       BB                              B     B",
    "B              BB                BB    BB              BB              BBBBB   B",
    "B        0     BB         BB           BB              BB                      X",
    "B    B         BB         BB           BB    B         BB         BB           X",
    "B    B         BB    0    BB           BB    B         BB         BB           X",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"};

void Tilemap::update() {
    // std::cout << "Update " << tilemap[0] << "\n";
    // tilemap_spr.setPosition(sf::Vector2f(0, 0));
}
void Tilemap::draw(sf::RenderWindow *w) {
    for (int i{}; i < H; ++i) {
        for (int j{}; j < W; ++j) {
            // std::cout << tilemap[i] << " \n";
            if (tilemap[i][j] == ' ') {
                continue;
            } else if (tilemap[i][j] == '0') {
                banana.setTextureRect(sf::IntRect(((int)i_banana % q_banana) * 32, 0, 32, 32));
                banana.setPosition(j * 32, i * 32);
                w->draw(banana);
            } else if (tilemap[i][j] == 'T') {
                trophy.setTextureRect(sf::IntRect(((int)i_trophy % q_trophy) * 64, 0, 64, 64));
                trophy.setPosition(j * 32, i * 32);
                w->draw(trophy);
            } else if (tilemap[i][j] == 'B') {
                ground.setPosition(j * 32, i * 32);
                w->draw(ground);
            } else {
            }
        }
    }
    i_banana += 0.5f;
    i_trophy += 0.1f;
}
void Tilemap::collision(int direction) {
    for (int i{}; i < H; ++i) {
        for (int j{}; j < W; ++j) {
            if (tilemap[i][j] == 'B') {
                if (tilemap[i][j] == '0') {
                    tilemap[i][j] = ' ';
                }
            }
        }
    }
}