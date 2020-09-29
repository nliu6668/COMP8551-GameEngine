#pragma once

#include "entityx/entityx.h"
#include <vector>
#include <algorithm>

using namespace entityx;

struct SASObject {
    SASObject(float val_, Entity& e_, bool isBegin_) : val(val_), e(e_), isBegin(isBegin_) {}
    bool operator<(SASObject& right) {
        return val < right.val;
    }

    float val;
    Entity e;
    bool isBegin;
};

struct EntityPair {
    EntityPair(Entity& a_, Entity& b_) : a(a_), b(b_) {}
    
    Entity a;
    Entity b;
};

class PhysicsSystem : public System<PhysicsSystem> {
    public:
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //Step 1: Apply rigidbody movement (velocity)
            //TODO

            //Step 2: Detect collisions
            std::vector<EntityPair> pairs = broadphase(es); //returns pairs of possible collisions
            //narrowphase(pairs) should return pairs of entities that are colliding

            //Step 3: apply physics to all entities and resolve all collisions from pairs
        }
    private:
        std::vector<EntityPair> broadphase(EntityManager& es) {
            //might need performance boost - right now it's sorting every frame,
            //could keep it sorted between frames but would need a way to track new/moving colliders

            //sort and sweep
            //get all colliders
            // auto entities = es.entities_with_components<BoxCollider>();
            // auto entities = es.entities_with_components<>(); // temp

            // colliders require b and e attributes (along x) - type float
            //get each collider's b & e
            //and put all b & e in a list
            std::vector<SASObject> sas;
            // for (Entity e : entities) {
                // ComponentHandle<BoxCollider> handle = e.component<BoxCollider>();
                // sas.emplace_back(SASObject(handle.b, e, true);
                // sas.emplace_back(SASObject(handle.e, e, false);
            // }
            //pretty sure that each entity can only have one component of each type, i.e. no duplicates.
            //If this is the case it doesnt make sense for an entity to be able to have two different types of components either
            //solution: Generic Collider component that is either modified, or has children types
            //for now just assume only has box collider

            //sort the list
            std::sort(sas.begin(), sas.end());

            //sweep
            std::vector<SASObject> active;
            std::vector<EntityPair> possibleCollides;
            for (auto it = sas.begin(); it != sas.end(); ++it) {
                if ((*it).isBegin) {
                    //add to active
                    active.push_back(*it);
                } else {
                    //remove match from active
                    //when removing an SASObject, perform AABB check between this obj and all active ones
                    std::vector<SASObject>::iterator oToRemove; // to remember where to remove
                    for (auto it2 = active.begin(); it2 != active.end(); ++it2) {
                        if ((*it).e == (*it2).e) {
                            //they have the same entity, begin and end are *it and *it2
                            //remove begin
                            oToRemove = it; //might be a reference issue here
                        } else {
                            //perform AABB check
                            //AABB check between (*it).e and (*it2).e or the entities they represent

                            //if AABB is true (they might be colliding)
                            //then
                            possibleCollides.emplace_back(EntityPair((*it).e, (*it2).e));
                        }
                    }
                }
            }
            return possibleCollides;
        }
};