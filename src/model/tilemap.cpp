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

    sf::RectangleShape block(sf::Vector2f(height_floor, height_floor));
}

std::string Tilemap::map[H] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                B                                  0000000000                     B",
    "B                                B                                  0000000000                     B",
    "B                                B                                  0000000000                     B",
    "B                                B                00000000000       BBBBBBBBBB                     B",
    "B                                0                00000000000  BBBB      B                         B",
    "B                                0                00000000000            B   BBBB                  B",
    "B                                0               BBBB T  BBBBB           B        000000    00000  B",
    "B         0                      0                    0                  B                  0 T 0  B",
    "B         0                      B00000              BBBB                B        BBBBBB    00 00  B",
    "B         0      00000000BBB     B00000                                  B00000             BBBBB  B",
    "B        BBBB    00000000000     BBBBBB0                                 BBBBBB                    B",
    "B                                B     B0                    0           B                         B",
    "B             BBBBBBBBBBBBBBBB 0 B      B0        0   0     000        T B      00000              B",
    "B 0                              B       B        0 0 0    00000         B      BBBBB              B",
    "B 0       0 0 0 0             BBBB        BBB     0 0 0               BBBB00000                    B",
    "B 0                              B                                       BBBBBB                    B",
    "B                                B             BBBBB                     B       0000000           B",
    "B              BB                BB    BBBB            BB              BBBBB     BBBBBBB           B",
    "B        0     BB         BB           BB              BB 0000000                                  X",
    "B              BB         BB           BB    B000000000BB 0000000 BB                               X",
    "B       000    BB    0    BB           BB    B000000000BB 0000000 BB                               X",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"};

void Tilemap::update() {
    // std::cout << "Update " << map[0] << "\n";
    // tilemap_spr.setPosition(sf::Vector2f(0, 0));
}
void Tilemap::draw(sf::RenderWindow *w) {
    for (int i{}; i < H; ++i) {
        for (int j{}; j < W; ++j) {
            // std::cout << map[i] << " \n";
            if (map[i][j] == ' ') {
                continue;
            } else if (map[i][j] == '0') {
                banana.setTextureRect(sf::IntRect(((int)i_banana % q_banana) * 32, 0, 32, 32));
                banana.setPosition(j * 32, i * 32);
                w->draw(banana);
            } else if (map[i][j] == 'T') {
                trophy.setTextureRect(sf::IntRect(((int)i_trophy % q_trophy) * 64, 0, 64, 64));
                trophy.setPosition(j * 32, i * 32);
                w->draw(trophy);
            } else if (map[i][j] == 'B') {
                ground.setPosition(j * 32, i * 32);
                w->draw(ground);
            } else {
            }
        }
    }
    i_banana += 0.5f;
    i_trophy += 0.1f;
}
// void Tilemap::collision(int direction) {
//     for (int i{}; i < H; ++i) {
//         for (int j{}; j < W; ++j) {
//             if (map[i][j] == 'B') {
//                 if (map[i][j] == '0') {
//                     map[i][j] = ' ';
//                 }
//             }
//         }
//     }
// }