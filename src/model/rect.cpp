#include "rect.hpp"

#include <algorithm>
#include <cmath>

rect::rect() : sf::FloatRect() {
}

rect::rect(float left, float top, float width, float height) : sf::FloatRect(left, top, width, height) {
}

rect::rect(const sf::FloatRect& other) : sf::FloatRect(other) {
}

rect& rect::operator=(const sf::FloatRect& other) {
    left = other.left;
    top = other.top;
    width = other.width;
    height = other.height;
    return *this;
}

std::string rect::touch(const class rect& other) const {
    return touch(static_cast<const sf::FloatRect&>(other));
}

std::string rect::touch(const sf::FloatRect& other) const {
    const float epsilon = 0.001f;

    const float thisRight = left + width;
    const float thisBottom = top + height;
    const float rectRight = other.left + other.width;
    const float rectBottom = other.top + other.height;

    const float overlapX = std::min(thisRight, rectRight) - std::max(left, other.left);
    const float overlapY = std::min(thisBottom, rectBottom) - std::max(top, other.top);

    if (overlapX < -epsilon || overlapY < -epsilon) {
        return "";
    }

    if (std::abs(rectRight - left) <= epsilon && overlapY >= -epsilon) {
        return "r";
    }

    if (std::abs(other.left - thisRight) <= epsilon && overlapY >= -epsilon) {
        return "l";
    }

    if (std::abs(rectBottom - top) <= epsilon && overlapX >= -epsilon) {
        return "b";
    }

    if (std::abs(other.top - thisBottom) <= epsilon && overlapX >= -epsilon) {
        return "t";
    }

    if (overlapX <= epsilon || overlapY <= epsilon) {
        return "";
    }

    const float thisCenterX = left + (width / 2.f);
    const float thisCenterY = top + (height / 2.f);
    const float rectCenterX = other.left + (other.width / 2.f);
    const float rectCenterY = other.top + (other.height / 2.f);

    if (overlapX < overlapY) {
        return thisCenterX < rectCenterX ? "l" : "r";
    }

    return thisCenterY < rectCenterY ? "t" : "b";
}

void rect::draw(sf::RenderWindow* w) const {
    sf::RectangleShape shape(sf::Vector2f(width, height));
    shape.setPosition(left, top);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(-1.f);
    w->draw(shape);
}
