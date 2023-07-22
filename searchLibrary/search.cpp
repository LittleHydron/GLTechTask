#include "search.h"
#include <filesystem>
#include <iostream>
#include <queue>

std::string getPath(const std::string &filename, const std::string &directory, bool* shouldStop) {
    try {
        for (const auto &entry: std::filesystem::directory_iterator(directory)) {
            if (*shouldStop) {
                return "";
            }
            if (entry.path().filename().string() == filename) {
                *shouldStop = true;
                return entry.path().string();
            }
        }
        std::string presentInChild = "";
        for (const auto &entry: std::filesystem::directory_iterator(directory)) {
            if (*shouldStop) return "";
            if (entry.is_directory()) {
                presentInChild = getPath(filename, entry.path().string(), shouldStop);
                if (presentInChild != "") {
                    return presentInChild;
                }
            }
        }
    } catch (...) {

    }
    return "";
}
