#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace fs = std::filesystem;

class ThreadPool {
public:
    ThreadPool(int numThreads);

    ~ThreadPool();

    void enqueue(std::function<void()> task);

    bool isStopped();

private:
    void workerThread();

    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

#endif