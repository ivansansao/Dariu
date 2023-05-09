// C++ Program to create
// a vector of class objects
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int wordOccurrence(std::string sentence, std::string word) {
    int slen = sentence.length();
    int wordlen = word.length();
    int count = 0;
    int i, j;
    for (i = 0; i < slen; i++) {
        for (j = 0; j < wordlen; j++) {
            if (sentence[i + j] != word[j])
                break;
        }
        if (j == wordlen) {
            count++;
        }
    }
    return count;
}
bool hasString(std::string line, std::string str) {
    int i_string = (int)line.find(str);
    if (i_string > 999)
        return false;
    return i_string > -1;
}

std::string get_lines_from_file(std::string filename, std::string tag, std::string endLine) {
    bool recording = tag.empty() || tag == "[]";
    std::string chunk = "";
    std::string line;

    std::ifstream map_file(filename);

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
    std::string lines = get_lines_from_file("../resource/map_" + std::to_string(phase) + ".dtm", "", "\n");
    std::stringstream ss(lines);
    std::string line;
    int q_lines = wordOccurrence(lines, "\n");

    while (getline(ss, line, '\n')) {
        std::cout << line << "\n";
    }
    std::cout << "Linhas: " << q_lines << std::endl;
}

int main() {
    load_from_file(1);
    return 0;
}
