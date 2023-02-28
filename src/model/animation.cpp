#include "animation.hpp"

using namespace std;

Animation::Animation(int q_frame, float step, std::string file) {
    q_frame = q_frame;
    step = step;
    setTexture(file);
}

void Animation::update() {
    i_frame += step;
    if (i_frame > q_frame) {
        i_frame = 0.f;
    }
}

void Animation::draw(sf::RenderWindow *w) {
    w->draw(this->sprite);
}

void Animation::setTexture(std::string file) {
    texture.loadFromFile(file);
    sprite.setTexture(texture);
}
void Animation::setTextureRect(sf::IntRect rect) {
    sprite.setTextureRect(rect);
}
void Animation::setPosition(float i, float j) {
    sprite.setPosition(j, i);
}