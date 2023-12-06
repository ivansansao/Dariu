#include "game.hpp"

#include <bits/stdc++.h>
#include <dirent.h>

#include <cmath>

#include "iostream"
#include "tools.hpp"

using namespace std;

Game::Game() {
    bool fullscreen = true;
    if (std::getenv("DARIU_FULLSCREEN")) {
        fullscreen = (std::string)std::getenv("DARIU_FULLSCREEN") == "1";
    }

    if (fullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), "Dariu", sf::Style::Fullscreen);
    } else {
        window.create(sf::VideoMode(1280, 736), "Dariu", sf::Style::Titlebar | sf::Style::Close);
    }
    // window.UseVerticalSync(false);
    window.setVerticalSyncEnabled(true);  // Don't allow more FPS than your monitor support.
    window.setFramerateLimit(60);         // There is a relation between framerate and setVerticalSyncEnabled.

    window.setPosition(sf::Vector2i(0, 0));

    view.reset(sf::FloatRect(0.f, 0.f, 1280.f, 736.f));
    gameover_loaded = false;

    font_roboto.loadFromFile("./src/asset/fonts/RobotoFlex-Regular.ttf");
    font_greatvibes.loadFromFile("./src/asset/fonts/GreatVibes-Regular.ttf");
    std::vector<Catraca> catracas;

    fireworks_tex.loadFromFile("./src/asset/image/fireworks.png");
    fireworks_spr.setTexture(fireworks_tex);
    fireworks_i = 0;
    fireworks_j = 0;
    window.setMouseCursorVisible(false);
    if (std::getenv("DARIU_EDITING")) {
        editing = (std::string)std::getenv("DARIU_EDITING") == "1";
        window.setMouseCursorVisible(editing);
    }
    if (std::getenv("DARIU_VOLUME_MUSIC")) {
        const int vol_music = std::stoi(std::getenv("DARIU_VOLUME_MUSIC"));
        sounds.volume_music = vol_music;
    }
    if (std::getenv("DARIU_VOLUME_EFFECT")) {
        const int vol_effect = std::stoi(std::getenv("DARIU_VOLUME_EFFECT"));
        sounds.volume_effect = vol_effect;
    }
    sounds.applyVolume();
}

std::string Game::menuopc[menuopc_size] = {"Jogar",
                                           "Volume ambiente",
                                           "Volume de efeitos",
                                           "Iniciar do zero (y)",
                                           "Sair"};
enum menuopcs { Play,
                Env_volumn,
                Effects_volumn,
                Reset,
                Exit };

