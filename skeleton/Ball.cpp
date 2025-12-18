#include "Ball.h"

Ball::Ball(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
	double staticFriction, double dynamicFriction, double restitution, Vector4& color):
	SolidDynamic(gScene,gPhysics,shape,transform,density,staticFriction, dynamicFriction, restitution, color)
{
}

Ball::~Ball()
{
}
