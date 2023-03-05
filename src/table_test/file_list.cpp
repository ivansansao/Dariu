#include <dirent.h>

#include <iostream>

int main() {
    int phase_total = 0;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("../resource")) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::cout << ent->d_name << std::endl;

            if (std::string(ent->d_name).find("map_") != std::string::npos) {
                phase_total++;
            }
        }
        closedir(dir);
        std::cout << "has " << phase_total << " phases\n";
    } else {
        std::cerr << "Could not open directory" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
