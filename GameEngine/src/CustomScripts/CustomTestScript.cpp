#include <iostream> 
#include "../CScript.h" 

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
