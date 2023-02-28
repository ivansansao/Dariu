#ifndef DARIU_H
#define DARIU_H
#include "actor.hpp"

class Dariu : public Actor {
   public:
    Dariu();
    ~Dariu();

    // The method that I want to override need to put here
    void on_collide(std::string where, int i, int j, Tilemap *tilemap);
};
#endif
