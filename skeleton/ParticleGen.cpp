#include "ParticleGen.h"

ParticleGen::ParticleGen(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping, double maxTimeLife,float size, Vector4 sV): Particle(Pos,vel,accel,dumping,size,sV),
timeLife(0),maxTimeLife(maxTimeLife)
{
	//gravedad
	//accel_ -= MVector3(0, -10, 0);
}
ParticleGen::ParticleGen(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping, double maxTimeLife, float size, physx::PxShape* s, Vector4 sV):
Particle(Pos, vel, accel, dumping, size,s, sV),timeLife(0), maxTimeLife(maxTimeLife)
{
	//gravedad
	//accel_ -= MVector3(0, -10, 0);
}


ParticleGen::~ParticleGen()
{
}

bool ParticleGen::updateTimeLife(double t)
{
	timeLife += t;
	return timeLife < maxTimeLife;
}
