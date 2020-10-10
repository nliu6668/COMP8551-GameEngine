#pragma once

#include <entityx/entityx.h>

class CScript
{
protected:
    entityx::Entity* entity;
public:
    CScript(entityx::Entity* ex) : entity(ex) {}
    ~CScript() { delete entity; }

    virtual void start() {};
    virtual void update() {};
    virtual void OnCollision() {};
};
