#pragma once

#ifndef RECT_H
#define RECT_H

#include <SFML/Graphics.hpp>
#include <string>

class rect : public sf::FloatRect {
   public:
    rect();
    rect(float left, float top, float width, float height);
    rect(const sf::FloatRect& rect);
    rect& operator=(const sf::FloatRect& other);

    std::string touch(const class rect& other) const;
    std::string touch(const sf::FloatRect& other) const;
    void draw(sf::RenderWindow* window) const;
};

#endif
