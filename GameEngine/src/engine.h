#ifndef engine_h
#define engine_h
#pragma once

#include <entityx/entityx.h>
#include <chrono>
#include "Systems/PhysicsSystem.h"
#include "Systems/SoundSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/CustomScriptSystem.h"
#include "Systems/RenderingSystem.h"

#include <Windows.h>

using namespace entityx;
class Engine : public EntityX {
    public:
        static Engine& getInstance();

        //initialize must be called right before starting the game loop
        void update();
    private:
        explicit Engine();
        std::chrono::high_resolution_clock clock;
        std::chrono::milliseconds lastTime;
        std::chrono::milliseconds deltaTime;
        bool initialized = false;
        void initialize();
    
    public:
        //remove other constructors
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;
};

// static methods implemented inside the header file
inline Engine& Engine::getInstance() {
    static Engine instance;
    return instance;
}

#endif /* engine_h */