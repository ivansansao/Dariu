#include "tools.hpp"

#include <chrono>

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

std::string Tools::addZero(int x) {
    if (x < 10) return "0" + std::to_string(x);
    return std::to_string(x);
}

std::string Tools::seconds_to_hour(int seconds) {
    int hours, minutes, remainingSeconds;

    hours = seconds / 3600;  // 1 hour = 3600 seconds
    remainingSeconds = seconds % 3600;
    minutes = remainingSeconds / 60;  // 1 minute = 60 seconds
    remainingSeconds = remainingSeconds % 60;

    return addZero(hours) + ":" + addZero(minutes) + ":" + addZero(remainingSeconds);
}

int Tools::time_dif_in_seconds(std::chrono::system_clock::time_point start, std::chrono::system_clock::time_point end) {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    return duration.count();
}
