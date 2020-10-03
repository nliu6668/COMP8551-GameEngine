#pragma once

#include "entityx/entityx.h"
#include <glad/glad.h>

/*#define Assert(x) (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    Assert(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);*/

using namespace entityx;
class RenderingSystem : public System<RenderingSystem> {
    public:
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
        }
};