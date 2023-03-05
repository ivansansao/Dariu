#include <fstream>
#include <iostream>

using namespace std;

int main() {
    string mylist[23];
    string myText;
    ifstream MyReadFile("example1.txt");
    int i = 0;
    while (getline(MyReadFile, myText)) {
        mylist[i] = myText;
        i++;
    }
    MyReadFile.close();

    return 0;
}
