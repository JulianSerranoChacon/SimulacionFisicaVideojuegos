#pragma once
#include "SolidDynamic.h"
class Ball :public SolidDynamic
{
public:
	Ball(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
		double staticFriction, double dynamicFriction, double restitution, PxFilterData filterdata, Vector4& color = Vector4(1));
	~Ball();
protected:
};

