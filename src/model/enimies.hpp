#pragma once

#ifndef ENIMIES_HPP
#define ENIMIES_HPP

#include "actor.hpp"

class Enimy : public Actor {
   public:
    Enimy();
    std::string name = "Indefinido";
    // Override
    void update(Tilemap *tilemap);
};

class Catraca : public Enimy {
   public:
    Catraca();
    int idade;
    // Override
    void update(Tilemap *tilemap);
};

#endif
