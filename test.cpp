#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <dirent.h>

const int timeoutTime = 1;



void read(const std::string& filename) 
{


    // ||||
    // VVVV
    // TODO: Your code for reading files
    // ...


    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Process each line in the file
            // ...
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

void find(const std::string& filename)
{


    // ||||
    // VVVV
    // TODO: Your algorithm is here
    // ...


}



void findTimeout(const std::string& filename)
{
    std::thread t([&]()
    {
        try
        {
            find(filename);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    });

    t.joinable();
    t.join();
}



int main()
{
    std::string folderPath = "./tests";
    std::vector<double> times;

    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(folderPath.c_str())) != nullptr)
    {
        while ((entry = readdir(dir)) != nullptr)
        {
            std::string filename = entry->d_name;
            if (filename != "." && filename != "..")
            {
                std::string filePath = folderPath + "/" + filename;
                auto startTime = std::chrono::high_resolution_clock::now();

                try
                {
                    findTimeout(filePath);
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                }
                auto endTime = std::chrono::high_resolution_clock::now();
                double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1'000'000'000.0;
                times.push_back(duration);
            }
        }
        closedir(dir);
    }
    else
    {
        std::cerr << "Failed to open directory: " << folderPath << std::endl;
        return 1;
    }



    // Printing the result
    std::string output;
    for (double time : times)
    {
        if (time < timeoutTime)
        {
            output += std::to_string(time) + " ";
        }
        else
        {
            output += "inf ";
        }
    }
    output.pop_back();

    std::cout << output << std::endl;
    return 0;
}
