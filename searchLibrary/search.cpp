#include "search.h"
#include <filesystem>
#include <iostream>
#include <queue>

std::string isPresent(const std::string &filename, const std::string &directory, bool* shouldStop) {
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
                    return entry.path().c_str() << '\n';
                }
                if (entry.is_directory()) {
                    nextDirectories.push(entry.path().c_str());
                }
            }
        } catch (std::filesystem::__cxx11::filesystem_error ex) {
            // std::cerr << ex.what() << '\n';
        }
    }
    return "";
}