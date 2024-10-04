#include "Particle.h"

Particle::Particle(MVector3 Pos, MVector3 vel): vel_(vel), pose_(Pos.getX(), Pos.getY(), Pos.getZ())
{
	physx::PxShape* s = CreateShape(physx::PxSphereGeometry(5));
	Vector4 sv = Vector4(1, 1, 1, 1);
	renderItem_ = new RenderItem(s, &pose_, sv);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem_);
}

void Particle::integrate(double t)
{
	pose_.p = pose_.p + vel_.toVector3() * t;
}
