#include "Goal.h"

Goal::Goal(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, PxFilterData filter, Vector4& color):
	SolidStatic(gScene,gPhysics,shape,transform,filter,color)
{
}

Goal::~Goal()
{
}
