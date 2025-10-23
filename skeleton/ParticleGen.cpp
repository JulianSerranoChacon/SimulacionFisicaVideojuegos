#include "ParticleGen.h"

ParticleGen::ParticleGen(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping, double maxTimeLife): Particle(Pos,vel,accel,dumping), 
timeLife(0),maxTimeLife(maxTimeLife)
{
}

ParticleGen::~ParticleGen()
{
}

bool ParticleGen::updateTimeLife(double t)
{
	timeLife += t;
	return timeLife < maxTimeLife;
}
