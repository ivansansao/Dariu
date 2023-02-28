#include "dariu.hpp"

#include <cmath>

#include "iostream"
#include "tilemap.hpp"
#include "tools.hpp"

using namespace std;

Dariu::Dariu() {
}
Dariu::~Dariu() {
}

void Dariu::on_collide(std::string where, int i, int j, Tilemap *tilemap) {
    Actor::on_collide(where, i, j, tilemap);
}
