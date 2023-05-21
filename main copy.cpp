#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <filesystem>

const int timeoutTime = 5;

void read(const std::string& filename)
{
    // Your code for reading the file goes here
}

void find(const std::string& filename)
{
    // Your code for finding the file goes here
}

void findTimeout(const std::string& filename)
{
    std::thread t([&filename]() {
        find(filename);
    });
    t.join();
}

int main()
{
    std::string folderPath = "./tests";
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(folderPath))
    {
        files.push_back(entry.path().string());
    }

    std::vector<double> times;

    // Measure the execution time for each file
    for (const auto& file : files)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        findTimeout(file);

        auto endTime = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
        times.push_back(duration);
    }

    // Print the measured times in a single line
    for (const auto& time : times)
    {
        if (time < timeoutTime)
        {
            std::cout << time << " ";
        }
        else
        {
            std::cout << "inf ";
        }
    }
    std::cout << std::endl;

    return 0;
}