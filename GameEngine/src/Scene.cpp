#include "Scene.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

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