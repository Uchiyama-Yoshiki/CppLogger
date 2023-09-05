#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "Logger.h"

int main(int argc, char *argv[])
{
    Logger::Info("start logger");
    Logger::Info("end logger");

    return 0;
}