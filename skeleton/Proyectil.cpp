#include "Proyectil.h"
#include <iostream>

Proyectil::Proyectil(MVector3 pos, MVector3 velR, MVector3 accel, float dumping, float mass, float gravity, MVector3 vS, Vector4 sV)
	: Particle(pos,velR,accel,dumping,sv), mReal(mass), gReal(gravity), vSim(vS)
{
}

Proyectil::~Proyectil()
{
}

void Proyectil::integrate(double t)
{
	appGravity(t);
	Particle::integrate(t);
	//std::cout << pose_.p.x << "x " << pose_.p.y << "y " << pose_.p.z << "z " << '\n';
}

void Proyectil::appGravity(double t)
{
	mSim = mReal * pow(vel_.Module() / vSim.Module(), 2);
	gSim = gReal * pow(vel_.Module() / vSim.Module(), 2);
	accel_ = accel_ - MVector3(0, gSim, 0);

	vSim = vel_ + accel_.scalar(t);
	vel_ = vSim;
}
