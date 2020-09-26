#pragma once

#include "entityx/entityx.h"

using namespace entityx;
class SoundSystem : public System<SoundSystem> {
    public:
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
        }
};