#include "tilemap.hpp"

#include <cmath>

#include "iostream"

Tilemap::Tilemap() {
    Animation ban(17, 0.5f, "./asset/Free/Terrain/Terrain (16x16).png");
    ban.setTextureRect(sf::IntRect(0, 0, 32, 32));

    terrain_tex.loadFromFile("./asset/Free/Terrain/Terrain (16x16).png");
    terrain2_tex.loadFromFile("./asset/Free/Terrain/Terrain (32x32).png");
    door_tex.loadFromFile("./asset/Free/door.png");

    ground.setTexture(terrain_tex);
    ground.setTextureRect(sf::IntRect(96, 0, 32, 32));

    ground_ora.setTexture(terrain_tex);
    ground_ora.setTextureRect(sf::IntRect(272, 64, 32, 32));

    ground_door_closed.setTexture(door_tex);
    ground_door_closed.setTextureRect(sf::IntRect(0, 0, 32, 32));

    ground_door_opened.setTexture(door_tex);
    ground_door_opened.setTextureRect(sf::IntRect(32, 0, 32, 32));

    ground_left.setTexture(terrain2_tex);
    ground_left.setTextureRect(sf::IntRect(0, 0, 32, 32));
    ground_mid.setTexture(terrain2_tex);
    ground_mid.setTextureRect(sf::IntRect(32, 0, 32, 32));
    ground_right.setTexture(terrain2_tex);
    ground_right.setTextureRect(sf::IntRect(64, 0, 32, 32));

    ground_left2.setTexture(terrain2_tex);
    ground_left2.setTextureRect(sf::IntRect(0, 32, 32, 32));
    ground_mid2.setTexture(terrain2_tex);
    ground_mid2.setTextureRect(sf::IntRect(32, 32, 32, 32));
    ground_right2.setTexture(terrain2_tex);
    ground_right2.setTextureRect(sf::IntRect(64, 32, 32, 32));

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

void Tilemap::update() {
    // std::cout << "Update " << map[0] << "\n";
    // tilemap_spr.setPosition(sf::Vector2f(0, 0));
    std::string e;
    for (auto& plataform : plataforms) {
        e = map[(int)plataform->pos.top / 32][(int)plataform->pos.left / 32];
        if (e == "<") {
            plataform->velocity.x = -plataform->vel_step;
            plataform->velocity.y = 0.0f;
        } else if (e == ">") {
            plataform->velocity.x = plataform->vel_step;
            plataform->velocity.y = 0.0f;
        } else if (e == "^") {
            plataform->velocity.x = 0.0f;
            plataform->velocity.y = -plataform->vel_step;
        } else if (e == "V") {
            plataform->velocity.x = 0.0f;
            plataform->velocity.y = plataform->vel_step;
        }
        plataform->update();
    }
}

void Tilemap::draw(sf::RenderWindow* w) {
    for (int i{}; i < H; ++i) {
        for (int j{}; j < W; ++j) {
            // std::cout << map[i] << " \n";
            if (map[i][j] == ' ') {
                continue;
            } else if (map[i][j] == '.') {
                banana.setTextureRect(sf::IntRect(((int)i_banana % q_banana) * 32, 0, 32, 32));
                banana.setPosition(j * 32, i * 32);
                w->draw(banana);
            } else if (map[i][j] == 'T') {
                trophy.setTextureRect(sf::IntRect(((int)i_trophy % q_trophy) * 64, 0, 64, 64));
                trophy.setPosition(j * 32, i * 32);
                w->draw(trophy);
            } else if (map[i][j] == 'A') {
                ground_left.setPosition(j * 32, i * 32);
                w->draw(ground_left);
            } else if (map[i][j] == 'B') {
                ground_mid.setPosition(j * 32, i * 32);
                w->draw(ground_mid);
            } else if (map[i][j] == 'C') {
                ground_right.setPosition(j * 32, i * 32);
                w->draw(ground_right);
            } else if (map[i][j] == 'D') {
                ground_left2.setPosition(j * 32, i * 32);
                w->draw(ground_left2);
            } else if (map[i][j] == 'E') {
                ground_mid2.setPosition(j * 32, i * 32);
                w->draw(ground_mid2);
            } else if (map[i][j] == 'F') {
                ground_right2.setPosition(j * 32, i * 32);
                w->draw(ground_right2);
            } else if (map[i][j] == 'b') {
                ground_ora.setPosition(j * 32, i * 32);
                w->draw(ground_ora);
            } else if (map[i][j] == 'R') {
                fire.setTextureRect(sf::IntRect(((int)i_fire % q_fire) * 32, 0, 32, 32));
                fire.setPosition(j * 32, i * 32);
                w->draw(fire);
            } else if (map[i][j] == 'X') {
                ground_door_closed.setPosition(j * 32, i * 32);
                w->draw(ground_door_closed);
            } else if (map[i][j] == 'x') {
                ground_door_opened.setPosition(j * 32, i * 32);
                w->draw(ground_door_opened);
            } else {
            }
        }
    }
    i_banana += 0.5f;
    i_trophy += 0.1f;
    i_fire += 0.5f;

    for (auto& plataform : plataforms) {
        plataform->draw(w);
    }
}
void Tilemap::load_from_file(int phase) {
    // Start

    int i;
    string line;

    // Map.

    ifstream map_file("./resource/map_" + to_string(phase) + ".dtm");

    i = 0;
    while (getline(map_file, line)) {
        this->map[i] = line;
        i++;
    }
    map_file.close();
}
void Tilemap::load_plataforms() {
    plataforms.clear();
    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            if (this->map[i][j] == 'M') {
                Plataform* plataform = new Plataform();
                plataform->pos.top = i * 32;
                plataform->pos.left = j * 32;
                plataforms.push_back(plataform);
            }
        }
    }
}