#include "Particle.h"

Particle::Particle(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping, Vector4 sV) : vel_(vel), accel_(accel), dumping_(dumping),
pose_(Pos.getX(), Pos.getY(), Pos.getZ()), sv(sV)
{
	physx::PxShape* s = CreateShape(physx::PxSphereGeometry(5));
	renderItem_ = new RenderItem(s, &pose_, sv);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem_);
}

void Particle::integrate(double t)
{

	accel(t);
	pose_.p = pose_.p + (vel_.toVector3() * t) * pow(dumping_, t);
}

void Particle::accel(double t)
{
	vel_ = vel_ + accel_.scalar(t);
}
