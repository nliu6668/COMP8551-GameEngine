#pragma once

#include "entityx/entityx.h"
#include "../Components/CustomScript.h"

using namespace entityx;
class CustomScriptSystem : public System<CustomScriptSystem> {
public:
    void update(EntityManager& es, EventManager& events, TimeDelta dt) override 
    {
        es.each<CustomScript>([dt](Entity entity, CustomScript &customScript) {

            customScript.cScript->update();
        
        });
    }      
};