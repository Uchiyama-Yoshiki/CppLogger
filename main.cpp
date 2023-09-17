#include <windows.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "Logger.h"

void worker()
{
    for (int i = 0; i < 1000; i++)
    {
        Logger::Info("start logger");
    }
}

int main(int argc, char *argv[])
{
    Logger::Start();

    std::thread thread1(worker);
    std::thread thread2(worker);

    thread1.join();
    thread2.join();

    Logger::Stop();

    return 0;
}