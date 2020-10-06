#pragma once

#include "entityx/entityx.h"

using namespace entityx;
class CustomScriptSystem : public System<CustomScriptSystem> {
    public:
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
        }      
};