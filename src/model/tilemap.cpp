#include "tilemap.hpp"

#include <cmath>

#include "iostream"

Tilemap::Tilemap() {
    gun.init(4, 0.2f, "./src/asset/image/Gun.png", sf::IntRect(0, 0, 32, 32), false, 0, 0, false);
    munition.init(3, 0.2f, "./src/asset/image/Munition.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    jetpack.init(4, 0.5f, "./src/asset/image/Jetpack.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    liquor.init(4, 0.1f, "./src/asset/image/Liquor/Liquor.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    banana.init(17, 0.5f, "./src/asset/image/Items/Fruits/Bananas.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    portalP.init(0, 0.f, "./src/asset/image/PortalP.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    portalQ.init(0, 0.f, "./src/asset/image/PortalQ.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    trophy.init(8, 0.01f, "./src/asset/image/SpinFlower.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    gate.init(10, 0.2f, "./src/asset/image/gate.png", sf::IntRect(0, 0, 32, 32), false, 0, 0, true);
    exitDoorClosed.init(8, 0.1f, "./src/asset/image/door.png", sf::IntRect(0, 0, 32, 32), false, 0, 0, true);
    exitDoorOpened.init(8, 0.1f, "./src/asset/image/door.png", sf::IntRect(0, 0, 32, 32), false, 0, 0, true);
    gatekey.init(0, 0.f, "./src/asset/image/gatekey.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
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
    terrain_mid_false_tex.loadFromFile(root + "falseblock.png");

    ground.setTexture(terrain_tex);
    ground.setTextureRect(sf::IntRect(96, 0, 32, 32));

    ground_ora.setTexture(terrain_tex);
    ground_ora.setTextureRect(sf::IntRect(272, 64, 32, 32));

    ground_left.setTexture(terrain2_tex);
    ground_left.setTextureRect(sf::IntRect(0, 0, 32, 32));

    ground_mid.setTexture(terrain2_tex);
    ground_mid.setTextureRect(sf::IntRect(32, 0, 32, 32));

    ground_mid_false.setTexture(terrain_mid_false_tex);
    ground_mid_false.setTextureRect(sf::IntRect(0, 0, 32, 32));

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

    water.init(5, 0.1f, root + "Water.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);

    treeLog.init(1, 0.1f, "./src/asset/image/Treelog.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    treeLogSolid.init(1, 0.1f, "./src/asset/image/Treelogsolid.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    leafc.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(32, 32, 32, 32), true, 0, 0, false);
    leaf1.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(0, 64, 32, 32), true, 0, 0, false);
    leaf2.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(0, 32, 32, 32), true, 0, 0, false);
    leaf3.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
    leaf4.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(32, 0, 32, 32), true, 0, 0, false);
    leaf5.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(64, 0, 32, 32), true, 0, 0, false);
    leaf6.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(64, 32, 32, 32), true, 0, 0, false);
    leaf7.init(1, 0.1f, "./src/asset/image/LeafTree.png", sf::IntRect(64, 64, 32, 32), true, 0, 0, false);

    woodBridge.init(1, 0.1f, "./src/asset/image/Woodbridge.png", sf::IntRect(0, 0, 32, 32), true, 0, 0, false);
}

bool Tilemap::isPortal(int i, int j) {
    return getTileChar(i, j) == 'P' || getTileChar(i, j) == 'Q';
    // return getTileChar(i, j) == 'P' || getTileChar(i, j) == 'Q';
};
char Tilemap::getTileChar(int i, int j) {
    char rs = ' ';
    if (i >= 0 && i < this->H && j >= 0 && j < this->W) {
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
            if (this->getTileChar(i, j) == name) {
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
    const char name = getTileChar(i, j) == 'P' ? 'Q' : 'P';
    const int number = this->getTileNumber(i, j);
    const auto op = this->getTileByNameNumber(name, number);
    return op;
};

void Tilemap::update() {
    this->updates++;

    if (this->updates > 999999) this->updates = 0;

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

    if (this->updates % 10 == 0) {
        // MOVE WATER
        for (int i = H - 2; i >= 0; --i) {  // de baixo pra cima, evita reprocessar quem acabou de cair
            for (int j = 0; j < W; ++j) {
                if (this->map[i][j] == 'a') {
                    if (this->free_path_water(i + 1, j)) {  // Está livre à baixo?
                        this->swapBlock(i, j, i + 1, j);
                    } else if (this->free_path_water(i, j - 1)) {  // Está livre à esquerda?
                        this->swapBlock(i, j, i, j - 1);
                    } else if (this->free_path_water(i, j + 1)) {  // Está livre à direita?
                        this->swapBlock(i, j, i, j + 1);
                    }
                }
            }
        }
    }
}

void Tilemap::swapBlock(int i1, int j1, int i2, int j2) {
    const char tileChar = this->getTileChar(i1, j1);
    this->map[i1][j1] = this->map[i2][j2];
    this->map[i2][j2] = tileChar;
}

void Tilemap::draw(sf::RenderWindow* w) {
    for (int i{}; i < H; ++i) {
        for (int j{}; j < W; ++j) {
            const char tileChar = this->getTileChar(i, j);
            if (tileChar == ' ') {
                continue;
            } else if (tileChar == '@') {
                start.setPosition(j * 32, i * 32);
                w->draw(start);
            } else if (tileChar == '%') {
                liquor.draw(j * 32, i * 32, w);
            } else if (tileChar == '.') {
                banana.draw(j * 32, i * 32, w);
            } else if (tileChar == 'J') {
                jetpack.draw(j * 32, i * 32, w);
            } else if (tileChar == 'L') {
                gun.draw(j * 32, i * 32, w);
            } else if (tileChar == 'u') {
                munition.draw(j * 32, i * 32, w);
            } else if (tileChar == 'T') {
                trophy.draw(j * 32, i * 32, w);
            } else if (tileChar == 'A') {
                ground_left.setPosition(j * 32, i * 32);
                w->draw(ground_left);
            } else if (tileChar == 'B') {
                ground_mid.setPosition(j * 32, i * 32);
                w->draw(ground_mid);
            } else if (tileChar == '-') {
                ground_mid_false.setPosition(j * 32, i * 32);
                w->draw(ground_mid_false);
            } else if (tileChar == 'C') {
                ground_right.setPosition(j * 32, i * 32);
                w->draw(ground_right);
            } else if (tileChar == 'D') {
                ground_left2.setPosition(j * 32, i * 32);
                w->draw(ground_left2);
            } else if (tileChar == 'E') {
                ground_mid2.setPosition(j * 32, i * 32);
                w->draw(ground_mid2);
            } else if (tileChar == 'F') {
                ground_right2.setPosition(j * 32, i * 32);
                w->draw(ground_right2);
            } else if (tileChar == 'b') {
                ground_ora.setPosition(j * 32, i * 32);
                w->draw(ground_ora);
            } else if (tileChar == 'R') {
                fire.setTextureRect(sf::IntRect(((int)i_fire % q_fire) * 32, 0, 32, 32));
                fire.setPosition(j * 32, i * 32);
                w->draw(fire);
            } else if (tileChar == 'P') {
                portalP.draw(j * 32, i * 32, w);
            } else if (tileChar == 'Q') {
                portalQ.draw(j * 32, i * 32, w);
            } else if (tileChar == 'G') {
                gate.draw(j * 32, i * 32, w);
            } else if (tileChar == 'K') {
                gatekey.draw(j * 32, i * 32, w);
            } else if (tileChar == 'W') {
                water.draw(j * 32, i * 32, w);
            } else if (tileChar == 'a') {
                water.draw(j * 32, i * 32, w);
            } else if (tileChar == 'd') {
                leafc.draw(j * 32, i * 32, w);
            } else if (tileChar == 'e') {
                leaf1.draw(j * 32, i * 32, w);
            } else if (tileChar == 'f') {
                leaf2.draw(j * 32, i * 32, w);
            } else if (tileChar == 's') {
                leaf3.draw(j * 32, i * 32, w);
            } else if (tileChar == 'h') {
                leaf4.draw(j * 32, i * 32, w);
            } else if (tileChar == 'i') {
                leaf5.draw(j * 32, i * 32, w);
            } else if (tileChar == 'l') {
                leaf6.draw(j * 32, i * 32, w);
            } else if (tileChar == 'm') {
                leaf7.draw(j * 32, i * 32, w);
            } else if (tileChar == 'c') {
                treeLog.draw(j * 32, i * 32, w);
            } else if (tileChar == 'n') {
                treeLogSolid.draw(j * 32, i * 32, w);
            } else if (tileChar == 'w') {
                woodBridge.draw(j * 32, i * 32, w);
            } else if (tileChar == 'X') {
                exitDoorClosed.draw(j * 32, i * 32, w);
                if (exitDoorOpened.i_frame != 0) exitDoorOpened.reset();
            } else if (tileChar == 'x') {
                exitDoorOpened.draw(j * 32, i * 32, w);
                exitDoorOpened.animeAuto();
            }
        }
    }
    gun.anime(sf::IntRect(gun.getFrame() * 32, 0, 32, 32), 1);
    munition.anime(sf::IntRect(munition.getFrame() * 32, 0, 32, 32), 1);
    jetpack.anime(sf::IntRect(jetpack.getFrame() * 32, 0, 32, 32), 1);
    liquor.anime(sf::IntRect(liquor.getFrame() * 32, 0, 32, 32), 1);
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
            if (this->getTileChar(i, j) == 'M') {
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
            if (this->getTileChar(i, j) == a) {
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
void Tilemap::edit_click() {

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
    const char til = this->getTileChar(i, j);
    return til == ' ' || til == '@' || til == '0' || til == '1' || til == '2' || til == '3' || til == '4' || til == '5' || til == '6' || til == '7' || til == '8' || til == '9';
}
bool Tilemap::free_path_water(int i, int j) {
    const char til = this->getTileChar(i, j);
    return til == ' ' || til == 'Z' || til == 'Y';
}
bool Tilemap::free_path_bullet(int i, int j) {
    const char til = this->getTileChar(i, j);
    return til == ' ' || til == '@' || til == 'P' || til == 'Q' || til == 'G' || til == 'X' || til == 'R' || til == '^' || til == 'V' || til == '>' || til == '<' || til == 'M' || til == 'H' || til == 'Z' || til == '#' || til == 'k' || til == 'K' || til == 'g' || til == 'x' || til == 'j' || til == 'L' || til == 'u' || til == 'J' || til == 'Y' || til == '.' || til == 'T' || til == '0' || til == '1' || til == '2' || til == '3' || til == '4' || til == '5' || til == '6' || til == '7' || til == '8' || til == '9' || til == 's' || til == 'h' || til == 'i' || til == 'f' || til == 'd' || til == 'l' || til == 'e' || til == 'd' || til == 'm' || til == 'c' || til == 'n';
}
// char* Tilemap::tile(int i, int j) {
//     if (i >= 0 && i <= this->H && j >= 0 && j <= this->W) {
//         return this->map[i][j];
//     }
//     return new char;
// }
bool Tilemap::is_valid(int i, int j) {
    return (i >= 0 && i < this->H && j >= 0 && j < this->W);
}