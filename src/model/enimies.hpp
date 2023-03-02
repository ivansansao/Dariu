#pragma once

#ifndef ENIMIES_HPP
#define ENIMIES_HPP

#include "actor.hpp"

class Enimy {
   public:
    Enimy();
    std::string name = "Indefinido";
};

// class Catraca : public Enimy {
//    public:
//     Catraca();
//     int idade;
// };

class Catraca : public Enimy {
   public:
    Catraca();
    int idade;
};

#endif
