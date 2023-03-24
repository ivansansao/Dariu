#include <iostream>

// You will need inclide string if not iostream

std::string addZero(int);

void convertSeconds(int seconds) {
    int hours, minutes, remainingSeconds;

    hours = seconds / 3600;  // 1 hour = 3600 seconds
    remainingSeconds = seconds % 3600;
    minutes = remainingSeconds / 60;  // 1 minute = 60 seconds
    remainingSeconds = remainingSeconds % 60;

    std::cout << addZero(hours) << ":" << addZero(minutes) << ":" << addZero(remainingSeconds) << std::endl;
}
std::string addZero(int x) {
    if (x < 10) return "0" + std::to_string(x);
    return std::to_string(x);
}

int main() {
    int totalSeconds = 70;
    convertSeconds(totalSeconds);

    return 0;
}