void Game::play() {
    if (!this->game_loaded) {
        load();
        phase_current = (int)profile.completed_phases + 1;
        load_phase();
    }
    std::stringstream ss;

    if (this->editing) {
        if ((editing_framecount % 60) == 0) {
            this->tilemap.load_from_file(this->phase_current);
        }
        editing_framecount++;
    }

    this->dariu.update(&tilemap, &sounds);
    this->tilemap.update();

    for (auto& catraca : catracas) {
        catraca->update(&tilemap, &sounds);
    }
    for (auto& sova : sovas) {
        sova->update(&tilemap, &sounds);
    }

    int i1 = 0;
    for (auto& cannon : cannons) {
        cannon->update(&tilemap, &sounds);
        bulletcs[i1]->update(&tilemap);
        bulletcs[i1]->start_pos.left = cannons[i1]->pos.left;
        bulletcs[i1]->start_pos.top = cannons[i1]->pos.top;
        if (cannons[i1]->pos.left == bulletcs[i1]->pos.left) {
            if (dariu.pos.left > cannons[i1]->pos.left)
                bulletcs[i1]->direction_x = 1;
            else
                bulletcs[i1]->direction_x = -1;
        }

        i1++;
    }

    check_collisions_enimies();

    // const int tiles_at_right = tilemap.W - (dariu.pos.left / dariu.pos.width);

    // if (tiles_at_right > 14) {
    //     // Width 40 tiles x 32 = 1280 per page
    //     // 115 tiles x 32 = 3680
    //     const int width = 800;
    //     float wLeft = floor((dariu.pos.left) / width) * width;
    //     dariu.text_score.setPosition(wLeft + 7, 7);
    //     if (dariu.pos.left < 2500) {
    //         if (wLeft < 0) wLeft = 0.f;
    //         view.reset(sf::FloatRect(wLeft, 0.f, 1280, 736.f));
    //     } else {
    //         view.reset(sf::FloatRect(2400.f, 0.f, 1280, 736.f));
    //     }
    // } else {
    //     if (dariu.pos.left > 2000) {
    //         view.reset(sf::FloatRect(2400.f, 0.f, 1280, 736.f));
    //     }
    // }

    // Test new behivier from screen.

    if (dariu.pos.left > 2496) {
        view.reset(sf::FloatRect(2496.f, 0.f, 1280, 736.f));
        dariu.text_score.setPosition(2496.f + 7, 7);
    } else if (dariu.pos.left > 1248) {
        dariu.text_score.setPosition(1248.f + 7, 7);
        view.reset(sf::FloatRect(1248.f, 0.f, 1280, 736.f));
    } else {
        dariu.text_score.setPosition(0.f + 7, 7);
        view.reset(sf::FloatRect(0.f, 0.f, 1280, 736.f));
    }

    if (dariu.win) {
        page = pages::GAME_WIN;
    } else if (dariu.over) {
        page = pages::GAME_OVER;
    }

    if (page == pages::GAME_WIN) {
        save_profile_if_good();
        if (phase_current < phase_total) {
            phase_current++;
            page = pages::GAME_PLAY;
            dariu.win = false;
            dariu.reset_position();
            load_phase();
        }
    }
    window.setView(this->view);

    window.clear(sf::Color(62, 49, 60, 255));
    this->tilemap.draw(&window);
    this->dariu.draw(&window, phase_current, phase_total);

    for (auto& catraca : catracas) {
        catraca->draw(&window);
    }
    for (auto& sova : sovas) {
        sova->draw(&window);
    }
    for (auto& bulletc : bulletcs) {
        bulletc->draw(&window);
    }
    for (auto& cannon : cannons) {
        cannon->draw(&window);
    }

    // window.setMouseCursorVisible(false);

    // auto mouse = sf::Mouse::getPosition(window);
    // const float i = dariu.pos.top / 32;
    // const float j = dariu.pos.left / 32;
    // ss << "Mouse (" << position.x << "," << position.y << ") Dariu (" << dariu.pos.top << "," << dariu.pos.left << ") i/32,j/32 (" << i << " , " << j << ") Bloco da esquerda: " << (int)Tools::floor_special(j + 1, 0.71) << " Bloco da direita: " << (int)Tools::ceil_special(j, 0.39);
    // ss << "Mouse (" << mouse.x << "," << mouse.y << ") " << mouse.x / 32 << tilemap.map[mouse.y / 32][mouse.x / 32];
    // window.setTitle(ss.str());
    // sf::RectangleShape rectangle;
    // rectangle.setSize(sf::Vector2f(1, 1));
    // rectangle.setOutlineColor(sf::Color::Red);
    // // rectangle.setOutlineThickness(5);
    // rectangle.setPosition(mouse.x, mouse.y);
    // window.draw(rectangle);

    window.display();
}

