
#include <iostream>

#define EXPORT __declspec(dllexport)

extern "C" __declspec(dllexport) void update()
{
    std::cout << "Test Script Update Function" << std::endl;
}