#include "game.hpp"

#include <bits/stdc++.h>

#include <cmath>

#include "iostream"
#include "tools.hpp"

using namespace std;

Game::Game() {
    window.create(sf::VideoMode(800, 600, 32), "Dariu - 0.1", sf::Style::Fullscreen);
    // window.create(sf::VideoMode(1280, 736), "Dariu - 0.1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));
    window.setMouseCursorVisible(true);
    music.openFromFile("./asset/sound/track1.mp3");
    music.setLoop(true);
    music.setVolume(8.f);  // 0 to 100
    music.play();

    music_gameover.openFromFile("./asset/sound/gameover.ogg");
    music_gameover.setVolume(8.f);

    music_gamewin.openFromFile("./asset/sound/gamewin.ogg");
    music_gamewin.setLoop(true);
    music_gamewin.setVolume(8.f);

    view.reset(sf::FloatRect(0.f, 0.f, 1280.f, 736.f));
    gameover = false;
    gameover_loaded = false;

    font_roboto.loadFromFile("./asset/fonts/RobotoFlex-Regular.ttf");
    font_greatvibes.loadFromFile("./asset/fonts/GreatVibes-Regular.ttf");
    std::vector<Inimigo> inimigos;
    std::vector<Catraca> catracas;

    fireworks_tex.loadFromFile("./asset/Free/fireworks.png");
    fireworks_spr.setTexture(fireworks_tex);
    fireworks_i = 0;
    fireworks_j = 0;
}
void Game::play() {
    if (!phase_loaded) {
        load_phase();
    }
    std::stringstream ss;

    auto position = sf::Mouse::getPosition(window);

    this->dariu.update(&tilemap);
    this->tilemap.update();

    for (auto& catraca : catracas) {
        catraca->update(&tilemap);
    }
    check_collisions_enimies();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        dariu.pos = sf::FloatRect(672.f, 672.f, 32.f, 32.f);
    }
    const int width = 800;
    float wLeft = floor((dariu.pos.left) / width) * width;
    if (dariu.pos.left < 2500) {
        if (wLeft < 0) wLeft = 0.f;
        view.reset(sf::FloatRect(wLeft, 0.f, 1280, 736.f));
        dariu.text_score.setPosition(wLeft + 36, 36);
    }

    gamewin = dariu.win;
    gameover = dariu.over;

    window.setView(this->view);

    window.clear(sf::Color(62, 49, 60, 255));
    this->tilemap.draw(&window);
    this->dariu.draw(&window);

    for (auto& catraca : catracas) {
        catraca->draw(&window);
    }

    window.display();
    const float i = dariu.pos.top / 32;
    const float j = dariu.pos.left / 32;

    ss << "Mouse (" << position.x << "," << position.y << ") Dariu (" << dariu.pos.top << "," << dariu.pos.left << ") i/32,j/32 (" << i << " , " << j << ") Bloco da esquerda: " << (int)Tools::floor_special(j + 1, 0.71) << " Bloco da direita: " << (int)Tools::ceil_special(j, 0.39);
    window.setTitle(ss.str());
}
void Game::pause() { music.pause(); };
void Game::game_win() {
    if (!gamewin_loaded) {
        view.reset(sf::FloatRect(0.f, 0.f, 1280, 736.f));
        window.setView(view);
        music.stop();
        music_gamewin.play();
        gamewin_loaded = true;
    }
    window.clear(sf::Color(62, 49, 60, 255));
    text_gamewin.setFont(font_greatvibes);
    text_gamewin.setCharacterSize(60);
    text_gamewin.setFillColor(sf::Color::White);
    text_gamewin.setString(L"Parabéns, você ganhou!!!");
    // int a = window.getSize().x;
    // int b = window.getSize().y;
    // int c = text_gamewin.getGlobalBounds().width;
    // int d = text_gamewin.getGlobalBounds().height;
    // cout << "a: " << a << " b: " << b << " c: " << c << " d: " << d << endl;

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

    // Show congratulations

    text_gamewin.setPosition(sf::Vector2f(600 - text_gamewin.getGlobalBounds().width / 2, window.getSize().y / 2 - text_gamewin.getGlobalBounds().height / 2));

    window.draw(fireworks_spr);
    window.draw(text_gamewin);
    window.display();
};
void Game::game_over() {
    if (!gameover_loaded) {
        view.reset(sf::FloatRect(0.f, 0.f, 1280, 736.f));
        window.setView(view);
        music.stop();
        music_gameover.play();
        gameover_loaded = true;
    }
    window.clear(sf::Color(62, 49, 60, 255));
    text_gameover.setFont(font_roboto);
    text_gameover.setCharacterSize(60);
    text_gameover.setFillColor(sf::Color::White);
    text_gameover.setString(L"VOCÊ PERDEU!");
    text_gameover.setPosition(sf::Vector2f(600 - text_gameover.getGlobalBounds().width / 2, window.getSize().y / 2 - text_gameover.getGlobalBounds().height / 2));
    window.draw(text_gameover);
    window.display();
};

void Game::loop_events() {
    sf::Event event;
    sf::Clock clock;
    while (window.pollEvent(event)) {
        // float time = clock.getElapsedTime().asMicroseconds();
        // clock.restart();
        // time = time / 800;

        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (playing) {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
                this->dariu.up_released = true;
            }
        }
    }
}

bool Game::is_fullscreen() {
    return window.getSize().x == sf::VideoMode::getDesktopMode().width;
}

void Game::load_phase() {
    phase_loaded = true;

    tilemap.load_from_file(1);

    load_enimy_catracas();

    // Read quantity of bananas from tilemap.
    dariu.score.bananas_total = 0;
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.map[i][j] == '0') {
                dariu.score.bananas_total += 1;
            }
        }
    }
    // Read quantity of bananas from thophys.
    dariu.score.thophy_total = 0;
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.map[i][j] == 'T') {
                dariu.score.thophy_total += 1;
            }
        }
    }

    cout << "Fase carregada!\n";
}
void Game::load_enimy_catracas() {
    for (int i{}; i < tilemap.H; ++i) {
        for (int j{}; j < tilemap.W; j++) {
            if (tilemap.enimies[i][j] == 'Z') {
                cout << "Encontrou um Enimy em: " << i << "," << j << endl;
                Catraca* catraca = new Catraca();
                catraca->pos.top = i * 32;
                catraca->pos.left = j * 32;
                catracas.push_back(catraca);
            }
        }
    }
};

void Game::check_collisions_enimies() {
    for (auto& catraca : catracas) {
        if (catraca->pos.intersects(dariu.pos)) {
            cout << "BATERAMMMMMMM\n";
            dariu.die();
        }
    }
}

void Game::run() {
    playing = true;
    while (window.isOpen()) {
        this->loop_events();

        if (this->gameover) {
            this->game_over();
        } else if (this->gamewin) {
            this->game_win();
        } else if (this->paused) {
            this->pause();
        } else {
            this->play();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            window.close();
        }
    }
}