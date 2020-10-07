#pragma once

#include "entityx/entityx.h"
#include <glad/glad.h>

#include "../Components/Position.h"

using namespace entityx;
class RenderingSystem : public System<RenderingSystem> {
    public:
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
            es.each<Position>([dt](Entity entity, Position &position) {
                position.x += direction.x * dt;
                position.y += direction.y * dt;
            });
        }
};