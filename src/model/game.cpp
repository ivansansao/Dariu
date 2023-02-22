#include "game.hpp"
#include "iostream"

// Constructor of class
Game::Game()
{
    std::cout << "Inside game.cpp\n";
    window.create(sf::VideoMode(1280, 720), "Dariu - 0.1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));
    window.setMouseCursorVisible(true);
}
void Game::play()
{
}
void Game::pause(){};
void Game::game_over(){};

void Game::loop_events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}
void Game::run()
{
    while (window.isOpen())
    {
        this->loop_events();

        if (this->gameover)
        {
            this->game_over();
        }
        else if (this->paused)
        {
            this->pause();
        }
        else
        {
            this->play();
        }
    }
}