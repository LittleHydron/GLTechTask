#include "FileSearch.h"
#include <filesystem>
#include <iostream>
#include <mutex>

namespace fs = std::filesystem;

void findFileOrDirectory(const fs::path& currentPath, const std::string& targetName, std::mutex *foundMutex, bool *targetFound) {
    try {
        for (const auto& entry : fs::directory_iterator(currentPath)) {
            if (*targetFound) {
                return;
            }

            if (entry.path().filename() == targetName) {
                {
                    std::lock_guard<std::mutex> lock(*foundMutex);
                    *targetFound = true;
                }
                std::cout << "Found: " << entry.path() << std::endl;
                return;
            }

            if (fs::is_directory(entry)) {
                findFileOrDirectory(entry.path(), targetName, foundMutex, targetFound);
            }
        }
    } catch (...) {

    }
}
