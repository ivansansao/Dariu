#include "game.hpp"

#include <bits/stdc++.h>

#include "iostream"

Game::Game() {
    window.create(sf::VideoMode(1280, 736), "Dariu - 0.1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));
    window.setMouseCursorVisible(true);

    music.openFromFile("./asset/soundtrack.wav");
    music.setVolume(4.f);  // 0 to 100

    view.reset(sf::FloatRect(0.f, 0.f, 1280.f, 736.f));
}
void Game::play() {
    std::stringstream ss;

    auto position = sf::Mouse::getPosition(window);

    this->dariu.update();
    this->tilemap.update();
    // this->view.move(1.f, 0.f);
    if (dariu.pos.x > 800) {
    }
    view.setCenter(dariu.pos.x, 736 / 2);
    window.setView(this->view);

    window.clear(sf::Color(62, 49, 60, 255));
    this->tilemap.draw(&window);
    this->dariu.draw(&window);
    window.display();
    ss << "Mouse (" << position.x << "," << position.y << ") Dariu (" << dariu.pos.x << "," << dariu.pos.y << ")";
    window.setTitle(ss.str());
}
void Game::pause() { music.pause(); };
void Game::game_over() { music.stop(); };

void Game::loop_events() {
    sf::Event event;
    sf::Clock clock;

    if (music.getStatus() == sf::Music::Stopped || music.getStatus() == sf::Music::Paused) {
        music.play();
    }

    while (window.pollEvent(event)) {
        // float time = clock.getElapsedTime().asMicroseconds();
        // clock.restart();
        // time = time / 800;

        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::run() {
    while (window.isOpen()) {
        this->loop_events();

        if (this->gameover) {
            this->game_over();
        } else if (this->paused) {
            this->pause();
        } else {
            this->play();
        }
    }
}