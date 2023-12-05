#include "tilemap.hpp"

#include <cmath>

#include "iostream"

Tilemap::Tilemap() {
    jetpack.init(4, 0.5f, "./src/asset/image/Jetpack.png", sf::IntRect(0, 0, 32, 32), true);
    banana.init(17, 0.5f, "./src/asset/image/Items/Fruits/Bananas.png", sf::IntRect(0, 0, 32, 32), true);
    portalP.init(0, 0.f, "./src/asset/image/PortalP.png", sf::IntRect(0, 0, 32, 32), true);
    portalQ.init(0, 0.f, "./src/asset/image/PortalQ.png", sf::IntRect(0, 0, 32, 32), true);
    trophy.init(12, 0.05f, "./src/asset/image/Items/Checkpoints/End/Olho.png", sf::IntRect(0, 0, 32, 32), false);
    gate.init(0, 0.f, "./src/asset/image/gate.png", sf::IntRect(0, 0, 32, 32), true);
    gatekey.init(0, 0.f, "./src/asset/image/gatekey.png", sf::IntRect(0, 0, 32, 32), true);
}

std::string Tilemap::map[H] = {};

void Tilemap::load_from_file(int phase) {
    const int fileNumber = phase;
    this->load_map_from_file(fileNumber);
    this->load_texture_from_file(fileNumber);
}
void Tilemap::load_map_from_file(int phase) {
    this->mapfile = "./src/resource/map_" + to_string(phase) + ".dtm";
    std::string lines = Tools::get_lines_from_dtm(this->mapfile, "", "\n");
    std::stringstream ss(lines);
    std::string line;
    int i = 0;

    while (getline(ss, line, '\n')) {
        this->W = line.length();
        this->map[i] = line;
        i++;
    }
}
void Tilemap::load_texture_from_file(int phase) {
    std::string terrain = Tools::get_lines_from_dtm("./src/resource/map_" + to_string(phase) + ".dtm", "[TERRAIN]", "");
    if (terrain.empty()) terrain = "Terrain";
    std::string root = "./src/asset/image/" + terrain + "/";

    terrain_tex.loadFromFile(root + "Terrain (16x16).png");
    terrain2_tex.loadFromFile(root + "Terrain (32x32).png");
    door_tex.loadFromFile("./src/asset/image/door.png");

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

    start_tex.loadFromFile("./src/asset/image/Start.png");
    start.setTexture(start_tex);
    start.setTextureRect(sf::IntRect(0, 0, 32, 32));

    fire_tex.loadFromFile("./src/asset/image/fire1.png");
    fire.setTexture(fire_tex);
    fire.setTextureRect(sf::IntRect(0, 0, 32, 32));

    water.init(5, 0.1f, root + "Water.png", sf::IntRect(0, 0, 32, 32), true);

    treeLog.init(1, 0.1f, "./src/asset/image/Treelog.png", sf::IntRect(0, 0, 32, 32), true);
    treeLogSolid.init(1, 0.1f, "./src/asset/image/Treelogsolid.png", sf::IntRect(0, 0, 32, 32), true);
    leafc.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(32, 32, 32, 32), true);
    leaf1.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(0, 64, 32, 32), true);
    leaf2.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(0, 32, 32, 32), true);
    leaf3.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(0, 0, 32, 32), true);
    leaf4.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(32, 0, 32, 32), true);
    leaf5.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(64, 0, 32, 32), true);
    leaf6.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(64, 32, 32, 32), true);
    leaf7.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(64, 64, 32, 32), true);

    woodBridge.init(1, 0.1f, "./src/asset/image/Woodbridge.png", sf::IntRect(0, 0, 32, 32), true);
}

bool Tilemap::isPortal(int i, int j) {
    return map[i][j] == 'P' || map[i][j] == 'Q';
    // return getTileName(i, j) == 'P' || getTileName(i, j) == 'Q';
};
char Tilemap::getTileName(int i, int j) {
    char rs = ' ';
    if (i >= 0 && i < this->W && j >= 0 && j < this->H) {
        rs = map[i][j];
    }
    return rs;
};
int Tilemap::getTileNumber(int i, int j) {
    char charNum = map[i][j + 1];
    // int intNum = (int)charNum;
    int intNum = std::atoi(&charNum);
    return intNum;
};

