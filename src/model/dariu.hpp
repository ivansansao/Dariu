#ifndef DARIU_H
#define DARIU_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "tilemap.hpp"

class Dariu {
   public:
    Dariu();

    sf::RenderWindow window;

    sf::Texture dariu_tex_fall;
    sf::Texture dariu_tex_idle;
    sf::Texture dariu_tex;
    sf::Sprite dariu_spr;

    sf::FloatRect pos;
    sf::Vector2f velocity;
    int direction_x;
    float i_idle_sprite;
    float ground_y;
    float gravity;
    float lift;
    bool on_ground;
    bool up_released = true;

    sf::Font font_vibes;
    sf::Text deb;

    sf::SoundBuffer jump;
    sf::Sound jump_sound;

    sf::SoundBuffer crash;
    sf::Sound crash_sound;

    sf::SoundBuffer pop;
    sf::Sound pop_sound0;
    sf::Sound pop_sound1;
    sf::Sound pop_sound2;
    sf::Sound pop_sound3;
    sf::Sound pop_sound4;
    sf::Sound pop_sound5;
    sf::Sound pop_sound6;
    sf::Sound pop_sound7;
    sf::Sound pop_sound8;
    sf::Sound pop_sound9;

    void update(Tilemap *tilemap);
    void draw(sf::RenderWindow *w);
    void up();
    bool onFloor();
    void collision_x(Tilemap *);
    void collision_y(Tilemap *);
    void collision_other(Tilemap *);
    void play_sound_pop();
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
};
#endif
