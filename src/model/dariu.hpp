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

    bool win;
    bool over;

    // Override
    void update(Tilemap *tilemap);
    void reset_position();
    void draw(sf::RenderWindow *w);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
    void on_collide_other(int i, int j, Tilemap *tilemap);
    void die();
};
#endif
