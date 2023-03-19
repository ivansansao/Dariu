
#include <iostream>

using namespace std;

int main() {
    std::string slifes = "lifes: 2 ";
    int lifes = stoi(slifes.substr(slifes.find(":") + 1, 99));
    cout << lifes;
    return 0;
}