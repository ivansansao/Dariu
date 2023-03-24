#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#include <chrono>
#include <string>

class Tools {
   public:
    Tools();

    static int getStartSprite(int, int);
    static float ceil_special(float num, float biggerthan);
    static float floor_special(float num, float lessthan);
    static std::string addZero(int seconds);
    static std::string seconds_to_hour(int seconds);
    static int time_dif_in_seconds(std::chrono::_V2::system_clock::time_point, std::chrono::_V2::system_clock::time_point);
};
#endif
