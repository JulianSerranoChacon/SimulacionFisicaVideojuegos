
#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

using MVector3 = Vector3D<float>;

class Particle
{
public:
	Particle(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping);
	~Particle();

	void integrate(double t);

private:

	void accel(double t);

	MVector3 vel_;
	MVector3 accel_;
	physx::PxTransform pose_;
	RenderItem* renderItem_;
	float dumping_;
};
