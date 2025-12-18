#pragma once
#include "SolidStatic.h"
class Goal : public SolidStatic
{
public:
	Goal(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, PxFilterData filter, Vector4& color);
	virtual ~Goal();
};

