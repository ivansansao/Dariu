#include "tilemap.hpp"

#include <cmath>

#include "iostream"

Tilemap::Tilemap() {
    Animation ban(17, 0.5f, "./asset/Free/Terrain/Terrain (16x16).png");
    ban.setTextureRect(sf::IntRect(0, 0, 32, 32));

    terrain_tex.loadFromFile("./asset/Free/Terrain/Terrain (16x16).png");
    ground.setTexture(terrain_tex);
    ground.setTextureRect(sf::IntRect(96, 0, 32, 32));

    ground_ora.setTexture(terrain_tex);
    ground_ora.setTextureRect(sf::IntRect(272, 64, 32, 32));

    ground_door_opened.setTexture(terrain_tex);
    ground_door_opened.setTextureRect(sf::IntRect(0, 0, 32, 5));

    ground_door_closed.setTexture(terrain_tex);
    ground_door_closed.setTextureRect(sf::IntRect(0, 0, 32, 32));

    banana_tex.loadFromFile("./asset/Free/Items/Fruits/Bananas.png");
    banana.setTexture(banana_tex);
    banana.setTextureRect(sf::IntRect(0, 0, 32, 32));

    fire_tex.loadFromFile("./asset/Free/fire1.png");
    fire.setTexture(fire_tex);
    fire.setTextureRect(sf::IntRect(0, 0, 32, 32));

    trophy_tex.loadFromFile("./asset/Free/Items/Checkpoints/End/End (Pressed) (64x64).png");
    trophy.setTexture(trophy_tex);
    trophy.setTextureRect(sf::IntRect(0, 0, 64, 64));

    background_tex.loadFromFile("./asset/Redwood.jpg");
    background.setTexture(background_tex);

    sf::RectangleShape block(sf::Vector2f(height_floor, height_floor));
}

std::string Tilemap::map[H] = {};
std::string Tilemap::enimies[H] = {};

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
            } else if (map[i][j] == 'b') {
                ground_ora.setPosition(j * 32, i * 32);
                w->draw(ground_ora);
            } else if (map[i][j] == 'F') {
                fire.setTextureRect(sf::IntRect(((int)i_fire % q_fire) * 32, 0, 32, 32));
                fire.setPosition(j * 32, i * 32);
                w->draw(fire);
            } else if (map[i][j] == 'D') {
                ground_door_closed.setPosition(j * 32, i * 32);
                w->draw(ground_door_closed);
            } else if (map[i][j] == 'd') {
                ground_door_opened.setPosition(j * 32, i * 32);
                w->draw(ground_door_opened);
            } else {
            }
        }
    }
    i_banana += 0.5f;
    i_trophy += 0.1f;
    i_fire += 0.5f;
}
void Tilemap::load_from_file(int phase) {
    // Start

    int i;
    string line;

    // Map.

    ifstream map_file("./resource/map_" + to_string(phase) + ".dtm");
    cout << "File opened? " << map_file.is_open() << endl;

    i = 0;
    while (getline(map_file, line)) {
        this->map[i] = line;
        i++;
    }
    map_file.close();

    // Enimies.
    ifstream enimies_file("./resource/enimies_" + to_string(phase) + ".dtm");
    i = 0;
    while (getline(enimies_file, line)) {
        this->enimies[i] = line;
        i++;
    }
    enimies_file.close();
}