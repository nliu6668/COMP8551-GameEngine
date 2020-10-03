#pragma once

#include "Components/Components.h"


namespace Physics
{
    bool DetectAABB(float x1, float y1, float width1, float height1,
    float x2, float y2, float width2, float height2){
        if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 &&
        y1 + height1 > height2){
            return true;
        }
        return false;
    }
}