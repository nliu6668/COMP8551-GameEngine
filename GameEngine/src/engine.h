// #ifndef engine_h
// #define engine_h
#pragma once

#include <entityx/entityx.h>
#include <chrono>


#include <Windows.h>

using namespace entityx;
class Engine : public EntityX {
    public:
        static Engine& getInstance();

        void update() {
            deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()) - lastTime;
            lastTime += deltaTime;
            float dt = deltaTime.count();
            dt *= 0.001f; //convert to seconds
        }
    private:
        explicit Engine() {
            //initialize
            //add systems
            // systems.add<InputSystem>();
            // systems.add<PhysicsSystem>();
            // systems.add<SoundSystem>();
            // systems.add<CustomScriptSystem>();
            // systems.add<RenderingSystem>();
            // systems.configure();
            // ticksSinceLaunch = std::chrono::system_clock
            lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch());
        }
        std::chrono::high_resolution_clock clock;
        std::chrono::milliseconds lastTime;
        std::chrono::milliseconds deltaTime;
    
    public:
        //remove other constructors
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;
};

// static methods implemented inside the header file
Engine& Engine::getInstance() {
    static Engine instance;
    return instance;
}

// #endif /* engine_h */