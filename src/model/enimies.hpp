#pragma once

#ifndef ENIMIES_HPP
#define ENIMIES_HPP

#include "actor.hpp"
#include "tools.hpp"

class Enimy : public Actor {
   public:
    Enimy();

    void update(Tilemap *tilemap, Sounds *sounds);
    void updateWalk(Tilemap *tilemap, Sounds *sounds);
    void updateFly(Tilemap *tilemap, Sounds *sounds);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds);
    void on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds);
    void die(Tilemap *tilemap, Sounds *sounds);
};
class Catraca : public Enimy {
   public:
    Catraca();

    void update(Tilemap *tilemap, Sounds *sounds);
    void updateWalk(Tilemap *tilemap, Sounds *sounds);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds);
    void on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds);
    void die(Tilemap *tilemap, Sounds *sounds);
};
class Sova : public Enimy {
   public:
    Sova();

    void update(Tilemap *tilemap, Sounds *sounds);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds);
    void on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds);
    void die(Tilemap *tilemap, Sounds *sounds);
};
class Cannon : public Enimy {
   public:
    Cannon();

    void update(Tilemap *tilemap, Sounds *sounds);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds);
    void on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds);
    void die(Tilemap *tilemap, Sounds *sounds);
};
class Bulletc : public Enimy {
   public:
    Bulletc();

    void update(Tilemap *tilemap);
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds);
    void on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds);
    void die(Tilemap *tilemap, Sounds *sounds);
};

#endif
