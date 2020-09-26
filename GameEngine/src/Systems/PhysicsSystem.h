#pragma once

#include "entityx/entityx.h"

using namespace entityx;
class PhysicsSystem : public System<PhysicsSystem> {
    public:
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
        }
};