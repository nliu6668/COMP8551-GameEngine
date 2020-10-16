#include "SceneManager.h"
#include "logger.h"
#include "engine.h"
#include "Events/Events.h"

SceneManager::SceneManager() {

}

void SceneManager::start() {
    Scene* first = scenes.at(0);
    loadScene(first->getName());
}

void SceneManager::loadScene(string sceneName) {
    //find scene with name
    Scene* scene;
    for (int i = 0; i < scenes.size(); ++i) {
        scene = scenes.at(i);
        if (scene->getName() == sceneName) {
            scene->load();
            Engine::getInstance().events.emit<SceneLoad>(scene->getName());
            
            return;
        }
    }

    Logger::getInstance() << "SceneManager::loadScene failed: Scene not found.\n";
}

void SceneManager::addScene(string sceneName, string tmxFile) {
    scenes.push_back(new Scene(sceneName, tmxFile));
}