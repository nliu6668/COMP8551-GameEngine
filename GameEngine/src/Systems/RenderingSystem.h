#pragma once

#include "entityx/entityx.h"

using namespace entityx;
class RenderingSystem : public System<RenderingSystem> {
    public:
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
        }
};