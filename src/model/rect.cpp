#include "rect.hpp"

#include <algorithm>
#include <cmath>

#undef FloatRect
#undef intersects

rect::rect() : sf::FloatRect() {
}

rect::rect(float left, float top, float width, float height) : sf::FloatRect({left, top}, {width, height}) {
}

rect::rect(const sf::FloatRect& other) : sf::FloatRect(other) {
}

rect& rect::operator=(const sf::FloatRect& other) {
    position = other.position;
    size = other.size;
    return *this;
}

std::string rect::touch(const class rect& other) const {
    return touch(static_cast<const sf::FloatRect&>(other));
}

std::string rect::touch(const sf::FloatRect& other) const {
    const float epsilon = 0.001f;

    const float thisRight = position.x + size.x;
    const float thisBottom = position.y + size.y;
    const float rectRight = other.position.x + other.size.x;
    const float rectBottom = other.position.y + other.size.y;

    const float overlapX = std::min(thisRight, rectRight) - std::max(position.x, other.position.x);
    const float overlapY = std::min(thisBottom, rectBottom) - std::max(position.y, other.position.y);

    if (overlapX < -epsilon || overlapY < -epsilon) {
        return "";
    }

    if (std::abs(rectRight - position.x) <= epsilon && overlapY >= -epsilon) {
        return "r";
    }

    if (std::abs(other.position.x - thisRight) <= epsilon && overlapY >= -epsilon) {
        return "l";
    }

    if (std::abs(rectBottom - position.y) <= epsilon && overlapX >= -epsilon) {
        return "b";
    }

    if (std::abs(other.position.y - thisBottom) <= epsilon && overlapX >= -epsilon) {
        return "t";
    }

    if (overlapX <= epsilon || overlapY <= epsilon) {
        return "";
    }

    const float thisCenterX = position.x + (size.x / 2.f);
    const float thisCenterY = position.y + (size.y / 2.f);
    const float rectCenterX = other.position.x + (other.size.x / 2.f);
    const float rectCenterY = other.position.y + (other.size.y / 2.f);

    if (overlapX < overlapY) {
        return thisCenterX < rectCenterX ? "l" : "r";
    }

    return thisCenterY < rectCenterY ? "t" : "b";
}

void rect::draw(sf::RenderWindow* w) const {
    sf::RectangleShape shape(sf::Vector2f(size.x, size.y));
    shape.setPosition({position.x, position.y});
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(-1.f);
    w->draw(shape);
}
