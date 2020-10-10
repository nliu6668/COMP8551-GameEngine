#include "Scene.h"

string Scene::getName() {
    return name;
}

void Scene::load() {
    //open file (fileName)
    //ifstream file(fileName);
    //read file, parse it


    //populate list of entities with their components

}

Scene::Scene(string sceneName, string tmxFile) : name(sceneName), fileName(tmxFile) {
    
}