point Tilemap::getTileByNameNumber(char name, int number) {
    point op;

    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            if (this->map[i][j] == name) {
                if (number == this->getTileNumber(i, j)) {
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

point Tilemap::getMapOppositPortal(int i, int j) {
    const char name = map[i][j] == 'P' ? 'Q' : 'P';
    const int number = this->getTileNumber(i, j);
    const auto op = this->getTileByNameNumber(name, number);
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
            } else if (map[i][j] == 'G') {
                gate.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'K') {
                gatekey.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'W') {
                water.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'd') {
                leafc.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'e') {
                leaf1.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'f') {
                leaf2.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 's') {
                leaf3.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'h') {
                leaf4.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'i') {
                leaf5.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'l') {
                leaf6.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'm') {
                leaf7.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'c') {
                treeLog.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'n') {
                treeLogSolid.draw(j * 32, i * 32, w);
            } else if (map[i][j] == 'w') {
                woodBridge.draw(j * 32, i * 32, w);
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
    water.anime(sf::IntRect(water.getFrame() * 32, 0, 32, 32), 1);
    trophy.anime(sf::IntRect(trophy.getFrame() * 32, 0, 32, 32), 1);

    i_fire += 0.5f;

    for (auto& plataform : plataforms) {
        plataform->draw(w);
    }
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
point Tilemap::getTileFromPixel(int x, int y, int height, int width) {
    point coord;
    coord.i = (int)y / height;
    coord.j = (int)x / width;
    coord.l = this->map[coord.i][coord.j];
    return coord;
}
void Tilemap::edit(sf::RenderWindow* w, sf::Event event, sf::View view) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->edit_current_char = 'A';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        this->edit_current_char = 'B';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        this->edit_current_char = 'b';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        this->edit_current_char = 'C';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->edit_current_char = 'D';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        this->edit_current_char = 'E';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        this->edit_current_char = 'F';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        this->edit_current_char = 'H';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        this->edit_current_char = 'P';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        this->edit_current_char = 'Q';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        this->edit_current_char = 'R';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        this->edit_current_char = 'J';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        this->edit_current_char = 'T';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        this->edit_current_char = 'Y';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        this->edit_current_char = 'X';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        this->edit_current_char = 'Z';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
        this->edit_current_char = '.';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        this->edit_current_char = ' ';
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        this->edit_save();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*w);
        sf::Vector2f worldPos = w->mapPixelToCoords(mousePos);
        point p = this->getTileFromPixel(worldPos.x, worldPos.y, 32, 32);
        this->map[p.i][p.j] = this->edit_current_char;
    }
};
void Tilemap::edit_click(){

};
void Tilemap::edit_save() {
    for (int i{}; i < this->H; ++i) {
        for (int j{}; j < this->W; j++) {
            std::cout << this->map[i][j];
        }
        std::cout << endl;
    }
};
bool Tilemap::free_path(int i, int j) {
    if (this->is_valid(i, j)) {
        return this->map[i][j] == ' ' || this->map[i][j] == '@' || this->map[i][j] == '0' || this->map[i][j] == '1' || this->map[i][j] == '2' || this->map[i][j] == '3' || this->map[i][j] == '4' || this->map[i][j] == '5' || this->map[i][j] == '6' || this->map[i][j] == '7' || this->map[i][j] == '8' || this->map[i][j] == '9';
    }
    return false;
}
bool Tilemap::free_path_bullet(int i, int j) {
    if (this->is_valid(i, j)) {
        return this->map[i][j] == ' ' || this->map[i][j] == '@' || this->map[i][j] == 'P' || this->map[i][j] == 'Q' || this->map[i][j] == 'G' || this->map[i][j] == 'R' || this->map[i][j] == '^' || this->map[i][j] == 'V' || this->map[i][j] == '>' || this->map[i][j] == '<' || this->map[i][j] == 'M' || this->map[i][j] == 'H' || this->map[i][j] == 'Z' || this->map[i][j] == 'k' || this->map[i][j] == 'K' || this->map[i][j] == 'g' || this->map[i][j] == 'x' || this->map[i][j] == 'j' || this->map[i][j] == 'J' || this->map[i][j] == 'Y' || this->map[i][j] == '.' || this->map[i][j] == 'T' || this->map[i][j] == '0' || this->map[i][j] == '1' || this->map[i][j] == '2' || this->map[i][j] == '3' || this->map[i][j] == '4' || this->map[i][j] == '5' || this->map[i][j] == '6' || this->map[i][j] == '7' || this->map[i][j] == '8' || this->map[i][j] == '9' || this->map[i][j] == 's' || this->map[i][j] == 'h' || this->map[i][j] == 'i' || this->map[i][j] == 'f' || this->map[i][j] == 'd' || this->map[i][j] == 'l' || this->map[i][j] == 'e' || this->map[i][j] == 'd' || this->map[i][j] == 'm' || this->map[i][j] == 'c' || this->map[i][j] == 'n';
    }
    return false;
}
// char* Tilemap::tile(int i, int j) {
//     if (i >= 0 && i <= this->H && j >= 0 && j <= this->W) {
//         return this->map[i][j];
//     }
//     return new char;
// }
bool Tilemap::is_valid(int i, int j) {
    return (i >= 0 && i <= this->H && j >= 0 && j <= this->W);
}