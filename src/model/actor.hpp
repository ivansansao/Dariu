#pragma once

#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "bulletgun.hpp"
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

    std::vector<BulletGun*> bulletguns;

    enum States { Normal,
                  DieStart,
                  Dieing,
                  Died,
                  ReviveStart,
                  Reviving,
                  Revived } state = Normal;

    int id = 0;
    int updates = 0;
    int direction_x;
    int direction_y;
    float i_walk_sprite = 0;
    float i_idle_sprite;
    float i_fall_sprite;
    float i_jump_sprite;
    float gravity;
    float lift;
    bool jetPack = false;
    bool stopped = false;
    float jetPackFuel = 0;
    float jetPackConsume = 0.1;
    float jetPackCapacity = 100;
    bool on_ground;

    bool hasGun = true;
    int munitions = 3;

    bool key_released = true;
    bool up_released = true;
    bool z_released = true;
    bool space_released = true;
    bool lcontroll_released = true;
    bool rcontroll_released = true;
    bool zerokey_released = true;

    bool onPortal = false;

    virtual void draw(sf::RenderWindow* w);
    virtual void update(Tilemap* tilemap, Sounds* sounds);
    virtual void updateWalk(Tilemap* tilemap, Sounds* sounds);
    virtual void updateFly(Tilemap* tilemap, Sounds* sounds);
    virtual void on_collide(std::string where, int i, int j, Tilemap* tilemap, Sounds* sounds);
    virtual void on_collide_other(int i, int j, Tilemap* tilemap, Sounds* sounds);
    virtual void set_position(float left, float top);
    virtual void reset_position();
    virtual void die(Tilemap* tilemap, Sounds* sounds);
    virtual void drawJetpackTime(sf::RenderWindow* w);
    virtual void shot(Sounds* sounds);
    virtual void update_bullets(Tilemap* tilemap, Sounds* sounds);
    virtual void draw_bullets(sf::RenderWindow* w);

    void jump();
    void jump(bool little);
    void add_gravity();
    bool onFloor();
    void collision_x(Tilemap*, Sounds* sounds);
    void collision_y(Tilemap*, Sounds* sounds);
    void collision_other(Tilemap*, Sounds* sounds);
    void collision_portal(Tilemap* tilemap, Sounds* sounds);
    void play_sound_pop(Sounds* sounds);
    bool is_block(char el);
    bool is_alive();
    point getCoord(Tilemap* tilemap, int offset_i, int offset_j);
    sf::Color setRandomColor();
    void setColor(sf::Color color);
};
#endif
