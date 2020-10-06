/**
 * Example CustomScript
 * 
 * Example adding of Component:
 * entityx::Entity entity = e.entities.create();
 * entity.assign<CustomScript>(new CustomTestScript());
 * 
 * By Darian Gratton
 */

#include <iostream> 
#include "CScript.h"

#define EXPORT extern "C" __declspec(dllexport) 

class CustomTestScript : public CScript 
{ 
public: 
   void update(); 
}; 

void CustomTestScript::update() 
{ 
   std::cout << "Test Script Update Function" << std::endl; 
} 

EXPORT CScript* CreateCustomScriptObject() 
{ 
   return new CustomTestScript(); 
} 
