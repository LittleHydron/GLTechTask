#ifndef SEARCH_H
#define SEARCH_H

#include <filesystem>
#include <string>
#include <mutex>
#include "ThreadPool.h"

namespace fs = std::filesystem;

void findFileOrDirectory(const fs::path& currentPath, const std::string& targetName, std::mutex *foundMutex, bool *targetFound);

#endif