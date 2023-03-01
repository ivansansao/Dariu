#include "tools.hpp"

Tools::Tools() {
}
int Tools::getStartSprite(int index, int direction) {
    if (direction == -1)
        return index + 1;

    return index;
}
float Tools::ceil_special(float num, float biggerthan) {
    const int int_num = num;
    const float dec = (num - int_num);
    if (dec >= biggerthan) {
        return int_num + 1;
    }
    return num;
}

float Tools::floor_special(float num, float lessthan) {
    const int int_num = num;
    const float dec = (num - int_num);
    if (dec <= lessthan) {
        return int_num - 1;
    }
    return num;
}