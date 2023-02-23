#include "tools.hpp"

Tools::Tools() {
}
int Tools::getStartSprite(int index, int direction) {
    if (direction == -1)
        return index + 1;

    return index;
}