#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "core.hpp"


using namespace physx;
class SolidDynamic
{
public:
	SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform,double density, Vector4& color = Vector4(1));
	~SolidDynamic();

private:

	PxPhysics* gPhysics_;
	PxRigidDynamic* obj_;
	PxTransform transform_;
	RenderItem* rItem_;

};