void Game::resume() {
    sounds.music.play();
    gamepause_loaded = false;
    page = pages::GAME_PLAY;
};
void Game::reset() {
    this->profile.lifes = 10;
    this->profile.completed_phases = 0;
    this->profile.seconds_playing = 0;
    this->phase_current = 0;
    this->game_loaded = false;
    this->save_profile(0);
};
void Game::close() {
    window.close();
};
void Game::win() {
    if (!gamewin_loaded) {
        view.reset(sf::FloatRect(0.f, 0.f, 1280, 736.f));
        window.setView(view);
        sounds.music.stop();
        sounds.music_gamewin.play();

        gamewin_loaded = true;
    }
    window.clear(sf::Color(62, 49, 60, 255));
    text_gamewin.setFont(font_greatvibes);
    text_gamewin.setCharacterSize(60);
    text_gamewin.setFillColor(sf::Color::White);
    text_gamewin.setString(L"Parabéns, você ganhou!!!");
    text_gamewin.setPosition(sf::Vector2f(600 - text_gamewin.getGlobalBounds().width / 2, window.getSize().y / 2 - text_gamewin.getGlobalBounds().height / 2));
    window.draw(text_gamewin);

    text_gamewin.setFont(font_roboto);
    text_gamewin.setCharacterSize(16);
    text_gamewin.setFillColor(sf::Color::White);
    text_gamewin.setString(L"V - Voltar ao menu");
    text_gamewin.setPosition(sf::Vector2f(600 - text_gamewin.getGlobalBounds().width / 2, window.getSize().y / 2 - text_gamewin.getGlobalBounds().height / 2 + 120));
    window.draw(text_gamewin);

    // Show fireworks

    fireworks_spr.setPosition(500, 100);
    fireworks_spr.setTextureRect(sf::IntRect((int)fireworks_j * 256, (int)fireworks_i * 256, 256, 256));
    fireworks_j += 0.3;
    if ((int)fireworks_j > 5) {
        fireworks_j = 0;
        fireworks_i += 1;
    }
    if ((int)fireworks_i > 10) {
        fireworks_j = 0;
        fireworks_i = 0;
    }

    window.draw(fireworks_spr);

    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
        gamewin_loaded = false;
        sounds.music_gamewin.stop();
        game_loaded = false;
        menumain_loaded = false;
        phase_current = 0;
        this->dariu.score.darius = 10;
        this->dariu.score.bananas = 0;
        this->dariu.score.thophy = 0;
        this->dariu.over = false;
        this->dariu.win = false;
        this->dariu.jetPackFuel = 0;
        page = pages::MENU_MAIN;
    }
};
void Game::over() {
    if (!gameover_loaded) {
        view.reset(sf::FloatRect(0.f, 0.f, 1280, 736.f));
        window.setView(view);
        sounds.music.stop();
        sounds.music_gameover.play();
        gameover_loaded = true;
    }
    window.clear(sf::Color(62, 49, 60, 255));
    text_gameover.setFont(font_roboto);
    text_gameover.setCharacterSize(60);
    text_gameover.setFillColor(sf::Color::White);
    text_gameover.setString(L"VOCÊ PERDEU!");
    text_gameover.setPosition(sf::Vector2f(600 - text_gameover.getGlobalBounds().width / 2, window.getSize().y / 2 - text_gameover.getGlobalBounds().height / 2));
    window.draw(text_gameover);

    text_gameover.setFont(font_roboto);
    text_gameover.setCharacterSize(16);
    text_gameover.setFillColor(sf::Color::White);
    text_gameover.setString(L"V - Voltar ao menu");
    text_gameover.setPosition(sf::Vector2f(600 - text_gameover.getGlobalBounds().width / 2, window.getSize().y / 2 - text_gameover.getGlobalBounds().height / 2 + 120));
    window.draw(text_gameover);

    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
        gameover_loaded = false;
        sounds.music_gameover.stop();
        game_loaded = false;
        menumain_loaded = false;
        phase_current = 0;
        this->dariu.score.darius = 10;
        this->dariu.score.bananas = 0;
        this->dariu.score.thophy = 0;
        this->dariu.over = false;
        this->dariu.win = false;
        this->dariu.jetPackFuel = 0;
        page = pages::MENU_MAIN;
    }
};
void Game::load() {
    game_loaded = true;

    // Start time
    starttime_play = std::chrono::high_resolution_clock::now();

    // Read total phases in the game

    phase_total = 0;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir("./src/resource")) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            if (std::string(ent->d_name).find("map_") != std::string::npos) {
                phase_total++;
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Could not open directory" << std::endl;
    }
}
bool Game::is_fullscreen() {
    return window.getSize().x == sf::VideoMode::getDesktopMode().width;
}

