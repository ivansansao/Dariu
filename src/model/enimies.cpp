#include "enimies.hpp"

#include <iostream>

using namespace std;

Enimy::Enimy() {
    name = "Do not know";
};

void Enimy::update(Tilemap *tilemap) {
    Actor::update(tilemap);
    cout << "Enimy update() \n";
}

Catraca::Catraca() {
    idade = 44;
};

void Catraca::update(Tilemap *tilemap) {
    // Enimy::update(tilemap);
    cout << "Catraca update() \n";
}
