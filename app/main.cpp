#include "FileSearch.h"
#include "ThreadPool.h"
#include <mutex>

const int maxThreads = 8;
bool *targetFound = new bool(false);
std::mutex *foundMutex = new std::mutex();

void processRoot(const fs::path& rootPath, const std::string& targetName) {
    ThreadPool pool(maxThreads);
    try {
        for (const auto& entry : fs::directory_iterator(rootPath)) {
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
                pool.enqueue(std::bind(findFileOrDirectory, entry.path(), targetName, foundMutex, targetFound));
            }
        }
    } catch (...) {
        
    }
}

int main() {
    fs::path rootPath = "/";

    std::string targetName;
    std::cout << "Enter name of the file to be found: ";
    std::getline(std::cin, targetName);

    if (fs::exists(rootPath) && fs::is_directory(rootPath)) {
        processRoot(rootPath, targetName);
        if (!(*targetFound)) {
            std::cout << "File not found!\n";
        }
    } else {
        std::cout << "Invalid root folder path." << std::endl;
    }

    return 0;
}
