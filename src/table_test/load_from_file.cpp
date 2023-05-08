// C++ Program to create
// a vector of class objects
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool hasString(std::string line, std::string str) {
    int i_string = (int)line.find(str);
    if (i_string > 999)
        return false;
    return i_string > -1;
}

std::string get_lines_from_file(std::string filename, std::string tag, std::string endLine) {
    bool recording = tag.empty() || tag == "[]";
    std::string chunk = "";
    string line;

    ifstream map_file(filename);

    while (getline(map_file, line)) {
        if (recording && hasString(line, "[ENDBLOCK]")) {
            break;
        } else if (!recording && hasString(line, tag)) {
            recording = true;
            continue;
        }
        if (recording) {
            // chunk += line.substr(0, 10) + "\n";
            chunk += line + endLine;
        }
    }
    map_file.close();

    return chunk;
}

void load_from_file(int phase) {
    cout << get_lines_from_file("../resource/map_" + to_string(phase) + ".dtm", "[THEME]", "") << "FIM";
}

int main() {
    load_from_file(1);
    return 0;
}
