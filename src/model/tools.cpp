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

int Tools::wordOccurrence(std::string sentence, std::string word) {
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
bool Tools::hasString(std::string line, std::string str) {
    int i_string = (int)line.find(str);
    if (i_string > 999)
        return false;
    return i_string > -1;
}

std::string Tools::get_lines_from_dtm(std::string filename, std::string tag, std::string endLine) {
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
            chunk += line + endLine;
        }
    }
    map_file.close();

    return chunk;
}
uint32_t Tools::crc32(const std::string& data) {
    uint32_t crc = 0xFFFFFFFF;
    for (unsigned char c : data) {
        crc ^= c;
        for (int i = 0; i < 8; i++) {
            crc = (crc >> 1) ^ (0xEDB88320u & -(int)(crc & 1));
        }
    }
    return ~crc;
}