#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

using MVector3 = Vector3D<float>;

class Particle
{
public:
	Particle(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping,float size = 5, Vector4 sV = Vector4(1,1,1,1));
	Particle(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping, float size = 5, physx::PxShape* s = nullptr, Vector4 sV = Vector4(1, 1, 1, 1));
	virtual ~Particle();

	virtual void integrate(double t);

	inline virtual Vector3 getPos() { return pose_.p; }

protected:

	virtual void accel(double t);

	MVector3 vel_;
	MVector3 accel_;
	physx::PxTransform pose_;
	RenderItem* renderItem_;
	float dumping_;
	Vector4 sv;
	float size;
};
