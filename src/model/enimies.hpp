#pragma once

#ifndef ENIMIES_HPP
#define ENIMIES_HPP

#include "actor.hpp"
#include "tools.hpp"

class Enimy : public Actor {
   public:
    Enimy();
    sf::SoundBuffer enimydie;
    sf::Sound enimydie_sound;
    // Override
    void update(Tilemap *tilemap);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
    void die();
};
class Catraca : public Enimy {
   public:
    Catraca();

    // Override
    void update(Tilemap *tilemap);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
    void die();
};
class Sova : public Enimy {
   public:
    Sova();

    // Override
    void update(Tilemap *tilemap);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
    void die();
};
class Cannon : public Enimy {
   public:
    Cannon();

    // Override
    void update(Tilemap *tilemap);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
    void die();
};
class Bulletc : public Enimy {
   public:
    Bulletc();

    // Override
    void update(Tilemap *tilemap);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
    void die();
};

#endif
