#include "game.hpp"
#include "iostream"

// Constructor of class
Game::Game()
{
    std::cout << "Inside game.cpp constructor\n";
    window.create(sf::VideoMode(1280, 720), "Dariu - 0.1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));
    window.setMouseCursorVisible(true);

    music.openFromFile("./asset/soundtrack.wav");
    music.setVolume(8.f); // 0 to 100
}
void Game::play()
{
    this->dariu.update();

    window.clear();
    this->dariu.draw(&window);
    window.display();
}
void Game::pause()
{
    music.pause();
};
void Game::game_over()
{
    music.stop();
};

void Game::loop_events()
{
    sf::Event event;
    if (music.getStatus() == sf::Music::Stopped || music.getStatus() == sf::Music::Paused)
    {
        std::cout << "Play a " << music.getStatus() << "\n";
        music.play();
        std::cout << "Play b " << music.getStatus() << "\n";
    }
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        ham.setPosition(sf::Vector2f(500.f, 500.f));
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