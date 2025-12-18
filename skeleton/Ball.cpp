#include "Ball.h"

Ball::Ball(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
	double staticFriction, double dynamicFriction, double restitution, PxFilterData filterdata, Vector4& color):
	SolidDynamic(gScene,gPhysics,shape,transform,density,staticFriction, dynamicFriction, restitution,filterdata, color)
{
}

Ball::~Ball()
{
}
