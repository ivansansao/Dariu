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
    gameover_trigged = false;
    font_roboto.loadFromFile("./asset/fonts/RobotoFlex-Regular.ttf");
    font_greatvibes.loadFromFile("./asset/fonts/GreatVibes-Regular.ttf");
    std::vector<Inimigo> inimigos;
    std::vector<Catraca> catracas;
}
void Game::play() {
    std::stringstream ss;

    auto position = sf::Mouse::getPosition(window);

    this->dariu.update(&tilemap);
    this->tilemap.update();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        dariu.pos = sf::FloatRect(672.f, 672.f, 32.f, 32.f);
    }
    const int width = 800;
    float wLeft = floor((dariu.pos.left) / width) * width;
    if (dariu.pos.left < 2500) {
        if (wLeft < 0) wLeft = 0.f;
        view.reset(sf::FloatRect(wLeft, 0.f, 1280, 736.f));
        dariu.text_score.setPosition(wLeft + 8, 6);
    }

    gamewin = dariu.win;
    gameover = dariu.over;

    window.setView(this->view);

    window.clear(sf::Color(62, 49, 60, 255));
    this->tilemap.draw(&window);
    this->dariu.draw(&window);
    window.display();
    const float i = dariu.pos.top / 32;
    const float j = dariu.pos.left / 32;

    ss << "Mouse (" << position.x << "," << position.y << ") Dariu (" << dariu.pos.top << "," << dariu.pos.left << ") i/32,j/32 (" << i << " , " << j << ") Bloco da esquerda: " << (int)Tools::floor_special(j + 1, 0.71) << " Bloco da direita: " << (int)Tools::ceil_special(j, 0.39);
    window.setTitle(ss.str());
}
void Game::pause() { music.pause(); };
void Game::game_win() {
    if (!gamewin_trigged) {
        view.reset(sf::FloatRect(0.f, 0.f, 1280, 736.f));
        window.setView(view);
        music.stop();
        music_gamewin.play();
        gamewin_trigged = true;
    }
    window.clear(sf::Color(62, 49, 60, 255));
    text_gamewin.setFont(font_greatvibes);
    text_gamewin.setCharacterSize(60);
    text_gamewin.setFillColor(sf::Color::White);
    text_gamewin.setString("Parabens, voce ganhou!!!");
    // int a = window.getSize().x;
    // int b = window.getSize().y;
    // int c = text_gamewin.getGlobalBounds().width;
    // int d = text_gamewin.getGlobalBounds().height;
    // cout << "a: " << a << " b: " << b << " c: " << c << " d: " << d << endl;

    text_gamewin.setPosition(sf::Vector2f(600 - text_gamewin.getGlobalBounds().width / 2, window.getSize().y / 2 - text_gamewin.getGlobalBounds().height / 2));

    window.draw(text_gamewin);
    window.display();
};
void Game::game_over() {
    if (!gameover_trigged) {
        view.reset(sf::FloatRect(0.f, 0.f, 1280, 736.f));
        window.setView(view);
        music.stop();
        music_gameover.play();
        gameover_trigged = true;
    }
    window.clear(sf::Color(62, 49, 60, 255));
    text_gameover.setFont(font_roboto);
    text_gameover.setCharacterSize(60);
    text_gameover.setFillColor(sf::Color::White);
    text_gameover.setString("GAME OVER!");
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

void Game::run() {
    Inimigo s1;
    Inimigo s2;
    Inimigo s3;
    s1.idade = 35;
    s2.idade = 36;
    s3.idade = 37;
    inimigos.push_back(s1);
    inimigos.push_back(s2);
    inimigos.push_back(s3);

    for (auto& e : inimigos) {
        cout << e.idade << endl;
    }

    // Catraca c1;
    // Catraca c2;
    // Catraca c3;
    // c1.idade = 45;
    // c2.idade = 46;
    // c3.idade = 47;
    // catracas.push_back(c1);
    // catracas.push_back(c2);
    // catracas.push_back(c3);

    // for (auto& e : catracas) {
    //     cout << e.idade << endl;
    // }

    Catraca* t1 = new Catraca();
    t1->idade = 45;
    t1->name = "Bigorna";

    Catraca* t2 = new Catraca();
    t2->idade = 80;
    t2->name = "Ferruga";

    catas.push_back(t1);
    catas.push_back(t2);

    for (auto& e : catas) {
        cout << e->idade << " name: " << e->name << endl;
    }

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