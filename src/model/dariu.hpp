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

    sf::SoundBuffer levelcomplete;
    sf::Sound levelcomplete_sound;

    bool win;
    bool over;

    // Override
    void update(Tilemap *tilemap);
    void reset_position();
    void draw(sf::RenderWindow *w, int phase);
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
    void on_collide_other(int i, int j, Tilemap *tilemap);
    void die();
};
#endif