void Game::load_phase() {
    tilemap.clear();
    tilemap.load_from_file(phase_current);
    tilemap.load_plataforms();

    load_enimies();

    // dariu.score.bananas = 0;
    dariu.score.thophy = 0;
    dariu.jetPack = false;
    dariu.jetPackFuel = 0;

    // Read quantity of bananas from tilemap.
    dariu.score.bananas_total = 0;
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.getTileChar(i, j) == '.') {
                dariu.score.bananas_total += 1;
            }
        }
    }
    // Read quantity of thophys from tilemap.
    dariu.score.thophy_total = 0;
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.getTileChar(i, j) == 'T') {
                dariu.score.thophy_total += 1;
            }
        }
    }
    // Search for start position of Dariu
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.getTileChar(i, j) == '@') {
                dariu.set_position(j * 32, i * 32);
                break;
            }
        }
    }
}
void Game::load_enimies() {
    catracas.clear();
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.getTileChar(i, j) == 'Z') {
                Catraca* catraca = new Catraca();
                catraca->set_position(j * 32, i * 32);
                catracas.push_back(catraca);
            }
        }
    }
    sovas.clear();
    int id = 0;
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.getTileChar(i, j) == 'Y') {
                Sova* sova = new Sova();
                sova->set_position(j * 32, i * 32);
                sova->id = ++id;
                sova->jetPack = false;
                sova->jetPackFuel = 0;
                sovas.push_back(sova);
            }
        }
    }
    cannons.clear();
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.getTileChar(i, j) == 'H') {
                Cannon* cannon = new Cannon();
                cannon->set_position(j * 32, i * 32);
                cannons.push_back(cannon);
            }
        }
    }
    bulletcs.clear();
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.getTileChar(i, j) == 'H') {
                Bulletc* bulletc = new Bulletc();
                bulletc->set_position(j * 32, i * 32);
                bulletcs.push_back(bulletc);
            }
        }
    }
};

