#pragma once

#ifndef DARIU_H
#define DARIU_H
#include <SFML/Graphics.hpp>

#include "actor.hpp"
#include "score.hpp"

class Dariu : public Actor {
   public:
    Dariu();
    ~Dariu();
    Score score;
    sf::Text text_score;

    sf::Font font_vibes;

    bool win;
    bool over;

    void update(Tilemap *tilemap, Sounds *sounds);
    void reset_position();
    void draw(sf::RenderWindow *w, int phase);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds);
    void on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds);
    void die(Sounds *sounds);
    void shot(Sounds *sounds);
};
#endif
