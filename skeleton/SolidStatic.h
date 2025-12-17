#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "core.hpp"

using namespace physx;
class SolidStatic
{
public:
	SolidStatic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, Vector4& color);
	~SolidStatic();

	inline PxRigidStatic* getObj() { return obj_; }

private:
	PxPhysics* gPhysics_;
	PxRigidStatic* obj_;
	PxTransform transform_;
	RenderItem* rItem_;
};

