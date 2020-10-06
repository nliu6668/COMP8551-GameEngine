#pragma once

#include <string>
#include <vector>

#include "../CScript.h"

struct CustomScript
{
    CustomScript(CScript* cScript) : cScript(cScript) {}

    CScript* cScript; 
    int y;
};
