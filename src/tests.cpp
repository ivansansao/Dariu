#include <iostream>

using namespace std;

float ceil_special(float num, float biggerthan) {
    const int int_num = num;
    const float dec = (num - int_num);
    if (dec >= biggerthan) {
        return int_num + 1;
    }
    return num;
}

float floor_special(float num, float lessthan) {
    const int int_num = num;
    const float dec = (num - int_num);
    if (dec <= lessthan) {
        return int_num - 1;
    }
    return num;
}

int main() {
    cout << floor_special(21.0, 0.61) << "\n";
    // cout << ceil_special(21.4, 0.39) << "\n";
    return EXIT_SUCCESS;
}