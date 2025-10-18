#pragma once

#ifndef BULLETGUN_H
#define BULLETGUN_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "animation.hpp"
#include "sounds.hpp"
#include "tilemap.hpp"

class BulletGun {
   public:
    BulletGun();
    Animation bulletGun;
    sf::FloatRect pos;
    bool onPortal = false;
    bool collided = false;
    virtual void draw(sf::RenderWindow* w);
    virtual void update(Tilemap* tilemap, Sounds* sounds);
};
#endif
