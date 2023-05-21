#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <dirent.h>



void read(const std::string& filename) {
    // TODO: Implement your code here
}



void find(const std::string& filename) {
    // TODO: Implement your code here
}



int main() {
    int n = 100;
    std::vector<std::string> files;
    DIR* directory = opendir("./tests");
    struct dirent* entry;

    while ((entry = readdir(directory)) != nullptr)
        {
#if defined(_DIRENT_HAVE_D_TYPE)
        if (entry->d_type == DT_REG) { // Check if it is a regular file
#else
        // Use platform-specific checks for regular files
        std::string filePath = std::string("./tests/") + entry->d_name;
        std::ifstream file(filePath);
        if (file.good()) { // Check if the file can be opened
            file.close();
#endif
            files.push_back(entry->d_name);
        }
    }

    closedir(directory);

    for (size_t i = 1; i < files.size(); ++i) {
        std::string& file = files[i];
        auto start = std::chrono::high_resolution_clock::now();

        find(file);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << duration.count() << std::endl;
    }

    return 0;
}
