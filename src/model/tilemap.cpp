#include "tilemap.hpp"

#include <cmath>

#include "iostream"

Tilemap::Tilemap() {
    terrain_tex.loadFromFile("./asset/Free/Terrain/Terrain (16x16).png");
    ground.setTexture(terrain_tex);
    ground.setTextureRect(sf::IntRect(96, 0, 48, 48));
    banana_tex.loadFromFile("./asset/Free/Items/Fruits/Bananas.png");
    banana.setTexture(banana_tex);
    banana.setTextureRect(sf::IntRect(0, 0, 32, 32));

    trophy_tex.loadFromFile("./asset/Free/Items/Checkpoints/End/End (Pressed) (64x64).png");
    trophy.setTexture(trophy_tex);
    trophy.setTextureRect(sf::IntRect(0, 0, 64, 64));

    background_tex.loadFromFile("./asset/Redwood.jpg");
    background.setTexture(background_tex);

    sf::RectangleShape block(sf::Vector2f(height_floor, height_floor));
    sf::String tilemap[H] = {
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "                                 B                                       B     B",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "           0                     B                                       B     B",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "B        BBBB                    B                                       B     B",
        "B                                B                                       B     B",
        "B                   BBBBB      0 B                                       B     B",
        "B                                B                                       B     B",
        "B         0 0 0 0             BBBB                0 0 0               BBBB     B",
        "B                                B                                       B     B",
        "BBB                              B       BB                              B     B",
        "B              BB                BB    BB              BB              BBBB    B",
        "B        0     BB         BB           BB              BB                      X",
        "B    B         BB         BB           BB    B         BB         BB           X",
        "B    B         BB    0    BB           BB    B         BB         BB           X",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"};
}
void Tilemap::update() {
    // tilemap_spr.setPosition(sf::Vector2f(0, 0));
}
void Tilemap::draw(sf::RenderWindow *w) {
    sf::String tilemap2[H] = {
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "                                 B                                       B     B",
        "B                                B                                       B     B",
        "B                                B                                       B     B",
        "                                 B                                       B     B",
        "B         T                      B                                       B     B",
        "B                     0          B                                       B     B",
        "B        BBBB                    B                                       B     B",
        "B                                B                                       B     B",
        "B                   BBBBB      0 B                                       B     B",
        "B                                B                                       B     B",
        "B         0 0 0 0             BBBB                0 0 0               BBBB     B",
        "B                                B                                       B     B",
        "BBB                              B       BB                              B     B",
        "B              BB                BB    BB              BB              BBBB    B",
        "B        0     BB         BB           BB              BB                      X",
        "B    B         BB         BB           BB    B         BB         BB           X",
        "B    B         BB    0    BB           BB    B         BB         BB           X",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"};

    w->draw(background);

    for (int i{}; i < H; ++i) {
        for (int j{}; j < W; ++j) {
            // std::cout << tilemap2[i][j] << " \n";
            if (tilemap2[i][j] == ' ') {
                continue;
            } else if (tilemap2[i][j] == '0') {
                banana.setTextureRect(sf::IntRect(((int)i_banana % q_banana) * 32, 0, 32, 32));
                banana.setPosition(j * 32, i * 32);
                w->draw(banana);
            } else if (tilemap2[i][j] == 'T') {
                trophy.setTextureRect(sf::IntRect(((int)i_trophy % q_trophy) * 64, 0, 64, 64));
                trophy.setPosition(j * 32, i * 32);
                w->draw(trophy);
            } else if (tilemap2[i][j] == 'B') {
                ground.setPosition(j * 32, i * 32);
                w->draw(ground);
            } else {
            }
        }
    }
    i_banana += 0.5f;
    i_trophy += 0.1f;
}
