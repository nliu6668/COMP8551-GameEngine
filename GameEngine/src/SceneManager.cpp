#include "SceneManager.h"
#include "logger.h"

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

            //find all entities with custom scripts and run their start methods
            
            return;
        }
    }

    Logger::getInstance() << "SceneManager::loadScene failed: Scene not found.\n";
}

void SceneManager::addScene(string sceneName, string tmxFile) {
    scenes.push_back(new Scene(sceneName, tmxFile));
}