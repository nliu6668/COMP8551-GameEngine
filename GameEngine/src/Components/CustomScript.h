#pragma once

#include <string>
#include <vector>

#include "../CScript.h"
#include "../Components/Components.h"

struct CustomScript
{
    CustomScript(CScript* cScript) : cScript(cScript) {}
    ~CustomScript() { delete cScript; };

    CScript* cScript; 
};
