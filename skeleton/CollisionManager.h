#pragma once
#include <PxPhysicsAPI.h>
#include "Filters.h"
#include "myScene.h"

using namespace physx;
class CollisionManager: public PxSimulationEventCallback
{
public:
    CollisionManager(myScene* mScene);
    void onContact(PxContactPairHeader const& pairHeader, PxContactPair const* pairs, PxU32 nbPairs) override;

    void onTrigger(PxTriggerPair*, PxU32) override {}
    void onConstraintBreak(PxConstraintInfo*, PxU32) override {}
    void onWake(PxActor**, PxU32) override {}
    void onSleep(PxActor**, PxU32) override {}
    void onAdvance(const PxRigidBody* const*, const PxTransform*, const PxU32) override {}
private:
    myScene* mScene;
};