void Game::check_collisions_enimies() {
    if (dariu.is_alive()) {
        bool dariuJump = false;

        for (auto& catraca : catracas) {
            if (catraca->is_alive()) {
                if (catraca->pos.intersects(dariu.pos)) {
                    if (dariu.velocity.y > 0) {
                        dariuJump = true;
                        catraca->die(&tilemap, &sounds);
                    } else {
                        if (!this->editing) dariu.die(&tilemap, &sounds);
                    }
                }
                for (auto& bullet : dariu.bulletguns) {
                    if (bullet->pos.intersects(catraca->pos)) {
                        bullet->collided = true;
                        catraca->die(&tilemap, &sounds);
                    }
                }
            }
        }

        for (auto& sova : sovas) {
            if (sova->is_alive()) {
                if (sova->pos.intersects(dariu.pos)) {
                    if (dariu.velocity.y > 0) {
                        dariuJump = true;
                        sova->die(&tilemap, &sounds);
                    } else {
                        if (!this->editing) dariu.die(&tilemap, &sounds);
                    }
                }
                for (auto& bullet : sova->bulletguns) {
                    if (bullet->pos.intersects(dariu.pos)) {
                        if (!this->editing) dariu.die(&tilemap, &sounds);
                    }
                }
                for (auto& bullet : dariu.bulletguns) {
                    if (bullet->pos.intersects(sova->pos)) {
                        bullet->collided = true;
                        sova->die(&tilemap, &sounds);
                    }
                }
            }
        }
        for (auto& bulletc : bulletcs) {
            if (bulletc->is_alive()) {
                if (bulletc->pos.intersects(dariu.pos)) {
                    if (dariu.velocity.y > 0) {
                        dariuJump = true;
                        bulletc->die(&tilemap, &sounds);
                    } else {
                        if (!this->editing) dariu.die(&tilemap, &sounds);
                    }
                }
                for (auto& bullet : dariu.bulletguns) {
                    if (bullet->pos.intersects(bulletc->pos)) {
                        bullet->collided = true;
                        bulletc->die(&tilemap, &sounds);
                    }
                }
            }
        }

        if (dariuJump) dariu.jump();
    }
}
void Game::pause(){};
void Game::save_profile_if_good() {
    this->endtime_play = std::chrono::high_resolution_clock::now();
    int seconds_playing = Tools::time_dif_in_seconds(this->starttime_play, this->endtime_play);

    int save = false;

    if (phase_current > profile.completed_phases) {
        save = true;
    } else if (phase_current == profile.completed_phases) {
        if (seconds_playing < profile.seconds_playing) {
            save = true;
        }
    }

    if (save) {
        this->save_profile(seconds_playing);
    }
}
void Game::save_profile(int seconds_playing) {
    ofstream MyFile("./src/resource/profile.dat");
    MyFile << "completed_phases:" + to_string(phase_current) << endl;
    MyFile << "lifes:" + to_string(dariu.score.darius) << endl;
    MyFile << "seconds_playing:" + to_string(seconds_playing) << endl;
    MyFile.close();
}
void Game::load_profile() {
    int i;
    string line;
    ifstream file("./src/resource/profile.dat");
    i = 0;
    while (getline(file, line)) {
        if (line.find("completed_phases") != std::string::npos) {
            profile.completed_phases = stoi(line.substr(line.find(":") + 1, 80));
        } else if (line.find("lifes") != std::string::npos) {
            profile.lifes = stoi(line.substr(line.find(":") + 1, 80));
        } else if (line.find("seconds_playing") != std::string::npos) {
            profile.seconds_playing = stoi(line.substr(line.find(":") + 1, 80));
        }
        i++;
    }
    file.close();
}
void Game::menu_main() {
    if (!menumain_loaded) {
        menumain_loaded = true;
        sounds.music.pause();
        view.reset(sf::FloatRect(0.f, 0.f, 1280.f, 736.f));
        window.setView(view);
        text_generic.setFont(font_greatvibes);
        text_generic.setFillColor(sf::Color::White);
        load_profile();
    }

    // Update

    if (key_released) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sounds.jump_sound.play();
            menuopc_selected--;
            if (menuopc_selected < 0) {
                menuopc_selected = menuopc_size - 1;
            }
            key_released = false;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sounds.jump_sound.play();
            menuopc_selected++;
            if (menuopc_selected > menuopc_size - 1) menuopc_selected = 0;
            key_released = false;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (menuopc_selected == menuopcs::Env_volumn) {
                sounds.music_up();
                menuopc[1] = "Volume ambiente " + to_string((int)sounds.volume_music);
            } else if (menuopc_selected == menuopcs::Effects_volumn) {
                sounds.effect_up();
                menuopc[2] = "Volume de efeitos " + to_string((int)sounds.volume_effect);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (menuopc_selected == menuopcs::Env_volumn) {
                sounds.music_down();
                menuopc[1] = "Volume ambiente " + to_string((int)sounds.volume_music);
            } else if (menuopc_selected == menuopcs::Effects_volumn) {
                sounds.effect_down();
                menuopc[2] = "Volume de efeitos " + to_string((int)sounds.volume_effect);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            if (menuopc_selected == menuopcs::Reset) {
                this->reset();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (menuopc_selected == menuopcs::Play) {
                page = pages::GAME_RESUME;
                menumain_loaded = false;
            } else if (menuopc_selected == menuopcs::Exit) {
                window.close();
            }
        }
    }

    if (menuopc_selected == menuopcs::Env_volumn) {
        if (sounds.music.getStatus() == sf::Music::Paused || sounds.music.getStatus() == sf::Music::Stopped)
            sounds.music.play();
    } else {
        if (sounds.music.getStatus() == sf::Music::Playing)
            sounds.music.pause();
    }

    // Draw

    window.clear(sf::Color(62, 49, 60, 255));
    text_generic.setFont(font_greatvibes);
    text_generic.setCharacterSize(60);

    int i = 0;
    int offset_y = 200;
    int top = 0;
    int left = 0;
    int line = 2;

    text_generic.setString("Dariu");
    left = 600 - text_generic.getGlobalBounds().width / 2;
    text_generic.setPosition(sf::Vector2f(left, 32));
    window.draw(text_generic);

    for (auto opc : menuopc) {
        top = offset_y + (i * 100);
        if (menuopc_selected == i)
            text_generic.setString("[  " + opc + "  ]");
        else
            text_generic.setString("   " + opc + "   ");
        left = 600 - text_generic.getGlobalBounds().width / 2;
        text_generic.setPosition(sf::Vector2f(left, top));
        window.draw(text_generic);
        i++;
    }

    // Profile

    text_generic.setFont(font_roboto);
    text_generic.setCharacterSize(32);

    text_generic.setString("Meu recorde:");
    left = 600 + 350;
    top = 64;
    text_generic.setPosition(sf::Vector2f(left, top));
    window.draw(text_generic);

    text_generic.setFont(font_roboto);
    text_generic.setCharacterSize(22);

    text_generic.setString("Fases: " + to_string(profile.completed_phases));
    top = 64 + (40 * line++);
    text_generic.setPosition(sf::Vector2f(left, top));
    window.draw(text_generic);

    text_generic.setString("Vidas: " + to_string(profile.lifes));
    top = 64 + (40 * line++);
    text_generic.setPosition(sf::Vector2f(left, top));
    window.draw(text_generic);

    text_generic.setString("Tempo: " + Tools::seconds_to_hour(profile.seconds_playing));
    top = 64 + (40 * line++);
    text_generic.setPosition(sf::Vector2f(left, top));
    window.draw(text_generic);

    window.display();
}

void Game::loop_events() {
    sf::Event event;
    sf::Clock clock;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyReleased || event.type == sf::Event::JoystickButtonReleased) {
            key_released = true;
            this->dariu.key_released = true;

            if (event.key.code == sf::Keyboard::Escape) {
                if (page == pages::GAME_PLAY) {
                    page = pages::MENU_MAIN;
                }
            } else if (event.key.code == sf::Keyboard::Up) {
                this->dariu.up_released = true;
            } else if (event.key.code == sf::Keyboard::Z) {
                this->dariu.z_released = true;
            } else if (event.key.code == sf::Keyboard::LControl) {
                this->dariu.lcontroll_released = true;
            } else if (event.key.code == sf::Keyboard::Numpad0) {
                this->dariu.zerokey_released = true;
            } else if (event.key.code == sf::Keyboard::Space) {
                this->dariu.space_released = true;
            }

            if (event.type == sf::Event::JoystickButtonReleased) {
                this->dariu.up_released = true;
                this->dariu.z_released = true;
                this->dariu.space_released = true;
                this->dariu.lcontroll_released = true;
                this->dariu.zerokey_released = true;
            }
            if (1) {
                if (event.key.code == sf::Keyboard::PageUp) {
                    window.setVerticalSyncEnabled(false);  // Don't allow more FPS than your monitor support.
                    window.setFramerateLimit(0);
                    sounds.jump_sound.play();
                    std::cout << "Sincronismo vertical desativado!" << std::endl;
                } else if (event.key.code == sf::Keyboard::PageDown) {
                    window.setVerticalSyncEnabled(true);  // Don't allow more FPS than your monitor support.
                    window.setFramerateLimit(60);
                    sounds.jump_sound.play();
                    std::cout << "Sincronismo vertical ativado!" << std::endl;
                }
            }
        }
    }
}

void Game::run() {
    while (window.isOpen()) {
        this->loop_events();

        if (this->page == pages::GAME_PLAY) {
            this->play();
        } else if (this->page == pages::GAME_OVER) {
            this->over();
        } else if (this->page == pages::GAME_WIN) {
            this->win();
        } else if (this->page == pages::GAME_PAUSE) {
            this->pause();
        } else if (this->page == pages::GAME_RESUME) {
            this->resume();
        } else if (this->page == pages::GAME_CLOSE) {
            this->close();
        } else if (this->page == pages::MENU_MAIN) {
            this->menu_main();
        }
    }
}