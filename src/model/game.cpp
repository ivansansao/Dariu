#include "game.hpp"

#include <bits/stdc++.h>

#include "iostream"

using namespace std;

Game::Game() {
    window.create(sf::VideoMode(1280, 736), "Dariu - 0.1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));
    window.setMouseCursorVisible(true);
    music.openFromFile("./asset/sound/track1.mp3");
    music.setLoop(true);
    music.setVolume(8.f);  // 0 to 100
    music.play();
    view.reset(sf::FloatRect(0.f, 0.f, 1280.f, 736.f));
}
void Game::play() {
    std::stringstream ss;

    auto position = sf::Mouse::getPosition(window);

    this->dariu.update(&tilemap);
    this->tilemap.update();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        dariu.pos = sf::FloatRect(700.f, 100.f, 32.f, 32.f);
    }

    if (dariu.pos.left > 900.f && dariu.pos.left < 2560.f) {
        view.setCenter(dariu.pos.left, 736 / 2);
    }

    window.setView(this->view);

    window.clear(sf::Color(62, 49, 60, 255));
    this->tilemap.draw(&window);
    this->dariu.draw(&window);
    window.display();
    ss << "Mouse (" << position.x << "," << position.y << ") Dariu TL (" << dariu.pos.top << "," << dariu.pos.left << ") / 32 = " << dariu.pos.left / 32;
    // window.setTitle(ss.str());
}
void Game::pause() { music.pause(); };
void Game::game_over() { music.stop(); };

void Game::loop_events() {
    if (music.getStatus() == sf::Music::Stopped || music.getStatus() == sf::Music::Paused) {
        // Accept 16 bits, convert to OGG on Vlc!
        // music.openFromFile("./asset/sound/track1.mp3");
        // music.play();
        cout << "Try play music...\n";
    }

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

void Game::run() {
    playing = true;
    while (window.isOpen()) {
        this->loop_events();

        if (this->gameover) {
            this->game_over();
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