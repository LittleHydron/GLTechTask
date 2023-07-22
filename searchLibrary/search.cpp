#include "search.h"
#include <filesystem>
#include <iostream>
#include <queue>

bool isPresent(const std::string &filename, const std::string &directory, bool* shouldStop) {
    std::queue < std::string > nextDirectories;
    nextDirectories.push(directory);
    while(!nextDirectories.empty()) {
        if (*shouldStop) {
            break;
        }
        std::string currentDirectory = nextDirectories.front();
        nextDirectories.pop();
        try{
            for (const auto &entry: std::filesystem::directory_iterator(currentDirectory)) {
                if (entry.path().filename().c_str() == filename) {
                    std::cout << "File found at: " << entry.path().c_str() << '\n';
                    return true;
                }
                if (entry.is_directory()) {
                    nextDirectories.push(entry.path().c_str());
                }
            }
        } catch (std::filesystem::__cxx11::filesystem_error ex) {
            // std::cerr << ex.what() << '\n';
        }
    }
    return false;
}