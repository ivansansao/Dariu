    #include <chrono>
    #include <iostream>
    
    int time_dif_in_seconds(std::chrono::system_clock::time_point start, std::chrono::system_clock::time_point end) {
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        return duration.count();
    }
    
    int main() {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        int dif = time_dif_in_seconds(start, end);
        std::cout << std::to_string(dif) << " seconds" << std::endl;
        return 0;
    }
