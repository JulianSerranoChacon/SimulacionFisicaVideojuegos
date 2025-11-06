#include "ParticleGen.h"

ParticleGen::ParticleGen(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping, double maxTimeLife, Vector4 sV): Particle(Pos,vel,accel,dumping,sV),
timeLife(0),maxTimeLife(maxTimeLife)
{
	//gravedad
	accel_ -= MVector3(0, -10, 0);
}

ParticleGen::~ParticleGen()
{
}

bool ParticleGen::updateTimeLife(double t)
{
	timeLife += t;
	return timeLife < maxTimeLife;
}
