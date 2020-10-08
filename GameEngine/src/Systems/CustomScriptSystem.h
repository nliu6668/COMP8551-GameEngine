#pragma once

#include <fstream>
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <windows.h>

#include "entityx/entityx.h"
#include "../Components/CustomScript.h"

using namespace entityx;
class CustomScriptSystem : public System<CustomScriptSystem> {
public:
    void update(EntityManager& es, EventManager& events, TimeDelta dt) override 
    {
        es.each<CustomScript>([dt](Entity entity, CustomScript &customScript) {

            //customScript.cScript->update();
        
        });

        // toFile(ccodestring, "ExampleCustomScript");

        CScript* cscript;
        cscript = getCustomScriptObject("ExampleCustomScript");
        
        if (cscript != NULL)
            cscript->update();
        else
            std::cout << "getCustomScriptObject failed" << std::endl;

        cleanDir();
    }

    /**
     * Opens or Creates a cpp file to fill with a string of c++ code
     * #PARAM ccode: String C++ of code
     * #PARAM filename: Name of file you want to create to file   
     */
    void toFile(std::string ccode, std::string filename)
    {
        ofstream myfile;
        std::string filepath = "src/CustomScripts/" + filename + ".cpp";
        myfile.open(filepath);
        myfile << ccode;
        myfile.close();
    }

    /**
     * 
     * #PARAM filename: name of file that contains the C++ code
     */
    CScript* getCustomScriptObject(std::string filename)
    {
        HINSTANCE hdll = NULL;
        CScript* cscript = NULL;
        typedef void* (*pvScriptObject)();
        pvScriptObject createCustomScriptObject;

        // Create dll file 
        std::string gccCommand = "g++ src/CustomScripts/" + filename + ".cpp -o src/CustomScripts/" + filename + ".dll -shared -fPIC";
        const char *cgccCommand = gccCommand.c_str();
        system(cgccCommand);
        
        // Load the dll ( It says there is an error but it compiles and works anyways :/ )
        std::string path = "src\\CustomScripts\\" + filename + ".dll";
        const char * cpath = path.c_str();
        hdll = LoadLibrary(cpath);

        if (!hdll)
        {
           Logger::getInstance() << "Error: Failed to load dll " + filename;
           return NULL;
        }

        // Get the function pointer
        createCustomScriptObject = (pvScriptObject) (GetProcAddress(hdll, "CreateCustomScriptObject"));

        if (!createCustomScriptObject)
        {
            Logger::getInstance() << "Error: Failed to find CreateCustomScriptObject in " + filename;
            return NULL;
        }

        // Create CScript Object
        cscript = static_cast<CScript*> ( createCustomScriptObject() ); 
        
        return cscript;
    }

    void cleanDir()
    {
        for (const auto& entry : std::experimental::filesystem::directory_iterator("src/CustomScripts"))
        {
            if (entry.path().string().compare("src/CustomScripts/ExampleCustomScript.cpp") != 0)
                std::experimental::filesystem::remove_all(entry.path());
        }
    }

private:
    std::string ccodestring = 
        "#include <iostream> \n"  
        "#include \"../CScript.h\" \n\n"
        "#define EXPORT extern \"C\" __declspec(dllexport) \n\n"  
        "class CustomTestScript : public CScript \n" 
        "{ \n" 
        "public: \n" 
        "   void update(); \n" 
        "}; \n\n" 
        "void CustomTestScript::update() \n" 
        "{ \n" 
        "   std::cout << \"Test Script Update Function\" << std::endl; \n" 
        "} \n\n"
        "EXPORT CScript* CreateCustomScriptObject() \n"
        "{ \n"
        "   return new CustomTestScript(); \n"
        "} \n";
}; 