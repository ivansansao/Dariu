#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

using namespace std;

class Animation {
   public:
    Animation(int q_frame, float step, std::string file);

    sf::Texture texture;
    sf::Sprite sprite;
    int q_frame = 0;
    float i_frame = 0;
    float step = 0.f;

    void update();
    void draw(sf::RenderWindow *w);
    void setTexture(std::string file);
    void setTextureRect(sf::IntRect rect);
    void setPosition(float i, float j);
};
#endif
