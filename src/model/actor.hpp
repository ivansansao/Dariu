#pragma once

#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "sounds.hpp"
#include "tilemap.hpp"

class Actor {
   public:
    Actor();
    Animation actorRun;
    Animation actorIdle;
    Animation actorJump;
    Animation actorJetpack;

    sf::RenderWindow window;

    sf::Texture actor_tex_fall;
    sf::Texture actor_tex_idle;
    sf::Texture actor_tex_jump;
    sf::Texture actor_tex;
    sf::Sprite actor_spr;

    sf::FloatRect start_pos;
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
    bool jetPack = false;
    float jetPackFuel = 0;
    float jetPackConsume = 0.1;
    float jetPackCapacity = 100;
    bool on_ground;

    bool key_released = true;
    bool up_released = true;
    bool space_released = true;

    bool onPortal = false;

    virtual void draw(sf::RenderWindow *w);
    virtual void update(Tilemap *tilemap, Sounds *sounds);
    virtual void updateWalk(Tilemap *tilemap, Sounds *sounds);
    virtual void updateFly(Tilemap *tilemap, Sounds *sounds);
    virtual void on_collide(std::string where, int i, int j, Tilemap *tilemap, Sounds *sounds);
    virtual void on_collide_other(int i, int j, Tilemap *tilemap, Sounds *sounds);
    virtual void set_position(float left, float top);
    virtual void reset_position();
    virtual void die(Sounds *sounds);
    virtual void drawJetpackTime(sf::RenderWindow *w);

    void jump();
    void jump(bool little);
    void add_gravity();
    bool onFloor();
    void collision_x(Tilemap *, Sounds *sounds);
    void collision_y(Tilemap *, Sounds *sounds);
    void collision_other(Tilemap *, Sounds *sounds);
    void collision_portal(Tilemap *tilemap, Sounds *sounds);
    void play_sound_pop(Sounds *sounds);
    bool is_block(char el);
    bool is_alive();
    point getCoord(Tilemap *tilemap, int offset_i, int offset_j);
};
#endif
