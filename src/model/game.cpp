#include "game.hpp"

#include <bits/stdc++.h>

#include "iostream"

using namespace std;

Game::Game() {
    window.create(sf::VideoMode(1280, 736), "Dariu - 0.1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));
    window.setMouseCursorVisible(true);

    if (music.openFromFile("./asset/track1.mp3")) {  // Accept 16 bits, convert to OGG on Vlc!
        std::cout << "Yep for the music!\n";
    } else {
        std::cout << "Given sheet for the music!\n";
    }
    music.setVolume(4.f);  // 0 to 100

    view.reset(sf::FloatRect(0.f, 0.f, 1280.f, 736.f));
}
void Game::play() {
    std::stringstream ss;

    auto position = sf::Mouse::getPosition(window);

    this->dariu.update(&tilemap);
    this->tilemap.update();
    // const float LERP_SPEED = 0.1f;
    // sf::Vector2f targetPosition = sf::Vector2f(dariu.pos.left, 736 / 2) + sf::Vector2f(dariu.pos.left / 2, 736 / 2);
    // view.setCenter(view.getCenter() + (targetPosition - view.getCenter()) * LERP_SPEED);
    view.setCenter(dariu.pos.left, 736 / 2);

    window.setView(this->view);

    window.clear(sf::Color(62, 49, 60, 255));
    this->tilemap.draw(&window);
    this->dariu.draw(&window);
    window.display();
    ss << "Mouse (" << position.x << "," << position.y << ") Dariu TL (" << dariu.pos.top << "," << dariu.pos.left << ") H: " << dariu.pos.height << " W: " << dariu.pos.width;
    window.setTitle(ss.str());
}
void Game::pause() { music.pause(); };
void Game::game_over() { music.stop(); };

void Game::loop_events() {
    sf::Event event;
    sf::Clock clock;

    if (music.getStatus() == sf::Music::Stopped || music.getStatus() == sf::Music::Paused) {
        music.openFromFile("./asset/track1.mp3");
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            window.close();
        }
    }
}