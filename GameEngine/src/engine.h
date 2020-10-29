#ifndef engine_h
#define engine_h
#pragma once

#include <entityx/entityx.h>
#include <chrono>
#include "Systems/PhysicsSystem.h"
#include "Systems/SoundSystem.h"

#include "Systems/CustomScriptSystem.h"
#include "Systems/RenderingSystem.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <functional>

#include <Windows.h>

using namespace entityx;

class Engine : public EntityX{
    public:
        static Engine& getInstance();

        void start();
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;
        GLFWwindow* window;

    private:
        explicit Engine();
        std::chrono::high_resolution_clock clock;
        std::chrono::milliseconds lastTime;
        std::chrono::milliseconds deltaTime;
        bool initialized = false;
        void initialize();
        void update();
    
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