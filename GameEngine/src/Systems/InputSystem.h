#pragma once

#include "entityx/entityx.h"

using namespace entityx;
class InputSystem : public System<InputSystem> {
    public:
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
        }
};