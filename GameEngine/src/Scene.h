#pragma once

#include <string>



using namespace std;
class Scene {
    public:
        string getName();
        void load();

        Scene(string sceneName, string tmxFile);
    private:
        string name;
        string fileName;
};