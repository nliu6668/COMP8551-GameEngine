#pragma once

#include <string>
#include <vector>

#include <windows.h>

struct CustomScript
{
    CustomScript(std::string _path) :  path(_path) {}

    std::vector<HINSTANCE> hGetProcIDDLL;
    std::string path;
};
