#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <atomic>
#include "../searchLibrary/search.h"
#include <filesystem>

int main(void) {
    const std::string rootDirectory = "/";


    std::cout << "Enter name of the file to be found: ";
    std::string filename;
    std::getline(std::cin, filename);

    const int maxThreadsNum = 0x8;
    std::atomic < int > numOfThreads(0x0);
    bool* shouldStop;
    shouldStop = new bool(false);
    std::atomic < bool > found(false);
    std::vector < std::thread > threads;
    std::queue < std::string > threadsToBeActivated;
    try {
        for (const auto &entry: std::filesystem::directory_iterator(rootDirectory)) {
            if (entry.path().filename().c_str() == filename) {
                std::cout << "File found at: " << entry.path().c_str() << '\n';
                found = true;
                *shouldStop = true;
                break;
            }
            while(numOfThreads < maxThreadsNum && !threadsToBeActivated.empty()) {
                std::string directory = threadsToBeActivated.front();
                threadsToBeActivated.pop();
                threads.push_back(std::thread([&]() {
                    ++ numOfThreads;
                    if (isPresent(filename, directory, shouldStop)) {
                        *shouldStop = true;
                    }
                    -- numOfThreads;
                }));
            }
            if (entry.is_directory()) {
                threadsToBeActivated.push(entry.path().c_str());
            }
        }
        while(!threadsToBeActivated.empty()) {
            while(numOfThreads >= maxThreadsNum) {
            }
            std::string directory = threadsToBeActivated.front();
            threadsToBeActivated.pop();
            threads.push_back(std::thread([&]() {
                ++ numOfThreads;
                if (isPresent(filename, directory, shouldStop)) {
                    *shouldStop = true;
                    found = true;
                }
                -- numOfThreads;
            }));
        }
        for (auto &activeThread: threads) {
            activeThread.join();
        }
        if (!found) {
            std::cout << "File not found!\n";
        }
    } catch (std::filesystem::__cxx11::filesystem_error ex) {
        // std::cerr << ex.what() << '\n';
    }
    return 0x0;
}