#include "engine.h"

//add any method implementations here

Engine::Engine() {
    //add systems
    systems.add<InputSystem>();
    systems.add<PhysicsSystem>();
    systems.add<SoundSystem>();
    systems.add<CustomScriptSystem>();
    systems.add<RenderingSystem>();
    systems.configure();
}

void Engine::initialize() {
    //initialize
    lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch());
    initialized = true;

}

void Engine::update() {
    if (!initialized) {
        initialize();
    }

    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()) - lastTime;
    lastTime += deltaTime;
    TimeDelta dt = deltaTime.count();
    dt *= 0.001f; //convert to seconds
    
    //do updates
    systems.update<InputSystem>(dt);
    systems.update<PhysicsSystem>(dt);
    systems.update<SoundSystem>(dt);
    systems.update<CustomScriptSystem>(dt);
    systems.update<RenderingSystem>(dt);
}
