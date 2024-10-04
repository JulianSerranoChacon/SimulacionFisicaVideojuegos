#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

using MVector3 = Vector3D<float>;

class Particle
{
public:
	Particle(MVector3 Pos, MVector3 vel);
	~Particle();

	void integrate(double t);

private:
	MVector3 vel_;
	physx::PxTransform pose_;
	RenderItem* renderItem_;
};