#pragma once

#include "entityx/entityx.h"
#include <vector>
#include <algorithm>
#include "../Components/Components.h"
// #include "PhysicsFunctions.h"
#include "../logger.h"
#include <string>

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
            std::vector<EntityPair> collidingPairs = narrowphase(pairs); //should return pairs of entities that are colliding

            for (int i = 0; i < collidingPairs.size(); ++i) {
                Logger::getInstance() << collidingPairs.at(i).a.id().id() << " colliding with " << collidingPairs.at(i).b.id().id() << "\n";
            }
            //Logger::getInstance() << "physics!\n";
            //Step 3: apply physics to all entities and resolve all collisions from pairs
        }
    private:
        std::vector<EntityPair> narrowphase(std::vector<EntityPair> possibleColl) {
            std::vector<EntityPair> collisions;
            for (EntityPair ep : possibleColl) {
                //get each entity's colliders and transforms
                ComponentHandle<BoxCollider> c1 = ep.a.component<BoxCollider>();
                ComponentHandle<BoxCollider> c2 = ep.b.component<BoxCollider>();
                ComponentHandle<Transform> c1T = ep.a.component<Transform>();
                ComponentHandle<Transform> c2T = ep.b.component<Transform>();

                //check if the colliders are colliding based on their type/shape
                bool isColliding = CheckCollision(c1, c2, c1T, c2T);
                if (isColliding) {
                    collisions.push_back(ep);
                }
            }

            return collisions;
        }
        #pragma region //Collision algorithms
        //Box - Box
        bool CheckCollision(ComponentHandle<BoxCollider>& c1, ComponentHandle<BoxCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            return DetectAABB(c1->x + c1T->x, c1->y + c1T->y, c1->bbWidth, c1->bbHeight, c2->x + c2T->x, c2->y + c2T->y, c2->bbWidth, c2->bbHeight);
        }

        //Circle - Circle
        bool CheckCollision(ComponentHandle<CircleCollider>& c1, ComponentHandle<CircleCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            //TODO
            return false;
        }

        //Capsule - Capsule
        bool CheckCollision(ComponentHandle<CapsuleCollider>& c1, ComponentHandle<CapsuleCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            //TODO
            return false;
        }

        //Box - Circle
        bool CheckCollision(ComponentHandle<BoxCollider>& c1, ComponentHandle<CircleCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            //TODO
            return false;
        }

        //Circle - Box (Calls Box - Circle)
        bool CheckCollision(ComponentHandle<CircleCollider>& c1, ComponentHandle<BoxCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            return CheckCollision(c2, c1, c2T, c1T);
        }

        //Box - Capsule
        bool CheckCollision(ComponentHandle<BoxCollider>& c1, ComponentHandle<CapsuleCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            //TODO
            return false;
        }

        //Capsule - Box (Calls Box - Capsule)
        bool CheckCollision(ComponentHandle<CapsuleCollider>& c1, ComponentHandle<BoxCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            return CheckCollision(c2, c1, c2T, c1T);
        }

        //Circle - Capsule
        bool CheckCollision(ComponentHandle<CircleCollider>& c1, ComponentHandle<CapsuleCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            //TODO
            return false;
        }

        //Capsule - Circle (Calls Circle - Capsule)
        bool CheckCollision(ComponentHandle<CapsuleCollider>& c1, ComponentHandle<CircleCollider>& c2, ComponentHandle<Transform> c1T, ComponentHandle<Transform> c2T) {
            return CheckCollision(c2, c1, c2T, c1T);
        }

        bool DetectAABB(float x1, float y1, float width1, float height1,
            float x2, float y2, float width2, float height2){
            if (x1 <= x2 + width2 && x1 + width1 >= x2 && y1 <= y2 + height2 &&
            y1 + height1 >= y2){
                return true;
            }
            return false;
        }

        #pragma endregion //collision algorithms

        std::vector<EntityPair> broadphase(EntityManager& es) {
            //might need performance boost - right now it's sorting every frame,
            //could keep it sorted between frames but would need a way to track new/moving colliders

            //sort and sweep
            //get all colliders
            auto entities = es.entities_with_components<BoxCollider>();
            // auto entities = es.entities_with_components<>(); // temp

            // colliders require b and e attributes (along x) - type float
            //get each collider's b & e
            //and put all b & e in a list
            std::vector<SASObject> sas;
            for (Entity e : entities) {
                ComponentHandle<BoxCollider> handle = e.component<BoxCollider>();
                ComponentHandle<Transform> handleT = e.component<Transform>();
                sas.emplace_back(SASObject(handle->b + handleT->x, e, true));
                sas.emplace_back(SASObject(handle->e + handleT->x, e, false));
            }
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
                            oToRemove = it2; //might be a reference issue here
                        } else {
                            Entity e1 = (*it).e;
                            Entity e2 = (*it2).e;
                            ComponentHandle<BoxCollider> c1 = e1.component<BoxCollider>();
                            ComponentHandle<BoxCollider> c2 = e2.component<BoxCollider>();
                            ComponentHandle<Transform> c1T = e1.component<Transform>();
                            ComponentHandle<Transform> c2T = e2.component<Transform>();
                            if (DetectAABB(c1->x + c1T->x, c1->y + c1T->y, c1->bbWidth, c1->bbHeight, c2->x + c2T->x, c2->y + c2T->y, c2->bbWidth, c2->bbHeight)) {
                                possibleCollides.emplace_back(EntityPair((*it).e, (*it2).e));
                            }
                        }
                    }
                    active.erase(oToRemove);
                }
            }
            return possibleCollides;
        }
};