#include "tilemap.hpp"

#include <cmath>

#include "iostream"

Tilemap::Tilemap() {
    jetpack.init(4, 0.5f, "./asset/Free/Jetpack.png", sf::IntRect(0, 0, 32, 32), true);
    banana.init(17, 0.5f, "./asset/Free/Items/Fruits/Bananas.png", sf::IntRect(0, 0, 32, 32), true);
    portalP.init(0, 0.f, "./asset/Free/PortalP.png", sf::IntRect(0, 0, 32, 32), true);
    portalQ.init(0, 0.f, "./asset/Free/PortalQ.png", sf::IntRect(0, 0, 32, 32), true);
    trophy.init(8, 0.2f, "./asset/Free/Items/Checkpoints/End/End (Pressed) (64x64).png", sf::IntRect(0, 0, 64, 64), false);

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

    start_tex.loadFromFile("./asset/Free/Start.png");
    start.setTexture(start_tex);
    start.setTextureRect(sf::IntRect(0, 0, 32, 32));

    fire_tex.loadFromFile("./asset/Free/fire1.png");
    fire.setTexture(fire_tex);
    fire.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

std::string Tilemap::map[H] = {};

bool Tilemap::isPortal(int i, int j) {
    return map[i][j] == 'P' || map[i][j] == 'Q';
};
int Tilemap::getPortalNumber(int i, int j) {
    char charNum = map[i][j + 1];
    int intNum = (int)charNum;
    return intNum;
};

point Tilemap::getMapOppositPortal(int i, int j) {
    char currentLetter = map[i][j];
    int currentNumber = this->getPortalNumber(i, j);

    point op;

    // Search opossit side
    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            if (this->map[i][j] != currentLetter) {
                if (currentNumber == this->getPortalNumber(i, j)) {
                    op.i = i;
                    op.j = j;
                    op.l = this->map[i][j];
                    op.found = true;
                }
            }
        }
    }
    return op;
};

void Tilemap::update() {
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
            if (map[i][j] == ' ') {
                continue;
            } else if (map[i][j] == '@') {
                start.setPosition(j * 32, i * 32);
                w->draw(start);
            } else if (map[i][j] == '.') {
                banana.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'J') {
                jetpack.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'T') {
                trophy.draw(j * 32, i * 32, w);
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
            } else if (map[i][j] == 'P') {
                portalP.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'Q') {
                portalQ.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'X') {
                ground_door_closed.setPosition(j * 32, i * 32);
                w->draw(ground_door_closed);
            } else if (map[i][j] == 'x') {
                ground_door_opened.setPosition(j * 32, i * 32);
                w->draw(ground_door_opened);
            }
        }
    }
    jetpack.anime(sf::IntRect(jetpack.getFrame() * 32, 0, 32, 32), 1);
    banana.anime(sf::IntRect(banana.getFrame() * 32, 0, 32, 32), 1);
    trophy.anime(sf::IntRect(trophy.getFrame() * 64, 0, 64, 64), 1);

    i_fire += 0.5f;

    for (auto& plataform : plataforms) {
        plataform->draw(w);
    }
}
void Tilemap::load_from_file(int phase) {
    int i;
    string line;

    ifstream map_file("./resource/map_" + to_string(phase) + ".dtm");

    i = 0;
    while (getline(map_file, line)) {
        this->W = line.length();
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

void Tilemap::replaceAll(char a, char b) {
    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            if (this->map[i][j] == a) {
                this->map[i][j] = b;
            }
        }
    }
}

void Tilemap::clear() {
    this->door_opened = false;
}