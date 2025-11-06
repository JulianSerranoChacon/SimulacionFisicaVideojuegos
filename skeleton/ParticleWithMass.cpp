#include "ParticleWithMass.h"

ParticleWithMass::ParticleWithMass(MVector3 pos, MVector3 velReal, MVector3 accel, float dumping, float mass,float timeLife, float size, Vector4 sV): 
	ParticleGen(pos,velReal,accel,dumping,timeLife,size,sV), mass(mass)
{
}

ParticleWithMass::ParticleWithMass(MVector3 pos, MVector3 velReal, MVector3 accel, float dumping, float mass, float timeLife, float size, physx::PxShape* s, Vector4 sV):
	ParticleGen(pos, velReal, accel, dumping, timeLife, size,s, sV), mass(mass)
{
}

ParticleWithMass::~ParticleWithMass()
{
	/*for (ForceGenerator* fg : fG) {

		if (fg != nullptr)
			delete fg;
		fg = nullptr;
	}*/
}

void ParticleWithMass::integrate(double t)
{
	for (ForceGenerator* fg : fG) {
		if (fg != nullptr)
			fg->addForce(this);
	}

	Particle::integrate(t);
}
