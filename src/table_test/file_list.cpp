#include <dirent.h>

#include <iostream>

int main() {
    int phase_total = 0;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("../src/resource")) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            if (std::string(ent->d_name).find("map_") != std::string::npos) {
                phase_total++;
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Could not open directory" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
