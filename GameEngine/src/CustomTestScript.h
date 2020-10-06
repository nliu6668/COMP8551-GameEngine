#pragma once

#include <iostream>
#include "CScript.h"

class CustomTestScript : public CScript
{
public:
    void update();
};

void CustomTestScript::update()
{
    std::cout << "Test Script Update Function" << std::endl;
}