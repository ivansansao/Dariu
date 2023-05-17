// C++ Program to create
// a vector of class objects
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student {
};

int main() {
    char charNum = '2';
    int intNum = std::atoi(&charNum);
    cout << intNum;
    cout << "end\n";

    // Vector of class objects
    vector<Student> v;
    Student s;

    for (int i = 0; i < 10; i++) {
        // getting the random values from
        // functions

        // inserting objects to vector
        v.push_back(s);
    }

    for (int i = 0; i < 10; i++) {
        // displaying object data
        // cout << v[i].name << endl;
    }

    return 0;
}
