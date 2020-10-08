#include <iostream> 
#include <entityx/entityx.h>

#include "../CScript.h" 
#include "../Components/Components.h"

#define EXPORT extern "C" __declspec(dllexport) 

class CustomTestScript : public CScript 
{ 
private:
   typedef CScript super;
public: 
   CustomTestScript(entityx::Entity* ex) : super(ex) {};

   void update(); 
}; 

void CustomTestScript::update() 
{ 
   entityx::ComponentHandle<Transform> transform = entity->component<Transform>();
   transform.get()->x = 2;
   //std::cout << entity->component<Transform>().get()->x << std::endl; 
} 

EXPORT CScript* CreateCustomScriptObject(entityx::Entity* ex) 
{ 
   return new CustomTestScript(ex); 
} 
