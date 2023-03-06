#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "tilemap.hpp"

class Actor {
   public:
    Actor();

    sf::RenderWindow window;

    sf::Texture actor_tex_fall;
    sf::Texture actor_tex_idle;
    sf::Texture actor_tex;
    sf::Sprite actor_spr;

    sf::FloatRect pos;
    sf::FloatRect abs_pos;
    sf::Vector2f velocity;

    enum States { Normal,
                  DieStart,
                  Dieing,
                  Died,
                  ReviveStart,
                  Reviving,
                  Revived } state = Normal;

    int direction_x;
    float i_idle_sprite;
    float gravity;
    float lift;
    bool on_ground;
    bool up_released = true;

    sf::Font font_vibes;
    sf::Text deb;

    sf::SoundBuffer jump_buffer;
    sf::Sound jump_sound;

    sf::SoundBuffer fired;
    sf::Sound fired_sound;

    sf::SoundBuffer dooropen;
    sf::Sound dooropen_sound;

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

    virtual void draw(sf::RenderWindow *w);
    virtual void update(Tilemap *tilemap);
    virtual void on_collide(std::string where, int i, int j, Tilemap *tilemap);
    virtual void on_collide_other(int i, int j, Tilemap *tilemap);
    virtual void reset_position();
    virtual void die();

    void jump();
    void jump(bool little);
    void add_gravity();
    bool onFloor();
    void collision_x(Tilemap *);
    void collision_y(Tilemap *);
    void collision_other(Tilemap *);
    void play_sound_pop();
    bool is_block(char el);
    bool is_alive();
};
#endif
